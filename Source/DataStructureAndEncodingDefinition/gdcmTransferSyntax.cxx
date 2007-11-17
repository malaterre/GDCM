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
#include "gdcmTransferSyntax.h"
#include "gdcmTrace.h"

#include <assert.h>
#include <string.h>

#include <string>
#include <iostream>

namespace gdcm
{

static const char *TSStrings[] = {
    // Implicit VR Little Endian
  "1.2.840.10008.1.2",
  // Implicit VR Big Endian DLX (G.E Private)
  "1.2.840.113619.5.2",
  // Explicit VR Little Endian
  "1.2.840.10008.1.2.1",
  // Deflated Explicit VR Little Endian
  "1.2.840.10008.1.2.1.99",
  // Explicit VR Big Endian
  "1.2.840.10008.1.2.2",
  // JPEG Baseline (Process 1)
  "1.2.840.10008.1.2.4.50",
  // JPEG Extended (Process 2 & 4)
  "1.2.840.10008.1.2.4.51",
  // JPEG Extended (Process 3 & 5)
  "1.2.840.10008.1.2.4.52",
  // JPEG Spectral Selection, Non-Hierarchical (Process 6 & 8)
  "1.2.840.10008.1.2.4.53",
  // JPEG Full Progression, Non-Hierarchical (Process 10 & 12)
  "1.2.840.10008.1.2.4.55",
  // JPEG Lossless, Non-Hierarchical (Process 14)
  "1.2.840.10008.1.2.4.57",
  // JPEG Lossless, Hierarchical, First-Order Prediction (Process 14,
  //                                                       [Selection Value 1])
  "1.2.840.10008.1.2.4.70",
  // JPEG-LS Lossless Image Compression
  "1.2.840.10008.1.2.4.80",
  // JPEG-LS Lossy (Near-Lossless) Image Compression
  "1.2.840.10008.1.2.4.81",
  // JPEG 2000 Lossless
  "1.2.840.10008.1.2.4.90",
  // JPEG 2000
  "1.2.840.10008.1.2.4.91",
  // RLE Lossless
  "1.2.840.10008.1.2.5",
  // MPEG2 Main Profile @ Main Level
  "1.2.840.10008.1.2.4.100",
  // Old ACR NEMA, fake a TS
  "ImplicitVRBigEndianACRNEMA",
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  // Weird Papyrus
  "1.2.840.10008.1.20",
#endif
  // Unknown
  "Unknown Transfer Syntax", // Pretty sure we never use this case...
  0 // Compilers have no obligation to finish by NULL, do it ourself
};

const TransferSyntax::TSType TransferSyntax::GetTSType(const char *cstr)
{
  // trim trailing whitespace
  std::string str = cstr;
  std::string::size_type notspace = str.find_last_not_of(" ") + 1;
  if( notspace != str.size() )
    {
    gdcmDebugMacro( "BUGGY HEADER: TS contains " << 
      str.size()-notspace << " whitespace character(s)" );
    str.erase(notspace);
    }

  int i = 0;
  while(TSStrings[i] != 0)
    {
    if( str == TSStrings[i] )
      return (TSType)i;
    ++i;
    }
  return TS_END;
}

const char* TransferSyntax::GetTSString(const TSType &ts)
{
  assert( ts <= TS_END );
  return TSStrings[(int)ts];
}

bool TransferSyntax::IsImplicit(const TSType &ts) const
{
  assert( ts != TS_END );
  return ts == ImplicitVRLittleEndian
    || ts == ImplicitVRBigEndianACRNEMA
    || ts == ImplicitVRBigEndianPrivateGE
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    || ts == WeirdPapryus
#endif
    ;
}

// By implementation those two functions form a partition
bool TransferSyntax::IsExplicit(const TSType &ts) const
{
  assert( ts != TS_END );
  return !IsImplicit(ts);
}

TransferSyntax::NegociatedType TransferSyntax::GetNegociatedType() const
{
  if( TSField == TS_END )
    {
    return TransferSyntax::Unknown;
    }
  else if( IsImplicit(TSField) )
    {
    return TransferSyntax::Implicit;
    }
  return TransferSyntax::Explicit;
}

bool TransferSyntax::IsLittleEndian(const TSType &ts) const
{
  assert( ts != TS_END );
  return !IsBigEndian(ts);
}

bool TransferSyntax::IsBigEndian(const TSType &ts) const
{
  assert( ts != TS_END );
  return ts == ExplicitVRBigEndian
//    || ts == ImplicitVRBigEndianPrivateGE // Indeed this is LittleEndian
    || ts == ImplicitVRBigEndianACRNEMA;
}

SwapCode TransferSyntax::GetSwapCode() const
{
  assert( TSField != TS_END );
  if( IsBigEndian( TSField ) )
    {
    return SwapCode::BigEndian;
    }
  assert( IsLittleEndian( TSField ) );
  return SwapCode::LittleEndian;
}

bool TransferSyntax::IsEncoded() const
{
  return TSField == DeflatedExplicitVRLittleEndian;
}

} // end namespace gdcm

