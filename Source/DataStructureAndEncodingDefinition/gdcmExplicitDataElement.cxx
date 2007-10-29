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
#include "gdcmExplicitDataElement.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"

// FIXME
#include "gdcmImplicitDataElement.h"

namespace gdcm
{

ExplicitDataElement::~ExplicitDataElement()
{
}

//-----------------------------------------------------------------------------
ExplicitDataElement::ExplicitDataElement(ImplicitDataElement const &val)
{
  TagField = val.GetTag();
  ValueLengthField = val.GetVL();
  VRField = VR::UN;
  ValueField = val.ValueField;
}

  VL ExplicitDataElement::GetLength() const {
    if( ValueLengthField.IsUndefined() )
      {
      assert( ValueField->GetLength().IsUndefined() );
      Value *p = ValueField;
      // If this is a SQ we need to compute it's proper length
      SequenceOfItems<ExplicitDataElement> *sq = dynamic_cast<SequenceOfItems<ExplicitDataElement>*>(p);
      if( sq )
        {
        return TagField.GetLength() + VRField.GetLength() + 
          ValueLengthField.GetLength() + sq->ComputeLength();
        }
      SequenceOfFragments *sf = dynamic_cast<SequenceOfFragments*>(p);
      if( sf )
        {
        assert( VRField & (VR::OB | VR::OW) );
        return TagField.GetLength() + VRField.GetLength() 
          + ValueLengthField.GetLength() + sf->ComputeLength();
        }
      abort();
      }
    else
      {
      // Each time VR::GetLength() is 2 then Value Length is coded in 2
      //                              4 then Value Length is coded in 4
      assert( !ValueField || ValueField->GetLength() == ValueLengthField );
      return TagField.GetLength() + 2*VRField.GetLength() + ValueLengthField;
      }
  }


} // end namespace gdcm
