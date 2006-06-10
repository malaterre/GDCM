
#ifndef __gdcmIOStream_h
#define __gdcmIOStream_h

#include "gdcmIStream.h"
#include "gdcmOStream.h"

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
  IOStream (std::streambuf* sb):IStream(sb),OStream(sb) {}
  ~IOStream() {}

protected:
};

}

#endif //__gdcmIOStream_h

