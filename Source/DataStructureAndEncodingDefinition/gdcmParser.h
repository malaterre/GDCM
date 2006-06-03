
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
    StatusError
  } Status;
  typedef enum {
    FatalError
  } ErrorType;

  typedef void (*StartElementHandler) (void *userData,
                                       const Tag &tag,
                                       const char *atts[]);
  typedef void (*EndElementHandler) (void *userData, const Tag &name);

  Parser();
  ~Parser();
  Status Parse(const char* buffer, size_t len, bool isFinal);

  void SetUserData(void *userData);
  void SetElementHandler(StartElementHandler start, EndElementHandler end);

  unsigned long GetCurrentOffset() const;
  ErrorType GetErrorCode() const;
  static const char *ErrorString(ErrorType const &err);

protected:
private:
  void* UserData;
  StartElementHandler StartElement;
  EndElementHandler EndElement;
};

} // end namespace gdcm

#endif //__gdcmParser_h
