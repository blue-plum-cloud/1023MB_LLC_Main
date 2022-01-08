#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include <ESP32Servo.h>
class Motor
{
  public:
    Motor(int enablePin, int motorPin1, int motorPin2, bool left); //constructor
    void rotate(int spd);
    void stop_rotate();
  private:
    bool _left;
    int _enablepin;
    int _motorPin1;
    int _motorPin2;
};
void manualMovement(int channel2, int channel1, Motor motorLF, Motor motorRF);
int servoMove(int counter, int currentPos, Servo servoL, Servo servoR);
int countVar(int channel7, int counter);
#endif
