
#ifndef __FOGSIM1_FOGNODE_H_
#define __FOGSIM1_FOGNODE_H_

#include <omnetpp.h>
using namespace omnetpp;


class FogNode : public cSimpleModule
{
    private:
    cMessage *recivedMessage = nullptr;
    cMessage *processMessageDelay = nullptr;
    std::string status="idle"; ///ether idle or now_processing
    double processing_delay=3;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void addToQueue(cMessage *message);
    void forwardMessage(cMessage *msg);

};

#endif
