package networkcodign.simulations.ClusterTree;

import networkcoding.ClusterTree.IEEE802154_CT_NODE;
import inet.world.radio.ChannelControl;

network ClusterTree
{
    parameters:
        double numHosts;
    submodules:
        host[numHosts]: IEEE802154_CT_NODE {
            parameters:
                @display("i=device/pocketpc_s;r=,,#707070;p=84,57");
        }
        channelControl: ChannelControl {
            parameters:
                @display("p=-65,20;i=misc/sun");
        }
    connections allowunconnected:
}