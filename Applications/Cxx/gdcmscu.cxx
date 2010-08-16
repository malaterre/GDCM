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
int main(int argc, char *argv[])
{
 if (argc < 3)
   {
   std::cerr << "Usage: " << argv [0] << " remote-host portno" << std::endl;
   return 1;
   }

  int portno = atoi (argv [2]);

  echo e(protocol::tcp);

  if (portno == 0)
    e->connect (argv [1]);
  else
    e->connect (argv [1], portno);

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

  // Print output DataSet:
  pdata2.GetPresentationDataValue(0).GetDataSet().Print( std::cout );

  // send release:
  gdcm::network::AReleaseRQPDU rel;
  rel.Write( e );

  return 0;
}
