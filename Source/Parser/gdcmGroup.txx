
#ifndef __gdcmGroup_txx
#define __gdcmGroup_txx

#include "gdcmGroup.h"
#include "gdcmDataElement.h"

namespace gdcm
{
//template Group<ExplicitDataElement>;
//template Group<ImplicitDataElement>;

template<class DEType>
uint32_t Group<DEType>::GetLength() const
{
  uint32_t length = 0;
  for(typename ElementsVector::const_iterator it = Tags.begin();
    it != Tags.end(); ++it)
    {
    // Do not count Group Length Element
    if( it->GetTag().GetElement() != 0x0000 )
      {
      // length is length of each DataElement
      length += it->GetLength();
      }
    }
  return length;
}


template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const Group<DEType> &_val)
{
  assert(0 && "TODO" );
  (void)_val;
  return _os;
}

} // end namespace gdcm

#endif //__gdcmGroup_txx
