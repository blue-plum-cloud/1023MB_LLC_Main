#include "Arduino.h"
#include "sensors.h"

// Ultrasonic Sensor

HCSR04::HCSR04(int echoPin, int trigPin) {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  _echoPin = echoPin;
  _trigPin = trigPin;
}

int HCSR04::read_distance() {
  // Clears the trigPin condition
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int duration = pulseIn(_echoPin, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  return distance;
}

// IR Line Sensor

IRLINE::IRLINE(int inputPin) {
  pinMode(inputPin, INPUT);
  _inputPin = inputPin;
}

boolean IRLINE::check_line() {
  boolean val = digitalRead(_inputPin);
  return val;
}

// Color Sensor

CLRSENS::CLRSENS(uint8_t intPin)  :
  CLRSENS(intPin, _offset_clr) {
}

CLRSENS::CLRSENS(uint8_t intPin, color offset_clr) :
  _offset_clr(offset_clr),
  _I2CCLR(0),
  _clr_sens(_I2CCLR, intPin)
{
}

bool CLRSENS::startColor() {
  return _clr_sens.begin();
}

CLRSENS::color CLRSENS::getColor() {
  if (_clr_sens.colorAvailable()) {
    _prev_color_val = _color_val;
    _clr_sens.readColor(_color_val.r, _color_val.g, _color_val.b);
    _color_val.r -= _offset_clr.r;      // Offset vals
    _color_val.g -= _offset_clr.g;
    _color_val.b -= _offset_clr.b;
  }
  return _color_val;
}

CLRSENS::color CLRSENS::getOffset() {
  return _offset_clr;
}

CLRSENS::color CLRSENS::setOffset(color offset_clr) {
  _offset_clr = offset_clr;
}
