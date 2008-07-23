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
#include "gdcmImageChangeTransferSyntax.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmFragment.h"
#include "gdcmRAWCodec.h"
#include "gdcmJPEGCodec.h"
#include "gdcmJPEG2000Codec.h"
#include "gdcmRLECodec.h"

namespace gdcm
{

bool ImageChangeTransferSyntax::TryJPEGCodec()
{
  unsigned long len = Input->GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();

  JPEGCodec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( Input->GetDimensions() );
    codec.SetPlanarConfiguration( Input->GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( Input->GetPhotometricInterpretation() );
    codec.SetPixelFormat( Input->GetPixelFormat() );
    codec.SetNeedOverlayCleanup( Input->AreOverlaysInPixelData() );
    DataElement out;
    bool r = codec.Code(Input->GetDataElement(), out);
    // Create a Sequence Of Fragments:
    SmartPointer<SequenceOfFragments> sq = new SequenceOfFragments;
    const Tag itemStart(0xfffe, 0xe000);
    sq->GetTable().SetTag( itemStart );
    out.SetTag( itemStart );
    sq->AddFragment( (Fragment const&)out );
    unsigned int n = sq->GetNumberOfFragments();
    assert( sq->GetNumberOfFragments() == 1 );
    DataElement &de = Output->GetDataElement();
    de.SetValue( *sq );
    // PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm    
    if( !r )
      {
      return false;
      }
    // FIXME ! This should be done all the time for all codec:
    // Did PI change or not ?
    if ( Output->GetPhotometricInterpretation() != codec.GetPhotometricInterpretation() )
      {
      // HACK
      //gdcm::Image *i = (gdcm::Image*)this;
      //i->SetPhotometricInterpretation( codec.GetPhotometricInterpretation() );
      }
    return true;
    }
  return false;
}

bool ImageChangeTransferSyntax::TryJPEG2000Codec()
{
  unsigned long len = Input->GetBufferLength();
  const TransferSyntax &ts = GetTransferSyntax();

  JPEG2000Codec codec;
  if( codec.CanCode( ts ) )
    {
    codec.SetDimensions( Input->GetDimensions() );
    codec.SetPixelFormat( Input->GetPixelFormat() );
    codec.SetNumberOfDimensions( Input->GetNumberOfDimensions() );
    codec.SetPlanarConfiguration( Input->GetPlanarConfiguration() );
    codec.SetPhotometricInterpretation( Input->GetPhotometricInterpretation() );
    codec.SetNeedOverlayCleanup( Input->AreOverlaysInPixelData() );
    DataElement out;
    bool r = codec.Code(Input->GetDataElement(), out);
    // Create a Sequence Of Fragments:
    SmartPointer<SequenceOfFragments> sq = new SequenceOfFragments;
    const Tag itemStart(0xfffe, 0xe000);
    sq->GetTable().SetTag( itemStart );
    out.SetTag( itemStart );
    sq->AddFragment( (Fragment const&)out );
    unsigned int n = sq->GetNumberOfFragments();
    assert( sq->GetNumberOfFragments() == 1 );
    DataElement &de = Output->GetDataElement();
    de.SetValue( *sq );
    assert( r );
    return r;
    }
  return false;
}

bool ImageChangeTransferSyntax::Change()
{
  Output = Input;

  // Fast path
  if( Input->GetTransferSyntax() == TS ) return true;

  // FIXME
  // For now only support raw input, otherwise we would need to first decompress them
  if( Input->GetTransferSyntax() != TransferSyntax::ImplicitVRLittleEndian 
   && Input->GetTransferSyntax() != TransferSyntax::ExplicitVRLittleEndian
   && Input->GetTransferSyntax() != TransferSyntax::ExplicitVRBigEndian ) 
    {
    return false;
    }

  // too bad we actually have to do some work...
  bool success = false;
  //if( !success ) success = TryRAWCodec(buffer);
  if( !success ) success = TryJPEGCodec();
  if( !success ) success = TryJPEG2000Codec();
  //if( !success ) success = TryRLECodec(buffer);
  Output->SetTransferSyntax( TS );
  if( !success )
    {
    //abort();
    return false;
    }

  assert( Output->GetTransferSyntax() == TS );
  return success;
}


} // end namespace gdcm

