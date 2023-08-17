
#include "Measurments.h"
#include <cmath>
Measurments::Measurments() {
    // TODO Auto-generated constructor stub

}

Measurments::~Measurments() {
    // TODO Auto-generated destructor stub
}


double Measurments::getResponseTime(cMessage *msg) {
     double dly =( simTime()- msg->getCreationTime()).dbl();
    responses_time_vector.push_back(dly);

  return  dly;
}
double Measurments::getServerUtilizationPrecent(double run_time,int poolSize,double process_delay) {
  double pooltime=poolSize*process_delay;   //messages in pool not yet processed
  double utilization = ((run_time - pooltime) / simTime().dbl() ) * 100;
     return std::round(utilization);
}
double Measurments::getAverageResponseTime() {
    double sum = 0.0;
    for(double val : responses_time_vector) sum += val;

    double  avg=sum/responses_time_vector.size();
  return  avg*1000;
}
double Measurments::getThrouPut_bps(int total_bytes,double frist_msg_time) {
    double wrokintime=(simTime().dbl() - frist_msg_time);
    double thr =( total_bytes / wrokintime)*8;

     return thr ;

}

void Measurments::analyseIncomingPacket(Image *pkt) {
    int packetSize = pkt->getByteLength();

}

