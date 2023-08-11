#include "HostNode.h"
#include "functions.h"
using namespace omnetpp;

Define_Module(HostNode);

void HostNode::initialize()
{

    generateMessageEvent = new cMessage("timer event");
    scheduleAt(simTime()+generate_message_delay, generateMessageEvent);


}

void HostNode::handleMessage(cMessage *msg)
{
    if(msg == generateMessageEvent){
            GenerateNewMesssage();
            scheduleAt(simTime() + generate_message_delay, generateMessageEvent);

    }
    else{

        delete msg;
    }


    }




void HostNode::GenerateNewMesssage()
{
    std::string host_name=this->getName();
            cMessage *actualmessage = new cMessage((("encrypted image from " + host_name).c_str()));
            send(actualmessage, "out");
            Display(actualmessage,(("New Message generated from " + host_name).c_str()));


}

