#include "ServerNode.h"

using namespace omnetpp;

Define_Module(ServerNode);

void ServerNode::initialize()
{
    // Corrected the spelling
    scheduleEvent = new cMessage("scheduleEvent");
}

void ServerNode::handleMessage(cMessage *msg)
{

            EV<<"returned ";
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

void ServerNode::addToQueue(cMessage *msg){
    if (waitingMessagePool.size() < queue_size)
    {
        waitingMessagePool.push(msg);
    }
    else
    {
        bubble(("Queue full, deleted image -" + functions.getMessageID(msg)).c_str());
        delete msg;
    }
}

void ServerNode::forwardMessage(cMessage *msg)
{
    std::string outputGateName = functions.getDestGate(std::string(this->getName()), std::string(msg->getArrivalGate()->getName()), msg);
    msg->setName(("Image-" + functions.getMessageID(msg) + " processed " + functions.getPcName(msg)).c_str());
    bubble(("Image served with id: " + functions.getMessageID(msg)).c_str());
    send(msg, outputGateName.c_str());
}

ServerNode::~ServerNode()
{
    while (!waitingMessagePool.empty()) {
        cMessage* msg = waitingMessagePool.front();
        waitingMessagePool.pop();
        delete msg;
    }

    if (scheduleEvent) {
        cancelAndDelete(scheduleEvent);
        scheduleEvent = nullptr;
    }
}
