
#ifndef __FOGSIM1_HOSTNODE_H_
#define __FOGSIM1_HOSTNODE_H_

#include <omnetpp.h>
#include "functions.h"
using namespace omnetpp;

class HostNode : public cSimpleModule
{
  private:
    Functions functions;

    cMessage *generateMessageEvent = nullptr;
    double generate_message_delay=uniform(0.01, 0.3);
    int messageCounter = 0;

  public:
    virtual ~HostNode();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void GenerateNewMesssage();
};



HostNode::~HostNode()
{
    cancelAndDelete(generateMessageEvent);
}
#endif
