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
#include "gdcmTS.h"
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

static const char *MSStrings[] = {
  "1.2.840.10008.1.3.10",
  "1.2.840.10008.5.1.4.1.1.1",    
  "1.2.840.10008.5.1.4.1.1.1.1",  
  "1.2.840.10008.5.1.4.1.1.1.1.1",
  "1.2.840.10008.5.1.4.1.1.1.2",  
  "1.2.840.10008.5.1.4.1.1.1.2.1",
  "1.2.840.10008.5.1.4.1.1.1.3",  
  "1.2.840.10008.5.1.4.1.1.1.3.1",
  "1.2.840.10008.5.1.4.1.1.2",    
  "1.2.840.10008.5.1.4.1.1.2.1",  
  "1.2.840.10008.5.1.4.1.1.3",    
  "1.2.840.10008.5.1.4.1.1.3.1",  
  "1.2.840.10008.5.1.4.1.1.4",    
  "1.2.840.10008.5.1.4.1.1.4.1",  
  "1.2.840.10008.5.1.4.1.1.4.2",  
  "1.2.840.10008.5.1.4.1.1.5",    
  "1.2.840.10008.5.1.4.1.1.6",    
  "1.2.840.10008.5.1.4.1.1.6.1",  
  "1.2.840.10008.5.1.4.1.1.7",    
  "1.2.840.10008.5.1.4.1.1.7.1",  
  "1.2.840.10008.5.1.4.1.1.7.2",  
  "1.2.840.10008.5.1.4.1.1.7.3",  
  "1.2.840.10008.5.1.4.1.1.7.4",  
  "1.2.840.10008.5.1.4.1.1.8",    
  "1.2.840.10008.5.1.4.1.1.9",    
  "1.2.840.10008.5.1.4.1.1.9.1.1",
  "1.2.840.10008.5.1.4.1.1.9.1.2",
  "1.2.840.10008.5.1.4.1.1.9.1.3",
  "1.2.840.10008.5.1.4.1.1.9.2.1",
  "1.2.840.10008.5.1.4.1.1.9.3.1",
  "1.2.840.10008.5.1.4.1.1.9.4.1",
  "1.2.840.10008.5.1.4.1.1.10",   
  "1.2.840.10008.5.1.4.1.1.11",   
  "1.2.840.10008.5.1.4.1.1.11.1", 
  "1.2.840.10008.5.1.4.1.1.12.1", 
  "1.2.840.10008.5.1.4.1.1.12.2", 
  "1.2.840.10008.5.1.4.1.1.12.3", 
  "1.2.840.10008.5.1.4.1.1.20",   
  "1.2.840.10008.5.1.4.1.1.66",   
  "1.2.840.10008.5.1.4.1.1.66.1", 
  "1.2.840.10008.5.1.4.1.1.66.2", 

  // See PETAt001_PT001.dcm
  "1.2.840.10008.5.1.4.1.1.128",
  // SYNGORTImage.dcm
  "1.2.840.10008.5.1.4.1.1.481.1",
  // eclipse_dose.dcm
  "1.2.840.10008.5.1.4.1.1.481.2",
  // exRT_Structure_Set_Storage.dcm
  "1.2.840.10008.5.1.4.1.1.481.3",
  // eclipse_plan.dcm
  "1.2.840.10008.5.1.4.1.1.481.5",
  // exCSA_Non-Image_Storage.dcm
  "1.3.12.2.1107.5.9.1",
  // 3DDCM011.dcm
  "1.2.840.113543.6.6.1.3.10002",
  0
};

const TS::TSType TS::GetTSType(const char *cstr)
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

const char* TS::GetTSString(const TSType &ts)
{
  assert( ts <= TS_END );
  return TSStrings[(int)ts];
}

const TS::MSType TS::GetMSType(const char *str)
{
  int i = 0;
  while(MSStrings[i] != 0)
    {
    if( strcmp(str, MSStrings[i]) == 0 )
      return (MSType)i;
    ++i;
    }
  return MS_END;
}

const char* TS::GetMSString(const MSType &ms)
{
  assert( ms <= MS_END );
  return MSStrings[(int)ms];
}

// FIXME IsJPEG and IsMPEG and real bad implementation... NEED TO REDO
bool TS::IsMPEG(const TSType &ts)
{
  const char *s = GetTSString(ts);
  const char mpeg[] = "1.2.840.10008.1.2.4.100"; // special case
  if( strcmp(s, mpeg) == 0)
    return true;
  return false;
}

// FIXME this function is not rebust and return JPEG when presented
// JPEG2000 TS
bool TS::IsJPEG(const TSType &ts)
{
  const char *s = GetTSString(ts);
  const char jpeg[] = "1.2.840.10008.1.2.4";
  const char mpeg[] = "1.2.840.10008.1.2.4.100"; // special case
  if( strcmp(s, mpeg) == 0)
    return false;
  if( strncmp(s, jpeg, strlen(jpeg)) == 0)
    {
    assert( !IsJPEG2000(ts) );
    return true;
    }
  return false;
}

bool TS::IsJPEG2000(const TSType &ts)
{
  if( ts == JPEG2000Lossless
    || ts == JPEG2000 )
    {
    //assert( !IsJPEG(ts) );
    return true;
    }
  return false;
}

bool TS::IsRAW(const TSType &ts)
{
  if( ts == TS::ImplicitVRLittleEndian
   || ts == TS::ExplicitVRLittleEndian
   || ts == TS::ExplicitVRBigEndian
   || ts == TS::ImplicitVRBigEndianPrivateGE )
    {
    return true;
    }
  return false;
}

bool TS::IsRLE(const TSType &ts)
{
  if( ts == TS::RLELossless )
    {
    return true;
    }
  return false;
}

TS::NegociatedType TS::GetNegociatedType() const
{
  if( TSField == TS_END )
    {
    return TS::Unknown;
    }
  else if( IsImplicit(TSField) )
    {
    return TS::Implicit;
    }
  return TS::Explicit;
}

bool TS::IsImplicit(const TSType &ts)
{
  assert( ts != TS::TS_END );
  return ts == ImplicitVRLittleEndian
    || ts == ImplicitVRBigEndianACRNEMA
    || ts == ImplicitVRBigEndianPrivateGE
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    || ts == WeirdPapryus
#endif
    ;
}

// By implementation those two functions form a partition
bool TS::IsExplicit(const TSType &ts)
{
  assert( ts != TS::TS_END );
  return !IsImplicit(ts);
}

bool TS::IsLittleEndian(const TSType &ts)
{
  assert( ts != TS::TS_END );
  return !IsBigEndian(ts);
}

bool TS::IsBigEndian(const TSType &ts)
{
  assert( ts != TS::TS_END );
  return ts == ExplicitVRBigEndian
//    || ts == ImplicitVRBigEndianPrivateGE // Indeed this is LittleEndian
    || ts == ImplicitVRBigEndianACRNEMA;
}

SwapCode TS::GetSwapCode() const
{
  assert( TSField != TS::TS_END );
  if( IsBigEndian( TSField ) )
    {
    return SwapCode::BigEndian;
    }
  assert( IsLittleEndian( TSField ) );
  return SwapCode::LittleEndian;
}

bool TS::IsDataSetEncoded(const TSType &ts)
{
  return ts == DeflatedExplicitVRLittleEndian;
}

// FIXME
// Currently the implementation is bogus it only define the TS which
// are associated with an image so indeed the implementation of IsImage 
// is only the verification of TSType is != TS_END
bool TS::IsImage(const MSType &ms)
{
  if ( ms == MS_END // most frequent first
    // lexicographical order then...
    || ms == BasicVoiceAudioWaveformStorage
    || ms == CSANonImageStorage
    || ms == HemodynamicWaveformStorage
    || ms == MediaStorageDirectoryStorage
    || ms == RTPlanStorage
    || ms == RTStructureSetStorage )
    {
    return false;
    }
  return true;
}

Compression::Types TS::GetCompressionType() const
{
  if( IsRAW( TSField ) )
    {
    return Compression::RAW;
    }
  else if ( IsJPEG2000( TSField ) )
    {
    return Compression::JPEG2000;
    }
  else if ( IsJPEG( TSField ) )
    {
    return Compression::JPEG;
    }
  else if ( IsRLE( TSField ) )
    {
    return Compression::RLE;
    }

  return Compression::UNKNOWN;
}

} // end namespace gdcm
