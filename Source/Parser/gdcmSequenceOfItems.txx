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
template<class DEType>
DICOMIStream& operator>>(DICOMIStream &_os, SequenceOfItems<DEType> &_val)
{
  return _val.Read(_os);
}

template<class DEType>
DICOMIStream& SequenceOfItems<DEType>::Read(DICOMIStream& _os)
{
  const Tag itemStart(0xfffe,0xe000);   // [Item]
  const Tag itemEnd(0xfffe,0xe00d);     // [Item Delimitation Item]
  const Tag seqEnd(0xfffe,0xe0dd);      // [Sequence Delimitation Item]
  DataElement de; // = si;
  bool isBroken = false;
  if( SequenceLengthField == 0xFFFFFFFF)
    {
    while( _os >> de ) // Read Tag only
      {
      if(de.GetTag() == seqEnd) 
        {
        uint32_t length;
        _os.Read(length);
        // 7.5.2 Delimitation of the Sequence of Items
        // ...
        // b) Undefined Length: The Data Element Length Field shall contain a Value FFFFFFFFH to
        // indicate an Undefined Sequence length. It shall be used in conjunction with a Sequence
        // Delimitation Item. A Sequence Delimitation Item shall be included after the last Item
        // in the sequence. Its Item Tag shall be (FFFE,E0DD) with an Item Length of 00000000H. 
        // No Value shall be present.
        if( length != 0 ) //*is* always true (hope so!)
          {
          std::cerr << "Wrong length for Sequence Delimitation Item: " << length; 
          abort();
          }
        // Looks like some pixel data have instead: == 0xFFFFFFFF -> SIEMENS-MR-RGB-16Bits.dcm
        break;
        }
      // else
      if( de.GetTag() != itemStart )
        {
        // gdcm-JPEG-LossLess3a.dcm
        std::streampos pos = _os.Tellg();
        _os.Seekg( 0, std::ios::end );
        std::streampos end = _os.Tellg();
        std::cerr << "Broken file: " << (long)(end-pos) 
          << " bytes were skipped at the end of file" << std::endl;
        isBroken = true;
        break;
        }
      Item<DEType> si; // = SequenceItemField;
      assert( si.GetTag() == de.GetTag() ); // Should be an Item Start
      assert( si.GetTag() == itemStart );
      _os >> si;
      Items.push_back( si );
      }
    if( !isBroken )
      {
      assert( de.GetTag() == seqEnd );
      }
    }
  else
    {
    // Defined length, just read the SQItem
    std::cerr << "Debug: SequenceLengthField=" 
              << SequenceLengthField << std::endl;
    uint32_t seq_length = 0;
    while( seq_length != SequenceLengthField )
      {
      _os >> de;
      if( de.GetTag() != itemStart )
        {
        std::cerr << "BUGGY header" << std::endl;
        _os.Seekg( SequenceLengthField - 4, std::ios::cur );
        break;
        }
      Item<DEType> si; // = SequenceItemField;
      _os >> si;
      Items.push_back( si );
      // Sequence Length = Item Tag Length + Sequence Value Length
      seq_length += de.GetTag().GetLength() + 4;
      seq_length += si.GetLength();
      std::cerr << "Debug: seq_length="  << seq_length << std::endl;
      assert( seq_length <= SequenceLengthField );
      }
    }
  return _os;
}

} // end namespace gdcm

#endif //__gdcmSequenceOfItems_txx

