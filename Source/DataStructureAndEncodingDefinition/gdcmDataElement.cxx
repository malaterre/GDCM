/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDataElement.h"

#include "gdcmByteValue.h"
#include "gdcmAttribute.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSequenceOfItems.h"

namespace gdcm
{
  void DataElement::SetVLToUndefined() { 
    Value &v = GetValue();
    SequenceOfItems *sq = dynamic_cast<SequenceOfItems*>(&v);
    if( sq )
      {
      sq->SetLengthToUndefined();
      ValueLengthField.SetToUndefined();
      }
  }

  const SequenceOfItems* DataElement::GetSequenceOfItems() const {
    const Value &v = GetValue();
    const SequenceOfItems *sqi = dynamic_cast<const SequenceOfItems*>(&v);
    return sqi;
  }
  const SequenceOfFragments* DataElement::GetSequenceOfFragments() const {
    const Value &v = GetValue();
    const SequenceOfFragments *sqf = dynamic_cast<const SequenceOfFragments*>(&v);
    return sqf; // Will return NULL if not ByteValue
  }

} // end namespace gdcm

