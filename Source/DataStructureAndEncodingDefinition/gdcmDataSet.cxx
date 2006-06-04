#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

namespace gdcm
{

struct ltstr
{
  bool operator()(const DataElement& s1,
		  const DataElement& s2) const
  {
    return s1.GetTag() < s2.GetTag();
  }
};

class StructuredSetBase {
public:
  virtual void Clear() = 0;
  virtual unsigned int Size() = 0;
  virtual ~StructuredSetBase() {}
};

template<class DEType>
class StructuredSet : public StructuredSetBase
{
public:
  typedef typename std::set<DEType, ltstr> DataElementSet;
  //typedef typename DataElementSet::iterator iterator;
  virtual unsigned int Size() {
    return DES.size();
  }
  virtual void Clear() {
    DES.clear();
  }
  virtual void Insert(const DEType& de) {
    DES.insert(de);
    }

  const DEType& GetDataElement(const Tag &t) const
    {
    const DEType r(t);
    typename DataElementSet::iterator it = DES.find(r);
    return *it;
    }

private:
  DataElementSet DES;
};


DataSet::DataSet(TS::NegociatedType const &type)
{
  if(type == TS::Explicit)
  {
    Internal = new StructuredSet<ExplicitDataElement>;
  }
  else
  {
    Internal = new StructuredSet<ImplicitDataElement>;
  }
  NegociatedTS = type;
}

DataSet::~DataSet()
{
  delete Internal;
}

void DataSet::Clear() {
  Internal->Clear();
}

unsigned int DataSet::Size() {
  return Internal->Size();
}

void DataSet::InsertDataElement(const DataElement& de)
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

gdcm::IStream &DataSet::Read(gdcm::IStream &is)
{
  return is;
}

gdcm::OStream &DataSet::Write(gdcm::OStream &os) const
{
  return os;
}

} // end namespace gdcm
