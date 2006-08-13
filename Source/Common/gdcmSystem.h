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

namespace gdcm
{

class System
{
public:
  // digest_str needs to be at least : strlen = [2*16+1];
  static bool ComputeMD5(const char *buffer, const unsigned long buf_len,
    char *digest_str);
  static bool ComputeFileMD5(const char *filename, char *digest_str);
  static bool MakeDirectory(const char *path); 
  static bool FileExists(const char* filename);
  static bool FileIsDirectory(const char* name);
  static bool RemoveFile(const char* source);

  static const char *GetLastSystemError();
  // TODO some system calls
  // GetLastError
  // Chdir
  // copy a file

protected:
  bool GetPermissions(const char* file, unsigned short& mode);
  bool SetPermissions(const char* file, unsigned short mode);
};

} // end namespace gdcm
