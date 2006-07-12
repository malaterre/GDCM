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

#include "gdcmTypes.h"

#include <string>

namespace gdcm
{

class Filename
{
public:
  Filename(const char* filename):FileName(filename) {}

  const char *GetPath();
  const char *GetName();

private:
  std::string FileName;
  std::string Path;
  std::string Name;
};

} // end namespace gdcm
