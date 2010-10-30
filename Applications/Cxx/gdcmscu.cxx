/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 * Simple command line tool to echo/store/find/move DICOM using
 * DICOM Query/Retrieve
 * This is largely inspired by other tool available from other toolkit, namely:
 * echoscu (DCMTK)
 * findscu (DCMTK)
 * movescu (DCMTK)
 * storescu (DCMTK)
 */
#include "gdcmReader.h"
#include "gdcmAttribute.h"
#include "gdcmULConnectionManager.h"
#include "gdcmDataSet.h"
#include "gdcmVersion.h"
#include "gdcmGlobal.h"
#include "gdcmSystem.h"
#include "gdcmUIDGenerator.h"
#include "gdcmStringFilter.h"
#include "gdcmWriter.h"

//for testing!  Should be put in a testing executable,
//but it's just here now because I know this path works
#include "gdcmDirectory.h"
#include "gdcmImageReader.h"
#include "gdcmQueryFactory.h"
#include "gdcmStudyRootQuery.h"
#include "gdcmPatientRootQuery.h"
#include "gdcmDefs.h"

#include <fstream>
#include <socket++/echo.h>
#include <stdlib.h>
#include <getopt.h>

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

bool CTestAllFunctions(const char* remote, int portno, const std::string& aetitle,
                       const std::string& call, const std::string& gdcmDataDirectory)
{
  //first, run an echo, make sure that that works.
  gdcm::network::ULConnectionManager theManager;
  gdcm::DataSet blank;
  if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 10, gdcm::network::eEcho, blank)){
    std::cerr << "Failed to establish connection." << std::endl;
    return false;
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
  theDir.Load(gdcmDataDirectory, false);

  std::vector<std::string> theFilenames = theDir.GetFilenames();

  std::vector<std::string>::iterator fitor;
  gdcm::Reader theReader;
  for (fitor = theFilenames.begin(); fitor < theFilenames.end(); ++fitor){

    //read in the file
    theReader.SetFileName(fitor->c_str());
    if (!theReader.Read()) {
      std::cerr << "Test failed, dicom file failed to load." <<std::endl;
      return false;
    }
    gdcm::File theFile = theReader.GetFile();
    gdcm::DataSet ds = theFile.GetDataSet();

    //store the file remotely
    if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 10, gdcm::network::eStore, ds)){
      std::cerr << "Failed to establish c-store connection." << std::endl;
      return false;
    }

    std::vector<gdcm::DataSet> theReturn = theManager.SendStore(&ds);
    theManager.BreakConnection(-1);
/*//FIXME-- must make the test useful
    //then search for it based on 0x20,xd and 0x20,xe, and maybe 0x8,0x18
    //but have to construct a proper cfind query first!
    gdcm::DataSet query;
    gdcm::Attribute<0x8,0x52> at1 = { "PATIENT" };
    query.Insert( at1.GetAsDataElement() );
  //  gdcm::Attribute<0x10,0x10> at2 = { "test" };
  gdcm::Attribute<0x10,0x10> at2 = { "FROG^KERMIT TCH " };
    //gdcm::PrivateTag t(0x10,0x10, "test");
    //query.Insert( ds.GetDataElement(t) );
    //query.Insert( at2.GetAsDataElement() );
    gdcm::Attribute<0x10,0x20> at3 = { "" };
    //query.Insert( at3.GetAsDataElement() );
    //store the file remotely
    if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 10, gdcm::network::eFind, query)){
      std::cerr << "Failed to establish c-find connection." << std::endl;
      return false;
    }

    std::vector<gdcm::DataSet> theQueryReturn = theManager.SendFind(&query);
    theManager.BreakConnection(-1);

    //now, find the dataset in theQueryReturn that corresponds to ds and then move it locally with a cmove
    //we will actually just do an in-memory comparison of the returned result.
    //for now, assume only one response.
    if (theQueryReturn.empty()){
      std::cerr << "Failed to find sent dataset." <<std::endl;
      return false;
    }

    std::vector<gdcm::DataSet>::iterator theQueryResultItor;
    bool foundMatch = false;
    for (theQueryResultItor = theQueryReturn.begin(); theQueryResultItor < theQueryReturn.end(); theQueryResultItor++){
      //check to see if any data sets match upon return.
      theManager.EstablishConnection(aetitle, call, remote, 0, portno, 10, gdcm::network::eMove, *theQueryResultItor);
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
    }
    if (!foundMatch){
      std::cerr << "No found dataset matches stored dataset." <<std::endl;
      return false;
    }
    std::cout << fitor->c_str() << " passed scu testing." <<std::endl;*/
  }
  return true;
}

// Execute like this:
// ./bin/gdcmscu www.dicomserver.co.uk 11112 echo
void CEcho( const char *remote, int portno, std::string const &aetitle,
std::string const &call )
{
  gdcm::network::ULConnectionManager theManager;
  gdcm::DataSet blank;
  if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 10, gdcm::network::eEcho, blank)){
    std::cerr << "Failed to establish connection." << std::endl;
    exit (-1);
  }
  std::vector<gdcm::network::PresentationDataValue> theValues1 = theManager.SendEcho();
  std::vector<gdcm::network::PresentationDataValue>::iterator itor;
  for (itor = theValues1.begin(); itor < theValues1.end(); itor++){
    itor->Print(std::cout);
  }
  std::vector<gdcm::network::PresentationDataValue> theValues2 = theManager.SendEcho();
  for (itor = theValues2.begin(); itor < theValues2.end(); itor++){
    itor->Print(std::cout);
  }
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite

}

//note that pointer to the base root query-- the caller must instantiated and delete
void CMove( const char *remote, int portno, std::string const &aetitle,
  std::string const &call, gdcm::network::BaseRootQuery* query,
  int portscp, std::string const & outputdir )
{
  // $ findscu -v  -d --aetitle ACME1 --call ACME_STORE  -P -k 0010,0010="X*" dhcp-67-183 5678  patqry.dcm
  // Add a query:

  gdcm::network::ULConnectionManager theManager;
  //theManager.EstablishConnection("ACME1", "ACME_STORE", remote, 0, portno, 1000, gdcm::network::eMove, ds);
  if (!theManager.EstablishConnectionMove(aetitle, call, remote, 0, portno, 1000, portscp, query->GetQueryDataSet())){
    std::cerr << "Failed to establish connection." << std::endl;
    exit (-1);
  }

  std::vector<gdcm::DataSet> theDataSets  = theManager.SendMove( query );
  std::vector<gdcm::DataSet>::iterator itor;
  int c = 0;
  //write to the output directory
  if (!outputdir.empty())
    {
    //loop over each dataset, write out the given objects by the SOP Instance UID
    for (itor = theDataSets.begin(); itor < theDataSets.end(); itor++)
      {
      if (itor->FindDataElement(gdcm::Tag(0x0008,0x0018)))
        {
        gdcm::DataElement de = itor->GetDataElement(gdcm::Tag(0x0008,0x0018));
        std::string sopclassuid_str( de.GetByteValue()->GetPointer(), de.GetByteValue()->GetLength() );
        gdcm::Writer w;
        std::string theLoc = outputdir + "/" + sopclassuid_str + ".dcm";
        w.SetFileName(theLoc.c_str());
        gdcm::File &f = w.GetFile();
        f.SetDataSet(*itor);
        gdcm::FileMetaInformation &fmi = f.GetHeader();
        fmi.SetDataSetTransferSyntax( gdcm::TransferSyntax::ImplicitVRLittleEndian );
        w.SetCheckFileMetaInformation( true );
        if (!w.Write())
          {
          std::cerr << "Failed to write " << sopclassuid_str << std::endl;
          }
        }
      }
    }
  else
    {
    std::cerr << "Output directory not specified." << std::endl;
    }

  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
}

//note that pointer to the base root query-- the caller must instantiated and delete
void CFind( const char *remote, int portno , std::string const &aetitle,
std::string const &call , gdcm::network::BaseRootQuery* query )
{
  // $ findscu -v  -d --aetitle ACME1 --call ACME_STORE  -P -k 0010,0010="X*" dhcp-67-183 5678  patqry.dcm
  // Add a query:
  gdcm::network::ULConnectionManager theManager;
  //theManager.EstablishConnection("ACME1", "ACME_STORE", remote, 0, portno, 1000, gdcm::network::eFind, ds);
  if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 1000, gdcm::network::eFind,  query->GetQueryDataSet())){
    std::cerr << "Failed to establish connection." << std::endl;
    exit (-1);
  }
  std::vector<gdcm::DataSet> theDataSets  = theManager.SendFind( query );
  std::vector<gdcm::DataSet>::iterator itor;
  int c = 0;
  for (itor = theDataSets.begin(); itor < theDataSets.end(); itor++){
    std::cout << "Message " << c++ << std::endl;
    itor->Print(std::cout);
  }
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
}

void CStore( const char *remote, int portno,
  std::string const &aetitle,
  std::string const &call,
  std::string const & filename )
{
  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  reader.Read();
  const gdcm::DataSet &ds = reader.GetFile().GetDataSet();

  gdcm::network::ULConnectionManager theManager;
  if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 1000, gdcm::network::eStore, ds)){
    std::cerr << "Failed to establish connection." << std::endl;
    exit (-1);
  }
  theManager.SendStore( (gdcm::DataSet*)&ds );
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite

}

void PrintVersion()
{
  std::cout << "gdcmscu: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmscu [OPTION]...[OPERATION]...HOSTNAME...[PORT]..." << std::endl;
  std::cout << "Execute a DICOM Q/R operation to HOSTNAME, using port PORT (104 when not specified)\n";
  std::cout << "Options:" << std::endl;
  std::cout << "  -H --hostname       Hostname." << std::endl;
  std::cout << "  -p --port           Port number." << std::endl;
  std::cout << "     --aetitle        Set Calling AE Title." << std::endl;
  std::cout << "     --call           Set Called AE Title." << std::endl;
//  std::cout << "  -t --testdir        Set the directory for testing images (if --test is chosen)." << std::endl;
  std::cout << "Mode Options:" << std::endl;
  std::cout << "     --echo           C-ECHO (default when none)." << std::endl;
  std::cout << "     --store          C-STORE." << std::endl;
  std::cout << "     --find           C-FIND." << std::endl;
  std::cout << "     --move           C-MOVE." << std::endl;
//  std::cout << "     --test           Test all functions agains a known working server." << std::endl;
  std::cout << "C-STORE Options:" << std::endl;
  std::cout << "  -i --input          DICOM filename" << std::endl;
  std::cout << "C-FIND Options:" << std::endl;
  //std::cout << "     --worklist       C-FIND Worklist Model." << std::endl;//!!not supported atm
  std::cout << "     --patient        C-FIND Patient Root Model." << std::endl;
  std::cout << "     --study          C-FIND Study Root Model." << std::endl;
  //std::cout << "     --psonly         C-FIND Patient/Study Only Model." << std::endl;
  std::cout << "C-MOVE Options:" << std::endl;
  std::cout << "  -o --output         DICOM output directory." << std::endl;
  std::cout << "     --port-scp       Port used for incoming association." << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "     --root-uid               Root UID." << std::endl;
  std::cout << "     --resources-path         Resources path." << std::endl;
  std::cout << "  -V --verbose   more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning   print warning info." << std::endl;
  std::cout << "  -D --debug     print debug info." << std::endl;
  std::cout << "  -E --error     print error info." << std::endl;
  std::cout << "  -h --help      print help." << std::endl;
  std::cout << "  -v --version   print version." << std::endl;
}

int main(int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::string shostname;
  std::string callingaetitle = "GDCMSCU";
  std::string callaetitle = "ANY-SCP";
  int port = 104; // default
  int portscp = 0;
  int outputopt = 0;
  int portscpnum = 0;
  std::string filename;
  std::string outputdir;
  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;
  int echomode = 0;
  int storemode = 0;
  int findmode = 0;
  int movemode = 0;
  int findworklist = 0;
  int findpatient = 0;
  int findstudy = 0;
  int findpsonly = 0;
  std::string xmlpath;
  int resourcespath = 0;
  std::string root;
  int rootuid = 0;
  gdcm::Tag tag;
  std::vector< std::pair<gdcm::Tag, std::string> > keys;

  //if you want study or patient level query help, uncomment these lines
  //gdcm::network::BaseRootQuery* theBase =
  //  gdcm::network::QueryFactory::ProduceQuery(gdcm::network::ePatientRootType);
  //theBase->WriteHelpFile(std::cout);
  //delete theBase;

  // FIXME: remove testing stuff:
  int testmode = 0;
  std::string testDir = "D:/gdcmData/scusubset";//changing the testdir doesn't work;
  //I think I'm not so good with these options
  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
/*
   struct option {
              const char *name;
              int has_arg;
              int *flag;
              int val;
          };
*/
    static struct option long_options[] = {
        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},
        {"hostname", 1, 0, 0},     // -h
        {"aetitle", 1, 0, 0},     //
        {"call", 1, 0, 0},     //
        {"port", 0, &port, 1}, // -p
        {"input", 1, 0, 0}, // dcmfile-in
        {"testdir", 0, 0, 1},
        {"echo", 0, &echomode, 1}, // --echo
        {"store", 0, &storemode, 1}, // --store
        {"find", 0, &findmode, 1}, // --find
        {"move", 0, &movemode, 1}, // --move
        {"key", 1, 0, 0}, // --key
        {"test", 0, &testmode, 1}, // --test
        {"worklist", 0, &findworklist, 1}, // --worklist
        {"patient", 0, &findpatient, 1}, // --patient
        {"study", 0, &findstudy, 1}, // --study
        {"psonly", 0, &findpsonly, 1}, // --psonly
        {"port-scp", 1, &portscp, 1}, // --port-scp
        {"output", 1, &outputopt, 1}, // --output
        {0, 0, 0, 0} // required
    };
    static const char short_options[] = "i:H:p:VWDEhvk:o:";
    c = getopt_long (argc, argv, short_options,
      long_options, &option_index);
    if (c == -1)
      {
      break;
      }

    switch (c)
      {
    case 0:
    case '-':
        {
        const char *s = long_options[option_index].name;
        //printf ("option %s", s);
        if (optarg)
          {
          if( option_index == 0 ) /* input */
            {
            assert( strcmp(s, "input") == 0 );
            assert( filename.empty() );
            filename = optarg;
            }
          else if( option_index == 7 ) /* calling aetitle */
            {
            assert( strcmp(s, "aetitle") == 0 );
            //assert( callingaetitle.empty() );
            callingaetitle = optarg;
            }
          else if( option_index == 8 ) /* called aetitle */
            {
            assert( strcmp(s, "call") == 0 );
            //assert( callaetitle.empty() );
            callaetitle = optarg;
            }
          else if( option_index == 16 ) /* key */
            {
            assert( strcmp(s, "key") == 0 );
            if( !tag.ReadFromCommaSeparatedString(optarg) )
              {
              std::cerr << "Could not read Tag: " << optarg << std::endl;
              return 1;
              }
            std::stringstream ss;
            ss.str( optarg );
            uint16_t dummy;
            char cdummy; // comma
            ss >> std::hex >> dummy;
            assert( tag.GetGroup() == dummy );
            ss >> cdummy;
            assert( cdummy == ',' );
            ss >> std::hex >> dummy;
            assert( tag.GetElement() == dummy );
            ss >> cdummy;
            assert( cdummy == ',' || cdummy == '=' );
            std::string str;
            ss >> str;
            keys.push_back( std::make_pair(tag, str) );
            }
          else if( option_index == 11 ) /* test */
            {
            assert( strcmp(s, "testdir") == 0 );
            //assert( callaetitle.empty() );
            testDir = optarg;
            }
          else if( option_index == 22 ) /* port-scp */
            {
            assert( strcmp(s, "port-scp") == 0 );
            portscpnum = atoi(optarg);
            }
          else if( option_index == 23 ) /* output */
            {
            assert( strcmp(s, "output") == 0 );
            outputdir = optarg;
            }
          else
            {
            assert( 0 );
            }
          //printf (" with arg %s", optarg);
          }
        //printf ("\n");
        }
      break;

    case 'k':
        {
        if( !tag.ReadFromCommaSeparatedString(optarg) )
          {
          std::cerr << "Could not read Tag: " << optarg << std::endl;
          return 1;
          }
        std::stringstream ss;
        ss.str( optarg );
        uint16_t dummy;
        char cdummy; // comma
        ss >> std::hex >> dummy;
        assert( tag.GetGroup() == dummy );
        ss >> cdummy;
        assert( cdummy == ',' );
        ss >> std::hex >> dummy;
        assert( tag.GetElement() == dummy );
        ss >> cdummy;
        assert( cdummy == ',' || cdummy == '=' );
        std::string str;
        ss >> str;
        keys.push_back( std::make_pair(tag, str) );
        }
      break;

    case 'i':
      //printf ("option i with value '%s'\n", optarg);
      assert( filename.empty() );
      filename = optarg;
      break;

    case 'o':
      assert( outputdir.empty() );
      outputdir = optarg;
      break;

    case 'H':
      shostname = optarg;
      break;

    case 'p':
      port = atoi( optarg );
      break;

    case 'V':
      verbose = 1;
      break;

    case 'W':
      warning = 1;
      break;

    case 'D':
      debug = 1;
      break;

    case 'E':
      error = 1;
      break;

    case 'h':
      help = 1;
      break;

    case 'v':
      version = 1;
      break;

    case '?':
      break;

    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
      }
  }

  if (optind < argc)
    {
    int v = argc - optind;
    // hostname port filename
    if( v == 1 )
      {
      shostname = argv[optind++];
      }
    else if( v == 2 )
      {
      shostname = argv[optind++];
      port = atoi( argv[optind++] );
      }
    else if( v == 3 )
      {
      shostname = argv[optind++];
      port = atoi( argv[optind++] );
      filename = argv[optind++];
      }
    else
      {
      return 1;
      }
    assert( optind == argc );
    }

  if( version )
    {
    PrintVersion();
    return 0;
    }

  if( help )
    {
    PrintHelp();
    return 0;
    }

  // Debug is a little too verbose
  gdcm::Trace::SetDebug( debug );
  gdcm::Trace::SetWarning( warning );
  gdcm::Trace::SetError( error );
  // when verbose is true, make sure warning+error are turned on:
  if( verbose )
    {
    gdcm::Trace::SetWarning( verbose );
    gdcm::Trace::SetError( verbose);
    }
  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( callaetitle.c_str() );
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
      return 1;
      }
    }
  // All set, then load the XML files:
  if( !g.LoadResourcesFiles() )
    {
    std::cerr << "Could not load XML file from specified path" << std::endl;
    return 1;
    }
  const gdcm::Defs &defs = g.GetDefs(); (void)defs;
  if( !rootuid )
    {
    // only read the env var if no explicit cmd line option
    // maybe there is an env var defined... let's check
    const char *rootuid_env = getenv("GDCM_ROOT_UID");
    if( rootuid_env )
      {
      rootuid = 1;
      root = rootuid_env;
      }
    }
  if( rootuid )
    {
    // root is set either by the cmd line option or the env var
    if( !gdcm::UIDGenerator::IsValid( root.c_str() ) )
      {
      std::cerr << "specified Root UID is not valid: " << root << std::endl;
      return 1;
      }
    gdcm::UIDGenerator::SetRoot( root.c_str() );
    }

  if( shostname.empty() )
    {
    std::cerr << "Hostname missing" << std::endl;
    return 1;
    }
  if( port == 0 )
    {
    std::cerr << "Problem with port number" << std::endl;
    return 1;
    }
  // checkout outputdir opt:
  if( outputopt )
    {
    if( !gdcm::System::FileIsDirectory( outputdir.c_str()) )
      {
      if( !gdcm::System::MakeDirectory( outputdir.c_str() ) )
        {
        std::cerr << "Sorry: " << outputdir << " is not a valid directory.";
        std::cerr << std::endl;
        std::cerr << "and I could not create it.";
        std::cerr << std::endl;
        return 1;
        }
      }
    }

  const char *hostname = shostname.c_str();
  std::string mode = "echo";
  if ( echomode )
    {
    mode = "echo";
    }
  else if ( storemode )
    {
    mode = "store";
    }
  else if ( findmode )
    {
    mode = "find";
    }
  else if ( movemode )
    {
    mode = "move";
    }
  if ( testmode )
    {
    mode = "test";
    }

  if ( mode == "server" ) // C-STORE SCP
    {
    // MM: Do not expose that to user for now (2010/10/11).
    //CStoreServer( port );
    return 1;
    }
  else if ( mode == "echo" ) // C-ECHO SCU
    {
    // ./bin/gdcmscu mi2b2.slicer.org 11112  --aetitle ACME1 --call MI2B2
    // ./bin/gdcmscu --echo mi2b2.slicer.org 11112  --aetitle ACME1 --call MI2B2
    CEcho( hostname, port, callingaetitle, callaetitle );
    }
  else if ( mode == "move" ) // C-FIND SCU
    {
    // ./bin/gdcmscu --move dhcp-67-183 5678 move
    // ./bin/gdcmscu --move mi2b2.slicer.org 11112 move
    gdcm::StringFilter sf;
    std::vector< std::pair<gdcm::Tag, std::string> >::const_iterator it =
      keys.begin();
    gdcm::network::BaseRootQuery* theQuery;
    if (findstudy > 0)
      {
      theQuery = new gdcm::network::StudyRootQuery();
      }
    else
      {
      theQuery = new gdcm::network::PatientRootQuery();
      }
    gdcm::DataSet ds;
    for(; it != keys.end(); ++it)
      {
      std::string s = sf.FromString( it->first, it->second.c_str(), it->second.size() );
      gdcm::DataElement de( it->first );
      de.SetByteValue ( s.c_str(), s.size() );
      ds.Insert( de );
      theQuery->SetSearchParameter(it->first, s);
      }

    ds.Print( std::cout );

    if( !portscp )
      {
      std::cerr << "Need to set explicitely port number for SCP association --port-scp" << std::endl;
      return 1;
      }

    CMove( hostname, port, callingaetitle, callaetitle, theQuery, portscpnum, outputdir );
    delete theQuery;
    }
  else if ( mode == "find" ) // C-FIND SCU
    {
    // Construct C-FIND DataSet:
    // ./bin/gdcmscu --find dhcp-67-183 5678
    // ./bin/gdcmscu --find mi2b2.slicer.org 11112  --aetitle ACME1 --call MI2B2
    // findscu -aec MI2B2 -P -k 0010,0010=F* mi2b2.slicer.org 11112 patqry.dcm

    // PATIENT query:
    // ./bin/gdcmscu --find mi2b2.slicer.org 11112  --aetitle ACME1 --call MI2B2 --key 8,52,PATIENT --key 10,10,"F*"
    gdcm::StringFilter sf;
    std::vector< std::pair<gdcm::Tag, std::string> >::const_iterator it =
      keys.begin();

    gdcm::network::BaseRootQuery* theQuery;
    if (findstudy > 0)
      {
      theQuery = new gdcm::network::StudyRootQuery();
      }
    else
      {
      theQuery = new gdcm::network::PatientRootQuery();
      }

    gdcm::DataSet ds;
    for(; it != keys.end(); ++it)
      {
      std::string s = sf.FromString( it->first, it->second.c_str(), it->second.size() );
      gdcm::DataElement de( it->first );
      de.SetByteValue ( s.c_str(), s.size() );
      ds.Insert( de );
      theQuery->SetSearchParameter(it->first, s);
      }

    ds.Print( std::cout );

    if (!theQuery->ValidateQuery())
      {
      std::cout << "You have not constructed a valid find query.  Please try again." << std::endl;
      delete theQuery;
      return 1;
      }//must ensure that 0x8,0x52 is set and that
    //the value in that tag corresponds to the query type
    CFind( hostname, port, callingaetitle, callaetitle, theQuery );
    delete theQuery;
    }
  else if ( mode == "test" ) // Test all images
    {
    // SHOULD USE A LOCAL SERVER!
    CTestAllFunctions( hostname, port, callingaetitle, callaetitle, testDir  );
    }
  else // C-STORE SCU
    {
    // mode == filename
    CStore( hostname, port, callingaetitle, callaetitle ,filename );
    }
  return 0;
}
