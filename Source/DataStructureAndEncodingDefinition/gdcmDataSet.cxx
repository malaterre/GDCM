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
  bool operator()(const DataElement& s1,
		  const DataElement& s2) const
  {
    return s1.GetTag() < s2.GetTag();
  }
};

//-----------------------------------------------------------------------------
class StructuredSetBase {
public:
  virtual ~StructuredSetBase() {}

  virtual void Clear() = 0;
  virtual unsigned int Size() const = 0;
  virtual void Print(std::ostream &os) const = 0;
  virtual IStream &Read(IStream &is) = 0;
  virtual IStream &ReadNested(IStream &is) = 0;
  virtual IStream &ReadWithLength(IStream &is, VL const & length) = 0;
};

//-----------------------------------------------------------------------------
template<class DEType>
class StructuredSet : public StructuredSetBase
{
public:
  typedef typename std::set<DEType, lttag> DataElementSet;
  //typedef typename DataElementSet::iterator iterator;
  virtual unsigned int Size() const {
    return DES.size();
  }
  virtual void Clear() {
    DES.clear();
  }

  void Print(std::ostream &os) const {
    std::copy(DES.begin(), DES.end(), 
      std::ostream_iterator<DEType>(os, "\n"));
  }

  IStream &Read(IStream &is) {
    DEType de;
    while( !is.Eof() && de.Read(is) )
      {
      //std::cerr << de << std::endl;
      assert( de.GetTag() != Tag(0,0) );
      DES.insert( de );
      }
    return is;
  }

  IStream &ReadWithLength(IStream &is, VL const & length) {
    DEType de;
    VL l = 0;
    //std::cout << "Length: " << l << std::endl;
    while( l != length && de.Read(is))
      {
      //std::cout << "Nested: " << de << std::endl;
      DES.insert( de );
      l += de.GetLength();
      assert( !de.GetVL().IsUndefined() );
      assert( l <= length );
      //std::cout << "Length: " << l << std::endl;
      }
    assert( l == length );
    return is;
  }

  IStream &ReadNested(IStream &is) {
    DEType de;
    const Tag itemDelItem(0xfffe,0xe00d);
    while( de.GetTag() != itemDelItem && de.Read(is) )
      {
      //std::cout << de << std::endl;
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
std::ostream& operator<<(std::ostream &os, const DataSet &val)
{
  os << "TS: " << val.NegociatedTS << "\n";
  StructuredSetBase *p = val.Internal;
  p->Print( os );
  return os;
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
unsigned int DataSet::Size() const {
  return Internal->Size();
}

//-----------------------------------------------------------------------------
void DataSet::InsertDataElement(DataElement const & de)
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

//-----------------------------------------------------------------------------
OStream &DataSet::Write(OStream &os) const
{
  return os;
}

} // end namespace gdcm
