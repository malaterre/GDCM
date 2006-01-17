#ifndef __gdcmSequenceOfItems_txx
#define __gdcmSequenceOfItems_txx

#include "gdcmSequenceOfItems.h"
#include "gdcmItem.txx"

namespace gdcm
{
template<class DEType>
void SequenceOfItems<DEType>::AddItem(Item<DEType> const &item)
{
  Items.push_back(item);
}

//-----------------------------------------------------------------------------
template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const SequenceOfItems<DEType> &_val)
{
  return _val.Write(_os);
}

template<class DEType>
DICOMOStream& SequenceOfItems<DEType>::Write(DICOMOStream& _os) const
{
  assert( 0 );
  return _os;
}
//-----------------------------------------------------------------------------
//template<class DEType>
//DICOMIStream& operator>>(DICOMIStream &_os, SequenceOfItems<DEType> &_val)
//{
//  return _val.Read(_os);
//}


} // end namespace gdcm

#endif //__gdcmSequenceOfItems_txx

