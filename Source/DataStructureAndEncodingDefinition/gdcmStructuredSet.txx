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

//#include "gdcmStructuredSet.h"
#include "gdcmByteValue.h"

namespace gdcm
{
  template <typename DEType>
  template <typename TSwap>
  IStream &StructuredSet<DEType>::ReadNested(IStream &is) {
    DEType de;
    const Tag itemDelItem(0xfffe,0xe00d);
    assert( de.GetTag() != itemDelItem ); // precondition before while loop
    while( de.Read<TSwap>(is) && de.GetTag() != itemDelItem  ) // Keep that order please !
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

  template <typename DEType>
  template <typename TSwap>
  OStream const &StructuredSet<DEType>::Write(OStream &os) const {
    //DEType de;
    typename StructuredSet<DEType>::ConstIterator it = DES.begin();
    for( ; it != DES.end(); ++it)
      {
      std::cerr << "DEBUG:" << *it << std::endl;
      const DEType & de = *it;
      // If this is a group length make sure this is consistant
      if( de.GetTag().GetGroup() == 0x0001
       || de.GetTag().GetGroup() == 0x0003
       || de.GetTag().GetGroup() == 0x0005
       || de.GetTag().GetGroup() == 0x0007 )
        {
        gdcmWarningMacro( "DataSet contains illegal Tags. "
          "Those elements will be discarded:" << de.GetTag() );
        }
      // After that we are sure the elements are valid
      else if( de.GetTag().GetElement() == 0x0 )
        {
        Element<VR::UL, VM::VM1> el;
        StringStream sst;
        //sst.SetSwapCode( os.GetSwapCode() );
        const Value &v = de.GetValue();
        const Value *pv = &v;
        const ByteValue *bv = dynamic_cast<const ByteValue*>(pv);
	      bv->Write<TSwap>(sst);
        el.Read( sst );
        //std::cerr << "GL=";
        //el.Print( std::cerr );
        //std::cerr << std::endl;
        unsigned int len = ComputeGroupLength( de.GetTag() );
        //std::cerr << len << std::endl;
        if( len != el.GetValue() )
          {
          gdcmWarningMacro( "Wrong group length for " << de.GetTag() << ":"
            << el.GetValue() << " should be " << len << ". Corrected." );
          DEType correct(de);
          // Set correct value:
          el.SetValue( len );
          el.Write( sst );
          // Pass it to the ByteValue
          ByteValue *bv2 = new ByteValue;
          bv2->SetLength(4);
          bv2->Read<TSwap>(sst);
          correct.SetValue( *bv2 );
          correct.Write<TSwap>(os);
          }
        else
          {
          // okay good value
          de.Write<TSwap>(os);
          }
        }
      else // well simply writes it
        {
        de.Write<TSwap>(os);
        }
      }
    return os;
  }
} // end namespace gdcm

#endif // __gdcmStructuredSet_txx

