#ifndef Sensors_h
#define Sensors_h
#include "Arduino.h"

class HCSR04
{
  public:
    HCSR04(int echoPin, int trigPin); //constructor
    int read_distance();
  private:
    int _echoPin;
    int _trigPin;
};

class IRLINE
{
  public:
    IRLINE(int inputPin);
    bool check_line();
  private:
    int _inputPin;
};

#endif
