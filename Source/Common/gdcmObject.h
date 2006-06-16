#ifndef __gdcmObject_h
#define __gdcmObject_h

#include "gdcmTypes.h"
#include <assert.h>

namespace gdcm
{

class Object
{
public:
  Object():ReferenceCount(0) {}
  virtual ~Object()
    {
    assert(ReferenceCount >= 0 );
    assert(ReferenceCount == 0 );
    }
  void Register() {
    ReferenceCount++;
  }
  void UnRegister()
    {
    ReferenceCount--;
    if(!ReferenceCount)
      {
      delete this;
      }
    }

private:
  long ReferenceCount;
};

} // end namespace gdcm

#endif //__gdcmObject_h
