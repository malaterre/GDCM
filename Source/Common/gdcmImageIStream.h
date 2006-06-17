#ifndef __gdcmImageIStream_h
#define __gdcmImageIStream_h

#include "gdcmImage.h"

namespace gdcm
{

/**
 * \brief ImageIStream
 * \note
 * Image constructed from a IStream
 */
class IStream;
class GDCM_EXPORT ImageIStream : public Image
{
public:
  ImageIStream();
  ~ImageIStream();

  // Acces the raw data
  bool GetBuffer(char *buffer) const;

private:
  IStream *Stream;
};

} // end namespace gdcm

#endif //__gdcmImageIStream_h

