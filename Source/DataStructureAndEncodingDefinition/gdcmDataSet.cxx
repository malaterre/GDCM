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
#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

#include <set>
#include <iterator>

namespace gdcm
{

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
  virtual IStream &ReadWithLength(IStream &is, VL const &length) = 0;
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
    DEType de;
    typename DataElementSet::const_iterator it = DES.begin();
    for( ; it != DES.end(); ++it)
      {
      //std::cerr << "DEBUG:" << *it << std::endl;
      it->Write(os);
      }
    return os;
  }

  IStream &ReadWithLength(IStream &is, VL const &length) {
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
      //std::cout << "Length: " << l << std::endl;
      // Bug_Philips_ItemTag_3F3F
      //  (0x2005, 0x1080): for some reason computation of length fails...
      if( l == 70 && locallength == 63 )
        {
        gdcmWarningMacro( "PMS: Super bad hack" );
        locallength = 140;
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
    typename DataElementSet::iterator it = DES.find(r);
    assert( DES.find(r) != DES.end() );
    return *it;
    }

  bool FindDataElement(const Tag &t) const {
    const DEType r(t);
    typename DataElementSet::iterator it = DES.find(r);
    if( DES.find(r) != DES.end() )
      {
      return true;
      }
    return false;
    }

private:
  DataElementSet DES;
};

//-----------------------------------------------------------------------------
class DataSetIteratorInternal
{
  //std
};

void DataSetIterator::Next()
{
  if( Internal == 0 )
    {
    Internal = new DataSetIteratorInternal();
    }
}

//-----------------------------------------------------------------------------
void DataSet::Print(std::ostream &os) const
{
  os << "TS: " << NegociatedTS << "\n";
  StructuredSetBase *p = Internal;
  p->Print( os );
}


//-----------------------------------------------------------------------------
DataSet::DataSet(TS::NegociatedType const &type):Length(0)
{
  if(type == TS::Explicit)
    {
    Internal = new StructuredSet<ExplicitDataElement>;
    }
  else if ( type == TS::Implicit )
    {
    Internal = new StructuredSet<ImplicitDataElement>;
    }
  else
    {
    Internal = 0;
    }
  NegociatedTS = type;
}

//-----------------------------------------------------------------------------
DataSet::~DataSet()
{
  delete Internal;
}

//-----------------------------------------------------------------------------
DataSet& DataSet::operator=(DataSet const &)
{
  abort();
  return *this;
}

//-----------------------------------------------------------------------------
DataSet::DataSet(DataSet const &ds):Value(ds)
{
  NegociatedTS = ds.NegociatedTS;
  if ( NegociatedTS == TS::Explicit )
    {
    Internal = new StructuredSet<ExplicitDataElement>;
    }
  else if ( NegociatedTS == TS::Implicit )
    {
    Internal = new StructuredSet<ImplicitDataElement>;
    }
  else
    {
    Internal = 0;
    }
  *Internal = *(ds.Internal);
}

//-----------------------------------------------------------------------------
void DataSet::Clear() {
  Internal->Clear();
}

//-----------------------------------------------------------------------------
void DataSet::InsertDataElement(DataElement const &de)
{
  if(NegociatedTS == TS::Explicit)
    {
    const ExplicitDataElement & xde =
      static_cast<const ExplicitDataElement&>(de);
    static_cast<StructuredSet<ExplicitDataElement>* >(Internal)->
      Insert(xde);
    }
  else
    {
    const ImplicitDataElement & ide =
      static_cast<const ImplicitDataElement&>(de);
    static_cast<StructuredSet<ImplicitDataElement>* >(Internal)->
      Insert(ide);
    }
}

//-----------------------------------------------------------------------------
const DataElement& DataSet::GetDataElement(const Tag &t) const
{
  if(NegociatedTS == TS::Explicit)
  {
    return static_cast<StructuredSet<ExplicitDataElement>* >(Internal)->
      GetDataElement(t);
  }
  else
  {
    return static_cast<StructuredSet<ImplicitDataElement>* >(Internal)->
      GetDataElement(t);
  }
}

bool DataSet::FindDataElement(const Tag &t) const
{
  if(NegociatedTS == TS::Explicit)
  {
    return static_cast<StructuredSet<ExplicitDataElement>* >(Internal)->
      FindDataElement(t);
  }
  else
  {
    return static_cast<StructuredSet<ImplicitDataElement>* >(Internal)->
      FindDataElement(t);
  }
}

//-----------------------------------------------------------------------------
IStream &DataSet::Read(IStream &is)
{
  if( Length == 0)
    {
    // Ok we are reading a root DataSet
    Internal->Read(is);
    }
  else if( Length.IsUndefined() )
    {
    // Nested DataSet with undefined length 
    Internal->ReadNested(is);
    }
  else
    {
    // Nested DataSet with defined length
    Internal->ReadWithLength(is, Length);
    }
  return is;
}

const VL & DataSet::GetLength() const
{
  static VL length = 0;
  if( Length.IsUndefined() )
    {
    length = Internal->GetLength();
    return length;
    }
  return Length;
}

//-----------------------------------------------------------------------------
OStream &DataSet::Write(OStream &os) const
{
  Internal->Write(os);
  return os;
}

} // end namespace gdcm
