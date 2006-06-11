
#ifndef __gdcmIStream_h
#define __gdcmIStream_h

#include "gdcmIOS.h"

//#include <fstream>

namespace gdcm
{

/**
 * \brief Wrapper around ifstream
 * specialized for binary stream. Is able to read DICOM attribute
 * \note bla
 */

class GDCM_EXPORT IStream : virtual public IOS
{

public:
  IStream();
  ~IStream();

  virtual IStream& Seekg (std::streamoff off, std::ios_base::seekdir dir);
  virtual std::streampos Tellg ( );

  virtual IStream& Read(char *str, std::streamsize n);
  virtual IStream& Get (char& c );
  virtual bool Eof();

  IStream &Read(uint16_t &vl);

private:
  IStream(IStream const &);
  IStream &operator= (IStream const &);
};

}

#endif //__gdcmIStream_h

