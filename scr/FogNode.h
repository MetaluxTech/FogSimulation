
#ifndef __FOGSIM1_FOGNODE_H_
#define __FOGSIM1_FOGNODE_H_
#include <queue>
#include "functions.h"
#include <omnetpp.h>
using namespace omnetpp;


class FogNode : public cSimpleModule
{

    private:
    Functions functions;

    cMessage *recivedMessage = nullptr;
    cMessage *processTimeEvent = nullptr;
    std::string status="idle"; ///ether idle or now_processing
    double processing_delay=0.001;
    int queue_size=5;
    std::queue<cMessage *> waitingMessagePool;
    public:
        virtual ~FogNode();
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void addToQueue(cMessage *message);
    void startProcessingDelay();
    void forwardMessage(cMessage *msg);


};

FogNode :: ~FogNode(){
    cancelAndDelete(recivedMessage);
    cancelAndDelete(processTimeEvent);



}

#endif
