#include "gdcmParser.h"

namespace gdcm
{
  static const char *ErrorStrings[] = {
    "FATAL",
    NULL
  };
  Parser::Parser() {}
  Parser::~Parser() {}
  
  PARSER_STATUS Parser::Parse(const char* buffer, size_t len, bool isFinal)
    {
    return STATUS_ERROR;
    }
  void Parser::SetUserData(void *userData) {}
  void Parser::SetElementHandler(StartElementHandler start, EndElementHandler end) {}

  unsigned long Parser::GetCurrentOffset() {
    return 0;
  }
  PARSER_ERROR_TYPE Parser::GetErrorCode() {
    return FATAL;
  }
  const char *Parser::ErrorString(PARSER_ERROR_TYPE err) {
    return ErrorStrings[(int)err];
  }

} // end namespace gdcm
            
