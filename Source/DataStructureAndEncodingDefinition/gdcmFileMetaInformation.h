
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
class ExplicitDataElement;
class ImplicitDataElement;
class GDCM_EXPORT FileMetaInformation
{
public:
  FileMetaInformation():DS(0) {}
  ~FileMetaInformation();

  friend std::ostream& operator<<(std::ostream &_os, const FileMetaInformation &_val);

  
  unsigned int Size() const {
    return DS->Size();
  }

  void InsertDataElement(const DataElement& de) {
    assert( de.GetTag().GetGroup() == 0x0002 );
    DS->InsertDataElement(de);
  }

  IStream &Read(IStream &is);

  OStream &Write(OStream &os) const;

protected:
  bool ReadExplicitDataElement(IStream &is, ExplicitDataElement &de);
  bool ReadImplicitDataElement(IStream &is, ImplicitDataElement &de);
private:
  DataSet *DS;
};
//-----------------------------------------------------------------------------
inline std::ostream& operator<<(std::ostream &os, const FileMetaInformation &val)
{
  DataSet ds = *(val.DS);
  os << ds;
  return os;
}

} // end namespace gdcm

#endif //__gdcmFileMetaInformation_h

