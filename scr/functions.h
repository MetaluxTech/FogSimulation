#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <omnetpp.h>
#include <map>
#include <string>

using namespace omnetpp;

class Functions {
public:
        Functions();
        ~Functions();
        std::map<std::string, std::string> ServerioDic;
        std::map<std::string, std::string> FogioDic;
        std::map<std::string, std::string> HostioDic;
    void Display(cMessage *msg, const std::string& displayedText = "");
    std::string getDestinationHostGateByMessage(cMessage *msg);
    std::string getFogOut(std::string inputgate, cMessage *msg = nullptr);
    std::string getHostOut(std::string inputgate, cMessage *msg = nullptr);
    std::string getServerOut(std::string inputgate, cMessage *msg = nullptr);
    std::string getDestGate(const std::string& nodeName, const std::string& inputgate, cMessage *msg);
    std::string getMessageID(cMessage* msg);


};




#endif





