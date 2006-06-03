#include "gdcmParser.h"
#include <vector>

namespace gdcm
{
  static const char *ErrorStrings[] = {
    "FATAL",
    NULL
  };
  
  bool Parser::Parse(const char* buffer, size_t len, bool isFinal)
    {
    if (len == 0)
      {
      if (!isFinal)
        {
        return true;
        }
      //PositionPtr = BufferPtr;
      //ErrorCode = processor(BufferPtr, ParseEndPtr = BufferEnd, 0);
      //if (ErrorCode == NoError)
      //  return true;
      //EventEndPtr = EventPtr;
      //ProcessorPtr = ErrorProcessor;
      return false;
      }
    else
      {
      memcpy(GetBuffer(len), buffer, len);
      return ParseBuffer(len, isFinal);
      }
    }

  class ByteBuffer
    {
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
        if ( Internal.empty() )
          bufferSize = InitBufferSize;
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
    static const size_t InitBufferSize = 1024;
    typedef std::vector<char> CharVector;
    const char *Start;
          char *End;
    const char *Limit;
    CharVector Internal;
    };

  char *Parser::GetBuffer(size_t len)
    {
    return Buffer;
    }

  bool Parser::ParseBuffer(size_t len, bool isFinal)
    {
    //const char *start = bufferPtr;
    //positionPtr = start;
    //bufferEnd += len;
    //parseEndByteIndex += len;
    //errorCode = processor(parser, start, parseEndPtr = bufferEnd,
    //  isFinal ? (const char **)0 : &bufferPtr);
    //if (errorCode == XML_ERROR_NONE)
    //  {
    //  if (!isFinal)
    //    XmlUpdatePosition(encoding, positionPtr, bufferPtr, &position);
    //  return 1;
    //  }
    //else
    //  {
    //  eventEndPtr = eventPtr;
    //  processor = errorProcessor;
    //  return 0;
    //  }
    return false;
    }


  void Parser::SetUserData(void *userData) {}
  void * Parser::GetUserData() const {
    return UserData;
  }
  void Parser::SetElementHandler(StartElementHandler start, EndElementHandler end) {}

  unsigned long Parser::GetCurrentByteIndex() const {
    return 0;
  }
  Parser::ErrorType Parser::GetErrorCode() const {
    return ErrorCode;
  }
  const char *Parser::GetErrorString(ErrorType const &err) {
    return ErrorStrings[(int)err];
  }

} // end namespace gdcm

