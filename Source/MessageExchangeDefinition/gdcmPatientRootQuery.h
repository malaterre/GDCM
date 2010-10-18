/* 
file name: gdcmPatientRootQuery.h
contains: the class which will produce a dataset for c-find and c-move with patient root
name and date: 18 oct 2010 mmr

*/

#ifndef PATIENTROOTQUERY_H
#define PATIENTROOTQUERY_H

#include "gdcmBaseRootQuery.h"

namespace gdcm{
  namespace network {
    class GDCM_EXPORT PatientRootQuery : public BaseRootQuery {
    private: 
      void SetParameters();
    public: 
      PatientRootQuery();
      ~PatientRootQuery();
    };
  }
}


#endif //PATIENTROOTQUERY_H