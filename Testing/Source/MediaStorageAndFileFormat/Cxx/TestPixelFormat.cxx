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
#include "gdcmPixelFormat.h"

int TestPixelFormat(int , char *[])
{
  using gdcm::PixelFormat;
  gdcm::PixelFormat pf;
  pf.SetScalarType( gdcm::PixelFormat::UNKNOWN );
  if( pf.GetScalarType() != gdcm::PixelFormat::UNKNOWN )
    {
    return 1;
    }
  pf.SetBitsStored( 8 );
  std::cout << pf.GetMin() << "," << pf.GetMax() << std::endl;
  pf.SetBitsStored( 12 );
  std::cout << pf.GetMin() << "," << pf.GetMax() << std::endl;
  pf.SetBitsStored( 16 );
  std::cout << pf.GetMin() << "," << pf.GetMax() << std::endl;
  pf.SetBitsStored( 32 );
  std::cout << pf.GetMin() << "," << pf.GetMax() << std::endl;

  pf.SetPixelRepresentation( 1 );

  pf.SetBitsStored( 8 );
  std::cout << pf.GetMin() << "," << pf.GetMax() << std::endl;
  pf.SetBitsStored( 12 );
  std::cout << pf.GetMin() << "," << pf.GetMax() << std::endl;
  pf.SetBitsStored( 16 );
  std::cout << pf.GetMin() << "," << pf.GetMax() << std::endl;
  pf.SetBitsStored( 32 );
  std::cout << pf.GetMin() << "," << pf.GetMax() << std::endl;

  for(unsigned int i = 0; i < PixelFormat::UNKNOWN; ++i)
    {
    PixelFormat::ScalarType st = (PixelFormat::ScalarType)i;
    pf.SetScalarType( st );
    gdcm::PixelFormat pf2 = st;
    std::cout << pf << std::endl;
    std::cout << pf.GetPixelRepresentation() << std::endl;
    std::cout << pf.GetScalarTypeAsString() << std::endl;
    if( pf2 != pf ) return 1;
    }
  return 0;
}
