
#include "FogNode.h"
#include "functions.h"
using namespace omnetpp;

Define_Module(FogNode);

void FogNode::initialize()
{

}

void FogNode::handleMessage(cMessage *msg)
{
  std::string nodename=this->getName();
  std::string inputgate= msg->getArrivalGate()->getName();
  std::string desGate=getDestGate(nodename, inputgate, msg);
  Display(msg,"destination gate gotted "+std::string(desGate));
 send (msg,desGate.c_str());
 Display(msg,"msg sent to des gate");
  }





void FogNode::forwardMessage(cMessage *msg)
{
  std::string nodename=this->getName();
  std::string inputgate= msg->getArrivalGate()->getName();
  std::string desGate=getDestGate(nodename, inputgate, msg);
  Display(msg,"destination gate gotted "+std::string(desGate));
 send (msg,desGate.c_str());
 Display(msg,"msg sent to des gate");
  }




