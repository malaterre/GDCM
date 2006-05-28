
#ifndef __gdcmDataSet_h
#define __gdcmDataSet_h


#include "gdcmDataElement.h"

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

  void Clear();

  void AddDataElement(const DataElement& de);
  const DataElement& GetDataElement(const Tag &t) const;

  //bool IsEmpty() { return DataElements.empty(); }

private:
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &_os, const DataSet &_val)
{
  return _os;
}

} // end namespace gdcm

#endif //__gdcmDataSet_h
