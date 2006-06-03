
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

  //friend std::ostream& operator<<(std::ostream &os, const Value &val);

  virtual const VL& GetLength() const = 0;
  virtual void SetLength(VL const & l) = 0;

  virtual void Clear() = 0;
  virtual void Print(std::ostream &os) const = 0;

  virtual std::istream& Read(std::istream &is,
    SC::SwapCode const &sc = SC::LittleEndian) = 0;
  virtual std::ostream const & Write(std::ostream &os,
    SC::SwapCode const &sc = SC::LittleEndian) const = 0;
};

//inline std::ostream& operator<<(std::ostream &os, const Value &val)
//{
//  (void)val;
//  os << "Should not happen";
//  return os;
//}

} // end namespace gdcm

#endif //__gdcmValue_h

