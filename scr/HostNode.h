
#ifndef __FOGSIM1_HOSTNODE_H_
#define __FOGSIM1_HOSTNODE_H_

#include <omnetpp.h>
using namespace omnetpp;

class HostNode : public cSimpleModule
{
  private:
    cMessage *sendMessageEvent = nullptr;

  public:
    virtual ~HostNode();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};



HostNode::~HostNode()
{
    cancelAndDelete(sendMessageEvent);
}
#endif
