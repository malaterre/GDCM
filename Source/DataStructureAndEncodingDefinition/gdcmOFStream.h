
#ifndef __gdcmOFStream_h
#define __gdcmOFStream_h

#include "gdcmOStream.h"

#include <fstream>
#include <iostream>
#include <assert.h>

namespace gdcm
{

/**
 * \brief Wrapper around ofstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT OFStream : public OStream
{
public:
  OFStream(const char *filename);
  ~OFStream();

private:
  OFStream(OFStream const &);
  OFStream &operator= (OFStream const &);
};

}

#endif //__gdcmOFStream_h

