#include <esp32cam.h>
#include <WebServer.h>
#include <WiFi.h>

const char* ssid = "H&B";
const char* pwd = "Bardo04@SUB31";

WebServer server(80);

static auto loRes = esp32cam::Resolution::find(320, 240);
static auto hiRes = esp32cam::Resolution::find(800, 600);

void serveJpg(){
  auto frame = esp32cam::capture();

  if (frame == nullptr){
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }
  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(), 
                static_cast<int>(frame->size()));

  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
}


void handleJpgLo(){
  if(!esp32cam::Camera.changeResolution(loRes)){
    Serial.println("SET-LO-RES FAIL");
  }
  serveJpg();
}

void handleJpgHi(){
  if(!esp32cam::Camera.changeResolution(hiRes)){
    Serial.println("SET-HI-RES FAIL");
  }
  serveJpg();
}



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

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
  }

  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/cam-hi.jpg");

  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/cam-lo.jpg");

  server.on("/cam-lo.jpg", handleJpgLo);
  server.on("/cam-hi.jpg", handleJpgHi);

  server.begin();

}

void loop() {
  server.handleClient();

}
