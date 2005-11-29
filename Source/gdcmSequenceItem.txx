#ifndef __gdcmSequenceItem_txx
#define __gdcmSequenceItem_txx

#include "gdcmSequenceItem.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
template<class DEType>
DICOMIStream& operator>>(DICOMIStream& _os, SequenceItem<DEType> &_val)
{
  const Tag item(0xfffe,0xe000);
  const Tag seqDel(0xfffe,0xe0dd); //[Sequence Delimitation Item]
  //if( !(_os.Read(_val.TagField))) return _os;
  //if( _val.TagField != item ) 
  //  {
  //  assert(0);
  //  return _os;
  //  }
  //assert(_val.TagField == item);
  _os.Read(_val.ItemLengthField);
  if( _val.ItemLengthField == 0xFFFFFFFF )
    {
    const Tag itemDel(0xfffe,0xe00d);
    DEType exde;
    DataElement &de = exde;
    while( _os >> de )
      {
      if(de.GetTag() == itemDel ) 
        {
        _val.TagField = de.GetTag();
        _os.Read(_val.ItemLengthField);
        //std::cerr << "End of SQ item: l=" << _val.ItemLengthField << std::endl;
        assert( _val.ItemLengthField == 0 
          || _val.ItemLengthField == 0xFFFFFFFF );
        break;
        }
      // else
      _os  >> exde;
      std::cout << "Debug SQ Item:\t" << exde << std::endl;
      }
    }
  else
    {
    std::cerr << "Debug Item: " << _val.ItemLengthField << std::endl;
    _val.ValueField.SetLength(_val.ItemLengthField);
    _os.Read(_val.ValueField);
    std::cout << "Debug \t" << _val << std::endl;
    }
  return _os;
}

//-----------------------------------------------------------------------------
template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const SequenceItem<DEType> &_val)
{
  (void)_val;
  assert( 0 );
  return _os;
}
} // end namespace gdcm

#endif //__gdcmSequenceItem_txx

