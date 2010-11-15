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

#include <locale>

namespace gdcm{
  namespace network {
BaseRootQuery* QueryFactory::ProduceQuery(const ERootType &inRootType, const EQueryLevel& inQueryLevel){
  BaseRootQuery* theReturn = NULL;
  switch (inRootType){
    case ePatientRootType:
    default:
      theReturn = new PatientRootQuery();
      theReturn->InitializeDataSet(inQueryLevel);
      return theReturn;
    case eStudyRootType:
      if (inQueryLevel != ePatient){
        theReturn = new StudyRootQuery();
        theReturn->InitializeDataSet(inQueryLevel);
        return theReturn;
      } else {
        return NULL;
      }
  }
}

ECharSet QueryFactory::GetCharacterFromCurrentLocale()
{
  std::locale l("");
  std::string loc = l.name();
  if( loc.find( "UTF-8" ) != std::string::npos )
    {
    return eUTF8;
    }
  return eLatin1;
}

///This function will produce the appropriate dataelement given a list of charsets.
///The first charset will be used directly, while the second and subsequent
///will be prepended with "ISO2022 ".  Redundant character sets are not permitted,
///so if they are encountered, they will just be skipped.
///if UTF8 or GB18030 is used, no subsequent character sets will be used
DataElement QueryFactory::ProduceCharacterSetDataElement(const std::vector<ECharSet>& inCharSetType){
  DataElement theReturn;
  //use the 'visited' array to make sure that if a redundant character set is entered,
  //it's skipped rather than produce a malformed tag.
  bool visited[eGB18030+1];
  memset(visited, 0, (eGB18030+1)*sizeof(bool));

  if (inCharSetType.empty())
    return theReturn;

  std::vector<ECharSet>::const_iterator itor;
  std::string theOutputString;
  for (itor = inCharSetType.begin(); itor < inCharSetType.end(); itor++){
    if (itor > inCharSetType.begin()){
      theOutputString += "ISO 2022 ";
    }
    else {
      theOutputString += "ISO_IR ";
    }

    if (visited[*itor]) continue;
    switch (*itor){
      default:
      case eLatin1:
        theOutputString += "100";
        break;
      case eLatin2:
        theOutputString += "101";
        break;
      case eLatin3:
        theOutputString += "109";
        break;
      case eLatin4:
        theOutputString += "110";
        break;
      case eCyrillic:
        theOutputString += "144";
        break;
      case eArabic:
        theOutputString += "127";
        break;
      case eGreek:
        theOutputString += "126";
        break;
      case eHebrew:
        theOutputString += "138";
        break;
      case eLatin5:
        theOutputString += "148";
        break;
      case eJapanese:
        theOutputString += "13";
        break;
      case eThai:
        theOutputString += "166";
        break;
      case eJapaneseKanjiMultibyte:
        theOutputString += "87";
        break;
      case eJapaneseSupplementaryKanjiMultibyte:
        theOutputString += "159";
        break;
      case eKoreanHangulHanjaMultibyte:
        theOutputString += "149";
        break;
        //for the next two, they are only valid if they are
        //the only ones that appear
      case eUTF8:
        theOutputString = "ISO_IR 192";
        itor = inCharSetType.end(); //stop the loop
        break;
      case eGB18030:
        theOutputString = "GB13080";
        itor = inCharSetType.end(); //stop the loop
        break;
    }
    if (itor < (inCharSetType.end()-1))
      theOutputString += "\\";
    assert( itor < inCharSetType.end() );
    visited[*itor] = true;
  }

  if( theOutputString.size() % 2 )
    theOutputString.push_back( ' ' ); // no \0 !
  theReturn.SetByteValue(theOutputString.c_str(),
    (uint32_t)theOutputString.length());
  theReturn.SetTag(Tag(0x0008, 0x0005));
  return theReturn;
}


void QueryFactory::ListCharSets(std::ostream& os){
  os << "The following character sets are supported by GDCM Network Queries." << std::endl;
  os << "The number in the parenthesis is the index to select." << std::endl;
  os << "Note that multiple selections are possible." << std::endl;
  os << "Latin1 (0): This is the default if nothing is specified." <<std::endl;
  os << "Latin2 (1)" << std::endl;
  os << "Latin3 (2)" << std::endl;
  os << "Latin4 (3)" << std::endl;
  os << "Cyrillic (4)" << std::endl;
  os << "Arabic (5)" << std::endl;
  os << "Greek (6)" << std::endl;
  os << "Hebrew (7)" << std::endl;
  os << "Latin5 (8)" << std::endl;
  os << "Japanese (9)" << std::endl;
  os << "Thai (10)" << std::endl;
  os << "Kanji (Japanese) (11)+" << std::endl;
  os << "Supplementary Kanji (12)+" << std::endl;
  os << "Hangul and Hanja (Korean) (13)+" << std::endl;
  os << "UTF-8 (14)++" << std::endl;
  os << "GB1308 (15)++" << std::endl;
  os << "+ These character sets must be chosen second or later in a set." << std::endl;
  os << "++ These character sets must be chosen alone, in no set." << std::endl;

}

  }
}
