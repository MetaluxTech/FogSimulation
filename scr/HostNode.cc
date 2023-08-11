#include "HostNode.h"
#include "messages_globalid.h"

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
            int uniqueID = GlobalID::getNextID();
            std::string msgcontent = "new encrypted image-" + std::to_string(uniqueID) + " from " + std::string(this->getName());
            cMessage *actualmessage = new cMessage(msgcontent.c_str());
            send(actualmessage, "out");
            functions.Display(actualmessage);


}

