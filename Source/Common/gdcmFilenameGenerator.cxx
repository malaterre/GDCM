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
#include "gdcmFilenameGenerator.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
void FilenameGenerator::SetDirectory(const char *dirname)
{
  //
  D.Load(dirname, false);
}

//-----------------------------------------------------------------------------
unsigned int FilenameGenerator::GetNumberOfFilenames() const
{
  //return Filenames.size();
  return D.GetFilenames().size();
}

//-----------------------------------------------------------------------------
const char * FilenameGenerator::GetFilename(unsigned int n) const
{
  //return Filenames[n].c_str();
  return D.GetFilenames()[n].c_str();
}

//-----------------------------------------------------------------------------
void FilenameGenerator::Order()
{
  // TODO
}

} // namespace gdcm
