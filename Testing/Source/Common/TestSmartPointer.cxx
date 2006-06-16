#include "gdcmSmartPointer.h"
#include "gdcmObject.h"

using gdcm::Object;

int TestSmartPointer(int, char *[])
{
  gdcm::SmartPointer<Object> p = new Object;
  return 0;
}
