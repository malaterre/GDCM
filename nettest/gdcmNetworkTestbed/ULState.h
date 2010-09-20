/*
This base class defines the concept of a 'state' as described in ps 3.8-2009 of the dicom specification.
Each network connection will have one instance of a state instantiated at any given point.
The base class is abstract; the actual state itself must be an instantiated version of an
inherited state.

Each state will be able to:
1) give a dicom description of itself
2) be able to determine the sets of ULAction that can be taken
3) Given an ULActionResult, determine what the next state will be, and return an instance of that next state.

Upon performing step 3, the state should be destroyed.  Ideally, then, 
the state should be contained in a gdcmSmartPointer object (not done yet, for the sake of separation
with the main code base for clarity).

name and date: 16 sept 2010 mmr
*/

#include <vector>

namespace gdcm {

  namespace primitives {

    class ULState { //inheriting from whatever class allows for smartpointerage
    private:
      //copy construction is private, because we don't want someone to copy a state.
      ULState(const gdcm::primitives::ULState& inState){};

    protected:

      ENetworkStateID mNetworkStateID; //the current id, also defined by the name
      //of the particular ULState class that's instantiated.

    public:
      //default constructor is to place the ULState in the ENetworkStateID of eSta1Idle.
      //subsequent ULActions can progress the ULConnection to another ULState.
      ULState();
      //destructors must be virtual to avoid memory leaks
      virtual ~ULState();

      //according to the standard, there are 13 possible states that a connection can be
      //in.  Therefore, this function will return that DicomDescriptor.
      virtual ENetworkStateID ReturnDicomDescriptor() = 0;

      //given the current state, return a vector of possible actions that can be
      //taken.  Note, again, that these should be smart pointer-ish objects,
      //and the deletion needs to be handled properly in the meantime.
      virtual std::vector<ULAction*> ProvideActionList() const = 0;

      
      //only one state can generate another state (that is not the idle state, that is)
      //this function MUST be overriden by the derivative state classes, as those
      //classes interpret which state will be made.
      //eventually, this function must return a smart pointer.
      //Which state is returned is dictated by the given action.  If a NullAction is given,
      //the it is up to the particular state to interpret what happened (probably nothing,
      //although some states may transition to an error state if a response doesn't happen in time).
      //note that an event triggers a state change, but the state dictates the possible actions that
      //can be taken.
      virtual ULState* GenerateState(ULEvent* inEvent) = 0; 
    }
  }
}