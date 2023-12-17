#include "servoTools.h"


ServoTools servoController(5, 6, 2, 3);  // Instancia de la clase ServoTools
uint8_t angle;
int mode = 0;
int state = 0;
int posCapture = 0;
int posServos[4];


int esp32camResponse();
void selectMode();


void setup() {
  Serial.begin(115200);
  Serial.begin(115200);
  
  servoController.initServos();
  servoController.getPos(posServos);
}

void loop() {
  
  
}

int esp32camResponse() {
  while (!Serial.available()) {
    delay(100);
  }
  return 0;
}


void selectMode(){
  switch(mode){
    
    case 0:
      servoController.initialPos();
      break;
    default:
      servoController.loopCapture(posCapture);
      break;
  }
  servoController.getPos(posServos);
}
