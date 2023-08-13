
#include "ServerNode.h"

using namespace omnetpp;

Define_Module(ServerNode);

void ServerNode::initialize()
{
    arrivalSignal = registerSignal("arrival");
}

void ServerNode::handleMessage(cMessage *msg)
{
    emitted_count=intuniform(0, 10);
    if(msg == processTimeEvent) {
          // Received a processing time event
           forwardMessage(recivedMessage);  // forward the currently processing message

//           functions.Display(msg, "server sent msg at " + std::to_string(simTime().dbl()) + " from " +std::string(this->getName()) );
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
     emit(arrivalSignal,emitted_count );

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
//           functions.Display(message,"message deleted in  "+std::string(this->getName()) + " queue full !!!");
       }
}


void ServerNode::forwardMessage(cMessage *msg)
{

   std::string  outputGateName=functions.getDestGate(std::string( this->getName()),std::string( msg->getArrivalGate()->getName()), msg);
    cMessage *respMessage = new cMessage(("image-" + functions.getMessageID(msg) +" processed "+ functions.getPcName(msg)).c_str());
    bubble((" image served with id: " + functions.getMessageID(msg)).c_str());
    delete msg;
   send(respMessage, outputGateName.c_str());
  }



void ServerNode::startProcessingDelay()
{
    if(!processTimeEvent) {
        processTimeEvent = new cMessage("processTimeEvent");
    }
    scheduleAt(simTime() + processing_delay, processTimeEvent);
}
