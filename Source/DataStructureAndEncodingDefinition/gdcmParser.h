
#ifndef __gdcmParser_h
#define __gdcmParser_h

#include "gdcmIStream.h"
#include "gdcmTag.h"

namespace gdcm
{
/**
 * \brief Parser ala XML_Parser from expat (SAD)
 *
 * Detailled description here
 * \note bla
 */
class GDCM_EXPORT Parser : public IStream
{
public:
  typedef enum {
    NoError,
    NoMemoryError,
    SyntaxError,
    NoElementsError,
    TagMismatchError,
    DuplicateAttributeError,
    JunkAfterDocElementError,
    UndefinedEntityError,
    UnexpectedStateError
  } ErrorType;

  typedef void (*StartElementHandler) (void *userData,
                                       const Tag &tag,
                                       const char *atts[]);
  typedef void (*EndElementHandler) (void *userData, const Tag &name);

  Parser();
  ~Parser();
  // If a parse error occurred, it returns 0. 
  // Otherwise it returns a non-zero value.
  bool Parse(const char* buffer, size_t len, bool isFinal);

  void SetUserData(void *userData);
  void SetElementHandler(StartElementHandler start, EndElementHandler end);

  unsigned long GetCurrentOffset() const;
  ErrorType GetErrorCode() const;
  static const char *ErrorString(ErrorType const &err);

protected:

  char *GetBuffer(size_t len);
  bool ParseBuffer(size_t len, bool isFinal);

private:
  void* UserData;
  char *Buffer;
  // First character to be parsed
  const char *BufferPtr;
        char *BufferEnd;
  const char *PositionPtr;
  const char *ParseEndPtr;

  const char *EventPtr;
  const char *EventEndPtr;

  StartElementHandler StartElement;
  EndElementHandler EndElement;

  ErrorType ErrorCode;
};

} // end namespace gdcm

#endif //__gdcmParser_h
