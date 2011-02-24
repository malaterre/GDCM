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

//#include "gdcmDirectory.h"
#include "gdcmScanner.h"
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

int TestSCUFunctions(int argc, char *argv[])
{
  if( argc < 6 )
    {
    std::cerr << argv[0] << " aetitle call portno moveReturnPort remote" << std::endl;
    return 1;
    }
  std::string aetitle = argv[1]; // the ae title of this computer
  std::string call = argv[2]; // the ae title of the server
  int portno = atoi(argv[3]); // the port of the server
  int moveReturnPort = atoi(argv[4]); // the port over which return cstore scps are done for cmove
  std::string remote = argv[5]; //the ip address of the remote server
  std::string tmpdir = gdcm::Testing::GetTempDirectory( "TestSCUFunctions" );
  std::string outputDir = tmpdir; //place to where data is returned by cmove
  //std::string inputDir = gdcm::Testing::GetDataRoot(); //input collection of data to transfer

  gdcm::CompositeNetworkFunctions theNetworkFunctions;
  bool didItWork = theNetworkFunctions.CEcho( remote.c_str(), portno,
    aetitle.c_str(), call.c_str() );

  if (!didItWork)
    {
    std::cerr << "Echo failed." << std::endl;
    return 1;
    }

  std::vector<std::string> theFilenames;
  const char *filename;
  int i = 0;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    theFilenames.push_back( filename );
    ++i;
    }

  // Fow now lets eliminate invalid candidates:
  // - no SOP Class UID
  // - no SOP Instance UID
  gdcm::Scanner sc;
  gdcm::Tag sopclass(0x8,0x16);
  gdcm::Tag sopinstance(0x8,0x18);
  sc.AddTag( sopclass );
  sc.AddTag( sopinstance );
  if( !sc.Scan( theFilenames ) )
    {
    return 1;
    }

  // remove any file without SOP Instance UID
  for(
    gdcm::Directory::FilenamesType::iterator it = theFilenames.begin();
    it != theFilenames.end(); )
    {
    const char *file = it->c_str();
    const char* v1 = sc.GetValue(file, sopclass );
    const char* v2 = sc.GetValue(file, sopinstance );
    if( !v1 || !v2 ) it = theFilenames.erase( it );
    else ++it;
    }


  //store the datasets remotely
  didItWork = theNetworkFunctions.CStore(remote.c_str(), portno, theFilenames,
    aetitle.c_str(), call.c_str());

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
    if (!theReader.Read())
      {
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
      theNetworkFunctions.ConstructQuery(gdcm::ePatientRootType, gdcm::ePatient, keys);

    std::vector<gdcm::DataSet> theDataSets;
    bool b = theNetworkFunctions.CFind(remote.c_str(), portno, theQuery, theDataSets, aetitle.c_str(), call.c_str());

    delete theQuery;
    if( !b )
      {
      std::cerr << "Problem in CFind" << std::endl;
      return 1;
      }

    if (theDataSets.empty())
      {
      std::cerr << "Unable to find the dataset that was just sent to the server, " << *fitor << std::endl;
      return 1;
      }

    keys.clear();
    //if it's not empty, then pull it.
    std::vector<gdcm::DataSet>::iterator itor;
    for (itor = theDataSets.begin(); itor != theDataSets.end(); itor++)
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

    theQuery = theNetworkFunctions.ConstructQuery(gdcm::ePatientRootType, gdcm::ePatient, keys, true);
    std::vector<gdcm::DataSet> theMoveDataSets = theNetworkFunctions.CMoveToMemory(remote.c_str(), portno, theQuery,
      moveReturnPort, aetitle.c_str(), call.c_str() );
    if (theMoveDataSets.empty())
      {
      std::cerr << "CMove failed for file " << *fitor << std::endl;
      return 1;
      }
    else  {
      bool foundMatch = false;
      for (itor = theMoveDataSets.begin(); itor != theMoveDataSets.end(); itor++)
      {
        if (AreDataSetsEqual(*itor, ds)){
          foundMatch = true;
          break;
        }
      }
      if (!foundMatch){
        std::cerr << "Retrieved datasets did not match sent dataset." << std::endl;
        return 1;
      }
    }
    delete theQuery;
    

    std::cout << "File " << *fitor << " moved back to server." << std::endl;
    }

  return 0;
}
