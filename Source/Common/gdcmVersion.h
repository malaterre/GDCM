/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmVersion_h
#define __gdcmVersion_h

#include "gdcmTypes.h"
#include <iostream>

namespace gdcm
{
/**
 * \class Version
 * \brief major/minor and build version
 */
//-----------------------------------------------------------------------------
class GDCM_EXPORT Version
{
  friend std::ostream& operator<<(std::ostream &_os, const Version &v);
public :
  static const char *GetVersion() { return GDCM_VERSION; }
  static int GetMajorVersion()    { return GDCM_MAJOR_VERSION; }
  static int GetMinorVersion()    { return GDCM_MINOR_VERSION; }
  static int GetBuildVersion()    { return GDCM_BUILD_VERSION; }

  void Print(std::ostream &os = std::cout) const;

protected:
  Version() {};
  ~Version() {};
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const Version &v)
{
  v.Print( os );
  return os;
}

} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmVersion_h
