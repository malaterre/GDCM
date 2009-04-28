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
#include "gdcmRAWCodec.h"
#include "gdcmTransferSyntax.h"
#include "gdcmByteSwap.txx"
#include "gdcmDataElement.h"
#include "gdcmSequenceOfFragments.h"

#include <sstream>

namespace gdcm
{

class RAWInternals
{
public:
};

RAWCodec::RAWCodec()
{
  Internals = new RAWInternals;
}

RAWCodec::~RAWCodec()
{
  delete Internals;
}

bool RAWCodec::CanCode(TransferSyntax const &ts) const
{
  return ts == TransferSyntax::ImplicitVRLittleEndian
   || ts == TransferSyntax::ExplicitVRLittleEndian
   || ts == TransferSyntax::ExplicitVRBigEndian
   || ts == TransferSyntax::ImplicitVRBigEndianPrivateGE
   || ts == TransferSyntax::DeflatedExplicitVRLittleEndian;
}

bool RAWCodec::CanDecode(TransferSyntax const &ts) const
{
  return ts == TransferSyntax::ImplicitVRLittleEndian
   || ts == TransferSyntax::ExplicitVRLittleEndian
   || ts == TransferSyntax::ExplicitVRBigEndian
   || ts == TransferSyntax::ImplicitVRBigEndianPrivateGE
   || ts == TransferSyntax::DeflatedExplicitVRLittleEndian;
}

bool RAWCodec::Code(DataElement const &in, DataElement &out)
{
  out = in;
  //abort();
  return true;
}

bool RAWCodec::Decode(DataElement const &in, DataElement &out)
{
  // First let's see if we can do a fast-path:
  if( !NeedByteSwap &&
    !RequestPaddedCompositePixelCode &&
    PI == PhotometricInterpretation::MONOCHROME2 &&
    !PlanarConfiguration && !RequestPlanarConfiguration &&
    !NeedOverlayCleanup )
    {
    out = in;
    return true;
    }
  // else
  const ByteValue *bv = in.GetByteValue();
  assert( bv );
  std::stringstream is;
  is.write(bv->GetPointer(), bv->GetLength());
  std::stringstream os;
  bool r = Decode(is, os);
  if(!r) return false;
  assert( r );

  std::string str = os.str();
  std::string::size_type check = str.size();

  out = in;
  out.SetByteValue( &str[0], str.size() );
  return r;
}

bool RAWCodec::Decode(std::istream &is, std::ostream &os)
{
  bool r = ImageCodec::Decode(is, os);
  return r;
}

bool RAWCodec::GetHeaderInfo(std::istream &is, TransferSyntax &ts)
{
  ts = gdcm::TransferSyntax::ExplicitVRLittleEndian;
  if( NeedByteSwap )
    {
    ts = gdcm::TransferSyntax::ImplicitVRBigEndianPrivateGE;
    }
  return true;
}

} // end namespace gdcm
