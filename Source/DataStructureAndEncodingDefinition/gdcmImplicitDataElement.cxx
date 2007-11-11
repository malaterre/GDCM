/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
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

	/*
ImplicitDataElement::~ImplicitDataElement()
{
}

ImplicitDataElement::ImplicitDataElement(ExplicitDataElement const &val)
{
  TagField = val.GetTag();
  ValueLengthField = val.GetVL();
  ValueField = val.ValueField;
}
*/

  VL ImplicitDataElement::GetLength() const
    {
    if( ValueLengthField.IsUndefined() )
      {
      assert( ValueField->GetLength().IsUndefined() );
      Value *p = ValueField;
      SequenceOfItems<ImplicitDataElement> *sq = dynamic_cast<SequenceOfItems<ImplicitDataElement>*>(p);
      if( sq )
        {
        return TagField.GetLength() + ValueLengthField.GetLength() 
          + sq->ComputeLength();
        }
      return ValueLengthField;
      }
    else // BUG !!! When a sequence is explicit length...
      {
      assert( !ValueField || ValueField->GetLength() == ValueLengthField );
      return TagField.GetLength() + ValueLengthField.GetLength() 
        + ValueLengthField;
      }
    }

} // end namespace gdcm

