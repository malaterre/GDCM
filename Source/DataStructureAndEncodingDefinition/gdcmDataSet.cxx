#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

#include <set>
#include <iterator>

namespace gdcm
{

//-----------------------------------------------------------------------------
struct ltstr
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
};

//-----------------------------------------------------------------------------
template<class DEType>
class StructuredSet : public StructuredSetBase
{
public:
  typedef typename std::set<DEType, ltstr> DataElementSet;
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
    while( !is.Eof() )
      {
      de.Read(is);
      //std::cerr << de << std::endl;
      DES.insert( de );
      }
    return is;
  }

  virtual void Insert(const DEType& de) {
    DES.insert(de);
    }

  const DEType& GetDataElement(const Tag &t) const {
    const DEType r(t);
    typename DataElementSet::iterator it = DES.find(r);
    return *it;
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
DataSet::DataSet(TS::NegociatedType const &type)
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
  //delete Internal;
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
    dynamic_cast<StructuredSet<ExplicitDataElement>* >(Internal)->
      Insert(dynamic_cast<const ExplicitDataElement&>(de));
    }
  else
    {
    dynamic_cast<StructuredSet<ImplicitDataElement>* >(Internal)->
      Insert(dynamic_cast<const ImplicitDataElement&>(de));
    }
}

//-----------------------------------------------------------------------------
const DataElement& DataSet::GetDataElement(const Tag &t) const
{
  if(NegociatedTS == TS::Explicit)
  {
    return dynamic_cast<StructuredSet<ExplicitDataElement>* >(Internal)->
      GetDataElement(t);
  }
  else
  {
    return dynamic_cast<StructuredSet<ImplicitDataElement>* >(Internal)->
      GetDataElement(t);
  }
}

//-----------------------------------------------------------------------------
IStream &DataSet::Read(IStream &is)
{
  Internal->Read(is);
  return is;
}

//-----------------------------------------------------------------------------
OStream &DataSet::Write(OStream &os) const
{
  return os;
}

} // end namespace gdcm
