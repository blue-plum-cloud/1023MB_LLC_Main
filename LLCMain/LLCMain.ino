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
int counterL = 0;
int counterR = 0;
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
  colorStarted = colorSen.startColor();
  if (!colorStarted)
    Serial.println("Error starting color sensor...");
}

void loop() { //test for now
  printChannels(chout);
  if (chout[5] == -255) { //check channel 6
    //emergency stop (UP)
    manualMovement(0, 0, motorLF, motorRF);
    countVar(chout[6]);
    servoMove(counterL);
  }
  else if (chout[5] == 0) {
    //manual mode (MIDDLE)
    //use channel 2 for forward/backward and channel 1 for left/right
    manualMovement(chout[1], chout[0], motorLF, motorRF);
    countVar(chout[6]);
    doubleServo(chout[6]);
  }
  else if (chout[5] == 255) {
    //auto mode (DOWN)
    countVar(chout[6]);
    doubleServo(chout[6]);
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


int currentPos = 0;
int currentTime = 0;
int prevTime = 0;

void countVar(int channel7) {
  if (channel7 == 255) {
    //    if (millis() - prevTime >= 1) {
    //      counterL++;
    //      counterL = constrain(counterL, 0, 180);
    //      prevTime = millis();
    //    }
    counterL += 5;
    counterL = constrain(counterL, 0, 180);
    counterR = 180 - counterL;
  }
  else if (channel7 == -255) {
    //    if (millis() - prevTime >= 1) {
    //      counterL--;
    //      counterL = constrain(counterL, 0, 180);
    //      prevTime = millis();
    //    }
    counterL -= 5;
    counterL = constrain(counterL, 0, 180);
    counterR = 180 - counterL;
  }
  Serial.println(counterL);
  //  prevTime = currentTime;
}
void servoMove(int counter) {
  //int pos2 = 180;
  if (currentPos < counterL) {
    for (int pos = currentPos; pos <= counterL; pos += 1) { // sweep from 0 degrees to 180 degrees
      // in steps of 1 degree
      servoL.write(pos);
      servoR.write(180-pos);
      //pos2--;
      delay(1);             // waits 20ms for the servo to reach the position
    }
  }
  else if (currentPos > counterL) {
    for (int pos = currentPos; pos >= counterL; pos -= 1) { // sweep from 0 degrees to 180 degrees
      // in steps of 1 degree
      servoL.write(pos);
      servoR.write(180-pos);
      //pos2--;
      delay(1);             // waits 20ms for the servo to reach the position
    }
  }
  currentPos = counterL;

}
void doubleServo(int channel){
  if(channel==255){
    servoL.writeMicroseconds(700);
    servoR.writeMicroseconds(2300);
  }
  else if(channel==0){
    servoL.writeMicroseconds(1500);
    servoR.writeMicroseconds(1500);
  }
  else if(channel==-255){
    servoL.writeMicroseconds(2300);
    servoR.writeMicroseconds(700);
  }
}
