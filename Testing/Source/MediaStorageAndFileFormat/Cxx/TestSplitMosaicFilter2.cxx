/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmSplitMosaicFilter.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"
#include "gdcmReader.h"
#include "gdcmAnonymizer.h"
#include "gdcmPrivateTag.h"
#include "gdcmCSAHeader.h"
#include "gdcmElement.h"
#include "gdcmDirectionCosines.h"

int TestSplitMosaicFilter2(int argc, char *argv[])
{
  std::string filename;
  if( argc == 2 )
    {
    filename = argv[1];
    }
  else
    {
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

    filename = extradataroot;
    filename += "/gdcmSampleData/images_of_interest/MR-sonata-3D-as-Tile.dcm";
    }
  gdcm::SplitMosaicFilter s;
  if( !gdcm::System::FileExists(filename.c_str()) )
    {
    return 1;
    }

  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  if( !reader.Read() )
    {
    std::cerr << "could not read: " << filename << std::endl;
    return 1;
    }

  gdcm::SplitMosaicFilter filter;
  filter.SetFile( reader.GetFile() );
  double slicenormal[3];
  bool b = filter.ComputeMOSAICSliceNormal( slicenormal );
  if( !b )
  {
    std::cerr << "Could not ComputeMOSAICSliceNormal: " << filename << std::endl;
    return 1;
  }

  const double refnormal[3] = {-0.08193696,0.08808136,0.99273763};
  const double eps = 1e-6;
  gdcm::DirectionCosines dc;
  const double dot = dc.Dot( slicenormal, refnormal );
  if( std::fabs( 1.0 - dot ) > eps )
  {
    std::cerr << "Invalid ComputeMOSAICSliceNormal: " << filename << std::endl;
    return 1;
  }

  double slicepos[3];
  b = filter.ComputeMOSAICSlicePosition( slicepos );
  if( !b )
  {
    std::cerr << "Could not ComputeMOSAICSlicePosition: " << filename << std::endl;
    return 1;
  }

  const double refpos[3] = { 2.24891108,-52.65585315,-26.94105767 };
  for( int i = 0; i < 3; ++i ) 
  {
    if( std::fabs( refpos[i] - slicepos[i] ) > eps )
    {
      std::cerr << "Invalid ComputeMOSAICSlicePosition: " << filename << std::endl;
      return 1;
    }
  }


  gdcm::Anonymizer ano;
  ano.SetFile( reader.GetFile() );
  gdcm::CSAHeader csa;
  const gdcm::PrivateTag &t1 = csa.GetCSAImageHeaderInfoTag();
  ano.Remove( t1 );

  unsigned int modims[3];
  b = filter.ComputeMOSAICDimensions( modims );
  if( b ) return 1;
 
  // alternate code path:
  gdcm::PrivateTag t2 (0x0019,0x0a, "SIEMENS MR HEADER");
  gdcm::DataSet & ds = reader.GetFile().GetDataSet();
  if( ds.FindDataElement( t2 ) )
  {
    return 1;
  }
  else
  {
    // Create a fake one:
    std::string creator = ds.GetPrivateCreator( t2 );
    if( !creator.empty() ) return 1;
    gdcm::Tag t3 (0x0019,0x10);
    ano.Replace( t3, t2.GetOwner() );
    gdcm::Element<gdcm::VR::US, gdcm::VM::VM1> elem;
    elem.SetValue( 31 );
    gdcm::DataElement de = elem.GetAsDataElement();
    de.SetTag( t2 );
    const uint16_t el = de.GetTag().GetElement();
    de.GetTag().SetElement( 0x1000 + el );
    if( de.GetVR() != gdcm::VR::US ) return 1;
    ds.Insert( de );
    creator = ds.GetPrivateCreator( de.GetTag() );
    if( creator.empty() ) return 1;
  }

  b = filter.ComputeMOSAICDimensions( modims );
  if( !b )
    {
    std::cerr << "Could not ComputeMOSAICDimensions " << filename << std::endl;
    return 1;
    }
  const unsigned int ref[3] = { 64u, 64u, 31u };
  if( modims[0] != ref[0] || modims[1] != ref[1] || modims[2] != ref[2] )
  {
    std::cerr << "Invalid ComputeMOSAICDimensions " << filename << std::endl;
    return 1;
  }

  return 0;
}
