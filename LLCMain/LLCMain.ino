#include "config.h"
#include "flysky.h"
#include "motor.h"
#include "sensors.h"
#include <ESP32Servo.h>

//Instantiating objects will also set up the pins for the component.
Motor motorLF(ENABLEAF, MOTORPIN1_LF, MOTORPIN2_LF, true);
Motor motorRF(ENABLEBF, MOTORPIN1_RF, MOTORPIN2_RF, true);

Servo servoL;
Servo servoR;
Servo servoClaw;
Servo servoGate;
int counterClaw = 0;
int counterGate = 0;
int gateminLimit = 0;
int gatemaxLimit = 120;
int liftminLimit = 100;
int liftmaxLimit = 170;
int gatePos = 0;
int clawPos = 0;
// === Sensors ===
//HCSR04 sensor1(ECHO_PIN,TRIG_PIN);
//IRLINE sensor2(ECHO_PIN);

// Color sensor
bool colorStarted{false};
CLRSENS::color colorVal = { -1, -1, -1};

CLRSENS colorSen(INT_COLOR);

int chout[10];

void setup() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  Serial.begin(9600);
  initializeRC();
  servoL.attach(servoLpin, minUs, maxUs);
  servoR.attach(servoRpin, minUs, maxUs);
  servoClaw.attach(servoClawpin, min180Us,max180Us);
  servoGate.attach(servoGatepin, min180Us,max180Us);
  colorStarted = colorSen.startColor();
  if (!colorStarted)
    Serial.println("Error starting color sensor...");
}

void loop() { //test for now
  printChannels(chout);
  if (chout[5] == -255) { //check channel 6
    //emergency stop (UP)
    manualMovement(0, 0, motorLF, motorRF);
  }
  else if (chout[5] == 0) {
    //manual mode (MIDDLE)
    //use channel 2 for forward/backward and channel 1 for left/right
    manualMovement(chout[1], chout[0], motorLF, motorRF);
    counterClaw = countVar(chout[8],counterClaw,liftminLimit, liftmaxLimit,5);
    counterGate = countVar(chout[7], counterGate, gateminLimit, gatemaxLimit,10);
    clawPos = servoMove(counterClaw, clawPos, servoClaw);
    gatePos = servoMove(counterGate, gatePos, servoGate);
    doubleServo(chout[6]);
  }
  else if (chout[5] == 255) {
    //auto mode (DOWN)
  }
  //  int spd = map(chout[0], 1000, 2000, -255, 255);
  //  spd = constrain(spd, -255,255);
  //  motor1.rotate(spd);
  //  delay(50);
  //  boolean check = sensor2.check_line();
  //  Serial.print("Line: ");
  //  Serial.println(check);
  //  delay(50);

  if (colorStarted) {
    colorVal  = colorSen.getColor();
    Serial.print("R:");
    Serial.print(colorVal.r);
    Serial.print("\tG:");
    Serial.print(colorVal.g);
    Serial.print("\tB:");
    Serial.println(colorVal.b);
  }

  delay(50);
}

int currentTime = 0;
int prevTime = 0;

int countVar(int channel7, int counter, int minLimit, int maxLimit, int spd) {
  int counterL = counter;
  if (channel7 == 255) {
    //    if (millis() - prevTime >= 1) {
    //      counterL++;
    //      counterL = constrain(counterL, 0, 180);
    //      prevTime = millis();
    //    }
    counterL += spd;
    counterL = constrain(counterL, minLimit, maxLimit);
  }
  else if (channel7 == -255) {
    //    if (millis() - prevTime >= 1) {
    //      counterL--;
    //      counterL = constrain(counterL, 0, 180);
    //      prevTime = millis();
    //    }
    counterL -= spd;
    counterL = constrain(counterL, minLimit, maxLimit);
  }
  Serial.println(counterL);
  return counterL;
  //  prevTime = currentTime;
}
int servoMove(int counter,int currentPos, Servo &servoL) {
  //int pos2 = 180;
  if (currentPos < counter) {
    for (int pos = currentPos; pos <= counter; pos += 1) { // sweep from 0 degrees to 180 degrees
      Serial.println("opening");
      // in steps of 1 degree
      servoL.write(pos);
      //pos2--;
      delay(1);             // waits 20ms for the servo to reach the position
    }
  }
  else if (currentPos > counter) {
    for (int pos = currentPos; pos >= counter; pos -= 1) { // sweep from 0 degrees to 180 degrees
      Serial.println("closing");
      // in steps of 1 degree
      servoL.write(pos);
      //pos2--;
      delay(1);             // waits 20ms for the servo to reach the position
    }
  }
  currentPos = counter;
  return currentPos;

}
void doubleServo(int channel){
  if(channel==255){
    servoL.writeMicroseconds(1300);
    servoR.writeMicroseconds(1700);
  }
  else if(channel==0){
    servoL.writeMicroseconds(1500);
    servoR.writeMicroseconds(1500);
  }
  else if(channel==-255){
    servoL.writeMicroseconds(1700);
    servoR.writeMicroseconds(1300);
  }
}
