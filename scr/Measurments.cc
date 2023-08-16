
#include "Measurments.h"

Measurments::Measurments() {
    // TODO Auto-generated constructor stub

}

Measurments::~Measurments() {
    // TODO Auto-generated destructor stub
}


double Measurments::getMesageDelayTime(cMessage *msg) {
    simtime_t msgdelay = simTime()- msg->getCreationTime();
  return  msgdelay.dbl();
}


