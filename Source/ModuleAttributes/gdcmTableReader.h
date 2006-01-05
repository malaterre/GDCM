#ifndef __gdcmTableReader_h
#define __gdcmTableReader_h

#include "gdcmType.h"
#include "expat/lib/expat.h"
#include <string>

namespace gdcm
{
/**
 * \brief Class for reprensenting a TableReader
 * \note bla
 */
class GDCM_EXPORT TableReader
{
public:
  TableReader() {}
  ~TableReader() {}

  // Set/Get filename
  void SetFilename(std::string const &filename) { Filename = filename; }
  std::string const &GetFilename() { return Filename; }

  int Read();

private:
  std::string Filename;
};

} // end namespace gdcm

#endif //__gdcmTableReader_h
