
#ifndef __gdcmValue_h
#define __gdcmValue_h

#include "gdcmTypes.h"
#include "gdcmSwapCode.h"
#include "gdcmVL.h"

#include <fstream>

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
  virtual ~Value() { }

  virtual const VL& GetLength() const = 0;
  virtual void SetLength(VL const & l) = 0;

  virtual void Clear() = 0;

  virtual void Read(std::istream &is,
    SC::SwapCode const &sc = SC::LittleEndian) = 0;
  virtual void Write(std::ostream &os,
    SC::SwapCode const &sc = SC::LittleEndian) const = 0;
};

} // end namespace gdcm

#endif //__gdcmValue_h

