
#include "FogNode.h"
#include "functions.h"
using namespace omnetpp;

Define_Module(FogNode);

std::map<cMessage*, int> FogNode::hopCounter;

void FogNode::initialize()
{

}

void FogNode::handleMessage(cMessage *msg)
{
    if(msg == processTimeEvent) {

            forwardMessage(recivedMessage);  // forward the currently processing message

            if(waitingMessagePool.empty()) {
                status = "idle";
                delete processTimeEvent;
                processTimeEvent = nullptr;
            }  else {
                recivedMessage = waitingMessagePool.front();
                waitingMessagePool.pop();
                startProcessingDelay();
            }


  }else

  {
      // Received a regular message

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




void FogNode::startProcessingDelay()
{
    if(!processTimeEvent) {
        processTimeEvent = new cMessage("processTimeEvent");
    }
    scheduleAt(simTime() + processing_delay, processTimeEvent);
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



