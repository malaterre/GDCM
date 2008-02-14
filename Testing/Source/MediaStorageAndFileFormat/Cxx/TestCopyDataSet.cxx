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
#include "gdcmReader.h"
#include "gdcmDataSet.h"

int TestCopyDataSet(int, char *[])
{
  const char filename[] = GDCM_DATA_ROOT "/test.acr";
  gdcm::Reader reader;
  reader.SetFileName( filename );
  if ( !reader.Read() )
    {
    return 1;
    }

  const gdcm::DataSet &ds = reader.GetFile().GetDataSet();

  gdcm::DataSet ds_copy = ds;
  std::cout << ds_copy << std::endl;

  return 0;
}
