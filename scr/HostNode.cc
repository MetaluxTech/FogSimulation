#include "HostNode.h"

#include "CustomPackets_m.h"
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
        bubble(("response arrive image id: " + std::to_string(uniqueID) ).c_str());

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
//            functions.Display(actualmessage);


}

