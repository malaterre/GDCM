
#ifndef __gdcmGroupDict_h
#define __gdcmGroupDict_h



#include "gdcmType.h"
#include <assert.h>
#include <vector>
#include <string>
#include <iostream>

namespace gdcm
{
/**
 * \brief Class to represent the mapping from group number to its abbreviation and name
 * \note Should I rewrite this class to use a std::map instead of vector from problem of 
 * memory consumption ?
 */
class GDCM_EXPORT GroupDict
{
public:
  typedef std::vector<std::string> GroupStringVector;
  GroupDict() { FillDefaultGroupName(); }
  ~GroupDict() {}

  friend std::ostream& operator<<(std::ostream& _os, const GroupDict &_val);

  unsigned long Size() const
    {
    assert( GroupName.size() == GroupAbbreviation.size() );
    return GroupName.size(); }

  std::string const &GetGroupAbbreviation(uint16_t num) const;

  std::string const &GetGroupName(uint16_t num) const;

protected:
  void AddGroupEntry(std::string const &abbreviation, std::string const &name);
  void InsertGroupEntry(uint16_t num, std::string const &abbreviation, std::string const &name);

private:
  // Generated implementation, see gdcmDefaultGroupNames
  void FillDefaultGroupName();

  GroupDict &operator=(const GroupDict &_val); // purposely not implemented
  GroupDict(const GroupDict &_val); // purposely not implemented

  GroupStringVector GroupAbbreviation;
  GroupStringVector GroupName;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream& _os, const GroupDict &_val)
{
  unsigned int size = _val.Size();
  for(unsigned int i=0; i<size; ++i)
    {
    _os << std::hex << i << "," << _val.GetGroupAbbreviation(i) << "," << _val.GetGroupName(i) << "\n";
    }
  return _os;
}

} // end namespace gdcm

#endif //__gdcmGroupDict_h
