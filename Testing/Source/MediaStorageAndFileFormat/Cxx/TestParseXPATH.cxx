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
#include "gdcmReader.h"
#include "gdcmDataSet.h"
#include "gdcmDict.h"
#include "gdcmDicts.h"
#include "gdcmGlobal.h"
#include "gdcmStringFilter.h"
#include "gdcmTesting.h"

int TestParseXPATHFile(const char* filename, bool verbose = false )
{
  static gdcm::Global &g = gdcm::Global::GetInstance();
  static const gdcm::Dicts &dicts = g.GetDicts();
  static const gdcm::Dict &pubdict = dicts.GetPublicDict();

  gdcm::Reader reader;
//  reader.SetFileName( "/home/mathieu/Creatis/gdcmData/D_CLUNIE_CT1_J2KI.dcm" );
  reader.SetFileName( filename );
  if( !reader.Read() )
    {
    return 1;
    }

  gdcm::StringFilter sf;
  sf.SetFile( reader.GetFile() );

  const char query_const[] = "/DicomNativeModel/DicomAttribute[@keyword='DerivationCodeSequence']/Item[@number=1]//DicomAttribute[@keyword='CodeMeaning']/Value[@number=1]";

  std::string value;
  bool ret = sf.ExecuteQuery( query_const, value );

  if( !ret )
    {
    return 1;
    }
  if( verbose )
    std::cout << "Res: " << value << std::endl;

  return 0;
}

int TestParseXPATH(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestParseXPATHFile(filename, true);
    }

  // else
  // First of get rid of warning/debug message
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestParseXPATHFile( filename);
    ++i;
    }
  return EXIT_SUCCESS;
}
