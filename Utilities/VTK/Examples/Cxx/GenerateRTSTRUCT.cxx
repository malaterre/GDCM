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
#include "vtkGDCMPolyDataWriter.h"

#include "vtkPolyData.h"
#include "vtkPolyDataReader.h"
#include "vtkMedicalImageProperties.h"
#include "vtkRTStructSetProperties.h"

int main(int argc, char *argv[])
{
#if 0
  const char *input = "/home/mathieu/Kitware/VTKData/Data/hello.vtk";

  vtkPolyDataReader *reader = vtkPolyDataReader::New();
  reader->SetFileName( input );
  reader->Update();
  vtkPolyData *pd = reader->GetOutput(); // vtkPolyData::New();
#else
  vtkPolyData *pd = vtkPolyData::New();
#endif

  const char * filename = argv[1];

  int numinput = 1;
  vtkMedicalImageProperties *iprop = vtkMedicalImageProperties::New();
  vtkRTStructSetProperties *rtprop = vtkRTStructSetProperties::New();

  vtkGDCMPolyDataWriter * writer = vtkGDCMPolyDataWriter::New();
  writer->SetNumberOfInputPorts( numinput );
  for(int num = 0; num < numinput; ++num )
    writer->SetInput( num, pd );
  writer->SetFileName( filename );
  writer->SetMedicalImageProperties( iprop );
  writer->SetRTStructSetProperties( rtprop );
  writer->Write();

  return 0;
}
