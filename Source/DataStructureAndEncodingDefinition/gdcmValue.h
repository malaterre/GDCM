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

#ifndef __gdcmValue_h
#define __gdcmValue_h

#include "gdcmObject.h"

// FIXME
#include "gdcmIStream.h"
#include "gdcmOStream.h"

namespace gdcm
{
/**
 * \brief Class to represent the value of a Data Element.
 * \note
 * VALUE: A component of a Value Field. A Value Field may consist of one
 * or more of these components.
 */
class VL;
class GDCM_EXPORT Value : public Object
{
public:
  Value() {}
  ~Value() {}

  virtual VL GetLength() const = 0;
  virtual void SetLength(VL l) = 0;

  virtual void Clear() = 0;

  //template <typename TSwap>
  //IStream& Read(IStream &is); // { return is;}
  //template <typename TSwap>
  //OStream const & Write(OStream &os); // const { return os;}
  template <typename TSwap>
  IStream &Read(IStream &is) {
//    if( ByteValue *bv = dynamic_cast<ByteValue*>(&v) )
//    {
//	    Read(is,*bv);
//    }
//    else if( SequenceOfItems *si = dynamic_cast<SequenceOfItems*>(&v) )
//    {
//	    Read(is,*si);
//    }
//    else if( SequenceOfFragments *sf = dynamic_cast<SequenceOfFragments*>(&v) )
//    {
//	    Read(is,*sf);
//    }
//    else
    {
	    assert( 0 && "error" );
    }
    return is;
  }
  template <typename TSwap>
  const OStream &Write(OStream &os) const {
//    if( const ByteValue *bv = dynamic_cast<const ByteValue*>(&v) )
//    {
//	    Write(os,*bv);
//    }
//    else if( const SequenceOfItems *si = dynamic_cast<const SequenceOfItems*>(&v) )
//    {
//	    Write(os,*si);
//    }
//    else if( const SequenceOfFragments *sf = dynamic_cast<const SequenceOfFragments*>(&v) )
//    {
//	    Write(os,*sf);
//    }
//    else
    {
	    assert( 0 && "error" );
    }
    return os;
  }
  
};


} // end namespace gdcm

#endif //__gdcmValue_h

