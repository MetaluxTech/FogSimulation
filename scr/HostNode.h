
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
    double gen_delay=uniform(0.2,1);
    int messageCounter = 0;

  public:
    virtual ~HostNode();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void GenerateNewMesssage();
};


#endif
