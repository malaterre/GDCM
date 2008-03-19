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
// .NAME vtkGDCMImageReader - read DICOM files
// .SECTION Description
// vtkGDCMImageReader is a source object that reads some DICOM files
// this reader is single threaded.
// .SECTION Implementation note: when FileLowerLeft is set to on the image is not flipped
// upside down as VTK would expect, use this option only if you know what you are doing
// .SECTION TODO
// This reader does not handle a series of 3D images, only a single 3D (multi frame) or a 
// list of 2D files are supported for now.
// .SECTION TODO
// Modality LUT with rescale slope/intercept is not applied. You need to use a vtkImageShiftScale externally for now.
// .SECTION BUG
// Overlay are assumed to have the same extent as image. Right now if overlay origin is not
// 0,0 the overlay will have an offset...
// Only the very first overlay is loaded for now (even if there are more than one in the file)

// .SECTION See Also
// vtkMedicalImageReader2 vtkMedicalImageProperties

#ifndef __vtkGDCMImageReader_h
#define __vtkGDCMImageReader_h

#include "vtkMedicalImageReader2.h"
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
#else
class vtkMedicalImageProperties;
#endif
#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
#else
class vtkStringArray;
#endif

//BTX
namespace gdcm { class ImageReader; }
//ETX
class vtkMatrix4x4;
class VTK_EXPORT vtkGDCMImageReader : public vtkMedicalImageReader2
{
public:
  static vtkGDCMImageReader *New();
  vtkTypeRevisionMacro(vtkGDCMImageReader,vtkMedicalImageReader2);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description: is the given file name a DICOM file?
  virtual int CanReadFile(const char* fname);

  // Description:
  // Valid extensions
  virtual const char* GetFileExtensions()
    {
    // I would like to get rid of ACR/NEMA/IMA so only allow dcm extension for now
    return ".dcm .DCM";
    }

  // Description: 
  // A descriptive name for this format
  virtual const char* GetDescriptiveName()
    {
    return "DICOM";
    }

  // Description:
  // Get the Image Position (Patient) as stored in the DICOM file
  // This is a read-only data member
  vtkGetObjectMacro(DirectionCosines, vtkMatrix4x4);

#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
#else
  // Description:
  // Get the medical image properties object
  vtkGetObjectMacro(MedicalImageProperties, vtkMedicalImageProperties);
#endif

#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
#else
  virtual void SetFileNames(vtkStringArray*);
  vtkGetObjectMacro(FileNames, vtkStringArray);
#endif

  // Description:
  // Specifically request to load the overlay into the gdcm-VTK layer (gdcm always loads them when found).
  // If no overlay is found in the image, then the vtkImageData for the overlay will be empty.
  vtkGetMacro(LoadOverlays,int);
  vtkSetMacro(LoadOverlays,int);
  vtkBooleanMacro(LoadOverlays,int);

  // Description:
  // Set/Get whether or not to load the Icon as vtkImageData (if found in the DICOM file)
  vtkGetMacro(LoadIconImage,int);
  vtkSetMacro(LoadIconImage,int);
  vtkBooleanMacro(LoadIconImage,int);

  // Description:
  // Read only: number of overlays as found in this image (multiple overlays per slice is allowed)
  vtkGetMacro(NumberOfOverlays,int);

  // Description:
  // Read only: number of icon image (there should ony be one)
  vtkGetMacro(NumberOfIconImages,int);

  // Description:
  // Get Overlay/IconImage
  // Remember to ALWAYS use those methods in your code, as the internal number for the output port
  // is not garantee to remain the same, as features are added to the reader
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
//FIXME: Need to get rid of BTX/ETX if only the Python Wrapper of VTK 4.2 would let me
//BTX
  vtkAlgorithmOutput* GetOverlayPort(int index);
  vtkAlgorithmOutput* GetIconImagePort();
//ETX
#endif
  vtkImageData* GetOverlay(int i);
  vtkImageData* GetIconImage();

protected:
  vtkGDCMImageReader();
  ~vtkGDCMImageReader();

//BTX
  void FillMedicalImageInformation(const gdcm::ImageReader &reader);
//ETX
  int RequestInformationCompat();
  int RequestDataCompat();

#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
  int ProcessRequest(vtkInformation* request,
                                 vtkInformationVector** inputVector,
                                 vtkInformationVector* outputVector);
  int RequestInformation(vtkInformation *request,
                         vtkInformationVector **inputVector,
                         vtkInformationVector *outputVector);
  int RequestData(vtkInformation *request,
                  vtkInformationVector **inputVector,
                  vtkInformationVector *outputVector);
#else /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/
  void ExecuteInformation();
  void ExecuteData(vtkDataObject *out);
#endif /*(VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )*/

protected:
#if (VTK_MAJOR_VERSION >= 5) || ( VTK_MAJOR_VERSION == 4 && VTK_MINOR_VERSION > 5 )
#else
  // Description:
  // Medical Image properties
  vtkMedicalImageProperties *MedicalImageProperties;
#endif
#if ( VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0 )
#else
  vtkStringArray *FileNames;
#endif

  vtkMatrix4x4 *DirectionCosines;
  int LoadOverlays;
  int NumberOfOverlays;
  int LoadIconImage;
  int NumberOfIconImages;
  int IconImageDataExtent[6];

  int LoadSingleFile(const char *filename, int *dext, vtkImageData* data, bool filelowerleft);

private:
  vtkGDCMImageReader(const vtkGDCMImageReader&);  // Not implemented.
  void operator=(const vtkGDCMImageReader&);  // Not implemented.
};
#endif

