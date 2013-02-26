package networkcoding.ClusterTree;
simple IEEE802154_CT_NET
{
    parameters:
        // debug switch
        bool debug; 				// debug switch
        bool isPANCoor;
        bool isCoordinator;
    gates:
        input upperLayerIn; 			// from the upper layer
        output upperLayerOut; 		// to the upper layer
        input lowerLayerIn; 			// from the physical layer
        output lowerLayerOut; 			// to the physical layer
}
