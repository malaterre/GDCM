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
#include "gdcmSequenceOfItems.h"

namespace gdcm
{
  void DataElement::SetVLToUndefined() { 
    gdcm::Value &v = GetValue();
    gdcm::SequenceOfItems *sq = dynamic_cast<gdcm::SequenceOfItems*>(&v);
    if( sq )
      {
      sq->SetLengthToUndefined();
      ValueLengthField.SetToUndefined();
      }
  }


} // end namespace gdcm

