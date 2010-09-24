/*
This is the class that contains the socket to another machine, and passes data through itself, 
as well as maintaining a sense of state.

The ULConnectionManager tells the ULConnection what data can actually be sent.

This class is done this way so that it can be eventually be replaced with a ULSecureConnection,
if such a protocol is warranted, so that all data that passes through can be managed through a
secure connection.  For now, this class provides a simple pass-through mechanism to the socket itself.

So, for instance, a gdcm object will be passes to this object, and it will then get passed 
along the connection, if that connection is in the proper state to do so.

For right now, this class is not directly intended to be inherited from, but the potential
for future ULSecureConnection warrants the addition, rather than having everything be managed
from within the ULConnectionManager (or this class) without a wrapper.

name and date: 16 sept 2010 mmr

*/
#include "gdcmULConnection.h"

using namespace gdcm::primitives;


ULConnection::ULConnection(){
  mCurrentState = eSta1Idle;
}


EStateID ULConnection::GetState() const{
  return mCurrentState;
}
