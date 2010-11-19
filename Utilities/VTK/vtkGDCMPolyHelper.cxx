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

/*
 This class is designed to help in writing out information in the vtkGDCMPolyDataWriter
 class.  However, the general functionality (ie, the ability to load all known
 CT/MR series in a directory) may be generally useful, so I've excised it.  For 
 now, it's in the vtk utilities directory, but could be put somewhere else.
 name and date: 18 Nov 2010 mmr
 */
 
 #include "vtkGDCMPolyHelper.h"
 #include "gdcmDirectory.h"
 #include "gdcmScanner.h"
 #include "gdcmDataSet.h"
 #include "gdcmReader.h"
 #include "gdcmIPPSorter.h"
 #include "gdcmAttribute.h"
 
 using namespace gdcm;

//given an SOPClassUID, get the number of series that are that SOP Class
//that is, the MR images, the CT Images, whatever.  Just have to be sure to give the proper
//SOP Class UID.
//returns an empty vector if nothing's there or if something goes wrong.
Directory::FilenamesType vtkGDCMPolyHelper::GetSeriesUIDsBySOPClassUID(const std::string& inDirectory, 
                                                                       const std::string& inSOPClassUID)
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


//given the name of a directory, return the list of CT Image UIDs
Directory::FilenamesType vtkGDCMPolyHelper::GetCTImageSeriesUIDs(const std::string& inDirectory)
{
  return GetSeriesUIDsBySOPClassUID(inDirectory, "1.2.840.10008.5.1.4.1.1.2");
}

//given the name of a directory, return the list of CT Image UIDs
Directory::FilenamesType vtkGDCMPolyHelper::GetMRImageSeriesUIDs(const std::string& inDirectory)
{
  return GetSeriesUIDsBySOPClassUID(inDirectory, "1.2.840.10008.5.1.4.1.1.4");
}


//the code in GetSeriesUIDsBySOPClassUID will enumerate the CT images in a directory
//This code will retrieve an image by its Series UID.
//this code doesn't return pointers or smart pointers because it's intended to 
//be easily wrapped by calling languages that don't know pointers (ie, Java)
//this function is a proof of concept
//for it to really work, it needs to also 
std::vector<DataSet> vtkGDCMPolyHelper::LoadImageFromFiles(const std::string& inDirectory,
                                                           const std::string& inSeriesUID)
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
          gdcmWarningMacro("Unable to sort Image Files.");
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


//When writing RTStructs, each contour will have z position defined.
//use that z position to determine the SOPInstanceUID for that plane.
std::string vtkGDCMPolyHelper::RetrieveSOPInstanceUIDFromZPosition(double inZPos,
                                                const std::vector<DataSet>& inDS)
{
  std::vector<DataSet>::const_iterator itor;
  gdcm::Tag thePosition(0x0020, 0x0032);
  gdcm::Tag theSOPInstanceUID(0x0008, 0x0018);
  std::string blank;//return only if there's a problem
  for (itor < inDS.begin(); itor != inDS.end(); itor++){
    if (itor->FindDataElement(thePosition)){
      DataElement de = itor->GetDataElement(thePosition);
      gdcm::Attribute<0x0020,0x0032> at;
      at.SetFromDataElement( de );
      if (fabs(at.GetValue(2) < inZPos)<0.01){
        DataElement de2 = itor->GetDataElement(theSOPInstanceUID);
        std::string theReturn(de2.GetByteValue()->GetPointer());
        return theReturn;
      }
    }
  }
  return blank;
}

//When writing RTStructs, the frame of reference is done by planes to start with
std::string vtkGDCMPolyHelper::RetrieveSOPInstanceUIDFromIndex(int inIndex,
                                                               const std::vector<DataSet>& inDS)
{
  
  gdcm::Tag theSOPInstanceUID(0x0008, 0x0018);
  std::string blank;//return only if there's a problem
  if (inDS[inIndex].FindDataElement(theSOPInstanceUID)){
    DataElement de = inDS[inIndex].GetDataElement(theSOPInstanceUID);
    std::string theReturn(de.GetByteValue()->GetPointer());
    return theReturn;
  }
  return blank;
}

//each plane needs to know the SOPClassUID, and that won't change from image to image
//so, retrieve this once at the start of writing.
std::string vtkGDCMPolyHelper::GetSOPClassUID(const std::vector<DataSet>& inDS)
{
  gdcm::Tag theSOPClassUID(0x0008, 0x0016);
  std::string blank;//return only if there's a problem
  if (inDS[0].FindDataElement(theSOPClassUID)){
    DataElement de = inDS[0].GetDataElement(theSOPClassUID);
    std::string theReturn(de.GetByteValue()->GetPointer());
    return theReturn;
  }
  return blank;
}

//retrieve the frame of reference from the set of datasets
std::string vtkGDCMPolyHelper::GetFrameOfReference(const std::vector<DataSet>& inDS){
  
  gdcm::Tag theSOPClassUID(0x0020, 0x0052);
  std::string blank;//return only if there's a problem
  if (inDS[0].FindDataElement(theSOPClassUID)){
    DataElement de = inDS[0].GetDataElement(theSOPClassUID);
    std::string theReturn(de.GetByteValue()->GetPointer());
    return theReturn;
  }
  return blank;
}