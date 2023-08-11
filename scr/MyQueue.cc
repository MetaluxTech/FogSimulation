
#include "MyQueue.h"
#include "functions.h"

using namespace omnetpp;

Define_Module(MyQueue);

void MyQueue::initialize()
{


}

void MyQueue::handleMessage(cMessage *msg)
{

  Display(msg);
}



