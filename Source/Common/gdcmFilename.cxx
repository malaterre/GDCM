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

#include "gdcmFilename.h"

namespace gdcm
{

/**
 * Return path of a full filename (no trailing slashes).
 * Warning: returned path is converted to Unix slashes format.
 */
const char *Filename::GetPath()
{
  std::string fn = FileName;
  //Filename::ConvertToUnixSlashes(fn);

  std::string::size_type slash_pos = fn.rfind("/");
  if(slash_pos != std::string::npos)
    {
    Path = fn.substr(0, slash_pos);
    }
  else
    {
    Path = "";
    }

  return Path.c_str();
}


/**
 * Return file name of a full filename (i.e. file name without path).
 */
const char *Filename::GetName()
{
  std::string filename = FileName;
#if defined(_WIN32)
  std::string::size_type slash_pos = filename.find_last_of("/\\");
#else
  std::string::size_type slash_pos = filename.find_last_of("/");
#endif
  if(slash_pos != std::string::npos)
    {
    Name = filename.substr(slash_pos + 1);
    }
  else
    {
    Name = filename;
    }

  return Name.c_str();
}

} // end namespace gdcm

