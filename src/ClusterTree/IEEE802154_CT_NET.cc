#include "IEEE802154_CT_NET.h"

Define_Module(IEEE802154_CT_NET);

void IEEE802154_CT_NET::initialize(int aStage)
{
    cSimpleModule::initialize(aStage); //DO NOT DELETE!!
    if (0 == aStage)
    {
        // WirelessMacBase stuff...
        mUpperLayerIn  = findGate("upperLayerIn");
        mUpperLayerOut = findGate("upperLayerOut");
        mLowerLayerIn  = findGate("lowerLayerIn");
        mLowerLayerOut = findGate("lowerLayerOut");

        m_moduleName    = getParentModule()->getFullName();

        m_debug         = par("debug");
        isPANCoor       = par("isPANCoor");
        isCoordinator   = par("isCoordinator");

        numForward      = 0;
    }
}

void IEEE802154_CT_NET::finish()
{
    recordScalar("num of pkts forwarded", numForward);
}

/////////////////////////////// Msg handler ///////////////////////////////////////
void IEEE802154_CT_NET::handleMessage(cMessage* msg)
{
    Ieee802154AppPkt* appPkt = check_and_cast<Ieee802154AppPkt *>(msg);

    // coming from App layer
    if (msg->getArrivalGateId() == mUpperLayerIn)
    {
        Ieee802154NetworkCtrlInfo *control_info = new Ieee802154NetworkCtrlInfo();

        if (isPANCoor)      // I'm PAN coordinator, msg is destined for a device
        {
            control_info->setToParent(false);
            control_info->setDestName(appPkt->getDestName());
        }
        else        // should always be sent to PAN coordinator first
        {
            control_info->setToParent(true);
            control_info->setDestName("PAN Coordinator");
        }

        appPkt->setControlInfo(control_info);
        send(appPkt, mLowerLayerOut);
    }

    // coming from MAC layer
    else if (msg->getArrivalGateId() == mLowerLayerIn)
    {
        if (strcmp(appPkt->getDestName(), m_moduleName) == 0)
        {
            EV << "[NETWORK]: sending received pkt to upper layer" << endl;
            send(appPkt, mUpperLayerOut);    // to app layer
        }
        else if (isPANCoor)     // need to forward this pkt
        {
            Ieee802154NetworkCtrlInfo *control_info = new Ieee802154NetworkCtrlInfo();
            control_info->setToParent(false);
            control_info->setDestName(appPkt->getDestName());
            appPkt->setControlInfo(control_info);
            EV << "[NETWORK]: received a pkt from " << appPkt->getSourceName() << " and forward it to " << appPkt->getDestName() << endl;
            numForward++;
            send(appPkt, mLowerLayerOut);
        }
        else if (isCoordinator)
        {
            EV<< "I'm a coordinator, pkt received from "<< appPkt->getSourceName() << "sending to my coordinator";
            Ieee802154NetworkCtrlInfo *control_info = new Ieee802154NetworkCtrlInfo();
            control_info->setToParent(false);
            control_info->setDestName(appPkt->getDestName());
            appPkt->setControlInfo(control_info);
            EV << "[NETWORK]: received a pkt from " << appPkt->getSourceName() << " and forward it to " << appPkt->getDestName() << endl;
            numForward++;
            send(appPkt, mLowerLayerOut);
        }
        else
        {
            EV << "[NETWORK]: my name is " << m_moduleName << endl;
            EV << "[NETWORK]: received pkt is destined for " << appPkt->getDestName() << endl;
            error("[NETWORK]: devices are not able to forward pkts in a star network");
        }
    }
    else
    {
        // not defined
    }
}
