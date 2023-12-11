#include "servoTools.h"

ServoTools servoController(5, 6, 2, 3);  // Instancia de la clase ServoTools
uint8_t angle;
int mode = 0;


int esp32camResponse();
void selectMode();

void setup() {
  Serial.begin(115200);
  servoController.initServos();
}

void loop() {
  esp32camResponse();
  selectMode();
  delay(10);
}

int esp32camResponse() {
  while (!Serial.available()) {
    delay(100);
  }
  return 0;
}

void selectMode() {
  switch (mode) {
    case 1:
      servoController.initialPos();
      Serial.println(99);
      break;
    case 2:
      for (int i =0; i<= 4; i++){
        servoController.loopCapture(i);
        Serial.println(99);
        delay(700);
      }
      break;
    case 3:
        servoController.loopCapture(2);
        Serial.println(99);
    default:
        Serial.println(99);
      break;
  }
}