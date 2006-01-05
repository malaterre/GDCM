
#ifndef __gdcmGroupSet_h
#define __gdcmGroupSet_h

#include "gdcmGroup.h"
#include <vector>

namespace gdcm
{

/**
 * \brief Class to represent a Data Set (which contains Data Elements)
 * A Data Set represents an instance of a real world Information Object
 * \note bla
 */


// This is needed in order to declare a friend of template class
template<class DEType>
class GroupSet;
template<class DEType>
std::ostream& operator<<(std::ostream& _os, const GroupSet<DEType> &_val);

// Data Set
template<class DEType> // DataElementType
class GDCM_EXPORT GroupSet
{
public:
  GroupSet() {}

  typedef typename std::vector<Group<DEType> > GroupVector;
  typedef typename GroupVector::iterator Iterator;
  typedef typename GroupVector::const_iterator ConstIterator;

  friend std::ostream& operator<< < >(std::ostream& _os, const GroupSet<DEType> &_val);

  // Clearly specify no check should be done to reorder the groups amoung them
  // This is up to the user to not make any error
  void AppendGroup(const Group<DEType>& group)
    {
#ifndef NDEBUG
    if( !Groups.empty() )
      {
      typename GroupVector::iterator it(Groups.end()-1);
      assert(it->GetNumber() < group.GetNumber() );
      }
#endif
    Groups.push_back(group);
    }
  // EXPENSIVE call
  void InsertGroup(const Group<DEType>& group)
    {
    uint16_t group_number = group.GetNumber();
    typename GroupVector::iterator it = Groups.begin();
    while(it->GetNumber() < group_number && it != Groups.end())
      {
      ++it;
      }
    if( it->GetNumber() == group_number )
      {
      std::cerr << "Error cannot add this group" << std::endl;
      }
    else
      Groups.insert(it, group);
    }

  const Group<DEType>& GetGroup(uint16_t group_number) const
    {
    typename GroupVector::const_iterator it = Groups.begin();
    while(it->GetNumber() < group_number && it != Groups.end())
      {
      ++it;
      }
    if( it->GetNumber() == group_number )
      return *it;
    return Group<DEType>(0xffff);
    }
  const Group<DEType>& operator[](uint16_t num) const
    {
    return GetGroup(num);
    }

  void AddDataElement(const DEType& de)
    {
    uint16_t group_number = de.GetTag().GetGroup();
    GetGroup(group_number).AddDataElement(de);
    }
  const DEType& GetDataElement(const Tag& t) const
    {
    uint16_t group_number = t.GetGroup();
    return GetGroup(group_number).GetDataElement(t);
    }
  
  Iterator Begin()
    {
    return Groups.begin();
    }
  ConstIterator Begin() const
    {
    return Groups.begin();
    }
  Iterator End()
    {
    return Groups.end();
    }
  ConstIterator End() const
    {
    return Groups.end();
    }

protected:
  // Indeed there can be at most 0xFFFF groups in one groupset
  uint16_t Size() const
    {
    return Groups.size();
    }

private:
  GroupVector Groups;
};
//-----------------------------------------------------------------------------
template<class DEType>
inline std::ostream& operator<<(std::ostream& _os, const GroupSet<DEType> &_val)
{
  typename GroupSet<DEType>::GroupVector::const_iterator it  = _val.Groups.begin();
  for(; it < _val.Groups.end();
    ++it)
    {
    _os << *it << std::endl;
    }
  return _os;
}

} // end namespace gdcm

#endif //__gdcmGroupSet_h
