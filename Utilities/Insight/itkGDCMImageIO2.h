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
#ifndef __itkGDCMImageIO2_h
#define __itkGDCMImageIO2_h

#include "itkImageIOBase.h"

namespace itk
{

/** \class GDCMImageIO2
 *
 *  \brief ImageIO class for reading and writing DICOM V3.0 and ACR/NEMA (V1.0 & V2.0) images
 *  This class is only an adaptor to the gdcm library (currently gdcm 2.0.0 is used):
 *
 *  http://gdcm.sourceforge.net
 *
 *  \ingroup IOFilters
 */

/* I could not figure out where/what was the API in ITK to achieve that,
 * instead duplicate code here */
#if defined(WIN32) && defined(ITK_BUILD_SHARED_LIBS)
 #if defined(itkgdcm2_EXPORTS)
  #define ITK_GDCM_EXPORT __declspec( dllexport ) 
 #else
  #define ITK_GDCM_EXPORT __declspec( dllimport ) 
 #endif
#endif

class ITK_GDCM_EXPORT GDCMImageIO2 : public ImageIOBase
{
public:
  /** Standard class typedefs. */
  typedef GDCMImageIO2         Self;
  typedef ImageIOBase         Superclass;
  typedef SmartPointer<Self>  Pointer;
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(GDCMImageIO2, Superclass);

  /*-------- This part of the interface deals with reading data. ------ */

  /** Determine the file type. Returns true if this ImageIO can read the
   * file specified. */
  virtual bool CanReadFile(const char*);
  
  /** Set the spacing and dimesion information for the current filename. */
  virtual void ReadImageInformation();
  
  /** Reads the data from disk into the memory buffer provided. */
  virtual void Read(void* buffer);

  /*-------- This part of the interfaces deals with writing data. ----- */

  /** Determine the file type. Returns true if this ImageIO can write the
   * file specified. GDCM triggers on ".dcm" and ".dicom". */
  virtual bool CanWriteFile(const char*);

  /** Writes the spacing and dimentions of the image.
   * Assumes SetFileName has been called with a valid file name. */
  virtual void WriteImageInformation();
  
  /** Writes the data to disk from the memory buffer provided. Make sure
   * that the IORegion has been set properly. */
  virtual void Write(const void* buffer);
  
protected:
  GDCMImageIO2();
  ~GDCMImageIO2();
  void PrintSelf(std::ostream& os, Indent indent) const;

  void InternalReadImageInformation(std::ifstream&);
  bool OpenGDCMFileForReading(std::ifstream&, const char*);
  bool OpenGDCMFileForWriting(std::ofstream&, const char*);

private:
  GDCMImageIO2(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};

} // end namespace itk

#endif // __itkGDCMImageIO2_h
