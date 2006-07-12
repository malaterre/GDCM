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
#include "gdcmWriter.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"

#include "gdcmDataImages.h"

int TestWrite(const char* filename)
{
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    std::cerr << "Failed to read: " << filename << std::endl;
    return 1;
    }

  gdcm::Filename out(filename);
  std::string tmpdir = "/tmp/debug";
  std::string outfilename = tmpdir;
  outfilename += "/";
  outfilename += out.GetName();

  gdcm::Writer writer;
  writer.SetFileName( outfilename.c_str() );
  writer.SetPreamble( reader.GetPreamble() );
  writer.SetHeader( reader.GetHeader() );
  writer.SetDataSet( reader.GetDataSet() );
  if( !writer.Write() )
    {
    std::cerr << "Failed to write: " << outfilename << std::endl;
    return 1;
    }

  // Ok we have now two files let's compare their md5 sum:
  bool b = gdcm::System::CompareMD5(filename, outfilename.c_str());
  if( b )
    {
    std::cerr << filename << " and "
      << outfilename << " are different\n";
    return 1;
    }
  else
    {
    std::cerr << filename << " and "
      << outfilename << " are identical\n";
    return 0;
    }
}

int TestWriter(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestWrite(filename);
    }

  // else
  int r = 0, i = 0;
  const char *filename;
  while( (filename = gdcmDataImages[i]) )
    {
    r += TestWrite( filename );
    ++i;
    }

  return r;
}
