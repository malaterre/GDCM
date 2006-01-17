
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

//template<class DEType>
//DICOMIStream& operator>>(DICOMIStream& _os, Group<DEType> &_val);

template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const Group<DEType> &_val);
 
// Group
template<class DEType> // DataElementType
class GDCM_EXPORT Group
{
public:
  Group(uint16_t number = 0) { Number = number; }
  typedef typename std::vector<DEType> ElementsVector;

  friend std::ostream& operator<< < >(std::ostream& _os, const Group<DEType>&_val);
  //friend DICOMIStream& operator>> < >(DICOMIStream& _os, Group<DEType> &_val);
  friend class DICOMIStream;
  friend DICOMOStream& operator<< < >(DICOMOStream& _os, const Group<DEType> &_val);

  void SetNumber(uint16_t gnum) { Number = gnum; }
  uint16_t GetNumber() const { return Number; }

  void AddDataElement(const DEType& _el)
    {
    assert( _el.GetTag().GetGroup() == Number);
    Tags.push_back( _el );
    }
  const DEType& operator[](unsigned int _id) const
    {
    return Tags[_id];
    }

  uint32_t GetLength() const;

  bool operator!=(const Group &_val) const
    {
    return Number != _val.Number;
    }

private:
  ElementsVector Tags; // All Data Element from within the same group
  uint16_t Number;
};
//-----------------------------------------------------------------------------
template<class DEType>
inline std::ostream& operator<<(std::ostream& _os, const Group<DEType> &_val)
{
  _os << "Group #" << std::hex << _val.Number << 
    " (" << std::dec << _val.Tags.size() << " elements)" << std::endl;
  for(typename Group<DEType>::ElementsVector::const_iterator it = _val.Tags.begin();
    it != _val.Tags.end(); ++it)
    {
    _os << *it << std::endl;
    }
  return _os;
}

}

#endif //__gdcmGroup_h
