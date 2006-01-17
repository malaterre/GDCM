#ifndef __gdcmItem_txx
#define __gdcmItem_txx

#include "gdcmItem.h"

namespace gdcm
{
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template<class DEType>
DICOMOStream& operator<<(DICOMOStream &_os, const Item<DEType> &_val)
{
  (void)_val;
  assert( 0 );
  return _os;
}
} // end namespace gdcm

#endif //__gdcmItem_txx

