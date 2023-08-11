

#ifndef __FOGSIM1_FOGPROCESSOR_H_
#define __FOGSIM1_FOGPROCESSOR_H_

#include <omnetpp.h>

using namespace omnetpp;

class FogProcessor : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

};

#endif

