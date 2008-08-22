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
#include "gdcmMediaStorage.h"

int TestMediaStorage(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  gdcm::MediaStorage ms;
  if( ms != gdcm::MediaStorage::MS_END )
    {
    return 1;
    }
  ms = gdcm::MediaStorage::SecondaryCaptureImageStorage;
  if( ms != gdcm::MediaStorage::SecondaryCaptureImageStorage )
    {
    return 1;
    }
  ms.GuessFromModality( "MR" );
  if( ms != gdcm::MediaStorage::MRImageStorage )
    {
    return 1;
    }
  ms.GuessFromModality( "MR" , 3 );
  if( ms != gdcm::MediaStorage::EnhancedMRImageStorage )
    {
    return 1;
    }

  return 0;
}

