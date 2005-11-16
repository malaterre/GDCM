#include "gdcmFileChunk.h"
#include "gdcmFileGroup.h"
#include "gdcmFileSequence.h"

int TestFileChunk(int , char *[])
{
  gdcm::FileChunk fc1;
  std::streampos zero = 0;
  if ( fc1.GetOffsetStart() != zero)
    return 1;
  if ( fc1.GetOffsetEnd() != zero)
    return 1;

  std::streampos start = 10;
  std::streampos end = 20;
  gdcm::FileChunk fc2(start, end);
  if ( fc2.GetOffsetStart() != start)
    return 1;
  if ( fc2.GetOffsetEnd() != end)
    return 1;

  gdcm::FileGroup fg1;
  if ( fg1.GetOffsetStart() != zero)
    return 1;
  if ( fg1.GetOffsetEnd() != zero)
    return 1;
  gdcm::FileGroup fg2(20, 30);
  const uint16_t group = 0x10;
  fg2.SetGroup( group );
  if( group != fg2.GetGroup() )
    return 1;

  return 0;
}
