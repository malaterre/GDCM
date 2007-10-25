/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmTS_h
#define __gdcmTS_h

//#include "gdcmTransferSyntax.h" // Generated File from TransferSyntax.dic
#include "gdcmSwapCode.h"
#include "gdcmCompression.h"

namespace gdcm
{

/**
 * \brief Class to manipulate Transfer Syntax
 * \note
 * TRANSFER SYNTAX (Standard and Private): A set of encoding rules that
 * allow Application Entities to unambiguously negotiate the encoding 
 * techniques (e.g., Data Element structure, byte ordering, compression) 
 * they are able to support, thereby allowing these Application Entities
 * to communicate.
 * \TODO: The implementation is completely retarded
 * We need: IsSupported
 * We need preprocess of raw/xml file
 * We need GetFullName()
 *
 * Need a notion of Private Syntax. As defined in Ps 3.5. Section 9.2
 */
class GDCM_EXPORT TS
{
public:
  typedef enum {
    Unknown = 0,
    Explicit,
    Implicit
  } NegociatedType;

  // TODO
  typedef enum {
    NoSpacing = 0,
    PixelSpacing,
    ImagerPixelSpacing,
    PixelAspectRatio
  } ImageSpacingType;
  ImageSpacingType GetImageSpacing();

  typedef enum {
    ImplicitVRLittleEndian = 0,
    ImplicitVRBigEndianPrivateGE,
    ExplicitVRLittleEndian,
    DeflatedExplicitVRLittleEndian,
    ExplicitVRBigEndian,
    JPEGBaselineProcess1,
    JPEGExtendedProcess2_4,
    JPEGExtendedProcess3_5,
    JPEGSpectralSelectionProcess6_8,
    JPEGFullProgressionProcess10_12,
    JPEGLosslessProcess14,
    JPEGLosslessProcess14_1,
    JPEGLSLossless,
    JPEGLSNearLossless,
    JPEG2000Lossless,
    JPEG2000,
    RLELossless,
    MPEG2MainProfile,
    ImplicitVRBigEndianACRNEMA,
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    WeirdPapryus,
#endif
    TS_END
  } TSType;


  typedef enum {
    MediaStorageDirectoryStorage = 0,
    ComputedRadiographyImageStorage,
    DigitalXRayImageStorageForPresentation,
    DigitalXRayImageStorageForProcessing,
    DigitalMammographyImageStorageForPresentation,
    DigitalMammographyImageStorageForProcessing,
    DigitalIntraoralXrayImageStorageForPresentation,
    DigitalIntraoralXRayImageStorageForProcessing,
    CTImageStorage,
    EnhancedCTImageStorage,
    UltrasoundMultiFrameImageStorageRetired,
    UltrasoundMultiFrameImageStorage,
    MRImageStorage,
    EnhancedMRImageStorage,
    MRSpectroscopyStorage,
    NuclearMedicineImageStorageRetired,
    UltrasoundImageStorageRetired,
    UltrasoundImageStorage,
    SecondaryCaptureImageStorage,
    MultiframeSingleBitSecondaryCaptureImageStorage,
    MultiframeGrayscaleByteSecondaryCaptureImageStorage,
    MultiframeGrayscaleWordSecondaryCaptureImageStorage,
    MultiframeTrueColorSecondaryCaptureImageStorage,
    StandaloneOverlayStorage,
    StandaloneCurveStorage,
    LeadECGWaveformStorage, // 12-
    GeneralECGWaveformStorage,
    AmbulatoryECGWaveformStorage,
    HemodynamicWaveformStorage,
    CardiacElectrophysiologyWaveformStorage,
    BasicVoiceAudioWaveformStorage,
    StandaloneModalityLUTStorage,
    StandaloneVOILUTStorage,
    GrayscaleSoftcopyPresentationStateStorageSOPClass,
    XRayAngiographicImageStorage,
    XRayRadiofluoroscopingImageStorage,
    XRayAngiographicBiPlaneImageStorageRetired,
    NuclearMedicineImageStorage,
    RawDataStorage,
    SpacialRegistrationStorage,
    SpacialFiducialsStorage,
    PETImageStorage,
    RTImageStorage,
    RTDoseStorage,
    RTStructureSetStorage,
    RTPlanStorage,
    CSANonImageStorage,
    Philips3D,
    MS_END
  } MSType; // Media Storage Type

  // Return the string as written in the official DICOM dict from
  // a custom enum type
  static const char* GetTSString(const TSType &ts);
  static const char* GetMSString(const MSType &ts);
  static const TSType GetTSType(const char *str);
  static const MSType GetMSType(const char *str);

  NegociatedType GetNegociatedType() const;
  // Return the SwapCode associated with the Transfer Syntax. Be carefull
  // with the special GE private syntax the DataSet is written in little
  // endian but the Pixel Data is in Big Endian.
  SwapCode GetSwapCode() const;

  bool IsValid() const { return TSField != TS_END; }

  operator TSType () const { return TSField; }

  TS(TSType type = ImplicitVRLittleEndian):TSField(type) {}

  static bool IsImage(const MSType &ts);

  Compression::Types GetCompressionType() const;

protected:
  // TODO are those function actually usefull ?
  static bool IsJPEG(const TSType &ts);
  static bool IsJPEG2000(const TSType &ts);
  static bool IsRAW(const TSType &ts);
  static bool IsRLE(const TSType &ts);
  static bool IsMPEG(const TSType &ts);
  static bool IsExplicit(const TSType &ts);
  static bool IsImplicit(const TSType &ts);
  static bool IsLittleEndian(const TSType &ts);
  static bool IsBigEndian(const TSType &ts);


  // Very special case of the DICOM specification the *whole* dataset
  // is encoded (typically compressed using the deflate algorithm)
  // therefore you cannot parse the file out of the box without
  // first uncompressing it (expensive operation)
  // TODO: Can we partially uncompress in LZW ?
  static bool IsDataSetEncoded(const TSType &ts);

private:
  TSType TSField;
};

} // end namespace gdcm

#endif //__gdcmTS_h
