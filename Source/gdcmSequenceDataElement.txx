#ifndef __gdcmSequenceDataElement_txx
#define __gdcmSequenceDataElement_txx

#include "gdcmSequenceDataElement.h"
#include "gdcmSequenceItem.txx"

namespace gdcm
{
//-----------------------------------------------------------------------------
template<class DEType>
DICOMOStream& operator<<(DICOMOStream& _os, const SequenceDataElement<DEType> &_val)
{
  (void)_val;
  assert( 0 );
  return _os;
}
//-----------------------------------------------------------------------------
template<class DEType>
DICOMIStream& operator>>(DICOMIStream& _os, SequenceDataElement<DEType> &_val)
{
  const Tag itemStart(0xfffe,0xe000); // Item
  const Tag itemEnd(0xfffe,0xe00d);
  (void)_val;
  const Tag seqDel(0xfffe,0xe0dd); //[Sequence Delimitation Item]
  SequenceItem<DEType> si;
  assert( si.GetTag() == Tag(0,0) );
  DataElement &de = si;
  if( _val.SequenceLengthField == 0xFFFFFFFF)
    {
    while( _os >> de )
      {
      if(de.GetTag() == seqDel ) 
        {
        //_val.TagField = de.GetTag();
        uint32_t length;
        _os.Read(length);
        //std::cerr << "End of SQ: l=" << length << std::endl;
        assert( length == 0 || length == 0xFFFFFFFF ); // FIXME can a sequence
        // with unknow lenght finish with FFFFFFF ?
        break;
        }
      // else
      assert( de.GetTag() == itemStart );
      _os >> si;
      if( si.GetLength() == 0xFFFFFFFF )
        {
        assert( de.GetTag() == itemEnd );
        }
      }
    assert( si.GetTag() == seqDel );
    }
  else
    {
    // Defined length, just read the SQItem
    std::cerr << "Debug: " << _val.SequenceLengthField << std::endl;
    uint32_t seq_length = 0;
    while( seq_length != _val.SequenceLengthField )
      {
      _os >> de;
      if( de.GetTag() != itemStart )
        {
        std::cerr << "BUGGY header" << std::endl;
        _os.Seekg( _val.SequenceLengthField - 4, std::ios::cur );
        break;
        }
      _os >> si;
      // Sequence Length = Item Tag Length + Sequence Value Length
      seq_length += de.GetTag().GetLength();
      seq_length += si.GetLength();
      std::cerr << "Debug: seq_length="  << seq_length << std::endl;
      assert( seq_length <= _val.SequenceLengthField );
      }
    }
  return _os;
}
}
#endif //__gdcmSequenceDataElement_txx

