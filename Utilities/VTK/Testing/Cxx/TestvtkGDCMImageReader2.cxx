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
#include "vtkImageData.h"
#include "vtkImageChangeInformation.h"

#include "gdcmFilename.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"
#include "gdcmTrace.h"
#include "gdcmDirectory.h"
#include "gdcmIPPSorter.h"

/*
 * Test to show the pipeline for 
 * IPPSorter -> vtkGDCMImageReader -> vtkImageChangeInformation
 */
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
  double ippzspacing = s.GetZSpacing();
  if( ippzspacing != 5.5 )
  {
	  // This should be test in another specific test ...
	  return 1;
  }

  const std::vector<std::string> & sorted = s.GetFilenames();
  vtkGDCMImageReader * reader = vtkGDCMImageReader::New();
  vtkStringArray *files = vtkStringArray::New();
  std::vector< std::string >::const_iterator it = sorted.begin();
  for( ; it != sorted.end(); ++it)
  {
	  const std::string &f = *it;
  files->InsertNextValue( f.c_str() );
  }
  reader->SetFileNames( files );
  reader->Update();

  const double *spacing = reader->GetOutput()->GetSpacing();
  std::cout << spacing[0] << "," << spacing[1] << "," << spacing[2] << std::endl;
  int ret = 0;
  if( spacing[2] != 0.5 )
  {
	  // Spacing Between Slice is set to 0.5 in those files
	  ret++;
  }

  // try again but this time we want 5.5 to be the spacing
  vtkGDCMImageReader * reader2 = vtkGDCMImageReader::New();
  reader2->SetDataSpacing( spacing[0], spacing[1], ippzspacing );
  reader2->SetFileNames( files );
  reader2->Update();
  const double *spacing2 = reader2->GetOutput()->GetSpacing();
  std::cout << spacing2[0] << "," << spacing2[1] << "," << spacing2[2] << std::endl;
  // You need to use this class to preserve spacing
  // across pipeline re-execution
  vtkImageChangeInformation *change = vtkImageChangeInformation::New();
  change->SetInput( reader2->GetOutput() );
  change->SetOutputSpacing( spacing2[0], spacing2[1], ippzspacing );
  change->Update();

  const double *spacing3 = change->GetOutput()->GetSpacing();
  std::cout << spacing3[0] << "," << spacing3[1] << "," << spacing3[2] << std::endl;
  if( spacing3[2] != 5.5 )
  {
	  ret++;
  }
  
  change->Delete();
  reader->Delete();
  files->Delete();

  return ret;
}
