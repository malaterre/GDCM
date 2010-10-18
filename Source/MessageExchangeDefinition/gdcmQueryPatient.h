/*
filename: gdcmQueryPatient.h
contains: class to construct a patient-based query for c-find and c-move
name and date: 15 oct 2010 mmr

*/

#ifndef QUERYPATIENT_H
#define QUERYPATIENT_H
#include "gdcmQueryBase.h"

namespace gdcm{
  namespace network{
    class QueryPatient : public QueryBase {
    public:
      std::vector<gdcm::Tag> GetRequiredTags(const ERootType& inRootType) const;
      std::vector<gdcm::Tag> GetUniqueTags(const ERootType& inRootType) const;
      std::vector<gdcm::Tag> GetOptionalTags(const ERootType& inRootType) const;
      
      std::string GetName() const { return "Patient"; }
    };
  }
}

#endif //QUERYPATIENT_H