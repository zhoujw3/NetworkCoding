#ifndef __NETWORKCODIGN_IEEE802154_CT_APP_H_
#define __NETWORKCODIGN_IEEE802154_CT_APP_H_

#include "TrafGenPar.h"
#include "Ieee802154AppPkt_m.h"
#include <omnetpp.h>

class IEEE802154_CT_APP : public TrafGenPar
{
public:

  // LIFECYCLE
  // this takes care of constructors and destructors

  virtual void initialize(int);
  virtual void finish();

protected:

  // OPERATIONS
  virtual void handleSelfMsg(cMessage*);
  virtual void handleLowerMsg(cMessage*);

  virtual void SendTraf(cPacket *msg, const char*);

private:
  bool    m_debug;        // debug switch
  int     mLowerLayerIn;
  int     mLowerLayerOut;

  int     mCurrentTrafficPattern;

  double  mNumTrafficMsgs;
  double  mNumTrafficMsgRcvd;
  double  mNumTrafficMsgNotDelivered;

  const char* m_moduleName;
  simtime_t   sumE2EDelay;
  double  numReceived;
  double  totalByteRecv;
  cOutVector e2eDelayVec;
  cOutVector meanE2EDelayVec;
};

#endif
