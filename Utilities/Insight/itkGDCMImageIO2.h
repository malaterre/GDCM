/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef ITKGDCMIMAGEIO2_H
#define ITKGDCMIMAGEIO2_H

#include "itkImageIOBase.h"

namespace itk
{

/** \class GDCMImageIO2
 *
 *  \brief ImageIO class for reading and writing DICOM V3.0 and ACR/NEMA (V1.0 & V2.0) images
 *  This class is only an adaptor to the gdcm library (currently gdcm 2.0 is used):
 *
 *  http://gdcm.sourceforge.net
 *
 *  \ingroup IOFilters
 *  \warning this class is deprecated, as gdcm 2.x has been integrated in ITK starting ITK 3.12
 */

#ifndef ITK_EXPORT
/* I could not figure out where/what was the API in ITK to achieve that,
 * instead duplicate code here */
#if defined(WIN32) && defined(ITK_BUILD_SHARED_LIBS)
 #if defined(itkgdcm2_EXPORTS)
  #define ITK_GDCM_EXPORT __declspec( dllexport )
 #else
  #define ITK_GDCM_EXPORT __declspec( dllimport )
 #endif
#else
  #define ITK_GDCM_EXPORT
#endif
#else
  #define ITK_GDCM_EXPORT ITK_EXPORT
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

  /** Macro to access Rescale Slope and Rescale Intercept. Which are
   * needed to rescale properly image when needed. User then need to
   * Always check those value when access value from the DICOM header */
  itkGetMacro(RescaleSlope, double);
  itkGetMacro(RescaleIntercept, double);

  /** Macro to access the DICOM UID prefix. By default this is the ITK
   *  root id. This default can be overriden if the exam is for example
   *  part of an existing study.
   */
  itkGetStringMacro(UIDPrefix);
  itkSetStringMacro(UIDPrefix);

  /** Access the generated DICOM UID's. */
  itkGetStringMacro(StudyInstanceUID);
  itkGetStringMacro(SeriesInstanceUID);
  itkGetStringMacro(FrameOfReferenceInstanceUID);

  /** Preserve the original DICOM UID of the input files
   */
  itkSetMacro(KeepOriginalUID,bool);
  itkGetMacro(KeepOriginalUID,bool);
  itkBooleanMacro(KeepOriginalUID);

  /** Convenience methods to query patient information and scanner
   * information. These methods are here for compatibility with the
   * DICOMImageIO2 class. */
  void GetPatientName(char* name);
  void GetPatientID(char* id);
  void GetPatientSex(char* sex);
  void GetPatientAge(char* age);
  void GetStudyID(char* id);
  void GetPatientDOB(char* dob);
  void GetStudyDescription(char* desc);
  void GetBodyPart(char* part);
  void GetNumberOfSeriesInStudy(char* series);
  void GetNumberOfStudyRelatedSeries(char* series);
  void GetStudyDate(char* date);
  void GetModality(char* modality);
  void GetManufacturer(char* manu);
  void GetInstitution(char* ins);
  void GetModel(char* model);
  void GetScanOptions(char *options);

  /** More general method to retrieve an arbitrary DICOM value based
   * on a DICOM Tag (eg "0123|4567").
   * WARNING: You need to use the lower case for hex 0x[a-f], for instance:
   * "0020|000d" instead of "0020|000D" (the latter won't work)
   */
  bool GetValueFromTag(const std::string & tag, std::string & value);

  /** Method for consulting the DICOM dictionary and recovering the text
   * description of a field using its numeric tag represented as a string.  If
   * the tagkey is not found in the dictionary then this static method return
   * false and the value "Unknown " in the labelId. If the tagkey is found then
   * this static method returns true and the actual string descriptor of the
   * tagkey is returned in the variable labelId. */
  static bool GetLabelFromTag( const std::string & tag,
                               std::string & labelId );

  /** A DICOM file can contains multiple binary stream that can be very long
   * For example an Overlay on the image. Most of the time user do not want to load
   * this binary structure in memory since it can consume lot of memory. Therefore
   * any field that is bigger than the default value 0xfff is discarded and just seek'd
   * This method allow advanced user to force the reading of such field
   */
  itkSetMacro(MaxSizeLoadEntry, long);

  /** Parse any sequences in the DICOM file. Defaults to the value of
   *  LoadSequencesDefault. Loading DICOM files is faster when
   *  sequences are not needed.
   */
  itkSetMacro(LoadSequences, bool);
  itkGetMacro(LoadSequences, bool);
  itkBooleanMacro(LoadSequences);

  /** Parse any private tags in the DICOM file. Defaults to the value
   * of LoadPrivateTagsDefault. Loading DICOM files is faster when
   * private tags are not needed.
   */
  itkSetMacro(LoadPrivateTags, bool);
  itkGetMacro(LoadPrivateTags, bool);
  itkBooleanMacro(LoadPrivateTags);

  /** Global method to define the default value for
   * LoadSequences. When instances of GDCMImageIO are created, the
   * ivar LoadSequences is initialized to the value of
   * LoadSequencesDefault.  This method is useful when relying on the
   * IO factory mechanism to load images rather than specifying a
   * particular ImageIO object on the readers. Default is false. */
  static void SetLoadSequencesDefault(bool ) {}
  static void LoadSequencesDefaultOn() {}
  static void LoadSequencesDefaultOff() {}
  static bool GetLoadSequencesDefault() { return true; }

  /** Global method to define the default value for
   * LoadPrivateTags. When instances of GDCMImageIO are created, the
   * ivar LoadPrivateTags is initialized to the value of
   * LoadPrivateTagsDefault.  This method is useful when relying on the
   * IO factory mechanism to load images rather than specifying a
   * particular ImageIO object on the readers. Default is false. */
  static void SetLoadPrivateTagsDefault(bool ) {}
  static void LoadPrivateTagsDefaultOn() {}
  static void LoadPrivateTagsDefaultOff() {}
  static bool GetLoadPrivateTagsDefault() { return true; }

  /** Set/Get a boolean to use the JPEG2000 compression or not. */
  typedef enum { JPEG = 0, JPEG2000 } TCompressionType;
  itkSetEnumMacro(CompressionType,TCompressionType);
  itkGetEnumMacro(CompressionType,TCompressionType);

protected:
  GDCMImageIO2();
  ~GDCMImageIO2();
  void PrintSelf(std::ostream& os, Indent indent) const;

  void InternalReadImageInformation(std::ifstream&);
  bool OpenGDCMFileForReading(std::ifstream&, const char*);
  bool OpenGDCMFileForWriting(std::ofstream&, const char*);

  double m_RescaleSlope;
  double m_RescaleIntercept;

  std::string m_UIDPrefix;
  std::string m_StudyInstanceUID;
  std::string m_SeriesInstanceUID;
  std::string m_FrameOfReferenceInstanceUID;
  bool        m_KeepOriginalUID;


private:
  GDCMImageIO2(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  /** defines whether this image is a 2D out of a 2D image
   *  or a 2D out of a 3D image. */
  unsigned int     m_GlobalNumberOfDimensions;
  TCompressionType m_CompressionType;

// LEGACY, REMOVE ME
  bool        m_LoadSequences;
  bool        m_LoadPrivateTags;
  long        m_MaxSizeLoadEntry;

};

} // end namespace itk

#endif // ITKGDCMIMAGEIO2_H
