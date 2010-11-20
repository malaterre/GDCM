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
#include "vtkGDCMPolyDataReader.h"
#include "vtkGDCMPolyDataWriter.h"

#include "vtkAppendPolyData.h"
#include "vtkPolyDataWriter.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkActor2D.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkMedicalImageProperties.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkCamera.h"
#include "vtkProperty.h"
#include "vtkProperty2D.h"
#include "vtkImageData.h"
#include "gdcmDirectoryHelper.h"

#include "vtkRTStructSetProperties.h"


// gdcmDataExtra/gdcmNonImageData/exRT_Structure_Set_Storage.dcm
// gdcmDataExtra/gdcmNonImageData/RTSTRUCT_1.3.6.1.4.1.22213.1.1396.2.dcm
// gdcmDataExtra/gdcmNonImageData/RT/RTStruct.dcm

using namespace gdcm;


int main(int argc, char *argv[])
{
  if( argc < 2 )
    {
    std::cerr << argv[0] << " directory-with-rtstruct-and-ct-images\n";
    return 1;
    }
  //const char * filename = argv[1];
  std::string theDirName(argv[1]);
  Directory::FilenamesType theRTSeries =
    DirectoryHelper::GetRTStructSeriesUIDs(theDirName);
  if (theRTSeries.empty()){
    std::cerr << "No RTStructs found for the test, ending." << std::endl;
    return 1;
  }

  Directory::FilenamesType theRTNames =
    DirectoryHelper::GetFilenamesFromSeriesUIDs(theDirName, theRTSeries[0]);

  vtkGDCMPolyDataReader * reader = vtkGDCMPolyDataReader::New();
  reader->SetFileName( theRTNames[0].c_str() );
  reader->Update();

  //std::cout << reader->GetMedicalImageProperties()->GetStudyDate() << std::endl;

  vtkGDCMPolyDataWriter * writer = vtkGDCMPolyDataWriter::New();
  writer->SetNumberOfInputPorts( reader->GetNumberOfOutputPorts() );
//  for(int num = 0; num < reader->GetNumberOfOutputPorts(); ++num )
//    writer->SetInput( num, reader->GetOutput(num) );
  writer->SetFileName( std::string(theDirName + "/" + "GDCMTestRTStruct." +  theRTSeries[0] + ".dcm").c_str());
  writer->SetMedicalImageProperties( reader->GetMedicalImageProperties() );
  //this line is cheating, we won't have the same stuff, and may not have a struct
  //to start with.
  //have to go back to the original data to reconstruct the RTStructureSetProperties
  //writer->SetRTStructSetProperties( reader->GetRTStructSetProperties() );
  //writer->Write();

  //loop through the outputs in order to write them out as if they had been created and appended
  Directory::FilenamesType roiNames, roiAlgorithms, roiTypes;
  for (int i = 0; i < reader->GetNumberOfOutputPorts(); ++i){
    writer->SetInput(i, reader->GetOutput(i));
    roiNames.push_back(reader->GetRTStructSetProperties()->GetStructureSetROIName(i));
    roiAlgorithms.push_back(reader->GetRTStructSetProperties()->GetStructureSetROIGenerationAlgorithm(i));
    roiTypes.push_back(reader->GetRTStructSetProperties()->GetStructureSetRTROIInterpretedType(i));
  }

  vtkRTStructSetProperties* theProperties =
    vtkRTStructSetProperties::ProduceStructureSetProperties(theDirName,
    reader->GetRTStructSetProperties()->GetStructureSetLabel(),
    reader->GetRTStructSetProperties()->GetStructureSetName(),
    writer, roiNames, roiAlgorithms, roiTypes);

  writer->SetRTStructSetProperties(theProperties);
  writer->Write();

  // print reader output:
  reader->Print( std::cout );
  // print first output:
  reader->GetOutput()->Print( std::cout );

  // Now we'll look at it.
  vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
  cubeMapper->SetInput( (vtkPolyData*)writer->GetInput() );
  cubeMapper->SetScalarRange(0,7);
  vtkActor *cubeActor = vtkActor::New();
  cubeActor->SetMapper(cubeMapper);
  vtkProperty * property = cubeActor->GetProperty();
  property->SetRepresentationToWireframe();

  vtkRenderer *renderer = vtkRenderer::New();
  vtkRenderWindow *renWin = vtkRenderWindow::New();
  renWin->AddRenderer(renderer);

  vtkRenderWindowInteractor *iren = vtkRenderWindowInteractor::New();
  iren->SetRenderWindow(renWin);

  renderer->AddActor(cubeActor);
  renderer->ResetCamera();
  renderer->SetBackground(1,1,1);

  renWin->SetSize(300,300);

  renWin->Render();
  iren->Start();

  reader->Delete();
//  append->Delete();
  cubeMapper->Delete();
  cubeActor->Delete();
  renderer->Delete();
  renWin->Delete();
  iren->Delete();

  writer->Delete();

  return 0;
}
