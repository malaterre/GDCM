/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmTesting.h"
#include "gdcmImageHelper.h"
#include "gdcmImageReader.h"
#include "gdcmImageWriter.h"
#include "gdcmMediaStorage.h"
#include "gdcmDataSet.h"
#include "gdcmAttribute.h"
#include "gdcmDirectionCosines.h"

int TestImageHelper2(int, char *[])
{
  static const char *filenames[] = {
    "D_CLUNIE_MR2_RLE.dcm",
  };

  const unsigned int nfiles = sizeof(filenames)/sizeof(*filenames);
  const char *root = gdcm::Testing::GetDataRoot();
  if( !root || !*root )
    {
    std::cerr << "root is not defiend" << std::endl;
    return 1;
    }
  std::string sroot = root;
  sroot += "/";

  for(unsigned int i = 0; i < nfiles; ++i)
    {
    const char * filename = filenames[i];
    std::string fullpath = sroot + filename;

  gdcm::ImageHelper::SetForceRescaleInterceptSlope(true);
    gdcm::ImageReader r;
    r.SetFileName( fullpath.c_str() );
    if( !r.Read() )
      {
        return 1;
      }
  gdcm::ImageHelper::SetForceRescaleInterceptSlope(false);
    gdcm::Image & img = r.GetImage();
    std::cout << img.GetIntercept() << std::endl;
    std::cout << img.GetSlope() << std::endl;
    gdcm::SmartPointer<gdcm::SequenceOfItems> sq = new gdcm::SequenceOfItems();
    const gdcm::Tag trwvms(0x0040,0x9096); // Real World Value Mapping Sequence
    gdcm::DataElement de( trwvms );
    de.SetVR( gdcm::VR::SQ );
    de.SetValue(*sq);

    gdcm::DataSet & ds = r.GetFile().GetDataSet();
    ds.Insert( de );

    ds.Remove( gdcm::Tag(0x28,0x1052) );
    ds.Remove( gdcm::Tag(0x28,0x1053) );
    ds.Remove( gdcm::Tag(0x28,0x1054) );
  // Create directory first:
  const char subdir[] = "TestImageHelper2";
  std::string tmpdir = gdcm::Testing::GetTempDirectory( subdir );
  if( !gdcm::System::FileIsDirectory( tmpdir.c_str() ) )
    {
    gdcm::System::MakeDirectory( tmpdir.c_str() );
    //return 1;
    }
  std::string outfilename = gdcm::Testing::GetTempFilename( filename, subdir );

  gdcm::ImageWriter writer;
  writer.SetFileName( outfilename.c_str() );
  writer.SetFile( r.GetFile() );
  writer.SetImage( r.GetImage() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }


    }

  return 0;
}
