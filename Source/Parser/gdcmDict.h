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
 */
class GDCM_EXPORT Dict
{
public:
  typedef std::map<Tag, DictEntry> MapDictEntry;
  Dict() { FillDefaultDataDict(); }

  friend std::ostream& operator<<(std::ostream& _os, const Dict &_val);

  void AddDictEntry(const Tag &tag, const DictEntry &de)
    {
    MapDictEntry::size_type s = DictInternal.size();
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
    return it->second;
    }

protected:
//  void AddDictEntry(uint16_t group, uint16_t element, const char *name, 
//    const char *vr, const char *vm)
//    {
//    gdcm::Tag t(group, element);
//    AddDictEntry(t, d);
//    }
private:
  // Generated implementation, see gdcmDefaultDicts
  void FillDefaultDataDict();

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
    _os << "(" << t  << ") " << de << '\n';
    }

  return _os;
}

} // end namespace gdcm

#endif //__gdcmDict_h
