

#ifndef SCR_MEASURMENTS_H_
#define SCR_MEASURMENTS_H_

#include <omnetpp.h>
using namespace omnetpp;
class Measurments {
public:
    Measurments();
    virtual ~Measurments();
    double getMesageDelayTime(cMessage *msg);
};

#endif /* SCR_MEASURMENTS_H_ */
