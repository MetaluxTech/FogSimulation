

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
    simsignal_t arrivalSignal;


       cMessage *recivedMessage = nullptr;
       cMessage *processTimeEvent = nullptr;
       std::string status="idle"; ///ether idle or now_processing
       double processing_delay=0.01;
       int queue_size=10;
       int emitted_count;
       std::queue<cMessage *> waitingMessagePool;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void addToQueue(cMessage *message);
    void startProcessingDelay();
    void forwardMessage(cMessage *msg);
    void handleprocessEvent(cMessage *msg);
    void handlereciveMessage(cMessage *msg);
    std::string rewriteMessage(cMessage *msg);

        virtual ~ServerNode();
};


ServerNode :: ~ServerNode(){
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
