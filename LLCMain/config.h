// ===== Pin Configuration =====
// ----- Motors -----
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

#define servoLpin 15
#define servoRpin 2
int minUs = 500;
int maxUs = 2500;
// ----- Sensors -----
// Ultrasonic Sensor
#define ECHO_PIN 2
#define TRIG_PIN 3

// Color Sensor
#define INT_COLOR 4   // Interrupt pin
