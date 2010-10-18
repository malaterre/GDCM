/*
filename: gdcmQuerySeries.h
contains: class to construct a series-based query for c-find and c-move
name and date: 15 oct 2010 mmr

*/

#ifndef QUERYSERIES_H
#define QUERYSERIES_H
#include "gdcmQueryBase.h"

namespace gdcm{
  namespace network{
    class QuerySeries : public QueryBase {
    public:
      std::vector<gdcm::Tag> GetRequiredTags(const ERootType& inRootType) const;
      std::vector<gdcm::Tag> GetUniqueTags(const ERootType& inRootType) const;
      std::vector<gdcm::Tag> GetOptionalTags(const ERootType& inRootType) const;
      
      std::string GetName() const { return "Series"; }
    };
  }
}

#endif //QUERYSERIES_H