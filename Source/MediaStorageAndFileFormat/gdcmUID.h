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
#ifndef __gdcmUID_h
#define __gdcmUID_h

#include "gdcmTypes.h"

namespace gdcm
{

/**
 * \brief Class 
 * \note bla
 */
class UID
{
public:
  UID(const char *root = GetGDCMUID() )/*:Root(root)*/ {}

  void SetRoot(const char * root) { Root = root; }
  const char *GetRoot() const { return Root.c_str(); }

  // Internally uses a std::string, so two calls have the same pointer !
  // save into a std::string
  const char* GenerateUniqueUID();

  static bool IsUIDValid(const char *uid);

  static const char *GetGDCMUID(); // who would want that in the public API ??

private:
  static const char GDCM_UID[];
  static std::string Root;
  static std::string EncodedHardwareAddress;
  std::string Unique; // Buffer
};


} // end namespace gdcm

#endif //__gdcmUID_h
