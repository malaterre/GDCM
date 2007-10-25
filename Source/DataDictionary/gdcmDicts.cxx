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
#include "gdcmDicts.h"

namespace gdcm
{

Dicts::Dicts()
{
  //PublicType = DICOMV3_DICT;
  //PublicDicts.resize(3, Dict() );
}

Dicts::~Dicts()
{
}

//void Dicts::AddPublicDict(const Dict& dict)
//{
//  (void)dict;
//  //PublicDicts.push_back( dict );
//}

//void Dicts::SetPublicType(int type)
//{
//  PublicType = type;
//}

const DictEntry &Dicts::GetDictEntry(const Tag& tag, const char *owner)
{
  if( tag.IsPublic() )
  {
    return PublicDict.GetDictEntry(tag);
  }
  else
  {
    // Test is tag.GetElement() < 0x10... return LO somehow
    return PrivateDicts[0].GetDictEntry(tag,owner);
  }
}

const char *Dicts::GetConstructorString(ConstructorType type)
{
  (void)type;
  return "";
}

const Dict &Dicts::GetPublicDict() const
{
  //assert( PublicType < PublicDicts.size() );
  return PublicDict; //[PublicType];
}

void Dicts::AddPrivateDict(const PrivateDict& dict)
{
  (void)dict;
  //PrivateDicts.push_back( dict );
}

//void Dicts::SetPrivateType(const char *type)
//{
//  PrivateType = type;
//}

const PrivateDict &Dicts::GetPrivateDict(unsigned int constructor) const
{
  return PrivateDicts[constructor];
}

} // end namespace gdcm

