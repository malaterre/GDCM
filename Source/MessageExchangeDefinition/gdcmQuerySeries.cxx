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
filename: gdcmQuerySeries.cxx
contains: class to construct a series-based query for c-find and c-move
name and date: 15 oct 2010 mmr

//note that at the series and image levels, there is no distinction between the root query types.
*/

#include "gdcmQuerySeries.h"

namespace gdcm{

std::vector<Tag> QuerySeries::GetRequiredTags(const ERootType& inRootType) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.1.1.4
  theReturn.push_back(Tag(0x0008, 0x0060));
  theReturn.push_back(Tag(0x0020, 0x0011));
  return theReturn;
}
std::vector<Tag> QuerySeries::GetUniqueTags(const ERootType& inRootType) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.1.1.4
  theReturn.push_back(Tag(0x0020, 0x000E));

  return theReturn;

}
std::vector<Tag> QuerySeries::GetOptionalTags(const ERootType& inRootType) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.1.1.4
  theReturn.push_back(Tag(0x0020, 0x1209));
  return theReturn;
}

DataElement QuerySeries::GetQueryLevel() const{
  std::string theValue = "SERIES";
  DataElement de;
  de.SetTag(Tag(0x0008,0x0052));
  de.SetByteValue(theValue.c_str(), (uint32_t)theValue.length());
  return de;
}

}
