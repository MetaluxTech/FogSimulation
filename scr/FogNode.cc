
#include "FogNode.h"
#include "functions.h"
using namespace omnetpp;

Define_Module(FogNode);


void FogNode::initialize()
{




    scheduleEvent = new cMessage("scheduleEvent");


}

void FogNode::handleMessage(cMessage *msg)
{
    if (!msg->isSelfMessage()){
           addToQueue(msg);

           if (!scheduleEvent->isScheduled()){
              scheduleAfter(processing_delay, scheduleEvent); //wait until get last message in queue
           }
       }
       else if (msg == scheduleEvent){

           if (!waitingMessagePool.empty()) {
               msg = waitingMessagePool.front();
               waitingMessagePool.pop(); //take the message
               forwardMessage(msg);
               scheduleAfter(processing_delay, scheduleEvent);
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
           forwardMessage(message,true);
       }
}


void FogNode::forwardMessage(cMessage *msg, BOOLEAN queue_full)
{
    if (!queue_full)
    {
        std::string outputGateName = functions.getDestGate(std::string(this->getName()), std::string(msg->getArrivalGate()->getName()), msg);
        send(msg, outputGateName.c_str());
        return;
    }

    std::string nextgate = getBestFogGate(msg);
    if (nextgate != "")
    {
        incrementHopCounter(msg);
        send(msg, nextgate.c_str());
    }
}






std::string FogNode::getBestFogGate(cMessage *msg) //Neighbor
 {

     int fog_node_number = std::stoi(std::string(msg->getArrivalModule()->getName()).substr(7));
     std:: string arrivall_gate=msg->getArrivalGate()->getName();
     bubble(("fog" + std::to_string(fog_node_number) + " queue full !!!  input gate: " + arrivall_gate + " hops: " + std::to_string(getHopCounter(msg))).c_str());

     if (getHopCounter(msg) == 0 ){

         return "out4";          //send all full messages to right edge
     }


     switch(fog_node_number)
     {
         case 1:
             return "out4";
         case 5:
                 bubble(("Deleting image-" + functions.getMessageID(msg) + "all queues full  !!!").c_str());
                    delete msg;
             break;
         default:
             return (arrivall_gate=="in5") ? "out4" : "out5";

     }

     return ""; // Return empty string for undefined behavior.
 }




void FogNode::incrementHopCounter(cMessage* msg) {
     hopCounter[msg]++;
 }
 int FogNode::getHopCounter(cMessage* msg) const {
     auto it = hopCounter.find(msg);
     if (it != hopCounter.end()) {
         return it->second;
     }
     return 0;  // Default hop count is 0 if not found
 }


 FogNode :: ~FogNode(){
     while(!waitingMessagePool.empty()) {
               cMessage* msg = waitingMessagePool.front();
               waitingMessagePool.pop();
               delete msg;
           }

           if (scheduleEvent) {
               cancelAndDelete(scheduleEvent);
               scheduleEvent = nullptr;
           }


 }

