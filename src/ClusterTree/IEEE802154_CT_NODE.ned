package networkcoding.ClusterTree;

import inet.battery.models.InetSimpleBattery;
import inet.mobility.IMobility;
import inet.base.NotificationBoard;
import inet.wpan.Isabel.Base.Display;

import networkcoding.ClusterTree.IEEE802154_CT_NIC;
import networkcoding.ClusterTree.IEEE802154_CT_NET;
import networkcoding.ClusterTree.IEEE802154_CT_APP;

//
// This module implements simple ZigBee nodes with IEEE 802.15.4 MAC and PHY layer, plus a simple test app layer
//

module IEEE802154_CT_NODE
{
    parameters:
        @node();
        string mobilityType;
        volatile double numHosts;
    gates:
        input radioIn;
    submodules:
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=65,70;i=block/control");

        }
        mobility: <mobilityType> like IMobility {
            parameters:
                @display("p=65,150;i=block/cogwheel");

        }
        disp: Display {
            parameters:
                @display("p=65,230;i=block/app2");

        }
        // battery module
        battery: InetSimpleBattery{
            parameters:
                @display("p=65,310;i=block/plug");

        }
        // application-layer
        app: IEEE802154_CT_APP {
            parameters:
                @display("p=250,100;i=block/source");

        }
        // network layer
        net: IEEE802154_CT_NET {
            parameters:
                @display("p=250,200;i=block/network2");

        }
        // network interface
        nic: IEEE802154_CT_NIC {
            parameters:
                @display("p=250,300;q=queue;i=block/ifcard");

        }
    connections allowunconnected:
        radioIn --> nic.radioIn;
        nic.upperLayerOut --> net.lowerLayerIn;
        nic.upperLayerIn <-- net.lowerLayerOut;
        net.upperLayerOut --> app.lowerLayerIn;
        net.upperLayerIn <-- app.lowerLayerOut;
}
