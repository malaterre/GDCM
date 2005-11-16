
#ifndef __gdcmFileGroup_h
#define __gdcmFileGroup_h

/**
 * \brief This define the start and end of the a particular group in a DICOM file
 * \note bla
 */

#include "gdcmFileChunk.h"

namespace gdcm
{
class FileGroup : public FileChunk
{
public:
  FileGroup() : FileChunk() {}
  FileGroup(std::streampos start, std::streampos end) : FileChunk(start, end) {}
  FileGroup(std::streampos start, std::streampos end, uint16_t group) : FileChunk(start, end) {
    Group = group; }

  void SetGroup(uint16_t group) { Group = group; }
  uint16_t GetGroup() const { return Group; }

private:
  uint16_t Group;
};

}

#endif //__gdcmFileGroup_h
