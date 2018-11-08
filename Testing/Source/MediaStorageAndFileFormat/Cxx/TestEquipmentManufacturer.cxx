/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmEquipmentManufacturer.h"
#include "gdcmReader.h"

#include "gdcmTesting.h"

static int TestEquipmentManufacturerFunc(const char* filename, bool verbose = false)
{
  if( verbose )
    std::cerr << "Reading: " << filename << std::endl;
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    std::cerr << "TestReadError: Failed to read: " << filename << std::endl;
    return 1;
    }

  const gdcm::File & file = reader.GetFile();
  const gdcm::DataSet & ds = file.GetDataSet();
  gdcm::EquipmentManufacturer::Type manufacturer = gdcm::EquipmentManufacturer::Compute( ds );
  if( manufacturer == gdcm::EquipmentManufacturer::UNKNOWN ) return 1;


  return 0;
}


int TestEquipmentManufacturer(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestEquipmentManufacturerFunc(filename, true);
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
    r += TestEquipmentManufacturerFunc(filename);
    ++i;
    }

  return r;
}
