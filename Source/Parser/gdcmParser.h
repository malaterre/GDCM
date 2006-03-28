
#ifndef __gdcmParser_h
#define __gdcmParser_h

#include "gdcmDICOMIStream.h"

namespace gdcm
{
/**
 * \brief Parser ala XML_Parser from expat
 *
 * Detailled description here
 * \note bla
 */
class GDCM_EXPORT Parser : public DICOMIStream
{
public:
  typedef void (*StartElementHandler) (void *userData,
                                       const Tag &tag,
                                       const void *atts[]);
  typedef void (*EndElementHandler) (void *userData);

  Parser();
  ~Parser();
  void Parse(const char* buffer, size_t len, bool isFinal);

  void SetUserData(void *userData);
  void SetElementHandler(StartElementHandler start, EndElementHandler end);

protected:
private:
  void* UserData;
  StartElementHandler StartElement;
  EndElementHandler EndElement;
};

} // end namespace gdcm

#endif //__gdcmParser_h
