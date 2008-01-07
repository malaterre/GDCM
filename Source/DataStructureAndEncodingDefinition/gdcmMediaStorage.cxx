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
#include "gdcmMediaStorage.h"

namespace gdcm
{

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

const MediaStorage::MSType MediaStorage::GetMSType(const char *str)
{
  assert( std::string(str).find( ' ' ) == std::string::npos ); // no space allowed in UI
  int i = 0;
  while(MSStrings[i] != 0)
    {
    if( strcmp(str, MSStrings[i]) == 0 )
      return (MSType)i;
    ++i;
    }
  return MS_END;
}

const char* MediaStorage::GetMSString(const MSType &ms)
{
  assert( ms <= MS_END );
  return MSStrings[(int)ms];
}

// FIXME
// Currently the implementation is bogus it only define the TS which
// are associated with an image so indeed the implementation of IsImage 
// is only the verification of TSType is != TS_END
bool MediaStorage::IsImage(const MSType &ms)
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

} // end namespace gdcm
