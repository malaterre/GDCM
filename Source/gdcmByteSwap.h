#ifndef __gdcmByteSwap_h
#define __gdcmByteSwap_h

#include "gdcmType.h"

namespace gdcm
{

/** \class ByteSwap
 * \brief Perform machine dependent byte swaping (Little Endian,
 * Big Endian, Bad Little Endian, Bad Big Endian).
 */

template<class T>
class GDCM_EXPORT ByteSwap
{
public:
  /** Query the machine Endian-ness. */
  static bool SystemIsBigEndian ();
  static bool SystemIsLittleEndian ();

  static void SwapFromSwapCodeIntoSystem(T &p, SC::SwapCodeType sc);
  static void SwapRangeFromSwapCodeIntoSystem(T *p, SC::SwapCodeType sc, unsigned int num);
  
protected:
  ByteSwap() {}
  ~ByteSwap() {}

private:
  
};

} // end namespace gdcm

#endif
