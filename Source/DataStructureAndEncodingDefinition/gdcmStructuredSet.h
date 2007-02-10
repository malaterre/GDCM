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
#ifndef __gdcmStructuredSet_h
#define __gdcmStructuredSet_h

#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmElement.h"
#include "gdcmStringStream.h"
#include "gdcmByteValue.h"

#include <set>
#include <iterator>

namespace gdcm
{
/**
 * \brief Class to represent
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
class StructuredSetBase {
public:
  virtual ~StructuredSetBase() {}

  virtual void Clear() = 0;
  virtual void Print(std::ostream &os) const = 0;
  virtual IStream &Read(IStream &is) = 0;
  virtual IStream &ReadNested(IStream &is) = 0;
  virtual IStream &ReadWithLength(IStream &is, VL &length) = 0;
  virtual VL GetLength() const = 0;
  virtual OStream &Write(OStream &os) = 0;
};


//-----------------------------------------------------------------------------
template<class DEType>
class StructuredSet : public StructuredSetBase
{
public:
  typedef typename std::set<DEType, lttag> DataElementSet;
  typedef typename DataElementSet::iterator DataElementSetIterator;
  DataElementSetIterator Begin() { return DES.begin(); }
  DataElementSetIterator End() { return DES.end(); }

  //typedef typename DataElementSet::iterator iterator;
  virtual void Clear() {
    DES.clear();
  }

  void Print(std::ostream &os) const {
    // CT_Phillips_JPEG2K_Decompr_Problem.dcm has a SQ of length == 0
    //int s = DES.size();
    //assert( s );
    std::copy(DES.begin(), DES.end(), 
      std::ostream_iterator<DEType>(os, "\n"));
  }

  IStream &Read(IStream &is) {
    DEType de;
    while( !is.Eof() && de.Read(is) )
      {
      //std::cerr << "DEBUG:" << de << std::endl;
      assert( de.GetTag() != Tag(0,0) );
      DES.insert( de );
      }
    return is;
  }

  OStream &Write(OStream &os) {
    //DEType de;
    typename DataElementSet::const_iterator it = DES.begin();
    for( ; it != DES.end(); ++it)
      {
      //std::cerr << "DEBUG:" << *it << std::endl;
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
        StringStream ss;
        ss.SetSwapCode( os.GetSwapCode() );
        const Value &v = de.GetValue();
        const Value *pv = &v;
        const ByteValue *bv = dynamic_cast<const ByteValue*>(pv);
        bv->Write( ss );
        el.Read( ss );
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
          el.Write( ss );
          // Pass it to the ByteValue
          ByteValue *bv2 = new ByteValue;
          bv2->SetLength(4);
          bv2->Read(ss);
          correct.SetValue( *bv2 );
          correct.Write(os);
          }
        else
          {
          // okay good value
          it->Write(os);
          }
        }
      else // well simply writes it
        {
        it->Write(os);
        }
      }
    return os;
  }

  unsigned int ComputeGroupLength(Tag const &tag)
    {
    assert( tag.GetElement() == 0x0 );
    const DEType r(tag);
    typename DataElementSet::const_iterator it = DES.find(r);
    unsigned int res = 0;
    for( ++it; it != DES.end()
      && it->GetTag().GetGroup() == tag.GetGroup(); ++it)
      {
      assert( it->GetTag().GetElement() != 0x0 );
      res += it->GetLength();
      }
    return res;
    }

  IStream &ReadWithLength(IStream &is, VL &length) {
    DEType de;
    VL l = 0;
    //std::cout << "Length: " << l << std::endl;
    VL locallength = length;
    while( l != locallength && de.Read(is))
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

  VL GetLength() const {
    assert( !DES.empty() );
    VL ll = 0;
    assert( ll == 0 );
    typename DataElementSet::const_iterator it = DES.begin();
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
  IStream &ReadNested(IStream &is) {
    DEType de;
    const Tag itemDelItem(0xfffe,0xe00d);
    while( de.GetTag() != itemDelItem && de.Read(is) )
      {
      //std::cout << "DEBUG: " << de << std::endl;
      DES.insert( de );
      }
    assert( de.GetTag() == itemDelItem );
    return is;
  }

  virtual void Insert(const DEType& de) {
    //assert( de.GetTag() != Tag(0,0) );
    DES.insert(de);
    }

  const DEType& GetDataElement(const Tag &t) const {
    const DEType r(t);
    typename DataElementSet::const_iterator it = DES.find(r);
    assert( DES.find(r) != DES.end() );
    return *it;
    }

  bool FindDataElement(const Tag &t) const {
    const DEType r(t);
    typename DataElementSet::const_iterator it = DES.find(r);
    if( DES.find(r) != DES.end() )
      {
      return true;
      }
    return false;
    }

private:
  DataElementSet DES;
};

} // end namespace gdcm

#endif //__gdcmStructuredSet_h

