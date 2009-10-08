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
#include "gdcmImageHelper.h"
#include "gdcmMediaStorage.h"
#include "gdcmDataSet.h"
#include "gdcmAttribute.h"

int TestImageHelper(int, char *[])
{
  gdcm::ImageHelper sh;
  const double pos[] = { 0,0,0,
                         1,1,1};
  const double answer[3] = {1,1,1};
  
  std::vector<double> impos(pos,pos+6);
  std::vector<double> spacing;
  spacing.resize(3);
  if( !gdcm::ImageHelper::ComputeSpacingFromImagePositionPatient(impos, spacing) )
    {
    return 1;
    }
  std::cout << spacing[0] << std::endl;
  std::cout << spacing[1] << std::endl;
  std::cout << spacing[2] << std::endl;


  std::vector<double> dircos;
  // make it an invalid call
  dircos.resize(6);
  dircos[0] = 1;
  dircos[1] = 0;
  dircos[2] = 0;
  dircos[3] = 1;
  dircos[4] = 0;
  dircos[5] = 0;
  // Try SC
{
  gdcm::MediaStorage ms( gdcm::MediaStorage::SecondaryCaptureImageStorage );
  gdcm::DataSet ds;

    gdcm::DataElement de( gdcm::Tag(0x0008, 0x0016) );
    const char* msstr = gdcm::MediaStorage::GetMSString(ms);
    de.SetByteValue( msstr, strlen(msstr) );
    de.SetVR( gdcm::Attribute<0x0008, 0x0016>::GetVR() );
    ds.Insert( de );

  // Since SC this is a no-op
  gdcm::ImageHelper::SetDirectionCosinesValue( ds, dircos );

  // previous call removed the attribute
  gdcm::Tag iop(0x0020,0x0037);
  if(  ds.FindDataElement( iop ) ) return 1;
}

  // MR now
{
  gdcm::MediaStorage ms( gdcm::MediaStorage::MRImageStorage );
  gdcm::DataSet ds;

    gdcm::DataElement de( gdcm::Tag(0x0008, 0x0016) );
    const char* msstr = gdcm::MediaStorage::GetMSString(ms);
    de.SetByteValue( msstr, strlen(msstr) );
    de.SetVR( gdcm::Attribute<0x0008, 0x0016>::GetVR() );
    ds.Insert( de );

  // Since SC this is a no-op
  gdcm::ImageHelper::SetDirectionCosinesValue( ds, dircos );

  // previous call should not have executed anything
  gdcm::Tag iop(0x0020,0x0037);
  if(  ds.FindDataElement( iop ) ) return 1;

  // TODO: need to check DirectionCosines .IsValid()
} 
  
  return 0;
}

