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
#include "gdcmDataTransfer.h"
#include "gdcmPDataTFPDU.h"

namespace gdcm
{
namespace network
{

/*
Table 9-3
DATA TRANSFER
State Definition
Sta 6 Association established and ready for data transfer
*/

DataTransfer::DataTransfer()
{
}

std::iostream &DataTransfer::Run(std::iostream &ios)
{
  gdcm::network::PDataTFPDU pdata;
  gdcm::network::PresentationDataValue pdv;
  pdata.AddPresentationDataValue( pdv );
  pdata.Write( ios );
  ios.flush();

  return ios;
}

} // end namespace network
} // end namespace gdcm
