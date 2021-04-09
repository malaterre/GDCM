/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmMediaStorage.h"
#include "gdcmFile.h"
#include "gdcmDataElement.h"

int TestMediaStorage(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  gdcm::MediaStorage ms;
  if( !ms.IsUndefined() )
    {
    std::cerr << "ms.IsUndefined" << std::endl;
    return 1;
    }
  ms = gdcm::MediaStorage::SecondaryCaptureImageStorage;
  if( ms != gdcm::MediaStorage::SecondaryCaptureImageStorage )
    {
    std::cerr << "SecondaryCaptureImageStorage" << std::endl;
    return 1;
    }
  ms.GuessFromModality( "MR" );
  if( ms != gdcm::MediaStorage::MRImageStorage )
    {
    std::cerr << "MRImageStorage" << std::endl;
    return 1;
    }
  ms.GuessFromModality( "MR" , 3 );
  if( ms != gdcm::MediaStorage::EnhancedMRImageStorage )
    {
    std::cerr << "EnhancedMRImageStorage" << std::endl;
    return 1;
    }
  //checks *MSStrings[] and MSModalityTypes[] length
  gdcm::MediaStorage::MSType mst;
  for ( mst = gdcm::MediaStorage::MediaStorageDirectoryStorage; mst < gdcm::MediaStorage::MS_END; mst = (gdcm::MediaStorage::MSType)(mst + 1) )
    {
    if ( gdcm::MediaStorage::GetMSString(mst) == nullptr )
      {
      std::cerr << "GetMSString" << std::endl;
      return 1;
      }
    }
  mst = gdcm::MediaStorage::MS_END;
  if ( gdcm::MediaStorage::GetMSString(mst) != nullptr )
    {
    std::cerr << "2: GetMSString" << std::endl;
    return 1;
    }
  gdcm::MediaStorage ms2;
  if ( ms2.GetModality() )
    {
    return 1;
    }

  // MediaStorage is really poorly implemented. We need to add a test to avoid dev shooting themself in the foot.
  unsigned int nMSType = gdcm::MediaStorage::GetNumberOfMSType();
  unsigned int nMSString = gdcm::MediaStorage::GetNumberOfMSString();
  unsigned int nMSMod = gdcm::MediaStorage::GetNumberOfModality();
  if( nMSType != nMSString || nMSType != nMSMod )
    {
    std::cerr << "you are shooting yourself in the foot, dear.: " << nMSType << "," << nMSString << "," << nMSMod << std::endl;
    return 1;
    }

{
  gdcm::File f;
  gdcm::DataSet &ds = f.GetDataSet();
  gdcm::DataElement de;
  de.SetTag( gdcm::Tag(0x8,0x16) );
  ds.Insert( de );
  gdcm::MediaStorage ms3;
  ms3.SetFromFile( f );
  if( ms3 != gdcm::MediaStorage::SecondaryCaptureImageStorage )
    {
    std::cerr << "SecondaryCaptureImageStorage" << std::endl;
    return 1;
    }
}
{
  gdcm::File f;
  gdcm::FileMetaInformation &fmi  = f.GetHeader();
  gdcm::DataElement de;
  de.SetTag( gdcm::Tag(0x2,0x2) );
  // de.SetByteValue( "", 0 );
  fmi.Insert( de );
  gdcm::MediaStorage ms4;
  ms4.SetFromFile( f );
  if( ms4 != gdcm::MediaStorage::SecondaryCaptureImageStorage )
    {
    std::cerr << "SecondaryCaptureImageStorage" << std::endl;
    return 1;
    }
}
  

  return 0;
}
