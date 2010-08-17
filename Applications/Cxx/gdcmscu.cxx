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
#include "gdcmAAbortPDU.h"
#include "gdcmReader.h"

#include <fstream>
#include <socket++/echo.h>
#include <stdlib.h>

// Execute like this:
// ./bin/gdcmscu www.dicomserver.co.uk 11112
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
  acpdu.Print( std::cout );
  //std::ofstream b( "/tmp/d1234" );
  //acpdu.Write( b );
  //b.close();

  gdcm::network::PDataTFPDU pdata;
  gdcm::network::PresentationDataValue pdv;
  pdata.AddPresentationDataValue( pdv );
  pdata.Write( e );
  e.flush();

  // listen back
  gdcm::network::PDataTFPDU pdata2;
  pdata2.Read( e );

  // Print output DataSet:
  pdata2.GetPresentationDataValue(0).GetDataSet().Print( std::cout );

  // send release:
  gdcm::network::AReleaseRQPDU rel;
  rel.Write( e );

}

static void process_input(iosockinet& sio)
{
  gdcm::network::AAssociateRQPDU rqpdu;
  rqpdu.Read( sio );

  std::cout << "done AAssociateRQPDU !" << std::endl;

  gdcm::network::PresentationContextAC pcac;
  gdcm::network::TransferSyntax_ ts;
  ts.SetNameFromUID( gdcm::UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM );
  pcac.SetTransferSyntax( ts );

  {
  std::ofstream b( "/tmp/dummys" );
  pcac.Write( b );
  b.close();
  }
  {
  std::ifstream b( "/tmp/dummys" );
  uint8_t itemtype = 0x0;
  b.read( (char*)&itemtype, 1 );
  assert( itemtype == 0x21 );
  pcac.Read( b );
  b.close();
  }

  gdcm::network::AAssociateACPDU acpdu;
  acpdu.AddPresentationContextAC( pcac );
  acpdu.Write( sio );
  std::ofstream b( "/tmp/d1234-bis" );
  acpdu.Write( b );
  b.close();
  sio.flush();
  std::cout << "done AAssociateACPDU!" << std::endl;

  gdcm::network::PDataTFPDU pdata;
  pdata.Read( sio );

  std::cout << "done PDataTFPDU!" << std::endl;

  gdcm::network::PDataTFPDU pdata2;
  gdcm::network::PresentationDataValue pdv;
  pdata2.AddPresentationDataValue( pdv );
  pdata2.Write( sio );
  sio.flush();

  std::cout << "done PDataTFPDU 2!" << std::endl;

  gdcm::network::AReleaseRQPDU rel;
  rel.Read( sio );

  std::cout << "done AReleaseRQPDU " << std::endl;

}

// Execute like this:
// ./bin/gdcmscu www.dicomserver.co.uk 11112 server
void CEchoServer( int portno )
{
  /*
  echo server (protocol::tcp);
  server->serve_clients ( portno );
  */

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
  ts.SetNameFromUID( gdcm::UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM );
  //ts.SetNameFromUID( gdcm::UIDs::ExplicitVRLittleEndian );

  gdcm::network::AAssociateRQPDU cstore;
  cstore.SetCallingAETitle( "STORESCU" );

  //gdcm::UIDs::TSName begin = gdcm::UIDs::AmbulatoryECGWaveformStorage; // 136
  gdcm::UIDs::TSName begin = gdcm::UIDs::ComputedRadiographyImageStorage; // 109
  //gdcm::UIDs::TSName end   = gdcm::UIDs::HemodynamicWaveformStorage;
  //gdcm::UIDs::TSName end   = gdcm::UIDs::BasicTextSRStorage; // 177
  gdcm::UIDs::TSName end   = gdcm::UIDs::RTIonBeamsTreatmentRecordStorage; // 197
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

  gdcm::Reader r;
  r.SetFileName( "/tmp/send3.dcm" );
  r.Read();

  gdcm::network::PresentationDataValue pdv;
  pdv.SetPresentationContextID( 197 );
  pdv.MyInit( r.GetFile() );

  gdcm::network::PresentationDataValue pdv2;
  pdv2.SetPresentationContextID( 197 );
  pdv2.SetDataSet( r.GetFile().GetDataSet() );

  gdcm::network::PDataTFPDU pdata;
  pdata.AddPresentationDataValue( pdv );
  //pdata.AddPresentationDataValue( pdv2 );
  pdata.Write( e );
  e.flush();

  gdcm::network::PDataTFPDU pdata2;
  pdata2.AddPresentationDataValue( pdv2 );
  pdata.Write( e );

  e.flush();

  // listen back
  gdcm::network::AAbortPDU ab;
  ab.Read( e );

  //ab.Print( std::cout );

//  gdcm::network::PDataTFPDU pdata3;
//  pdata3.Read( e );
//
//  // Print output DataSet:
//  pdata3.GetPresentationDataValue(0).GetDataSet().Print( std::cout );
//
//  // send release:
//  gdcm::network::AReleaseRQPDU rel;
//  rel.Write( e );

}

static void process_input2(iosockinet& sio)
{
  gdcm::network::AAssociateRQPDU rqpdu;
  rqpdu.Read( sio );

  std::cout << "done AAssociateRQPDU !" << std::endl;

  gdcm::network::PresentationContextAC pcac;
  gdcm::network::TransferSyntax_ ts;
  ts.SetNameFromUID( gdcm::UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM );
  pcac.SetTransferSyntax( ts );

  gdcm::network::AAssociateACPDU acpdu;
  acpdu.AddPresentationContextAC( pcac );
  acpdu.Write( sio );
  sio.flush();

  std::cout << "done AAssociateACPDU !" << std::endl;

  gdcm::network::PDataTFPDU pdata;
  //pdata.Read( sio );

  std::ofstream out("/tmp/storescu");
  char b;
  while( sio >> b )
    {
    out.write( &b, 1 );
    out.flush();
    std::cout << "Found: " << (int)b << std::endl;
    }

  std::cout << "done PDataTFPDU!" << std::endl;

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
      process_input2(s);
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

  if ( mode == "server" )
    {
    //CEchoServer( portno );
    CStoreServer( portno );
    }
  else
    {
    //CEcho( argv[1], portno );
    CStore( argv[1], portno );
    }
  return 0;
}
