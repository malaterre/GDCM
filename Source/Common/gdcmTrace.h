#ifndef __gdcmTrace_h
#define __gdcmTrace_h

#include "gdcmType.h"

#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

namespace gdcm 
{
//-----------------------------------------------------------------------------
class GDCM_EXPORT Trace
{
public :
  Trace() { DebugFlag = WarningFlag = ErrorFlag = false; };
  ~Trace() {};

  static void DebugOn()  { DebugFlag = true; };
  static void DebugOff() { DebugFlag = false; };
  
  static void WarningOn()  { WarningFlag = true; };
  static void WarningOff() { WarningFlag = false; };

  static void ErrorOn()  { ErrorFlag = true; };
  static void ErrorOff() { ErrorFlag = false; };

protected:
private:
  static bool DebugFlag;
  static bool WarningFlag;
  static bool ErrorFlag;
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif
