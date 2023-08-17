#include "HostNode.h"

#include "../messages/CustomPackets_m.h"
#include "../messages/messages_globalid.h"

using namespace omnetpp;

Define_Module(HostNode);

void HostNode::initialize()
{
    messagesdelayVector.setName("Messages Delay");
    msgevent = new cMessage("timer event");
//if (strcmp(getName(), "pc1")==0)
    firstmessage_time=nextRandomDelay();
    scheduleAfter(firstmessage_time, (msgevent));


}

void HostNode::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
            GenerateNewMesssage();
            scheduleAfter(nextRandomDelay(), msgevent);

    }
    else{
        double  msgdly=measurments.getResponseTime(msg)*1000;//in ms
        messagesdelayVector.recordWithTimestamp(simTime(), msgdly);
        totalMBytesRecived+=message_size;
        EV<<"message ms recorded delay: "+std::to_string(msgdly);
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
    packet1->setByteLength(4);  // Example packet size 1Byte
    bubble(("generate new image id: " + std::to_string(uniqueID)).c_str());

    (gate("out")->getTransmissionChannel()->isBusy()) ? delete packet1 : send(packet1, "out");

}


double HostNode::nextRandomDelay(double lowerBound, double upperBound) {
    double dly=uniform(lowerBound,upperBound);

    return dly;
}

HostNode::~HostNode()
{
    cancelAndDelete(msgevent);
}
void HostNode::finish() {
    EV << "Average System Response: " <<std::to_string(measurments.getAverageResponseTime())  << " ms\n";  // EV is OMNeT++'s way to log data
    EV << "SystemThroughput: " <<std::to_string(measurments.getThrouPut_bps(totalMBytesRecived *message_size,firstmessage_time))  << " Mbps\n";  // EV is OMNeT++'s way to log data

}
