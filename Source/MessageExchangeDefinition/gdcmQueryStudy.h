/*
filename: gdcmQueryStudy.h
contains: class to construct a study-based query for c-find and c-move
name and date: 15 oct 2010 mmr

*/

#ifndef QUERYSTUDY_H
#define QUERYSTUDY_H
#include "gdcmQueryBase.h"

namespace gdcm{
  namespace network{
    class QueryStudy : public QueryBase {
    public:
      std::vector<gdcm::Tag> GetRequiredTags(const ERootType& inRootType) const;
      std::vector<gdcm::Tag> GetUniqueTags(const ERootType& inRootType) const;
      std::vector<gdcm::Tag> GetOptionalTags(const ERootType& inRootType) const;
      
      std::string GetName() const { return "Study"; }
    };
  }
}

#endif //QUERYSTUDY_H