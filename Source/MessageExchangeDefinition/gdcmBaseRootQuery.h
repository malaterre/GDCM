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
#ifndef GDCMBASEROOTQUERY_H
#define GDCMBASEROOTQUERY_H

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
/**
 * \brief BaseRootQuery
 * contains: a baseclass which will produce a dataset for c-find and c-move with patient/study root
 * name and date: 18 oct 2010 mmr
 *
 * This class contains the functionality used in patient c-find and c-move queries.
 * PatientRootQuery and StudyRootQuery derive from this class.
 *
 * Namely:
 * 1) list all tags associated with a particular query type
 * 2) produce a query dataset via tag association
 *
 * Eventually, it can be used to validate a particular dataset type.
 *
 * The dataset held by this object (or, really, one of its derivates) should be passed to a c-find or c-move query.
 */
    enum GDCM_EXPORT EQueryLevel {
      ePatient,
      eStudy,
      eSeries,
      eImageOrFrame
    };

    class QueryFactory;
class GDCM_EXPORT BaseRootQuery
{
      //these four classes contain the required, unique, and optional tags from the standard.
      //used both to list the tags as well as to validate a dataset, if ever we were to do so.

      DataSet mDataSet;
    protected:

      friend class QueryFactory;
      BaseRootQuery();

      QueryPatient mPatient;
      QueryStudy mStudy;
      QuerySeries mSeries;
      QueryImage mImage;

      ERootType mRootType; //set in construction, and it's something else in the study root type
      std::string mHelpDescription; //used when generating the help output
      virtual void SetParameters() = 0; //to ensure that this base class is not used directly,
      //a particular instance must be chosen

      void SetSearchParameter(const gdcm::Tag& inTag, const gdcm::DictEntry& inDictEntry, const std::string& inValue);
    public:
      virtual ~BaseRootQuery();

      void SetSearchParameter(const gdcm::Tag& inTag, const std::string& inValue);
      void SetSearchParameter(const std::string& inKeyword, const std::string& inValue);

      virtual const std::ostream &WriteHelpFile(std::ostream &os);

      DataSet GetQueryDataSet() const;

      ///this function will return all tags at a given query level, so that
      ///they maybe selected for searching.  The boolean forFind is true
      ///if the query is a find query, or false for a move query.
      virtual std::vector<gdcm::Tag> GetTagListByLevel(const EQueryLevel& inQueryLevel, bool forFind) = 0;

      //this function sets tag 8,52 to the appropriate value based on query level
      void InitializeDataSet(const EQueryLevel& inQueryLevel);

      ///have to be able to ensure that
      ///0x8,0x52 is set (which will be true if InitializeDataSet is called...)
      ///that the level is appropriate (ie, not setting PATIENT for a study query
      ///that the tags in the query match the right level (either required, unique, optional)
      ///by default, this function checks to see if the query is for finding, which is more
      ///permissive than for moving.  For moving, only the unique tags are allowed.
      virtual bool ValidateQuery(bool forFind) const = 0;
    };
  }
}


#endif //GDCMBASEROOTQUERY_H
