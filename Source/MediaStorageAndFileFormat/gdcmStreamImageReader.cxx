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


#include "gdcmStreamImageReader.h"
#include "gdcmImage.h"
#include "gdcmMediaStorage.h"

namespace gdcm
{

StreamImageReader::StreamImageReader(){

}
StreamImageReader::~StreamImageReader(){

}

/// Read the DICOM image. There are two reason for failure:
/// 1. The input filename is not DICOM
/// 2. The input DICOM file does not contains an Image.
/// This method has been implemented to look similar to the metaimageio in itk
bool StreamImageReader::Read(){

  return false; //for now
}

/** Set the spacing and dimension information for the set filename. */
void StreamImageReader::ReadImageInformation(){
  //read up to the point in the stream where the pixel information tag is
  //store that location and keep the rest of the data as the header information dataset
  std::set<Tag> theSkipTags;
  Tag thePixelDataTag(0x7fe0, 0x0010);
  bool read = false;
  std::ifstream* theStream = GetStreamPtr();
  if (theStream == NULL){
    gdcmErrorMacro("Filename was not initialized for gdcm stream mage reader.");
    return;
  }
  try
  {
    //ok, need to read up until I know what kind of endianness i'm dealing with?
    if (!ReadUpToTag(thePixelDataTag, theSkipTags)){
      gdcmWarningMacro("Failed to read tags in the gdcm stream image reader.");
    }
    //get the file stream position
    mFileOffset = theStream->tellg();//part of the reader functionality, the really
    //super class of this reader
    //when reading past here, can use file pointers and the like
  }
  catch(std::exception & ex)
  {
    (void)ex;
    gdcmWarningMacro( "Failed to read:" << GetFileName() << " with ex:" << ex.what() );
  }
  catch(...)
  {
    gdcmWarningMacro( "Failed to read:" << GetFileName()  << " with unknown error" );
  }

 
}


} // end namespace gdcm


