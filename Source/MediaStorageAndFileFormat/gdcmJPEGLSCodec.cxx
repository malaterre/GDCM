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
#include "gdcmJPEGLSCodec.h"
#include "gdcmTransferSyntax.h"
#include "gdcmDataElement.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmPNMCodec.h"

namespace gdcm
{

JPEGLSCodec::JPEGLSCodec():BufferLength(0)
{
}

JPEGLSCodec::~JPEGLSCodec()
{
}

bool JPEGLSCodec::CanDecode(TransferSyntax const &ts) const
{
  return ts == TransferSyntax::JPEGLSLossless 
    || ts == TransferSyntax::JPEGLSNearLossless;
}

bool JPEGLSCodec::CanCode(TransferSyntax const &ts) const
{
  // only a decoder for now
  return false;
//  return ts == TransferSyntax::JPEGLSLossless 
//    || ts == TransferSyntax::JPEGLSNearLossless;
}

bool JPEGLSCodec::Decode(DataElement const &in, DataElement &out)
{
  // First thing create a jpegls file from the fragment:
  //const gdcm::ByteValue *bv = in.GetByteValue();
  //assert( bv );
  const gdcm::SequenceOfFragments *sf = in.GetSequenceOfFragments();
  assert(sf);

  char *input  = tempnam(0, "gdcminjpegls");
  char *output = tempnam(0, "gdcmoutjpegls");

  std::ofstream outfile(input, std::ios::binary);
  sf->WriteBuffer(outfile);

  gdcm::Filename fn( System::GetCurrentProcessFileName() );
  std::string executable_path = fn.GetPath();
  std::string locod_command = executable_path + "/locod ";
  locod_command += "-i";
  locod_command += input; // no space !
  locod_command += " -o";
  locod_command += output; // no space !

  std::cerr << locod_command << std::endl;
  int ret = system(locod_command.c_str());

  PNMCodec pnm;
  pnm.SetBufferLength( GetBufferLength() );
  bool b = pnm.Read( output, out );

  free(input);
  free(output);

  return true;
}

// Compress into JPEG
bool JPEGLSCodec::Code(DataElement const &in, DataElement &out)
{
//  out = in;

  return true;
}

} // end namespace gdcm
