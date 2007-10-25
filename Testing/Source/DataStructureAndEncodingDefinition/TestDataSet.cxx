/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
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
  gdcm::DataSet ds; // ( gdcm::TS::Implicit );
  std::cout << sizeof ds << std::endl;
  gdcm::ImplicitDataElement d;
  ds.InsertDataElement(d);
  const gdcm::DataElement& r =
	  ds.GetDataElement( gdcm::Tag(0,0) );
  std::cout << r << std::endl;

  const gdcm::Tag t = gdcm::Tag(0x1234, 0x5678);
  gdcm::ImplicitDataElement d2(t);
  std::cout << d2 << std::endl;
  ds.InsertDataElement(d2);
  const gdcm::DataElement& r2 =
	  ds.GetDataElement( t );
  std::cout << r2 << std::endl;

  const gdcm::Tag t3 = gdcm::Tag(0x1234, 0x5679);
  gdcm::ExplicitDataElement d3(t3);
  d3.SetVR( gdcm::VR::UL );
  std::cout << d3 << std::endl;
  ds.InsertDataElement(d3);
  const gdcm::DataElement& r3 =
	  ds.GetDataElement( t3 );
  std::cout << r3 << std::endl;

  std::cout << "Print Dataset:" << std::endl;
  std::cout << "Length:" << ds.GetLength() << std::endl;
  std::cout << ds << std::endl;

  return 0;
}

