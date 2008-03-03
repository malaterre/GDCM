/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
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
class GDCM_EXPORT DataSet
{
public:
  typedef std::set<DataElement> DataElementSet;
  typedef DataElementSet::const_iterator ConstIterator;
  typedef DataElementSet::size_type SizeType;
  //typedef typename DataElementSet::iterator iterator;
  ConstIterator Begin() const { return DES.begin(); }
  ConstIterator End() const { return DES.end(); }
  const DataElementSet &GetDES() const { return DES; }
  DataElementSet &GetDES() { return DES; }
  void Clear() {
    DES.clear();
    assert( DES.empty() );
  }

  unsigned int Size() const {
    return DES.size();
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
 void Replace(const DataElement& de) {
    //assert( de.GetTag() != Tag(0,0) );
    if( DES.find(de) != DES.end() ) DES.erase(de);
    DES.insert(de);
    }
 SizeType Remove(const Tag& tag) {
    //assert( de.GetTag() != Tag(0,0) );
    //const DataElement r(tag);
    DataElementSet::size_type count = DES.erase(tag);
    assert( count == 0 || count == 1 );
    return count;
    }

  // WARNING:
  // This only search at the same level as the DataSet is !
  const DataElement& GetDataElement(const Tag &t) const {
    const DataElement r(t);
    ConstIterator it = DES.find(r);
    if( it != DES.end() )
      return *it;
    return GetDEEnd();
    }
  const DataElement& operator[] (const Tag &t) const { return GetDataElement(t); }
  const DataElement& operator() (uint16_t group, uint16_t element) const { return GetDataElement( Tag(group,element) ); }

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
  const DataElement& FindNextDataElement(const Tag &t) const {
    const DataElement r(t);
    ConstIterator it = DES.lower_bound(r);
    if( it != DES.end() )
      return *it;
    return GetDEEnd();
    }

  bool IsEmpty() const { return DES.empty(); };

  DataSet& operator=(DataSet const &val)
  {
    DES = val.DES;
    return *this;
  }

/*
  template <typename TOperation>
  void ExecuteOperation(TOperation & operation) {
    assert( !DES.empty() );
    DataElementSet::iterator it = Begin();
    for( ; it != End(); ++it)
      {
      DataElement &de = (DataElement&)*it;
      operation( de );
      }
  }
*/

  template <typename TDE, typename TSwap>
  std::istream &ReadNested(std::istream &is);

  template <typename TDE, typename TSwap>
  std::istream &Read(std::istream &is);

  template <typename TDE, typename TSwap>
  std::istream &ReadUpToTag(std::istream &is, const Tag &t);

  template <typename TDE, typename TSwap>
  std::ostream const &Write(std::ostream &os) const;

  template <typename TDE, typename TSwap>
  std::istream &ReadWithLength(std::istream &is, VL &length);

protected:
  /* GetDEEnd is a Win32 only issue, one cannot use a dllexported
   * static member data in an inline function, otherwise symbol
   * will get reported as missing in any dll using the inlined function
   */
  const DataElement& GetDEEnd() const;

private:
  DataElementSet DES;
  static DataElement DEEnd;
  friend std::ostream& operator<<(std::ostream &_os, const DataSet &val);
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const DataSet &val)
{
  val.Print(os);
  return os;
}

} // end namespace gdcm

#include "gdcmDataSet.txx"

#endif //__gdcmDataSet_h

