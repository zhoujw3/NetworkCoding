#ifndef __NETWORKCODIGN_IEEE802154_CT_NET_H_
#define __NETWORKCODIGN_IEEE802154_CT_NET_H_

#include "Ieee802154AppPkt_m.h"
#include "Ieee802154NetworkCtrlInfo_m.h"
#include <omnetpp.h>


class IEEE802154_CT_NET : public cSimpleModule
{
public:
  virtual void initialize(int);
  virtual void finish();

protected:
  // Message handle functions
  void                handleMessage           (cMessage*);

  // debugging enabled for this node? Used in the definition of EV
  bool                m_debug;
  bool                isPANCoor;
  const char*     m_moduleName;
  bool                isCoordinator;

  // module gate ID
  int             mUpperLayerIn;
  int             mUpperLayerOut;
  int             mLowerLayerIn;
  int             mLowerLayerOut;

  // for statistical data
  double          numForward;
};

#endif
