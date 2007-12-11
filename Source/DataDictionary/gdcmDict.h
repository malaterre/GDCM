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
#ifndef __gdcmDict_h
#define __gdcmDict_h

#include "gdcmTag.h"
#include "gdcmDictEntry.h"

#include <iostream>
#include <iomanip>
#include <map>

namespace gdcm
{
// Data Element Tag
/**
 * \brief Class to represent a map of DictEntry
 * \note bla
 * TODO FIXME: For Element == 0x0 need to return
 * Name = Group Length
 * ValueRepresentation = UL
 * ValueMultiplicity = 1
 */
class GDCM_EXPORT Dict
{
public:
  typedef std::map<Tag, DictEntry> MapDictEntry;
  static DictEntry GroupLengthDictEntry; // = DictEntry("Group Length",VR::UL,VM::VM1);

  Dict() {
//    FillDICOMV3DataDict();
//    FillNIHDataDict();
////  FillSPIDataDict();
//   Tag t(0, 0);
//   DictEntry e( "", (VR::VRType)0, (VM::VMType)0);
//   AddDictEntry( t, e );
  }

  friend std::ostream& operator<<(std::ostream& _os, const Dict &_val);

  void AddDictEntry(const Tag &tag, const DictEntry &de)
    {
#ifndef NDEBUG
    MapDictEntry::size_type s = DictInternal.size();
#endif
    DictInternal.insert(
      MapDictEntry::value_type(tag, de));
    assert( s < DictInternal.size() );
    }
  const DictEntry &GetDictEntry(const Tag &tag) const
    {
    MapDictEntry::const_iterator it = 
      DictInternal.find(tag);
    if (it == DictInternal.end())
      {
      //assert( 0 && "Impossible" );
      return GetDictEntry(Tag(0,0));
      }
    assert( DictInternal.count(tag) == 1 );
    return it->second;
    }

protected:
//  void AddDictEntry(uint16_t group, uint16_t element, const char *name, 
//    const char *vr, const char *vm)
//    {
//    Tag t(group, element);
//    AddDictEntry(t, d);
//    }
private:
  void FillDICOMV3DataDict();
  void FillNIHDataDict();
  void FillSPIDataDict();

  Dict &operator=(const Dict &_val); // purposely not implemented
  Dict(const Dict &_val); // purposely not implemented

  MapDictEntry DictInternal;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const Dict &_val)
{
  Dict::MapDictEntry::const_iterator it = _val.DictInternal.begin();
  for(;it != _val.DictInternal.end(); ++it)
    {
    const Tag &t = it->first;
    const DictEntry &de = it->second;
    _os << t << " " << de << '\n';
    }

  return _os;
}

// TODO
// For privat dict, element < 0x10 should automatically defined:
// Name = "Private Creator"
// ValueRepresentation = LO
// ValueMultiplicity = 1
// Owner = ""
class GDCM_EXPORT PrivateDict
{
  typedef std::map<Tag, PrivateDictEntry> MapDictEntry;
public:
  const DictEntry &GetDictEntry(const Tag &tag, const char *owner = NULL) const
    {
    // if 0x10 -> return Private Creator
    MapDictEntry::const_iterator it = 
      DictInternal.find(tag);
    if (it == DictInternal.end())
      {
      //assert( 0 && "Impossible" );
      return GetDictEntry(Tag(0,0));
      }
    const char *tag_owner = it->second.GetOwner();
    if( strcmp(tag_owner, owner) == 0)
      {
      return it->second;
      }
    //else
    abort();
    return it->second;
    }


private:
  // Philips, GEMS, SIEMENS...
  std::string Constructor;

  PrivateDict &operator=(const PrivateDict &_val); // purposely not implemented
  PrivateDict(const PrivateDict &_val); // purposely not implemented

  MapDictEntry DictInternal;
};

} // end namespace gdcm

#endif //__gdcmDict_h
