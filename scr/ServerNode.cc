
#include "ServerNode.h"

using namespace omnetpp;

Define_Module(ServerNode);

void ServerNode::initialize()
{
    // TODO - Generated method body
}

void ServerNode::handleMessage(cMessage *msg)
{
    if(msg == processTimeEvent) {
          // Received a processing time event
           forwardMessage(recivedMessage);  // forward the currently processing message

           functions.Display(msg, "server sent msg at " + std::to_string(simTime().dbl()) + " from " +std::string(this->getName()) );
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
     functions.Display(msg, "server recive msg at" + std::to_string(simTime().dbl()) + " from " +std::string(this->getName()) );

     if(status == "idle") {
         status = "processing";
         recivedMessage = msg;
         startProcessingDelay();
     } else if(status == "processing") {
         addToQueue(msg);
     }
 }
 }

void ServerNode::addToQueue(cMessage *message)
{
    if (waitingMessagePool.size() < queue_size)
       {
           waitingMessagePool.push(message);
       }
       else
       {
           this->bubble(("queue full deleted image -" + functions.getMessageID(message)).c_str());
           delete message;
           functions.Display(message,"message deleted in  "+std::string(this->getName()) + " queue full !!!");
       }
}


void ServerNode::forwardMessage(cMessage *msg)
{
    cGate* arrivalGate = msg->getArrivalGate();
    std::string gateName = arrivalGate->getName();
       int gateIndex = std::stoi(gateName.substr(2));
    std::string outputGateName = "out" + std::to_string(gateIndex);
   send(msg, outputGateName.c_str());
  }



void ServerNode::startProcessingDelay()
{
    if(!processTimeEvent) {
        processTimeEvent = new cMessage("processTimeEvent");
    }
    scheduleAt(simTime() + processing_delay, processTimeEvent);
}
