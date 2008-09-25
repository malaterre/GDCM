/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL: https://gdcm.svn.sourceforge.net/svnroot/gdcm/trunk/Source/DataDictionary/TagToType.xsl $

  Copyright (c) 2006-2008 Mathieu Malaterre
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
};

} // end namespace gdcm

#endif //__gdcmSOPClassUIDToIOD_h


