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
// .NAME vtkGDCMImageReader - read DICOM Image files (Pixel Data)
// .SECTION Description
// vtkGDCMImageReader is a source object that reads some DICOM files
// this reader is single threaded.
// .SECTION Implementation note: when FileLowerLeft is set to on the image is not flipped
// upside down as VTK would expect, use this option only if you know what you are doing
// .SECTION Implementation note: when reading a series of 2D slices, user is expected to provide an ordered list of filenames. No sorting will be applied afterward. 
// .SECTION Implementation note: Although 99% of the time the Zspacing as read from a tag in a 2D DICOM file should be correct, there has been reports that this value can be missing, or incorrect, in which case users are advised to override this value using the return value from gdcm::IPPSorter::GetZSpacing() and set it via SetDataSpacing on the reader itself.
// .SECTION TODO
// This reader does not handle a series of 3D images, only a single 3D (multi frame) or a 
// list of 2D files are supported for now.
// .SECTION TODO
// Modality LUT with rescale slope/intercept is not applied. You need to use a vtkImageShiftScale externally for now.
// .SECTION BUG
// Overlay are assumed to have the same extent as image. Right now if overlay origin is not
// 0,0 the overlay will have an offset...
// Only the very first overlay is loaded at the VTK level, for now (even if there are more than one in the file)
// .SECTION BUG
// Only the first Curve Data is loaded at the VTK layer, for now.
// .SECTION DataOrigin
// In the case of a direction cosine (1,0,0,0,1,0) the DataOrigin is properly set. Otherwise user
// need to use the GetPatientPosition to compute the proper pixel x,y,z position.

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
class vtkPolyData;

// vtkSystemIncludes.h defines:
// #define VTK_LUMINANCE       1
// #define VTK_LUMINANCE_ALPHA 2
// #define VTK_RGB             3
// #define VTK_RGBA            4
#ifndef VTK_INVERSE_LUMINANCE
#define VTK_INVERSE_LUMINANCE 5
#endif
#ifndef VTK_LOOKUP_TABLE
#define VTK_LOOKUP_TABLE 6
#endif
#ifndef VTK_YBR
#define VTK_YBR 7
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

  // Description: is the given file name a DICOM file containing an image ?
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

  // Description:
  // Load image with its associated Lookup Table
  vtkGetMacro(ApplyLookupTable,int);
  vtkSetMacro(ApplyLookupTable,int);
  vtkBooleanMacro(ApplyLookupTable,int);

  // Description:
  // Load image as YBR
  vtkGetMacro(ApplyYBRToRGB,int)
  vtkSetMacro(ApplyYBRToRGB,int)
  vtkBooleanMacro(ApplyYBRToRGB,int);

  // Description:
  // Return VTK_LUMINANCE, VTK_RGB, VTK_LOOKUP_TABLE or VTK_YBR
  vtkGetMacro(ImageFormat,int);

  // Description:
  // Return the 'raw' information stored in the DICOM file:
  // In case of a series of multiple files, only the first file is considered. The Image Orientation (Patient)
  // is garantee to remain the same, and image Image Position (Patient) in other slice can be computed
  // using the ZSpacing (3rd dimension)
  // (0020,0032) DS [87.774866\-182.908510\168.629671]       #  32, 3 ImagePositionPatient
  // (0020,0037) DS [0.001479\0.999989\-0.004376\-0.002039\-0.004372\-0.999988] #  58, 6 ImageOrientationPatient
  vtkGetVector3Macro(ImagePositionPatient,double);
  vtkGetVector6Macro(ImageOrientationPatient,double);

  // Set/Get the first Curve Data:
  vtkGetObjectMacro(Curve,vtkPolyData);
  virtual void SetCurve(vtkPolyData *pd);

  // Modality LUT
  vtkGetMacro(Shift,double);
  vtkGetMacro(Scale,double);

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
  double ImagePositionPatient[3];
  double ImageOrientationPatient[6];
  vtkPolyData *Curve;

  int ImageFormat;
  // the following 3, should remain optional
  int ApplyInverseVideo;
  int ApplyLookupTable;
  int ApplyYBRToRGB;
  // I think that planar configuration need to always be applied as far as VTK is concerned
  int ApplyPlanarConfiguration;
  int ApplyShiftScale;

  int LoadSingleFile(const char *filename, char *pointer, unsigned long &outlen);

  double Shift;
  double Scale;
  int IconDataScalarType;
  int IconNumberOfScalarComponents;

private:
  vtkGDCMImageReader(const vtkGDCMImageReader&);  // Not implemented.
  void operator=(const vtkGDCMImageReader&);  // Not implemented.
};
#endif

