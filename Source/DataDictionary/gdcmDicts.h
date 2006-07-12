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


  enum PublicTypes {
    DICOMV3_DICT,
    ACRNEMA_DICT,
    NIH_DICT
  };
  // Set public dict to a particular type: DICOMV3, ACR-NEMA, NIH
  void SetPublicType(int type);
  int GetPublicType() const { return PublicType; }
  const Dict &GetPublicDict() const;

  // TODO define the private dict API
  void SetPrivateType(const char *);
  const std::string &GetPrivateType() { return PrivateType; }
  const Dict &GetPrivateDict();

protected:
  void AddPublicDict(const Dict& dict);
  void AddPrivateDict(const Dict& dict);

private:
  // Generated implementation, see gdcmDataDicts
  void FillDataDicts();

  unsigned int PublicType;
  //std::vector<Dict> PublicDicts;
  Dict PublicDicts[3];

  std::string PrivateType;
  std::vector<Dict> PrivateDicts;
};


} // end namespace gdcm

#endif //__gdcmDicts_h
