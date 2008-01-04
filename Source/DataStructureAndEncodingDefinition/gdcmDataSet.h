/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmDataSet_h
#define __gdcmDataSet_h

#include "gdcmDataElement.h"
#include "gdcmTag.h"
#include "gdcmVR.h"
#include "gdcmElement.h"

#include <set>
#include <iterator>

namespace gdcm
{
/**
 * \brief Class to represent a Data Set (which contains Data Elements)
 * A Data Set represents an instance of a real world Information Object
 * \note
 * DATA SET: 
 * Exchanged information consisting of a structured set of Attribute values
 * directly or indirectly related to Information Objects. The value of each
 * Attribute in a Data Set is expressed as a Data Element.
 * A collection of Data Elements ordered by increasing Data Element Tag 
 * number that is an encoding of the values of Attributes of a real world 
 * object.
 * \note
 * Implementation note. If one do:
 * DataSet ds;
 * ds.SetLength(0);
 * ds.Read(is);
 * setting length to 0 actually means try to read is as if it was a root
 * DataSet. Other value are undefined (nested dataset with undefined length)
 * or defined length (different from 0) means nested dataset with defined
 * length.
 *
 * TODO:
 * a DataSet DOES NOT have a TS type... a file does !
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
class DataSet
{
public:
  typedef std::set<DataElement, lttag> DataElementSet;
  typedef DataElementSet::iterator Iterator;
  typedef DataElementSet::const_iterator ConstIterator;
  Iterator Begin() { return DES.begin(); }
  Iterator End() { return DES.end(); }
  ConstIterator Begin() const { return DES.begin(); }
  ConstIterator End() const { return DES.end(); }


  //typedef typename DataElementSet::iterator iterator;
  void Clear() {
    DES.clear();
  }

  void Print(std::ostream &os, std::string const &indent = "") const {
    // CT_Phillips_JPEG2K_Decompr_Problem.dcm has a SQ of length == 0
    //int s = DES.size();
    //assert( s );
    //std::copy(DES.begin(), DES.end(), 
    //  std::ostream_iterator<DataElement>(os, "\n"));
    ConstIterator it = DES.begin();
    for( ; it != DES.end(); ++it)
      {
      os << indent << *it << "\n";
      }
  }

  template <typename TDE>
  unsigned int ComputeGroupLength(Tag const &tag) const
    {
    assert( tag.GetElement() == 0x0 );
    const DataElement r(tag);
    ConstIterator it = DES.find(r);
    unsigned int res = 0;
    for( ++it; it != DES.end()
      && it->GetTag().GetGroup() == tag.GetGroup(); ++it)
      {
      assert( it->GetTag().GetElement() != 0x0 );
      assert( it->GetTag().GetGroup() == tag.GetGroup() );
      res += it->GetLength<TDE>();
      }
    return res;
    }

  template <typename TDE>
  VL GetLength() const {
    assert( !DES.empty() );
    VL ll = 0;
    assert( ll == 0 );
    ConstIterator it = DES.begin();
    for( ; it != DES.end(); ++it)
      {
      assert( !(it->GetLength<TDE>().IsUndefined()) );
      VL len = it->GetLength<TDE>();
      if ( it->GetTag() != Tag(0xfffe,0xe00d) )
        {
        ll += it->GetLength<TDE>();
        }
      }
    return ll;
  }
 void Insert(const DataElement& de) {
    //assert( de.GetTag() != Tag(0,0) );
    DES.insert(de);
    }

  // WARNING:
  // This only search at the same level as the DataSet is !
  const DataElement& GetDataElement(const Tag &t) const {
    const DataElement r(t);
    ConstIterator it = DES.find(r);
    assert( it != DES.end() );
    return *it;
    }
  const DataElement& operator[] (const Tag &t) const { return GetDataElement(t); }

  std::string GetPrivateCreator(const Tag &t) const;

  // DUMB: this only search within the level of the current DataSet
  bool FindDataElement(const Tag &t) const {
    const DataElement r(t);
    ConstIterator it = DES.find(r);
    if( DES.find(r) != DES.end() )
      {
      return true;
      }
    return false;
    }

  // WARNING:
  // This only search at the same level as the DataSet is !
  const DataElement& GetNextDataElement(const Tag &t) const {
    const DataElement r(t);
    ConstIterator it = DES.lower_bound(r);
    assert( it != DES.end() );
    return *it;
    }

  bool IsEmpty() const { return DES.empty(); };

  DataSet& operator=(DataSet const &val)
  {
    DES = val.DES;
    return *this;
  }

  template <typename TOperation>
  void ExecuteOperation(TOperation & operation) {
    assert( !DES.empty() );
    DataElementSet::iterator it = Begin();
    for( ; it != End(); ++it)
      {
      gdcm::DataElement &de = (gdcm::DataElement&)*it;
      operation( de );
      }
  }

  template <typename TDE, typename TSwap>
  std::istream &ReadNested(std::istream &is);

  template <typename TDE, typename TSwap>
  std::istream &Read(std::istream &is);

  template <typename TDE, typename TSwap>
  std::ostream const &Write(std::ostream &os) const;

  template <typename TDE, typename TSwap>
  std::istream &ReadWithLength(std::istream &is, VL &length);

private:
  DataElementSet DES;
};


} // end namespace gdcm

#include "gdcmDataSet.txx"

#endif //__gdcmDataSet_h

