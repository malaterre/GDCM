/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkMedicalImageProperties.cxx,v

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkRTStructSetProperties.h"
#include "vtkObjectFactory.h"
#include "vtkAppendPolyData.h"

#include "gdcmDirectory.h"
#include "gdcmScanner.h"
#include "gdcmDataSet.h"
#include "gdcmReader.h"
#include "gdcmIPPSorter.h"
#include "gdcmAttribute.h"

#include <string>
#include <map>
#include <vector>
#include <set>
#include <time.h> // for strftime
#include <ctype.h> // for isdigit
#include <assert.h>

//----------------------------------------------------------------------------
vtkCxxRevisionMacro(vtkRTStructSetProperties, "1.21")
vtkStandardNewMacro(vtkRTStructSetProperties)

namespace gdcm
{
class vtkGDCMPolyHelper
{
  friend class vtkRTStructSetProperties;
public:
  //returns all series UIDs in a given directory that match a particular SOP Instance UID
  static Directory::FilenamesType GetSeriesUIDsBySOPClassUID(const std::string& inDirectory,
    const std::string& inSOPClassUID);

  //specific implementations of the SOPClassUID grabber, so you don't have to
  //remember the SOP Class UIDs of CT or MR images.
  static Directory::FilenamesType GetCTImageSeriesUIDs(const std::string& inDirectory);
  static Directory::FilenamesType GetMRImageSeriesUIDs(const std::string& inDirectory);

  //given a series UID, load all the images associated with that series UID
  //these images will be IPP sorted, so that they can be used for gathering all
  //the necessary information for generating an RTStruct
  //this function should be called by the writer once, if the writer's dataset
  //vector is empty.  Make sure to have a new writer for new rtstructs.
  static std::vector<DataSet> LoadImageFromFiles(const std::string& inDirectory,
    const std::string& inSeriesUID);

  //When writing RTStructs, each contour will have z position defined.
  //use that z position to determine the SOPInstanceUID for that plane.
  static std::string RetrieveSOPInstanceUIDFromZPosition(double inZPos,
    const std::vector<DataSet>& inDS);

  //When writing RTStructs, the frame of reference is done by planes to start with
  static std::string RetrieveSOPInstanceUIDFromIndex(int inIndex,
   const std::vector<DataSet>& inDS);

  //each plane needs to know the SOPClassUID, and that won't change from image to image
  //so, retrieve this once at the start of writing.
  static std::string GetSOPClassUID(const std::vector<DataSet>& inDS);

  //retrieve the frame of reference from the set of datasets
  static std::string GetFrameOfReference(const std::vector<DataSet>& inDS);
};

//given an SOPClassUID, get the number of series that are that SOP Class
//that is, the MR images, the CT Images, whatever.  Just have to be sure to give the proper
//SOP Class UID.
//returns an empty vector if nothing's there or if something goes wrong.
gdcm::Directory::FilenamesType vtkGDCMPolyHelper::GetSeriesUIDsBySOPClassUID(const std::string& inDirectory,
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
gdcm::Directory::FilenamesType vtkGDCMPolyHelper::GetCTImageSeriesUIDs(const std::string& inDirectory)
{
  return GetSeriesUIDsBySOPClassUID(inDirectory, "1.2.840.10008.5.1.4.1.1.2");
}

//given the name of a directory, return the list of CT Image UIDs
gdcm::Directory::FilenamesType vtkGDCMPolyHelper::GetMRImageSeriesUIDs(const std::string& inDirectory)
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
} // end namespace gdcm

//the function LoadCTImageFromFiles gives us a list of images in IPP-sorted order for
//constructing rt structures
//(that need both the z position and the appropriate SOP Instance UID for a plane)
//so, armed with that list of points and the list of images, the first point in
//each polydata object can be appropriately compiled into the rtstruct
//we use appendpolydata here-- each polydata is an organ
//NOTE: the number of outputs for the appendpolydata MUST MATCH the organ vectors!
vtkRTStructSetProperties* vtkRTStructSetProperties::ProduceStructureSetProperties(const std::string& inDirectory,
                                                                           const std::string& inStructLabel,
                                                                           const std::string& inStructName,
                                                                           vtkAppendPolyData* inPolyData,//should also have colors
                                                                           gdcm::Directory::FilenamesType inROINames,
                                                                           gdcm::Directory::FilenamesType inROIAlgorithmName,
                                                                           gdcm::Directory::FilenamesType inROIType)
{
  using namespace gdcm;
  gdcm::Directory::FilenamesType theCTSeries =
    gdcm::vtkGDCMPolyHelper::GetCTImageSeriesUIDs(inDirectory);
  if (theCTSeries.size() > 1){
    gdcmWarningMacro("More than one CT series detected, only reading series UID: " << theCTSeries[0]);
  }
  if (theCTSeries.empty()){
    gdcmWarningMacro("No CT Series found, trying MR.");
    theCTSeries = gdcm::vtkGDCMPolyHelper::GetMRImageSeriesUIDs(inDirectory);
    if (theCTSeries.size() > 1){
      gdcmWarningMacro("More than one MR series detected, only reading series UID: " << theCTSeries[0]);
    }
    if (theCTSeries.empty()){
      gdcmWarningMacro("No CT or MR series found, throwing.");
      return NULL;
    }
  }
  //load the images in the CT series
  std::vector<DataSet> theCTDataSets = gdcm::vtkGDCMPolyHelper::LoadImageFromFiles(inDirectory, theCTSeries[0]);
  if (theCTDataSets.empty()){
    gdcmWarningMacro("No CT or MR Images loaded, throwing.");
    return NULL;
  }

  //now, armed with this set of images, we can begin to properly construct the RTStructureSet
  vtkRTStructSetProperties* theRTStruct = vtkRTStructSetProperties::New();
  theRTStruct->SetStructureSetLabel(inStructLabel.c_str());
  theRTStruct->SetStructureSetName(inStructName.c_str());
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

  //for each image, we need to fill in the sop class and instance UIDs for the frame of reference
  std::string theSOPClassID = vtkGDCMPolyHelper::GetSOPClassUID(theCTDataSets).c_str();
  for (unsigned long i = 0; i < theCTDataSets.size(); i++){
    theRTStruct->AddContourReferencedFrameOfReference(i, theSOPClassID.c_str(),
      vtkGDCMPolyHelper::RetrieveSOPInstanceUIDFromIndex(i,theCTDataSets).c_str());
  }

  //now, we have go to through each vtkPolyData, assign the ROI names per polydata, and then also assign the
  //reference SOP instance UIDs on a per-plane basis.
  for (int j = 0; j < inPolyData->GetNumberOfOutputPorts(); j++){
    theRTStruct->AddStructureSetROI(j,
      theRTStruct->GetReferenceFrameOfReferenceUID(),
      inROINames[j].c_str(),
      inROIAlgorithmName[j].c_str());
    theRTStruct->AddStructureSetROIObservation(j,
     j, inROIType[j].c_str(), "");
     //for each organ, gotta go through and add in the right planes in the
     //order that the tuples appear, as well as the colors
     //right now, each cell in the vtkpolydata is a contour in an xy plane
     //that's what MUST be passed in
    vtkPolyData* theData = inPolyData->GetOutput(j);
    if (theData->GetPoints() == NULL || theData->GetNumberOfPoints() == 0)
      continue; //not sure this can happen, but hey
    //use the first point in each plane.
    //theRTStruct->SetContourReferencedFrameOfReferenceSize(theData->GetNumberOfPoints());
    for (int k = 0; k < theData->GetNumberOfPoints(); k++){
      vtkPoints* thePoints = theData->GetPoints();
      if (thePoints->GetNumberOfPoints() < 1) continue;
      double* thePoint = thePoints->GetPoint(0);
      double theZ = thePoint[2];
      std::string theSOPInstance = vtkGDCMPolyHelper::RetrieveSOPInstanceUIDFromZPosition(theZ, theCTDataSets);
      //j is correct here, because it's adding, as in there's an internal vector
      //that's growing.
      theRTStruct->AddContourReferencedFrameOfReference(j, theSOPInstance.c_str(), theSOPClassID.c_str());
    }
  }


  return theRTStruct;
}
struct StructureSetROI
{
  int ROINumber;
  std::string RefFrameRefUID;
  std::string ROIName;
  std::string ROIGenerationAlgorithm;

  // (3006,0080) SQ (Sequence with undefine)# u/l, 1 RTROIObservationsSequence
  // (3006,0082) IS [0]                     #   2, 1 ObservationNumber
  // (3006,0084) IS [0]                     #   2, 1 ReferencedROINumber
  // (3006,00a4) CS [ORGAN]                 #   6, 1 RTROIInterpretedType
  // (3006,00a6) PN (no value available)    #   0, 0 ROIInterpreter
  int ObservationNumber;
  // RefROI is AFAIK simply ROINumber
  std::string RTROIInterpretedType;
  std::string ROIInterpreter;
};

//----------------------------------------------------------------------------
class vtkRTStructSetPropertiesInternals
{
public:
  void Print(ostream &os, vtkIndent indent)
    {
    }
  void DeepCopy(vtkRTStructSetPropertiesInternals *p)
    {
    ReferencedFrameOfReferences = p->ReferencedFrameOfReferences;
    }
  vtkIdType GetNumberOfContourReferencedFrameOfReferences()
    {
    return ContourReferencedFrameOfReferences.size();
    }
  vtkIdType GetNumberOfContourReferencedFrameOfReferences(vtkIdType pdnum)
    {
    return ContourReferencedFrameOfReferences[pdnum].size();
    }
  const char *GetContourReferencedFrameOfReferenceClassUID( vtkIdType pdnum, vtkIdType id )
    {
    return ContourReferencedFrameOfReferences[pdnum][ id ].first.c_str();
    }
  const char *GetContourReferencedFrameOfReferenceInstanceUID( vtkIdType pdnum, vtkIdType id )
    {
    return ContourReferencedFrameOfReferences[pdnum][ id ].second.c_str();
    }
  vtkIdType GetNumberOfReferencedFrameOfReferences()
    {
    return ReferencedFrameOfReferences.size();
    }
  const char *GetReferencedFrameOfReferenceClassUID( vtkIdType id )
    {
    return ReferencedFrameOfReferences[ id ].first.c_str();
    }
  const char *GetReferencedFrameOfReferenceInstanceUID(vtkIdType id )
    {
    return ReferencedFrameOfReferences[ id ].second.c_str();
    }
  void AddContourReferencedFrameOfReference( vtkIdType pdnum, const char *classuid , const char * instanceuid )
    {
    ContourReferencedFrameOfReferences.resize(pdnum+1);
    ContourReferencedFrameOfReferences[pdnum].push_back(
      std::make_pair( classuid, instanceuid ) );
    }
  std::vector< std::vector < std::pair< std::string, std::string > > > ContourReferencedFrameOfReferences;
  void AddReferencedFrameOfReference( const char *classuid , const char * instanceuid )
    {
    ReferencedFrameOfReferences.push_back(
      std::make_pair( classuid, instanceuid ) );
    }
  std::vector < std::pair< std::string, std::string > > ReferencedFrameOfReferences;
  void AddStructureSetROIObservation( int refnumber,
    int observationnumber,
    const char *rtroiinterpretedtype,
    const char *roiinterpreter
  )
    {
    std::vector<StructureSetROI>::iterator it = StructureSetROIs.begin();
    bool found = false;
    for( ; it != StructureSetROIs.end(); ++it )
      {
      if( it->ROINumber == refnumber )
        {
        found = true;
        it->ObservationNumber = observationnumber;
        it->RTROIInterpretedType = rtroiinterpretedtype;
        it->ROIInterpreter = roiinterpreter;
        }
      }
    // postcond
    assert( found );
    }

  void AddStructureSetROI( int roinumber,
    const char* refframerefuid,
    const char* roiname,
    const char* roigenerationalgorithm
  )
    {
    StructureSetROI structuresetroi;
    structuresetroi.ROIName = roiname;
    structuresetroi.ROINumber = roinumber;
    structuresetroi.RefFrameRefUID = refframerefuid;
    structuresetroi.ROIGenerationAlgorithm = roigenerationalgorithm;
    StructureSetROIs.push_back( structuresetroi );
    }
  vtkIdType GetNumberOfStructureSetROIs()
    {
    return StructureSetROIs.size();
    }
  int GetStructureSetObservationNumber(vtkIdType id)
    {
    return StructureSetROIs[id].ObservationNumber;
    }
  int GetStructureSetROINumber(vtkIdType id)
    {
    return StructureSetROIs[id].ROINumber;
    }
  const char *GetStructureSetRTROIInterpretedType(vtkIdType id)
    {
    return StructureSetROIs[id].RTROIInterpretedType.c_str();
    }
  const char *GetStructureSetROIRefFrameRefUID(vtkIdType id)
    {
    return StructureSetROIs[id].RefFrameRefUID.c_str();
    }
  const char *GetStructureSetROIName(vtkIdType id)
    {
    return StructureSetROIs[id].ROIName.c_str();
    }
  const char *GetStructureSetROIGenerationAlgorithm(vtkIdType id)
    {
    return StructureSetROIs[id].ROIGenerationAlgorithm.c_str();
    }

  std::vector<StructureSetROI> StructureSetROIs;
};

//----------------------------------------------------------------------------
vtkRTStructSetProperties::vtkRTStructSetProperties()
{
  this->Internals = new vtkRTStructSetPropertiesInternals;

  this->StructureSetLabel             = NULL;
  this->StructureSetName              = NULL;
  this->StructureSetDate              = NULL;
  this->StructureSetTime              = NULL;

  this->SOPInstanceUID= NULL;
  this->StudyInstanceUID = NULL;
  this->SeriesInstanceUID = NULL;
  this->ReferenceSeriesInstanceUID = NULL;
  this->ReferenceFrameOfReferenceUID = NULL;
}

//----------------------------------------------------------------------------
vtkRTStructSetProperties::~vtkRTStructSetProperties()
{
  delete this->Internals;
  this->Clear();
}

//----------------------------------------------------------------------------
void vtkRTStructSetProperties::AddContourReferencedFrameOfReference(vtkIdType pdnum, const char *classuid , const char * instanceuid )
{
  this->Internals->AddContourReferencedFrameOfReference(pdnum, classuid, instanceuid );
}
const char *vtkRTStructSetProperties::GetContourReferencedFrameOfReferenceClassUID( vtkIdType pdnum, vtkIdType id )
{
  return this->Internals->GetContourReferencedFrameOfReferenceClassUID(pdnum, id );
}

const char *vtkRTStructSetProperties::GetContourReferencedFrameOfReferenceInstanceUID( vtkIdType pdnum, vtkIdType id )
{
  return this->Internals->GetContourReferencedFrameOfReferenceInstanceUID(pdnum ,id );
}

vtkIdType vtkRTStructSetProperties::GetNumberOfContourReferencedFrameOfReferences()
{
  return this->Internals->GetNumberOfContourReferencedFrameOfReferences();
}

vtkIdType vtkRTStructSetProperties::GetNumberOfContourReferencedFrameOfReferences(vtkIdType pdnum)
{
  return this->Internals->GetNumberOfContourReferencedFrameOfReferences(pdnum);
}

void vtkRTStructSetProperties::AddReferencedFrameOfReference( const char *classuid , const char * instanceuid )
{
  this->Internals->AddReferencedFrameOfReference( classuid, instanceuid );
}

const char *vtkRTStructSetProperties::GetReferencedFrameOfReferenceClassUID( vtkIdType id )
{
  return this->Internals->GetReferencedFrameOfReferenceClassUID(id );
}

const char *vtkRTStructSetProperties::GetReferencedFrameOfReferenceInstanceUID( vtkIdType id )
{
  return this->Internals->GetReferencedFrameOfReferenceInstanceUID(id );
}

vtkIdType vtkRTStructSetProperties::GetNumberOfReferencedFrameOfReferences()
{
  return this->Internals->GetNumberOfReferencedFrameOfReferences();
}
void vtkRTStructSetProperties::AddStructureSetROIObservation( int refnumber,
    int observationnumber,
    const char *rtroiinterpretedtype,
    const char *roiinterpreter)
{
  this->Internals->AddStructureSetROIObservation( refnumber, observationnumber, rtroiinterpretedtype, roiinterpreter );
}

void vtkRTStructSetProperties::AddStructureSetROI( int roinumber,
    const char* refframerefuid,
    const char* roiname,
    const char* roigenerationalgorithm
  )
{
  this->Internals->AddStructureSetROI( roinumber, refframerefuid, roiname, roigenerationalgorithm );
}

vtkIdType vtkRTStructSetProperties::GetNumberOfStructureSetROIs()
{
  return this->Internals->GetNumberOfStructureSetROIs();
}
int vtkRTStructSetProperties::GetStructureSetObservationNumber(vtkIdType id)
{
  return this->Internals->GetStructureSetObservationNumber(id);
}
int vtkRTStructSetProperties::GetStructureSetROINumber(vtkIdType id)
{
  return this->Internals->GetStructureSetROINumber(id);
}
const char *vtkRTStructSetProperties::GetStructureSetRTROIInterpretedType(vtkIdType id)
{
  return this->Internals->GetStructureSetRTROIInterpretedType(id);
}

const char *vtkRTStructSetProperties::GetStructureSetROIRefFrameRefUID(vtkIdType id)
{
  return this->Internals->GetStructureSetROIRefFrameRefUID(id);
}
const char *vtkRTStructSetProperties::GetStructureSetROIName(vtkIdType id)
{
  return this->Internals->GetStructureSetROIName(id);
}
const char *vtkRTStructSetProperties::GetStructureSetROIGenerationAlgorithm(vtkIdType id)
{
  return this->Internals->GetStructureSetROIGenerationAlgorithm(id);
}

//----------------------------------------------------------------------------
void vtkRTStructSetProperties::Clear()
{
  this->SetStructureSetLabel(NULL);
  this->SetStructureSetName(NULL);
  this->SetStructureSetDate(NULL);
  this->SetStructureSetTime(NULL);

  this->SetSOPInstanceUID( NULL );
  this->SetStudyInstanceUID ( NULL );
  this->SetSeriesInstanceUID ( NULL );
  this->SetReferenceSeriesInstanceUID ( NULL );
  this->SetReferenceFrameOfReferenceUID ( NULL );

}

//----------------------------------------------------------------------------
void vtkRTStructSetProperties::DeepCopy(vtkRTStructSetProperties *p)
{
  if (p == NULL)
    {
    return;
    }

  this->Clear();

  this->SetStructureSetDate(p->GetStructureSetDate());
  this->SetStructureSetTime(p->GetStructureSetTime());

  this->Internals->DeepCopy( p->Internals );
}

//----------------------------------------------------------------------------
void vtkRTStructSetProperties::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << "\n" << indent << "StructureSetDate: ";
  if (this->StructureSetDate)
    {
    os << this->StructureSetDate;
    }
  os << "\n" << indent << "StructureSetTime: ";
  if (this->StructureSetTime)
    {
    os << this->StructureSetTime;
    }

  this->Internals->Print(os << "\n", indent.GetNextIndent() );
}
