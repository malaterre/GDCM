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
filename: gdcmQueryPatient.cxx
contains: class to construct a patient-based query for c-find and c-move
name and date: 15 oct 2010 mmr

//note that at the series and image levels, there is no distinction between the root query types.
*/

#include "gdcmQueryPatient.h"

namespace gdcm{

std::vector<Tag> QueryPatient::GetRequiredTags(const ERootType& inRootType) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.1.1.2
  switch (inRootType){
    case ePatientRootType:
    default:
      theReturn.push_back(Tag(0x0010, 0x0010));
      break;
    case eStudyRootType:
      //do nothing
      break;
  }
  return theReturn;
}
std::vector<Tag> QueryPatient::GetUniqueTags(const ERootType& inRootType) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.1.1.2
  switch (inRootType){
    case ePatientRootType:
    default:
      theReturn.push_back(Tag(0x0010, 0x0020));
      break;
    case eStudyRootType:
      //do nothing
      break;
  }
  return theReturn;

}
std::vector<Tag> QueryPatient::GetOptionalTags(const ERootType& inRootType) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.1.1.2
  switch (inRootType){
    case ePatientRootType:
    default:
      theReturn.push_back(Tag(0x0010, 0x0021));
      theReturn.push_back(Tag(0x0008, 0x1120));
      theReturn.push_back(Tag(0x0010, 0x0030));
      theReturn.push_back(Tag(0x0010, 0x0032));
      theReturn.push_back(Tag(0x0010, 0x0040));
      theReturn.push_back(Tag(0x0010, 0x1000));
      theReturn.push_back(Tag(0x0010, 0x1001));
      theReturn.push_back(Tag(0x0010, 0x2160));
      theReturn.push_back(Tag(0x0010, 0x4000));
      theReturn.push_back(Tag(0x0020, 0x1200));
      theReturn.push_back(Tag(0x0020, 0x1202));
      theReturn.push_back(Tag(0x0020, 0x1204));
      break;
    case eStudyRootType:
      //do nothing
      break;
  }
  return theReturn;
}

DataElement QueryPatient::GetQueryLevel() const{
  std::string theValue = "PATIENT";
  DataElement de;
  de.SetTag(Tag(0x0008,0x0052));
  de.SetByteValue(theValue.c_str(), (uint32_t)theValue.length());
  return de;
}
}
