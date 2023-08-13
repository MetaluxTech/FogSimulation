// DelayMeasurement.h
#include <omnetpp.h>
#include <string.h>
using namespace omnetpp;


class MessagesDelay {
private:
    std::map<cMessage*, simtime_t> sentMessagesTimestamps;
    std::vector<simtime_t> delays;

public:
    MessagesDelay();

    void recordSentMessage(cMessage* msg);
    void calculateReceivedMessageDelay(cMessage* msg);
    double getAverageDelay();
};
