/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmMediaStorage_h
#define __gdcmMediaStorage_h

#include "gdcmTransferSyntax.h"

namespace gdcm
{

class DataSet;
class FileMetaInformation;
class File;
/**
 * \brief MediaStorage
 *
 * \note
 * FIXME There should not be any notion of Image and/or PDF at that point
 * Only the codec can answer yes I support this Media Storage or not...
 * For instance an ImageCodec will answer yes to most of them
 * while a PDFCodec will answer only for the Encaplusated PDF
 */
class GDCM_EXPORT MediaStorage
{
public:
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
    UltrasoundImageStorageRetired,
    UltrasoundImageStorage,
    UltrasoundMultiFrameImageStorageRetired,
    UltrasoundMultiFrameImageStorage,
    MRImageStorage,
    EnhancedMRImageStorage,
    MRSpectroscopyStorage,
    NuclearMedicineImageStorageRetired,
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
    EnhancedSR,
    BasicTextSR,
    HardcopyGrayscaleImageStorage,
    ComprehensiveSR,
    DetachedStudyManagementSOPClass,
    EncapsulatedPDFStorage,
    StudyComponentManagementSOPClass,
    DetachedVisitManagementSOPClass,
    DetachedPatientManagementSOPClass,
    VideoEndoscopicImageStorage,
    GeneralElectricMagneticResonanceImageStorage,
    GEPrivate3DModelStorage,
    ToshibaPrivateDataStorage,
    MammographyCADSR,
    KeyObjectSelectionDocument,
    HangingProtocolStorage,
    ModalityPerformedProcedureStepSOPClass,
    MS_END
  } MSType; // Media Storage Type

typedef enum {
	  NoObject = 0, // DICOMDIR
	  Video, // Most common, include image, video and volume
	  Waveform, // Isn't it simply a 1D video ?
	  Audio, // ???
	  PDF,
	  URI, // URL...
	  Segmentation, // TODO
	  ObjectEnd
  } ObjectType;

  static const char* GetMSString(MSType ts);
  const char* GetString() const;
  static MSType GetMSType(const char *str);

  MediaStorage(MSType type = MS_END):MSField(type) {}

  /// Returns whether DICOM has a Pixel Data element (7fe0,0010)
  /// \warning MRSpectroscopyStorage could be image but are not 
  static bool IsImage(MSType ts);

  operator MSType () const { return MSField; }

  const char *GetModality() const;

  // Attempt to set the MediaStorage from a file:
  // WARNING: When no MediaStorage & Modality are found BUT a PixelData element is found
  // then MediaStorage is set to the default SecondaryCaptureImageStorage
  void SetFromFile(File const &file);

  // Those function are lower level than SetFromFile
  void SetFromDataSet(DataSet const &ds, bool guess = false); // Will get the SOP Class UID
  void SetFromHeader(FileMetaInformation const &fmi); // Will get the Media Storage SOP Class UID
  void SetFromModality(DataSet const &ds);
  void SetFromSourceImageSequence(DataSet const &ds);
  void GuessFromModality(const char *modality, unsigned int dimension = 2);

  friend std::ostream &operator<<(std::ostream &os, const MediaStorage &ms);

  bool IsUndefined() const { return MSField == MS_END; }

private:
  MSType MSField;
};
//-----------------------------------------------------------------------------
inline std::ostream &operator<<(std::ostream &_os, const MediaStorage &ms)
{
  _os << MediaStorage::GetMSString(ms);
  return _os;

}

} // end namespace gdcm

#endif // __gdcmMediaStorage_h
