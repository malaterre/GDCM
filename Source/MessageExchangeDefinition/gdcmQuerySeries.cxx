/*
filename: gdcmQuerySeries.cxx
contains: class to construct a series-based query for c-find and c-move
name and date: 15 oct 2010 mmr

//note that at the series and image levels, there is no distinction between the root query types.
*/

#include "gdcmQuerySeries.h"

namespace gdcm{
namespace network{
std::vector<gdcm::Tag> QuerySeries::GetRequiredTags(const ERootType& inRootType) const{
  std::vector<gdcm::Tag> theReturn;//see 3.4 C.6.1.1.4
  theReturn.push_back(Tag(0x0008, 0x0060));
  theReturn.push_back(Tag(0x0020, 0x0011));
  return theReturn;
}
std::vector<gdcm::Tag> QuerySeries::GetUniqueTags(const ERootType& inRootType) const{
  std::vector<gdcm::Tag> theReturn;//see 3.4 C.6.1.1.4
  theReturn.push_back(Tag(0x0020, 0x000E));

  return theReturn;

}
std::vector<gdcm::Tag> QuerySeries::GetOptionalTags(const ERootType& inRootType) const{
  std::vector<gdcm::Tag> theReturn;//see 3.4 C.6.1.1.4
  theReturn.push_back(Tag(0x0020, 0x1209));
  return theReturn;
}

}
}