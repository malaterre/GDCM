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
#ifndef __gdcmValueIO_txx
#define __gdcmValueIO_txx

#include "gdcmValueIO.h"

#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmByteValue.h"

namespace gdcm
{

  template <typename TDE, typename TSwap>
  std::istream &ValueIO<TDE,TSwap>::Read(std::istream &is, Value& _v) {
    Value* v = &_v;
    if( ByteValue *bv = dynamic_cast<ByteValue*>(v) )
    {
      bv->template Read<TSwap>(is);
    }
    else if( SequenceOfItems *si = dynamic_cast<SequenceOfItems*>(v) )
    {
      si->template Read<TDE,TSwap>(is);
    }
    else if( SequenceOfFragments *sf = dynamic_cast<SequenceOfFragments*>(v) )
    {
      sf->template Read<TSwap>(is);
    }
    else
    {
	    assert( 0 && "error" );
    }
    return is;
  }

  template <typename DE, typename TSwap>
  const std::ostream &ValueIO<DE,TSwap>::Write(std::ostream &os, const Value& _v) {
    const Value* v = &_v;
    if( const ByteValue *bv = dynamic_cast<const ByteValue*>(v) )
    {
	    bv->template Write<TSwap>(os);
    }
    else if( const SequenceOfItems *si = dynamic_cast<const SequenceOfItems*>(v) )
    {
	    si->template Write<DE,TSwap>(os);
    }
    else if( const SequenceOfFragments *sf = dynamic_cast<const SequenceOfFragments*>(v) )
    {
	    sf->template Write<TSwap>(os);
    }
    else
    {
	    assert( 0 && "error" );
    }
    return os;
  }

} // end namespace gdcm

#endif // __gdcmValue_txx

