/* 
file name: gdcmStudyRootQuery.h
contains: the class which will produce a dataset for c-find and c-move with study root
name and date: 18 oct 2010 mmr

*/

#ifndef STUDYROOTQUERY_H
#define STUDYROOTQUERY_H

#include "gdcmPatientRootQuery.h"

namespace gdcm{
  namespace network {
    class GDCM_EXPORT StudyRootQuery : public PatientRootQuery {
    public: 
      StudyRootQuery();
      ~StudyRootQuery();
    };
  }
}


#endif //STUDYROOTQUERY_H