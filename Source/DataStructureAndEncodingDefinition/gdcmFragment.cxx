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
#include "gdcmFragment.h"

namespace gdcm
{
  IStream &Fragment::Read(IStream &is)
    {
    // Superclass
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !TagField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    if( TagField != itemStart && TagField != seqDelItem )
      {
      // gdcm-JPEG-LossLess3a.dcm
      std::streampos pos = is.Tellg();
      is.Seekg( 0, std::ios::end );
      std::streampos end = is.Tellg();
      assert( (long)(end-pos) == 4 );
      gdcmWarningMacro( "Broken file: " << (long)(end-pos)
        << " bytes were skipped at the end of file. Use at own risk." );
      // Pretend to end properly...
      TagField = Tag(0xfffe,0xe0dd);
      ValueLengthField = 0;
      // Make sure to clear the FragmentValue
      FragmentValue = new ByteValue;
      FragmentValue->SetLength( ValueLengthField );
      return is;
      }
#endif
    if( !ValueLengthField.Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    // Self
    FragmentValue = new ByteValue;
    FragmentValue->SetLength(ValueLengthField);
    if( !FragmentValue->Read(is) )
      {
      assert(0 && "Should not happen");
      return is;
      }
    return is;
    }


  OStream &Fragment::Write(OStream &os) const {
    const Tag itemStart(0xfffe, 0xe000);
    const Tag seqDelItem(0xfffe,0xe0dd);
    if( !TagField.Write(os) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    assert( TagField == itemStart
         || TagField == seqDelItem );
    if( !ValueLengthField.Write(os) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    // Self
    if( !FragmentValue->Write(os) )
      {
      assert(0 && "Should not happen");
      return os;
      }
    return os;
    }

} // end namespace gdcm

