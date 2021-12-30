#ifndef Motor_h
#define Motor_h
#include "Arduino.h"

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
#endif
