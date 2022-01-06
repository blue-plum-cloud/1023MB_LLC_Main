#include "config.h"
#include "flysky.h"
#include "motor.h"
#include "sensors.h"
#include <ESP32Servo.h>

//Instantiating objects will also set up the pins for the component.
Motor motorLF(ENABLEAF, MOTORPIN1_LF, MOTORPIN2_LF, true);
Motor motorRF(ENABLEBF, MOTORPIN1_RF, MOTORPIN2_RF, true);
Motor motorLR(ENABLEAR, MOTORPIN1_LR, MOTORPIN2_LR, true);
Motor motorRR(ENABLEBR, MOTORPIN1_RR, MOTORPIN2_RR, true);

Servo servoL;
Servo servoR;

// === Sensors ===
//HCSR04 sensor1(ECHO_PIN,TRIG_PIN);
//IRLINE sensor2(ECHO_PIN);

// Color sensor
bool colorStarted{false};
CLRSENS::color colorVal = { -1, -1, -1};

CLRSENS colorSen(INT_COLOR);

int chout[10];
void setup() {
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
    manualMovement(0, 0, motorLF, motorRF, motorLR, motorRR);
  }
  else if (chout[5] == 0) {
    //manual mode (MIDDLE)
    //use channel 2 for forward/backward and channel 1 for left/right
    manualMovement(chout[1], chout[0], motorLF, motorRF, motorLR, motorRR);
  }
  else if (chout[5] == 255) {
    //auto mode (DOWN)
    servoMove();
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


void servoMove(){
    for (int pos = 0; pos <= 180; pos += 1) { // sweep from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoL.write(pos);
    delay(1);             // waits 20ms for the servo to reach the position
  }
  for (int pos = 180; pos >= 0; pos -= 1) { // sweep from 180 degrees to 0 degrees
    servoL.write(pos);
    delay(1);
  }

  for (int pos = 0; pos <= 180; pos += 1) { // sweep from 0 degrees to 180 degrees
    // in steps of 1 degree
    servoR.write(pos);
    delay(1);             // waits 20ms for the servo to reach the position
  }
  for (int pos = 180; pos >= 0; pos -= 1) { // sweep from 180 degrees to 0 degrees
    servoR.write(pos);
    delay(1);
  }
}
