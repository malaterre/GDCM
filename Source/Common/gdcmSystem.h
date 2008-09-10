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
#ifndef __gdcmSystem_h
#define __gdcmSystem_h

#include "gdcmTypes.h"

namespace gdcm
{

/**
 * \brief Class to do system operation
 * \details OS independant functionalities
 */
class GDCM_EXPORT System
{
public:
  /// Create a directory
  static bool MakeDirectory(const char *path); 
  /// Check whether the specified file exist on the sytem
  static bool FileExists(const char* filename);
  /// Check whether the file specified is a directory:
  static bool FileIsDirectory(const char* name);
  /// remove a file
  static bool RemoveFile(const char* source);
  //static bool MakeDirectory(FilenameType const &name) { (void)name; return false; }; // TODO
  //static bool DeleteDirectory(FilenameType const &name) { (void)name; return false; }; // TODO

  /// Return the last error
  static const char *GetLastSystemError();

  /// Return the filesize
  static size_t FileSize(const char* filename);

  /// Return the directory the current process (executable) is located:
  /// NOT THREAD SAFE
  static const char *GetCurrentProcessFileName();

  /// Return the directory the current module is located:
  /// NOT THREAD SAFE
  static const char *GetCurrentModuleFileName();

  /// On some system (Apple) return the path to the current bundled 'Resources' directory
  /// NOT THREAD SAFE
  static const char *GetCurrentResourcesDirectory();

  // TODO some system calls
  // Chdir
  // copy a file

  /// \deprecated DO NOT USE: This function might disapear real time soon...
  static bool GetHardwareAddress(unsigned char addr[6]);

  // somewhat UID specific:
  /// Return the current data time
  static bool GetCurrentDateTime(char date[18]);
  /// Encode bytes
  static size_t EncodeBytes(char *out, const unsigned char *data, int size);

  /// consistant func for C99 spec of strcasecmp/strncasecmp
  static int StrCaseCmp(const char *s1, const char *s2);
  /// \pre n != 0
  static int StrNCaseCmp(const char *s1, const char *s2, size_t n);

  /// Return current working directory
  /// Warning: if current working path is too long (>2048 bytes) the call will fail
  /// and call will return NULL
  /// NOT THREAD SAFE
  static const char * GetCWD();

  /// NOT THREAD SAFE
/*
  static void SetArgv0(const char *);
  static const char* GetArgv0();
*/

protected:
  static bool GetPermissions(const char* file, unsigned short& mode);
  static bool SetPermissions(const char* file, unsigned short mode);

private:
};

} // end namespace gdcm

#endif //__gdcmSystem_h
