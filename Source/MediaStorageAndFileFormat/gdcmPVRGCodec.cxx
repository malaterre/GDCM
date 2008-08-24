/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmPVRGCodec.h"
#include "gdcmTransferSyntax.h"
#include "gdcmDataElement.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmPNMCodec.h"
#include "gdcmByteSwap.txx"

namespace gdcm
{

PVRGCodec::PVRGCodec()
{
  NeedByteSwap = true;
}

PVRGCodec::~PVRGCodec()
{
}

bool PVRGCodec::CanDecode(TransferSyntax const &ts) const
{
#ifndef GDCM_USE_PVRG
  return false;
#else
  return ts == TransferSyntax::JPEGBaselineProcess1
      || ts == TransferSyntax::JPEGExtendedProcess2_4
      || ts == TransferSyntax::JPEGExtendedProcess3_5
      || ts == TransferSyntax::JPEGSpectralSelectionProcess6_8
      || ts == TransferSyntax::JPEGFullProgressionProcess10_12
      || ts == TransferSyntax::JPEGLosslessProcess14
      || ts == TransferSyntax::JPEGLosslessProcess14_1;
#endif
}

bool PVRGCodec::CanCode(TransferSyntax const &ts) const
{
  return false;
}

/* PVRG command line is a bit tricky to use:
 *
 * ./bin/pvrgjpeg -d -s jpeg.jpg -ci 0 out.raw  
 *
 * means decompress input file: jpeg.jpg into out.raw
 * warning the -ci is important otherwise JFIF is assumed 
 * and comp # is assumed to be 1...
 */
bool PVRGCodec::Decode(DataElement const &in, DataElement &out)
{
#ifndef GDCM_USE_PVRG
  return false;
#else
  // First thing create a jpegls file from the fragment:
  const gdcm::SequenceOfFragments *sf = in.GetSequenceOfFragments();
  assert(sf);

  char *input  = tempnam(0, "gdcminpvrg");
  char *output = tempnam(0, "gdcmoutpvrg");
  if( !input || !output ) 
    {
    //free(input);
    //free(output);
    return false;
    }

  std::ofstream outfile(input, std::ios::binary);
  sf->WriteBuffer(outfile);
  outfile.close(); // flush !

  gdcm::Filename fn( System::GetCurrentProcessFileName() );
  std::string executable_path = fn.GetPath();
  // -u -> set Notify to 0 (less verbose)
  std::string pvrg_command = executable_path + "/gdcmjpeg -ci 0 -d -u ";
  // ./bin/pvrgjpeg -d -s jpeg.jpg -ci 0 out.raw  
  pvrg_command += "-s ";
  pvrg_command += input;
  pvrg_command += " ";
  pvrg_command += output;

  //std::cerr << pvrg_command << std::endl;
  gdcmDebugMacro( pvrg_command );
  int ret = system(pvrg_command.c_str());
  //std::cerr << "system: " << ret << std::endl;

  size_t len = gdcm::System::FileSize(output);
  assert( len );

  std::ifstream is(output);
  char * buf = new char[len];
  is.read(buf, len);
  out.SetTag( gdcm::Tag(0x7fe0,0x0010) );

  if ( PF.GetBitsAllocated() == 16 )
    {
    ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)
      buf,
#ifdef GDCM_WORDS_BIGENDIAN
      SwapCode::LittleEndian, 
#else
      SwapCode::BigEndian, 
#endif
      len/2);
    }
  out.SetByteValue( buf, len );
  delete[] buf;

  if( !System::RemoveFile(input) )
    {
    gdcmErrorMacro( "Could not delete input: " << input );
    }

  if( !System::RemoveFile(output) )
    {
    gdcmErrorMacro( "Could not delete output: " << output );
    }

  free(input);
  free(output);

  //return ImageCodec::Decode(in,out);
  return true;
#endif
}

// Compress into JPEG
bool PVRGCodec::Code(DataElement const &in, DataElement &out)
{
#ifndef GDCM_USE_PVRG
  return false;
#else
  /* Do I really want to produce JPEG by PRVRG ? Shouldn't IJG handle all cases nicely ? */
  return false;
#endif
}

} // end namespace gdcm
