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
#include "vtkGDCMImageReader.h"
#include "vtkStringArray.h"

#include "gdcmFilename.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"
#include "gdcmTrace.h"
#include "gdcmDirectory.h"
#include "gdcmIPPSorter.h"

int TestvtkGDCMImageReader2(int argc, char *argv[])
{
  const char *directory = gdcm::Testing::GetDataRoot();
  std::vector<std::string> filenames;
    std::string file0 = std::string(directory) + "/SIEMENS_MAGNETOM-12-MONO2-FileSeq0.dcm";
    std::string file1 = std::string(directory) + "/SIEMENS_MAGNETOM-12-MONO2-FileSeq1.dcm";
    std::string file2 = std::string(directory) + "/SIEMENS_MAGNETOM-12-MONO2-FileSeq2.dcm";
    std::string file3 = std::string(directory) + "/SIEMENS_MAGNETOM-12-MONO2-FileSeq3.dcm";
    filenames.push_back( file1 );
    filenames.push_back( file3 );
    filenames.push_back( file2 );
    filenames.push_back( file0 );
      gdcm::IPPSorter s;
  s.SetComputeZSpacing( true );
  s.SetZSpacingTolerance( 1e-10 );
  bool b = s.Sort( filenames );
  if( !b )
    {
    std::cerr << "Failed to sort:" << directory << std::endl;
    return 1;
    }
  std::cout << "Sorting succeeded:" << std::endl;
  s.Print( std::cout );

  std::cout << "Found z-spacing:" << std::endl;
  std::cout << s.GetZSpacing() << std::endl;

  const std::vector<std::string> & sorted = s.GetFilenames();
  vtkGDCMImageReader * reader = vtkGDCMImageReader::New();
  vtkStringArray *files = vtkStringArray::New();
  std::vector< std::string >::const_iterator it = sorted.begin();
  for( ; it != sorted.end(); ++it)
  {
	  const std::string &f = *it;
  files->InsertNextValue( f.c_str() );
  }


  
  reader->Delete();
  return 0;
}
