
#ifndef __gdcmIFStream_h
#define __gdcmIFStream_h

#include "gdcmIStream.h"

#include <string>
#include <fstream>

namespace gdcm
{

/**
 * \brief Wrapper around ifstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT IFStream : public IStream
{
public:
  IFStream();
  explicit IFStream(const char *filename);
  ~IFStream();

  void Open(const char* filename);
  void Close();

private:
  std::string FileName;
  std::ifstream InternalIStream;

  IFStream(IFStream const &);
  IFStream &operator= (IFStream const &);
};

}

#endif //__gdcmIFStream_h

