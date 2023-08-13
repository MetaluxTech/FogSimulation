
#ifndef SCR_MEASURMENT_POWER_MANAGER_H_
#define SCR_MEASURMENT_POWER_MANAGER_H_


#include <omnetpp.h>
using namespace omnetpp;


class PowerManager {
public:
    enum PowerState {
        IDLE,
        ACTIVE,
        SLEEP
    };

private:
    PowerState currentState;
    double lastStateChangeTime;

    // Define power consumption for different states
    double idlePower;
    double activePower;
    double sleepPower;
    double totalEnergyConsumed = 0.0;

public:
    PowerManager(double idle, double active, double sleep); // Constructor to initialize power values

    void changePowerState(PowerState newState);
    double getEnergyConsumed();
};


#endif /* SCR_MEASURMENT_POWER_MANAGER_H_ */
