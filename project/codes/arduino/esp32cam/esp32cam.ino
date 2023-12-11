#include <esp32cam.h>
#include <WebServer.h>
#include <WiFi.h>
#include <ArduinoJson.h>

const char* ssid = "H&B";
const char* pwd = "Bardo04@SUB31";

WebServer server(80);

static auto loRes = esp32cam::Resolution::find(320, 240);
static auto hiRes = esp32cam::Resolution::find(800, 600);

#define flashPin 4
#define NUM_SERVOS 4
int state = 0;
int mode = 0;
uint8_t servos[NUM_SERVOS] = {0, 0, 0, 0};

// Funciones declaradas
void serveJpg();
void handleJpgLo();
void handleJpgHi();
void startServer();
void sendStatusJson();
void receiveStatusJson();
void flashIntensity(int i);
void pulseFlash(int a, int b);
int nanoResponse();
void selectMode();

void setup() {
  Serial.begin(115200);
  Serial.println();

  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);

    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }

  pinMode(flashPin, OUTPUT);
  analogWrite(flashPin, 0);

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  startServer();
}

void loop() {
  selectMode();
  server.handleClient();
  delay(10);
}

void serveJpg() {
  auto frame = esp32cam::capture();

  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }

  flashIntensity(255);
  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
                static_cast<int>(frame->size()));

  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
  delay(10);
  flashIntensity(0);
}

void handleJpgLo() {
  if (!esp32cam::Camera.changeResolution(loRes)) {
    Serial.println("SET-LO-RES FAIL");
  }
  serveJpg();
}

void handleJpgHi() {
  if (!esp32cam::Camera.changeResolution(hiRes)) {
    Serial.println("SET-HI-RES FAIL");
  }
  serveJpg();
}

void sendStatusJson() {
  String jsonStr = server.arg("plain");

  DynamicJsonDocument doc(256);
  DeserializationError error = deserializeJson(doc, jsonStr);
  Serial.println(jsonStr);
  delay(500);

  if (error) {
    server.send(400, "text/plain", "Bad Request");
  } else {
    mode = doc["mode"];
    state = doc["state"];

    JsonObject servosObj = doc["servos"];
    servos[0] = servosObj["s1"];
    servos[1] = servosObj["s2"];
    servos[2] = servosObj["s3"];
    servos[3] = servosObj["s4"];

    server.send(200, "text/plain", "OK");
  }
}

void receiveStatusJson() {
  DynamicJsonDocument doc(256);
  doc["mode"] = mode;
  doc["state"] = state;

  JsonObject servosObj = doc.createNestedObject("servos");
  servosObj["s1"] = servos[0];
  servosObj["s2"] = servos[1];
  servosObj["s3"] = servos[2];
  servosObj["s4"] = servos[3];

  String jsonStr;
  serializeJson(doc, jsonStr);
  server.send(200, "application/json", jsonStr);
}

void startServer() {
  Serial.println("Conexión exitosa");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Puerta de enlace (Gateway): ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("Máscara de subred (Subnet): ");
  Serial.println(WiFi.subnetMask());

  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/cam-hi.jpg");

  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/cam-lo.jpg");

  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/status");

  server.on("/cam-lo.jpg", handleJpgLo);
  server.on("/cam-hi.jpg", handleJpgHi);
  server.on("/status", HTTP_POST, sendStatusJson);
  server.on("/status", HTTP_GET, receiveStatusJson);

  server.begin();
}

void flashIntensity(int i) {
  analogWrite(flashPin, i);
}

void pulseFlash(int a, int b) {
  for (int i = a; i <= b; i++) {
    flashIntensity(i);
    delay(10);
  }
  for (int i = b; i >= a; i--) {
    flashIntensity(i);
    delay(10);
  }
}

int nanoResponse() {
  while (!Serial.available()) {
    state = 1;
    server.handleClient();
    delay(100);
  }
  return 0;
}

void selectMode() {
  switch (mode) {
    case 0:
      Serial.println(mode+1);
      pulseFlash(20, 100);
      state = 0;
      break;
    case 1:
      Serial.println(mode+1);
      state = nanoResponse();
      break;
    case 2:
      Serial.println(mode+1);
      //pasar posiciones de los servos 
      //para seguir el objeto.
      state = nanoResponse();
    default:
      state = 0;
      break;
  }
}
