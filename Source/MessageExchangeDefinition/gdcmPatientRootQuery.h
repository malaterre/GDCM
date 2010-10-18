/* 
file name: gdcmPatientRootQuery.h
contains: a baseclass which will produce a dataset for c-find and c-move with patient root
name and date: 18 oct 2010 mmr

This class contains the functionality used in patient c-find and c-move queries.
StudyRootQuery derives from this class.

Namely:
1) list all tags associated with a particular query type
2) produce a query dataset via tag association

Eventually, it can be used to validate a particular dataset type.

The dataset held by this object (or, really, one of its derivates) should be passed to a c-find or c-move query.

*/

#ifndef PATIENTROOTQUERY_H
#define PATIENTROOTQUERY_H

#include "gdcmQueryPatient.h"
#include "gdcmQueryStudy.h"
#include "gdcmQuerySeries.h"
#include "gdcmQueryImage.h"
#include "gdcmDataSet.h"
#include "gdcmDictEntry.h"
#include "gdcmTag.h"
#include <iostream>

namespace gdcm{
  namespace network {
    class GDCM_EXPORT PatientRootQuery{
      //these four classes contain the required, unique, and optional tags from the standard.
      //used both to list the tags as well as to validate a dataset, if ever we were to do so.
      QueryPatient mPatient;
      QueryStudy mStudy;
      QuerySeries mSeries;
      QueryImage mImage;

      DataSet mDataSet; 
    protected:
      ERootType mRootType; //set in construction, and it's something else in the study root type
      std::string mHelpDescription; //used when generating the help output
      ERootType GetRootType() const;//accessible from studyrootquery

      void SetSearchParameter(const gdcm::Tag& inTag, const gdcm::DictEntry& inDictEntry, const std::string& inValue);
    public:
      PatientRootQuery();
      virtual ~PatientRootQuery();

      void SetSearchParameter(const gdcm::Tag& inTag, const std::string& inValue);
      void SetSearchParameter(const std::string& inKeyword, const std::string& inValue);

      virtual const std::ostream &WriteHelpFile(std::ostream &os);

      DataSet GetQueryDataSet() const;

      //the following functionality would be nice, but is not necessary at the moment.
      //virtual void ValidateDataSet(const DataSet& inDS) const; 
    };
  }
}


#endif //PATIENTROOTQUERY_H