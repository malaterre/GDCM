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
#ifndef __gdcmDict_h
#define __gdcmDict_h

#include "gdcmTypes.h"
#include "gdcmTag.h"
#include "gdcmDictEntry.h"

#include <iostream>
#include <iomanip>
#include <map>

/*
 * FIXME / TODO
 * I need to seriously rewrite this mess. a class template should work for both a public
 * and a private dict
 */

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
  typedef MapDictEntry::iterator Iterator;
  typedef MapDictEntry::const_iterator ConstIterator;
  //static DictEntry GroupLengthDictEntry; // = DictEntry("Group Length",VR::UL,VM::VM1);

  Dict():DictInternal() {
    assert( DictInternal.empty() );
  }

  friend std::ostream& operator<<(std::ostream& _os, const Dict &_val);

  ConstIterator Begin() const { return DictInternal.begin(); }
  ConstIterator End() const { return DictInternal.end(); }

  bool IsEmpty() const { return DictInternal.empty(); }
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
      it = DictInternal.find( Tag(0xffff,0xffff) );
      return it->second;
      }
    assert( DictInternal.count(tag) == 1 );
    return it->second;
    }

protected:
  friend class Dicts;
  void LoadDefault();

private:
  Dict &operator=(const Dict &_val); // purposely not implemented
  Dict(const Dict &_val); // purposely not implemented

  MapDictEntry DictInternal;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const Dict &val)
{
  Dict::MapDictEntry::const_iterator it = val.DictInternal.begin();
  for(;it != val.DictInternal.end(); ++it)
    {
    const Tag &t = it->first;
    const DictEntry &de = it->second;
    os << t << " " << de << '\n';
    }

  return os;
}

class GDCM_EXPORT PrivateTag : public Tag
{
  friend std::ostream& operator<<(std::ostream &_os, const PrivateTag &_val);
public:
  PrivateTag(uint16_t group = 0, uint16_t element = 0, const char *owner = ""):Tag(group,element),Owner(owner) {}

  const char *GetOwner() const { return Owner.c_str(); }
  void SetOwner(const char *owner) { Owner = owner; }

  bool operator<(const PrivateTag &_val) const
    {
    const Tag & t1 = *this;
    const Tag & t2 = _val;
    if( t1 == t2 )
      {
      //assert( strcmp(Owner.c_str(), _val.GetOwner()) != 0 ); // prevent adding duplicate element
      return strcmp(Owner.c_str(), _val.GetOwner() ) < 0;
      }
    else return t1 < t2;
    }

private:
  // SIEMENS MED, GEMS_PETD_01 ...
  std::string Owner;
};

inline std::ostream& operator<<(std::ostream &os, const PrivateTag &val)
{
  //assert( !val.Owner.empty() );
  os.setf( std::ios::right );
  os << std::hex << '(' << std::setw( 4 ) << std::setfill( '0' )
    << val[0] << ',' << std::setw( 4 ) << std::setfill( '0' )
    << val[1] << ')' << std::setfill( ' ' ) << std::dec;
  os << val.Owner;
  return os;
}

// TODO
// For private dict, element < 0x10 should automatically defined:
// Name = "Private Creator"
// ValueRepresentation = LO
// ValueMultiplicity = 1
// Owner = ""
class GDCM_EXPORT PrivateDict
{
  typedef std::map<PrivateTag, DictEntry> MapDictEntry;
  friend std::ostream& operator<<(std::ostream& os, const PrivateDict &val);
public:
  PrivateDict() {}
  ~PrivateDict() {}
  void AddDictEntry(const PrivateTag &tag, const DictEntry &de)
    {
#ifndef NDEBUG
    MapDictEntry::size_type s = DictInternal.size();
#endif
    DictInternal.insert(
      MapDictEntry::value_type(tag, de));
// The following code should only be used when manually constructing a Private.xml file by hand
// it will get rid of VR::UN duplicate (ie. if a VR != VR::Un can be found)
#if defined(NDEBUG) && 0
    if( s == DictInternal.size() )
      {
      MapDictEntry::iterator it = 
        DictInternal.find(tag);
      assert( it != DictInternal.end() );
      DictEntry &duplicate = it->second;
      assert( de.GetVR() == VR::UN || duplicate.GetVR() == VR::UN );
      assert( de.GetVR() != duplicate.GetVR() );
      if( duplicate.GetVR() == VR::UN )
        {
        assert( de.GetVR() != VR::UN );
        duplicate.SetVR( de.GetVR() );
        duplicate.SetVM( de.GetVM() );
        assert( GetDictEntry(tag).GetVR() != VR::UN );
        assert( GetDictEntry(tag).GetVR() == de.GetVR() );
        assert( GetDictEntry(tag).GetVM() == de.GetVM() );
        }
      return;
      }
#endif
    assert( s < DictInternal.size() /*&& std::cout << tag << std::endl*/ );
    }
  const DictEntry &GetDictEntry(const PrivateTag &tag) const
    {
    // if 0x10 -> return Private Creator
    MapDictEntry::const_iterator it = 
      DictInternal.find(tag);
    if (it == DictInternal.end())
      {
      //assert( 0 && "Impossible" );
      it = DictInternal.find( PrivateTag(0xffff,0xffff) );
      assert (it != DictInternal.end());
      return it->second;
      }
    assert( DictInternal.count(tag) == 1 );
    return it->second;
    }


  void PrintXML() const
    {
    MapDictEntry::const_iterator it = DictInternal.begin();
    std::cout << "<dict edition=\"2007\">\n";
    for(;it != DictInternal.end(); ++it)
      {
      const PrivateTag &t = it->first;
      const DictEntry &de = it->second;
      std::cout << "  <entry group=\"" << std::hex << std::setw(4)
        << std::setfill('0') << t.GetGroup() << "\"" << 
        " element=\"xx" << std::setw(2) << std::setfill('0')<< t.GetElement() << "\"" << " vr=\"" 
        << de.GetVR() << "\" vm=\"" << de.GetVM() << "\" owner=\""
        << t.GetOwner();
      const char *name = de.GetName();
      if( *name == 0 )
        {
        std::cout << "\"/>\n";
        }
      else
        {
        std::cout << "\" name=\"" << de.GetName() << "\"/>\n";
        }
      }
    std::cout << "</dict>\n";
    }

  bool IsEmpty() const { return DictInternal.empty(); }
protected:
  friend class Dicts;
  void LoadDefault();

private:
  PrivateDict &operator=(const PrivateDict &_val); // purposely not implemented
  PrivateDict(const PrivateDict &_val); // purposely not implemented

  MapDictEntry DictInternal;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& os, const PrivateDict &val)
{
  PrivateDict::MapDictEntry::const_iterator it = val.DictInternal.begin();
  for(;it != val.DictInternal.end(); ++it)
    {
    const PrivateTag &t = it->first;
    const DictEntry &de = it->second;
    os << t << " " << de << '\n';
    }

  return os;
}

} // end namespace gdcm

#endif //__gdcmDict_h
