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
 
 #include "gdcmDirectory.h"
 #include "gdcmDataSet.h"
 
 namespace gdcm {
 
 class vtkGDCMPolyHelper {
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
 
 }

