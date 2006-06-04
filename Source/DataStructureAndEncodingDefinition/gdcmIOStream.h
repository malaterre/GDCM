
#ifndef __gdcmIOStream_h
#define __gdcmIOStream_h

#include "gdcmType.h"
#include "gdcmSwapCode.h"

#include <fstream>

namespace gdcm
{

/**
 * \brief Wrapper around ifstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT IOStream : public IStream, public OStream
{
public:
  IOStream () {}
  ~IOStream() {}

protected:
};

}

#endif //__gdcmIOStream_h

