#include "gdcmFileChunk.h"
#include <fstream>

int TestFileIO(int , char *[])
{
  std::streampos p1 = 5;
  std::streampos p2 = 10;
  if( p1 > p2 )
    return 1;
  if( p2 < p1 )
    return 1;

  return 0;
}
