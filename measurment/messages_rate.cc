
#include "messages_rate.h"
#include <omnetpp.h>
using namespace omnetpp;


MessagesRate::~MessagesRate() {
}


MessagesRate::MessagesRate() : sentMessagesCount(0), receivedMessagesCount(0), lastUpdateTime(simTime()) {}

void MessagesRate::recordSentMessage() {
    sentMessagesCount++;
}

void MessagesRate::recordReceivedMessage() {
    receivedMessagesCount++;
}

double MessagesRate::getSentRate() {
    simtime_t currentTime = simTime();
    double elapsedTime = (currentTime - lastUpdateTime).dbl();
    double rate = sentMessagesCount / elapsedTime;
    return rate;
}

double MessagesRate::getReceivedRate() {
    simtime_t currentTime = simTime();
    double elapsedTime = (currentTime - lastUpdateTime).dbl();
    double rate = receivedMessagesCount / elapsedTime;
    return rate;
}

void MessagesRate::resetCounters() {
    sentMessagesCount = 0;
    receivedMessagesCount = 0;
    lastUpdateTime = simTime();
}


