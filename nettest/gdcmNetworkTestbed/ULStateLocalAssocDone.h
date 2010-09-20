/*
implements a connection state from the ps3.8-2009 specification.

name and date: 16 sept 2010 mmr 
*/

#include "ULState.h"

namespace gdcm{
  namespace primitives{
    class ULStateLocalAssocDone: public ULState {
      ULStateLocalAssocDone(gdcm::primitives::ULStateLocalAssocDone& inState) {};
    public:

      ULStateLocalAssocDone();
      ~ULStateLocalAssocDone(); //not intended to provide any inheritance, definitely derived.

      ENetworkStateID ReturnDicomDescriptor();

      std::vector<ULAction*> ProvideActionList() const;

      ULState* GenerateState(ULEvent* inEvent); 

    }
  }
}