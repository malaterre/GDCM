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
#ifndef __gdcmSystem_h
#define __gdcmSystem_h

#include "gdcmTypes.h"

namespace gdcm
{

/**
 * \brief Class to do system operation
 * \note bla
 */
class GDCM_EXPORT System
{
public:
  // system operation 
  static bool MakeDirectory(const char *path); 
  static bool FileExists(const char* filename);
  static bool FileIsDirectory(const char* name);
  static bool RemoveFile(const char* source);
  //static bool MakeDirectory(FilenameType const &name) { (void)name; return false; }; // TODO
  //static bool DeleteDirectory(FilenameType const &name) { (void)name; return false; }; // TODO

  static const char *GetLastSystemError();
  static size_t FileSize(const char* filename);

  // TODO some system calls
  // Chdir
  // copy a file

  // DO NOT USE: This function might disapear real time soon...
  static bool GetHardwareAddress(unsigned char addr[6]);

  // somewhat UID specific:
  static bool GetCurrentDateTime(char date[18]);
  static size_t EncodeBytes(char *out, const unsigned char *data, int size);

  static int StrCaseCmp(const char *s1, const char *s2);
  static int StrNCaseCmp(const char *s1, const char *s2, size_t n);

protected:
  static bool GetPermissions(const char* file, unsigned short& mode);
  static bool SetPermissions(const char* file, unsigned short mode);

private:
};

} // end namespace gdcm

#endif //__gdcmSystem_h
