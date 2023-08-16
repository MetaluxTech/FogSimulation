
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
    cMessage *msgevent;
        int messageCounter = 0;

  public:
    virtual ~HostNode();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void GenerateNewMesssage();
    double nextRandomDelay(double lowerBound=30.0/1000.0, double upperBound=40.0/1000.0);

};


#endif
