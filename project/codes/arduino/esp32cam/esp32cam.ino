#include <Arduino.h>
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

struct Data {
  int mode = 0;
  int state = 0;
  int posCapture = 0;
  int servos[4] = {0, 0, 0, 0};
};

Data data;

// Funciones declaradas
void serveJpg();
void handleJpgLo();
void handleJpgHi();
void startServer();
void sendStatusJson();
void receiveStatusJson();
void flashIntensity(int i);
void pulseFlash(int a, int b);
void selectMode();
void sendSerialData(const Data& data);
void receiveSerialData(Data& data);

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

void selectMode() {
  sendSerialData(data);
  receiveSerialData(data);
  switch (data.mode) {
    case 0:
      data.posCapture = 0;
      pulseFlash(20, 100);
      break;
    case 1: 
      if (data.posCapture > 4){
        data.posCapture = 0;
      }
      else{
        data.posCapture++;
      }
      break;
      case 2:
        data.posCapture = 0;
        pulseFlash(20, 50);
        break;
      case 3:
        data.posCapture = 1;
        break;
    default:
      flashIntensity(0);
      break;
  }
  
}

void sendSerialData(const Data& data) {
  DynamicJsonDocument doc(256);
  doc["mode"] = data.mode;
  doc["state"] = data.state;
  doc["posCapture"] = data.posCapture;
  JsonArray servosArray = doc.createNestedArray("servos");
  for (int i = 0; i < 4; i++) {
    servosArray.add(data.servos[i]);
  }

  String jsonString;
  serializeJson(doc, jsonString);
  Serial.println(jsonString);
}

void receiveSerialData(Data& data) {
  while (Serial.available()) {
    String jsonString = Serial.readStringUntil('\n');

    DynamicJsonDocument doc(256);
    DeserializationError error = deserializeJson(doc, jsonString);

    if (!error) {
      data.mode = doc["mode"];
      data.state = doc["state"];
      data.posCapture = doc["posCapture"];
      JsonArray servosArray = doc["servos"];
      for (int i = 0; i < 4; i++) {
        data.servos[i] = servosArray[i];
      }
    }
  }
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

void flashIntensity(int i) {
  analogWrite(flashPin, i);
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

void serveJpg() {
  auto frame = esp32cam::capture();

  if (frame == nullptr) {
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }
  delay(1);
  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
                static_cast<int>(frame->size()));

  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
}

void sendStatusJson() {
  String jsonStr = server.arg("plain");

  DynamicJsonDocument doc(256);
  DeserializationError error = deserializeJson(doc, jsonStr);

  if (error) {
    server.send(400, "text/plain", "Bad Request");
  } else {
    data.mode = doc["mode"];
    data.state = doc["state"];
    data.state = doc["posCapture"];

    JsonObject servosObj = doc["servos"];
    data.servos[0] = servosObj["s1"];
    data.servos[1] = servosObj["s2"];
    data.servos[2] = servosObj["s3"];
    data.servos[3] = servosObj["s4"];

    server.send(200, "text/plain", "OK");
  }
}

void receiveStatusJson() {
  DynamicJsonDocument doc(256);
  doc["mode"] = data.mode;
  doc["state"] = data.state;
  data.state = doc["posCapture"];

  JsonObject servosObj = doc.createNestedObject("servos");
  servosObj["s1"] = data.servos[0];
  servosObj["s2"] = data.servos[1];
  servosObj["s3"] = data.servos[2];
  servosObj["s4"] = data.servos[3];

  String jsonStr;
  serializeJson(doc, jsonStr);
  server.send(200, "application/json", jsonStr);
}
