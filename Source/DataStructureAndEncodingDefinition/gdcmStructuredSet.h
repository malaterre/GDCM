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
#ifndef __gdcmStructuredSet_h
#define __gdcmStructuredSet_h

#include "gdcmDataElement.h"
#include "gdcmTag.h"
#include "gdcmVR.h"
#include "gdcmElement.h"
#include "gdcmStringStream.h"
#include "gdcmByteValue.h"
//#include "gdcmExplicitDataElement.h"
//#include "gdcmImplicitDataElement.h"

#include <set>
#include <iterator>

namespace gdcm
{
/**
 * \brief TODO This class should be merged with DataSet !!!
 */

//-----------------------------------------------------------------------------
struct lttag
{
  bool operator()(const DataElement &s1,
		  const DataElement &s2) const
  {
    return s1.GetTag() < s2.GetTag();
  }
};

//-----------------------------------------------------------------------------
template<class DEType>
class StructuredSet
{
public:
  typedef typename std::set<DEType, lttag> DataElementSet;
  typedef typename DataElementSet::iterator Iterator;
  typedef typename DataElementSet::const_iterator ConstIterator;
  Iterator Begin() { return DES.begin(); }
  Iterator End() { return DES.end(); }
  ConstIterator Begin() const { return DES.begin(); }
  ConstIterator End() const { return DES.end(); }


  //typedef typename DataElementSet::iterator iterator;
  void Clear() {
    DES.clear();
  }

  void Print(std::ostream &os) const {
    // CT_Phillips_JPEG2K_Decompr_Problem.dcm has a SQ of length == 0
    //int s = DES.size();
    //assert( s );
    std::copy(DES.begin(), DES.end(), 
      std::ostream_iterator<DEType>(os, "\n"));
  }

 unsigned int ComputeGroupLength(Tag const &tag) const
    {
    assert( tag.GetElement() == 0x0 );
    const DEType r(tag);
    ConstIterator it = DES.find(r);
    unsigned int res = 0;
    for( ++it; it != DES.end()
      && it->GetTag().GetGroup() == tag.GetGroup(); ++it)
      {
      assert( it->GetTag().GetElement() != 0x0 );
      assert( it->GetTag().GetGroup() == tag.GetGroup() );
      res += it->GetLength();
      }
    return res;
    }

  VL GetLength() const {
    assert( !DES.empty() );
    VL ll = 0;
    assert( ll == 0 );
    ConstIterator it = DES.begin();
    for( ; it != DES.end(); ++it)
      {
      assert( !(it->GetLength().IsUndefined()) );
      VL len = it->GetLength();
      if ( it->GetTag() != Tag(0xfffe,0xe00d) )
        {
        ll += it->GetLength();
        }
      }
    return ll;
  }
 void Insert(const DEType& de) {
    //assert( de.GetTag() != Tag(0,0) );
    DES.insert(de);
    }

  const DEType& GetDataElement(const Tag &t) const {
    const DEType r(t);
    ConstIterator it = DES.find(r);
    assert( it != DES.end() );
    return *it;
    }

  bool FindDataElement(const Tag &t) const {
    const DEType r(t);
    ConstIterator it = DES.find(r);
    if( DES.find(r) != DES.end() )
      {
      return true;
      }
    return false;
    }
  
  bool IsEmpty() const { return DES.empty(); };

  template <typename OtherDEType> // TODO: Should be only Implicit or Explicit DataElement
  void Copy(const StructuredSet<OtherDEType>& ss)
  {
    typename StructuredSet<OtherDEType>::ConstIterator it = ss.Begin();
    for( ; it != ss.End(); ++it)
      {
      //std::cerr << *it << std::endl;
      DEType de( *it );
      Insert(de);
      }
   }

  StructuredSet<DEType>& operator=(StructuredSet<DEType> const &val)
  {
    DES = val.DES;
    return *this;
  }
  //StructuredSet<DEType>(StructuredSet<DEType> const &ds)
  //{
  //        assert( 0 && "TODO" );
  //}

  template <typename TSwap>
  IStream &ReadNested(IStream &is);

  template <typename TSwap>
  IStream &Read(IStream &is);

  template <typename TSwap>
  OStream const &Write(OStream &os) const {
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


  template <typename TSwap>
  IStream &ReadWithLength(IStream &is, VL &length);

protected:
 
 
private:
  DataElementSet DES;
};


} // end namespace gdcm

#endif //__gdcmStructuredSet_h

