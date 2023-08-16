// MessagesDelay.cpp

#include "message_delay.h"
#include <omnetpp.h>
using namespace omnetpp;


MessagesDelay::MessagesDelay() {}

void MessagesDelay::recordSentMessage(cMessage* msg) {
    sentMessagesTimestamps[msg] = simTime();
}

void MessagesDelay::calculateReceivedMessageDelay(cMessage* msg) {
    auto it = sentMessagesTimestamps.find(msg);
    if (it != sentMessagesTimestamps.end()) {
        simtime_t delay = simTime() - it->second;
        delays.push_back(delay);
        sentMessagesTimestamps.erase(it);  // remove the timestamp as it's no longer needed
    }
}

double MessagesDelay::getAverageDelay() {
    if (delays.empty()) return 0.0;

    simtime_t totalDelay = 0;
    for (auto delay : delays) {
        totalDelay += delay;
    }

    return totalDelay.dbl() / delays.size();
}
