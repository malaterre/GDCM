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
#include "gdcmSequenceOfItems.h"

namespace gdcm
{

void SequenceOfItems::AddItem(Item const &item)
{
  Items.push_back( item );
  if( !SequenceLengthField.IsUndefined() )
    {
    abort(); // TODO
    }
}

const Item &SequenceOfItems::GetItem(unsigned int position) const
{
  if( position < 1 || position > Items.size() )
    {
    throw Exception( "Out of Range" );
    }
  return Items[position-1];
}


} // end namespace gdcm

