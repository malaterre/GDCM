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
#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmFile.h"
#include "gdcmTesting.h"
#include "gdcmMediaStorage.h"
#include "gdcmSystem.h"

struct element {
  const char *in;
  const char *inmd5;
  const char *outmd5;
  size_t outlen;
};

// non of the input file can be read by DCMTK
// output file was check against DCMTK on Aug 12 2010 (MM)
static const element list[] = {
    { "Enhanced_MR_Image_Storage_PixelSpacingNotIn_0028_0030.dcm",
    "854653ae806c224bfae3f196af250311",
    "e6d42da08e33e526dab4626864a1580e",
    26851994 },
    { "Siemens_CT_Sensation64_has_VR_RT.dcm",
    "3388c4f8e35cdb3d9512823f71e2415b",
    "cc57ee3ff427b859d3022071c8f1be95",
    526460 },
    { "ITK-GDCM-1.2.2.saysExplicitVR-butIsImplicitVR.dcm",
    "1158160333e00c0d1f8a7fdcbe352cac",
    "7fb2ef887fa29b9a793242b28d4e8258",
    199218 },
    { "MR_Philips_Intera_in_SQ_2001_e05f_item_wrong_lgt_use_NOSHADOWSEQ.dcm",
    "1158160333e00c0d1f8a7fdcbe352cac",
    "7fb2ef887fa29b9a793242b28d4e8258",
    199218 },
    { "MR_Philips_Intera_No_PrivateSequenceImplicitVR.dcm",
    "1158160333e00c0d1f8a7fdcbe352cac",
    "7fb2ef887fa29b9a793242b28d4e8258",
    199218 },
    { "MR_Philips_Intera_PrivateSequenceExplicitVR.dcm"
    "1158160333e00c0d1f8a7fdcbe352cac",
    "7fb2ef887fa29b9a793242b28d4e8258",
    199218 },
    { "MR_Philips_Intera_SwitchIndianess_noLgtSQItem_in_trueLgtSeq.dcm",
    "1158160333e00c0d1f8a7fdcbe352cac",
    "7fb2ef887fa29b9a793242b28d4e8258",
    199218 },
    { "illegal_UN_stands_for_SQ.dcm" // JPR ??
    "1158160333e00c0d1f8a7fdcbe352cac",
    "7fb2ef887fa29b9a793242b28d4e8258",
    199218 },
};

int TestInvalidDICOMFiles(int , char *[])
{
  int r = 0;
  const char *extradataroot = gdcm::Testing::GetDataExtraRoot();
  if( !extradataroot )
    {
    return 1;
    }
  if( !gdcm::System::FileIsDirectory(extradataroot) )
    {
    std::cerr << "No such directory: " << extradataroot <<  std::endl;
    return 1;
    }
  static const size_t n = sizeof( list ) / sizeof( element );
  for( size_t i = 0; i < n; ++i )
  {
  const &element = list[i];
  std::string sfilename = extradataroot;
  sfilename += "/gdcmSampleData/images_of_interest/";
  sfilename += element.in;

  // dcmdump --disable-cp246 ...
  const char *filename = sfilename.c_str();

  gdcm::Reader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    std::cerr << "TestReadError: Failed to read: " << filename << std::endl;
    return 1;
    }

  //const char *ref = gdcm::Testing::GetMediaStorageFromFile(filename);
  //std::cerr << "ref:" << ref << std::endl;
  char digest_str[33];
  bool b = gdcm::Testing::ComputeFileMD5(filename, digest_str);
  if( !b ) return 1;
  std::string md5ref = "854653ae806c224bfae3f196af250311";
  if( md5ref != digest_str )
    {
    std::cerr << "pb: " << md5ref << " vs " << digest_str << std::endl;
    ++r;
    }

  const char subdir[] = "TestCP246ExplicitDataElement";
  // Create directory first:
  std::string tmpdir = gdcm::Testing::GetTempDirectory( subdir );
  if( !gdcm::System::FileIsDirectory( tmpdir.c_str() ) )
    {
    gdcm::System::MakeDirectory( tmpdir.c_str() );
    }
  std::string outfilename = gdcm::Testing::GetTempFilename( filename, subdir );
  std::cout << "Corrected to: " << outfilename << std::endl;

  gdcm::Writer writer;
  writer.SetFileName( outfilename.c_str() );
  writer.SetFile( reader.GetFile() );
  writer.SetCheckFileMetaInformation( false );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    ++r;
    }

  char digest_str2[33];
  bool b2 = gdcm::Testing::ComputeFileMD5(outfilename.c_str(), digest_str2);
  if( !b2 ) return 1;
  std::string md5ref2 = "e6d42da08e33e526dab4626864a1580e";
  if( md5ref2 != digest_str2 )
    {
    std::cerr << "pb: " << md5ref2 << " vs " << digest_str2 << std::endl;
    ++r;
    }
  // paranoid:
  size_t s = gdcm::System::FileSize(outfilename.c_str());
  if ( s != 26851994 ) // identical in size !
    {
    ++r;
    }
    }

  return r;
}
