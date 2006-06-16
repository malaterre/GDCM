
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
  Value():ReferenceCount(1) { }
  virtual ~Value() { 
    --ReferenceCount;
    if( ReferenceCount > 1 )
      {
      abort();
      }
  }

  friend std::ostream& operator<<(std::ostream &os, const Value &val);

  virtual const VL & GetLength() const = 0;
  virtual void SetLength(VL const & l) = 0;

  virtual void Clear() = 0;

  virtual IStream& Read(IStream &is) = 0;
  virtual OStream const & Write(OStream &os) const = 0;

  virtual void Print(std::ostream &os) const = 0;

  void Register() { ++ReferenceCount; }
  void UnRegister() { --ReferenceCount; }

private:
  int ReferenceCount;
};

//----------------------------------------------------------------------------
// function do not carry vtable. Thus define in the base class the operator
// and use the member function ->Print() to call the appropriate function
// NOTE: All subclass of Value needs to implement the Print function
inline std::ostream& operator<<(std::ostream &os, const Value &val)
{
  val.Print(os);
  return os;
}

} // end namespace gdcm

#endif //__gdcmValue_h

