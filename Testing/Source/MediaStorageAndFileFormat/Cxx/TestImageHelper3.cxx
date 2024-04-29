/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageHelper.h"
#include "gdcmMediaStorage.h"
#include "gdcmDataSet.h"
#include "gdcmAttribute.h"
#include "gdcmDirectionCosines.h"
#include "gdcmImage.h"
#include "gdcmFile.h"

int TestImageHelper3(int, char *[])
{

  std::vector<double> impos;
  impos.resize(3);
  impos[0] = 1;
  impos[1] = 2;
  impos[2] = 3;
  std::vector<double> spacing;
  spacing.resize(3);
  spacing[0] = 0.6;
  spacing[1] = 0.5;
  spacing[2] = 0.4;

  std::vector<double> dircos;
  dircos.resize(6);
  dircos[0] = 0;
  dircos[1] = 1;
  dircos[2] = 0;
  dircos[3] = 1;
  dircos[4] = 0;
  dircos[5] = 0;

  gdcm::Image img;
  img.SetNumberOfDimensions(3);
  img.SetOrigin( impos.data() );
  img.SetSpacing( spacing.data() );
  img.SetDirectionCosines( dircos.data() );
  // Try SC
  gdcm::File file;
{
  gdcm::ImageHelper::SetSecondaryCaptureImagePlaneModule( false );
  gdcm::MediaStorage ms( gdcm::MediaStorage::SecondaryCaptureImageStorage );
  gdcm::DataSet&ds = file.GetDataSet();

    gdcm::DataElement de( gdcm::Tag(0x0008, 0x0016) );
    const char* msstr = gdcm::MediaStorage::GetMSString(ms);
    de.SetByteValue( msstr, (uint32_t)strlen(msstr) );
    de.SetVR( gdcm::Attribute<0x0008, 0x0016>::GetVR() );
    ds.Insert( de );

  gdcm::ImageHelper::SetDirectionCosinesValue( ds, dircos );
  gdcm::ImageHelper::SetOriginValue( ds, img );
  gdcm::ImageHelper::SetSpacingValue( ds, spacing );

  std::cout << ds << std::endl;

  gdcm::Tag nominal(0x0018,0x2010 );
  if( !ds.FindDataElement( nominal ) ) return 1;
  gdcm::Tag iop(0x0020,0x0037);
  if( ds.FindDataElement( iop ) ) return 1;

  std::vector<double> ret = gdcm::ImageHelper::GetSpacingValue( file );
  // warning;: only two dim:
  if( ret[0] != spacing[0] || ret[1] != spacing[1] ) {
    std::cerr << ret[0] << "," << ret[1] << std::endl;
    return 1;
  }
}
  gdcm::File cp2330file;
{
  // New CP 2330 behavior
  gdcm::ImageHelper::SetSecondaryCaptureImagePlaneModule( true );
  gdcm::MediaStorage ms( gdcm::MediaStorage::SecondaryCaptureImageStorage );
  gdcm::DataSet&ds = cp2330file.GetDataSet();

    gdcm::DataElement de( gdcm::Tag(0x0008, 0x0016) );
    const char* msstr = gdcm::MediaStorage::GetMSString(ms);
    de.SetByteValue( msstr, (uint32_t)strlen(msstr) );
    de.SetVR( gdcm::Attribute<0x0008, 0x0016>::GetVR() );
    ds.Insert( de );

  // New CP 2330 behavior
  gdcm::ImageHelper::SetDirectionCosinesValue( ds, dircos );
  gdcm::ImageHelper::SetOriginValue( ds, img );
  gdcm::ImageHelper::SetSpacingValue( ds, spacing );

  std::cout << ds << std::endl;

  // previous call added the attribute
  gdcm::Tag pixelspacing(0x0028,0x0030);
  if( !ds.FindDataElement( pixelspacing ) ) return 1;
  gdcm::Tag iop(0x0020,0x0037);
  if( !ds.FindDataElement( iop ) ) return 1;

  std::vector<double> ret = gdcm::ImageHelper::GetSpacingValue( cp2330file );
  if( ret != spacing ) {
    std::cerr << ret[0] << "," << ret[1]  << "," << ret[2] << std::endl;
    return 1;
  }
  // make sure legacy still works:
  ret = gdcm::ImageHelper::GetSpacingValue( file );
  if( ret[0] != spacing[0] || ret[1] != spacing[1] || ret[2] != 1 ) {
    std::cerr << ret[0] << "," << ret[1] << std::endl;
    return 1;
  }

}


  std::cout << "success" << std::endl;
  return 0;
}
