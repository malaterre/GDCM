/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmReader.h"
#include "gdcmPrinter.h"

int TestPrinter(int argc, char *argv[])
{
  if( argc < 2 )
    {
    return 1;
    }
  gdcm::Reader r;
  r.SetFileName( argv[1] );
  r.Read();

  gdcm::Printer p;
  p.SetDataSet( r.GetDataSet() );
  p.Print( std::cout );

  return 0;
}

