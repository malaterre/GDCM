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

  // listen back
  gdcm::network::PDataTFPDU pdata2;
  pdata2.Read( ios );
  pdata2.Print( std::cout );

  return ios;
}

} // end namespace network
} // end namespace gdcm
