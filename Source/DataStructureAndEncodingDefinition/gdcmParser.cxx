#include "gdcmParser.h"

namespace gdcm
{
  static const char *ErrorStrings[] = {
    "FATAL",
    NULL
  };
  Parser::Parser() {}
  Parser::~Parser() {}
  
  Parser::Status Parser::Parse(const char* buffer, size_t len, bool isFinal)
    {
    return Parser::StatusError;
    }
  void Parser::SetUserData(void *userData) {}
  void Parser::SetElementHandler(StartElementHandler start, EndElementHandler end) {}

  unsigned long Parser::GetCurrentOffset() const {
    return 0;
  }
  Parser::ErrorType Parser::GetErrorCode() const {
    return Parser::FatalError;
  }
  const char *Parser::ErrorString(ErrorType const &err) {
    return ErrorStrings[(int)err];
  }

} // end namespace gdcm

