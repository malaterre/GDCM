/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmVersion_h
#define __gdcmVersion_h

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \class Version
 * \brief major/minor and build version
 */
//-----------------------------------------------------------------------------
class GDCM_EXPORT Version
{
public :
  static const char *GetVersion() { return GDCM_VERSION; }
  static int GetMajorVersion()    { return GDCM_MAJOR_VERSION; }
  static int GetMinorVersion()    { return GDCM_MINOR_VERSION; }
  static int GetBuildVersion()    { return GDCM_BUILD_VERSION; }

protected:
  Version() {};
  ~Version() {};
};

} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmVersion_h
