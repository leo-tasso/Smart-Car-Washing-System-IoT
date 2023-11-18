#include "task/scenarioUpdater.h"

ScenarioUpdater::ScenarioUpdater(int period,
                                 CarWasher *carWasher)
    : Task(period),
      carWasher(carWasher) {
}

void ScenarioUpdater::tick() {
    if(this->carWasher->activeScenario == SLEEP && this->carWasher->carInCheckIn){
        this->carWasher->activeScenario = WELCOME;
    }
    // TODO Cover all the scenarios.
};
