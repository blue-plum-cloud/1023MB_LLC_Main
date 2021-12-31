#include "flysky.h"
#include "motor.h"
#include "sensors.h"
#define MOTORPIN1 11
#define MOTORPIN2 12
#define ENABLEA 10
#define ECHO_PIN 2
#define  TRIG_PIN 3
//Instantiating objects will also set up the pins for the component.
//Motor motor1(ENABLEA, MOTORPIN1, MOTORPIN2, true);
//HCSR04 sensor1(ECHO_PIN,TRIG_PIN);
//IRLINE sensor2(ECHO_PIN);

int chout[ARRAY_SIZE];
void setup() {
  Serial.begin(9600);
  initializeRC();
}

void loop() { //test for now
  printChannels(chout);
  //  int spd = map(chout[0], 1000, 2000, -255, 255);
  //  spd = constrain(spd, -255,255);
  //  motor1.rotate(spd);
  //  delay(50);
  //  boolean check = sensor2.check_line();
  //  Serial.print("Line: ");
  //  Serial.println(check);
  //  delay(50);
}
