#include "servoTools.h"

ServoTools::ServoTools(uint8_t pinServo1, uint8_t pinServo2, uint8_t pinServo3, uint8_t pinServo4) {
  this->pinServo1 = pinServo1;
  this->pinServo2 = pinServo2;
  this->pinServo3 = pinServo3;
  this->pinServo4 = pinServo4;
}

void ServoTools::initServos() {
  servo1.attach(pinServo1);  
  servo2.attach(pinServo2);
  servo3.attach(pinServo3);
  servo4.attach(pinServo4);
  
  servo1.write(posStart1);
  servo2.write(posStart2);
  servo3.write(posStart3);
  servo4.write(posStart4);
  delay(500);
}
void ServoTools::initialPos(){
  this->moveServo(1, this->posStart1);
  this->moveServo(2, this->posStart2);
  this->moveServo(3, this->posStart3);
  this->moveServo(4, this->posStart4);
  delay(500);
}

void ServoTools::moveServo(uint8_t numServo, uint8_t angle) {

  switch (numServo) {
    case 1:
      if(valideRange(1, angle)){
       smoothServo(this->servo1, angle, this->currentPos1); 
      }
      break;
    case 2:
      if(valideRange(2, angle)){
       smoothServo(this->servo2, angle, this->currentPos2); 
      }
      break;
    case 3:
      if(valideRange(3, angle)){
       smoothServo(this->servo3, angle, this->currentPos3); 
      }
      break;
    case 4:
      if(valideRange(4, angle)){
       smoothServo(this->servo4, angle, this->currentPos4); 
      }
      break;
    default:
      return;  
  }

  
}

void ServoTools::smoothServo(Servo &servo, uint8_t desiredPos, uint8_t &currentPos){

  if(desiredPos > currentPos){
    for(uint8_t i = currentPos; i <= desiredPos; i++){
      servo.write(i);
      delay(25);
    }
  }
  else{
    for(uint8_t i = currentPos; i >= desiredPos; i--){
      servo.write(i);
      delay(25);
    }
  }
  currentPos = desiredPos;
}

bool ServoTools::valideRange(uint8_t numServo, uint8_t angle){
  switch (numServo) {
    case 1:
      if(60 <= angle && angle<=130){
        return true;
      }
      break;
    case 2:
      if(70 < angle && angle < 160){
        return true;
      }
      break;
    case 3:
      if(20 < angle && angle<170){
        return true;
      }
      break;
    case 4:
      if(0 < angle && angle<90){
        return true;
      }
      break;
    default:
      return false;  // Si se proporciona un número de servo no válido, salimos sin hacer nada
  }
  return false;
}

void ServoTools::loopCapture(int i){
  if (i ==0){
    smoothServo(this->servo1, 105, this->currentPos1);
    smoothServo(this->servo2, 165, this->currentPos2);
    smoothServo(this->servo3,  85, this->currentPos3);
    smoothServo(this->servo4,  15, this->currentPos4);
    delay(500);
  }
  if (i ==1){
    smoothServo(this->servo1,  80, this->currentPos1);
    smoothServo(this->servo2, 140, this->currentPos2);
    smoothServo(this->servo3,  85, this->currentPos3);
    smoothServo(this->servo4,  30, this->currentPos4);
    delay(500);
  }
  if (i ==2){
    smoothServo(this->servo1,  70, this->currentPos1);
    smoothServo(this->servo2, 120, this->currentPos2);
    smoothServo(this->servo3,  90, this->currentPos3);
    smoothServo(this->servo4,  60, this->currentPos4);
    delay(500);
  }
  if (i ==3){
    smoothServo(this->servo1,  60, this->currentPos1);
    smoothServo(this->servo2,  90, this->currentPos2);
    smoothServo(this->servo3,  85, this->currentPos3);
    smoothServo(this->servo4,  90, this->currentPos4);
    delay(500);
  }
  if (i ==4){
    smoothServo(this->servo2, 120, this->currentPos2);
  }

}
