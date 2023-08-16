//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

#include "PacketLossTracker.h"



PacketLossTracker::PacketLossTracker() : sentPacketsCount(0), receivedPacketsCount(0) {}


PacketLossTracker::~PacketLossTracker() {
    // TODO Auto-generated destructor stub
}


void PacketLossTracker::recordSentPacket() {
    sentPacketsCount++;
}

void PacketLossTracker::recordReceivedPacket() {
    receivedPacketsCount++;
}

int PacketLossTracker::getLostPacketsCount() {
    return sentPacketsCount - receivedPacketsCount;
}

double PacketLossTracker::getPacketLossRate() {
    if (sentPacketsCount == 0) return 0.0;  // Avoid division by zero
    return (double)getLostPacketsCount() / sentPacketsCount;
}
