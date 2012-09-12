/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDicts.h"

namespace gdcm
{

Dicts::Dicts():PublicDict(),ShadowDict()
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

const DictEntry &Dicts::GetDictEntry(const Tag& tag, const char *owner) const
{
  static DictEntry Dummy;
  if( tag.IsGroupLength() )
    {
    const DictEntry & de = PublicDict.GetDictEntry(tag);
    const char *name = de.GetName();
    if( name && *name )
      {
      return de;
      }
    else
      {
      Dummy.SetName( "Generic Group Length" );
      Dummy.SetKeyword( "GenericGroupLength" );
      bool retired = true; // Since DICOM 2008, all (but 0002,0004) group length are retired
      Dummy.SetVR( VR::UL );
      Dummy.SetVM( VM::VM1 );
      Dummy.SetRetired( retired );
      return Dummy;
      }
    }
  else if( tag.IsPublic() )
    {
    assert( owner == NULL );
    return PublicDict.GetDictEntry(tag);
    }
  else
    {
    assert( tag.IsPrivate() );
    if( owner && *owner )
      {
      size_t len = strlen(owner); (void)len;
      PrivateTag ptag(tag.GetGroup(), (uint16_t)(((uint16_t)(tag.GetElement() << 8)) >> 8), owner);
      const DictEntry &de = GetPrivateDict().GetDictEntry(ptag);
      return de;
      }
    else
      {
      // Check special private element: 0x0000 and [0x1,0xFF] are special cases:
      if( tag.IsIllegal() )
        {
        std::string pc ( "Illegal Element" );
        Dummy.SetName( pc.c_str() );
        std::string kw ( "IllegalElement" );
        Dummy.SetKeyword( kw.c_str() );
        Dummy.SetVR( VR::INVALID );
        Dummy.SetVM( VM::VM0 );
        Dummy.SetRetired( false ); // ??
        return Dummy;
        }
      else if( tag.IsPrivateCreator() )
        {
        assert( !tag.IsIllegal() );
        assert( tag.GetElement() ); // Not a group length !
        //assert( owner );
        assert( tag.IsPrivate() );
        std::string pc ( "Private Creator" );
        Dummy.SetName( pc.c_str() );
        std::string kw ( "Private Creator" );
        Dummy.SetKeyword( pc.c_str() );
        Dummy.SetVR( VR::LO );
        Dummy.SetVM( VM::VM1 );
        Dummy.SetRetired( false );
        return Dummy;
        }
      else
        {
        Dummy.SetName( "Private Element Without Private Creator" );
        Dummy.SetKeyword( "PrivateElementWithoutPrivateCreator" );
        Dummy.SetVR( VR::INVALID );
        Dummy.SetVM( VM::VM0 );
        return Dummy;
        }
      }
  }
}

const DictEntry &Dicts::GetDictEntry(const PrivateTag& tag) const
{
  return GetDictEntry(tag, tag.GetOwner() );
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

const PrivateDict &Dicts::GetPrivateDict() const
{
  return ShadowDict;
}
PrivateDict &Dicts::GetPrivateDict()
{
  return ShadowDict;
}

const CSAHeaderDict &Dicts::GetCSAHeaderDict() const
{
  return CSADict;
}

void Dicts::LoadDefaults()
{
  // TODO: should the user be able to control which dict to load ?
  PublicDict.LoadDefault();
  ShadowDict.LoadDefault();
  CSADict.LoadDefault();
}

} // end namespace gdcm
