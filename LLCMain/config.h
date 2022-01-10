// ===== Pin Configuration =====
// ----- Motors -----
#define MOTORPIN1_LF 32
#define MOTORPIN2_LF 33
#define ENABLEAF 25
#define MOTORPIN1_RF 26
#define MOTORPIN2_RF 27
#define ENABLEBF 14

#define servoLpin 15
#define servoRpin 2
#define servoClawpin 12
#define servoGatepin 4
int minUs = 1000;
int maxUs = 2000;
int min180Us = 500;
int max180Us = 2400;
// ----- Sensors -----
// Ultrasonic Sensor
#define ECHO_PIN 2
#define TRIG_PIN 3

// Color Sensor
#define INT_COLOR 4   // Interrupt pin
