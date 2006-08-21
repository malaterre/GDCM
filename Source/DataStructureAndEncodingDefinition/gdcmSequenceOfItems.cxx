/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmSequenceOfItems.h"

namespace gdcm
{
IStream &SequenceOfItems::Read(IStream &is)
{
  if( SequenceLengthField.IsUndefined() )
    {
    Item item(NType);
    const Tag seqDelItem(0xfffe,0xe0dd);
    do
      {
      item.Read(is);
      //std::cout << "Item: " << item << std::endl;
      Items.push_back( item );
      }
    while( item.GetTag() != seqDelItem );
    }
  else
    {
    Item item(NType);
    VL l = 0;
    //std::cout << "Length: " << l << std::endl;
    while( l != SequenceLengthField )
      {
      item.Read(is);
      //std::cout << "Item: " << item << std::endl;
      Items.push_back( item );
      l += item.GetLength();
      //assert( !item.GetVL().IsUndefined() );
      assert( l <= SequenceLengthField );
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
      // MR_Philips_Intera_No_PrivateSequenceImplicitVR.dcm
      // (0x2005, 0x1080): for some reason computation of length fails...
      if( SequenceLengthField == 778 && l == 774 )
        {
        gdcmWarningMacro( "PMS: Super bad hack" );
        l = SequenceLengthField;
        }
      // Bug_Philips_ItemTag_3F3F
      // (0x2005, 0x1080): Because we do not handle fully the bug at the item
      // level we need to check here too
      else if ( SequenceLengthField == 444 && l == 3*71 )
        {
        // This one is a double bug. Item length is wrong and impact SQ length
        gdcmWarningMacro( "PMS: Super bad hack" );
        l = SequenceLengthField;
        }
#endif
      }
    assert( l == SequenceLengthField );
    }
  return is;
}

VL SequenceOfItems::ComputeLength() const
{
  ItemVector::const_iterator it = Items.begin();
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

OStream const &SequenceOfItems::Write(OStream &os) const
{
  ItemVector::const_iterator it = Items.begin();
  for(;it != Items.end(); ++it)
    {
    it->Write(os);
    }
  //if( SequenceLengthField.IsUndefined() )
  //  {
  //  const Tag seqDelItem(0xfffe,0xe0dd);
  //  const ImplicitDataElement ide(seqDelItem);
  //  assert( ide.GetVL() == 0 );
  //  ide.Write(os);
  //  }
  return os;
}

} // end namespace gdcm
