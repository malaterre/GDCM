
#ifndef __gdcmValue_h
#define __gdcmValue_h

#include "gdcmTypes.h"

namespace gdcm
{
/**
 * \brief Class to represent the value of a Data Element.
 * \note
 * VALUE: A component of a Value Field. A Value Field may consist of one
 * or more of these components.
 */
class GDCM_EXPORT Value
{
public:
  Value() { }
  ~Value() { }

  virtual uint32_t GetLength() const = 0;
  virtual void SetLength(uint32_t l) = 0;

  virtual void Clear() = 0;

  virtual void Read(std::istream &is) = 0;
  virtual void Write(std::ostream &os) const = 0;
};

} // end namespace gdcm

#endif //__gdcmValue_h

