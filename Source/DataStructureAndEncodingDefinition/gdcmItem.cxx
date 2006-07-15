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
#include "gdcmItem.h"

namespace gdcm
{

VL Item::GetLength() const
{
  if( ValueLengthField.IsUndefined() )
    {
    assert( !NestedDataSet->GetLength().IsUndefined() );
    // Item Start             4
    // Item Length            4
    // DataSet                ?
    // Item End Delimitation  4
    // Item End Length        4
    return TagField.GetLength() /* 4 */ + ValueLengthField.GetLength() /* 4 */
      + NestedDataSet->GetLength() + 4 + 4;
    }
  else
    {
    // Item Start             4
    // Item Length            4
    // DataSet                ?
    return TagField.GetLength() /* 4 */ + ValueLengthField.GetLength() /* 4 */
      + ValueLengthField;
    }
}

IStream &Item::Read(IStream &is)
{
  // Superclass
  if( !TagField.Read(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  assert ( TagField == Tag(0xfffe, 0xe000)
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    || TagField == Tag(0x3f3f, 0x3f00)
    //|| TagField == Tag(0xfeff, 0x00e0)
#endif
    || TagField == Tag(0xfffe, 0xe0dd) );
  if( !ValueLengthField.Read(is) )
    {
    assert(0 && "Should not happen");
    return is;
    }
  // Self
  NestedDataSet = new DataSet(NType);
  NestedDataSet->SetLength( ValueLengthField );
  // BUG: This test is required because DataSet::Read with a Length
  // of 0 is actually thinking it is reading a root DataSet
  // so we need to make sure not to call NestedDataSet.Read here
  if( ValueLengthField == 0 )
    {
    assert( TagField == Tag( 0xfffe, 0xe0dd)
         || TagField == Tag( 0xfffe, 0xe000) );
    if( TagField != Tag( 0xfffe, 0xe0dd) )
      {
      gdcmErrorMacro( "SQ: " << TagField << " has a length of 0" );
      }
    }
  else
    {
    NestedDataSet->Read(is);
    }
  return is;
}

OStream &Item::Write(OStream &os) const
{
  if( !TagField.Write(os) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  assert ( TagField == Tag(0xfffe, 0xe000)
        || TagField == Tag(0xfffe, 0xe0dd) );
  if( !ValueLengthField.Write(os) )
    {
    assert(0 && "Should not happen");
    return os;
    }
  // Self
  NestedDataSet->Write(os);
  //if( ValueLengthField.IsUndefined() )
  //  {
  //  const Tag itemDelItem(0xfffe,0xe00d);
  //  const ImplicitDataElement ide(itemDelItem);
  //  assert( ide.GetVL() == 0 );
  //  ide.Write(os);
  //  }

  return os;
}

} // end namespace gdcm

