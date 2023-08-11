
#ifndef __FOGSIM1_FOGNODE_H_
#define __FOGSIM1_FOGNODE_H_

#include <omnetpp.h>
using namespace omnetpp;


class FogNode : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


};

#endif
