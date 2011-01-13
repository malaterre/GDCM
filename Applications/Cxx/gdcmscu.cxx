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
#include "gdcmULConnection.h"
#include "gdcmDataSet.h"
#include "gdcmVersion.h"
#include "gdcmGlobal.h"
#include "gdcmSystem.h"
#include "gdcmUIDGenerator.h"
#include "gdcmStringFilter.h"
#include "gdcmWriter.h"
#include "gdcmPrinter.h"

//for testing!  Should be put in a testing executable,
//but it's just here now because I know this path works
#include "gdcmDirectory.h"
#include "gdcmImageReader.h"
#include "gdcmQueryFactory.h"
#include "gdcmStudyRootQuery.h"
#include "gdcmPatientRootQuery.h"
#include "gdcmULWritingCallback.h"

#include <fstream>
#include <socket++/echo.h>
#include <stdlib.h>
#include <getopt.h>




// Execute like this:
// ./bin/gdcmscu www.dicomserver.co.uk 11112 echo
int CEcho( const char *remote, int portno, std::string const &aetitle,
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
    return 1;
    }
  std::vector<gdcm::network::PresentationDataValue> theValues1 = theManager.SendEcho();

  //should print _something_ to let the user know of success, if they ask for something
  //other than a return code.
  if (gdcm::Trace::GetWarningFlag())
    {
      gdcm::DataSet ds = gdcm::network::PresentationDataValue::ConcatenatePDVBlobs(theValues1);
      gdcm::Printer thePrinter;
      thePrinter.PrintDataSet(ds, std::cout);
  //  std::vector<gdcm::network::PresentationDataValue>::iterator itor;
  //  for (itor = theValues1.begin(); itor < theValues1.end(); itor++)
  //    {
   //   itor->Print(std::cout);
   //   }
    }
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite

  // Check the Success Status
  gdcm::DataSet ds = gdcm::network::PresentationDataValue::ConcatenatePDVBlobs( theValues1 );
  gdcm::Attribute<0x0,0x0900> at;
  at.SetFromDataSet( ds );

  if( at.GetValue() != 0 )
    {
    return 1;
    }

  return 0;
}

//this function will take command line options and construct a cmove query from them
//returns NULL if the query could not be constructed.
//note that the caller is responsible for deleting the constructed query.
//used to build both a move and a find query (true for inMove if it's move, false if it's find)
gdcm::network::BaseRootQuery* ConstructQuery(bool inMove, bool findstudy, bool findpatient,
                                             const std::vector< std::pair<gdcm::Tag, std::string> >& keys)
{
  gdcm::StringFilter sf;
  std::vector< std::pair<gdcm::Tag, std::string> >::const_iterator it =
    keys.begin();
  gdcm::network::BaseRootQuery* outQuery = 0;
  if (findstudy)
    {
    //theQuery = new gdcm::network::StudyRootQuery();
    outQuery =
      gdcm::network::QueryFactory::ProduceQuery(
        gdcm::network::eStudyRootType, gdcm::network::eStudy);
    }
  else if (findpatient)
    {
    //theQuery = new gdcm::network::PatientRootQuery();
    outQuery =
      gdcm::network::QueryFactory::ProduceQuery(
        gdcm::network::ePatientRootType, gdcm::network::ePatient);

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
  std::vector<gdcm::network::ECharSet> inCharSetType;
  inCharSetType.push_back( gdcm::network::QueryFactory::GetCharacterFromCurrentLocale() );
  gdcm::DataElement de = gdcm::network::QueryFactory::ProduceCharacterSetDataElement(inCharSetType);
  std::string param ( de.GetByteValue()->GetPointer(),
    de.GetByteValue()->GetLength() );
  outQuery->SetSearchParameter(de.GetTag(), param );

  return outQuery;
}

//note that pointer to the base root query-- the caller must instantiated and delete
int CMove( const char *remote, int portno, std::string const &aetitle,
  std::string const &call, gdcm::network::BaseRootQuery* query,
  int portscp, std::string const & outputdir, bool inInterleaveWriting )
{
  // $ findscu -v  -d --aetitle ACME1 --call ACME_STORE  -P -k 0010,0010="X*" dhcp-67-183 5678  patqry.dcm
  // Add a query:

  if (outputdir.empty())
    {
      if (gdcm::Trace::GetErrorFlag())
        {
        std::cerr << "Output directory not specified." << std::endl;
        }
    return 1;
    }

  gdcm::network::ULConnectionManager theManager;
  if (!theManager.EstablishConnectionMove(aetitle, call, remote, 0, portno, 1000,
      portscp, query->GetQueryDataSet()))
    {
      if (gdcm::Trace::GetErrorFlag())
        {
        std::cerr << "Failed to establish connection." << std::endl;
        }
    return 1;
    }

  int ret = 0;
  if (!inInterleaveWriting)
    {
    std::vector<gdcm::DataSet> theDataSets  = theManager.SendMove( query );
    std::vector<gdcm::DataSet>::iterator itor;
    int c = 0;
    //write to the output directory
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
          if (gdcm::Trace::GetErrorFlag())
            {
            std::cerr << "Failed to write " << sopclassuid_str << std::endl;
            }
          ++ret;
          }
        }
      }
    }
  else 
    {
    gdcm::network::ULWritingCallback theCallback;
    theCallback.SetDirectory(outputdir);
    theManager.SendMove( query, &theCallback );
    }
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
  return ret;
}

//note that pointer to the base root query-- the caller must instantiated and delete
int CFind( const char *remote, int portno , std::string const &aetitle,
  std::string const &call , gdcm::network::BaseRootQuery* query )
{
  // $ findscu -v  -d --aetitle ACME1 --call ACME_STORE  -P -k 0010,0010="X*" dhcp-67-183 5678  patqry.dcm
  // Add a query:
  gdcm::network::ULConnectionManager theManager;
  //theManager.EstablishConnection("ACME1", "ACME_STORE", remote, 0, portno, 1000, gdcm::network::eFind, ds);
  if (!theManager.EstablishConnection(aetitle, call, remote, 0, portno, 1000, gdcm::network::eFind,  query->GetQueryDataSet())){

    if (gdcm::Trace::GetErrorFlag())
      {
      std::cerr << "Failed to establish connection." << std::endl;
      }
    return 1;
  }
  std::vector<gdcm::DataSet> theDataSets  = theManager.SendFind( query );
  std::vector<gdcm::DataSet>::iterator itor;
  int c = 0;
  if (gdcm::Trace::GetWarningFlag())
    {
    for (itor = theDataSets.begin(); itor < theDataSets.end(); itor++)
      {
        std::cout << "Message " << c++ << std::endl;
        itor->Print(std::cout);
      }
  }
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
  return 0;
}

int CStore( const char *remote, int portno,
  std::string const &aetitle,
  std::string const &call,
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
    if( !reader.Read() ) return 1;
    const gdcm::DataSet &ds = reader.GetFile().GetDataSet();
    theManager.SendStore( (gdcm::DataSet*)&ds );
    }

  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
  return 0;

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
  std::cout << "Mode Options:" << std::endl;
  std::cout << "     --echo           C-ECHO (default when none)." << std::endl;
  std::cout << "     --store          C-STORE." << std::endl;
  std::cout << "     --find           C-FIND." << std::endl;
  std::cout << "     --move           C-MOVE." << std::endl;
  std::cout << "C-STORE Options:" << std::endl;
  std::cout << "  -i --input          DICOM filename" << std::endl;
  std::cout << "  -r --recursive      recursively process (sub-)directories." << std::endl;
  std::cout << "     --store-query    Store constructed query in file." << std::endl;
  std::cout << "C-FIND Options:" << std::endl;
  //std::cout << "     --worklist       C-FIND Worklist Model." << std::endl;//!!not supported atm
  std::cout << "     --patient        C-FIND Patient Root Model." << std::endl;
  std::cout << "     --study          C-FIND Study Root Model." << std::endl;
  //std::cout << "     --psonly         C-FIND Patient/Study Only Model." << std::endl;
  std::cout << "     --key        0123,4567=VALUE for specifying search criteria (wildcard allowed)." << std::endl;
  std::cout << "C-MOVE Options:" << std::endl;
  std::cout << "  -o --output         DICOM output directory." << std::endl;
  std::cout << "     --port-scp       Port used for incoming association." << std::endl;
  std::cout << "     --key            0123,4567=VALUE for specifying search criteria (wildcard not allowed)." << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "     --root-uid               Root UID." << std::endl;
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
  gdcm::Directory::FilenamesType filenames;
  std::string outputdir;
  int storequery = 0;
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
  std::string queryfile;
  std::string root;
  int rootuid = 0;
  int recursive = 0;
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
        {"echo", 0, &echomode, 1}, // --echo
        {"store", 0, &storemode, 1}, // --store
        {"find", 0, &findmode, 1}, // --find
        {"move", 0, &movemode, 1}, // --move
        {"key", 1, 0, 0}, // (15) --key
        {"worklist", 0, &findworklist, 1}, // --worklist
        {"patient", 0, &findpatient, 1}, // --patient
        {"study", 0, &findstudy, 1}, // --study
        {"psonly", 0, &findpsonly, 1}, // --psonly
        {"port-scp", 1, &portscp, 1}, // (20) --port-scp
        {"output", 1, &outputopt, 1}, // --output
        {"recursive", 0, &recursive, 1},
        {"store-query", 1, &storequery, 1},
        {0, 0, 0, 0} // required
    };
    static const char short_options[] = "i:H:p:VWDEhvk:o:r";
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
          else if( option_index == 15 ) /* key */
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
            //ss >> str;
            std::getline(ss, str); // do not skip whitespace
            keys.push_back( std::make_pair(tag, str) );
            }
          else if( option_index == 20 ) /* port-scp */
            {
            assert( strcmp(s, "port-scp") == 0 );
            portscpnum = atoi(optarg);
            }
          else if( option_index == 21 ) /* output */
            {
            assert( strcmp(s, "output") == 0 );
            outputdir = optarg;
            }
          else if( option_index == 23 ) /* store-query */
            {
            assert( strcmp(s, "store-query") == 0 );
            queryfile = optarg;
            }
          else
            {
            // If you reach here someone mess-up the index and the argument in
            // the getopt table
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
        //ss >> str;
        std::getline(ss, str); // do not skip whitespace
        keys.push_back( std::make_pair(tag, str) );
        }
      break;

    case 'i':
      //printf ("option i with value '%s'\n", optarg);
      assert( filename.empty() );
      filename = optarg;
      break;

    case 'r':
      recursive = 1;
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
    else if( v >= 3 )
      {
      shostname = argv[optind++];
      port = atoi( argv[optind++] );
      //filename = argv[optind++];
      std::vector<std::string> files;
      while (optind < argc)
        {
        files.push_back( argv[optind++] );
        }
      filenames = files;
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

  bool theDebug = debug != 0;
  bool theWarning = warning != 0;
  bool theError = error != 0;
  bool theVerbose = verbose != 0;
  bool theRecursive = recursive != 0;
  // Debug is a little too verbose
  gdcm::Trace::SetDebug( theDebug );
  gdcm::Trace::SetWarning( theWarning );
  gdcm::Trace::SetError( theError );
  // when verbose is true, make sure warning+error are turned on:
  if( verbose )
    {
    gdcm::Trace::SetWarning( theVerbose );
    gdcm::Trace::SetError( theVerbose);
    }
  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( callaetitle.c_str() );
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
    int theReturnCode = CEcho( hostname, port, callingaetitle, callaetitle );
    if (theReturnCode != 0)
      {
      std::cout << "Echo failed." << std::endl;
      }
    else
      {
      std::cout << "Echo succeeded." << std::endl;
      }
    return theReturnCode;
    }
  else if ( mode == "move" ) // C-FIND SCU
    {
    // ./bin/gdcmscu --move --patient dhcp-67-183 5678 move
    // ./bin/gdcmscu --move --patient mi2b2.slicer.org 11112 move
    gdcm::network::BaseRootQuery* theQuery = ConstructQuery(true, findstudy != 0, findpatient != 0, keys);

    if( !portscp )
      {
      if (gdcm::Trace::GetErrorFlag())
        {
        std::cerr << "Need to set explicitely port number for SCP association --port-scp" << std::endl;      
        }
      std::cout << "Move failed." << std::endl;
      return 1;
      }


    if( storequery )
      {
      if (!theQuery->WriteQuery(queryfile))
        {
        std::cerr << "Could not write out query to: " << queryfile << std::endl;
        delete [] theQuery;
        return 1;
        }
      }

    if (!theQuery->ValidateQuery(true, false))
      {
      std::cerr << "You have not constructed a valid find query.  Please try again." << std::endl;
      delete theQuery;
      return 1;
      }//must ensure that 0x8,0x52 is set and that

    //!!! added the boolean to 'interleave writing', which basically writes each file out as it comes
    //across, rather than all at once at the end.  Turn off the boolean to have
    //it written all at once at the end.
    int ret = CMove( hostname, port, callingaetitle, callaetitle, theQuery, portscpnum, outputdir, true );
    delete theQuery;
    if (ret != 0)
      {
      std::cout << "Move failed." << std::endl;
      }
    else
      {
      std::cout << "Move succeeded." << std::endl;
      }
    return ret;
    }
  else if ( mode == "find" ) // C-FIND SCU
    {
    // Construct C-FIND DataSet:
    // ./bin/gdcmscu --find --patient dhcp-67-183 5678
    // ./bin/gdcmscu --find --patient mi2b2.slicer.org 11112  --aetitle ACME1 --call MI2B2
    // findscu -aec MI2B2 -P -k 0010,0010=F* mi2b2.slicer.org 11112 patqry.dcm

    // PATIENT query:
    // ./bin/gdcmscu --find --patient mi2b2.slicer.org 11112  --aetitle ACME1 --call MI2B2 --key 8,52,PATIENT --key 10,10="F*"
    gdcm::network::BaseRootQuery* theQuery = ConstructQuery(false, findstudy != 0, findpatient != 0, keys);

    if (!theQuery)
      {
        std::cerr << "Query construction failed." <<std::endl;
        return 1;
      }

    if( storequery )
      {
      if (!theQuery->WriteQuery(queryfile))
        {
        std::cerr << "Could not write out query to: " << queryfile << std::endl;
        delete [] theQuery;
        return 1;
        }
      }

    //doing a non-strict query, the second parameter there.
    //look at the base query comments
    if (!theQuery->ValidateQuery(true, false))
      {
      std::cerr << "You have not constructed a valid find query.  Please try again." << std::endl;
      delete theQuery;
      return 1;
      }//must ensure that 0x8,0x52 is set and that
    //the value in that tag corresponds to the query type
    int ret = CFind( hostname, port, callingaetitle, callaetitle, theQuery );
    delete theQuery;
    if (ret == 0)
      std::cout << "Find was successful." << std::endl;
    else
      std::cout << "Find failed." << std::endl;
    return ret;
    }
  else // C-STORE SCU
    {
    // mode == filename
    int ret = CStore( hostname, port, callingaetitle, callaetitle ,filenames, theRecursive );

    if (ret == 0)
      std::cout << "Store was successful." << std::endl;
    else
      std::cout << "Store failed." << std::endl;
    return ret;
    }
  return 0;
}
