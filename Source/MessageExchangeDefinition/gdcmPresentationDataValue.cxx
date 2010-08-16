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
#include "gdcmPresentationDataValue.h"
#include "gdcmSwapper.h"
#include "gdcmDataSet.h"
#include "gdcmImplicitDataElement.h"

namespace gdcm
{
namespace network
{

PresentationDataValue::PresentationDataValue()
{
  ItemLength = 0;
  PresentationContextID = 1;
  ItemLength = 70;
}

std::istream &PresentationDataValue::Read(std::istream &is)
{
  uint32_t itemlength = ItemLength;
  is.read( (char*)&itemlength, sizeof(ItemLength) );
  SwapperDoOp::SwapArray(&itemlength,1);
  ItemLength = itemlength;
  is.read( (char*)&PresentationContextID, sizeof(PresentationContextID) );
  
  uint8_t mh;
  is.read( (char*)&mh, 1 );

#if 0
  char buf[256];
  is.read( buf, ItemLength - 2 );
#else
  DataSet ds;
  VL vl = ItemLength - 2;
  ds.ReadWithLength<ImplicitDataElement,SwapperNoOp>( is, vl );

  std::cout << "DEBUG" << std::endl;
  std::cout << ds << std::endl;
#endif

  return is;
}

const std::ostream &PresentationDataValue::Write(std::ostream &os) const
{
  uint32_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );
  os.write( (char*)&PresentationContextID, sizeof(PresentationContextID) );

  return os;
}

} // end namespace network
} // end namespace gdcm
