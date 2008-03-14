/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
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
/*
 * \brief Class for Version
 */
//-----------------------------------------------------------------------------
class GDCM_EXPORT Version
{
public :
  static const char *GetGDCMVersion() { return GDCM_VERSION; }
  static int GetGDCMMajorVersion()    { return GDCM_MAJOR_VERSION; }
  static int GetGDCMMinorVersion()    { return GDCM_MINOR_VERSION; }
  static int GetGDCMBuildVersion()    { return GDCM_BUILD_VERSION; }

protected:
  Version() {};
  ~Version() {};
};

} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmVersion_h
