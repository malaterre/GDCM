/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmFileChangeTransferSyntax.h"

#include "gdcmImageCodec.h"
#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmImageRegionReader.h"
#include "gdcmJPEGCodec.h"
#include "gdcmImageHelper.h"
#include "gdcmEvent.h"
#include "gdcmProgressEvent.h"

namespace gdcm
{

class FileChangeTransferSyntaxInternals
{
public:
  FileChangeTransferSyntaxInternals():
    IC(NULL),
    InitializeCopy(false)
  {}
  ~FileChangeTransferSyntaxInternals()
    {
    }
  ImageCodec *IC;
  bool InitializeCopy;
  std::streampos PixelDataPos;
  std::string InFilename;
  std::string OutFilename;
  TransferSyntax TS;
  JPEGCodec jpeg;
  std::vector<unsigned int> Dims;
  PixelFormat PF;
  PhotometricInterpretation PI;
  unsigned int PC;
  bool Needbyteswap;
  double Progress;
};

FileChangeTransferSyntax::FileChangeTransferSyntax()
{
  Internals = new FileChangeTransferSyntaxInternals;
}

FileChangeTransferSyntax::~FileChangeTransferSyntax()
{
  delete Internals;
}

bool FileChangeTransferSyntax::Change()
{
  this->InvokeEvent( StartEvent() );
  if( !InitializeCopy() )
    {
    gdcmDebugMacro( "Could not InitializeCopy" );
    return false;
    }

  const char *filename = this->Internals->InFilename.c_str();
  std::ifstream is( filename, std::ios::binary );
  is.seekg( Internals->PixelDataPos, std::ios::beg );
  const char *outfilename = this->Internals->OutFilename.c_str();
  std::fstream os( outfilename, std::ofstream::in | std::ofstream::out | std::ios::binary );
  os.seekp( 0, std::ios::end );

  const std::vector<unsigned int> & dims = Internals->Dims;
  const PixelFormat &pf = Internals->PF;
  const PhotometricInterpretation &pi = Internals->PI;
  unsigned int pc = Internals->PC;
  const int pixsize = pf.GetPixelSize();

  const bool needbyteswap = Internals->Needbyteswap;
  ImageCodec *codec = Internals->IC;
  codec->SetDimensions( dims );
  codec->SetNumberOfDimensions( 2 );
  codec->SetPlanarConfiguration( pc );
  codec->SetPhotometricInterpretation( pi );
  codec->SetNeedByteSwap( needbyteswap );
  codec->SetPixelFormat( pf ); // need to be last !

  std::vector<char> vbuffer;
  vbuffer.resize( dims[0] * pixsize );

  char *data = &vbuffer[0];
  const size_t datalen = vbuffer.size();

  VL vl;
  vl.SetToUndefined();
  DataElement de( Tag(0x7fe0,0x0010), vl, VR::OB );
  switch ( pf.GetBitsAllocated() )
    {
  case 8:
    de.SetVR( VR::OB );
    break;
    //case 12:
  case 16:
  case 32:
    de.SetVR( VR::OW );
    break;
  default:
    return false;
    }
  de.GetTag().Write<SwapperNoOp>( os );
  de.GetVR().Write( os );
  de.GetVL().Write<SwapperNoOp>( os );

  Fragment frag;
  // Basic Offset Table
  frag.Write<SwapperNoOp>( os );

  const size_t nscanlines = dims[2] * dims[1];
  const double progresstick = 1. / (double)nscanlines;
  Internals->Progress = 0;
  for( unsigned int z = 0; z < dims[2]; ++z )
    {
    // frag header:
    frag.Write<SwapperNoOp>( os );
    std::streampos start = os.tellp();
    for( unsigned int y = 0; y < dims[1]; ++y )
      {
      is.read( data, datalen );
      assert( is.good() );
      bool b = ((JPEGCodec*)Internals->IC)->EncodeBuffer(os, data, datalen);
      if( !b ) return false;
      Internals->Progress += progresstick;
      ProgressEvent pe;
      pe.SetProgress( Internals->Progress );
      this->InvokeEvent( pe );
      }
    const std::streampos end = os.tellp();

    // Compute JPEG length:
    const VL jpegvl = (uint32_t)(end - start);
    start -= 4;
    if( jpegvl.IsOdd() )
      {
      // 0 - padding:
      os.put( 0 );
      }
    os.seekp( start, std::ios::beg );
    jpegvl.Write<SwapperNoOp>( os );
    os.seekp( 0, std::ios::end );
    }

  const Tag seqDelItem(0xfffe,0xe0dd);
  seqDelItem.Write<SwapperNoOp>(os);
  VL zero = 0;
  zero.Write<SwapperNoOp>(os);

  is.close();
  os.close();

  this->InvokeEvent( EndEvent() );
  return true;
}

void FileChangeTransferSyntax::SetTransferSyntax( TransferSyntax const & ts )
{
  Internals->TS = ts;
  Internals->IC = &Internals->jpeg;
}

ImageCodec * FileChangeTransferSyntax::GetCodec()
{
  return Internals->IC;
}

void FileChangeTransferSyntax::SetInputFileName(const char *filename_native)
{
  if( filename_native )
    Internals->InFilename = filename_native;
}

void FileChangeTransferSyntax::SetOutputFileName(const char *filename_native)
{
  if( filename_native )
    Internals->OutFilename = filename_native;
}

bool FileChangeTransferSyntax::InitializeCopy()
{
  if( !Internals->IC )
    {
    return false;
    }
  if( !this->Internals->InitializeCopy )
    {
    const char *filename = this->Internals->InFilename.c_str();
    const char *outfilename = this->Internals->OutFilename.c_str();
      {
      // Make sure to update image meta data:
      std::ifstream is( filename, std::ios::binary );
      ImageRegionReader reader;
      reader.SetStream( is );
      if( !reader.ReadInformation() )
        {
        gdcmDebugMacro("ImageRegionReader::ReadInformation failed" );
        return false;
        }
      is.clear(); // important
      Internals->PixelDataPos = is.tellg();
      gdcm::File & file = reader.GetFile();
      const DataSet & ds = file.GetDataSet();
      if( ds.FindDataElement( Tag(0x7fe0,0x0010) ) )
        {
        const DataElement & de = ds.GetDataElement( Tag(0x7fe0,0x0010) );
        gdcmAssertAlwaysMacro( "Impossible happen"); (void)de;
        return false;
        }
      gdcm::FileMetaInformation & fmi = file.GetHeader();
      const TransferSyntax &ts = fmi.GetDataSetTransferSyntax();
      if( ts.IsEncapsulated() )
        {
        gdcmDebugMacro( "Dont know how to handle encapsulated TS: " << ts );
        return false;
        }
      if(ts == TransferSyntax::ImplicitVRBigEndianPrivateGE || ts == TransferSyntax::ExplicitVRBigEndian )
        {
        gdcmDebugMacro( "Dont know how to handle TS: " << ts );
        return false;
        }
      Internals->Needbyteswap = (ts == TransferSyntax::ImplicitVRBigEndianPrivateGE || ts == TransferSyntax::ExplicitVRBigEndian );
      Internals->Dims = ImageHelper::GetDimensionsValue(file);
      Internals->PF = ImageHelper::GetPixelFormatValue(file);
      Internals->PI = ImageHelper::GetPhotometricInterpretationValue(file);
      Internals->PC = ImageHelper::GetPlanarConfigurationValue(file);
      if( Internals->PC )
        {
        gdcmDebugMacro( "Dont know how to handle Planar Configuration" );
        return false;
        }
      is.close();

      Writer writer;
      fmi.Clear();
      fmi.SetDataSetTransferSyntax( Internals->TS );
      writer.SetFileName( outfilename );
      writer.SetFile( file );
      if( !writer.Write() ) return false;
      }
    this->Internals->InitializeCopy = true;
    }
  return true;
}

} // end namespace gdcm
