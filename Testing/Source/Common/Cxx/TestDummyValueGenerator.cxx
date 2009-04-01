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
#include "gdcmDummyValueGenerator.h"
#include "gdcmTesting.h"

int TestDummyValueGenerator(int argc, char *argv[])
{
  gdcm::DummyValueGenerator dvg;
  const char patientid1[] = "hello";
  const char patientid2[] = "hello ";
  // Because patientid1 & patientid2 are equivalent in DICOM we need to be able to generate 
  // identical replacement value in case of de-identifier operation:

  std::string str1 = gdcm::DummyValueGenerator::Generate( patientid1 );
  std::string str2 = gdcm::DummyValueGenerator::Generate( patientid2 );

  if( str1 != str2 )
    {
    return 1;
    }

  return 0;
}

