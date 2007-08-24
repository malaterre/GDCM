/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmFileSet_h
#define __gdcmFileSet_h

#include "gdcmFile.h"

namespace gdcm
{
/**
 * \brief
 * File-set: A File-set is a collection of DICOM Files (and possibly non-DICOM Files)
 * that share a common naming space within which File IDs are unique.
 */
class GDCM_EXPORT FileSet
{
public:
  FileSet() { 
  }
  void AddFile(File *file);

private:
  File *Files;
};

} // end namespace gdcm

#endif //__gdcmFileSet_h
