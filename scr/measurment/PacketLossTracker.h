

#ifndef SCR_MEASURMENT_PACKETLOSSTRACKER_H_
#define SCR_MEASURMENT_PACKETLOSSTRACKER_H_


#include <omnetpp.h>
using namespace omnetpp;


class PacketLossTracker {
public:
private:
    int sentPacketsCount;
    int receivedPacketsCount;

public:
    PacketLossTracker();
    virtual ~PacketLossTracker();


    void recordSentPacket();
    void recordReceivedPacket();
    int getLostPacketsCount();
    double getPacketLossRate();

};

#endif /* SCR_MEASURMENT_PACKETLOSSTRACKER_H_ */
