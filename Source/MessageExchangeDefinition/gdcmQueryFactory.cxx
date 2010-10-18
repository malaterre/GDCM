/*
file name: gdcmQueryFactory.cxx
contains: a class to produce a query based off of user-entered information
name and date: 18 oct 2010 mmr

Essentially, this class is used to construct a query based off of user input (typically
from the command line; if in code directly, the query itself could just be instantiated)

In theory, could also be used as the interface to validate incoming datasets as belonging
to a particular query style
*/


#include "gdcmQueryFactory.h"
#include "gdcmPatientRootQuery.h"
#include "gdcmStudyRootQuery.h"

namespace gdcm{
  namespace network {
BaseRootQuery* QueryFactory::ProduceQuery(const ERootType &inRootType){
  switch (inRootType){
    case ePatientRootType:
    default:
      return new PatientRootQuery();
    case eStudyRootType:
      return new StudyRootQuery();
  }
}
  }
}