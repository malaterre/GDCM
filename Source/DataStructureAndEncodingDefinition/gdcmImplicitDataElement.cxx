/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImplicitDataElement.h"

#include "gdcmByteValue.h"
#include "gdcmSequenceOfItems.h"

namespace gdcm
{

VL ImplicitDataElement::GetLength() const
{
  const Value &v = GetValue();
  if( ValueLengthField.IsUndefined() )
    {
    assert( ValueField->GetLength().IsUndefined() );
    Value *p = ValueField;
    SequenceOfItems *sq = dynamic_cast<SequenceOfItems*>(p);
    if( sq )
      {
      return TagField.GetLength() + ValueLengthField.GetLength() 
        + sq->ComputeLength<ImplicitDataElement>();
      }
    assert( !ValueLengthField.IsUndefined() );
    return ValueLengthField;
    }
  //else if( const SequenceOfItems *sqi = GetSequenceOfItems() )
  else if( const SequenceOfItems *sqi = dynamic_cast<const SequenceOfItems*>(&v) )
    {
    // TestWrite2
    return TagField.GetLength() + ValueLengthField.GetLength() 
      + sqi->ComputeLength<ImplicitDataElement>();
    }
  else
    {
    assert( !ValueField || ValueField->GetLength() == ValueLengthField );
    return TagField.GetLength() + ValueLengthField.GetLength() 
      + ValueLengthField;
    }
}

} // end namespace gdcm

