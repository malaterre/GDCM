/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmPresentationContext.h"
#include "gdcmUIDs.h"
#include "gdcmSwapper.h"
#include "gdcmAttribute.h"
#include "gdcmGlobal.h"
#include "gdcmMediaStorage.h"

#include <limits>

namespace gdcm
{
namespace network
{
const uint8_t PresentationContext::ItemType = 0x20;
const uint8_t PresentationContext::Reserved2 = 0x00;
const uint8_t PresentationContext::Reserved6 = 0x00;
const uint8_t PresentationContext::Reserved7 = 0x00;
//const uint8_t PresentationContext::Reserved7 = 0xff; // DCMTK ??
const uint8_t PresentationContext::Reserved8 = 0x00;

PresentationContext::PresentationContext()
{
  ID = 0x01;
  ItemLength = 8;
  assert( (size_t)ItemLength + 4 == Size() );
}

std::istream &PresentationContext::Read(std::istream &is)
{
  //uint8_t itemtype = 0x0;
  //is.read( (char*)&itemtype, sizeof(ItemType) );
  //assert( itemtype == ItemType );
  uint8_t reserved2;
  is.read( (char*)&reserved2, sizeof(Reserved2) );
  uint16_t itemlength;
  is.read( (char*)&itemlength, sizeof(ItemLength) );
  SwapperDoOp::SwapArray(&itemlength,1);
  ItemLength = itemlength;
  uint8_t id;
  is.read( (char*)&id, sizeof(ID) );
  ID = id;
  uint8_t reserved6;
  is.read( (char*)&reserved6, sizeof(Reserved6) );
  uint8_t reserved7;
  is.read( (char*)&reserved7, sizeof(Reserved7) );
  uint8_t reserved8;
  is.read( (char*)&reserved8, sizeof(Reserved6) );
  SubItems.Read( is );

  size_t curlen = 0;
  size_t offset = SubItems.Size() + 4;
  while( curlen + offset < ItemLength )
    {
    TransferSyntaxSub ts;
    ts.Read( is );
    TransferSyntaxes.push_back( ts );
    curlen += ts.Size();
    }
  assert( curlen + offset == ItemLength );

  assert( (size_t)ItemLength + 4 == Size() );
  return is;
}

const std::ostream &PresentationContext::Write(std::ostream &os) const
{
  assert( (size_t)ItemLength + 4 == Size() );
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );
  //os.write( (char*)&ItemLength, sizeof(ItemLength) );
  uint16_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );

  os.write( (char*)&ID, sizeof(ID) );
  os.write( (char*)&Reserved6, sizeof(Reserved6) );
  os.write( (char*)&Reserved7, sizeof(Reserved7) );
  os.write( (char*)&Reserved8, sizeof(Reserved8) );
  SubItems.Write(os);
  std::vector<TransferSyntaxSub>::const_iterator it = TransferSyntaxes.begin();
  for( ; it != TransferSyntaxes.end(); ++it )
    {
    it->Write( os );
    }

  return os;
}

size_t PresentationContext::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemType);
  ret += sizeof(Reserved2);
  ret += sizeof(ItemLength);
  ret += sizeof(ID);
  ret += sizeof(Reserved6);
  ret += sizeof(Reserved7);
  ret += sizeof(Reserved8);
  ret += SubItems.Size();
  std::vector<TransferSyntaxSub>::const_iterator it = TransferSyntaxes.begin();
  for( ; it != TransferSyntaxes.end(); ++it )
    {
    ret += it->Size();
    }

  assert(ret <= (size_t)std::numeric_limits<uint16_t>::max);
  assert(ret >= 4);
  return ret;
}

void PresentationContext::SetAbstractSyntax( AbstractSyntax const & as )
{
  SubItems = as;
  ItemLength = (uint16_t)Size() - 4;
  assert( (size_t)ItemLength + 4 == Size() );
}

void PresentationContext::AddTransferSyntax( TransferSyntaxSub const &ts )
{
  TransferSyntaxes.push_back( ts );
  ItemLength = (uint16_t)Size() - 4;
  assert( (size_t)ItemLength + 4 == Size() );
}

void PresentationContext::SetPresentationContextID( uint8_t id )
{
  ID = id;
}

uint8_t PresentationContext::GetPresentationContextID() const
{
  return ID;
}

void PresentationContext::Print(std::ostream &os) const
{
  //static const uint8_t ItemType;
  //static const uint8_t Reserved2;
  os << "ItemLength: " << ItemLength << std::endl; // len of last transfer syntax
  os << "PresentationContext ID: " << (int)ID << std::endl;
  //static const uint8_t Reserved6;
  //static const uint8_t Reserved7;
  //static const uint8_t Reserved8;
  SubItems.Print( os );
  std::vector<TransferSyntaxSub>::const_iterator it = TransferSyntaxes.begin();
  for( ; it != TransferSyntaxes.end(); ++it )
    {
    it->Print( os );
    }
}

//this function will return the appropriate ID from the above
//list, after querying the appropriate tag in the dataset.  If the tag above
//does not exist, then the result is a pure verification ID.
//if the operation is something other than an echo, that should be interpreted
//as a failure; echos themselves take a null dataset.
EPresentationContextID PresentationContext::AssignPresentationContextID(const DataSet& inDS, std::string& outUIDString){
  //check to see if you have the 0x0008, 0x0016 tag in the dataset
  //if not, return verification
//  assert( inDS.FindDataElement(Tag(0x0008, 0x0016)) );
//  assert( inDS.FindDataElement(Tag(0x0008, 0x0018)) );
  const DataElement &de1 = inDS.GetDataElement(Tag(0x0008, 0x0016));
  const DataElement &de2 = inDS.GetDataElement(Tag(0x0008, 0x0018));

  if (de1.IsEmpty() || de2.IsEmpty()) {
      return eVerificationSOPClass;
  }
  else {
#if 0
    Global& g = Global::GetInstance();
    if( !g.LoadResourcesFiles() ) // NOT THREAD SAFE
      {
      std::cerr << "Could not LoadResourcesFiles" << std::endl;
      return eVerificationSOPClass;
      }
#endif
    MediaStorage mst;
    if (!mst.SetFromDataSet(inDS)){
      return eVerificationSOPClass;
    }
    UIDs uid;//want to get this as well, to set the abstract syntax properly
    uid.SetFromUID( MediaStorage::GetMSString(mst) /*mst.GetString()*/ );
    outUIDString = std::string(MediaStorage::GetMSString(mst));
    switch (uid){
      case UIDs::AmbulatoryECGWaveformStorage:
        return eAmbulatoryECGWaveformStorage;
      case UIDs::BasicTextSRStorage:
        return eBasicTextSR;
      case UIDs::BasicVoiceAudioWaveformStorage:
        return eBasicVoiceAudioWaveformStorage;
      case UIDs::BlendingSoftcopyPresentationStateStorageSOPClass:
        return eBlendingSoftcopyPresentationStateStorage;
      case UIDs::CardiacElectrophysiologyWaveformStorage:
        return eCardiacElectrophysiologyWaveformStorage;
      case UIDs::ChestCADSRStorage:
        return eChestCADSR;
      case UIDs::ColorSoftcopyPresentationStateStorageSOPClass:
        return eColorSoftcopyPresentationStateStorage;
      case UIDs::ComprehensiveSRStorage:
        return eComprehensiveSR;
      case UIDs::ComputedRadiographyImageStorage:
        return eComputedRadiographyImageStorage;
      case UIDs::CTImageStorage:
        return eCTImageStorage;
      case UIDs::DigitalIntraoralXRayImageStorageForPresentation:
        return eDigitalIntraOralXRayImageStorageForPresentation;
      case UIDs::DigitalIntraoralXRayImageStorageForProcessing:
        return eDigitalIntraOralXRayImageStorageForProcessing;
      case UIDs::DigitalMammographyXRayImageStorageForPresentation:
        return eDigitalMammographyXRayImageStorageForPresentation;
      case UIDs::DigitalMammographyXRayImageStorageForProcessing:
        return eDigitalMammographyXRayImageStorageForProcessing;
      case UIDs::DigitalXRayImageStorageForPresentation:
        return eDigitalXRayImageStorageForPresentation;
      case UIDs::DigitalXRayImageStorageForProcessing:
        return eDigitalXRayImageStorageForProcessing;
      case UIDs::EncapsulatedPDFStorage:
        return eEncapsulatedPDFStorage;
      case UIDs::EnhancedCTImageStorage:
        return eEnhancedCTImageStorage;
      case UIDs::EnhancedMRImageStorage:
        return eEnhancedMRImageStorage;
      case UIDs::EnhancedSRStorage:
        return eEnhancedSR;
      case UIDs::EnhancedXAImageStorage:
        return eEnhancedXAImageStorage;
      case UIDs::EnhancedXRFImageStorage:
        return eEnhancedXRFImageStorage;
      case UIDs::GeneralECGWaveformStorage:
        return eGeneralECGWaveformStorage;
      case UIDs::GrayscaleSoftcopyPresentationStateStorageSOPClass:
        return eGrayscaleSoftcopyPresentationStateStorage;
      case UIDs::HemodynamicWaveformStorage:
        return eHemodynamicWaveformStorage;
      case UIDs::KeyObjectSelectionDocumentStorage:
        return eKeyObjectSelectionDocument;
      case UIDs::MammographyCADSRStorage:
        return eMammographyCADSR;
      case UIDs::MRImageStorage:
        return eMRImageStorage;
      case UIDs::MRSpectroscopyStorage:
        return eMRSpectroscopyStorage;
      case UIDs::MultiframeGrayscaleByteSecondaryCaptureImageStorage:
        return eMultiframeGrayscaleByteSecondaryCaptureImageStorage;
      case UIDs::MultiframeGrayscaleWordSecondaryCaptureImageStorage:
        return eMultiframeGrayscaleWordSecondaryCaptureImageStorage;
      case UIDs::MultiframeSingleBitSecondaryCaptureImageStorage:
        return eMultiframeSingleBitSecondaryCaptureImageStorage;
      case UIDs::MultiframeTrueColorSecondaryCaptureImageStorage:
        return eMultiframeTrueColorSecondaryCaptureImageStorage;
      case UIDs::NuclearMedicineImageStorage:
        return eNuclearMedicineImageStorage;
      case UIDs::OphthalmicPhotography16BitImageStorage:
        return eOphthalmicPhotography16BitImageStorage;
      case UIDs::OphthalmicPhotography8BitImageStorage:
        return eOphthalmicPhotography8BitImageStorage;
      //case UIDs::PositronEmissionTomographyImageStorage:
      //  return ePETCurveStorage;//!!!NOTE!  This isn't right! can we handle curve storage?
      case UIDs::PositronEmissionTomographyImageStorage:
        return ePETImageStorage;
      case UIDs::ProcedureLogStorage:
        return eProcedureLogStorage;
      case UIDs::PseudoColorSoftcopyPresentationStateStorageSOPClass:
        return ePseudoColorSoftcopyPresentationStateStorage;
      case UIDs::RawDataStorage:
        return eRawDataStorage;
      case UIDs::RealWorldValueMappingStorage:
        return eRealWorldValueMappingStorage;
      case UIDs::RTBeamsTreatmentRecordStorage:
        return eRTBeamsTreatmentRecordStorage;
      case UIDs::RTBrachyTreatmentRecordStorage:
        return eRTBrachyTreatmentRecordStorage;
      case UIDs::RTDoseStorage:
        return eRTDoseStorage;
      case UIDs::RTImageStorage:
        return eRTImageStorage;
      case UIDs::RTPlanStorage:
        return eRTPlanStorage;
      case UIDs::RTStructureSetStorage:
        return eRTStructureSetStorage;
      case UIDs::RTTreatmentSummaryRecordStorage:
        return eRTTreatmentSummaryRecordStorage;
      case UIDs::SecondaryCaptureImageStorage:
        return eSecondaryCaptureImageStorage;
      case UIDs::SpatialFiducialsStorage:
        return eSpatialFiducialsStorage;
      case UIDs::SpatialRegistrationStorage:
        return eSpatialRegistrationStorage;
      case UIDs::StereometricRelationshipStorage:
        return eStereometricRelationshipStorage;
      case UIDs::WaveformStorageTrialRetired://!!NOTE: I'm not sure these are equivalent
        return eTwelveLeadECGWaveformStorage;
      case UIDs::UltrasoundImageStorage:
        return eUltrasoundImageStorage;
      case UIDs::UltrasoundMultiframeImageStorage:
        return eUltrasoundMultiframeImageStorage;
      case UIDs::VLEndoscopicImageStorage:
        return eVLEndoscopicImageStorage;
      case UIDs::VLMicroscopicImageStorage:
        return eVLMicroscopicImageStorage;
      case UIDs::VLPhotographicImageStorage:
        return eVLPhotographicImageStorage;
      case UIDs::VLSlideCoordinatesMicroscopicImageStorage:
        return eVLSlideCoordinatesMicroscopicImageStorage;
      case UIDs::XRayAngiographicImageStorage:
        return eXRayAngiographicImageStorage;
      case UIDs::XRayRadiofluoroscopicImageStorage:
        return eXRayFluoroscopyImageStorage;
      case UIDs::XRayRadiationDoseSRStorage:
        return eXRayRadiationDoseSR;
      default:
        return eVerificationSOPClass;
    }
  }
}

} // end namespace network
} // end namespace gdcm
