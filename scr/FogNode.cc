
#include "FogNode.h"
#include "functions.h"
using namespace omnetpp;

Define_Module(FogNode);


void FogNode::initialize()
{
}

void FogNode::handleMessage(cMessage *msg)
{
    if(msg == processTimeEvent) {
            // Received a processing time event
            forwardMessage(recivedMessage);  // forward the currently processing message

            functions.Display(msg, "msg sent at " + std::to_string(simTime().dbl()) + " from " +std::string( msg->getArrivalModule()->getName()) );

            if(waitingMessagePool.empty()) {
                status = "idle";
                delete processTimeEvent;
                processTimeEvent = nullptr;
            }  else {
                recivedMessage = waitingMessagePool.front();
                waitingMessagePool.pop();
                startProcessingDelay();
            }


  }else {   // Received a regular message
      functions.Display(msg, "msg recived at " + std::to_string(simTime().dbl()) + " from " +std::string( msg->getArrivalModule()->getName()) );

      if(status == "idle") {
          status = "processing";
          recivedMessage = msg;
          startProcessingDelay();
      } else if(status == "processing") {
          addToQueue(msg);
      }
  }
  }



void FogNode::addToQueue(cMessage *message)
{
    if (waitingMessagePool.size() < queue_size)
       {
           waitingMessagePool.push(message);
       }
       else
       {
           delete message;
           functions.Display(message,"message deleted in "+std::string(this->getName()) + " queue full !!!");
       }
}


void FogNode::forwardMessage(cMessage *msg)
{
  std::string nodename=this->getName();
  std::string inputgate= msg->getArrivalGate()->getName();
  std::string desGate=functions.getDestGate(nodename, inputgate, msg);
 send (msg,desGate.c_str());
  }




void FogNode::startProcessingDelay()
{
    if(!processTimeEvent) {
        processTimeEvent = new cMessage("processTimeEvent");
    }
    scheduleAt(simTime() + processing_delay, processTimeEvent);
}

