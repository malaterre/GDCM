/*
filename: gdcmQueryImage.h
contains: class to construct an image-based query for c-find and c-move
name and date: 15 oct 2010 mmr

*/
#ifndef QUERYIMAGE_H
#define QUERYIMAGE_H
#include "gdcmQueryBase.h"
#include "gdcmDataSet.h"

namespace gdcm{
  namespace network{
    class QueryImage : public QueryBase {
      gdcm::DataSet mCurrentQuery;
    public:
      std::vector<gdcm::Tag> GetRequiredTags(const ERootType& inRootType) const;
      std::vector<gdcm::Tag> GetUniqueTags(const ERootType& inRootType) const;
      std::vector<gdcm::Tag> GetOptionalTags(const ERootType& inRootType) const;

      std::string GetName() const { return "Composite Object Instance (Image)"; }
    };
  }
}

#endif //QUERYIMAGE_H