
#ifndef __gdcmLoader_h
#define __gdcmLoader_h

#include "gdcmDICOMIStream.h"

namespace gdcm
{
/**
 * \brief Actually Load data instead of just parsing
 *
 * Detailled description here
 * \note bla
 */
class GDCM_EXPORT Loader : public DICOMIStream
{
public:
  Loader() {}
  ~Loader() {};
  void Update();

protected:
private:
};

} // end namespace gdcm

#endif //__gdcmLoader_h
