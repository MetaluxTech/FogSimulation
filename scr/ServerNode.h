

#ifndef __FOGSIM1_SERVERNODE_H_
#define __FOGSIM1_SERVERNODE_H_

#include <omnetpp.h>
#include <queue>
#include "functions.h"
using namespace omnetpp;

class ServerNode : public cSimpleModule
{
    private:
    Functions functions;


       cMessage *scheduleEvent ;
       std::string status="idle"; ///ether idle or now_processing
       double processing_delay=0.07;
       int queue_size=10;
       std::queue<cMessage *> waitingMessagePool;


  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void addToQueue(cMessage *message);
    void forwardMessage(cMessage *msg);


        virtual ~ServerNode();
};



#endif
