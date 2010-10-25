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
