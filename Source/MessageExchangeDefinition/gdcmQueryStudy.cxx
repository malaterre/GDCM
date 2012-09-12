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
filename: gdcmQueryStudy.cxx
contains: class to construct a study-based query for c-find and c-move
name and date: 15 oct 2010 mmr

//note that at the series and image levels, there is no distinction between the root query types.
*/

#include "gdcmQueryStudy.h"

namespace gdcm{

std::vector<Tag> QueryStudy::GetRequiredTags(const ERootType& inRootType) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.1.1.3
  switch (inRootType){
    case ePatientRootType:
    default:
      theReturn.push_back(Tag(0x0008, 0x0020));
      theReturn.push_back(Tag(0x0008, 0x0030));
      theReturn.push_back(Tag(0x0008, 0x0050));
      theReturn.push_back(Tag(0x0020, 0x0010));
      break;
    case eStudyRootType:
      theReturn.push_back(Tag(0x0008, 0x0020));
      theReturn.push_back(Tag(0x0008, 0x0030));
      theReturn.push_back(Tag(0x0008, 0x0050));
      theReturn.push_back(Tag(0x0010, 0x0010));
      theReturn.push_back(Tag(0x0010, 0x0020));
      theReturn.push_back(Tag(0x0020, 0x0010));
      break;
  }
  return theReturn;
}
std::vector<Tag> QueryStudy::GetUniqueTags(const ERootType& ) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.2.1.2
  theReturn.push_back(Tag(0x0020, 0x000D));
  return theReturn;

}
std::vector<Tag> QueryStudy::GetOptionalTags(const ERootType& inRootType) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.1.1.3
  switch (inRootType){
    case ePatientRootType:
    default:
      theReturn.push_back(Tag(0x0008, 0x0061));
      theReturn.push_back(Tag(0x0008, 0x0062));
      theReturn.push_back(Tag(0x0008, 0x0090));
      theReturn.push_back(Tag(0x0008, 0x1030));
      theReturn.push_back(Tag(0x0008, 0x1032));
      theReturn.push_back(Tag(0x0008, 0x1060));
      theReturn.push_back(Tag(0x0008, 0x1080));
      theReturn.push_back(Tag(0x0008, 0x1110));
      theReturn.push_back(Tag(0x0010, 0x1010));
      theReturn.push_back(Tag(0x0010, 0x1020));
      theReturn.push_back(Tag(0x0010, 0x1030));
      theReturn.push_back(Tag(0x0010, 0x2180));
      theReturn.push_back(Tag(0x0010, 0x21B0));
      theReturn.push_back(Tag(0x0020, 0x1070));
      theReturn.push_back(Tag(0x0020, 0x1206));
      theReturn.push_back(Tag(0x0020, 0x1208));
      break;
    case eStudyRootType:
      theReturn.push_back(Tag(0x0008, 0x0061));
      theReturn.push_back(Tag(0x0008, 0x0062));
      theReturn.push_back(Tag(0x0008, 0x0090));
      theReturn.push_back(Tag(0x0008, 0x1030));
      theReturn.push_back(Tag(0x0008, 0x1032));
      theReturn.push_back(Tag(0x0008, 0x1060));
      theReturn.push_back(Tag(0x0008, 0x1080));
      theReturn.push_back(Tag(0x0008, 0x1110));
      theReturn.push_back(Tag(0x0008, 0x1120));
      theReturn.push_back(Tag(0x0010, 0x0021));
      theReturn.push_back(Tag(0x0010, 0x0030));
      theReturn.push_back(Tag(0x0010, 0x0032));
      theReturn.push_back(Tag(0x0010, 0x0040));
      theReturn.push_back(Tag(0x0010, 0x1000));
      theReturn.push_back(Tag(0x0010, 0x1001));
      theReturn.push_back(Tag(0x0010, 0x1010));
      theReturn.push_back(Tag(0x0010, 0x1020));
      theReturn.push_back(Tag(0x0010, 0x1030));
      theReturn.push_back(Tag(0x0010, 0x2160));
      theReturn.push_back(Tag(0x0010, 0x2180));
      theReturn.push_back(Tag(0x0010, 0x21B0));
      theReturn.push_back(Tag(0x0010, 0x4000));

      theReturn.push_back(Tag(0x0020, 0x1070));
      theReturn.push_back(Tag(0x0020, 0x1200));
      theReturn.push_back(Tag(0x0020, 0x1202));
      theReturn.push_back(Tag(0x0020, 0x1204));
      theReturn.push_back(Tag(0x0020, 0x1206));
      theReturn.push_back(Tag(0x0020, 0x1208));
      break;
  }
  return theReturn;
}

DataElement QueryStudy::GetQueryLevel() const{
  std::string theValue = "STUDY";
  DataElement de;
  de.SetTag(Tag(0x0008,0x0052));
  de.SetByteValue(theValue.c_str(), (uint32_t)theValue.length());
  return de;
}

}
