#ifndef SERVOTOOLS_H
#define SERVOTOOLS_H

#include <Arduino.h>
#include <Servo.h>

class ServoTools {
public:
  ServoTools(uint8_t pinServo1 = 2, uint8_t pinServo2 = 3, uint8_t pinServo3 = 5, uint8_t pinServo4 = 6);  // Constructor

  void initServos();
  void initialPos();
  void moveServo(uint8_t numServo, uint8_t angle);
  void smoothServo(Servo &servo, uint8_t desiredPos, uint8_t &currentPos);
  bool valideRange(uint8_t numServo, uint8_t angle);
  void loopCapture(int i);
  void getPos(int pos[4]);


  

private:
  uint8_t pinServo1; 
  uint8_t pinServo2; 
  uint8_t pinServo3; 
  uint8_t pinServo4; 

  Servo servo1;
  Servo servo2;
  Servo servo3;
  Servo servo4;
  
  uint8_t posStart1 = 130;
  uint8_t posStart2 = 130;
  uint8_t posStart3 = 85;
  uint8_t posStart4 = 45;

  uint8_t currentPos1 = posStart1;
  uint8_t currentPos2 = posStart2;
  uint8_t currentPos3 = posStart3;
  uint8_t currentPos4 = posStart4;
  
  uint8_t currentPos[4]= {
    currentPos1,
    currentPos2,
    currentPos3,
    currentPos4,
  };

};

#endif
