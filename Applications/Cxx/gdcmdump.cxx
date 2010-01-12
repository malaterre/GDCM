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
 * Simple command line tool to dump the layout/values of a DICOM file
 * This is largely inspired by other tools available from other toolkit, namely:
 * - dcdump (dicom3tools)
 * - dcmdump (dcmtk)
 * - dcmInfo (SIEMENS)
 * - PrintFile (GDCM 1.x)
 *
 * For now all layout are harcoded (see --color/--xml-dict for instance)
 *
 * gdcmdump has some feature not described in the DICOM standard:
 *   --csa : to print CSA information (dcmInfo.exe compatible)
 *   --pdb : to print PDB information (GEMS private info)
 *
 *
 * TODO: it would be nice to have custom printing, namely printing as HTML/XML
 *       it would be nice to have runtime dict (instead of compile time)
 */

#include "gdcmReader.h"
#include "gdcmVersion.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"
#include "gdcmPrivateTag.h"
#include "gdcmPrinter.h"
#include "gdcmDumper.h"
#include "gdcmDictPrinter.h"
#include "gdcmValidate.h"
#include "gdcmWriter.h"
#include "gdcmSystem.h"
#include "gdcmDirectory.h"
#include "gdcmCSAHeader.h"
#include "gdcmPDBHeader.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmASN1.h"

#include <string>
#include <iostream>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

int color = 0;

int ignoreerrors = 0;

template <typename TPrinter>
int DoOperation(const std::string & filename)
{
  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  bool success = reader.Read();
  if( !success && !ignoreerrors )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  TPrinter printer;
  printer.SetFile ( reader.GetFile() );
  printer.SetColor( color );
  printer.Print( std::cout );

  // Only return success when file read succeeded not depending whether or not we printed it
  return success ? 0 : 1;
}

int PrintASN1(const std::string & filename, bool verbose)
{
  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();
  gdcm::Tag tencryptedattributessequence(0x0400,0x0500);
  if( !ds.FindDataElement( tencryptedattributessequence ) )
    {
    return 1;
    }
  const gdcm::DataElement &encryptedattributessequence = ds.GetDataElement( tencryptedattributessequence );
  //const gdcm::SequenceOfItems * sqi = encryptedattributessequence.GetSequenceOfItems();
  gdcm::SmartPointer<gdcm::SequenceOfItems> sqi = encryptedattributessequence.GetValueAsSQ();
  if( !sqi->GetNumberOfItems() )
    {
    return 1;
    }
  const gdcm::Item &item1 = sqi->GetItem(1);
  const gdcm::DataSet &subds = item1.GetNestedDataSet();

  gdcm::Tag tencryptedcontent(0x0400,0x0520);
  if( !subds.FindDataElement( tencryptedcontent) )
    {
    return 1;
    }
  const gdcm::DataElement &encryptedcontent = subds.GetDataElement( tencryptedcontent );
  const gdcm::ByteValue *bv = encryptedcontent.GetByteValue();

  bool b = gdcm::ASN1::ParseDump( bv->GetPointer(), bv->GetLength() );
  if( !b ) return 1;
  return 0;
}

int PrintPDB(const std::string & filename, bool verbose)
{
  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  gdcm::PDBHeader pdb;
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();

  const gdcm::PrivateTag &t1 = pdb.GetPDBInfoTag();

  bool found = false;
  int ret = 0;
  if( ds.FindDataElement( t1 ) )
    {
    pdb.LoadFromDataElement( ds.GetDataElement( t1 ) );
    pdb.Print( std::cout );
    found = true;
    }
  if( !found )
    {
    std::cout << "no pdb tag found" << std::endl;
    ret = 1;
    }

  return ret;
}

int PrintCSA(const std::string & filename)
{
  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  if( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  gdcm::CSAHeader csa;
  const gdcm::DataSet& ds = reader.GetFile().GetDataSet();

  const gdcm::PrivateTag &t1 = csa.GetCSAImageHeaderInfoTag();
  const gdcm::PrivateTag &t2 = csa.GetCSASeriesHeaderInfoTag();
  const gdcm::PrivateTag &t3 = csa.GetCSADataInfo();

  bool found = false;
  int ret = 0;
  if( ds.FindDataElement( t1 ) )
    {
    csa.LoadFromDataElement( ds.GetDataElement( t1 ) );
    csa.Print( std::cout );
    found = true;
    if( csa.GetFormat() == gdcm::CSAHeader::ZEROED_OUT )
      {
      std::cout << "CSA Header has been zero-out (contains only 0)" << std::endl;
      ret = 1;
      }
    else if( csa.GetFormat() == gdcm::CSAHeader::DATASET_FORMAT )
      {
      gdcm::Printer p;
      gdcm::File f;
      f.SetDataSet( csa.GetDataSet() );
      p.SetFile( f );
      p.Print( std::cout );
      }
    }
  if( ds.FindDataElement( t2 ) )
    {
    csa.LoadFromDataElement( ds.GetDataElement( t2 ) );
    csa.Print( std::cout );
    found = true;
    if( csa.GetFormat() == gdcm::CSAHeader::ZEROED_OUT )
      {
      std::cout << "CSA Header has been zero-out (contains only 0)" << std::endl;
      ret = 1;
      }
    else if( csa.GetFormat() == gdcm::CSAHeader::DATASET_FORMAT )
      {
      gdcm::Printer p;
      gdcm::File f;
      f.SetDataSet( csa.GetDataSet() );
      p.SetFile( f );
      p.Print( std::cout );
      }
    }
  if( ds.FindDataElement( t3 ) )
    {
    csa.LoadFromDataElement( ds.GetDataElement( t3 ) );
    csa.Print( std::cout );
    found = true;
    if( csa.GetFormat() == gdcm::CSAHeader::ZEROED_OUT )
      {
      std::cout << "CSA Header has been zero-out (contains only 0)" << std::endl;
      ret = 1;
      }
    else if( csa.GetFormat() == gdcm::CSAHeader::INTERFILE )
      {
      const char *interfile = csa.GetInterfile();
      if( interfile ) std::cout << interfile << std::endl;
      }
    else if( csa.GetFormat() == gdcm::CSAHeader::DATASET_FORMAT )
      {
      gdcm::Printer p;
      gdcm::File f;
      f.SetDataSet( csa.GetDataSet() );
      p.SetFile( f );
      p.Print( std::cout );
      }
    }
  if( !found )
    {
    std::cout << "no csa tag found" << std::endl;
    ret = 1;
    }

  return ret;
}



void PrintVersion()
{
  std::cout << "gdcmdump: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmdump [OPTION]... FILE..." << std::endl;
  std::cout << "dumps a DICOM file, it will display the structure and values contained in the specified DICOM file\n";
  std::cout << "Parameter (required):" << std::endl;
  std::cout << "  -i --input     DICOM filename or directory" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -x --xml-dict       generate the XML dict (only private elements for now)." << std::endl;
  std::cout << "  -r --recursive      recursive." << std::endl;
  std::cout << "  -d --dump           dump value (limited use)." << std::endl;
  std::cout << "  -p --print          print value instead of simply dumping (default)." << std::endl;
  std::cout << "  -c --color          print in color." << std::endl;
  std::cout << "  -C --csa            print SIEMENS CSA Header (0029,[12]0,SIEMENS CSA HEADER)." << std::endl;
  std::cout << "  -P --pdb            print GEMS Protocol Data Block (0025,1b,GEMS_SERS_01)." << std::endl;
  std::cout << "  -A --asn1           print encapsulated ASN1 structure >(0400,0520)." << std::endl;
  std::cout << "     --map-uid-names  map UID to names." << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -V --verbose   more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning   print warning info." << std::endl;
  std::cout << "  -D --debug     print debug info." << std::endl;
  std::cout << "  -E --error     print error info." << std::endl;
  std::cout << "  -h --help      print help." << std::endl;
  std::cout << "  -v --version   print version." << std::endl;
  std::cout << "Special Options:" << std::endl;
  std::cout << "  -I --ignore-errors   print even if file is corrupted." << std::endl;
}


int main (int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::string filename;
  int printdict = 0;
  int dump = 0;
  int print = 0;
  int printcsa = 0;
  int printpdb = 0;
  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;
  int recursive = 0;
  int printasn1 = 0;
  int mapuidnames = 0;
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
        {"input", 1, 0, 0},
        {"xml-dict", 0, &printdict, 1},
        {"recursive", 0, &recursive, 1},
        {"print", 0, &print, 1},
        {"dump", 0, &dump, 1},
        {"color", 0, &color, 1},
        {"csa", 0, &printcsa, 1},
        {"pdb", 0, &printpdb, 1},
        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},
        {"ignore-errors", 0, &ignoreerrors, 1},
        {"asn1", 0, &printasn1, 1},
        {"map-uid-names", 0, &mapuidnames, 1},
        {0, 0, 0, 0} // required
    };
    static const char short_options[] = "i:xrpdcCPAVWDEhvI";
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

    case 'x':
      //printf ("option d with value '%s'\n", optarg);
      printdict = 1;
      break;

    case 'r':
      recursive = 1;
      break;

    case 'p':
      //printf ("option p with value '%s'\n", optarg);
      print = 1;
      break;

    case 'd':
      dump = 1;
      break;

    case 'c':
      color = 1;
      break;

    case 'C':
      printcsa = 1;
      break;

    case 'A':
      printasn1 = 1;
      break;

    case 'P':
      printpdb = 1;
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

    case 'I':
      ignoreerrors = 1;
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

  //
  //gdcm::System::SetArgv0( argv[0] );

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

  // check if d or p are passed, only one at a time
  if( print || printdict )
    {
    if ( print && printdict )
      {
      std::cerr << "d or p" << std::endl;
      return 1;
      }
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
   
  if( mapuidnames )
    {
    std::cerr << "Not handled for now" << std::endl;
    }

  // else
  int res = 0;
  if( !gdcm::System::FileExists(filename.c_str()) )
    {
    std::cerr << "no such file: " << filename << std::endl;
    return 1;
    }
  else if( gdcm::System::FileIsDirectory( filename.c_str() ) )
    {
    gdcm::Directory d;
    d.Load(filename, recursive);
    gdcm::Directory::FilenamesType const &filenames = d.GetFilenames();
    for( gdcm::Directory::FilenamesType::const_iterator it = filenames.begin(); it != filenames.end(); ++it )
      {
      if( printdict )
        {
        res += DoOperation<gdcm::DictPrinter>(*it);
        }
      else if( printasn1 )
        {
        res += PrintASN1(*it, verbose);
        }
      else if( printpdb )
        {
        res += PrintPDB(*it, verbose);
        }
      else if( printcsa )
        {
        res += PrintCSA(*it);
        }
      else if( dump )
        {
        res += DoOperation<gdcm::Dumper>(*it);
        }
      else
        {
        res += DoOperation<gdcm::Printer>(*it);
        }
      if( verbose ) std::cerr << *it << std::endl;
      }
    if( verbose ) std::cerr << "Total: " << filenames.size() << " files were processed" << std::endl;
    }
  else
    {
    assert( gdcm::System::FileExists(filename.c_str()) );
    if( printdict )
      {
      res += DoOperation<gdcm::DictPrinter>(filename);
      }
    else if( printasn1 )
      {
      res += PrintASN1(filename, verbose);
      }
    else if( printpdb )
      {
      res += PrintPDB(filename, verbose);
      }
    else if( printcsa )
      {
      res += PrintCSA(filename);
      }
    else if( dump )
      {
      res += DoOperation<gdcm::Dumper>(filename);
      }
    else
      {
      res += DoOperation<gdcm::Printer>(filename);
      }
    // ...
    if ( verbose )
      std::cerr << "Filename: " << filename << std::endl;
    }

  return res;
}

/*
 * Harvested data:
 * A lot of them are still non-obvious

Most obvious ones:
ETL -> Echo Train Length
FLIPANG -> Flip Angle
MATRIXX / MATRIXY ->  Acquisition Matrix
SLTHICK ->  Slice Thickness

   ENTRY "Feet First"
+  POSITION "Supine"
--------------------
=  Patient Position


Full list:
 
ANREF "IC"
ANREF "NA"
ANREF "SN"
AUTOCF "Water"
AUTOSCIC "0"
AUTOSCIC "2"
AUTOSHIM "Auto"
AUTOSHIM "Off"
AUTOSHIM "Yes"
AUTOSUBOPTIONS "0"
AUTOTRGTYPE "0"
AUTOTRIGWIN "0"
AUTOVOICE "0"
B4PAUSE "0"
BPMMODE "0"
BWRT "0"
BWRT "-1"
CLOC1 "0.0"
CLOC1 "L4.7"
CLOC1 "L5.9"
CLOC2 "0.0"
CLOC2 "P20.0"
CLOC2 "P42.2"
CLOC2 "P44.5"
CLOC3 "0.0"
CLOC3 "S7.0"
CLOC3 "S8.2"
COIL "5GP"
COIL "8HRBRAIN"
COIL "HEAD"
COIL "LOOP2CM"
CONTAG "GAD"
CONTAM "10    GAD"
CONTAM "No    "
CONTAM "Yes   "
CONTRAST "No"
CONTRAST "Yes"
DELACQ "Minimum"
DUMACQ "0"
ELOC1 "L12.4"
ELOC1 "L142.9"
ELOC1 "L1.6"
ELOC1 "L2.2"
ELOC1 "L4.9"
ELOC1 "L5.9"
ELOC1 "L80.1"
ELOC1 "L84.1"
ELOC1 "L99.3"
ELOC1 "S65.4"
ELOC1 "S66.5"
ELOC1 "S89.0"
ELOC2 "0.0"
ELOC2 "A18.3"
ELOC2 "A43.5"
ELOC2 "A79.2"
ELOC2 "A87.6"
ELOC2 "L6.9"
ELOC2 "P27.4"
ELOC2 "P38.8"
ELOC2 "P48.8"
ELOC2 "P49.4"
ELOC3 "A12.8"
ELOC3 "I111.9"
ELOC3 "I27.7"
ELOC3 "I7.1"
ELOC3 "P21.2"
ELOC3 "P31.1"
ELOC3 "S12.3"
ELOC3 "S1.7"
ELOC3 "S31.8"
ELOC3 "S5.4"
ELOC3 "S7.0"
ELOC3 "S9.8"
ENTRY "Head First"
ETL "17"
ETL "2"
ETL "24"
ETL "3"
ETL "6"
ETL "8"
ETL "9"
FILTCHOICE "None"
FLDIR "Slice"
FLIPANG "12"
FLIPANG "17"
FLIPANG "20"
FLIPANG "36"
FLIPANG "8"
FLIPANG "90"
FOV "12"
FOV "14"
FOV "24"
FOV "24.0"
FOV "3"
FOV "30"
FOV "4"
FOV "6"
FOV "8"
FOVCNT1 "0.0"
FOVCNT2 "0.0"
FOVCNT2 "P21.2"
FOVCNT2 "P31.1"
GRADMODE "WHOLE"
GRADMODE "ZOOM"
GRIP_NUMPSCVOL "0"
GRIP_NUMSLGROUPS "0"
GRIP_NUMSLGROUPS "1"
GRIP_PSCVOL1 "0"
GRIP_PSCVOL2 "0"
GRIP_PSCVOLFOV "0"
GRIP_PSCVOLFOV "0.000000"
GRIP_PSCVOLTHICK "0"
GRIP_PSCVOLTHICK "0.000000"
GRIP_SATGROUP1 "0"
GRIP_SATGROUP2 "0"
GRIP_SATGROUP3 "0"
GRIP_SATGROUP4 "0"
GRIP_SATGROUP5 "0"
GRIP_SATGROUP6 "0"
GRIP_SLGROUP1 "0.000000 -21.170785 -13.463666 0.000000 0.000000 1.000000 1.000000 0.000000 0.000000 0.000000 -1.000000 0.000000 1 0.000000 1 0"
GRIP_SLGROUP1 "0.000000 -31.122005 2.926577 0.000000 0.000000 1.000000 0.000000 1.000000 0.000000 1.000000 0.000000 0.000000 26 0.000000 1 0"
GRIP_SLGROUP1 "-13.163267 0.000000 25.592358 0.005670 0.000000 -0.999984 0.999984 0.000000 0.005670 0.000000 -1.000000 0.000000 56 0.000000 1 0 1"
GRIP_SLGROUP1 "3.135807 14.667716 -32.340976 -0.997518 0.043626 0.055276 -0.056814 -0.962372 -0.265728 0.041603 -0.268209 0.962462 1 0.000000 1 0 1"
GRIP_SPECTRO "0"
GRIP_TRACKER "0"
GRXOPT "0"
GRXOPT "2"
IEC_ACCEPT "ON"
IMODE "2D"
IMODE "3D"
INITSTATE "0"
IOPT "EDR, Fast, IrP"
IOPT "EPI, FMRI"
IOPT "Fast, IrP"
IOPT "Fast, ZIP512, FR"
IOPT "FC, EDR, TRF, Fast, ZIP512"
IOPT "FC, VBw, EDR"
IOPT "None"
IOPT "NPW, Seq, VBw, TRF, Fast"
IOPT "NPW, TRF, Fast, ZIP512, FR"
IOPT "NPW, VBw, EDR, Fast, ZIP2"
IOPT "NPW, VBw, Fast"
IOPT "NPW, ZIP512"
IOPT "TRF, Fast"
IOPT "VBw, EDR, Fast"
IOPT "VBw, Fast"
MASKPAUSE "0"
MASKPHASE "0"
MATRIXX "192"
MATRIXX "256"
MATRIXX "288"
MATRIXX "320"
MATRIXX "416"
MATRIXX "512"
MATRIXX "64"
MATRIXY "128"
MATRIXY "160"
MATRIXY "192"
MATRIXY "224"
MATRIXY "256"
MATRIXY "320"
MATRIXY "64"
MONSAR "y"
NECHO "1"
NEX "1.00"
NEX "1.50"
NEX "2.00"
NEX "3.00"
NEX "4.00"
NOSLC "1"
NOSLC "12"
NOSLC "15"
NOSLC "19"
NOSLC "20"
NOSLC "21"
NOSLC "24"
NOSLC "26"
NOSLC "56"
NOTES ".pn/_2"
NOTES ".pn/_3"
NOTES ".pn/_4"
NUMACCELFACTOR "1.00"
NUMACCELFACTOR "Recommended"
NUMACQS "0"
NUMACQS "2"
NUMSHOTS "1"
OVLPLOC "0"
PAUSEDELMASKACQ "1"
PDGMSTR "None"
PHASEASSET "1.00"
PHASECORR "No"
PHASECORR "Yes"
PHASEFOV "0.75"
PHASEFOV "1.00"
PLANE "3-PLANE"
PLANE "AXIAL"
PLANE "OBLIQUE"
PLUG "0"
PLUG "11"
PLUG "14"
PLUG "22"
PLUG "23"
PLUG "45"
PLUG "5"
PLUG "6"
PLUG "9"
POSITION "Prone"
POSITION "Supine"
PRESETDELAY "0.0"
PSDNAME "fse-xl"
PSDTRIG "0"
PSEQ "FRFSE-XL"
PSEQ "FSE-XL"
PSEQ "Gradient Echo"
PSEQ "IR"
PSEQ "Localizer"
PSEQ "SPGR"
PSEQ "Spin Echo"
RBW "12.50"
RBW "14.71"
RBW "15.63"
RBW "17.86"
RBW "20.83"
RBW "22.73"
RBW "25.00"
RBW "31.25"
SATLOCZ1 "9990"
SATLOCZ2 "9990"
SATTHICKZ1 "40.0"
SATTHICKZ2 "40.0"
SEDESC "3D FSPGR IR"
SEDESC "3DIR PREP"
SEDESC "3 plane loc"
SEDESC "AX FSE T1"
SEDESC "AX FSE T2"
SEDESC "AX T2*"
SEDESC "FATSAT T2 FSE Scout"
SEDESCFLAG "1"
SEDESC "LOCALIZER-RATCOIL"
SEDESC "O-Ax FATSAT T2 FSE high Res"
SEDESC "Oblique PD AX"
SEDESC "Oblique STIR"
SEDESC "Oblique T1 AX +C"
SEDESC "Oblique T1-SAG"
SEDESC "Oblique T1-SAG+C"
SEDESC "Oblique T2 AX."
SEDESC "O-Cor T1 "
SEDESC "RUN 1"
SEDESC "SPGR3D-HRES-Brasch"
SEDESC "SPGR3D-LRES-Brasch"
SEPSERIES "0"
SL3PLANE "0"
SL3PLANE "1"
SL3PLANE1 "0"
SL3PLANE1 "5"
SL3PLANE2 "0"
SL3PLANE2 "5"
SL3PLANE3 "0"
SL3PLANE3 "5"
SLABLOC "128"
SLABLOC "144"
SLABLOC "64"
SLABLOC "80"
SLICEASSET "1.00"
SLICEORDER "1"
SLOC1 "I35.2"
SLOC1 "I59.6"
SLOC1 "I93.4"
SLOC1 "L13.9"
SLOC1 "L1.6"
SLOC1 "L2.1"
SLOC1 "L5.0"
SLOC1 "L5.9"
SLOC1 "L84.1"
SLOC1 "L85.9"
SLOC1 "L99.2"
SLOC1 "R86.3"
SLOC2 "0.0"
SLOC2 "A11.0"
SLOC2 "A115.0"
SLOC2 "A79.2"
SLOC2 "A80.8"
SLOC2 "P34.4"
SLOC2 "P37.0"
SLOC2 "P46.5"
SLOC2 "P50.2"
SLOC3 "I27.8"
SLOC3 "I37.0"
SLOC3 "I7.1"
SLOC3 "S12.3"
SLOC3 "S163.1"
SLOC3 "S1.7"
SLOC3 "S5.4"
SLOC3 "S7.0"
SLPERLOC "274"
SLTHICK "0.2"
SLTHICK "0.7"
SLTHICK "1.2"
SLTHICK "1.3"
SLTHICK "3.0"
SLTHICK "4.0"
SLTHICK "5.0"
SLTHICK "5.5"
SPC "0.0"
SPC "1.5"
SPCPERPLANE1 "0.0"
SPCPERPLANE1 "1.5"
SPCPERPLANE2 "0.0"
SPCPERPLANE2 "1.5"
SPCPERPLANE3 "0.0"
SPCPERPLANE3 "1.5"
STATION "0"
SUPPTQ "1"
SWAPPF "A/P"
SWAPPF "R/L"
SWAPPF "S/I"
SWAPPF "Unswap"
TAG_SPACE "7"
TAG_TYPE "None"
TBLDELTA "0.00"
TE "100.0"
TE "102.0"
TE "15.0"
TE "30.0"
TE "50.0"
TE "Min Full"
TE "Minimum"
TI "150"
TI "450"
TI "500"
TOTALNOSTATION "0"
TR "2000.0"
TR "3000.0"
TR "4000.0"
TR "4125.0"
TR "4575.0"
TR "475.0"
TR "500.0"
TR "5200.0"
TR "525.0"
TR "5325.0"
TR "6600.0"
TRACKLEN "200.0"
TRACKTHICK "20.0"
TRACTIVE "0"
TRACTIVE "4"
TRICKSIMG "1"
TRREST "0"
TRREST "4"
USERCV0 "0.00"
USERCV0 "1.00"
USERCV21 "0.00"
USERCV23 "100.00"
USERCV4 "0.00"
USERCV6 "0.00"
USERCV7 "0.00"
USERCV_MASK "0"
USERCV_MASK "1"
USERCV_MASK "128"
USERCV_MASK "192"
USERCV_MASK "2097344"
USERCV_MASK "6144"
USERCV_MASK "64"
USERCV_MASK "8388688"
VIEWORDER "1"

*/
