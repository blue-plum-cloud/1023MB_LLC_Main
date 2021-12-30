#include "flysky.h"
#include <Arduino.h>
int chlist[] = {CH2,CH3,CH4, CH5, CH6, CH7, CH8, CH9};
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Red the channel and return a boolean value
bool redSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void printChannels(int chout[]) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    //Serial.print(i);
    chout[i] = readChannel(chlist[i], 1000, 2000, 0);
    if (i == ARRAY_SIZE - 1) {
      Serial.print("  CH" + String(i + 1) + ":  ");
      Serial.println(chout[i]);
    }
    else {
      Serial.print("  CH" + String(i + 1) + ":  ");
      Serial.print(chout[i]);
    }
  }
}
void initializeRC(){
  Serial.println("Initializing...");
  for (int i = 0; i < ARRAY_SIZE; i++) {
    pinMode(chlist[i], INPUT);
  }
  Serial.println("Initialized!");
}
