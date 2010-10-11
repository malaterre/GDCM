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
/*
 * Simple command line tool to echo/store/find/move DICOM using
 * DICOM Query/Retrieve
 * This is largely inspired by other tool available from other toolkit, namely:
 * echoscu (DCMTK)
 * findscu (DCMTK)
 * movescu (DCMTK)
 * storescu (DCMTK)
 */
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
#include "gdcmDataSet.h"
#include "gdcmVersion.h"

#include <fstream>
#include <socket++/echo.h>
#include <stdlib.h>
#include <getopt.h>

// Execute like this:
// ./bin/gdcmscu www.dicomserver.co.uk 11112 echo
void CEcho( const char *remote, int portno, std::string const &aetitle,
std::string const &call )
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
  gdcm::DataSet blank;
  theManager.EstablishConnection(aetitle, call, remote, 0, portno, 1000, gdcm::network::eEcho, blank);
  std::vector<gdcm::network::PresentationDataValue> theValues1 = theManager.SendEcho();
  std::vector<gdcm::network::PresentationDataValue>::iterator itor;
  for (itor = theValues1.begin(); itor < theValues1.end(); itor++){
    itor->Print(std::cout);
  }
  std::vector<gdcm::network::PresentationDataValue> theValues2 = theManager.SendEcho();
  for (itor = theValues2.begin(); itor < theValues2.end(); itor++){
    itor->Print(std::cout);
  }
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite

}

void CMove( const char *remote, int portno )
{
/*
(0008,0052) CS [PATIENT]                                #   8, 1 QueryRetrieveLevel
(0010,0010) PN (no value available)                     #   0, 0 PatientsName
(0010,0020) LO (no value available)                     #   0, 0 PatientID

*/
  gdcm::DataSet ds;
  gdcm::Attribute<0x8,0x52> at1 = { "PATIENT" };
  ds.Insert( at1.GetAsDataElement() );
  gdcm::Attribute<0x10,0x10> at2 = { "FROG^KERMIT TCH " };
  ds.Insert( at2.GetAsDataElement() );
  gdcm::Attribute<0x10,0x20> at3 = { "" };
  //ds.Insert( at3.GetAsDataElement() );

  // $ findscu -v  -d --aetitle ACME1 --call ACME_STORE  -P -k 0010,0010="X*" dhcp-67-183 5678  patqry.dcm      
  // Add a query:

  gdcm::network::ULConnectionManager theManager;
  //theManager.EstablishConnection("ACME1", "ACME_STORE", remote, 0, portno, 1000, gdcm::network::eMove, ds);
  theManager.EstablishConnection("ACME1", "MI2B2", remote, 0, portno, 1000, gdcm::network::eMove, ds);
  theManager.SendMove( (gdcm::DataSet*)&ds );
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
}

void CFind( const char *remote, int portno )
{
/*
(0008,0052) CS [PATIENT]                                #   8, 1 QueryRetrieveLevel
(0010,0010) PN (no value available)                     #   0, 0 PatientsName
(0010,0020) LO (no value available)                     #   0, 0 PatientID

*/
  gdcm::DataSet ds;
  gdcm::Attribute<0x8,0x52> at1 = { "PATIENT" };
  ds.Insert( at1.GetAsDataElement() );
  gdcm::Attribute<0x10,0x10> at2 = { "F*" };
  //Attribute<0x10,0x10> at2 = { "X*" };
  ds.Insert( at2.GetAsDataElement() );
  gdcm::Attribute<0x10,0x20> at3 = { "" };
  ds.Insert( at3.GetAsDataElement() );

  // $ findscu -v  -d --aetitle ACME1 --call ACME_STORE  -P -k 0010,0010="X*" dhcp-67-183 5678  patqry.dcm      
  // Add a query:
  gdcm::network::ULConnectionManager theManager;
  //theManager.EstablishConnection("ACME1", "ACME_STORE", remote, 0, portno, 1000, gdcm::network::eFind, ds);
  theManager.EstablishConnection("ACME1", "MI2B2", remote, 0, portno, 1, gdcm::network::eFind, ds);
  std::vector<gdcm::DataSet> theDataSets  = theManager.SendFind( (gdcm::DataSet*)&ds );
  std::vector<gdcm::DataSet>::iterator itor;
  int c = 0;
  for (itor = theDataSets.begin(); itor < theDataSets.end(); itor++){
    std::cout << "Message " << c++ << std::endl;
    itor->Print(std::cout);
  }
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
}

void CStore( const char *remote, int portno, std::string const & filename )
{
  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  reader.Read();
  const gdcm::DataSet &ds = reader.GetFile().GetDataSet();

  gdcm::network::ULConnectionManager theManager;
  theManager.EstablishConnection("UNITED1", "COMMON", remote, 0, portno, 1000, gdcm::network::eStore, ds);
  theManager.SendStore( (gdcm::DataSet*)&ds );
  theManager.BreakConnection(-1);//wait for a while for the connection to break, ie, infinite
  
/*
  echo e(protocol::tcp);

  if (portno == 0)
    e->connect ( remote );
  else
    e->connect ( remote, portno);
*/
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
  /*
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
*/
}

static void process_input(iosockinet& sio)
{
  /*
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
  */
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

void PrintVersion()
{
  std::cout << "gdcmscu: gdcm " << gdcm::Version::GetVersion() << " ";
  const char date[] = "$Date$";
  std::cout << date << std::endl;
}

void PrintHelp()
{
  PrintVersion();
  std::cout << "Usage: gdcmscu [OPTION]...[OPERATION]...HOSTNAME...[PORT]..." << std::endl;
  std::cout << "Execute a DICOM Q/R operation to HOSTNAME, using port PORT (104 when not specified)\n";
  std::cout << "Parameter (required):" << std::endl;
  std::cout << "  -i --input          DICOM filename" << std::endl;
  std::cout << "Options:" << std::endl;
  std::cout << "  -H --hostname       Hostname." << std::endl;
  std::cout << "  -p --port           Port number." << std::endl;
  std::cout << "     --aetitle        Set Calling AE Title." << std::endl;
  std::cout << "     --call           Set Called AE Title." << std::endl;
  std::cout << "Mode Options:" << std::endl;
  std::cout << "     --echo           C-ECHO (default when none)." << std::endl;
  std::cout << "     --store          C-STORE." << std::endl;
  std::cout << "     --find           C-FIND." << std::endl;
  std::cout << "     --move           C-MOVE." << std::endl;
  std::cout << "General Options:" << std::endl;
  std::cout << "  -V --verbose   more verbose (warning+error)." << std::endl;
  std::cout << "  -W --warning   print warning info." << std::endl;
  std::cout << "  -D --debug     print debug info." << std::endl;
  std::cout << "  -E --error     print error info." << std::endl;
  std::cout << "  -h --help      print help." << std::endl;
  std::cout << "  -v --version   print version." << std::endl;
}

int main(int argc, char *argv[])
{
  int c;
  //int digit_optind = 0;

  std::string shostname;
  std::string callingaetitle = "GDCMSCU";
  std::string callaetitle = "ANY-SCP";
  int port = 104; // default
  std::string filename;
  int verbose = 0;
  int warning = 0;
  int debug = 0;
  int error = 0;
  int help = 0;
  int version = 0;
  int echomode = 0;
  int storemode = 0;
  int findmode = 0;
  int movemode = 0;
  while (1) {
    //int this_option_optind = optind ? optind : 1;
    int option_index = 0;
/*
   struct option {
              const char *name;
              int has_arg;
              int *flag;
              int val;
          };
*/
    static struct option long_options[] = {
        {"verbose", 0, &verbose, 1},
        {"warning", 0, &warning, 1},
        {"debug", 0, &debug, 1},
        {"error", 0, &error, 1},
        {"help", 0, &help, 1},
        {"version", 0, &version, 1},
        {"hostname", 1, 0, 0},     // -h
        {"aetitle", 1, 0, 0},     // 
        {"call", 1, 0, 0},     // 
        {"port", 0, &port, 1}, // -p
        {"input", 1, 0, 0}, // dcmfile-in
        {"echo", 1, &echomode, 1}, // --echo
        {"store", 1, &storemode, 1}, // --store
        {"find", 1, &findmode, 1}, // --find
        {"move", 1, &movemode, 1}, // --move
        {0, 0, 0, 0} // required
    };
    static const char short_options[] = "i:H:p:VWDEhv";
    c = getopt_long (argc, argv, short_options,
      long_options, &option_index);
    if (c == -1)
      {
      break;
      }

    switch (c)
      {
    case 0:
    case '-':
        {
        const char *s = long_options[option_index].name;
        //printf ("option %s", s);
        if (optarg)
          {
          if( option_index == 0 ) /* input */
            {
            assert( strcmp(s, "input") == 0 );
            assert( filename.empty() );
            filename = optarg;
            }
          else if( option_index == 7 ) /* calling aetitle */
            {
            assert( strcmp(s, "aetitle") == 0 );
            //assert( callingaetitle.empty() );
            callingaetitle = optarg;
            }
          else if( option_index == 8 ) /* called aetitle */
            {
            assert( strcmp(s, "call") == 0 );
            //assert( callaetitle.empty() );
            callaetitle = optarg;
            }
          //printf (" with arg %s", optarg);
          }
        //printf ("\n");
        }
      break;

    case 'i':
      //printf ("option i with value '%s'\n", optarg);
      assert( filename.empty() );
      filename = optarg;
      break;

    case 'H':
      shostname = optarg;
      break;

    case 'p':
      port = atoi( optarg );
      break;

    case 'V':
      verbose = 1;
      break;

    case 'W':
      warning = 1;
      break;

    case 'D':
      debug = 1;
      break;

    case 'E':
      error = 1;
      break;

    case 'h':
      help = 1;
      break;

    case 'v':
      version = 1;
      break;

    case '?':
      break;

    default:
      printf ("?? getopt returned character code 0%o ??\n", c);
      }
  }

  if (optind < argc)
    {
    int v = argc - optind;
    // hostname port filename
    if( v == 1 )
      {
      shostname = argv[optind++];
      }
    else if( v == 2 )
      {
      shostname = argv[optind++];
      port = atoi( argv[optind++] );
      }
    else if( v == 3 )
      {
      shostname = argv[optind++];
      port = atoi( argv[optind++] );
      filename = argv[optind++];
      }
    else
      {
      return 1;
      }
    assert( optind == argc );
    }

  if( version )
    {
    PrintVersion();
    return 0;
    }

  if( help )
    {
    PrintHelp();
    return 0;
    }

  if( shostname.empty() )
    {
    std::cerr << "Hostname missing" << std::endl;
    return 1;
    }
  if( port == 0 )
    {
    std::cerr << "Problem with port number" << std::endl;
    return 1;
    }

  const char *hostname = shostname.c_str();
  std::string mode = "echo";
  if ( echomode )
    {
    mode = "echo";
    }
  else if ( storemode )
    {
    mode = "store";
    }
  else if ( findmode )
    {
    mode = "find";
    }
  else if ( movemode )
    {
    mode = "move";
    }

  if ( mode == "server" ) // C-STORE SCP
    {
    // MM: Do not expose that to user for now (2010/10/11).
    CStoreServer( port );
    }
  else if ( mode == "echo" ) // C-ECHO SCU
    {
    CEcho( hostname, port, callingaetitle, callaetitle );
    }
  else if ( mode == "move" ) // C-FIND SCU
    {
    // ./bin/gdcmscu dhcp-67-183 5678 move
    // ./bin/gdcmscu mi2b2.slicer.org 11112 move
    CMove( hostname, port );
    }
  else if ( mode == "find" ) // C-FIND SCU
    {
    // ./bin/gdcmscu dhcp-67-183 5678 find
    // ./bin/gdcmscu mi2b2.slicer.org 11112  find
    // findscu -aec MI2B2 -P -k 0010,0010=F* mi2b2.slicer.org 11112 patqry.dcm
    CFind( hostname, port );
    }
  else // C-STORE SCU
    {
    // mode == filename
    CStore( hostname, port, filename );
    }
  return 0;
}
