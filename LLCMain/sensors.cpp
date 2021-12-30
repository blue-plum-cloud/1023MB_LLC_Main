#include "Arduino.h"
#include "sensors.h"

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

IRLINE::IRLINE(int inputPin){
  pinMode(inputPin, INPUT);
  _inputPin = inputPin;
}

boolean IRLINE::check_line(){
  boolean val = digitalRead(_inputPin);
  return val; 
}
