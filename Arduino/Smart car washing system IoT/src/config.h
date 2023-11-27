#ifndef __CONFIG__
#define __CONFIG__

#define __DEBUG__
constexpr int TMP_PIN = A5;
constexpr int PIR_PIN = 4;
constexpr int L1_PIN = 7;
constexpr int L2_PIN = 6;
constexpr int L3_PIN = 5;
constexpr int BASE_PERIOD = 50;
constexpr int SERVO_PIN = 3;
constexpr int SONAR_TRIG_PIN = 11;
constexpr int SONAR_ECHO_PIN = 12;

constexpr int START_BUTTON_PIN = 2;

constexpr int N1 = 1000;          // ms
constexpr int N2 = 500;           // ms
constexpr int N3 = 15000;         // ms washing time
constexpr int N4 = 5000;          // ms exit time
constexpr int transitionTime = 150;  // ms opening/closing time of the gate
constexpr double minDist = 0.07; //100cm = 1m
constexpr double maxDist = 0.09; //300cm = 3m
constexpr int noObjDetected = -1;
constexpr unsigned int PERIOD_L2_GATE = 100;
constexpr unsigned int PERIOD_L2_WASHING =500;

#endif