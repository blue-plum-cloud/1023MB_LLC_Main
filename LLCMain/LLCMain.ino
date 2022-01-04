#include "flysky.h"
#include "motor.h"
#include "sensors.h"

//define motor pins
#define MOTORPIN1_LF 32
#define MOTORPIN2_LF 33
#define ENABLEAF 25
#define MOTORPIN1_RF 26
#define MOTORPIN2_RF 27
#define ENABLEBF 14
#define MOTORPIN1_LR 12
#define MOTORPIN2_LR 13
#define ENABLEAR 23
#define MOTORPIN1_RR 22
#define MOTORPIN2_RR 21
#define ENABLEBR 19

//define sensor pins
// Ultrasonic Sensor
#define ECHO_PIN 2
#define TRIG_PIN 3

// Color Sensor
#define INT_COLOR 4   // Interrupt pin

//Instantiating objects will also set up the pins for the component.
Motor motorLF(ENABLEAF, MOTORPIN1_LF, MOTORPIN2_LF, true);
Motor motorRF(ENABLEBF, MOTORPIN1_RF, MOTORPIN2_RF, true);
Motor motorLR(ENABLEAR, MOTORPIN1_LR, MOTORPIN2_LR, true);
Motor motorRR(ENABLEBR, MOTORPIN1_RR, MOTORPIN2_RR, true);
//HCSR04 sensor1(ECHO_PIN,TRIG_PIN);
//IRLINE sensor2(ECHO_PIN);

// COlor sensor
CLRSENS::color colorVal = { -1, -1, -1};
bool colorStarted{false};

CLRSENS colorSen(INT_COLOR);

int chout[10];
void setup() {
  Serial.begin(9600);
  initializeRC();
  colorStarted = colorSen.startColor();
  if (!colorStarted)
    Serial.println("Error start color sensor...");
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


////might want to consider some kind of deadzone for the controller for this movement
//void manualMovement(int channel2, int channel1,) { //channel2 is left U/D, channel 1 is right L/R
//  int turningMultiplier = 0.5; //how responsive should the turning be?
//  if (channel2 == 0 && channel1 != 0) { //rotate on spot
//    Serial.println("Rotating!");
//    motorLF.rotate(channel1);
//    motorRF.rotate(-channel1);
//    motorLR.rotate(channel1);
//    motorRR.rotate(-channel1);
//  }
//  else if (channel1 == 0 && channel2 != 0) { //move forward/backward straight
//    Serial.println("Moving Straight!");
//    motorLF.rotate(channel2);
//    motorRF.rotate(channel2);
//    motorLR.rotate(channel2);
//    motorRR.rotate(channel2);
//  }
//  else if (channel1 != 0 && channel2 != 0) { //some kind of diagonal movement
//    int turningSpeed = channel2 * turningMultiplier;
//    if (channel1 < 0) { //going left
//      Serial.println("Turning Left!");
//      motorLF.rotate(turningSpeed);
//      motorRF.rotate(channel2);
//      motorLR.rotate(turningSpeed);
//      motorRR.rotate(channel2);
//    }
//    else {
//      Serial.println("Turning Right!");
//      motorRF.rotate(turningSpeed);
//      motorLF.rotate(channel2);
//      motorRR.rotate(turningSpeed);
//      motorLR.rotate(channel2);
//    }
//  }
//  else {
//    Serial.println("Stopped!");
//    motorLF.stop_rotate();
//    motorRF.stop_rotate();
//    motorLR.stop_rotate();
//    motorRR.stop_rotate();
//  }
//}
