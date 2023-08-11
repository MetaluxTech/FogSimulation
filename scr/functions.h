#include <omnetpp.h>

using namespace omnetpp;

inline std::map<std::string, std::string> ServerioDic = {
        {"in1", "out1"},
        {"in2", "out2"},
        {"in3", "out3"}
    };

inline std::map<std::string, std::string> FogioDic = {
        {"in1", "out3"},
        {"in2", "out3"}

    };

inline std::map<std::string, std::string> HostioDic = {
        {"in", "out"}
    };

inline void Display(cMessage *msg, const std::string& displayedText = "")
{
    if(!displayedText.empty())  {
        EV << displayedText << "\n";
    } else {

         EV  << " Message: " << msg->getName()
           << " Sender: " << msg->getSenderModule()->getFullName()
           << " Receiver: " << msg->getArrivalModule()->getFullName()
           << " Arrival Gate: " << msg->getArrivalGate()->getName() << "\n";
    }
}
inline std::string getDestinationHostGateByMessage(cMessage *msg)
{
    std::string desgate="out1";
    std::string messagename = msg->getName();
    char lastChar = messagename.back();
        if (lastChar == '2' || lastChar == '4' || lastChar == '6' || lastChar == '8' || lastChar == '0') {
               desgate="out2";
          }
   return desgate ;
}


inline std::string getFogOut(std::string inputgate,cMessage *msg=nullptr)
{
    Display(msg,"iam in gotfogout inputgate= ");

    if (FogioDic.count(inputgate)) {
            Display(msg,"iam in gotgogout found input gate in dictionary "+inputgate);

              return FogioDic[inputgate];
          } else {
             Display(msg, "iam in gotgogout found input gate not in dictionary "+inputgate);

            return  getDestinationHostGateByMessage(msg);
          }

}

inline std::string getHostOut(std::string inputgate,cMessage *msg=nullptr)
{
    return HostioDic[inputgate];
}
inline std::string getServerOut(std::string inputgate,cMessage *msg=nullptr)
{
           return ServerioDic[inputgate];

}

inline std::string getDestGate(const std::string& nodeName, const std::string& inputgate, cMessage *msg)
{
    Display(msg,"iam in getDestGate   "+inputgate);

    if (nodeName.find("fog") != std::string::npos) {
        Display(msg,"iam in getDestGate fognode   "+inputgate);


        return getFogOut(inputgate, msg);
    }
    else if (nodeName.find("host") != std::string::npos) {
        return getHostOut(inputgate, msg);
    }
    else if (nodeName.find("Server") != std::string::npos) {
        return getServerOut(inputgate, msg);
    }
    else {
        Display(msg, "not known node name error in getOutGate function");
        return "out3";
    }
}













