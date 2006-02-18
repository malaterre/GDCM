#include "gdcmTrace.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
// Warning message level to be displayed
static bool DebugFlag   = false;
static bool WarningFlag   = true;
static bool ErrorFlag   = true;
static bool DebugToFile = false;
static std::ofstream DebugFile;

//-----------------------------------------------------------------------------
// Constructor / Destructor
Trace::Trace()
{
  DebugFlag = WarningFlag = ErrorFlag = false;
}

Trace::~Trace()
{
  if ( DebugFile.is_open() )
    {
    DebugFile.close();     
    }
}

bool Trace::GetDebugFlag()
{
  return DebugFlag;
}

bool Trace::GetWarningFlag()
{
  return WarningFlag;
}

bool Trace::GetErrorFlag()
{
  return WarningFlag;
}

bool Trace::GetDebugToFile()
{
  return DebugToFile;
}

/**
 * \brief Internal use only. Allow us to retrieve the static from anywhere
 *        in gdcm code
 * @return Debug file
 */
std::ofstream &Trace::GetDebugFile ()
{
  return DebugFile;
}

}
