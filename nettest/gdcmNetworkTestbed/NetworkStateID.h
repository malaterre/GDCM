/*
Each network connection will be in a particular state at any given time.
Those states have IDs as described in the standard ps3.8-2009, roughly 1-13.
This enumeration lists those states. The actual ULState class will contain more information
about transitions to other states.

name and date: 16 sept 2010 mmr
*/

namespace gdcm {
  namespace primitives {
    enum ENetworkStateID {
      eSta1Idle = 1,
      eSta2Open = 2,
      eSta3WaitLocalAssoc = 3,
      eSta4LocalAssocDone = 4,
      eSta5WaitRemoteAssoc = 5,
      eSta6TransferReady = 6,
      eSta7WaitRelease = 7,
      eSta8WaitLocalRelease = 8,
      eSta9ReleaseCollisionRqLocal = 9,
      eSta10ReleaseCollisionAc = 10,
      eSta11ReleaseCollisionRq = 11,
      eSta12ReleaseCollisionAcLocal = 12,
      eSta13AwaitingClose = 13
    }
  }
}