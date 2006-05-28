
#ifndef __gdcmDataSet_h
#define __gdcmDataSet_h


#include "gdcmDataElement.h"

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
 */
class GDCM_EXPORT DataSet
{
public:
  DataSet() {}

  friend std::ostream& operator<<(std::ostream &_os, const DataSet &_val);

  void Clear() {
    Internal.clear();
  }
  unsigned int Size() {
    return Internal.size();
  }

  void InsertDataElement(const DataElement& de) {
    Internal.insert(de);
  }
  const DataElement& GetDataElement(const Tag &t) const {
    const DataElement r(t);
    StructuredSet::iterator it = Internal.find(r);
    return *it;
  }

  //bool IsEmpty() { return DataElements.empty(); }

struct ltstr
{
  bool operator()(const DataElement& s1,
		  const DataElement& s2) const
  {
    return s1.GetTag() < s2.GetTag();
  }
};
  typedef std::set<DataElement, ltstr> StructuredSet;
  private:
  StructuredSet Internal;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const DataSet &val)
{
  std::copy(val.Internal.begin(), val.Internal.end(), 
    std::ostream_iterator<DataElement>(os, "\n"));
  return os;
}

} // end namespace gdcm

#endif //__gdcmDataSet_h
