#include "HostNode.h"
#include "functions.h"
using namespace omnetpp;

Define_Module(HostNode);

void HostNode::initialize()
{
    double delay = uniform(0.009, 0.011);
    sendMessageEvent = new cMessage("sendMessageEvent");
       scheduleAt(simTime()+delay, sendMessageEvent);


}

void HostNode::handleMessage(cMessage *msg)
{
    if(msg == sendMessageEvent){
      std::string host_name=this->getName();
      double delay = uniform(0.009, 0.011);
        cMessage *actualmessage = new cMessage((("encrypted image from " + host_name).c_str()));
        send(actualmessage, "out");
        Display(msg,(("New Message generated from " + host_name).c_str()));
        scheduleAt(simTime() + delay, sendMessageEvent);


    }
    else{

        delete msg;
    }


    }





