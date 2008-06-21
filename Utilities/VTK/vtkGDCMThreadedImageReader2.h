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

#ifndef __vtkGDCMThreadedImageReader2_h
#define __vtkGDCMThreadedImageReader2_h

//#include "vtkGDCMImageReader.h"
#include "vtkThreadedImageAlgorithm.h"

class vtkStringArray;
class VTK_EXPORT vtkGDCMThreadedImageReader2 : public vtkThreadedImageAlgorithm
{
public:
  static vtkGDCMThreadedImageReader2 *New();
  vtkTypeRevisionMacro(vtkGDCMThreadedImageReader2,vtkThreadedImageAlgorithm);
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  vtkGetMacro(FileLowerLeft,int);
  vtkSetMacro(FileLowerLeft,int);
  vtkBooleanMacro(FileLowerLeft,int);

  vtkGetMacro(NumberOfOverlays,int);

  vtkSetMacro(DataScalarType,int);
  vtkGetMacro(DataScalarType,int);

  vtkSetMacro(NumberOfScalarComponents,int);
  vtkGetMacro(NumberOfScalarComponents,int);

  vtkGetMacro(LoadOverlays,int);
  vtkSetMacro(LoadOverlays,int);
  vtkBooleanMacro(LoadOverlays,int);

  vtkSetVector6Macro(DataExtent,int);
  vtkGetVector6Macro(DataExtent,int);

  vtkGetStringMacro(FileName);
  vtkSetStringMacro(FileName);

  virtual void SetFileNames(vtkStringArray*);
  vtkGetObjectMacro(FileNames, vtkStringArray);

  int SplitExtent(int splitExt[6], int startExt[6], 
                  int num, int total);

protected:
  vtkGDCMThreadedImageReader2();
  ~vtkGDCMThreadedImageReader2();

  int RequestInformation(vtkInformation *request,
                         vtkInformationVector **inputVector,
                         vtkInformationVector *outputVector);
  //int RequestData(vtkInformation *request,
  //                vtkInformationVector **inputVector,
  //                vtkInformationVector *outputVector);

protected:
void ThreadedRequestData (
  vtkInformation * vtkNotUsed( request ), 
  vtkInformationVector** vtkNotUsed( inputVector ),
  vtkInformationVector * vtkNotUsed( outputVector ),
  vtkImageData ***inData, 
  vtkImageData **outData,
  int outExt[6], int id);

private:
  int FileLowerLeft;
  char *FileName;
  vtkStringArray *FileNames;
  int LoadIconImage;
  int DataExtent[6];
  int LoadOverlays;
    int NumberOfOverlays;
  int DataScalarType;

  int NumberOfScalarComponents;
  double DataSpacing[3];
  double DataOrigin[3];
  int IconImageDataExtent[6];

private:
  vtkGDCMThreadedImageReader2(const vtkGDCMThreadedImageReader2&);  // Not implemented.
  void operator=(const vtkGDCMThreadedImageReader2&);  // Not implemented.
};

#endif
