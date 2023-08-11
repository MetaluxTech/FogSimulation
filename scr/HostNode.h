
#ifndef __FOGSIM1_HOSTNODE_H_
#define __FOGSIM1_HOSTNODE_H_

#include <omnetpp.h>
using namespace omnetpp;

class HostNode : public cSimpleModule
{
  private:
    cMessage *generateMessageEvent = nullptr;
    double generate_message_delay=uniform(10e-3, 15e-3);

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
