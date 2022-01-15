#include "Arduino.h"
#include "motor.h"
#include "analogWrite.h"
#include <ESP32Servo.h>
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

//might want to consider some kind of deadzone for the controller for this movement
void manualMovement(int channel2, int channel1, Motor &motorLF, Motor &motorRF, int multiplier) { //channel2 is left U/D, channel 1 is right L/R
  int turningMultiplier = 0.0; //how responsive should the turning be?
  int deadZone = 10;
  if (channel2 == 0 && (channel1 > deadZone || channel1 < deadZone)) { //rotate on spot
    Serial.println("Rotating!");
    motorLF.rotate(int(-channel1*multiplier));
    motorRF.rotate(int(channel1*multiplier));

  }
  else if (channel1 == 0 && (channel2 > deadZone || channel2 < deadZone)) { //move forward/backward straight
    if (channel2 < 0) {
      Serial.print(channel2*0.5);
      motorLF.rotate(int(channel2*multiplier));
      motorRF.rotate(int(channel2*multiplier));

    }
    else {
      motorLF.rotate(channel2);
      motorRF.rotate(channel2);
    }
  }
  else if (channel1 != 0 && channel2 != 0) { //some kind of diagonal movement
    int turningSpeed = channel2 * turningMultiplier;
    if (channel1 > 0) { //going left
 
      motorLF.rotate(turningSpeed);
      motorRF.rotate(channel2);
    }
    else {
      motorRF.rotate(turningSpeed);
      motorLF.rotate(channel2);
    }
  }
  else {
    Serial.println("Stopped!");
    motorLF.stop_rotate();
    motorRF.stop_rotate();

  }
}

void checkclawState(int &clawState, bool clawPress, int channel9){
    if (clawPress == true && clawState == 0) { //open claw
      clawState = 1;
    }
    else if (clawState == 1 && channel9 != 255) { //make sure switch is unpressed first
      clawState = 2;
    }
    else if (clawState == 2 && channel9 == 255){
      clawState = 0;
    }
}
