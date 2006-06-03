#include "gdcmParser.h"

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


  char *Parser::GetBuffer(int len)
    {
    return Buffer.Get(len);
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

