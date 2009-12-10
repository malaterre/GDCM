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

#ifndef __gdcmSOPClassUIDToIOD_h
#define __gdcmSOPClassUIDToIOD_h

#include "gdcmUIDs.h"

namespace gdcm
{

/**
 * \brief Class convert a class uid into IOD
 */
class GDCM_EXPORT SOPClassUIDToIOD
{
public:
  static const char *GetIOD(UIDs const & uid);
  static unsigned int GetNumberOfSOPClassToIOD();
};

} // end namespace gdcm

#endif //__gdcmSOPClassUIDToIOD_h


