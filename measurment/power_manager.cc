// PowerManager.cpp

#include "power_manager.h"

PowerManager::PowerManager(double idle, double active, double sleep) :
    idlePower(idle),
    activePower(active),
    sleepPower(sleep),
    currentState(IDLE),
    lastStateChangeTime(0) {}

void PowerManager::changePowerState(PowerState newState) {
    double currentTime = simTime().dbl();
    double timeInCurrentState = currentTime - lastStateChangeTime;

    switch (currentState) {
        case IDLE:
            totalEnergyConsumed += timeInCurrentState * idlePower;
            break;
        case ACTIVE:
            totalEnergyConsumed += timeInCurrentState * activePower;
            break;
        case SLEEP:
            totalEnergyConsumed += timeInCurrentState * sleepPower;
            break;
    }

    currentState = newState;
    lastStateChangeTime = currentTime;
}

double PowerManager::getEnergyConsumed() {
    return totalEnergyConsumed;
}
