package networkcoding.ClusterTree;

import inet.linklayer.IOutputQueue;
import networkcoding.ClusterTree.IEEE802154_CT_MAC;
import networkcoding.ClusterTree.IEEE802154_CT_PHY;

module IEEE802154_CT_NIC
{
    parameters:
        // name of the interface queue type
        string ifqType; // name of the interface queue type
    gates:
        input upperLayerIn; // to upper layers
        output upperLayerOut; // from upper layers
        input radioIn; // to receive AirFrames
    submodules:
        ifq: <ifqType> like IOutputQueue {
            parameters:
                @display("p=70,80;i=block/passiveq;q=IFQueue");
        }
        mac: IEEE802154_CT_MAC {
            parameters:
                queueModule = "ifq";
                @display("p=70,180;i=block/layer");
        }
        phy: IEEE802154_CT_PHY {
            parameters:
                @display("p=70,280;i=block/wrxtx");
        }
    connections:
        radioIn --> phy.radioIn;
        phy.upperLayerOut --> { @display("m=m,50,50,75,0"); } --> mac.lowerLayerIn;
        phy.upperLayerIn <-- { @display("m=m,25,0,25,0"); } <-- mac.lowerLayerOut;
        mac.upperLayerOut --> upperLayerOut;
        mac.upperLayerIn <-- ifq.out;
        ifq.in <-- upperLayerIn;
}
