
#ifndef __FOGSIM1_HOSTNODE_H_
#define __FOGSIM1_HOSTNODE_H_

#include <omnetpp.h>
#include "functions.h"
#include "Measurments.h"
using namespace omnetpp;

class HostNode : public cSimpleModule
{
  private:
    Functions functions;
    Measurments measurments;
    cOutVector messagesdelayVector;
    int totalMBytesRecived=0;
    double firstmessage_time=0;
    int message_size=4;//in MB
    cMessage *msgevent;
        int messageCounter = 0;
    int sum_recieved_packets=0;
    int sum_sent_packets=0;

  public:
    virtual ~HostNode();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void GenerateNewMesssage();
    double nextRandomDelay(double lowerBound=5.0/1000.0, double upperBound=500/1000.0);
    virtual void finish() override;


};


#endif
