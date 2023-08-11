
#include "ServerNode.h"
#include "functions.h"

using namespace omnetpp;

Define_Module(ServerNode);

void ServerNode::initialize()
{
    // TODO - Generated method body
}

void ServerNode::handleMessage(cMessage *msg)
{
    cGate* arrivalGate = msg->getArrivalGate();
 std::string gateName = arrivalGate->getName();
    int gateIndex = std::stoi(gateName.substr(2));
 std::string outputGateName = "out" + std::to_string(gateIndex);
send(msg, outputGateName.c_str());
// delete(msg);
}
