

#ifndef __FOGSIM1_SERVERNODE_H_
#define __FOGSIM1_SERVERNODE_H_

#include <omnetpp.h>
#include <queue>
#include "functions.h"
#include  "Measurments.h"

using namespace omnetpp;

class ServerNode : public cSimpleModule
{
    private:
    Functions functions;
    Measurments measurments;

       cMessage *scheduleEvent ;
       std::string status="idle"; ///ether idle or now_processing
       double processing_delay = 10.0/1000.0;
       int queue_size=100;
       simtime_t sum_utilize_time=0.0;
       simtime_t start_utlize_time=0.0;
       std::queue<cMessage *> waitingMessagePool;


  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void addToQueue(cMessage *message);
    void forwardMessage(cMessage *msg);
    virtual void finish() override;


        virtual ~ServerNode();
};



#endif
