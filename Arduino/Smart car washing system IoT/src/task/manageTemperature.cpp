#include "manageTemperature.h"

#include <Arduino.h>

#include "config.h"
#include "sensors/tempSensor36.h"

constexpr float vcc = 5.0;

ManageTemperature::ManageTemperature(int period,
                                     CarWasher *carWasher,
                                     int pin)
    : TaskWithState(period),
      temperature(new TempSensor36(pin, vcc)),
      carWasher(carWasher) {
    for (int i = 0; i < 10; i++) {
        this->temperatureHistory[i] = 0.0;
    }
    this->currentIndex = 0;
}

void ManageTemperature::tick() {
    float currentTemp = (float)temperature->getTemperature();
    temperatureHistory[currentIndex] = currentTemp;
    currentIndex = (currentIndex + 1) % AVG_VALUES;
    float averageTemp = calculateAverageTemperature();
    carWasher->temp = averageTemp;
    if (carWasher->washing) {
        switch (this->getState()) {
            case TemperatureState::ACCEPTABLE:
                if (this->carWasher->temp < MAXTEMP && this->elapsedTimeInState() >= N5) {
                    carWasher->requiringManteinance = true;
                    this->setState(TemperatureState::UNACCEPTABLE);
                }
                break;
            case TemperatureState::UNACCEPTABLE:
                if (this->carWasher->temp >= MAXTEMP) {
                    this->setState(TemperatureState::ACCEPTABLE);
                }
                break;
        }
    }
}

float ManageTemperature::calculateAverageTemperature() {
    float sum = 0.0;
    for (float temp : temperatureHistory) {
        sum += temp;
    }
    return sum / AVG_VALUES;
}