/*flysky RC receiver using PulseIn method. might change to iBusBM method once swapped to ESP32*/
#include <Arduino.h>
#ifndef FLYSKY_H
#define FLYSKY_H
#define CH2 2 //left joystick up/down
#define CH3 3 //right joystick up/down
#define CH4 4 //left joystick left/right (anything after this channel can be configured!)
#define CH5 5 //right joystick left/right 
#define CH6 6 //SWA
#define CH7 7 //SWB
#define CH8 8 //SWC
#define CH9 9 //KEY1
//#define CH10 10 //KEY2
#define ARRAY_SIZE 8

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue);
bool redSwitch(byte channelInput, bool defaultValue);
void printChannels(int chout[]);
void initializeRC();

#endif //FLYSKY_H
