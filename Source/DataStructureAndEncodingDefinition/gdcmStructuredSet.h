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
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

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
  template <typename TSwap> friend class IOSerialize;
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

private:
  DataElementSet DES;
};


} // end namespace gdcm

#endif //__gdcmStructuredSet_h

