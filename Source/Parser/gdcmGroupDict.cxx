#include "gdcmGroupDict.h"

namespace gdcm
{

std::string const &GroupDict::GetGroupAbbreviation(uint16_t num) const
{
  assert(num < GroupAbbreviation.size());
  return GroupAbbreviation[num];
}

std::string const &GroupDict::GetGroupName(uint16_t num) const
{
  assert(num < GroupName.size());
  return GroupName[num];
}

void GroupDict::AddGroupEntry(std::string const &abbreviation, std::string const &name)
{
  GroupAbbreviation.push_back(abbreviation);
  GroupName.push_back(name);
}

void GroupDict::InsertGroupEntry(uint16_t num, std::string const &abbreviation, 
  std::string const &name)
{
  GroupAbbreviation.resize(num+1);
  GroupName.resize(num+1);
  GroupAbbreviation.insert(GroupAbbreviation.begin()+num, abbreviation);
  GroupName.insert(GroupName.begin()+num, name);
}


} // end namespace gdcm
