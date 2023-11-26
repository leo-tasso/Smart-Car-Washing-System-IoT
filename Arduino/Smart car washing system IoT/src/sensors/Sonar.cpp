#include <Arduino.h>
#include "sensors/Sonar.h"

Sonar::Sonar(int echoPin, 
             int trigPin, 
             long maxTime) 
    : echoPin(echoPin), 
      trigPin(trigPin), 
      timeOut(maxTime){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    temperature = 20; //default in normal ambient
}

float Sonar::getSoundVelocity(){
    return 331.5 + 0.6*temperature;
}

float Sonar::setTemperature(float temp){
    this->temperature = temp;
}

float Sonar::getDistance(){
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin,LOW);

    float signal = pulseIn(echoPin, HIGH, timeOut);

    if (signal == 0){
        return NO_OBJ_DETECTED;
    } else {
        float time = signal / 1000.0 / 1000.0 / 2;
        float distance = time*getSoundVelocity();
        return distance;
    }
}

bool isDetected(){
    //TO DO
}