
#ifndef __gdcmImageReader_h
#define __gdcmImageReader_h

#include "gdcmDataSet.h"
#include "gdcmReader.h"

namespace gdcm
{
/**
 * \brief ImageReader
 */
class GDCM_EXPORT ImageReader : public Reader
{
public:
  ImageReader();
  ~ImageReader();

  const char *GetPointer() const;
private:
};

} // end namespace gdcm

#endif //__gdcmImageReader_h

