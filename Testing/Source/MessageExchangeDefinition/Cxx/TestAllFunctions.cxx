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
#include "gdcmBaseRootQuery.h"

#include "gdcmDirectory.h"
#include "gdcmTesting.h"
#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmAttribute.h"
#include "gdcmGlobal.h"

#include <iostream>
#include <fstream>

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

int TestAllFunctions(int argc, char *argv[])
{
#if 1
  std::string aetitle("UNITED1");//the ae title of this computer
  std::string call("COMMON");//the ae title of the server
  int portno = 11112;//the port of the server
  int moveReturnPort = 11111;//the port over which return cstore scps are done for cmove
  std::string remote("192.168.1.9");//the ip address of the remote server
  std::string outputDir("h:/gdcmtestdataretrievedcmtkoutput");//place to where data is returned by cmove
  std::string inputDir("h:/gdcmtestdataretrievedcmtk");//input collection of data to transfer
#else
  if( argc < 6 )
    {
    std::cerr << argv[0] << " aetitle call portno moveReturnPort remote" << std::endl;
    return 1;
    }
  std::string aetitle = argv[1]; // ("UNITED1");//the ae title of this computer
  std::string call = argv[2]; //("COMMON");//the ae title of the server
  int portno = atoi(argv[3]); // 11112;//the port of the server
  int moveReturnPort = atoi(argv[4]); // 11111;//the port over which return cstore scps are done for cmove
  std::string remote = argv[5]; //("192.168.1.4");//the ip address of the remote server
  std::string tmpdir = gdcm::Testing::GetTempDirectory( "TestAllFunctions" );
  std::string outputDir = tmpdir; // ("h:/gdcmtestdataretrievedcmtk");//place to where data is returned by cmove
  std::string inputDir = tmpdir; //("h:/gdcmtestdataretrievedcmtk");//input collection of data to transfer

#endif  
  
  gdcm::CompositeNetworkFunctions theNetworkFunctions;
  bool didItWork = theNetworkFunctions.CEcho( remote.c_str(), portno, aetitle, call );

  if (!didItWork)
    {
    std::cerr << "Echo failed." << std::endl;
    return 1;
    }

  //now, run the individual tests.
  //get the filenames from the test directory
  gdcm::Directory theDir;
  theDir.Load(inputDir, false);

  std::vector<std::string> theFilenames = theDir.GetFilenames();
  //store the datasets remotely
  didItWork = theNetworkFunctions.CStore(remote.c_str(), portno, aetitle, call, theFilenames, false);

  if (!didItWork) 
    {
    std::cerr << "Store failed." << std::endl;
    return 1;
    }

  std::vector<std::string>::iterator fitor;
  for (fitor = theFilenames.begin(); fitor < theFilenames.end(); ++fitor)
    {

    //read in the file
    gdcm::Reader theReader;
    theReader.SetFileName(fitor->c_str());
    if (!theReader.Read()) {
      std::cerr << "Test failed, dicom file " << *fitor << " failed to load." <<std::endl;
      return 1;
    }
    gdcm::File theFile = theReader.GetFile();
    gdcm::DataSet ds = theFile.GetDataSet();

    //have to construct a query from the dataset.
    //grab tag 10,10, use that to get 10,20
    //set the query just to be the first character and * after that.
    std::vector<std::pair<gdcm::Tag, std::string> > keys;
    gdcm::Tag theTag(0x0010, 0x0010);
    gdcm::Tag theIDTag(0x0010, 0x0020);
    if (ds.FindDataElement(theTag))
      {
      gdcm::DataElement de = ds.GetDataElement(theTag);
      const gdcm::ByteValue* bv = de.GetByteValue();
      int theBufferLen = bv->GetLength();
      if (theBufferLen < 2) continue;
      char* theBuf = new char[theBufferLen];
      bv->GetBuffer(theBuf, theBufferLen);
      std::string theSearchString(theBuf, theBuf + theBufferLen/2);
      delete [] theBuf;
      theSearchString += "*";
      if (theSearchString.size() %2 == 1)
        {
        theSearchString += " "; //to make sure everything is double spaced
        }
      keys.push_back(std::make_pair(theTag, theSearchString));
      }
    else 
      { 
      continue;
      }
    std::string theEmptyString;
    keys.push_back(std::make_pair(theIDTag, theEmptyString));

    
    gdcm::BaseRootQuery *theQuery =
      theNetworkFunctions.ConstructQuery(false, gdcm::ePatientRootType, gdcm::ePatient, keys);


    std::vector<gdcm::DataSet> theDataSets =
      theNetworkFunctions.CFind(remote.c_str(), portno, aetitle, call, theQuery);

    delete theQuery;

    if (theDataSets.empty())
      {
      std::cerr << "Unable to find the dataset that was just sent to the server, " << *fitor << std::endl;
      return 1;
      }

    keys.clear();
    //if it's not empty, then pull it.
    for (std::vector<gdcm::DataSet>::iterator itor = theDataSets.begin();
      itor != theDataSets.end(); itor++)
      {
      if (itor->FindDataElement(theIDTag))
        {
        gdcm::DataElement de = itor->GetDataElement(theIDTag);
        const gdcm::ByteValue *bv = de.GetByteValue();
        int theBufferLen = bv->GetLength();
        char* theBuf = new char[theBufferLen];
        bv->GetBuffer(theBuf, theBufferLen);
        std::string theSearchString(theBuf, theBuf + theBufferLen);
        delete [] theBuf;
        keys.push_back(std::make_pair(theIDTag, theSearchString));
        
        gdcm::DataElement de2 = ds.GetDataElement(theIDTag);
        if (!(de == de2))
          {
          std::cerr << "Sent dataset does not match returned dataset ID. " << std::endl;
          return 1;
          }
        break;
        }
      else 
        {
        continue;
        }
    }

    if (keys.empty())
      {
      std::cerr << "Sent dataset " << *fitor << " was not found by resulting CFind query. " << std::endl;
      return 1;
      }

    theQuery = theNetworkFunctions.ConstructQuery(true, gdcm::ePatientRootType, gdcm::ePatient, keys);
    didItWork = theNetworkFunctions.CMove(remote.c_str(), portno, aetitle, call, theQuery, moveReturnPort, outputDir);
    if (!didItWork)
      {
      std::cerr << "CMove failed for file " << *fitor << std::endl;
      return 1;
      }
    delete theQuery;

    std::cout << "File " << *fitor << " moved back to server." << std::endl;

  }
  return 0;

}
