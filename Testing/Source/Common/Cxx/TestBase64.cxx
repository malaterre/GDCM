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
#include "gdcmBase64.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"


using gdcm::Base64;
struct MyBase64 : public Base64
{
  int MySelfTest( int verbose ) { return SelfTest(verbose); }
};

int TestBase64(int argc, char *argv[])
{
  MyBase64 mybase64;
  int ret = mybase64.MySelfTest( 0 );

  return ret;
}

