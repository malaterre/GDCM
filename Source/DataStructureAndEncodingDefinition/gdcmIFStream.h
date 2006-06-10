
#ifndef __gdcmIFStream_h
#define __gdcmIFStream_h

#include "gdcmIStream.h"

//#include <fstream>
//#include <iostream>
//#include <assert.h>

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

  void SetFileName(const char* filename);
  void Open();
  void Close();

private:
  std::string FileName;

  IFStream(IFStream const &);
  IFStream &operator= (IFStream const &);
};

}

#endif //__gdcmIFStream_h

