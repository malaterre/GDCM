/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmAnonymizer.h"
#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmTesting.h"
#include "gdcmSystem.h"
#include "gdcmUIDGenerator.h"

namespace gdcm
{
static int TestAnonymize(const char *subdir, const char* filename)
{
  Reader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    return 1;
    }

  Anonymizer anonymizer;
  anonymizer.SetFile( reader.GetFile() );
  // Setup some actions:
  const char empty[] = "";
  const PrivateTag ptag1 = PrivateTag(0x0029,0x20,"SIEMENS MEDCOM HEADER");
  const PrivateTag ptag2 = PrivateTag(0x0029,0x60,"SIEMENS MEDCOM HEADER2");
  const PrivateTag ptag3 = PrivateTag(0x0029,0x10,"SIEMENS CSA HEADER");
  anonymizer.Replace( ptag1 , empty );
  anonymizer.Remove( ptag2 );
  anonymizer.Empty( ptag3 );
  anonymizer.Clear( ptag3 );

  // Create directory first:
  std::string tmpdir = Testing::GetTempDirectory( subdir );
  if( !System::FileIsDirectory( tmpdir.c_str() ) )
    {
    System::MakeDirectory( tmpdir.c_str() );
    //return 1;
    }
  std::string outfilename = Testing::GetTempFilename( filename, subdir );

  Writer writer;
  writer.SetFileName( outfilename.c_str() );
  writer.SetFile( reader.GetFile() );
  writer.SetCheckFileMetaInformation( false );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }
  std::cout << "Success to write: " << outfilename << std::endl;

  // now let's try to read it back in:
  Reader reader2;
  reader2.SetFileName( outfilename.c_str() );
  if ( !reader2.Read() )
    {
    std::cerr << "Could not reread written file: " << outfilename << std::endl;
    return 1;
    }

  const DataSet & ds = reader.GetFile().GetDataSet();
  //std::cout << ds << std::endl;

  const ByteValue *bv = ds.GetDataElement( ptag2 ).GetByteValue();
  if( !bv )
    {
    return 1;
    }
  if( bv->GetLength() != 0 )
    {
    return 1;
    }

  return 0;
}
}

int TestAnonymizer4(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return gdcm::TestAnonymize(argv[0], filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += gdcm::TestAnonymize( argv[0], filename );
    ++i;
    }

  return r;
}
