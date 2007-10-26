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
#ifndef __gdcmStructuredSet_txx
#define __gdcmStructuredSet_txx

#include "gdcmStructuredSet.h"

namespace gdcm
{
  template <typename DEType>
  template <typename TSwap>
  IStream &StructuredSet<DEType>::ReadNested(IStream &is) {
    DEType de;
    const Tag itemDelItem(0xfffe,0xe00d);
    while( de.Read<TSwap>(is) && de.GetTag() != itemDelItem )
      {
      //std::cout << "DEBUG Nested: " << de << std::endl;
      DES.insert( de );
      }
    assert( de.GetTag() == itemDelItem );
    //std::cerr << "Finish nested" << std::endl;
    return is;
}

  template <typename DEType>
  template <typename TSwap>
  IStream &StructuredSet<DEType>::Read(IStream &is) {
    DEType de;
    while( !is.eof() && de.Read<TSwap>(is) )
      {
      std::cerr << "DEBUG:" << de << std::endl;
      assert( de.GetTag() != Tag(0,0) );
      DES.insert( de );
      }
      //std::cerr << "finsih"  << std::endl;
    return is;
  }

  template <typename DEType>
  template <typename TSwap>
  IStream &StructuredSet<DEType>::ReadWithLength(IStream &is, VL &length) {
    DEType de;
    VL l = 0;
    //std::cout << "ReadWithLength Length: " << length << std::endl;
    VL locallength = length;
    while( l != locallength && de.Read<TSwap>(is))
      {
      //std::cout << "Nested: " << de << std::endl;
      DES.insert( de );
      l += de.GetLength();
      assert( !de.GetVL().IsUndefined() );
      //std::cerr << "DEBUG: " << de.GetTag() << " "<< de.GetLength() << 
      //  "," << de.GetVL() << "," << l << std::endl;
      // Bug_Philips_ItemTag_3F3F
      //  (0x2005, 0x1080): for some reason computation of length fails...
      if( l == 70 && locallength == 63 )
        {
        gdcmWarningMacro( "PMS: Super bad hack. Changing length" );
        length = locallength = 140;
        }
      assert( l <= locallength );
      }
    assert( l == locallength );
    return is;
  }

} // end namespace gdcm

#endif // __gdcmStructuredSet_txx

