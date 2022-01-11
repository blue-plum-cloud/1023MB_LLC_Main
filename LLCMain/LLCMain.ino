#include "config.h"
#include "flysky.h"
#include "motor.h"
#include "sensors.h"
#include <ESP32Servo.h>

//Instantiating objects will also set up the pins for the component.
Motor motorLF(ENABLEAF, MOTORPIN1_LF, MOTORPIN2_LF, true);
Motor motorRF(ENABLEBF, MOTORPIN1_RF, MOTORPIN2_RF, true);
IRLINE IR_left(32);
IRLINE IR_right(33);
IRLINE IR_center(25);

Servo servoL;
Servo servoR;
Servo servoClaw;
Servo servoGate;
int counterClaw = 0;
int counterGate = 0;
int gateminLimit = 130;
int gatemaxLimit = 180;
int clawminLimit = 100;
int clawmaxLimit = 180;
int gatePos = 0;
int clawPos = 0;
int prevTime;
int clawState = 0;
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
  servoClaw.attach(servoClawpin, min180Us, max180Us);
  servoGate.attach(servoGatepin, min180Us, max180Us);
  prevTime = millis();
  colorStarted = colorSen.startColor();
  if (!colorStarted)
    Serial.println("Error starting color sensor...");
}
void loop() { //test for now
  printChannels(chout);
  bool clawPress = buttonTimer(chout[8], prevTime);
  int clawChannel = chout[8];
  if (chout[5] == -255) { //check channel 6
    //emergency stop (UP)
    manualMovement(0, 0, motorLF, motorRF, 0);
  }
  else if (chout[5] == 0) {
    //manual mode (MIDDLE)
    //use channel 2 for forward/backward and channel 1 for left/right
    if (chout[4] == 255) {
      manualMovement(chout[1], chout[0], motorLF, motorRF, 1);
    }
    else {
      manualMovement(chout[1], chout[0], motorLF, motorRF, 0.6);
    }
//    checkclawState(clawState, clawPress, chout[8]);
//    if (clawState == 2 || clawState == 1)
//      clawChannel = 255;
 
    counterClaw = countVar(clawChannel, counterClaw, clawminLimit, clawmaxLimit, 10);
    counterGate = countVar(chout[7], counterGate, gateminLimit, gatemaxLimit, 10);
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


// -----SERVO MOTOR AND DC MOTOR STUFF-----//


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
int servoMove(int counter, int currentPos, Servo &servoL) {
  //int pos2 = 180;
  if (currentPos < counter) {
    for (int pos = currentPos; pos <= counter; pos += 1) { // sweep from 0 degrees to 180 degrees;
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
void doubleServo(int channel) {
  Serial.println(channel);
  if (channel <= -250) {
    Serial.println("down");
    servoL.writeMicroseconds(1100);
    servoR.writeMicroseconds(1900);
  }
  else if (channel < 250 && channel > -250) {
    Serial.println("stop");
    servoL.write(90);
    servoR.write(90);
  }
  else if (channel >= 250) {
    Serial.println("up");
    servoL.writeMicroseconds(1700);
    servoR.writeMicroseconds(1300);
  }
}
