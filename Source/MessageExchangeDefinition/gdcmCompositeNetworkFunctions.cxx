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

#include <socket++/echo.h>

#include "gdcmReader.h"
#include "gdcmAttribute.h"
#include "gdcmULConnectionManager.h"
#include "gdcmULConnection.h"
#include "gdcmDataSet.h"
#include "gdcmVersion.h"
#include "gdcmGlobal.h"
#include "gdcmSystem.h"
#include "gdcmUIDGenerator.h"
#include "gdcmStringFilter.h"
#include "gdcmWriter.h"
#include "gdcmPrinter.h"

#include "gdcmQueryFactory.h"
#include "gdcmDirectory.h"
#include "gdcmStudyRootQuery.h"
#include "gdcmPatientRootQuery.h"
#include "gdcmULWritingCallback.h"
#include "gdcmImageReader.h"

using namespace gdcm;


// Execute like this:
// ./bin/gdcmscu www.dicomserver.co.uk 11112 echo
bool CompositeNetworkFunctions::CEcho( const char *remote, int portno, std::string const &aetitle,
            std::string const &call )
{
  gdcm::network::ULConnectionManager theManager;
  gdcm::DataSet blank;
  if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 10,
      gdcm::network::eEcho, blank))
    {
      if (gdcm::Trace::GetErrorFlag())
        {
        std::cerr << "Failed to establish connection." << std::endl;
        }
    return false;
    }
  std::vector<gdcm::network::PresentationDataValue> theValues1 = theManager.SendEcho();

  //should print _something_ to let the user know of success, if they ask for something
  //other than a return code.
  if (gdcm::Trace::GetWarningFlag())
    {
      gdcm::DataSet ds = gdcm::network::PresentationDataValue::ConcatenatePDVBlobs(theValues1);
      gdcm::Printer thePrinter;
      thePrinter.PrintDataSet(ds, std::cout);
    }
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite

  // Check the Success Status
  gdcm::DataSet ds = gdcm::network::PresentationDataValue::ConcatenatePDVBlobs( theValues1 );
  gdcm::Attribute<0x0,0x0900> at;
  at.SetFromDataSet( ds );

  if( at.GetValue() != 0 )
    {
    return false;
    }

  return true;
}

//this function will take command line options and construct a cmove query from them
//returns NULL if the query could not be constructed.
//note that the caller is responsible for deleting the constructed query.
//used to build both a move and a find query (true for inMove if it's move, false if it's find)
gdcm::BaseRootQuery* CompositeNetworkFunctions::ConstructQuery(bool inMove, bool findstudy, bool findpatient,
                                             const std::vector< std::pair<gdcm::Tag, std::string> >& keys)
{
  gdcm::StringFilter sf;
  std::vector< std::pair<gdcm::Tag, std::string> >::const_iterator it =
    keys.begin();
  gdcm::BaseRootQuery* outQuery = 0;
  if (findstudy)
    {
    //theQuery = new gdcm::network::StudyRootQuery();
    outQuery =
      gdcm::QueryFactory::ProduceQuery(
        gdcm::eStudyRootType, gdcm::eStudy);
    }
  else if (findpatient)
    {
    //theQuery = new gdcm::network::PatientRootQuery();
    outQuery =
      gdcm::QueryFactory::ProduceQuery(
        gdcm::ePatientRootType, gdcm::ePatient);

    }
  else
    {
    if (gdcm::Trace::GetErrorFlag())
      std::cerr << "Specify the query" << std::endl;
    return NULL;
    }
  gdcm::DataSet ds;
  for(; it != keys.end(); ++it)
    {
    std::string s = sf.FromString( it->first, it->second.c_str(), it->second.size() );
    if (inMove)
      {
      gdcm::DataElement de( it->first );
      de.SetByteValue ( s.c_str(), s.size() );
      ds.Insert( de );
      }
    outQuery->SetSearchParameter(it->first, s);
    }

  if (gdcm::Trace::GetWarningFlag())
    ds.Print( std::cout );


  // setup the special character set
  std::vector<gdcm::ECharSet> inCharSetType;
  inCharSetType.push_back( gdcm::QueryFactory::GetCharacterFromCurrentLocale() );
  gdcm::DataElement de = gdcm::QueryFactory::ProduceCharacterSetDataElement(inCharSetType);
  std::string param ( de.GetByteValue()->GetPointer(),
    de.GetByteValue()->GetLength() );
  outQuery->SetSearchParameter(de.GetTag(), param );

  return outQuery;
}


//note that pointer to the base root query-- the caller must instantiated and delete
bool CompositeNetworkFunctions::CMove( const char *remote, int portno, std::string const &aetitle,
            std::string const &call, gdcm::BaseRootQuery* query,
            int portscp, std::string const & outputdir)
{
  // $ findscu -v  -d --aetitle ACME1 --call ACME_STORE  -P -k 0010,0010="X*" dhcp-67-183 5678  patqry.dcm
  // Add a query:

  if (outputdir.empty())
    {
      if (gdcm::Trace::GetErrorFlag())
        {
        std::cerr << "Output directory not specified." << std::endl;
        }
    return false;
    }

  gdcm::network::ULConnectionManager theManager;
  if (!theManager.EstablishConnectionMove(aetitle, call, remote, 0, portno, 1000,
      portscp, query->GetQueryDataSet()))
    {
      if (gdcm::Trace::GetErrorFlag())
        {
        std::cerr << "Failed to establish connection." << std::endl;
        }
    return false;
    }

  int ret = 0;
  gdcm::network::ULWritingCallback theCallback;
  theCallback.SetDirectory(outputdir);
  theManager.SendMove( query, &theCallback );

  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
  return (ret == 0);//if ret == 0, then nothing was broken
}

//note that pointer to the base root query-- the caller must instantiated and delete
std::vector<gdcm::DataSet> CompositeNetworkFunctions::CFind( const char *remote, int portno , std::string const &aetitle,
                                  std::string const &call , gdcm::BaseRootQuery* query )
{
  // $ findscu -v  -d --aetitle ACME1 --call ACME_STORE  -P -k 0010,0010="X*" dhcp-67-183 5678  patqry.dcm
  // Add a query:
  gdcm::network::ULConnectionManager theManager;
  std::vector<gdcm::DataSet> theDataSets;
  //theManager.EstablishConnection("ACME1", "ACME_STORE", remote, 0, portno, 1000, gdcm::network::eFind, ds);
  if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 1000, gdcm::network::eFind,  query->GetQueryDataSet())){

    if (gdcm::Trace::GetErrorFlag())
      {
      std::cerr << "Failed to establish connection." << std::endl;
      }
    return theDataSets;
  }
  theDataSets = theManager.SendFind( query );

  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
  return theDataSets;
}

bool CompositeNetworkFunctions::CStore( const char *remote, int portno,
             std::string const &aetitle, std::string const &call,
             std::vector<std::string> const & filenames, bool inRecursive )
{
  std::string filename = filenames[0];
  gdcm::network::ULConnectionManager theManager;
  std::vector<std::string> files;
  if( gdcm::System::FileIsDirectory(filename.c_str()) )
    {
    unsigned int nfiles = 1;
    gdcm::Directory dir;
    nfiles = dir.Load(filename, inRecursive);
    files = dir.GetFilenames();
    }
  else
    {
    files = filenames;
    }
  filename = files[0];
  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  if( !reader.Read() ) return 1;
  //const gdcm::File &file = reader.GetFile();
  const gdcm::DataSet &ds = reader.GetFile().GetDataSet();

  if (!theManager.EstablishConnection(aetitle, call, remote, 0,
      portno, 1000, gdcm::network::eStore, ds))
    {
      if (gdcm::Trace::GetErrorFlag())
        {
        std::cerr << "Failed to establish connection." << std::endl;
        }
      return 1;
    }
#if 0
  // Right now we are never reading back the AC-Acpt to
  // if we can prefer a compressed TS
  gdcm::network::ULConnection* uc = theManager.GetConnection();
  std::vector<gdcm::network::PresentationContext> const &pcs =
    uc->GetPresentationContexts();
  std::vector<gdcm::network::PresentationContext>::const_iterator it =
    pcs.begin();
  std::cout << "B" << std::endl;
  for( ; it != pcs.end(); ++it )
    {
    it->Print ( std::cout );
    }
  std::cout << "BB" << std::endl;
  theManager.SendStore( (gdcm::DataSet*)&ds );
#endif

  theManager.SendStore( (gdcm::DataSet*)&ds );

  for( size_t i = 1; i < files.size(); ++i )
    {
    const std::string & filename = files[i];
    gdcm::Reader reader;
    reader.SetFileName( filename.c_str() );
    if( !reader.Read() ) return false;
    const gdcm::DataSet &ds = reader.GetFile().GetDataSet();
    theManager.SendStore( (gdcm::DataSet*)&ds );
    }

  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
  return true;

}
