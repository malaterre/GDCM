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
#ifndef __gdcmDicts_h
#define __gdcmDicts_h

#include "gdcmDict.h"

#include <vector>
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
  const DictEntry &GetDictEntry(const Tag& tag, const char *owner = NULL);

  //enum PublicTypes {
  //  DICOMV3_DICT,
  //  ACRNEMA_DICT,
  //  NIH_DICT
  //};
  const Dict &GetPublicDict() const;

protected:
  typedef enum {
    PHILIPS,
    GEMS,
    SIEMENS
  //  ...
  } ConstructorType;
  static const char *GetConstructorString(ConstructorType type);


  // TODO define the private dict API
  const PrivateDict &GetPrivateDict(unsigned int constructor = 0) const;

  void AddPrivateDict(const PrivateDict& dict);

private:
  // Generated implementation, see gdcmDataDicts
  void FillDataDicts();

  // Public dict:
  Dict PublicDict;

  // Private Dicts:
  std::vector<PrivateDict> PrivateDicts;
};


} // end namespace gdcm

#endif //__gdcmDicts_h
