
#ifndef __gdcmFileChunk_h
#define __gdcmFileChunk_h

/**
 * \brief Will retains an offset start and an offset end
 * usefull to store the beinging and end of let say a group
 * usefull to store the beinging and end of let say a Sequence
 * \note bla
 */

#include "gdcmType.h"
#include <fstream>
#include <assert.h>

namespace gdcm
{
class FileChunk
{
public:
  FileChunk() { OffsetStart = OffsetEnd = 0; }
  FileChunk(std::streampos start, std::streampos end) {
    assert( start <= end );
    OffsetStart = start; OffsetEnd = end; }

  std::streampos GetOffsetStart() const { return OffsetStart; }
  void SetOffsetStart(std::streampos start) { 
    assert( start <= OffsetEnd );
    OffsetStart = start; }

  std::streampos GetOffsetEnd() const { return OffsetEnd; }
  void SetOffsetEnd(std::streampos end) { 
    assert( OffsetStart <= end );
    OffsetEnd = end; }

private:
  std::streampos OffsetStart;
  std::streampos OffsetEnd;
};

}

#endif //__gdcmFileChunk_h
