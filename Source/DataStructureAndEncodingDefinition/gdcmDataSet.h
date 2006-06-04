
#ifndef __gdcmDataSet_h
#define __gdcmDataSet_h


#include "gdcmDataElement.h"
#include "gdcmTS.h"


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
class StructuredSetBase;
class GDCM_EXPORT DataSet
{
public:
  DataSet(TS::NegociatedType const &type = TS::Explicit);
  virtual ~DataSet();

  friend std::ostream& operator<<(std::ostream &_os, const DataSet &_val);

  // Clear
  void Clear();

  // Size
  unsigned int Size();

  // Insert
  virtual void InsertDataElement(const DataElement& de);

  // Get
  const DataElement& GetDataElement(const Tag &t) const;

  //bool IsEmpty() { return DataElements.empty(); }

  // Read
  virtual IStream &Read(IStream &is);

  // Write
  virtual OStream &Write(OStream &os) const;

private:
  TS::NegociatedType NegociatedTS;
  StructuredSetBase *Internal;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const DataSet &val)
{
  (void)val;
  //std::copy(val.Internal.begin(), val.Internal.end(), 
  //  std::ostream_iterator<DataElement>(os, "\n"));
  return os;
}

} // end namespace gdcm

#endif //__gdcmDataSet_h

