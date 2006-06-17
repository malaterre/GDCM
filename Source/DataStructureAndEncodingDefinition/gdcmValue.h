
#ifndef __gdcmValue_h
#define __gdcmValue_h

#include "gdcmObject.h"
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
class GDCM_EXPORT Value : public Object
{
public:
  Value() {}
  ~Value() {}

  virtual const VL & GetLength() const = 0;
  virtual void SetLength(VL const & l) = 0;

  virtual void Clear() = 0;

  virtual IStream& Read(IStream &is) = 0;
  virtual OStream const & Write(OStream &os) const = 0;

  //virtual void Print(std::ostream &os) const = 0;

};


} // end namespace gdcm

#endif //__gdcmValue_h

