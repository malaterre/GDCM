
#ifndef __gdcmIStream_h
#define __gdcmIStream_h

#include "gdcmIOS.h"

#include <fstream>

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
  IStream(std::streambuf *sb);
  ~IStream();

//  IStream &operator>> (char &c);
//  IStream &operator>> (signed char &c);
//  IStream &operator>> (unsigned char &c);
//
//  IStream &operator>> (float &f);
//  IStream &operator>> (double &d);
//
//  IStream &operator>> (short &s);
//  IStream &operator>> (unsigned short &s);
//  IStream &operator>> (int &i);
//  IStream &operator>> (unsigned int &i);
//  IStream &operator>> (long &l);
//  IStream &operator>> (unsigned long &l);
//
//  IStream &operator>> (char *str);

  IStream& Seekg (std::streamoff off, std::ios_base::seekdir dir);
  std::streampos Tellg ( );

  IStream& Read(char *str, std::streamsize n);
  IStream& Get (char& c );

private:
  IStream(IStream const &);
  IStream &operator= (IStream const &);
};

}

#endif //__gdcmIStream_h

