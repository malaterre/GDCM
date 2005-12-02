#ifndef __gdcmItem_txx
#define __gdcmItem_txx

#include "gdcmItem.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
template<class DEType>
DICOMIStream& operator>>(DICOMIStream &_os, Item<DEType> &_val)
{
  const Tag item(0xfffe,0xe000);
  //if( !(_os.Read(_val.TagField))) return _os;
  assert(_val.TagField == item); // KEEPME
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
        assert( _val.ItemLengthField == 0 );
        break;
        }
      // else
      _os >> exde;
      assert(exde.GetTag() == de.GetTag());
      _val.AddDataElement(exde);
      //std::cout << "Debug SQ Item:\t" << exde << std::endl;
      }
    }
  else
    {
    std::cout << "Debug Item: " << _val.ItemLengthField << std::endl;
    _val.ValueField.SetLength(_val.ItemLengthField);
    _os.Read(_val.ValueField);
    //std::cout << "Debug \t" << _val << std::endl;
    }
  return _os;
}

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

