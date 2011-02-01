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

#include "gdcmCompositeNetworkFunctions.h"
#include "gdcmTag.h"
#include "gdcmQueryFactory.h"


int TestFind(int argc, char *argv[])
{

  std::string hostname = "mi2b2.slicer.org";
  int port = 11112;
  std::string callaetitle = "MI2B2";
  std::string callingaetitle = "ACME1";

  gdcm::CompositeNetworkFunctions theNetworkFunctions;
  
  gdcm::Tag theTag(0x0010, 0x0010);
  std::string theName = "F*";
  std::pair<gdcm::Tag, std::string> theTagPair =
    std::make_pair<gdcm::Tag, std::string>(theTag, theName);

  std::vector<std::pair<gdcm::Tag, std::string> > theTags;
  theTags.push_back(theTagPair);

  gdcm::BaseRootQuery* theQuery = theNetworkFunctions.ConstructQuery(false, false, true, theTags);

  if (!theQuery) {
    std::cerr << "Query construction failed!" << std::endl; 
    return 1;
  }    
  
  if (!theQuery->ValidateQuery(true, false))
    {
    std::cerr << "Find query is not valid.  Please try again." << std::endl;
    delete theQuery;
    return 1;
    }

  std::vector<gdcm::DataSet> theDataSet = theNetworkFunctions.CFind(hostname.c_str(), port, callingaetitle, callaetitle, theQuery);

  //need to put some kind of validation of theDataSet here

  return (theDataSet.empty() ? 1:0);//shouldn't be a zero-sized dataset
}