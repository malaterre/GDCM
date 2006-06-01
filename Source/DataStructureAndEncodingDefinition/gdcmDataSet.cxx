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
  virtual void Size() = 0;
};
template<class DEType>
class StructuredSet : public StructuredSetBase
{
public:
  typedef typename std::set<DEType, ltstr> DataElementSet;
  typedef typename DataElementSet::iterator iterator;
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
}

void DataSet::Clear() {
  Internal->DES.clear();
}

unsigned int DataSet::Size() {
  return Internal->DES.size();
}

void DataSet::InsertDataElement(const DataElement& de)
{
  Internal->DES.insert(de);
}

const DataElement& DataSet::GetDataElement(const Tag &t) const
{
  const DataElement r(t);
  StructuredSet::iterator it = Internal->DES.find(r);
  return *it;
}

} // end namespace gdcm
