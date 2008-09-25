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
#ifndef __gdcmDICOMDIR_h
#define __gdcmDICOMDIR_h

#include "gdcmFileSet.h"

namespace gdcm
{
/**
 * \brief DICOMDIR 
 */
class GDCM_EXPORT DICOMDIR
{
public:
  DICOMDIR() {}
  DICOMDIR(const FileSet& fs):FS(fs) {}

private:
  FileSet FS;
};

} // end namespace gdcm

#endif //__gdcmDICOMDIR_h
