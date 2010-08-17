/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmAAssociateRQPDU.h"
#include "gdcmAAssociateACPDU.h"
#include "gdcmPDataTFPDU.h"
#include "gdcmAReleaseRQPDU.h"

#include <fstream>
#include <socket++/echo.h>
#include <stdlib.h>

// Execute like this:
// ./bin/gdcmscu www.dicomserver.co.uk 11112 toto 
void CEcho( const char *remote, int portno )
{
  echo e(protocol::tcp);

  if (portno == 0)
    e->connect ( remote );
  else
    e->connect ( remote, portno);

  gdcm::network::AAssociateRQPDU cecho;
  cecho.SetCallingAETitle( "ECHOSCU" );

  gdcm::network::PresentationContext pc;
  gdcm::network::AbstractSyntax as;
  as.SetNameFromUID( gdcm::UIDs::VerificationSOPClass );
  pc.SetAbstractSyntax( as );

  gdcm::network::TransferSyntax_ ts;
  ts.SetNameFromUID( gdcm::UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM );
  pc.AddTransferSyntax( ts );

  cecho.AddPresentationContext( pc );
  cecho.Write(e);
  e.flush();

  gdcm::network::AAssociateACPDU acpdu;
  acpdu.Read( e );

  gdcm::network::PDataTPPDU pdata;
  //gdcm::network::PresentationDataValue pdv;
  //pdata.AddPresentationDataValue( pdv );
  pdata.Write( e );
  e.flush();

  // listen back
  gdcm::network::PDataTPPDU pdata2;
  pdata2.Read( e );

  // Print output DataSet:
  pdata2.GetPresentationDataValue(0).GetDataSet().Print( std::cout );

  // send release:
  gdcm::network::AReleaseRQPDU rel;
  rel.Write( e );

}

void CStore( const char *remote, int portno )
{
  echo e(protocol::tcp);

  if (portno == 0)
    e->connect ( remote );
  else
    e->connect ( remote, portno);

/*
I:     Abstract Syntax: =AmbulatoryECGWaveformStorage
I:     Abstract Syntax: =BasicTextSR
I:     Abstract Syntax: =BasicVoiceAudioWaveformStorage
I:     Abstract Syntax: =BlendingSoftcopyPresentationStateStorage
I:     Abstract Syntax: =CardiacElectrophysiologyWaveformStorage
I:     Abstract Syntax: =ChestCADSR
I:     Abstract Syntax: =ColorSoftcopyPresentationStateStorage
I:     Abstract Syntax: =ComprehensiveSR
I:     Abstract Syntax: =ComputedRadiographyImageStorage
I:     Abstract Syntax: =CTImageStorage
I:     Abstract Syntax: =DigitalIntraOralXRayImageStorageForPresentation
I:     Abstract Syntax: =DigitalIntraOralXRayImageStorageForProcessing
I:     Abstract Syntax: =DigitalMammographyXRayImageStorageForPresentation
I:     Abstract Syntax: =DigitalMammographyXRayImageStorageForProcessing
I:     Abstract Syntax: =DigitalXRayImageStorageForPresentation
I:     Abstract Syntax: =DigitalXRayImageStorageForProcessing
I:     Abstract Syntax: =EncapsulatedPDFStorage
I:     Abstract Syntax: =EnhancedCTImageStorage
I:     Abstract Syntax: =EnhancedMRImageStorage
I:     Abstract Syntax: =EnhancedSR
I:     Abstract Syntax: =EnhancedXAImageStorage
I:     Abstract Syntax: =EnhancedXRFImageStorage
I:     Abstract Syntax: =GeneralECGWaveformStorage
I:     Abstract Syntax: =GrayscaleSoftcopyPresentationStateStorage
I:     Abstract Syntax: =HemodynamicWaveformStorage
I:     Abstract Syntax: =KeyObjectSelectionDocument
I:     Abstract Syntax: =MammographyCADSR
I:     Abstract Syntax: =MRImageStorage
I:     Abstract Syntax: =MRSpectroscopyStorage
I:     Abstract Syntax: =MultiframeGrayscaleByteSecondaryCaptureImageStorage
I:     Abstract Syntax: =MultiframeGrayscaleWordSecondaryCaptureImageStorage
I:     Abstract Syntax: =MultiframeSingleBitSecondaryCaptureImageStorage
I:     Abstract Syntax: =MultiframeTrueColorSecondaryCaptureImageStorage
I:     Abstract Syntax: =NuclearMedicineImageStorage
I:     Abstract Syntax: =OphthalmicPhotography16BitImageStorage
I:     Abstract Syntax: =OphthalmicPhotography8BitImageStorage
I:     Abstract Syntax: =PETCurveStorage
I:     Abstract Syntax: =PETImageStorage
I:     Abstract Syntax: =ProcedureLogStorage
I:     Abstract Syntax: =PseudoColorSoftcopyPresentationStateStorage
I:     Abstract Syntax: =RawDataStorage
I:     Abstract Syntax: =RealWorldValueMappingStorage
I:     Abstract Syntax: =RTBeamsTreatmentRecordStorage
I:     Abstract Syntax: =RTBrachyTreatmentRecordStorage
I:     Abstract Syntax: =RTDoseStorage
I:     Abstract Syntax: =RTImageStorage
I:     Abstract Syntax: =RTPlanStorage
I:     Abstract Syntax: =RTStructureSetStorage
I:     Abstract Syntax: =RTTreatmentSummaryRecordStorage
I:     Abstract Syntax: =SecondaryCaptureImageStorage
I:     Abstract Syntax: =SpatialFiducialsStorage
I:     Abstract Syntax: =SpatialRegistrationStorage
I:     Abstract Syntax: =StereometricRelationshipStorage
I:     Abstract Syntax: =TwelveLeadECGWaveformStorage
I:     Abstract Syntax: =UltrasoundImageStorage
I:     Abstract Syntax: =UltrasoundMultiframeImageStorage
I:     Abstract Syntax: =VLEndoscopicImageStorage
I:     Abstract Syntax: =VLMicroscopicImageStorage
I:     Abstract Syntax: =VLPhotographicImageStorage
I:     Abstract Syntax: =VLSlideCoordinatesMicroscopicImageStorage
I:     Abstract Syntax: =XRayAngiographicImageStorage
I:     Abstract Syntax: =XRayFluoroscopyImageStorage
I:     Abstract Syntax: =XRayRadiationDoseSR
*/
  gdcm::network::TransferSyntax_ ts;
  //ts.SetNameFromUID( gdcm::UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM );
  ts.SetNameFromUID( gdcm::UIDs::ExplicitVRLittleEndian );

  gdcm::network::AAssociateRQPDU cstore;
  cstore.SetCallingAETitle( "STORESCU" );

  gdcm::UIDs::TSName begin = gdcm::UIDs::AmbulatoryECGWaveformStorage; // 136
  //gdcm::UIDs::TSName end   = gdcm::UIDs::HemodynamicWaveformStorage;
  gdcm::UIDs::TSName end   = gdcm::UIDs::BasicTextSRStorage; // 177
  unsigned int id = 1;
  for( unsigned int tsname = begin; tsname <= end; ++tsname, id +=2  )
    {
    gdcm::network::AbstractSyntax as;
    as.SetNameFromUID( (gdcm::UIDs::TSName)tsname );

    gdcm::network::PresentationContext pc;
    pc.SetPresentationContextID( id );
    pc.SetAbstractSyntax( as );
    pc.AddTransferSyntax( ts );
    cstore.AddPresentationContext( pc );
    }

  cstore.Write(e);
  e.flush();

  gdcm::network::AAssociateACPDU acpdu;
  acpdu.Read( e );

}

int main(int argc, char *argv[])
{
 if (argc < 3)
   {
   std::cerr << "Usage: " << argv [0] << " remote-host portno" << std::endl;
   return 1;
   }

  int portno = atoi (argv [2]);

  //CEcho( argv[1], portno );
  CStore( argv[1], portno );

  return 0;
}
