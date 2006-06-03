
#ifndef __gdcmReader_h
#define __gdcmReader_h

#include "gdcmTag.h"

namespace gdcm
{
/**
 * \brief Reader ala DOM (Document Object Model)
 *
 * Detailled description here
 * \note bla
 */
class Document;
class GDCM_EXPORT Reader /*: public IStream*/
{
public:
  Reader();
  ~Reader();
  int Read(); // Execute()

  const Document *GetDocument() const {
    return DocumentP;
  }

protected:
private:
  Document* DocumentP;
};

} // end namespace gdcm

#endif //__gdcmReader_h
