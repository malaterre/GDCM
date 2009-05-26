/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 * Implementation of General Purpose CD-R Interchange / STD-GEN-CD DICOMDIR in GDCM 
 */
#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmScanner.h"
#include "gdcmVersion.h"
#include "gdcmSystem.h"
#include "gdcmUIDGenerator.h"
#include "gdcmAnonymizer.h"
#include "gdcmGlobal.h"
#include "gdcmDefs.h"
#include "gdcmDirectory.h"

#include "gdcmSequenceOfItems.h"
#include "gdcmTag.h"
#include "gdcmVR.h"

#include <getopt.h>


void PrintVersion()
{
  std::cout << "gdcmgendir: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmgendir [OPTION]... FILE..." << std::endl;
  std::cout << "create DICOMDIR" << std::endl;
  std::cout << "Parameter:" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -i --input     DICOM filename or directory" << std::endl;
  std::cout << "  -o --output    DICOM filename or directory" << std::endl;
  std::cout << "  -r --recursive          recursive." << std::endl;
  std::cout << "     --root-uid               Root UID." << std::endl;
  std::cout << "     --resources-path         Resources path." << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -V --verbose   more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning   print warning info." << std::endl;
  std::cout << "  -D --debug     print debug info." << std::endl;
  std::cout << "  -E --error     print error info." << std::endl;
  std::cout << "  -h --help      print help." << std::endl;
  std::cout << "  -v --version   print version." << std::endl;
  std::cout << "Env var:" << std::endl;
  std::cout << "  GDCM_ROOT_UID Root UID" << std::endl;
  std::cout << "  GDCM_RESOURCES_PATH path pointing to resources files (Part3.xml, ...)" << std::endl;
}

/*
  (fffe,e000) na "Directory Record" IMAGE #=13            # u/l, 1 Item
  #  offset=$1398  refFileID="IMAGES\DXIMAGE"
    (0004,1400) up 0                                        #   4, 1 OffsetOfTheNextDirectoryRecord
    (0004,1410) US 65535                                    #   2, 1 RecordInUseFlag
    (0004,1420) up 0                                        #   4, 1 OffsetOfReferencedLowerLevelDirectoryEntity
    (0004,1430) CS [IMAGE]                                  #   6, 1 DirectoryRecordType
    (0004,1500) CS [IMAGES\DXIMAGE]                         #  14, 2 ReferencedFileID
    (0004,1510) UI =DigitalXRayImageStorageForPresentation  #  28, 1 ReferencedSOPClassUIDInFile
    (0004,1511) UI [1.3.6.1.4.1.5962.1.1.65535.3.1.1119624143.7180.0] #  48, 1 ReferencedSOPInstanceUIDInFile
    (0004,1512) UI =LittleEndianExplicit                    #  20, 1 ReferencedTransferSyntaxUIDInFile
    (0008,0008) CS [ORIGINAL\PRIMARY]                       #  16, 2 ImageType
    (0020,0013) IS [1]                                      #   2, 1 InstanceNumber
    (0028,0004) CS [MONOCHROME2]                            #  12, 1 PhotometricInterpretation
    (0028,0008) IS [1]                                      #   2, 1 NumberOfFrames
    (0050,0004) CS (no value available)                     #   0, 0 CalibrationImage
  (fffe,e00d) na "ItemDelimitationItem"                   #   0, 0 ItemDelimitationItem
*/
using gdcm::Tag;
using gdcm::VR;
using gdcm::SequenceOfItems;
using gdcm::DataSet;
using gdcm::DataElement;
using gdcm::Item;

bool AddImageDirectoryRecord(gdcm::DataSet &ds, gdcm::Scanner const & scanner)
{
  const gdcm::DataElement &de = ds.GetDataElement( Tag(0x4,0x1220) );
  SequenceOfItems * sqi;
  sqi = (SequenceOfItems*)de.GetSequenceOfItems();

  Item item1; //( Tag(0xfffe,0xe000) );
  item1.SetVLToUndefined();
  sqi->AddItem( item1 );

  Item &item = sqi->GetItem(1);
  DataSet &subds = item.GetNestedDataSet();

  DataElement sopinstanceuid( Tag(0x0008,0x008) );
  sopinstanceuid.SetByteValue( "toto", 4 );
  subds.Replace( sopinstanceuid );

  return true;
}

int main(int argc, char *argv[])
{
  int c;
  std::string filename;
  gdcm::Directory::FilenamesType filenames;
  std::string xmlpath;
  int verbose = 0;
  int warning = 0;
  int help = 0;
  int recursive = 0;
  int version = 0;
  int debug = 0;
  int error = 0;
  int resourcespath = 0;
  int rootuid = 0;
  while (1) {
    int option_index = 0;
    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},                // o
        {"recursive", 0, &recursive, 1},
        {"root-uid", 1, &rootuid, 1}, // specific Root (not GDCM)
        {"resources-path", 1, &resourcespath, 1},

        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},
        {0, 0, 0, 0} // required
    };
    static const char short_options[] = "i:rVWDEhv";
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
          else if( option_index == 3 ) /* resources-path */
            {
            assert( strcmp(s, "resources-path") == 0 );
            assert( xmlpath.empty() );
            xmlpath = optarg;
            }
          //printf (" with arg %s", optarg);
          }
        //printf ("\n");
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
    //printf ("non-option ARGV-elements: %d", optind );
    //while (optind < argc)
    //  {
    //  printf ("%s\n", argv[optind++]);
    //  }
    //printf ("\n");
    // Ok there is only one arg, easy, it's the filename:
    int v = argc - optind;
    if( v == 1 )
      {
      filename = argv[optind];
      }
    }

  if( version )
    {
    //std::cout << "version" << std::endl;
    PrintVersion();
    return 0;
    }

  if( help )
    {
    //std::cout << "help" << std::endl;
    PrintHelp();
    return 0;
    }

  if( filename.empty() )
    {
    //std::cerr << "Need input file (-i)\n";
    PrintHelp();
    return 1;
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

  if( !gdcm::System::FileExists(filename.c_str()) )
    {
    return 1;
    }

/*
  gdcm::Global& g = gdcm::Global::GetInstance();
  // First thing we need to locate the XML dict
  // did the user requested to look XML file in a particular directory ?
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
      std::cerr << "specified Resources Path is not valid: " << xmlpath << std::endl;
      return 1;
      }
    }

  // All set, then load the XML files:
  if( !g.LoadResourcesFiles() )
    {
    return 1;
    }

  const gdcm::Defs &defs = g.GetDefs();
*/

  int res = 0;
  unsigned int nfiles = 1;
  if( gdcm::System::FileIsDirectory(filename.c_str()) )
    {
    gdcm::Directory dir;
    nfiles = dir.Load(filename, recursive);
    filenames = dir.GetFilenames();
    }
  else
    {
    filenames.push_back( filename );
    }
  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( "gdcmgendir" );

  gdcm::Scanner scanner;
  // 
  scanner.AddTag( Tag(0x8,0x8) );
  scanner.AddTag( Tag(0x20,0x13) );
  scanner.AddTag( Tag(0x28,0x4) );
  scanner.AddTag( Tag(0x28,0x8) );
  scanner.AddTag( Tag(0x50,0x4) );

  if( !scanner.Scan( filenames ) )
    {
    return false;
    }

  scanner.Print( std::cout );

  // (0004,1220) SQ (Sequence with undefined length #=8)     # u/l, 1 DirectoryRecordSequence

  gdcm::Writer writer;
  gdcm::DataSet &ds = writer.GetFile().GetDataSet();
  gdcm::DataElement de( Tag(0x4,0x1220) );

  SequenceOfItems * sqi = new SequenceOfItems;
  //DataElement de( sisq );
  de.SetVR( VR::SQ );
  de.SetValue( *sqi );
  de.SetVLToUndefined();

  ds.Insert( de );

  bool b = AddImageDirectoryRecord(ds, scanner);

  writer.GetFile().GetHeader();

  std::cout << ds << std::endl;

  writer.SetFileName( "debug.DICOMDIR" );
  if( !writer.Write() )
    {
    return 1;
    }

  return res;
}

