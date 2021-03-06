#include "flysky.h"
#include <Arduino.h>
#include <IBusBM.h>
IBusBM ibusRc; //pin 16 is used for this

HardwareSerial& ibusRcSerial = Serial2;

int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = ibusRc.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Red the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void printChannels(int chout[]) {

  for (byte i = 0; i < 10; i++) {
    chout[i] = readChannel(i, -255, 255, 0);
    //    if (i !=9) {
    //      Serial.print("Ch");
    //      Serial.print(i + 1);
    //      Serial.print(": ");
    //      Serial.print(chout[i]);
    //      Serial.print(" ");
    //    }
    //    else {
    //      Serial.print("Ch");
    //      Serial.print(i + 1);
    //      Serial.print(": ");
    //      Serial.print(chout[i]);
    //      Serial.println(" ");
    //    }
  }
}
void initializeRC() {
  Serial.println("Initializing...");
  ibusRc.begin(ibusRcSerial);
  Serial.println("Initialized!");
}

bool buttonTimer(int channel, int &prevTime) {
  if (channel < 255) { //release button
    prevTime = millis();
  }
  else if (channel == 255) {
    if ((millis() - prevTime) > 1500) {
      return true;
    }
  }
  return false;
}
