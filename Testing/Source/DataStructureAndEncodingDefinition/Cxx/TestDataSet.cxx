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
#include "gdcmDataSet.h"
#include "gdcmDataElement.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"


int TestDataSet(int , char *[])
{
  gdcm::DataSet ds;
  std::cout << sizeof ds << std::endl;
  gdcm::DataElement d;
  ds.Insert(d);
  const gdcm::DataElement& r =
	  ds.GetDataElement( gdcm::Tag(0,0) );
  std::cout << r << std::endl;

  const gdcm::Tag t2 = gdcm::Tag(0x1234, 0x5678);
  gdcm::DataElement d2(t2);
  std::cout << d2 << std::endl;
  ds.Insert(d2);
  const gdcm::DataElement& r2 =
	  ds.GetDataElement( t2 );
  std::cout << r2 << std::endl;

  const gdcm::Tag t3 = gdcm::Tag(0x1234, 0x5679);
  gdcm::DataElement d3(t3);
  d3.SetVR( gdcm::VR::UL );
  std::cout << d3 << std::endl;
  ds.Insert(d3);
  const gdcm::DataElement& r3 =
	  ds.GetDataElement( t3 );
  std::cout << r3 << std::endl;

  std::cout << "Size:" << ds.Size() << std::endl;
  if( ds.Size() != 3 )
    {
    return 1;
    }

  std::cout << "Print Dataset:" << std::endl;
  std::cout << ds << std::endl;

  return 0;
}

