/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 * HISTORY:
 * In GDCM 1.X the prefered terms was 'ReWrite', however one author of GDCM dislike
 * the term ReWrite since it is associated with the highly associated with the Rewrite
 * notion in software programming where using reinvent the wheel and rewrite from scratch code
 * the term convert was prefered
 *
 * Tools to conv. Goals being to 'purify' a DICOM file.
 * For now it will do the minimum:
 * - If Group Length is present, the length is garantee to be correct
 * - If Element with Group Tag 0x1, 0x3, 0x5 or 0x7 are present they are
 *   simply discarded (not written).
 * - Elements are written in alphabetical order
 * - 32bits VR have the residue bytes sets to 0x0,0x0
 * - Same goes from Item Length end delimitor, sets to 0x0,0x0
 * - All buggy files (wrong length: GE, 13 and Siemens Leonardo) are fixed
 * - All size are even (no odd length from gdcm 1.x)
 *
 * // \todo:
 * // --preamble: clean preamble
 * // --meta: clean meta (meta info version...)
 * // --dicomV3 (use TS unless not supported)
 * // --recompute group-length
 * // --undefined sq
 * // --explicit sq *
 * \todo in a close future:
 * - Set appropriate VR from DICOM dict
 * - Rewrite PMS SQ into DICOM SQ
 * - Rewrite Implicit SQ with defined length as undefined length
 * - PixelData with `overlay` in unused bits should be cleanup
 * - Any broken JPEG file (wrong bits) should be fixed
 * - DicomObject bug should be fixed
 * - Meta and Dataset should have a matching UID (more generally File Meta
 *   should be correct (Explicit!) and consistant with DataSet)
 * - User should be able to specify he wants Group Length (or remove them)
 * - Media SOP should be correct (deduct from something else or set to
 *   SOP Secondary if all else fail).
 * - Padding character should be correct
 *
 * \todo distant future:
 * - Later on, it should run through a Validator
 *   which will make sure all field 1, 1C are present and those only
 * - In a perfect world I should remove private tags and transform them into
 *   public fields.
 * - DA should be correct, PN should be correct (no space!)
 * - Enumerated Value should be correct
 */
/*
 check-meta is ideal for image like:

  make gdcmconv && ./bin/gdcmconv -i ~/Creatis/gdcmData/PICKER-16-MONO2-No_DicomV3_Preamble.dcm -o bla.dcm 
*/
#include "gdcmReader.h"
#include "gdcmVersion.h"
#include "gdcmImageReader.h"
#include "gdcmImageWriter.h"
#include "gdcmWriter.h"
#include "gdcmSystem.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmDataSet.h"
#include "gdcmAttribute.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmUIDGenerator.h"
#include "gdcmImageChangeTransferSyntax.h"
#include "gdcmImageApplyLookupTable.h"

#include <string>
#include <iostream>

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>
#include <string.h>

struct SetSQToUndefined
{
  void operator() (gdcm::DataElement &de) {
    de.SetVLToUndefined();
  }
};

void PrintVersion()
{
  std::cout << "gdcmconv: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmconv [OPTION] -i input.dcm -o output.dcm" << std::endl;
  std::cout << "Convert a DICOM file into another DICOM file.\n";
  std::cout << "Parameter (required):" << std::endl;
  std::cout << "  -i --input     DICOM filename" << std::endl;
  std::cout << "  -o --output    DICOM filename (generated)" << std::endl;
  std::cout << "Options:" << std::endl;
  //std::cout << "  -l --lut       Apply LUT." << std::endl;
  std::cout << "  -W --raw       Decompress image." << std::endl;
  std::cout << "  -J --jpeg      Compress image in jpeg." << std::endl;
  std::cout << "  -K --j2k       Compress image in j2k." << std::endl;
  std::cout << "  -L --jpegls    Compress image in jpeg-ls." << std::endl;
  std::cout << "  -R --rle       Compress image in rle." << std::endl;
  std::cout << "  -F --force     Force decompression before recompression." << std::endl;
  std::cout << "  -Y --lossy  %d Use the lossy (if possible), followed by comp. ratio" << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -V --verbose   more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning   print warning info." << std::endl;
  std::cout << "  -D --debug     print debug info." << std::endl;
  std::cout << "  -E --error     print error info." << std::endl;
  std::cout << "  -h --help      print help." << std::endl;
  std::cout << "  -v --version   print version." << std::endl;
}


int main (int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::string filename;
  std::string outfilename;
  std::string root;
  int lut = 0;
  int raw = 0;
  int rootuid = 0;
  int checkmeta = 0;
  int jpeg = 0;
  int jpegls = 0;
  int j2k = 0;
  int lossy = 0;
  int rle = 0;
  int force = 0;

  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;

  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"input", 1, 0, 0},
        {"output", 1, 0, 0},
        {"group-length", 1, 0, 0}, // valid / create / remove
        {"preamble", 1, 0, 0}, // valid / create / remove
        {"padding", 1, 0, 0}, // valid (\0 -> space) / optimize (at most 1 byte of padding)
        {"vr", 1, 0, 0}, // valid
        {"sop", 1, 0, 0}, // default to SC...
        {"iod", 1, 0, 0}, // valid
        {"meta", 1, 0, 0}, // valid / create / remove
        {"dataset", 1, 0, 0}, // valid / create / remove?
        {"sequence", 1, 0, 0}, // defined / undefined 
        {"deflate", 1, 0, 0}, // 1 - 9 / best = 9 / fast = 1
        {"tag", 1, 0, 0}, // need to specify a tag xxxx,yyyy = value to override default
        {"name", 1, 0, 0}, // same as tag but explicit use of name
        {"root-uid", 1, &rootuid, 1}, // specific Root (not GDCM)
        {"check-meta", 0, &checkmeta, 1}, // specific Root (not GDCM)
// Image specific options:
        {"pixeldata", 1, 0, 0}, // valid
        {"lut", 0, &lut, 1}, // default (implicit VR, LE) / Explicit LE / Explicit BE
        {"raw", 0, &raw, 1}, // default (implicit VR, LE) / Explicit LE / Explicit BE
        {"lossy", 1, &lossy, 1}, // Specify the compression ratio for lossy comp
        {"force", 0, &force, 1}, // force decompression even if target compression is identical
        {"jpeg", 0, &jpeg, 1}, // JPEG lossy / lossless
        {"jpegls", 0, &jpegls, 1}, // JPEG-LS: lossy / lossless
        {"j2k", 0, &j2k, 1}, // J2K: lossy / lossless
        {"rle", 0, &rle, 1}, // lossless !
        {"mpeg2", 0, 0, 0}, // lossy !
        {"jpip", 0, 0, 0}, // ??

// General options !
        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},

        {0, 0, 0, 0}
    };

    c = getopt_long (argc, argv, "i:o:",
      long_options, &option_index);
    if (c == -1)
      {
      break;
      }

    switch (c)
      {
    case 0:
        {
        const char *s = long_options[option_index].name;
        printf ("option %s", s);
        if (optarg)
          {
          if( option_index == 0 ) /* input */
            {
            assert( strcmp(s, "input") == 0 );
            assert( filename.empty() );
            filename = optarg;
            }
          else if( option_index == 14 ) /* root-uid */
            {
            assert( strcmp(s, "root-uid") == 0 );
            assert( root.empty() );
            root = optarg;
            }
          printf (" with arg %s, index = %d", optarg, option_index);
          }
        printf ("\n");
        }
      break;

    case 'i':
      printf ("option i with value '%s'\n", optarg);
      assert( filename.empty() );
      filename = optarg;
      break;

    case 'o':
      printf ("option o with value '%s'\n", optarg);
      assert( outfilename.empty() );
      outfilename = optarg;
      break;

    case '?':
      break;

    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
      }
  }

  // For now only support one input / one output
  if (optind < argc)
    {
    //printf ("non-option ARGV-elements: ");
    //while (optind < argc)
    //  {
    //  printf ("%s ", argv[optind++]);
    //  }
    //printf ("\n");
    return 1;
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
  if( outfilename.empty() )
    {
    //std::cerr << "Need output file (-o)\n";
    PrintHelp();
    return 1;
    }
  
  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle( "gdcmconv" );
  if( rootuid )
    {
    if( !gdcm::UIDGenerator::IsValid( root.c_str() ) )
      {
      std::cerr << "specified Root UID is not valid: " << root << std::endl;
      return 1;
      }
    gdcm::UIDGenerator::SetRoot( root.c_str() );
    }

  if( lossy )
    {
    std::cerr << "not supported for now" << std::endl;
    return 1;
    }

  if( lut )
    {
    gdcm::ImageReader reader;
    reader.SetFileName( filename.c_str() );
    if( !reader.Read() )
      {
      std::cerr << "could not read: " << filename << std::endl;
      return 1;
      }
    const gdcm::Image &image = reader.GetImage();

    gdcm::ImageApplyLookupTable lutfilt;
    lutfilt.SetInput( image );
    bool b = lutfilt.Apply();
    if( !b )
      {
      std::cerr << "Could not apply LUT: " << filename << std::endl;
      return 1;
      }
    gdcm::ImageWriter writer;
    writer.SetFileName( outfilename.c_str() );
    writer.SetFile( reader.GetFile() );
    writer.SetImage( lutfilt.GetOutput() );
    if( !writer.Write() )
      {
      std::cerr << "Failed to write: " << outfilename << std::endl;
      return 1;
      }
    }
  else if( jpeg || j2k || jpegls || rle || raw )
    {
    gdcm::ImageReader reader;
    reader.SetFileName( filename.c_str() );
    if( !reader.Read() )
      {
      std::cerr << "could not read: " << filename << std::endl;
      return 1;
      }
    const gdcm::Image &image = reader.GetImage();

    gdcm::ImageChangeTransferSyntax change;
    change.SetForce( force );
    if( jpeg )
      {
      change.SetTransferSyntax( gdcm::TransferSyntax::JPEGLosslessProcess14_1 );
      }
    else if( jpegls )
      {
      change.SetTransferSyntax( gdcm::TransferSyntax::JPEGLSLossless );
      }
    else if( j2k )
      {
      change.SetTransferSyntax( gdcm::TransferSyntax::JPEG2000Lossless );
      }
    else if( raw )
      {
      change.SetTransferSyntax( gdcm::TransferSyntax::ExplicitVRLittleEndian );
      }
    else if( rle )
      {
      change.SetTransferSyntax( gdcm::TransferSyntax::RLELossless );
      }
    else
      {
      return 1;
      }
    change.SetInput( image );
    bool b = change.Change();
    if( !b )
      {
      std::cerr << "Could not change the Transfer Syntax: " << filename << std::endl;
      return 1;
      }
    gdcm::ImageWriter writer;
    writer.SetFileName( outfilename.c_str() );
    writer.SetFile( reader.GetFile() );
    writer.SetImage( change.GetOutput() );
    if( !writer.Write() )
      {
      std::cerr << "Failed to write: " << outfilename << std::endl;
      return 1;
      }

    }
  else if( raw && false )
    {
    gdcm::ImageReader reader;
    reader.SetFileName( filename.c_str() );
    if( !reader.Read() )
      {
      std::cerr << "could not read: " << filename << std::endl;
      return 1;
      }

    const gdcm::Image &ir = reader.GetImage();

    gdcm::Image image( ir );
    const gdcm::TransferSyntax &ts = ir.GetTransferSyntax();
    if( ts.IsExplicit() )
      {
      image.SetTransferSyntax( gdcm::TransferSyntax::ExplicitVRLittleEndian );
      }
    else
      {
      assert( ts.IsImplicit() );
      image.SetTransferSyntax( gdcm::TransferSyntax::ImplicitVRLittleEndian );
      }

/*
    image.SetNumberOfDimensions( ir.GetNumberOfDimensions() );

    const unsigned int *dims = ir.GetDimensions();
    image.SetDimension(0, dims[0] );
    image.SetDimension(1, dims[1] );

    const gdcm::PixelFormat &pixeltype = ir.GetPixelFormat();
    image.SetPixelFormat( pixeltype );

    const gdcm::PhotometricInterpretation &pi = ir.GetPhotometricInterpretation();
    image.SetPhotometricInterpretation( pi );
*/

    unsigned long len = ir.GetBufferLength();
    //assert( len = ir.GetBufferLength() );
    std::vector<char> buffer;
    buffer.resize(len); // black image

    ir.GetBuffer( &buffer[0] );
    gdcm::ByteValue *bv = new gdcm::ByteValue(buffer);
    gdcm::DataElement pixeldata( gdcm::Tag(0x7fe0,0x0010) );
    pixeldata.SetValue( *bv );
    image.SetDataElement( pixeldata );

    gdcm::ImageWriter writer;
    writer.SetFile( reader.GetFile() );
    writer.SetImage( image );
    writer.SetFileName( outfilename.c_str() );

    gdcm::File& file = writer.GetFile();
    gdcm::DataSet& ds = file.GetDataSet();

    if( !writer.Write() )
      {
      std::cerr << "could not write: " << outfilename << std::endl;
      return 1;
      }
    }
  else
    {
    gdcm::Reader reader;
    reader.SetFileName( filename.c_str() );
    if( !reader.Read() )
      {
      std::cerr << "Failed to read: " << filename << std::endl;
      return 1;
      }

#if 0
    // if preamble create:
    gdcm::File f(reader.GetFile());
    gdcm::Preamble p;
    p.Create();
    f.SetPreamble(p);
    gdcm::DataSet ds = reader.GetFile().GetDataSet();
    SetSQToUndefined undef;
    ds.ExecuteOperation(undef);

    gdcm::File f(reader.GetFile());
    f.SetDataSet(ds);
#endif

    gdcm::DataSet& ds = reader.GetFile().GetDataSet();
#if 0
    gdcm::DataElement de = ds.GetDataElement( gdcm::Tag(0x0010,0x0010) );
    const char patname[] = "John^Doe";
    de.SetByteValue(patname, strlen(patname));
    std::cout << de << std::endl;

    ds.Replace( de );
    std::cout << ds.GetDataElement( gdcm::Tag(0x0010,0x0010) ) << std::endl;
#endif

    /*
    //(0020,0032) DS [-158.135803\-179.035797\-75.699997]     #  34, 3 ImagePositionPatient
    //(0020,0037) DS [1.000000\0.000000\0.000000\0.000000\1.000000\0.000000] #  54, 6 ImageOrientationPatient
    gdcm::Attribute<0x0020,0x0032> at = { -158.135803, -179.035797, -75.699997 };
    gdcm::DataElement ipp = at.GetAsDataElement();
    ds.Remove( at.GetTag() );
    ds.Remove( ipp.GetTag() );
    ds.Replace( ipp );
     */

    gdcm::Writer writer;
    writer.SetFileName( outfilename.c_str() );
    writer.SetCheckFileMetaInformation( checkmeta );
    //writer.SetFile( f );
    writer.SetFile( reader.GetFile() );
    if( !writer.Write() )
      {
      std::cerr << "Failed to write: " << outfilename << std::endl;
      // remove file to avoid any temptation
      if( filename != outfilename )
        {
        gdcm::System::RemoveFile( outfilename.c_str() );
        }
      else
        {
        std::cerr << "gdcmconv just corrupted: " << filename << " for you (data lost)." << std::endl;
        }
      return 1;
      }
    }

  return 0;
}

