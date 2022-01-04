#ifndef Sensors_h
#define Sensors_h
#include "Arduino.h"

#include <Wire.h>
#include <Arduino_APDS9960.h>

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

class CLRSENS
{
  public:
    struct color {
      int r;
      int g;
      int b;
    };
    CLRSENS(uint8_t intPin);
    CLRSENS(uint8_t intPin, color offset_clr);
    bool startColor();
    color getColor();
    color getOffset();
    color setOffset(color offset_clr);

  private:
    color _prev_color_val;
    color _color_val;
    color _offset_clr{0, 0, 0};
    TwoWire _I2CCLR;
    APDS9960 _clr_sens;
};

#endif
