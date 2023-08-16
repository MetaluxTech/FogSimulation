#include "HostNode.h"

#include "../messages/CustomPackets_m.h"
#include "../messages/messages_globalid.h"

using namespace omnetpp;

Define_Module(HostNode);

void HostNode::initialize()
{
    messagesdelayVector.setName("Messages Delay");
    msgevent = new cMessage("timer event");
    scheduleAfter(gen_delay, msgevent);


}

void HostNode::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
            GenerateNewMesssage();
            scheduleAfter(gen_delay, msgevent);

    }
    else{
        double  msgdly=measurments.getMesageDelayTime(msg);
        messagesdelayVector.recordWithTimestamp(simTime(), msgdly);
        bubble(("response arrive image id: " + functions.getMessageID(msg) ).c_str());
        delete msg;
    }


    }




void HostNode::GenerateNewMesssage()
{
       int uniqueID = GlobalID::getNextID();
       std::string msgcontent = "encrypted image-" + std::to_string(uniqueID) + " from " + std::string(this->getName());
       Image *packet1 = new Image(msgcontent.c_str());
       packet1->setUniqueID(uniqueID);
       packet1->setContent((msgcontent).c_str());
       packet1->setByteLength(1024);  // Example packet size
       bubble(("generate new image id: " + std::to_string(uniqueID) ).c_str());
       send(packet1, "out");
}


HostNode::~HostNode()
{
    cancelAndDelete(msgevent);
}
