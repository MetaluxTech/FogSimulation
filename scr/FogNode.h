
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
    double processing_delay=0.3;
    int queue_size=3;
    static std::map<cMessage*, int> hopCounter;  // Declare hopCounter as static

    std::queue<cMessage *> waitingMessagePool;
    public:
        virtual ~FogNode();
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void addToQueue(cMessage *message);
    void startProcessingDelay();
    void forwardMessage(cMessage *msg,BOOLEAN queue_full=false);
    std::string getBestFogGate(cMessage *msg);
        void incrementHopCounter(cMessage* msg);
           int getHopCounter(cMessage* msg) const;


};

FogNode :: ~FogNode(){
    while(!waitingMessagePool.empty()) {
              cMessage* msg = waitingMessagePool.front();
              waitingMessagePool.pop();
              delete msg;
          }

          // Cancel and delete the other messages
          if (recivedMessage) {
              cancelAndDelete(recivedMessage);
              recivedMessage = nullptr;
          }
          if (processTimeEvent) {
              cancelAndDelete(processTimeEvent);
              processTimeEvent = nullptr;
          }


}

#endif
