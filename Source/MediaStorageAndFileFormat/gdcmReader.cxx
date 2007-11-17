/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmReader.h"
#include "gdcmTrace.h"
#include "gdcmVR.h"
#include "gdcmFileMetaInformation.h"
#include "gdcmSwapper.h"
#include "gdcmIOSerialize.txx"

namespace gdcm
{

Reader::~Reader()
{
  delete F;
#if 0
  if( Preamble )
    {
    delete[] Preamble;
    }
#endif
}

/// \brief tells us if "DICM" is found as position 128
///        (i.e. the file is a 'true dicom' one)
/// If not found then seek back at beginning of file (could be Mallinckrodt
/// or old ACRNEMA with no preamble)
/// \precondition we are at the beginning of file
/// \postcondition we are at the beginning of the DataSet or
/// Meta Information Header
bool Reader::ReadPreamble()
{
 return true;
}

/// \brief read the DICOM Meta Information Header
/// Find out the TransferSyntax used (default: Little Endian Explicit)
/// \precondition we are at the start of group 0x0002 (well after preamble)
/// \postcondition we are at the beginning of the DataSet
bool Reader::ReadMetaInformation()
{
#if 0
  if( !Header )
    {
    Header = new FileMetaInformation;
    }
  return Header->Read(Stream);
#endif
  return true;
}

bool Reader::ReadDataSet()
{
#if 0
  if( !DS )
    {
    TS ts (TS::TSType(0)); // = Header->GetTransferSyntaxType();
    //std::cerr << ts << std::endl;
    if( ts.GetNegociatedType() == TS::Explicit )
      {
      DS = new DataSet; //<ExplicitDataElement>;
      }
    else // default to instanciating an implicit one (old ACRNEMA...)
      {
      assert( ts.GetNegociatedType() == TS::Implicit
           || ts.GetNegociatedType() == TS::Unknown );
      DS = new DataSet; //<ImplicitDataElement>;
      }
    }
  //assert( Stream.GetSwapCode() != SwapCode::Unknown );
  return DS->Read(Stream);
#endif
  return true;
}

TransferSyntax Reader::GuessTransferSyntax()
{
  // Don't call this function if you have a meta file info
  //assert( Header->GetTransferSyntaxType() == TransferSyntax::TS_END );
  std::streampos start = Stream.tellg();
  SwapCode sc = SwapCode::Unknown;
  TransferSyntax::NegociatedType nts = TransferSyntax::Unknown;
  TransferSyntax ts (TransferSyntax::TS_END);
  Tag t;
  t.Read<SwapperNoOp>(Stream);
  if( ! (t.GetGroup() % 2) )
    {
    switch( t.GetGroup() )
      {
    case 0x0008:
      sc = SwapCode::LittleEndian;
      break;
    case 0x0800:
      sc = SwapCode::BigEndian;
      break;
    default:
      abort();
      }
    // Purposely not Re-use ReadVR since we can read VR_END
    char vr_str[3];
    Stream.read(vr_str, 2);
    vr_str[2] = '\0';
    // Cannot use GetVRTypeFromFile since is assert ...
    VR::VRType vr = VR::GetVRType(vr_str);
    if( vr != VR::VR_END )
      {
      nts = TransferSyntax::Explicit;
      }
    else
      {
      assert( !(VR::IsSwap(vr_str)));
      Stream.seekg(-2, std::ios::cur); // Seek back
      if( t.GetElement() == 0x0000 )
        {
        VL gl; // group length
        gl.Read<SwapperNoOp>(Stream);
        switch(gl)
          {
        case 0x00000004 :
          sc = SwapCode::LittleEndian;    // 1234
          break;
        case 0x04000000 :
          sc = SwapCode::BigEndian;       // 4321
          break;
        case 0x00040000 :
          sc = SwapCode::BadLittleEndian; // 3412
          gdcmWarningMacro( "Bad Little Endian" );
          break;
        case 0x00000400 :
          sc = SwapCode::BadBigEndian;    // 2143
          gdcmWarningMacro( "Bad Big Endian" );
          break;
        default:
          abort();
          }
        }
      nts = TransferSyntax::Implicit;
      }
    }
  else
    {
    gdcmWarningMacro( "Start with a private tag creator" );
    assert( t.GetGroup() > 0x0002 );
    switch( t.GetElement() )
      {
    case 0x0010:
      sc = SwapCode::LittleEndian;
      break;
    default:
      abort();
      }
    // Purposely not Re-use ReadVR since we can read VR_END
    char vr_str[3];
    Stream.read(vr_str, 2);
    vr_str[2] = '\0';
    // Cannot use GetVRTypeFromFile since is assert ...
    VR::VRType vr = VR::GetVRType(vr_str);
    if( vr != VR::VR_END )
      {
      nts = TransferSyntax::Explicit;
      }
    else
      {
      nts = TransferSyntax::Implicit;
      // We are reading a private creator (0x0010) so it's LO, it's
      // difficult to come up with someting to check, maybe that
      // VL < 256 ...
      gdcmWarningMacro( "Very dangerous assertion needs some work" );
      }
    }
  assert( nts != TransferSyntax::Unknown );
  assert( sc != SwapCode::Unknown );
  if( nts == TransferSyntax::Implicit )
    {
    if( sc == SwapCode::BigEndian )
      {
      ts = TransferSyntax::ImplicitVRBigEndianACRNEMA;
      }
    else if ( sc == SwapCode::LittleEndian )
      {
      ts = TransferSyntax::ImplicitVRLittleEndian;
      }
    else
      {
      abort();
      }
    }
  else
    {
    abort();
    }
  Stream.seekg( start, std::ios::beg );
  assert( ts != TransferSyntax::TS_END );
  return ts;
}

bool Reader::Read()
{
  if( !Stream.is_open() )
    {
    gdcmErrorMacro( "No File" );
    return false;
    }

  F = new File;
//  try
    {
    F->Read( Stream );
    assert( Stream.eof() );
    }
//  catch( std::exception &ex )
//    {
//    std::cerr << ex.what() << std::endl;
//    return false;
//    }

  // FIXME : call this function twice...
  Stream.close();

  return true;
}

} // end namespace gdcm
