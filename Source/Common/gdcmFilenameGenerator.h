/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmFilenameGenerator_h
#define __gdcmFilenameGenerator_h

// doc

#include "gdcmTypes.h"
//#include <string>
//#include <vector>
#include "gdcmDirectory.h"


namespace gdcm
{

// It's a source
class GDCM_EXPORT FilenameGenerator
{
public:
  FilenameGenerator();
  ~FilenameGenerator();

  void SetDirectory(const char *dirname);
  void Order();

  unsigned int GetNumberOfFilenames() const;
  const char * GetFilename(unsigned int n) const;

private:
  //std::vector<std::string> Filenames;
  Directory D;
};

} // end namespace gdcm

#endif //__gdcmFilenameGenerator_h
