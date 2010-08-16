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
#include <fstream>
#include <socket++/echo.h>
#include <stdlib.h>
#include <stdint.h>
#include "gdcmAAssociateRQPDU.h"
#include "gdcmAttribute.h"
#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmUIDs.h"
#include "gdcmAAssociateACPDU.h"
#include "gdcmPDataTFPDU.h"
#include "gdcmAReleaseRQPDU.h"

// Execute like this:
// ./bin/gdcmscu www.dicomserver.co.uk 11112 toto 
int main(int ac, char *av[])
{
 using namespace std;
 using namespace gdcm;

  if (ac < 3) {
    cerr << "USAGE: " << av [0] << " remote-host portno string...\n";
    return 1;
  }

  int portno = atoi (av [2]);

  echo e(protocol::tcp);

  if (portno == 0)
    e->connect (av [1]);
  else
    e->connect (av [1], portno);

  const char s = '1';
  std::cout << "val:" << (int)s << std::endl;

  //cout << e->rfc_name () << ' ' << e->rfc_doc () << endl;
  const char echoscu[] = {
   0x01,0x00,0x00,0x00,0x00,0xcd,0x00,0x01,0x00,0x00,0x41,0x4e,0x59,0x2d,0x53,0x43,
   0x50,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x45,0x43,0x48,0x4f,0x53,0x43,
   0x55,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x15,0x31,0x2e,
   0x32,0x2e,0x38,0x34,0x30,0x2e,0x31,0x30,0x30,0x30,0x38,0x2e,0x33,0x2e,0x31,0x2e,
   0x31,0x2e,0x31,0x20,0x00,0x00,0x2e,0x01,0x00,0xff,0x00,0x30,0x00,0x00,0x11,0x31,
   0x2e,0x32,0x2e,0x38,0x34,0x30,0x2e,0x31,0x30,0x30,0x30,0x38,0x2e,0x31,0x2e,0x31,
   0x40,0x00,0x00,0x11,0x31,0x2e,0x32,0x2e,0x38,0x34,0x30,0x2e,0x31,0x30,0x30,0x30,
   0x38,0x2e,0x31,0x2e,0x32,0x50,0x00,0x00,0x3a,0x51,0x00,0x00,0x04,0x00,0x00,0x40,
   0x00,0x52,0x00,0x00,0x1b,0x31,0x2e,0x32,0x2e,0x32,0x37,0x36,0x2e,0x30,0x2e,0x37,
   0x32,0x33,0x30,0x30,0x31,0x30,0x2e,0x33,0x2e,0x30,0x2e,0x33,0x2e,0x35,0x2e,0x35,
   0x55,0x00,0x00,0x0f,0x4f,0x46,0x46,0x49,0x53,0x5f,0x44,0x43,0x4d,0x54,0x4b,0x5f,
   0x33,0x35,0x35};
   /*
  ..........ANY-SCP         ECHOSCU         ..................
  ..................1.2.840.10008.3.1.1.1 .......0...1.2.840.1
  0008.1.1@...1.2.840.10008.1.2P..:Q.....@.R...1.2.276.0.72300
  10.3.0.3.5.5U...OFFIS_DCMTK_355
   */

   gdcm::network::AAssociateRQPDU cecho;

      DataSet ds;
/*
D: # Dicom-Data-Set
D: # Used TransferSyntax: Unknown Transfer Syntax
D: (0000,0000) UL 0                                        #   4, 1 CommandGroupLength
D: (0000,0002) UI =VerificationSOPClass                    #  18, 1 AffectedSOPClassUID
D: (0000,0100) US 48                                       #   2, 1 CommandField
D: (0000,0110) US 1                                        #   2, 1 MessageID
D: (0000,0800) US 257                                      #   2, 1 DataSetType
*/

    DataElement de( Tag(0x0,0x2) );
    de.SetVR( VR::UI );
    const char *uid = gdcm::UIDs::GetUIDString( gdcm::UIDs::VerificationSOPClass );
    std::string suid = uid;
    suid.push_back( ' ' );
    //de.SetByteValue(  uid, strlen(uid)  );
    de.SetByteValue(  suid.c_str(), suid.size()  );
    ds.Insert( de );
{
    gdcm::Attribute<0x0,0x100> at = { 48 };
    ds.Insert( at.GetAsDataElement() );
}
{
    gdcm::Attribute<0x0,0x110> at = { 1 };
    ds.Insert( at.GetAsDataElement() );
}
{
    gdcm::Attribute<0x0,0x800> at = { 257 };
    ds.Insert( at.GetAsDataElement() );
}
{
    gdcm::Attribute<0x0,0x0> at = { 0 };
    unsigned int glen = ds.GetLength<ImplicitDataElement>();
    assert( (glen % 2) == 0 );
    at.SetValue( glen );
    ds.Insert( at.GetAsDataElement() );
}


/*
D: (0000,0002) UI =VerificationSOPClass                    #  18, 1 AffectedSOPClassUID
D: (0000,0100) US 48                                       #   2, 1 CommandField
D: (0000,0110) US 1                                        #   2, 1 MessageID
D: (0000,0800) US 257                                      #   2, 1 DataSetType
*/


   std::ofstream b( "/tmp/out");
   //b.write( echoscu, sizeof(echoscu) );
   cecho.Write( b );

  const char msg[] = { 0x01  , 0x00  , 0x00  ,0x00  ,0x00  ,0x1  ,0x00  ,0x01  ,0x00  ,0x00  ,0x41  ,0x4e  ,0x59  ,0x2d  ,0x53  ,0x43 };
//  for (int i = 3; i < ac; i++) {
    char buf [256];

    //cout << "sending: " << av [i] << endl;

    //e << av [i] << endl;
    //e << msg << endl;
   // for(int j = 0; j < 255; ++j )
   // {
   //   e << (j+10); // << endl;
   // }
      uint8_t t;
      cecho.Write(e);
      //e << endl;
      e.flush();
      e >> t;
      std::cout << "response: " << (int)t << std::endl;
    //e.getline (buf, 255);
gdcm::network::AAssociateACPDU acpdu;
acpdu.Read( e );
    //  e >> t;
    //cout << "left over: " << t << endl;
    //e.getline (buf, 255);
gdcm::network::PDataTPPDU pdata;
//  const char msg2[] = { 0x00, 0x00, 0x00, 0x00 };

//e.write( msg2, sizeof(msg2) );
pdata.Write( e );

//    buf [255] = 0;

    //cout << "left over: " << buf << endl;

   t = 3; // E.2 MESSAGE CONTROL HEADER ENCODING
   e.write( (char*)&t, 1 );
   ds.Write<ImplicitDataElement,SwapperNoOp>( e );
   e.flush();

   // listen back
gdcm::network::PDataTPPDU pdata2;
pdata2.Read( e );
//e.getline( buf , 1);
//cout << "left over: " << buf << endl;


// send release:
gdcm::network::AReleaseRQPDU rel;
rel.Write( e );

pdata.Write( b );
   ds.Write<ImplicitDataElement,SwapperNoOp>( b );
   b.close();

      //std::vector<char> v = cecho.GetBytes();
      //e.write(msg, sizeof(msg) );
      //e.write(echoscu,sizeof(echoscu)/2  );
      //e.write(echoscu + sizeof(echoscu)/2 , sizeof(echoscu)/2 + 1 );
      //e.write( &v[0], v.size() );
      //t = 0x2;
      //e << t;
      //t = 0x1;
      //e << t;
      //e << t;
      //e << t;
      //e << 0;
      //e << 0;
      //e << 0;
      //e << 10;
      //e << 1;
      //e << 0;
      //e << "coucou";
//      e << endl;
//
//    e.getline (buf, 255);
//    buf [255] = 0;

//    cout << "got back: " << buf << endl;
//  }

  return 0;
}
