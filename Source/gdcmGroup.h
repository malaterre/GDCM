
#ifndef __gdcmGroup_h
#define __gdcmGroup_h

#include "gdcmDataElement.h"
#include <vector>

namespace gdcm
{

/**
 * \brief Class to store all DataElement from within the same group
 * basically a vector of Tags
 * \note bla
 */
// This is needed in order to declare a friend of template class
template<class DEType>
class Group;
template<class DEType>
std::ostream& operator<<(std::ostream& _os, const Group<DEType> &_val);

template<class DEType>
DICOMIStream& operator>>(DICOMIStream& _os, Group<DEType> &_val);

template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const Group<DEType> &_val);
 
// Group
template<class DEType> // DataElementType
class Group
{
public:
  Group() { GroupNumber = 0; }
  Group(int number) { GroupNumber = number; }
  typedef typename std::vector<DEType> GroupTagsVector;

  friend std::ostream& operator<< < >(std::ostream& _os, const Group<DEType>&_val);
  friend DICOMIStream& operator>> < >(DICOMIStream& _os, Group<DEType> &_val);
  friend DICOMOStream& operator<< < >(DICOMOStream& _os, const Group<DEType> &_val);

  void SetGroupNumber(uint16_t gnum) { GroupNumber = gnum; }
  uint16_t GetGroupNumber() const { return GroupNumber; }

  void AddDataElement(const DEType&_el)
    {
    assert( _el.GetTag().GetGroup() == GroupNumber);
    GroupTags.push_back( _el );
    }
  const DEType& operator[](unsigned int _id) const
    {
    return GroupTags[_id];
    }

  uint32_t GetLength() const;

  bool operator!=(const Group &_val) const
    {
    return GroupNumber != _val.GroupNumber;
    }

private:
  GroupTagsVector GroupTags; // All Data Element from within the same group
  uint16_t GroupNumber;
};
//-----------------------------------------------------------------------------
template<class DEType>
inline std::ostream& operator<<(std::ostream& _os, const Group<DEType> &_val)
{
  _os << "Group #" << std::hex << _val.GroupNumber << 
    " (" << std::dec << _val.GroupTags.size() << " elements)" << std::endl;
  for(typename Group<DEType>::GroupTagsVector::const_iterator it = _val.GroupTags.begin();
    it != _val.GroupTags.end(); ++it)
    {
    _os << *it << std::endl;
    }
  return _os;
}

}

#endif //__gdcmGroup_h
