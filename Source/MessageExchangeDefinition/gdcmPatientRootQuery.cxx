/* 
file name: gdcmPatientRootQuery.cxx
contains: the class which will produce a dataset for c-find and c-move with study root
name and date: 18 oct 2010 mmr

placeholder file to get the compiler/linker to play nice with this file
*/


#include "gdcmPatientRootQuery.h"

namespace gdcm{
namespace network { 

PatientRootQuery::PatientRootQuery() {
  SetParameters();
}

PatientRootQuery::~PatientRootQuery(){};

void PatientRootQuery::SetParameters(){
  mRootType = ePatientRootType;
  mHelpDescription = "Patient-level root query";
}
}
}
