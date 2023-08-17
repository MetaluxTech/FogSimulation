

#ifndef SCR_MEASURMENTS_H_
#define SCR_MEASURMENTS_H_

#include "../messages/CustomPackets_m.h"
#include <omnetpp.h>
using namespace omnetpp;
class Measurments {
private:
  std::vector<double> responses_time_vector;

public:
    Measurments();
    virtual ~Measurments();
    double getResponseTime(cMessage *msg);
    double getAverageResponseTime();
    double getServerUtilizationPrecent(double run_time,int poolSize,double process_delay);
    void analyseIncomingPacket(Image *pkt);
    double getThrouPut_bps(int total_bytes,double frist_msg_time);

};

#endif /* SCR_MEASURMENTS_H_ */
