
#ifndef __gdcmFileMetaInformation_h
#define __gdcmFileMetaInformation_h

#include "gdcmDataSet.h"

namespace gdcm
{
/**
 * \brief Class to represent a File Meta Information
 * \note
 * In theory this should only be explicit, but just in case
 */
class GDCM_EXPORT FileMetaInformation : public DataSet
{
public:
  FileMetaInformation(TS::NegociatedType const &type = TS::Explicit) {}
  ~FileMetaInformation() {}

  friend std::ostream& operator<<(std::ostream &_os, const FileMetaInformation &_val);

  void InsertDataElement(const DataElement& de) {
    assert( de.GetTag().GetGroup() == 0x0002 );
    DataSet::InsertDataElement(de);
  }

  IStream &Read(IStream &is);

  OStream &Write(OStream &os) const;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const FileMetaInformation &val)
{
  (void)val;
  //std::copy(val.Internal.begin(), val.Internal.end(), 
  //  std::ostream_iterator<DataElement>(os, "\n"));
  return os;
}

} // end namespace gdcm

#endif //__gdcmFileMetaInformation_h

