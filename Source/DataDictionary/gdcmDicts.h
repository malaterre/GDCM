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
#ifndef __gdcmDicts_h
#define __gdcmDicts_h

#include "gdcmDict.h"
#include "gdcmCSAHeaderDict.h"

#include <string>

namespace gdcm
{
/**
 * \brief Class to manipulate the sum of knowledge (all the dict user load)
 * \note bla
 */
class GDCM_EXPORT Dicts
{
public:
  Dicts();
  ~Dicts();

  // works for both public and private dicts:
  // owner is null for public dict
  const DictEntry &GetDictEntry(const Tag& tag, const char *owner = NULL) const;

  //enum PublicTypes {
  //  DICOMV3_DICT,
  //  ACRNEMA_DICT,
  //  NIH_DICT
  //};
  const Dict &GetPublicDict() const;

  const PrivateDict &GetPrivateDict() const;

  const CSAHeaderDict &GetCSAHeaderDict() const;

  bool IsEmpty() const { return GetPublicDict().IsEmpty(); }

protected:
  typedef enum {
    PHILIPS,
    GEMS,
    SIEMENS
  //  ...
  } ConstructorType;
  static const char *GetConstructorString(ConstructorType type);

  friend class Global;
  void LoadDefaults();

private:
  // Public dict:
  Dict PublicDict;

  // Private Dicts:
  PrivateDict ShadowDict;

  CSAHeaderDict CSADict;
  Dicts &operator=(const Dicts &_val); // purposely not implemented
  Dicts(const Dicts &_val); // purposely not implemented
};


} // end namespace gdcm

#endif //__gdcmDicts_h
