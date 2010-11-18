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
#include "gdcmDirectory.h"
#include "gdcmScanner.h"
#include "vtkGDCMImageReader.h"
#include "gdcmIPPSorter.h"
#include "vtkStringArray.h"
#include "vtkSmartPointer.h"
#include "gdcmImageReader.h"
#include "vtkRTStructSetProperties.h"

// gdcmDataExtra/gdcmNonImageData/exRT_Structure_Set_Storage.dcm
// gdcmDataExtra/gdcmNonImageData/RTSTRUCT_1.3.6.1.4.1.22213.1.1396.2.dcm
// gdcmDataExtra/gdcmNonImageData/RT/RTStruct.dcm

using namespace gdcm;


//given an SOPClassUID, get the number of series that are that SOP Class
//that is, the MR images, the CT Images, whatever.  Just have to be sure to give the proper
//SOP Class UID.
//returns an empty vector if nothing's there or if something goes wrong.
Directory::FilenamesType GetSeriesUIDsBySOPClassUID(std::string inDirectory, std::string inSOPClassUID)
{
  gdcm::Scanner theScanner;
  gdcm::Directory theDir;
  theScanner.AddTag(Tag(0x0008, 0x0016));//SOP Class UID
  theScanner.AddTag(Tag(0x0020, 0x000e));//Series UID
  Directory::FilenamesType theReturn;
  
  try {
    theDir.Load(inDirectory);
    theScanner.Scan(theDir.GetFilenames());
    
    //now find all series UIDs
    Directory::FilenamesType theSeriesValues = theScanner.GetOrderedValues(Tag(0x0020,0x000e));
    
    //now count the number of series that are of that given SOPClassUID
    int theNumSeries = theSeriesValues.size();
    for (int i = 0; i < theNumSeries; i++){
      std::string theFirstFilename =
        theScanner.GetFilenameFromTagToValue(Tag(0x0020,0x000e), theSeriesValues[0].c_str());
      if (theScanner.GetValue(theFirstFilename.c_str(), Tag(0x0008,0x0016)) == inSOPClassUID.c_str()){
        theReturn.push_back(theSeriesValues[0]);
      }
    }
    return theReturn;
  } catch (...){
    Directory::FilenamesType theBlank;
    return theBlank;//something broke during scanning
  }
}

//given the name of a directory, return the list of RTStruct Series UIDs
Directory::FilenamesType GetRTStructSeriesUIDs(std::string inDirectory)
{
  return GetSeriesUIDsBySOPClassUID(inDirectory, "1.2.840.10008.5.1.4.1.1.481.3");
}

//given the name of a directory, return the list of CT Image UIDs
Directory::FilenamesType GetCTImageSeriesUIDs(std::string inDirectory)
{
  return GetSeriesUIDsBySOPClassUID(inDirectory, "1.2.840.10008.5.1.4.1.1.2");
}

//the code in GetSeriesUIDsBySOPClassUID will enumerate the CT images in a directory
//This code will retrieve an image by its Series UID.
//this code doesn't return pointers or smart pointers because it's intended to 
//be easily wrapped by calling languages that don't know pointers (ie, Java)
//this function is a proof of concept
//for it to really work, it needs to also 
std::vector<DataSet> LoadCTImageFromFiles(std::string inDirectory, std::string inSeriesUID)
{
  gdcm::Scanner theScanner;
  gdcm::Directory theDir;
  theScanner.AddTag(Tag(0x0020, 0x000e));//Series UID
  std::vector<DataSet> theReturn;
  std::vector<DataSet> blank;//returned in case of an error
  
  try {
    theDir.Load(inDirectory);
    theScanner.Scan(theDir.GetFilenames());
    
    //now find all series UIDs
    Directory::FilenamesType theSeriesValues = theScanner.GetOrderedValues(Tag(0x0020,0x000e));
    
    //now count the number of series that are of that given SOPClassUID
    int theNumSeries = theSeriesValues.size();
    for (int i = 0; i < theNumSeries; i++){
      if (inSeriesUID == theSeriesValues[0]){
        //find all files that have that series UID, and then load them via 
        //the vtkImageReader
        Directory::FilenamesType theFiles =
          theScanner.GetAllFilenamesFromTagToValue(Tag(0x0020, 0x000e), theSeriesValues[0].c_str());
        IPPSorter sorter;
        sorter.SetComputeZSpacing(true);
        sorter.SetZSpacingTolerance(0.000001);
        if (!sorter.Sort(theFiles)){
          gdcmWarningMacro("Unable to sort CT Image Files.");
          return blank;
        }
        Directory::FilenamesType theSortedFiles = sorter.GetFilenames();
        for (unsigned long j = 0; j < theSortedFiles.size(); ++j){
          Reader theReader;
          theReader.SetFileName(theSortedFiles[j].c_str());
          theReader.Read();
          theReturn.push_back(theReader.GetFile().GetDataSet());
        }
        return theReturn;
      }
    }
    return blank;
  } catch (...){
    gdcmWarningMacro("Something went wrong reading CT images.");
    return blank;
  }
}

//the gdcm rtstruct reader works fine with a single filename
//obtain the filename from a series UID
//this way, a single directory can be read and parsed from a single command line argument
std::string FindRTStructFileNameBySeriesUID(std::string inDirectory, std::string inSeriesUID)
{
  gdcm::Scanner theScanner;
  gdcm::Directory theDir;
  theScanner.AddTag(Tag(0x0020, 0x000e));//Series UID
  std::string blank;//returned in case of an error
  
  try {
    theDir.Load(inDirectory);
    theScanner.Scan(theDir.GetFilenames());
    
    //now find all series UIDs
    Directory::FilenamesType theSeriesValues = theScanner.GetOrderedValues(Tag(0x0020,0x000e));
    
    //now count the number of series that are of that given SOPClassUID
    int theNumSeries = theSeriesValues.size();
    for (int i = 0; i < theNumSeries; i++){
      if (inSeriesUID == theSeriesValues[0]){
        //find all files that have that series UID, and then load them via 
        //the vtkImageReader
        Directory::FilenamesType theFiles =
        theScanner.GetAllFilenamesFromTagToValue(Tag(0x0020, 0x000e), theSeriesValues[0].c_str());
        
        if (theFiles.size() == 1){
          return theFiles[0];
        } else {
          if (theFiles.size() > 1){
            gdcmWarningMacro("Multiple RT Struct files share the same Series UID, loading the first one.");
            return theFiles[0];
          } else{
            gdcmWarningMacro("This shouldn't happen, but no rtstructs were found.");
            return blank;
          }
        }
      }
    }
    return blank;
  } catch (...){
    gdcmWarningMacro("Something went wrong reading CT images.");
    return blank;
  }
}

//the function LoadCTImageFromFiles gives us a list of images in IPP-sorted order for 
//constructing rt structures
//(that need both the z position and the appropriate SOP Instance UID for a plane)
//so, armed with that list of points and the list of images, the first point in 
//each polydata object can be appropriately compiled into the rtstruct
vtkRTStructSetProperties* ProduceStructureSetProperties(std::string inDirectory,
                                                        vtkAppendPolyData* inPolyData)
{
  Directory::FilenamesType theCTSeries = GetCTImageSeriesUIDs(inDirectory);
  if (theCTSeries.size() > 1){
    gdcmWarningMacro("More than one CT series detected, only reading series UID: " << theCTSeries[0]);
  }
  if (theCTSeries.empty()){
    gdcmWarningMacro("No CT Series found, stopping.");
    return NULL;
  }
  //load the images in the CT series
  std::vector<DataSet> theCTDataSets = LoadCTImageFromFiles(inDirectory, theCTSeries[0]);
  if (theCTDataSets.empty()){
    gdcmWarningMacro("No CT Images loaded, stopping.");
    return NULL;
  }
  
  //now, armed with this set of images, we can begin to properly construct the RTStructureSet
  vtkRTStructSetProperties* theRTStruct = vtkRTStructSetProperties::New();
  //theRTStruct->SetSOPInstanceUID(<#const char *_arg#>);//should be autogenerated by the object itself
  theRTStruct->SetStudyInstanceUID(theCTDataSets[0].FindNextDataElement(Tag(0x0020,0x000d)).GetByteValue()->GetPointer());
  //the series UID should be set automatically, and happen during creation
  theRTStruct->SetReferenceSeriesInstanceUID(theCTDataSets[0].FindNextDataElement(Tag(0x0020,0x000e)).GetByteValue()->GetPointer());
  theRTStruct->SetReferenceFrameOfReferenceUID(theCTDataSets[0].FindNextDataElement(Tag(0x0020,0x0052)).GetByteValue()->
  GetPointer());
  //set the date and time to be now
  
  char date[22];
  const size_t datelen = 8;
  int res = System::GetCurrentDateTime(date);
  assert( res );
  (void)res;//warning removal
  //the date is the first 8 chars 
  std::string dateString;
  std::copy(&(date[0]), &(date[datelen]), dateString.begin());
  theRTStruct->SetStructureSetDate(dateString.c_str());
  std::string timeString;
  const size_t timelen = 6; //for now, only need hhmmss
  std::copy(&(date[datelen]), &(date[datelen+timelen]), timeString.begin());
  theRTStruct->SetStructureSetTime(timeString.c_str());
  
  //now, we have go to through each vtkPolyData, assign the ROI names per polydata, and then also assign the
  //reference SOP instance UIDs on a per-plane basis.
  for (int i = 0; i < inPolyData->GetNumberOfOutputPorts(); i++){
    
  }
  

  return theRTStruct;
}



int main(int argc, char *argv[])
{
  if( argc < 2 )
    {
    std::cerr << argv[0] << " filename1.dcm\n";
    return 1;
    }
  const char * filename = argv[1];

  vtkGDCMPolyDataReader * reader = vtkGDCMPolyDataReader::New();
  reader->SetFileName( filename );
  reader->Update();

  //std::cout << reader->GetMedicalImageProperties()->GetStudyDate() << std::endl;

  vtkGDCMPolyDataWriter * writer = vtkGDCMPolyDataWriter::New();
  writer->SetNumberOfInputPorts( reader->GetNumberOfOutputPorts() );
  for(int num = 0; num < reader->GetNumberOfOutputPorts(); ++num )
    writer->SetInput( num, reader->GetOutput(num) );
  writer->SetFileName( "rtstruct.dcm" );
  writer->SetMedicalImageProperties( reader->GetMedicalImageProperties() );
  //this line is cheating, we won't have the same stuff, and may not have a struct
  //to start with.
  //have to go back to the original data to reconstruct the RTStructureSetProperties
  //writer->SetRTStructSetProperties( reader->GetRTStructSetProperties() );
  //writer->Write();

  // print reader output:
  reader->Print( std::cout );
  // print first output:
  reader->GetOutput()->Print( std::cout );

  vtkAppendPolyData *append = vtkAppendPolyData::New();
  int n = reader->GetNumberOfOutputPorts();
  for(int i = 0; i < n; ++i)
    {
    append->AddInput( reader->GetOutput(i) );
    }

  // Now we'll look at it.
  vtkPolyDataMapper *cubeMapper = vtkPolyDataMapper::New();
  cubeMapper->SetInput( append->GetOutput() );
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
  append->Delete();
  cubeMapper->Delete();
  cubeActor->Delete();
  renderer->Delete();
  renWin->Delete();
  iren->Delete();

  writer->Delete();

  return 0;
}
