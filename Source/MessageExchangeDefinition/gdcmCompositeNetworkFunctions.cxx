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
#include "gdcmWriter.h"
#include "gdcmPrinter.h"
#include "gdcmSimpleSubjectWatcher.h"
#include "gdcmProgressEvent.h"
#include "gdcmQueryFactory.h"
#include "gdcmULWritingCallback.h"
#include "gdcmPresentationContextGenerator.h"

namespace gdcm
{

// Execute like this:
// gdcmscu www.dicomserver.co.uk 11112 echo
bool CompositeNetworkFunctions::CEcho(const char *remote, uint16_t portno,
  const char *aetitle, const char *call)
{
  if( !remote ) return false;
  if( !aetitle )
    {
    aetitle = "GDCMSCU";
    }
  if( !call )
    {
    call = "ANY-SCP";
    }

  // Generate the PresentationContext array from the echo UID:
  PresentationContextGenerator generator;
  if( !generator.GenerateFromUID( UIDs::VerificationSOPClass ) )
    {
    gdcmErrorMacro( "Failed to generate pres context." );
    return false;
    }

  network::ULConnectionManager theManager;
  if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 10,
      generator.GetPresentationContexts() ))
    {
    gdcmErrorMacro( "Failed to establish connection." );
    return false;
    }
  std::vector<network::PresentationDataValue> theValues1 = theManager.SendEcho();

  //should print _something_ to let the user know of success, if they ask for something
  //other than a return code.
  if (Trace::GetDebugFlag())
    {
    DataSet ds = network::PresentationDataValue::ConcatenatePDVBlobs(theValues1);
    Printer thePrinter;
    thePrinter.PrintDataSet(ds, std::cout);
    }
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite

  // Check the Success Status
  DataSet ds = network::PresentationDataValue::ConcatenatePDVBlobs( theValues1 );
  Attribute<0x0,0x0900> at;
  at.SetFromDataSet( ds );

  if( at.GetValue() != 0 )
    {
    gdcmErrorMacro( "Wrong value" );
    return false;
    }

  return true;
}

// this function will take command line options and construct a cmove query from them
// returns NULL if the query could not be constructed.
// note that the caller is responsible for deleting the constructed query.
// used to build both a move and a find query (true for inMove if it's move, false if it's find)
BaseRootQuery* CompositeNetworkFunctions::ConstructQuery( ERootType inRootType,
  EQueryLevel inQueryLevel, const KeyValuePairArrayType& keys, bool inMove)
{
  KeyValuePairArrayType::const_iterator it = keys.begin();
  DataSet ds;
  for(; it != keys.end(); ++it)
    {
    DataElement de( it->first );
    const std::string &s = it->second;
    de.SetByteValue ( s.c_str(), (uint32_t)s.size() );
    ds.Insert( de );
    }
  return CompositeNetworkFunctions::ConstructQuery( inRootType,
    inQueryLevel, ds, inMove);
}

BaseRootQuery* CompositeNetworkFunctions::ConstructQuery( ERootType inRootType,
  EQueryLevel inQueryLevel, const DataSet& ds, bool inMove)
{
  BaseRootQuery* outQuery;
  if( inMove )
    outQuery = QueryFactory::ProduceQuery(inRootType, eMove, inQueryLevel);
  else
    outQuery = QueryFactory::ProduceQuery(inRootType, eFind, inQueryLevel);
  if (!outQuery)
    {
    gdcmErrorMacro( "Specify the query" );
    return NULL;
    }
  outQuery->AddQueryDataSet(ds);

  if (Trace::GetDebugFlag())
    ds.Print( std::cout );

  // setup the special character set
  std::vector<ECharSet> inCharSetType;
  inCharSetType.push_back( QueryFactory::GetCharacterFromCurrentLocale() );
  DataElement de = QueryFactory::ProduceCharacterSetDataElement(inCharSetType);
  std::string param ( de.GetByteValue()->GetPointer(),
    de.GetByteValue()->GetLength() );
  outQuery->SetSearchParameter(de.GetTag(), param );

  return outQuery;
}


//note that pointer to the base root query-- the caller must instantiated and delete
bool CompositeNetworkFunctions::CMove( const char *remote, uint16_t portno,
  const BaseRootQuery* query, uint16_t portscp,
  const char *aetitle, const char *call, const char* outputdir)
{
  if( !remote ) return false;
  if( !aetitle )
    {
    aetitle = "GDCMSCU";
    }
  if( !call )
    {
    call = "ANY-SCP";
    }

  /* movescu -v -d --aetitle GDCMDASH3 --call GDCM_STORE --patient --key
   * 8,52=IMAGE --key 8,18=1.3.12.2.1107.5.8.1.123456789.199507271758050707765
   * dicom.example.com 11112 --key 10,20 +P 5677
   * --key 20,d=1.3.12.2.1107.5.8.1.123456789.199507271758050705910
   * --key 20,e=1.3.12.2.1107.5.8.1.123456789.199507271758050706635
   */

  if (!outputdir || !*outputdir)
    {
    outputdir = ".";
    }

  // Generate the PresentationContext array from the query UID:
  PresentationContextGenerator generator;
  if( !generator.GenerateFromUID( query->GetAbstractSyntaxUID() ) )
    {
    gdcmErrorMacro( "Failed to generate pres context." );
    return false;
    }

  network::ULConnectionManager theManager;
  if (!theManager.EstablishConnectionMove(aetitle, call, remote, 0, portno, 1000,
      portscp, generator.GetPresentationContexts()))
    {
    gdcmErrorMacro( "Failed to establish connection." );
    return false;
    }

  network::ULWritingCallback theCallback;
  theCallback.SetDirectory(outputdir);
  theManager.SendMove( query, &theCallback );

  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
  return true;
}

//note that pointer to the base root query-- the caller must instantiated and delete
bool CompositeNetworkFunctions::CFind( const char *remote, uint16_t portno,
  const BaseRootQuery* query, std::vector<DataSet> &retDataSets,
  const char *aetitle, const char *call )
{
  if( !remote ) return false;
  if( !aetitle )
    {
    aetitle = "GDCMSCU";
    }
  if( !call )
    {
    call = "ANY-SCP";
    }

  // $ findscu -v  -d --aetitle ACME1 --call ACME_STORE  -P -k 0010,0010="X*"
  //   dhcp-67-183 5678  patqry.dcm
  // Add a query:

  // Generate the PresentationContext array from the query UID:
  PresentationContextGenerator generator;
  if( !generator.GenerateFromUID( query->GetAbstractSyntaxUID() ) )
    {
    gdcmErrorMacro( "Failed to generate pres context." );
    return false;
    }

  network::ULConnectionManager theManager;
  if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 1000,
      generator.GetPresentationContexts()))
    {
    gdcmErrorMacro( "Failed to establish connection." );
    return false;
    }
  std::vector<DataSet> theDataSets;
  theDataSets = theManager.SendFind( query );
  // Append the new DataSet to the ret one:
  retDataSets.insert( retDataSets.end(), theDataSets.begin(), theDataSets.end() );

  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
  return true;
}

class MyWatcher : public SimpleSubjectWatcher
{
  size_t nfiles;
  double progress;
  size_t index;
  double refprogress;
public:
  MyWatcher(Subject * s, const char *comment = "", size_t n = 1):SimpleSubjectWatcher(s,comment),nfiles(n),progress(0),index(0),refprogress(0){}
  void ShowIteration()
    {
    index++;
    assert( index <= nfiles );
    refprogress = progress;
    }
  void ShowProgress(Subject *caller, const Event &evt)
    {
    const ProgressEvent &pe = dynamic_cast<const ProgressEvent&>(evt);
    (void)caller;
    progress = refprogress + (1. / (double)nfiles ) * pe.GetProgress();
//    std::cout << "Progress: " << progress << " " << pe.GetProgress() << std::endl;
    }
  virtual void ShowDataSet(Subject *, const Event &) {}
};

bool CompositeNetworkFunctions::CStore( const char *remote, uint16_t portno,
  const Directory::FilenamesType& filenames,
  const char *aetitle, const char *call)
{
  if( !remote ) return false;
  // TODO AE-TITLE are more restrictive than that !
  if( !aetitle )
    {
    aetitle = "GDCMSCU";
    }
  if( !call )
    {
    call = "ANY-SCP";
    }

  SmartPointer<network::ULConnectionManager> ps = new network::ULConnectionManager;
  network::ULConnectionManager &theManager = *ps;
  Directory::FilenamesType const &files = filenames;

  //SimpleSubjectWatcher watcher(ps, "cstore");
  MyWatcher watcher(ps, "cstore", files.size() );

  // Generate the PresentationContext array from the File-Set:
  PresentationContextGenerator generator;
  if( !generator.GenerateFromFilenames(filenames) )
    {
    gdcmErrorMacro( "Failed to generate pres context." );
    return false;
    }

  if (!theManager.EstablishConnection(aetitle, call, remote, 0,
      portno, 1000, generator.GetPresentationContexts() ))
    {
    gdcmErrorMacro( "Failed to establish connection." );
    return false;
    }

  const char *fn = ""; // FIXME
  try
    {
    for( size_t i = 0; i < files.size(); ++i )
      {
      const std::string & filename = files[i];
      fn = filename.c_str();
      assert( fn && *fn );
      Reader reader;
      reader.SetFileName( filename.c_str() );
      gdcmDebugMacro( "Processing: " << filename );
      if( !reader.Read() )
        {
        gdcmErrorMacro( "Could not read: " << filename );
        return false;
        }
      const File &file = reader.GetFile();
      theManager.SendStore( file );
      theManager.InvokeEvent( IterationEvent() );
      gdcmDebugMacro( "C-Store of file " << filename << " was successful." );
      }
    }
  catch ( Exception &e )
    {
    (void)e;  //to avoid unreferenced variable warning on release
    // If you reach here this is basically because GDCM does not support encoding other
    // than raw transfer syntx (Little Endian Explicit/Implicit...)
    theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
    gdcmErrorMacro( "C-Store of file " << fn << " was unsuccessful, aborting. " )
    gdcmErrorMacro( "Error was " << e.what() );
    return false;
    }
  catch (...)
    {
    theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
    gdcmErrorMacro( "C-Store of file " << fn << " was unsuccessful, aborting. " )
    return false;
    }
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
  return true;
}

} // end namespace gdcm
