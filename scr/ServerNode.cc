
#include "ServerNode.h"
#include <iostream>
#include <string>
#include <regex>
using namespace omnetpp;

Define_Module(ServerNode);

void ServerNode::initialize()
{
    // TODO - Generated method body
}

void ServerNode::handleMessage(cMessage *msg)
{
    if(msg == processTimeEvent) {
         handleprocessEvent(msg);
 }else {   // Received a regular message
     handlereciveMessage(msg);
 }
 }
void ServerNode::handleprocessEvent(cMessage *msg)
{

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

}

void ServerNode::handlereciveMessage(cMessage *msg)
{

    functions.Display(msg, "server recive msg at" + std::to_string(simTime().dbl()) + " from " +std::string(this->getName()) );

        if(status == "idle") {
            status = "processing";
            recivedMessage = msg;
            startProcessingDelay();
        } else if(status == "processing") {
            addToQueue(msg);
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

std::string ServerNode::rewriteMessage(cMessage *msg)
{

    std::string input = std::string(msg->getName());

       std::regex pattern(R"(encrypted image-(\d{1,4}) from pc(\d{1,2}))");

           std::smatch match;
       if (std::regex_search(input, match, pattern) && match.size() > 2) {
           std::string message_id = match[1];
           std::string pc_name = match[2];
           return ("image-" + message_id + " processed pc" + pc_name );
       }
       return "error in server rewrite";
}

void ServerNode::forwardMessage(cMessage *msg)
{
    cGate* arrivalGate = msg->getArrivalGate();
    std::string gateName = arrivalGate->getName();
       int gateIndex = std::stoi(gateName.substr(2));
    std::string outputGateName = "out" + std::to_string(gateIndex);
    msg->setName( rewriteMessage(msg).c_str());
   send(msg, outputGateName.c_str());
  }



void ServerNode::startProcessingDelay()
{
    if(!processTimeEvent) {
        processTimeEvent = new cMessage("processTimeEvent");
    }
    scheduleAt(simTime() + processing_delay, processTimeEvent);
}
