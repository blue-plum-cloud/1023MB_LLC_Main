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
void manualMovement(int channel2, int channel1, Motor motorLF, Motor motorRF) { //channel2 is left U/D, channel 1 is right L/R
  int turningMultiplier = 0.5; //how responsive should the turning be?
  if (channel2 == 0 && channel1 != 0) { //rotate on spot
    Serial.println("Rotating!");
    motorLF.rotate(channel1);
    motorRF.rotate(-channel1);
  }
  else if (channel1 == 0 && channel2 != 0) { //move forward/backward straight
    Serial.println("Moving Straight!");
    motorLF.rotate(channel2);
    motorRF.rotate(channel2);
  }
  else if (channel1 != 0 && channel2 != 0) { //some kind of diagonal movement
    int turningSpeed = channel2 * turningMultiplier;
    if (channel1 < 0) { //going left
      Serial.println("Turning Left!");
      motorLF.rotate(turningSpeed);
      motorRF.rotate(channel2);
    }
    else {
      Serial.println("Turning Right!");
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


//int countVar(int channel7, int counter) { //counts how long var is scrolled
//  if (channel7 == 255) {
//    //    if (millis() - prevTime >= 1) {
//    //      counterL++;
//    //      counterL = constrain(counterL, 0, 180);
//    //      prevTime = millis();
//    //    } //don't really need this as the ESP32 doesn't count that fast
//    counter += 5;
//    counter = constrain(counter, 0, 180);
//  }
//  else if (channel7 == -255) {
//    //    if (millis() - prevTime >= 1) {
//    //      counterL--;
//    //      counterL = constrain(counterL, 0, 180);
//    //      prevTime = millis();
//    //    } 
//    counter -= 5;
//    counter = constrain(counter, 0, 180);
//  }
//  //  prevTime = currentTime;
//  return counter;
//}
//int servoMove(int counter, int currentPos, Servo servoL, Servo servoR) {
//  //int pos2 = 180;
//  if (currentPos < counter) {
//    for (int pos = currentPos; pos <= counter; pos += 1) { // sweep from 0 degrees to 180 degrees
//      // in steps of 1 degree
//      servoL.write(pos);
//      servoR.write(180-pos);
//      //pos2--;
//      delay(1);             // waits 20ms for the servo to reach the position
//    }
//  }
//  else if (currentPos > counter) {
//    for (int pos = currentPos; pos >= counter; pos -= 1) { // sweep from 0 degrees to 180 degrees
//      // in steps of 1 degree
//      servoL.write(pos);
//      servoR.write(180-pos);
//      //pos2--;
//      delay(1);             // waits 20ms for the servo to reach the position
//    }
//  }
//  currentPos = counter;
//  return currentPos;
//
//}
