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
filename: gdcmQueryImage.cxx
contains: class to construct an image-based query for c-find and c-move
name and date: 15 oct 2010 mmr

//note that at the series and image levels, there is no distinction between the root query types.
*/

#include "gdcmQueryImage.h"

namespace gdcm{
namespace network{
std::vector<Tag> QueryImage::GetRequiredTags(const ERootType& inRootType) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.1.1.5
  theReturn.push_back(Tag(0x0020, 0x0013));
  return theReturn;
}
std::vector<Tag> QueryImage::GetUniqueTags(const ERootType& inRootType) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.1.1.5
  theReturn.push_back(Tag(0x0008, 0x0018));

  return theReturn;

}
std::vector<Tag> QueryImage::GetOptionalTags(const ERootType& inRootType) const{
  std::vector<Tag> theReturn;//see 3.4 C.6.1.1.5
  theReturn.push_back(Tag(0x0008, 0x0016));//SOP class UID
  //theReturn.push_back(Tag(0x0008, 0x3001));//alternate representation
  theReturn.push_back(Tag(0x0008, 0x001A));//related General SOP Class UID
  //sequence tags, not including for now
  //theReturn.push_back(Tag(0x0040, 0xA504));
  //theReturn.push_back(Tag(0x0040, 0x0512));
  //theReturn.push_back(Tag(0x0040, 0x0560));
  return theReturn;
}

}
}
