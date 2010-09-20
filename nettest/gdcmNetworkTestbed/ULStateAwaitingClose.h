/*
implements a connection state from the ps3.8-2009 specification.

name and date: 16 sept 2010 mmr 
*/

#include "ULState.h"

namespace gdcm{
  namespace primitives{
    class ULStateAwaitingClose: public ULState {
      ULStateAwaitingClose(gdcm::primitives::ULStateAwaitingClose& inState) {};
    public:

      ULStateAwaitingClose();
      ~ULStateAwaitingClose(); //not intended to provide any inheritance, definitely derived.

      ENetworkStateID ReturnDicomDescriptor();

      std::vector<ULAction*> ProvideActionList() const;

      ULState* GenerateState(ULEvent* inEvent); 

    }
  }
}