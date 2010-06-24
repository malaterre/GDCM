/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmSplitMosaicFilter.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"
#include "gdcmImageReader.h"

int TestSplitMosaicFilter(int, char *[])
{
  gdcm::SplitMosaicFilter s;

  const char *extradataroot = gdcm::Testing::GetDataExtraRoot();
  if( !extradataroot )
    {
    return 1;
    }
  if( !gdcm::System::FileIsDirectory(extradataroot) )
    {
    std::cerr << "No such directory: " << extradataroot <<  std::endl;
    return 1;
    }

  std::string filename = extradataroot;
  filename += "/gdcmSampleData/images_of_interest/MR-sonata-3D-as-Tile.dcm";

  // std::cout << filename << std::endl;
  if( !gdcm::System::FileExists(filename.c_str()) )
    {
    return 1;
    }

  gdcm::ImageReader reader;
  reader.SetFileName( filename.c_str() );
  if( !reader.Read() )
    {
    std::cerr << "could not read: " << filename << std::endl;
    return 1;
    }

  gdcm::SplitMosaicFilter filter;
  filter.SetImage( reader.GetImage() );
  filter.SetFile( reader.GetFile() );
  bool b = filter.Split();
  if( !b )
    {
    std::cerr << "Could not split << " << filename << std::endl;
    return 1;
    }

  const gdcm::Image &image = filter.GetImage();

  return 0;
}
