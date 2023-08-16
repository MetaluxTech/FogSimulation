

#ifndef SCR_MEASURMENT_MESSAGES_RATE_H_
#define SCR_MEASURMENT_MESSAGES_RATE_H_


#include <omnetpp.h>
using namespace omnetpp;


class MessagesRate {
    private:
        int sentMessagesCount;
        int receivedMessagesCount;
        simtime_t lastUpdateTime;

    public:

        void recordSentMessage();
        void recordReceivedMessage();
        double getSentRate();
        double getReceivedRate();
        void resetCounters();

    MessagesRate();
    virtual ~MessagesRate();
};

#endif /* SCR_MEASURMENT_MESSAGES_RATE_H_ */
