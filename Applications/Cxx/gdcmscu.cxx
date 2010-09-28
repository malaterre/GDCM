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
#include "gdcmAReleaseRPPDU.h"
#include "gdcmAAssociateACPDU.h"
#include "gdcmPDataTFPDU.h"
#include "gdcmAReleaseRQPDU.h"
#include "gdcmAReleaseRPPDU.h"
#include "gdcmAAbortPDU.h"
#include "gdcmReader.h"
#include "gdcmAAssociateRJPDU.h"
#include "gdcmAssociationEstablishment.h"
#include "gdcmDataTransfer.h"
#include "gdcmAttribute.h"
#include "gdcmAssociationRelease.h"
#include "gdcmULConnectionManager.h"

#include <fstream>
#include <socket++/echo.h>
#include <stdlib.h>

// Execute like this:
// ./bin/gdcmscu www.dicomserver.co.uk 11112 echo
void CEcho( const char *remote, int portno )
{
  /*
  echo e(protocol::tcp);

  if (portno == 0)
    e->connect ( remote );
  else
    e->connect ( remote, portno);

  gdcm::network::AssociationEstablishment ae;
  ae.Run(e);

  gdcm::network::DataTransfer dt;
  dt.Run(e);
  e.flush();

  gdcm::network::AssociationRelease ar;
  ar.Run(e);
*/
  gdcm::network::ULConnectionManager theManager;
  theManager.EstablishConnection("ACME1", "A", remote, 0, portno, 1000);
  theManager.SendEcho();
  theManager.SendEcho();
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite

}

void CStore( const char *remote, int portno, std::string const & filename )
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
  ts.SetNameFromUID( gdcm::UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM );
  //ts.SetNameFromUID( gdcm::UIDs::ExplicitVRLittleEndian );

  gdcm::network::AAssociateRQPDU cstore;
  cstore.SetCallingAETitle( "STORESCU" );

  //gdcm::UIDs::TSName begin = gdcm::UIDs::AmbulatoryECGWaveformStorage; // 136
  gdcm::UIDs::TSName begin = gdcm::UIDs::ComputedRadiographyImageStorage; // 109
  //gdcm::UIDs::TSName end   = gdcm::UIDs::HemodynamicWaveformStorage;
  //gdcm::UIDs::TSName end   = gdcm::UIDs::BasicTextSRStorage; // 177
  gdcm::UIDs::TSName end   = gdcm::UIDs::RTIonBeamsTreatmentRecordStorage; // 197
//  unsigned int id = 1;
//  for( unsigned int tsname = begin; tsname <= end; ++tsname, id +=2  )
//    {
//    gdcm::network::AbstractSyntax as;
//    as.SetNameFromUID( (gdcm::UIDs::TSName)tsname );
//
//    gdcm::network::PresentationContext pc;
//    pc.SetPresentationContextID( id );
//    pc.SetAbstractSyntax( as );
//    pc.AddTransferSyntax( ts );
//    cstore.AddPresentationContext( pc );
//    }

    gdcm::network::AbstractSyntax as;
    as.SetNameFromUID( gdcm::UIDs::SecondaryCaptureImageStorage );

    gdcm::network::PresentationContext pc;
    pc.SetPresentationContextID( 197 );
    pc.SetAbstractSyntax( as );
    pc.AddTransferSyntax( ts );
    cstore.AddPresentationContext( pc );

  cstore.Write(e);
  e.flush();

  uint8_t itemtype = 0;
  e.read( (char*)&itemtype, 1 );
  gdcm::network::AAssociateACPDU acpdu;
  switch ( itemtype )
    {
  case 0x2:
    acpdu.Read( e );
    break;
  default:
    assert( 0 );
    throw "Unimplemented";
    }

  gdcm::network::AAssociateACPDU::SizeType s = acpdu.GetNumberOfPresentationContextAC();
  std::cout << "BEGIN AAssociateACPDU: " << std::endl;
  acpdu.Print( std::cout );
  std::cout << "END AAssociateACPDU: " << std::endl;

  gdcm::Reader r;
  r.SetFileName( "/tmp/send3.dcm" ); // FIXME: use 'filename'
  r.Read();

  {
  gdcm::network::PresentationDataValue pdv;
  pdv.SetPresentationContextID( 197 );
  pdv.MyInit( r.GetFile() );

  gdcm::network::PDataTFPDU pdata;
  pdata.AddPresentationDataValue( pdv );
  pdata.Write( e );
  e.flush();
  }
  std::cout << "done PDataTFPDU 1!" << std::endl;

  {
  gdcm::network::PresentationDataValue pdv2;
  pdv2.SetPresentationContextID( 197 );
  pdv2.SetDataSet( r.GetFile().GetDataSet() );
  pdv2.SetMessageHeader( 2 );

  gdcm::network::PDataTFPDU pdata2;
  pdata2.AddPresentationDataValue( pdv2 );
  pdata2.Write( e );
  e.flush();
  }
  std::cout << "done PDataTFPDU 2!" << std::endl;

  gdcm::network::PDataTFPDU pdata3;
  pdata3.Read( e );
  pdata3.Print( std::cout );

  gdcm::network::AssociationRelease ar;
  ar.Run(e);

}

static void process_input(iosockinet& sio)
{
  gdcm::network::AAssociateRQPDU rqpdu;
  rqpdu.SetCallingAETitle( "STORESCU" );
  rqpdu.Read( sio );
  //rqpdu.Print( std::cout );

  std::cout << "done AAssociateRQPDU !" << std::endl;

  gdcm::network::TransferSyntax_ ts1;
  ts1.SetNameFromUID( gdcm::UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM );

  gdcm::network::TransferSyntax_ ts2;
  ts2.SetNameFromUID( gdcm::UIDs::ExplicitVRLittleEndian );

  gdcm::network::TransferSyntax_ ts3;
  ts3.SetNameFromUID( gdcm::UIDs::ExplicitVRBigEndian );

  gdcm::network::AAssociateACPDU acpdu;
  for( unsigned int id = 1; id < 252; id += 4  )
    {
    gdcm::network::PresentationContextAC pcac1;
    pcac1.SetPresentationContextID( id );
    pcac1.SetTransferSyntax( ts2 );
    acpdu.AddPresentationContextAC( pcac1 );

    gdcm::network::PresentationContextAC pcac2;
    pcac2.SetPresentationContextID( id + 2 );
    pcac2.SetTransferSyntax( ts3 );
    acpdu.AddPresentationContextAC( pcac2 );
    }

  acpdu.Write( sio );
  sio.flush();

  std::cout << "done AAssociateACPDU !" << std::endl;

  gdcm::network::PDataTFPDU pdata;
  pdata.Read( sio );
  //pdata.Print( std::cout );
  // pick the first one:
  gdcm::network::PresentationDataValue const &input_pdv = pdata.GetPresentationDataValue(0);

  std::cout << "done PDataTFPDU 1!" << std::endl;

  uint8_t messageheader;
  messageheader = input_pdv.GetMessageHeader();

  std::cout << "Start with MessageHeader : " << (int)messageheader << std::endl;
  //input_pdv.GetDataSet().Print (std::cout);

  gdcm::Attribute<0x0,0x800> at = { 0 };
  at.SetFromDataSet( input_pdv.GetDataSet() );
  unsigned short commanddatasettype = at.GetValue();
  std::cout << "CommandDataSetType: " << at.GetValue() << std::endl;
  assert( messageheader == 3 );

  // C-STORE
  if( commanddatasettype == 1 )
    {
    std::ofstream out( "/tmp/storescu.dcm" );
    int i = 0;
    do
      {
      gdcm::network::PDataTFPDU pdata2;
      pdata2.ReadInto( sio, out );
      //pdata2.Print( std::cout );
      gdcm::network::PresentationDataValue const &pdv = pdata2.GetPresentationDataValue(0);
      messageheader = pdv.GetMessageHeader();
      std::cout << "---------------- done PDataTFPDU: " << i << std::endl;
      std::cout << "---------------- done MessageHeader: " << (int)messageheader << std::endl;
      ++i;
      }
    while( messageheader == 0 );
    assert( messageheader == 2 ); // end of data

    //gdcm::network::PDataTFPDU pdata3;
    //pdata3.ReadInto( sio, out );
    //pdata3.Print( std::cout );
    //gdcm::network::PresentationDataValue const &pdv3 = pdata3.GetPresentationDataValue(0);
    //messageheader = pdv3.GetMessageHeader();
    //std::cout << "---------------- done PDataTFPDU: " << i << std::endl;
    //std::cout << "---------------- done MessageHeader: " << (int)messageheader << std::endl;

    out.close();

    gdcm::network::PresentationDataValue pdv;
    pdv.SetPresentationContextID( input_pdv.GetPresentationContextID() );
    gdcm::File f;
    pdv.MyInit2( f );

    //std::cout << "Compare:" << std::endl;
    //input_pdv.Print( std::cout );
    //std::cout << "To:" << std::endl;
    //pdv.Print( std::cout );

    gdcm::network::PDataTFPDU pdata4;
    pdata4.AddPresentationDataValue( pdv );
    pdata4.Write( sio );

    }
  // C-ECHO
  else if( commanddatasettype == 257 )
    {
    gdcm::network::PDataTFPDU pdata2;
    gdcm::network::PresentationDataValue pdv;
    pdv.MyInit3();
    pdata2.AddPresentationDataValue( pdv );
    pdata2.Write( sio );
    sio.flush();

    }
  else 
    {
    assert( 0 );
    }


  // send release:
  gdcm::network::AReleaseRPPDU rel;
  rel.Write( sio );
  sio.flush();

  std::cout << "done AReleaseRPPDU!" << std::endl;

  gdcm::network::AReleaseRPPDU rel2;
  rel2.Write( sio );
  sio.flush();
}

void CStoreServer( int portno )
{
  sockinetbuf sin (sockbuf::sock_stream);

  //sin.bind( );
  sin.bind( portno );

  std::cout << "localhost = " << sin.localhost() << std::endl
    << "localport = " << sin.localport() << std::endl;

  sin.listen();

  for(;;)
    {
    iosockinet s (sin.accept());
    process_input(s);
    }
}

int main(int argc, char *argv[])
{
 if (argc < 3)
   {
   std::cerr << "Usage: " << argv [0] << " remote-host portno" << std::endl;
   return 1;
   }

  int portno = atoi (argv [2]);

  std::string mode;
  if (argc == 4)
    {
    mode = argv[3];
    }

  if ( mode == "server" ) // C-STORE SCP
    {
    CStoreServer( portno );
    }
  else if ( mode == "echo" ) // C-ECHO SCU
    {
    CEcho( argv[1], portno );
    }
  else // C-STORE SCU
    {
    // mode == filename
    CStore( argv[1], portno, mode );
    }
  return 0;
}
