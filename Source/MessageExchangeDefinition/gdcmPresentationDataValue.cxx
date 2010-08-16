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
#include "gdcmUIDs.h"
#include "gdcmAttribute.h"

namespace gdcm
{
namespace network
{

PresentationDataValue::PresentationDataValue()
{
  PresentationContextID = 1;

  DataSet &ds = DS;
  DataElement de( Tag(0x0,0x2) );
  de.SetVR( VR::UI );
  const char *uid = gdcm::UIDs::GetUIDString( gdcm::UIDs::VerificationSOPClass );
  std::string suid = uid;
  suid.push_back( ' ' ); // no \0 !
  de.SetByteValue( suid.c_str(), suid.size()  );
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

  ItemLength = Size() - 4;
  assert (ItemLength + 4 == Size() );
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
  //assert( mh == 0 ); // bitwise stuff...

  DataSet ds;
  VL vl = ItemLength - 2;
  ds.ReadWithLength<ImplicitDataElement,SwapperNoOp>( is, vl );

  return is;
}

const std::ostream &PresentationDataValue::Write(std::ostream &os) const
{
  uint32_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );
  os.write( (char*)&PresentationContextID, sizeof(PresentationContextID) );

   uint8_t t;
   t = 3; // E.2 MESSAGE CONTROL HEADER ENCODING
   os.write( (char*)&t, 1 );
   DS.Write<ImplicitDataElement,SwapperNoOp>( os );

  return os;
}

size_t PresentationDataValue::Size() const
{
  size_t ret = 0;
  ret += sizeof(ItemLength);
  ret += sizeof(PresentationContextID);
  ret += 1; // MESSAGE CONTROL HEADER ENCODING

  VL vl = DS.GetLength<ImplicitDataElement>();
  ret += vl;

  return ret;
}

} // end namespace network
} // end namespace gdcm
