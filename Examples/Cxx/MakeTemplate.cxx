/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#include "gdcmFileAnonymizer.h"

int main(int argc, char *argv[])
{
  const char* filename = argv[1];
  const char* outfilename = argv[2];

  gdcm::Trace::DebugOn();

  gdcm::FileAnonymizer fa;
  fa.SetInputFileName( filename );
  fa.SetOutputFileName( outfilename );

  fa.Empty( gdcm::Tag(0x7fe0,0x10) );
  //fa.Empty( gdcm::Tag(0x10,0x10) );

  if( !fa.Write() )
    {
    std::cerr << "impossible to remove Pixel Data attribute" << std::endl;
    return 1;
    }

  return 0;
}
