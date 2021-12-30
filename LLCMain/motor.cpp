#include "Arduino.h"
#include "motor.h"

Motor::Motor(int enablePin, int motorPin1, int motorPin2, bool left) {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  _left = left;
  _enablepin = enablePin;
  _motorPin1 = motorPin1;
  _motorPin2 = motorPin2;
}

void Motor::rotate(int spd) {
  analogWrite(_enablepin, abs(spd));
  if (spd > 0) {
    digitalWrite( _motorPin1, HIGH);
    digitalWrite( _motorPin2, LOW);
  }
  else if (spd < 0) {
    digitalWrite( _motorPin1, LOW);
    digitalWrite( _motorPin2, HIGH);
  }
  else
    stop_rotate();
}
void Motor::stop_rotate() {
  digitalWrite( _motorPin1, HIGH);
  digitalWrite( _motorPin2, HIGH);
}
