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
#ifndef __gdcmUIDGenerator_h
#define __gdcmUIDGenerator_h

#include "gdcmTypes.h"

namespace gdcm
{

/**
 * \brief Class 
 * \note bla
 * Usage:
 * When constructing a Series or Study UID, user *has* to keep around the UID,
 * otherwise the UID Generator will simply forget the value and create a new UID.
 */
class GDCM_EXPORT UIDGenerator
{
public:
  // By default the root of a UID is a GDCM Root...
  UIDGenerator() {}

  // Override the GDCM root with a user one:
  static void SetRoot(const char * root) { Root = root; }
  static const char *GetRoot() { return Root.c_str(); }

  // Internally uses a std::string, so two calls have the same pointer !
  // save into a std::string
  // In summary do not write code like that:
  // const char *uid1 = uid.Generate();
  // const char *uid2 = uid.Generate();
  // since uid1 == uid2 
  const char* Generate();

  // Find out if the string is a valid UID or not
  static bool IsValid(const char *uid);

  static const char *GetGDCMUID(); // who would want that in the public API ??

private:
  static const char GDCM_UID[];
  static std::string Root;
  static std::string EncodedHardwareAddress;
  std::string Unique; // Buffer
};


} // end namespace gdcm

#endif //__gdcmUIDGenerator_h
