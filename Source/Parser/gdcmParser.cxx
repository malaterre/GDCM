#include "gdcmParser.h"

namespace gdcm
{

Parser::Parser()
{
}
Parser::~Parser()
{
}

void Parser::SetUserData(void *userData)
{
  UserData = userData;
}

void Parser::SetElementHandler(StartElementHandler start, EndElementHandler end)
{
  StartElement = start;
  EndElement = end;
}

void Parser::Parse(const char* buffer, size_t len, bool isFinal)
{
}

} // end namespace gdcm
