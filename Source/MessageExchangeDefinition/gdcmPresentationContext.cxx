/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "gdcmPresentationContext.h"
#include "gdcmUIDs.h"
#include "gdcmSwapper.h"
#include "gdcmAttribute.h"
#include "gdcmDefs.h"
#include "gdcmGlobal.h"
#include "gdcmMediaStorage.h"
#include "gdcmSOPClassUIDToIOD.h"
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

  size_t lenTemp = Size() - 4;
  assert(lenTemp < (size_t)std::numeric_limits<uint16_t>::max);
  ItemLength = (uint16_t)lenTemp;
  assert( ItemLength + 4 == Size() );
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

  assert( ItemLength + 4 == Size() );
  return is;
}

const std::ostream &PresentationContext::Write(std::ostream &os) const
{
  assert( ItemLength + 4 == Size() );
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

  return ret;
}

void PresentationContext::SetAbstractSyntax( AbstractSyntax const & as )
{
  SubItems = as;
  size_t lenTemp = Size() - 4;
  assert(lenTemp < (size_t)std::numeric_limits<uint16_t>::max);
  ItemLength = (uint16_t)lenTemp;
  assert( ItemLength + 4 == Size() );
}

void PresentationContext::AddTransferSyntax( TransferSyntaxSub const &ts )
{
  TransferSyntaxes.push_back( ts );
  size_t lenTemp = Size() - 4;
  assert(lenTemp < (size_t)std::numeric_limits<uint16_t>::max);
  ItemLength = (uint16_t)lenTemp;
  assert( ItemLength + 4 == Size() );
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
    using gdcm::MediaStorage;
    gdcm::Global& g = gdcm::Global::GetInstance();
#if 0
    if( !g.LoadResourcesFiles() ) // NOT THREAD SAFE
      {
      std::cerr << "Could not LoadResourcesFiles" << std::endl;
      return eVerificationSOPClass;
      }
#endif
    const gdcm::Defs &defs = g.GetDefs();
    gdcm::MediaStorage mst;
    if (!mst.SetFromDataSet(inDS)){
      return eVerificationSOPClass;
    }
    const char *iod = defs.GetIODNameFromMediaStorage(mst);
    gdcm::UIDs uid;//want to get this as well, to set the abstract syntax properly
    uid.SetFromUID( gdcm::MediaStorage::GetMSString(mst) /*mst.GetString()*/ );
    outUIDString = std::string(gdcm::MediaStorage::GetMSString(mst));
    switch (uid){
      case gdcm::UIDs::AmbulatoryECGWaveformStorage:
        return eAmbulatoryECGWaveformStorage;
      case gdcm::UIDs::BasicTextSRStorage:
        return eBasicTextSR;
      case gdcm::UIDs::BasicVoiceAudioWaveformStorage:
        return eBasicVoiceAudioWaveformStorage;
      case gdcm::UIDs::BlendingSoftcopyPresentationStateStorageSOPClass:
        return eBlendingSoftcopyPresentationStateStorage;
      case gdcm::UIDs::CardiacElectrophysiologyWaveformStorage:
        return eCardiacElectrophysiologyWaveformStorage;
      case gdcm::UIDs::ChestCADSRStorage:
        return eChestCADSR;
      case gdcm::UIDs::ColorSoftcopyPresentationStateStorageSOPClass:
        return eColorSoftcopyPresentationStateStorage;
      case gdcm::UIDs::ComprehensiveSRStorage:
        return eComprehensiveSR;
      case gdcm::UIDs::ComputedRadiographyImageStorage:
        return eComputedRadiographyImageStorage;
      case gdcm::UIDs::CTImageStorage:
        return eCTImageStorage;
      case gdcm::UIDs::DigitalIntraoralXRayImageStorageForPresentation:
        return eDigitalIntraOralXRayImageStorageForPresentation;
      case gdcm::UIDs::DigitalIntraoralXRayImageStorageForProcessing:
        return eDigitalIntraOralXRayImageStorageForProcessing;
      case gdcm::UIDs::DigitalMammographyXRayImageStorageForPresentation:
        return eDigitalMammographyXRayImageStorageForPresentation;
      case gdcm::UIDs::DigitalMammographyXRayImageStorageForProcessing:
        return eDigitalMammographyXRayImageStorageForProcessing;
      case gdcm::UIDs::DigitalXRayImageStorageForPresentation:
        return eDigitalXRayImageStorageForPresentation;
      case gdcm::UIDs::DigitalXRayImageStorageForProcessing:
        return eDigitalXRayImageStorageForProcessing;
      case gdcm::UIDs::EncapsulatedPDFStorage:
        return eEncapsulatedPDFStorage;
      case gdcm::UIDs::EnhancedCTImageStorage:
        return eEnhancedCTImageStorage;
      case gdcm::UIDs::EnhancedMRImageStorage:
        return eEnhancedMRImageStorage;
      case gdcm::UIDs::EnhancedSRStorage:
        return eEnhancedSR;
      case gdcm::UIDs::EnhancedXAImageStorage:
        return eEnhancedXAImageStorage;
      case gdcm::UIDs::EnhancedXRFImageStorage:
        return eEnhancedXRFImageStorage;
      case gdcm::UIDs::GeneralECGWaveformStorage:
        return eGeneralECGWaveformStorage;
      case gdcm::UIDs::GrayscaleSoftcopyPresentationStateStorageSOPClass:
        return eGrayscaleSoftcopyPresentationStateStorage;
      case gdcm::UIDs::HemodynamicWaveformStorage:
        return eHemodynamicWaveformStorage;
      case gdcm::UIDs::KeyObjectSelectionDocumentStorage:
        return eKeyObjectSelectionDocument;
      case gdcm::UIDs::MammographyCADSRStorage:
        return eMammographyCADSR;
      case gdcm::UIDs::MRImageStorage:
        return eMRImageStorage;
      case gdcm::UIDs::MRSpectroscopyStorage:
        return eMRSpectroscopyStorage;
      case gdcm::UIDs::MultiframeGrayscaleByteSecondaryCaptureImageStorage:
        return eMultiframeGrayscaleByteSecondaryCaptureImageStorage;
      case gdcm::UIDs::MultiframeGrayscaleWordSecondaryCaptureImageStorage:
        return eMultiframeGrayscaleWordSecondaryCaptureImageStorage;
      case gdcm::UIDs::MultiframeSingleBitSecondaryCaptureImageStorage:
        return eMultiframeSingleBitSecondaryCaptureImageStorage;
      case gdcm::UIDs::MultiframeTrueColorSecondaryCaptureImageStorage:
        return eMultiframeTrueColorSecondaryCaptureImageStorage;
      case gdcm::UIDs::NuclearMedicineImageStorage:
        return eNuclearMedicineImageStorage;
      case gdcm::UIDs::OphthalmicPhotography16BitImageStorage:
        return eOphthalmicPhotography16BitImageStorage;
      case gdcm::UIDs::OphthalmicPhotography8BitImageStorage:
        return eOphthalmicPhotography8BitImageStorage;
      //case gdcm::UIDs::PositronEmissionTomographyImageStorage:
      //  return ePETCurveStorage;//!!!NOTE!  This isn't right! can we handle curve storage?
      case gdcm::UIDs::PositronEmissionTomographyImageStorage:
        return ePETImageStorage;
      case gdcm::UIDs::ProcedureLogStorage:
        return eProcedureLogStorage;
      case gdcm::UIDs::PseudoColorSoftcopyPresentationStateStorageSOPClass:
        return ePseudoColorSoftcopyPresentationStateStorage;
      case gdcm::UIDs::RawDataStorage:
        return eRawDataStorage;
      case gdcm::UIDs::RealWorldValueMappingStorage:
        return eRealWorldValueMappingStorage;
      case gdcm::UIDs::RTBeamsTreatmentRecordStorage:
        return eRTBeamsTreatmentRecordStorage;
      case gdcm::UIDs::RTBrachyTreatmentRecordStorage:
        return eRTBrachyTreatmentRecordStorage;
      case gdcm::UIDs::RTDoseStorage:
        return eRTDoseStorage;
      case gdcm::UIDs::RTImageStorage:
        return eRTImageStorage;
      case gdcm::UIDs::RTPlanStorage:
        return eRTPlanStorage;
      case gdcm::UIDs::RTStructureSetStorage:
        return eRTStructureSetStorage;
      case gdcm::UIDs::RTTreatmentSummaryRecordStorage:
        return eRTTreatmentSummaryRecordStorage;
      case gdcm::UIDs::SecondaryCaptureImageStorage:
        return eSecondaryCaptureImageStorage;
      case gdcm::UIDs::SpatialFiducialsStorage:
        return eSpatialFiducialsStorage;
      case gdcm::UIDs::SpatialRegistrationStorage:
        return eSpatialRegistrationStorage;
      case gdcm::UIDs::StereometricRelationshipStorage:
        return eStereometricRelationshipStorage;
      case gdcm::UIDs::WaveformStorageTrialRetired://!!NOTE: I'm not sure these are equivalent
        return eTwelveLeadECGWaveformStorage;
      case gdcm::UIDs::UltrasoundImageStorage:
        return eUltrasoundImageStorage;
      case gdcm::UIDs::UltrasoundMultiframeImageStorage:
        return eUltrasoundMultiframeImageStorage;
      case gdcm::UIDs::VLEndoscopicImageStorage:
        return eVLEndoscopicImageStorage;
      case gdcm::UIDs::VLMicroscopicImageStorage:
        return eVLMicroscopicImageStorage;
      case gdcm::UIDs::VLPhotographicImageStorage:
        return eVLPhotographicImageStorage;
      case gdcm::UIDs::VLSlideCoordinatesMicroscopicImageStorage:
        return eVLSlideCoordinatesMicroscopicImageStorage;
      case gdcm::UIDs::XRayAngiographicImageStorage:
        return eXRayAngiographicImageStorage;
      case gdcm::UIDs::XRayRadiofluoroscopicImageStorage:
        return eXRayFluoroscopyImageStorage;
      case gdcm::UIDs::XRayRadiationDoseSRStorage:
        return eXRayRadiationDoseSR;
      default:
        return eVerificationSOPClass;
    }
  }
}

} // end namespace network
} // end namespace gdcm
