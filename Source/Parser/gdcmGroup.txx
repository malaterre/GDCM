
#ifndef __gdcmGroup_txx
#define __gdcmGroup_txx

#include "gdcmGroup.h"
#include "gdcmDataElement.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

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
    if( it->GetTag().GetElement() != 0x0000 )
      {
      // length is length of each DataElement
      length += it->GetLength();
      }
    }
  return length;
}

template<class DEType>
DICOMIStream& operator>>(DICOMIStream& _os, Group<DEType> &_val)
{
  DEType de;
  DataElement &de_tag = de;
  bool initialized = false;
  while( !_os.eof() && _os >> de_tag )
    {
    if(!initialized)
      {
      _val.SetNumber(de_tag.GetTag().GetGroup());
      initialized = true;
      }
    else
      {
      if( de_tag.GetTag().GetGroup() != _val.Number )
        {
        // Seek back
        _os.Seekg( -4 /*de_tag.GetLength()*/, std::ios::cur);
        break;
        }
      }
    if( !(_os >> de) )
      {
      assert( 0 && "Impossible" );
      }
    _val.AddDataElement(de);
    }

  return _os;
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
