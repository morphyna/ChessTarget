#include "servoTools.h"

ServoTools servoController(5, 6, 2, 3);  // Instancia de la clase ServoTools
uint8_t angle;
void setup() {
  Serial.begin(115200);
  servoController.initServos();
}

void loop() {
  if (Serial.available() >= 2 * sizeof(int)) {
    int dato1;
    int dato2;

    Serial.readBytes((char*)&dato1, sizeof(dato1)); 
    Serial.readBytes((char*)&dato2, sizeof(dato2));

    // Haz lo que quieras con los datos recibidos
    // En este ejemplo, simplemente los imprime
    Serial.print("Dato 1: ");
    Serial.println(dato1);
    Serial.print("Dato 2: ");
    Serial.println(dato2);
  }
  if (dato1==1){
    servoController.loopCapture(dato2);
    delay(1000);
  }
  
}
