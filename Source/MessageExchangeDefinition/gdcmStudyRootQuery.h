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
file name: gdcmStudyRootQuery.h
contains: the class which will produce a dataset for c-find and c-move with study root
name and date: 18 oct 2010 mmr

*/

#ifndef STUDYROOTQUERY_H
#define STUDYROOTQUERY_H

#include "gdcmBaseRootQuery.h"

namespace gdcm{
  namespace network {
    class GDCM_EXPORT StudyRootQuery : public BaseRootQuery {
    private:
      void SetParameters();
    public:
      StudyRootQuery();
      ~StudyRootQuery();


      ///have to be able to ensure that
      ///0x8,0x52 is set
      ///that the level is appropriate (ie, not setting PATIENT for a study query
      ///that the tags in the query match the right level (either required, unique, optional)
      bool ValidateQuery() const;
    };
  }
}


#endif //STUDYROOTQUERY_H
