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

#ifndef GDCMPRESENTATIONCONTEXT_H
#define GDCMPRESENTATIONCONTEXT_H

#include "gdcmTypes.h"
#include "gdcmAbstractSyntax.h"
#include "gdcmTransferSyntax_.h"
#include "gdcmDataSet.h"

namespace gdcm
{

namespace network
{


//the presentation context id is arbitrary per connection
//so, just to make life easier for now, the ID will be the same as the UID of the type
//that way, when the return comes, the selected presentation context can be used
//by the service by referring to the ID.
//we cannot use the UID const directly, since that's not guaranteed to be lower
//than 255, and the number has to be within a byte
enum EPresentationContextID {
  eVerificationSOPClass = 1,
  ePatientRootQueryRetrieveInformationModelFIND = 3,
  eStudyRootQueryRetrieveInformationModelFIND = 5,
  ePatientStudyOnlyQueryRetrieveInformationModelFINDRetired = 7,
  eModalityWorklistInformationModelFIND = 9,
  eGeneralPurposeWorklistInformationModelFIND = 11,
  ePatientRootQueryRetrieveInformationModelMOVE = 13,
  eStudyRootQueryRetrieveInformationModelMOVE = 15,
  ePatientStudyOnlyQueryRetrieveInformationModelMOVERetired = 17,
  eAmbulatoryECGWaveformStorage = 19,
  eBasicTextSR = 21,
  eBasicVoiceAudioWaveformStorage = 23,
  eBlendingSoftcopyPresentationStateStorage = 25,
  eCardiacElectrophysiologyWaveformStorage = 27,
  eChestCADSR = 29,
  eColorSoftcopyPresentationStateStorage = 31,
  eComprehensiveSR = 33,
  eComputedRadiographyImageStorage = 35,
  eCTImageStorage = 37,
  eDigitalIntraOralXRayImageStorageForPresentation = 39,
  eDigitalIntraOralXRayImageStorageForProcessing = 41,
  eDigitalMammographyXRayImageStorageForPresentation = 43,
  eDigitalMammographyXRayImageStorageForProcessing = 45,
  eDigitalXRayImageStorageForPresentation = 47,
  eDigitalXRayImageStorageForProcessing = 49,
  eEncapsulatedPDFStorage = 51,
  eEnhancedCTImageStorage = 53,
  eEnhancedMRImageStorage = 55,
  eEnhancedSR = 57,
  eEnhancedXAImageStorage = 59,
  eEnhancedXRFImageStorage= 61,
  eGeneralECGWaveformStorage = 63,
  eGrayscaleSoftcopyPresentationStateStorage = 65,
  eHemodynamicWaveformStorage = 67,
  eKeyObjectSelectionDocument = 69,
  eMammographyCADSR = 71,
  eMRImageStorage = 73,
  eMRSpectroscopyStorage = 75,
  eMultiframeGrayscaleByteSecondaryCaptureImageStorage = 77,
  eMultiframeGrayscaleWordSecondaryCaptureImageStorage = 79,
  eMultiframeSingleBitSecondaryCaptureImageStorage = 81,
  eMultiframeTrueColorSecondaryCaptureImageStorage = 83,
  eNuclearMedicineImageStorage = 85,
  eOphthalmicPhotography16BitImageStorage = 87,
  eOphthalmicPhotography8BitImageStorage = 89,
  ePETCurveStorage = 91,
  ePETImageStorage = 93,
  eProcedureLogStorage = 95,
  ePseudoColorSoftcopyPresentationStateStorage = 97,
  eRawDataStorage = 99,
  eRealWorldValueMappingStorage = 101,
  eRTBeamsTreatmentRecordStorage = 103,
  eRTBrachyTreatmentRecordStorage = 105,
  eRTDoseStorage = 107,
  eRTImageStorage = 109,
  eRTPlanStorage = 111,
  eRTStructureSetStorage = 113,
  eRTTreatmentSummaryRecordStorage = 115,
  eSecondaryCaptureImageStorage = 117,
  eSpatialFiducialsStorage = 119,
  eSpatialRegistrationStorage = 121,
  eStereometricRelationshipStorage = 123,
  eTwelveLeadECGWaveformStorage = 125,
  eUltrasoundImageStorage = 127,
  eUltrasoundMultiframeImageStorage = 129,
  eVLEndoscopicImageStorage = 131,
  eVLMicroscopicImageStorage = 133,
  eVLPhotographicImageStorage = 135,
  eVLSlideCoordinatesMicroscopicImageStorage = 137,
  eXRayAngiographicImageStorage = 139,
  eXRayFluoroscopyImageStorage = 141,
  eXRayRadiationDoseSR = 143
};

/**
 Table 9-13
 PRESENTATION CONTEXT ITEM FIELDS
\see PresentationContextAC
 */
class GDCM_EXPORT PresentationContext
{
public:
  PresentationContext();
  std::istream &Read(std::istream &is);
  const std::ostream &Write(std::ostream &os) const;
  size_t Size() const;

  void SetAbstractSyntax( AbstractSyntax const & as );
  AbstractSyntax const &GetAbstractSyntax() const { return SubItems; }

  void AddTransferSyntax( TransferSyntax_ const &ts );

  void SetPresentationContextID( uint8_t id );
  uint8_t GetPresentationContextID() const;

  void Print(std::ostream &os) const;

  //this function will return the appropriate ID from the above
  //list, after querying the appropriate tag in the dataset.  If the tag above
  //does not exist, then the result is a pure verification ID.
  //if the operation is something other than an echo, that should be interpreted
  //as a failure; echos themselves take a null dataset.
  //it is assumed that Find will do the Right Thing, or that the find class is unimportant.
  //however, this function could be extended in the future to validate that a given
  //dataset conforms to the expectations of a particular FIND SOP abstract syntax, if necessary.
  //current tests (7 oct 2010) show that for our test queries, find SOP didn't
  //change the outcome of the search.
  //if it's not a verification context ID, then you can also get the UID associated with the data set.
  static EPresentationContextID AssignPresentationContextID(const DataSet& inDS, std::string& outUIDString);

private:
  static const uint8_t ItemType;
  static const uint8_t Reserved2;
  uint16_t ItemLength; // len of last transfer syntax
  uint8_t /*PresentationContext*/ID;
  static const uint8_t Reserved6;
  static const uint8_t Reserved7;
  static const uint8_t Reserved8;
/*
This variable field shall contain the following sub-items: one Abstract
Syntax and one or more Transfer Syntax(es). For a complete
description of the use and encoding of these sub-items see Sections
9.3.2.2.1 and 9.3.2.2.2.
*/

  AbstractSyntax SubItems;
  std::vector<TransferSyntax_> TransferSyntaxes;
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMPRESENTATIONCONTEXT_H
