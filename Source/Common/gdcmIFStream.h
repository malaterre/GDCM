
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

  operator void * ( ) const { return InternalIStream; }

  void Open(const char* filename);
  bool IsOpen() { return InternalIStream.is_open(); }
  void Close();

  IStream& Seekg (std::streamoff off, std::ios_base::seekdir dir);
  std::streampos Tellg ( );
  IStream& Read(char *str, std::streamsize n);
  bool Eof() { return InternalIStream.eof(); }

private:
  std::string FileName;
  std::ifstream InternalIStream;

  IFStream(IFStream const &);
  IFStream &operator= (IFStream const &);
};

}

#endif //__gdcmIFStream_h

