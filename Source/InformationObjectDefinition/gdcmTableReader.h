#ifndef __gdcmTableReader_h
#define __gdcmTableReader_h

#include "gdcmTypes.h"
#include <string>

namespace gdcm
{
/**
 * \brief Class for representing a TableReader
 * \note bla
 */
class GDCM_EXPORT TableReader
{
public:
  TableReader() {}
  ~TableReader() {}

  // Set/Get filename
  void SetFilename(const char *filename) { Filename = filename; }
  const char *GetFilename() { return Filename.c_str(); }

  int Read();

private:
  std::string Filename;
};

} // end namespace gdcm

#endif //__gdcmTableReader_h
