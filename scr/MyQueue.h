

#ifndef __FOGSIM1_MYQUEUE_H_
#define __FOGSIM1_MYQUEUE_H_

#include <omnetpp.h>
using namespace omnetpp;

class MyQueue : public cSimpleModule
{ private:


  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);


};

#endif
