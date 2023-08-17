
#ifndef __FOGSIM1_FOGNODE_H_
#define __FOGSIM1_FOGNODE_H_
#include <queue>
#include "functions.h"
#include <omnetpp.h>
#include "Measurments.h"
using namespace omnetpp;



class FogNode : public cSimpleModule
{

    private:
    Functions functions;
    Measurments measurments;
    cMessage *scheduleEvent ;
    std::string status="idle"; ///ether idle or now_processing
    double processing_delay =15.0/1000.0;
    int queue_size=3;
    simtime_t sum_utilize_time=0.0;
    simtime_t start_utilize_time=0.0;
    std::map<cMessage*, int> hopCounter;
    std::queue<cMessage *> waitingMessagePool;
    public:
        virtual ~FogNode();
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void addToQueue(cMessage *message);
    void startProcessingDelay();
    void forwardMessage(cMessage *msg,BOOLEAN queue_full=false);
    std::string getBestFogGate(cMessage *msg);
        void incrementHopCounter(cMessage* msg);
           int getHopCounter(cMessage* msg) const;
           virtual void finish() override;



};


#endif
