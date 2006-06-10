
#ifndef __gdcmOFStream_h
#define __gdcmOFStream_h

#include "gdcmOStream.h"

#include <string>
#include <fstream>

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
  OFStream();
  explicit OFStream(const char *filename);
  ~OFStream();

  void Open(const char *filename);
  void Close();

private:
  std::string FileName;
  std::ofstream InternalOStream;

  OFStream(OFStream const &);
  OFStream &operator= (OFStream const &);
};

}

#endif //__gdcmOFStream_h

