/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
/* 
file name: gdcmBaseRootQuery.h
contains: a baseclass which will produce a dataset for c-find and c-move with patient/study root
name and date: 18 oct 2010 mmr

This class contains the functionality used in patient c-find and c-move queries.
PatientRootQuery and StudyRootQuery derive from this class.

Namely:
1) list all tags associated with a particular query type
2) produce a query dataset via tag association

Eventually, it can be used to validate a particular dataset type.

The dataset held by this object (or, really, one of its derivates) should be passed to a c-find or c-move query.

*/

#ifndef BASEROOTQUERY_H
#define BASEROOTQUERY_H

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
    class GDCM_EXPORT BaseRootQuery{
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
      virtual void SetParameters() = 0; //to ensure that this base class is not used directly,
      //a particular instance must be chosen

      void SetSearchParameter(const gdcm::Tag& inTag, const gdcm::DictEntry& inDictEntry, const std::string& inValue);
    public:
      BaseRootQuery();
      virtual ~BaseRootQuery();

      void SetSearchParameter(const gdcm::Tag& inTag, const std::string& inValue);
      void SetSearchParameter(const std::string& inKeyword, const std::string& inValue);

      virtual const std::ostream &WriteHelpFile(std::ostream &os);

      DataSet GetQueryDataSet() const;

      //the following functionality would be nice, but is not necessary at the moment.
      //virtual void ValidateDataSet(const DataSet& inDS) const; 
    };
  }
}


#endif //BASEROOTQUERY_H