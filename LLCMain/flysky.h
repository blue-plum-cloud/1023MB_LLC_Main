/*flysky RC receiver using iBusBM method.
List of Channels: 
CH1: Right L/R
CH2: Left U/D
CH3: Right U/D
CH4: Left L/R
Channel 5 onwards can be configured.
CH5: SwA
CH6: SwB
CH7: SwC
CH8: SwD
CH9: Key1
CH10: Key2
*/
#include <Arduino.h>
#ifndef FLYSKY_H
#define FLYSKY_H
 

int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue);
bool redSwitch(byte channelInput, bool defaultValue);
void printChannels(int chout[]);
void initializeRC();

#endif //FLYSKY_H
