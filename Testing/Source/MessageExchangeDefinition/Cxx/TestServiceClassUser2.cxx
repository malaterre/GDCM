/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmServiceClassUser.h"
#include "gdcmDataEvent.h"
#include "gdcmSimpleSubjectWatcher.h"
#include "gdcmPresentationContextGenerator.h"
#include "gdcmAttribute.h"
#include "gdcmCompositeNetworkFunctions.h"
#include "gdcmTransferSyntax.h"
#include "gdcmWriter.h"
#include "gdcmReader.h"
#include "gdcmUIDGenerator.h"

#include "gdcmTesting.h"

/*
 * This test make sure we can send/receive as many dataset as we want
 */

int TestServiceClassUser2(int argc, char *argv[])
{
  if( argc < 5 )
    {
    std::cerr << argv[0] << " aetitle call portno moveReturnPort remote" << std::endl;
    return 1;
    }
  std::string aetitle = argv[1]; // the ae title of this computer
  std::string call = argv[2]; // the ae title of the server
  int portno = atoi(argv[3]); // the port of the server
  int moveReturnPort = atoi(argv[4]); // the port over which return cstore scps are done for cmove
  std::string remote = argv[5]; //the ip address of the remote server

  gdcm::SmartPointer<gdcm::ServiceClassUser> scup = new gdcm::ServiceClassUser;
  gdcm::ServiceClassUser &scu = *scup;
  gdcm::SimpleSubjectWatcher w( &scu, "TestServiceClassUser" );

  scu.SetHostname( remote.c_str() );
  scu.SetPort( portno );
  scu.SetTimeout( 1000 );
  scu.SetCalledAETitle( call.c_str() );
  scu.SetAETitle( aetitle.c_str() );

  if( !scu.InitializeConnection() )
    {
    return 1;
    }

  gdcm::PresentationContextGenerator generator;
  if( !generator.GenerateFromUID( gdcm::UIDs::VerificationSOPClass ) )
    {
    return 1;
    }

  // make sure to fail if no pres contexts:
  if( scu.StartAssociation() )
    {
    return 1;
    }

  scu.SetPresentationContexts( generator.GetPresentationContexts() );

  if( !scu.StartAssociation() )
    {
    return 1;
    }

  // C-ECHO
  if( !scu.SendEcho() )
    {
    return 1;
    }

  if( !scu.StopAssociation() )
    {
    return 1;
    }

  gdcm::Directory::FilenamesType filenames;
  const char *directory = gdcm::Testing::GetDataRoot();
  // DEBUG:
  // storescu -R -xs --call GDCM_STORE macminig4 11112 gdcmData/gdcm-MR-PHILIPS-16-NonSquarePixels.dcm
  std::string filename = std::string(directory) + "/gdcm-MR-PHILIPS-16-NonSquarePixels.dcm";
  filenames.push_back( filename );

  if( !generator.GenerateFromFilenames(filenames) )
    {
    return 1;
    }

  scu.SetPresentationContexts( generator.GetPresentationContexts() );

  if( !scu.StartAssociation() )
    {
    return 1;
    }

  gdcm::Reader reader;
  reader.SetFileName( filename.c_str() );
  if( !reader.Read() )
    {
    return 1;
    }

  gdcm::File & file = reader.GetFile();
  gdcm::UIDGenerator uid;
  const int nmax = 50;
  for( int i = 0; i < nmax; ++i )
    {
    gdcm::DataSet & ds = file.GetDataSet();
    std::string instance_uid = uid.Generate();
      {
      gdcm::Attribute<0x8,0x18> at;
      at.SetValue( instance_uid.c_str() );
      ds.Replace( at.GetAsDataElement() );
      }
      {
      gdcm::Attribute<0x10,0x20> at;
      at.SetValue( "TestServiceClassUser2" );
      ds.Replace( at.GetAsDataElement() );
      }
    if( !scu.SendStore( file ) )
      {
      return 1;
      }
    }

  if( !scu.StopAssociation() )
    {
    return 1;
    }

  // customize the find query
  gdcm::DataSet findds;
  gdcm::Attribute<0x10,0x20> pid ={"TestServiceClassUser2"};
  findds.Insert( pid.GetAsDataElement() );
  gdcm::Attribute<0x8,0x18> iuid;
  findds.Insert( iuid.GetAsDataElement() );

  gdcm::SmartPointer<gdcm::BaseRootQuery> findquery =
    gdcm::CompositeNetworkFunctions::ConstructQuery(
      gdcm::ePatientRootType, gdcm::eImageOrFrame, findds);

  // make sure the query is valid
  if (!findquery->ValidateQuery(false))
    {
    return 1;
    }

  // Generate the PresentationContext array from the query UID:
  if( !generator.GenerateFromUID( findquery->GetAbstractSyntaxUID() ) )
    {
    return 1;
    }

  scu.SetPresentationContexts( generator.GetPresentationContexts() );

  if( !scu.StartAssociation() )
    {
    return 1;
    }
  // $ findscu --call GDCM_STORE -P  macminig4 11112 -k 8,52=IMAGE -k
  //   10,20=TestServiceClassUser2  -k 20,d  -k 20,e -k 8,18
  // gdcmscu --find --call GDCM_STORE --image --patientroot  macminig4 11112
  //   -k 10,20=TestServiceClassUser2 -k 8,18

  // C-FIND
  std::vector<gdcm::DataSet> datasets;
  if( !scu.SendFind(findquery, datasets) )
    {
    return 1;
    }

  if( !scu.StopAssociation() )
    {
    return 1;
    }

  // C-MOVE
  // customize the move query
  gdcm::DataSet moveds;
  // use results from the c-find to construct the c-move query:
  moveds.Insert( datasets[0].GetDataElement( gdcm::Tag(0x10,0x20) ) );
  moveds.Insert( datasets[0].GetDataElement( gdcm::Tag(0x20,0xd) ) );
  moveds.Insert( datasets[0].GetDataElement( gdcm::Tag(0x20,0xe) ) );

  gdcm::SmartPointer<gdcm::BaseRootQuery> movequery =
    gdcm::CompositeNetworkFunctions::ConstructQuery(
      gdcm::ePatientRootType, gdcm::eImageOrFrame, moveds, true);

  // Generate the PresentationContext array from the query UID:
  if( !generator.GenerateFromUID( movequery->GetAbstractSyntaxUID() ) )
    {
    return 1;
    }

  scu.SetPresentationContexts( generator.GetPresentationContexts() );

  scu.SetPortSCP( moveReturnPort );

  if( !scu.StartAssociation() )
    {
    return 1;
    }

  //std::cerr << "size: " << datasets.size() << std::endl;

  for(
    std::vector<gdcm::DataSet>::const_iterator cfind_it = datasets.begin();
    cfind_it != datasets.end(); ++cfind_it )
    {
    gdcm::DataSet &queryds = movequery->GetQueryDataSet();
    const gdcm::DataElement &instanceuid = cfind_it->GetDataElement( gdcm::Tag(0x8,0x18) );
    //std::cout << "CMove-ing: " << instanceuid << std::endl;
    queryds.Replace( instanceuid );
    //std::cout << "ds: " << queryds << std::endl;

    // C-MOVE
    std::vector<gdcm::DataSet> data;
    if( !scu.SendMove(movequery, data) )
      {
      std::cerr << "CMove Failure for: " << instanceuid << std::endl;
      return 1;
      }
    if( data.size() != 1 )
      {
      std::cerr << "data size: " << data.size() << std::endl;
      return 1;
      }
    }

  if( !scu.StopAssociation() )
    {
    return 1;
    }
  // scu dstor will close the connection (!= association)

  return 0;
}
