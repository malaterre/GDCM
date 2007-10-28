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
#ifndef __gdcmSequenceOfItems_txx
#define __gdcmSequenceOfItems_txx

#include "gdcmSequenceOfItems.h"

namespace gdcm
{

template <typename DEType>
VL SequenceOfItems<DEType>::ComputeLength() const
{
  typename ItemVector::const_iterator it = Items.begin();
  VL length = 0;
  for(;it != Items.end(); ++it)
    {
    length += it->GetLength();
    }
  // For defined length SQ, make sure computation is correct (compare
  // to original length)
  assert( SequenceLengthField.IsUndefined()
    || length == SequenceLengthField );
  return length;
}

} // end namespace gdcm

#endif // __gdcmSequenceOfItems_txx
