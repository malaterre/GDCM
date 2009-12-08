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
#include "gdcmDefs.h"
#include "gdcmUIDs.h"
#include "gdcmGlobal.h"
#include "gdcmMediaStorage.h"

int TestDefs(int, char *[])
{
  using gdcm::MediaStorage;
  gdcm::Global& g = gdcm::Global::GetInstance();
  if( !g.LoadResourcesFiles() )
    {
    std::cerr << "Could not LoadResourcesFiles" << std::endl;
    return 1;
    }

  const gdcm::Defs &defs = g.GetDefs();

  int ret = 0;
  gdcm::MediaStorage::MSType mst;
  for ( mst = gdcm::MediaStorage::MediaStorageDirectoryStorage; mst < gdcm::MediaStorage::MS_END; mst = (gdcm::MediaStorage::MSType)(mst + 1) )
    {
    const char *iod = defs.GetIODNameFromMediaStorage(mst);
    if( !iod )
      {
      gdcm::UIDs uid;
      uid.SetFromUID( gdcm::MediaStorage::GetMSString(mst) /*mst.GetString()*/ );
      // We do not support Private IODs (for now??)
      if( mst != MediaStorage::PhilipsPrivateMRSyntheticImageStorage 
        && mst != MediaStorage::ToshibaPrivateDataStorage 
        && mst != MediaStorage::GEPrivate3DModelStorage 
        && mst != MediaStorage::Philips3D
        && mst != MediaStorage::CSANonImageStorage
        && mst != MediaStorage::GeneralElectricMagneticResonanceImageStorage )
        {
        std::cerr << "Missing iod for MS: " << mst << " " <<
          gdcm::MediaStorage::GetMSString(mst) << std::endl;
        std::cerr << "MediaStorage is " << mst << " [" << uid.GetName() << "]" << std::endl;
        ++ret;
        }
      }
    }


  return ret;
}

