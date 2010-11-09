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
#include "gdcmStudyRootQuery.h"
#include "gdcmULConnectionManager.h"
#include "gdcmPatientRootQuery.h"
#include "gdcmQueryFactory.h"

#include "gdcmDirectory.h"
#include "gdcmTesting.h"
#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmAttribute.h"
#include "gdcmGlobal.h"

//this should maybe override == ?
bool AreDataSetsEqual(const gdcm::DataSet& ds1, const gdcm::DataSet& ds2){
  gdcm::DataSet::ConstIterator it1 = ds1.Begin();
  gdcm::DataSet::ConstIterator it2 = ds2.Begin();

  const gdcm::DataElement &de1 = *it1;
  const gdcm::DataElement &de2 = *it2;
  if( de1 == de2 )
    {
    }
  while( it1 != ds1.End() && it2 != ds2.End() && *it1 == *it2 )
    {
    ++it1;
    ++it2;
    }

  if( it1 != ds1.End() || it2 != ds2.End() )
    {
    std::cerr << "Problem with:" << std::endl;
    if( it1 != ds1.End() )
      {
      std::cerr << "ds1: " << *it1 << std::endl;
      }
    if( it2 != ds2.End() )
      {
      std::cerr << "ds2: " << *it2 << std::endl;
      }
    return false;
    }

  return true;
}

bool LoadGlobalDicts(){

  int resourcespath = 0;
  std::string xmlpath;

  gdcm::Global& g = gdcm::Global::GetInstance();
  if( !resourcespath )
    {
    const char *xmlpathenv = getenv("GDCM_RESOURCES_PATH");
    if( xmlpathenv )
      {
      // Make sure to look for XML dict in user explicitly specified dir first:
      xmlpath = xmlpathenv;
      resourcespath = 1;
      }
    }
  if( resourcespath )
    {
    // xmlpath is set either by the cmd line option or the env var
    if( !g.Prepend( xmlpath.c_str() ) )
      {
      std::cerr << "Specified Resources Path is not valid: " << xmlpath << std::endl;
      return false;
      }
    }
  // All set, then load the XML files:
  if( !g.LoadResourcesFiles() )
    {
    std::cerr << "Could not load XML file from specified path" << std::endl;
      return false;
    }
  return true;
}

int TestAllFunctions(int argc, char *argv[])
{
#if 0
  std::string aetitle("UNITED1");//the ae title of this computer
  std::string call("COMMON");//the ae title of the server
  int portno = 11112;//the port of the server
  int moveReturnPort = 11111;//the port over which return cstore scps are done for cmove
  std::string remote("192.168.1.4");//the ip address of the remote server
  std::string outputDir("h:/gdcmtestdataretrievedcmtk");//place to where data is returned by cmove
  std::string inputDir("h:/gdcmtestdataretrievedcmtk");//input collection of data to transfer
#else
  std::string aetitle = argv[1]; // ("UNITED1");//the ae title of this computer
  std::string call = argv[2]; //("COMMON");//the ae title of the server
  int portno = atoi(argv[3]); // 11112;//the port of the server
  int moveReturnPort = atoi(argv[4]); // 11111;//the port over which return cstore scps are done for cmove
  std::string remote = argv[5]; //("192.168.1.4");//the ip address of the remote server
  std::string tmpdir = gdcm::Testing::GetTempDirectory( "TestAllFunctions" );
  std::string outputDir = tmpdir; // ("h:/gdcmtestdataretrievedcmtk");//place to where data is returned by cmove
  std::string inputDir = tmpdir; //("h:/gdcmtestdataretrievedcmtk");//input collection of data to transfer

#endif
  gdcm::network::ERootType queryRootType = gdcm::network::ePatientRootType;//how queries are done

  if (!LoadGlobalDicts()){//for IODs
    return 1;
  }


  //first, run an echo, make sure that that works.
  gdcm::network::ULConnectionManager theManager;
  gdcm::DataSet blank;
  if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 10, gdcm::network::eEcho, blank)){
    std::cerr << "Failed to establish connection." << std::endl;
    return 1;
  }
  std::vector<gdcm::network::PresentationDataValue> theValues1 = theManager.SendEcho();
  std::vector<gdcm::network::PresentationDataValue>::iterator itor;
  for (itor = theValues1.begin(); itor < theValues1.end(); itor++){
    itor->Print(std::cout);
  }
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite

  //now, run the individual tests.
  //get the filenames from the test directory
  gdcm::Directory theDir;
  theDir.Load(inputDir, false);

  std::vector<std::string> theFilenames = theDir.GetFilenames();

  //contrary to the warning, the factory is actually used.
  gdcm::network::QueryFactory theFactory;

  std::vector<std::string>::iterator fitor;
  for (fitor = theFilenames.begin(); fitor < theFilenames.end(); ++fitor){

    //read in the file
    gdcm::Reader theReader;
    theReader.SetFileName(fitor->c_str());
    if (!theReader.Read()) {
      std::cerr << "Test failed, dicom file failed to load." <<std::endl;
      continue;
    }
    gdcm::File theFile = theReader.GetFile();
    gdcm::DataSet ds = theFile.GetDataSet();

    //store the file remotely
    if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 10, gdcm::network::eStore, ds)){
      std::cerr << "Failed to establish c-store connection." << std::endl;
      continue;
    }

    std::vector<gdcm::DataSet> theReturn = theManager.SendStore(&ds);
    theManager.BreakConnection(-1);

    //construct the cfind query
    gdcm::network::BaseRootQuery* theQuery =
      theFactory.ProduceQuery(queryRootType, gdcm::network::eSeries);

    //take one of the required tags from the dataset
    //search the tags in the returned list for one that's in the dataset
    //whichever one's hit first, we'll search on, using the first char value followed by *
    std::vector<gdcm::Tag> theTags = theQuery->GetTagListByLevel(gdcm::network::eSeries, true);

    gdcm::Tag selectedTag;
    std::vector<gdcm::Tag>::iterator tagItor;
    for (tagItor = theTags.begin(); tagItor < theTags.end(); tagItor++){
      if (ds.FindDataElement(*tagItor)){
        gdcm::DataElement de = ds.GetDataElement(*tagItor);
        gdcm::ByteValue* theVal = de.GetByteValue();
        unsigned long len = 2;
        char* buf = new char[len];
        if (theVal->GetBuffer(buf, len)){
          std::string searchTerm(buf, &(buf[len]));//because buf is probably not null terminated
          searchTerm += "*";
          theQuery->SetSearchParameter(*tagItor, searchTerm);
          delete [] buf;
          break;
        }
        delete [] buf;
      }
    }
    if (!theQuery->ValidateQuery(true)){
      std::cerr << "Unable to validate query." << std::endl;
      delete theQuery;
      continue;
    }
    if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 10,
      gdcm::network::eFind, theQuery->GetQueryDataSet())){
      std::cerr << "Failed to establish c-find connection." << std::endl;
      delete theQuery;
      continue;
    }

    std::vector<gdcm::DataSet> theQueryReturn = theManager.SendFind(theQuery);
    theManager.BreakConnection(-1);

    //now, find the dataset in theQueryReturn that corresponds to ds and then move it locally with a cmove
    //we will actually just do an in-memory comparison of the returned result.
    //for now, assume only one response.
    if (theQueryReturn.empty()){
      std::cerr << "Failed to find sent dataset." <<std::endl;
      delete theQuery;
      continue;
    }

    std::vector<gdcm::DataSet>::iterator theQueryResultItor;
    bool foundMatch = false;
/*    for (theQueryResultItor = theQueryReturn.begin(); theQueryResultItor < theQueryReturn.end(); theQueryResultItor++){
      //check to see if any data sets match upon return.
      theManager.EstablishConnectionMove(aetitle, call, remote, 0, portno, 10, moveReturnPort, *theQueryResultItor);
      std::vector<gdcm::DataSet> theMoveResult = theManager.SendMove(&(*theQueryResultItor));
      theManager.BreakConnection(-1);
      std::vector<gdcm::DataSet>::iterator theMoveResultItor;
      for (theMoveResultItor = theMoveResult.begin(); theMoveResultItor < theMoveResult.end(); ++theMoveResultItor){
        //now iterate over each data element

        if (AreDataSetsEqual(*theMoveResultItor, ds)){
          foundMatch = true;//can break now
          theQueryResultItor = theQueryReturn.end();
          theMoveResultItor = theMoveResult.end();
          break;
        }
      }
    }*/
    if (!foundMatch){
      std::cerr << "No found dataset matches stored dataset." <<std::endl;
      delete theQuery;
      continue;
    }
    delete theQuery;
    std::cout << fitor->c_str() << " passed scu testing." <<std::endl;
  }
  return 0;

}
