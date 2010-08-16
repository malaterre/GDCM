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

  gdcm::network::AAssociateRQPDU cecho;
  cecho.Write(e);
  e.flush();

  gdcm::network::AAssociateACPDU acpdu;
  acpdu.Read( e );

  gdcm::network::PDataTPPDU pdata;
  pdata.Write( e );
  e.flush();

  // listen back
  gdcm::network::PDataTPPDU pdata2;
  pdata2.Read( e );

  // send release:
  gdcm::network::AReleaseRQPDU rel;
  rel.Write( e );

  return 0;
}
