
#ifndef __gdcmGroup_h
#define __gdcmGroup_h

/**
 * \brief Class to store all DataElement from within the same group
 * basically a vector of Tags
 * \note bla
 */

#include "gdcmDataElement.h"
#include <vector>
//#include <iostream>
//#include <iomanip>

namespace gdcm
{
// Group
class Group
{
public:
  Group() { GroupNumber = 0; }
  friend std::ostream& operator<<(std::ostream& _os, const Group&_val);


  void AddDataElement(const DataElement &_el)
    {
    //assert( _el.GetTag().GetGroup() == GroupNumber);
    GroupTags.push_back( _el );
    }
  const DataElement&operator[](unsigned int _id) const
    {
    return GroupTags[_id];
    }


private:
  std::vector<DataElement> GroupTags; // All Data Element from within the same group
  uint16_t GroupNumber;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const Group&_val)
{
  _os << _val.GroupNumber << std::endl;
  return _os;
}

}

#endif //__gdcmGroup_h
