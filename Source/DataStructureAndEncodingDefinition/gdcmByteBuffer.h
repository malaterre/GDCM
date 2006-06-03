
#ifndef __gdcmByteBuffer_h
#define __gdcmByteBuffer_h

#include "gdcmTypes.h"
#include <vector>

namespace gdcm
{
/**
 * \brief ByteBuffer
 *
 * Detailled description here
 * \note 
 */
class ByteBuffer
{
  static const int InitBufferSize = 1024;
public:
  ByteBuffer() : Start(0), End(0),Limit(0) {}
  char *Get(int len)
    {
    char *buffer = &Internal[0];
    if (len > Limit - End)
      {
      // FIXME avoid integer overflow
      int neededSize = len + (End - Start);
      if (neededSize  <= Limit - buffer)
        {
        memmove(buffer, Start, End - Start);
        End = buffer + (End - Start);
        Start = buffer;
        }
      else
        {
        char *newBuf;
        int bufferSize = Limit - Start;
        if ( bufferSize == 0 )
          {
          bufferSize = InitBufferSize;
          }
        do
          {
          bufferSize *= 2;
          } while (bufferSize < neededSize);
        //newBuf = MALLOC(bufferSize);
        try
          {
          Internal.reserve(bufferSize);
          newBuf = &Internal[0];
          }
        catch(...)
          {
          //errorCode = XML_ERROR_NO_MEMORY;
          return 0;
          }
        Limit = newBuf + bufferSize;

        if (Start) 
          {
          memcpy(newBuf, Start, End - Start);
          }
        End = newBuf + (End - Start);
        Start = /*buffer =*/ newBuf;
        }
      }
    return End;
    }

private:
  typedef std::vector<char> CharVector;
  const char *Start;
        char *End;
  const char *Limit;
  CharVector Internal;
};

} // end namespace gdcm

#endif //__gdcmByteBuffer_h
