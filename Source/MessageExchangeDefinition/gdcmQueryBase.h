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
filename: gdcmQueryBase.h
contains: the base class for constructing a query dataset for a c-find and a c-move
name and date: 15 oct 2010 mmr

There are four levels of c-find and c-move query:
Patient
Study
Series
Image

Each one has its own required and optional tags.  This class provides an interface for getting those tags.
This is an interface class.

See 3.4 C 6.1 and 3.4 C 6.2 for the patient and study root query types.  These sections define the tags allowed by a particular query.
The caller must pass in which root type they want, patient or study.  A third root type, Modality Worklist Query, isn't yet supported.

This class (or rather it's derived classes) will be held in the
RootQuery types.  These query types actually make the dataset, and will use this dataset to list the required, unique, and optional tags for each type of query.  This design is somewhat overly complicated, but is kept so that if we ever wanted to try to guess the query type from the given tags, we could do so.

*/

#ifndef QUERYBASE_H
#define QUERYBASE_H
#include <vector>
#include <algorithm>
#include "gdcmTag.h"
#include "gdcmDataSet.h"
#include <string>


namespace gdcm{
  namespace network{
    enum ERootType{
      ePatientRootType, 
      eStudyRootType
    };

    class QueryBase {
    public:

      virtual std::vector<gdcm::Tag> GetRequiredTags(const ERootType& inRootType) const = 0;
      virtual std::vector<gdcm::Tag> GetUniqueTags(const ERootType& inRootType) const = 0;
      virtual std::vector<gdcm::Tag> GetOptionalTags(const ERootType& inRootType) const = 0;

      virtual std::string GetName() const = 0;
    };
  }
}

#endif //QUERYBASE_H