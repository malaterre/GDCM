#include "gdcmType.h"
#include "gdcmDICOMIStream.h"
#include "gdcmVR.h"
#include "gdcmByteSwap.txx"
#include "gdcmDataElement.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmTS.h"
#include "gdcmSequenceOfItems.txx"
#include "gdcmItem.txx"
#include "gdcmGroup.txx"
#include "gdcmTrace.h"

namespace gdcm
{
DICOMIStream::DICOMIStream()
{
  NegociatedTS = Unknown; 
  ReadForPrinting = false;
}

DICOMIStream::~DICOMIStream()
{
}

IStream &DICOMIStream::Read(Tag &t)
  throw (std::exception)
{
  assert( sizeof(t) == 4 );
  if( !IStream::Read((char*)(&t.ElementTag.tag), 4) ) return *this;
  //assert(!(t.GetGroup()%2));
  ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem(t.ElementTag.tags,
    SwapCode, 2);
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  if( t == Tag(0,0) )
    {
    throw std::exception( );
    }
#endif
  assert( t != Tag(0,0) ); // FIXME
  return *this;
}

IStream &DICOMIStream::Read(VR::VRType &vr)
{
  char vr_str[3];
  IStream::Read(vr_str, 2);
  vr_str[2] = '\0';
  vr = VR::GetVRType(vr_str);
  assert( vr != VR::VR_END );
  return *this;
}

IStream &DICOMIStream::Read(uint16_t &vl)
{
  char vl_str[2];
  IStream::Read(vl_str,2);
  ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem((uint16_t*)(&vl_str),
    SwapCode, 1);
  memcpy(&vl, vl_str, 2);
  return *this;
}

IStream &DICOMIStream::Read(uint32_t &vl)
{
  char vl_str[4];
  IStream::Read(vl_str,4);
  ByteSwap<uint32_t>::SwapRangeFromSwapCodeIntoSystem((uint32_t*)(&vl_str),
    SwapCode, 1);
  memcpy(&vl, vl_str, 4);
  return *this;
}

IStream &DICOMIStream::Read(Value &v)
{
  uint32_t length = v.GetLength();
  assert( length != 0xFFFFFFFF );
  IStream::Read(v.Internal, length);
//  ByteSwap<short>::SwapRangeFromSwapCodeIntoSystem((short*)(v.Internal),
//    SwapCode, length);
  return *this;
}
//-----------------------------------------------------------------------------
//inline DICOMIStream& operator>>(DICOMIStream &_os, DataElement &_val)
IStream& DICOMIStream::Read(DataElement& da)
{
  // Read Tag
  assert( !eof() ); // FIXME
  if( !Read(da.TagField) ) return *this;
  return *this;
}

template<class DEType>
IStream& DICOMIStream::Read(SequenceOfItems<DEType>& sq)
{
  const Tag itemStart(0xfffe,0xe000);   // [Item]
  const Tag itemEnd(0xfffe,0xe00d);     // [Item Delimitation Item]
  const Tag seqEnd(0xfffe,0xe0dd);      // [Sequence Delimitation Item]
  DataElement de; // = si;
  bool isBroken = false;
  if( sq.SequenceLengthField == 0xFFFFFFFF)
    {
    while( Read(de) ) // Read Tag only
      {
      if(de.GetTag() == seqEnd) 
        {
        uint32_t length;
        Read(length);
        // 7.5.2 Delimitation of the Sequence of Items
        // ...
        // b) Undefined Length: The Data Element Length Field shall contain a Value FFFFFFFFH to
        // indicate an Undefined Sequence length. It shall be used in conjunction with a Sequence
        // Delimitation Item. A Sequence Delimitation Item shall be included after the last Item
        // in the sequence. Its Item Tag shall be (FFFE,E0DD) with an Item Length of 00000000H. 
        // No Value shall be present.
        if( length != 0 ) //*is* always true (hope so!)
          {
          gdcmWarningMacro( "Wrong length for Sequence Delimitation Item: " << length ); 
          abort();
          }
        // Looks like some pixel data have instead: == 0xFFFFFFFF -> SIEMENS-MR-RGB-16Bits.dcm
        break;
        }
      // else
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
      if( de.GetTag() != itemStart )
        {
        // gdcm-JPEG-LossLess3a.dcm
        std::streampos pos = Tellg();
        Seekg( 0, std::ios::end );
        std::streampos end = Tellg();
        gdcmWarningMacro( "Broken file: " << (long)(end-pos) 
          << " bytes were skipped at the end of file" );
        isBroken = true;
        break;
        }
#endif
      Item<DEType> si; // = SequenceItemField;
      assert( si.GetTag() == de.GetTag() ); // Should be an Item Start
      assert( si.GetTag() == itemStart );
      Read(si);
      sq.Items.push_back( si );
      }
    if( !isBroken )
      {
      assert( de.GetTag() == seqEnd );
      }
    }
  else
    {
    // Defined length, just read the SQItem
    gdcmDebugMacro( "SequenceLengthField=" << sq.SequenceLengthField );
    uint32_t seq_length = 0;
    while( seq_length != sq.SequenceLengthField )
      {
      Read(de);
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
      if( de.GetTag() != itemStart )
        {
        gdcmErrorMacro( "BUGGY header: Does not start with Item Start. Skipping sequence ("
          << sq.SequenceLengthField - 4 << ") bytes");
        Seekg( sq.SequenceLengthField - 4, std::ios::cur );
        break;
        }
#endif
      Item<DEType> si; // = SequenceItemField;
      Read(si);
      sq.Items.push_back( si );
      // Sequence Length = Item Tag Length + Sequence Value Length
      seq_length += de.GetTag().GetLength() + 4;
      seq_length += si.GetLength();
      gdcmDebugMacro( "seq_length="  << seq_length );
      assert( seq_length <= sq.SequenceLengthField );
      }
    }
  return *this;
}

IStream& DICOMIStream::Read(ImplicitDataElement& ida)
{
  // See PS 3.5, 7.1.3 Data Element Structure With Implicit VR
  // Read Tag
  //if( !_os.Read(TagField) ) return _os;
  //static Dict d;
  //const DictEntry &de = d.GetDictEntry(TagField);
  // Read Value Length
  if( !(Read(ida.ValueLengthField)) ) return *this;
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  // THE WORST BUG EVER. From GE Workstartion
  if(ida.ValueLengthField == 13 )
    {
    // Historically gdcm did not enforce proper length
    // thus Theralys started writting illegal DICOM images:
    const Tag theralys1(0x0008,0x0070);
    const Tag theralys2(0x0008,0x0080);
    if( ida.GetTag() != theralys1
     && ida.GetTag() != theralys2 )
      {
      gdcmWarningMacro( "BUGGY HEADER (GE, 13)" );
      ida.ValueLengthField = 10;
      }
    }
#endif
  if(ida.ValueLengthField == 0xFFFFFFFF)
    {
    //assert( de.GetVR() == VR::SQ );
    const Tag sdi(0xfffe,0xe0dd); // Sequence Delimitation Item
    SequenceOfItems<ImplicitDataElement> si(ida.ValueLengthField);
    Read(si);
    gdcmDebugMacro( "SI: " << si );
    }
  else
    {
    // We have the length we should be able to read the value
    bool needReading = true;
    if( ReadForPrinting )
      {
      needReading = ida.ValueLengthField < 0xfff;
      }
    if( needReading )
      {
      ida.ValueField.SetLength(ida.ValueLengthField); // perform realloc
      Read(ida.ValueField);
      }
    else
      {
      ida.ValueField.SetLength(0); // perform realloc
      Seekg(ida.ValueLengthField, std::ios::cur);
      }
    }
  return *this;
}

IStream& DICOMIStream::Read(ExplicitDataElement& xda)
{
  // See PS 3.5, Date Element Structure With Explicit VR
  // Read Tag
  //if( !_os.Read(TagField) ) return _os;
  //static Dict d;
  //const DictEntry &de = d.GetDictEntry(TagField);
  // Read VR
  if( !(Read(xda.VRField)) ) return *this;
//  if( !(de.GetVR() & VRField) && de.GetVR() != VR::INVALID )
//    {
//    std::cerr << "BUGGY VR for Tag: " << TagField << " : " << VR::GetVRString(VRField)
//      << " should be: " << VR::GetVRString(de.GetVR()) << std::endl;
//    }
  if( xda.VRField == VR::OB
   || xda.VRField == VR::OW
   || xda.VRField == VR::OF
   || xda.VRField == VR::SQ
   || xda.VRField == VR::UN )
    {
    uint16_t check;
    Read(check);
    assert( check == 0x0 );
    // Read Value Length (32bits)
    Read(xda.ValueLengthField);
    }
  else if( xda.VRField == VR::UT )
    {
    uint16_t check;
    Read(check);
    assert( check == 0x0 );
    // Read Value Length (32bits)
    Read(xda.ValueLengthField);
    assert( xda.ValueLengthField != 0xFFFFFFFF );
    }
  else
    {
    // Two steps since ValueLengthField is 32 bits, we need to declare a 16bits int first
    uint16_t vl;
    // Read Value Length (16bits)
    Read(vl);
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
    if( xda.VRField == VR::UL )
      {
      if(vl == 6)
        {
        gdcmWarningMacro( "BUGGY HEADER: vl=6 should be 4" );
        vl = 4;
        }
#ifndef NDEBUG
      if( vl == 1024 )
        {
        abort(); // If your code reach here there is probably a bug in your image
        // It happen for instance in the case of DICOM wrongly declared as BigEndian
        }
#endif
      }
#endif // GDCM_SUPPORT_BROKEN_IMPLEMENTATION
//#define BIG_HACK2
#ifdef BIG_HACK // Trying to read NM_FromJulius_Caesar.dcm
    const Tag bug(0x0054,0x0200);
    if( xda.TagField == bug )
      {
      vl = 20;
      }
#endif
#ifdef BIG_HACK2 // Trying to read Siemens-leonardo-bugged.dcm
      if(vl == 2573) // 0xa0d
        {
        vl = 11; // 0xb
        }
      if(vl == 149)
        {
        vl = 240;
        }
      const Tag bug(0x0019,0x1313);
      if(xda.TagField == bug)
        {
        assert( vl == 6 );
        vl = 7;
        }
#endif
    xda.ValueLengthField = vl;
    }
  // Read the Value
  if( xda.VRField == VR::SQ )
    {
    // Check wether or not this is an undefined length sequence
    SequenceOfItems<ExplicitDataElement> si( xda.ValueLengthField  );
    Read(si);
    }
  else if( xda.ValueLengthField == 0xFFFFFFFF )
    {
    // Ok this is Pixel Data fragmented...
    const Tag pixelData(0x7fe0,0x0010);
    assert( xda.VRField == VR::OB 
         || xda.VRField == VR::OW );
    assert( xda.TagField == pixelData );
    SequenceOfItems<ExplicitDataElement> si;
    Read(si);
    }
  else
    {
    assert( xda.ValueLengthField != 0xFFFF ); // ??
    // We have the length we should be able to read the value
//    if( xda.ValueLengthField < 0xfff )
      {
      if (xda.ValueLengthField%2)
        {
        gdcmWarningMacro( "BUGGY HEADER: Your dicom contain odd length value field." );
        }
      xda.ValueField.SetLength(xda.ValueLengthField); // perform realloc
      Read(xda.ValueField);
      }
//    else
//      {
//      gdcmWarningMacro( "Seeking long field: " << xda.GetTag() << " l= " 
//        << xda.ValueLengthField );
//#ifdef BIG_HACK2
//      xda.ValueField.SetLength(xda.ValueLengthField);
//      Read(xda.ValueField);
//      std::ofstream f("/tmp/pixel.raw");
//      f.write(ValueField.GetPointer(), ValueField.GetLength());
//      f.close();
//      Seekg(0, std::ios::end); // FIXME garbage at the end...
//#else
//      xda.ValueField.SetLength(0); // perform realloc
//      Seekg(xda.ValueLengthField, std::ios::cur);
//#endif
//      }
    }

  return *this;
}

template<class DEType>
IStream& DICOMIStream::Read(Group<DEType> &_val)
{
  DEType de;
  DataElement &de_tag = de;
  bool initialized = false;
  while( !eof() && Read(de_tag) )
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
        Seekg( -4 /*de_tag.GetLength()*/, std::ios::cur);
        break;
        }
      }
    if( !(Read(de)) )
      {
      assert( 0 && "Impossible" );
      }
    _val.AddDataElement(de);
    }

  return *this;
}

template<class DEType>
DICOMIStream& DICOMIStream::Read(Item<DEType> &_val)
{
  const Tag item(0xfffe,0xe000);
  //if( !(Read(_val.TagField))) return *this;
  assert(_val.TagField == item); // KEEPME
  Read(_val.ItemLengthField);
  if( _val.ItemLengthField == 0xFFFFFFFF )
    {
    const Tag itemDel(0xfffe,0xe00d);
    DEType exde;
    DataElement &de = exde;
    while( Read(de) )
      {
      if(de.GetTag() == itemDel ) 
        {
        _val.TagField = de.GetTag();
        Read(_val.ItemLengthField);
        gdcmDebugMacro( "End of SQ item: l=" << _val.ItemLengthField );
        if( _val.ItemLengthField != 0 )
          {
          gdcmWarningMacro( "BUGGY HEADER: Length should be 0, instead is: "
            << _val.ItemLengthField );
          }
        break;
        }
      // else
      Read(exde);
      assert(exde.GetTag() == de.GetTag());
      _val.AddDataElement(exde);
      gdcmDebugMacro( "SQ Item:\t" << exde );
      }
    }
  else
    {
    gdcmDebugMacro( "Item Length: " << _val.ItemLengthField );
    _val.ValueField.SetLength(_val.ItemLengthField);
    Read(_val.ValueField);
    gdcmDebugMacro( "Val: \t" << _val );
    }
  return *this;
}

void DICOMIStream::Initialize()
{
  //FindNegociatedTS();
  ReadNonStandardDataElements();
  gdcmDebugMacro( "NegociatedTS: " << NegociatedTS );
  gdcmDebugMacro( "SwapCode: " << SwapCode );
  assert( NegociatedTS != Unknown );
  //assert( SwapCode != SC::Unknown );
}

/// \brief tells us if "DICM" is found as position 128 
///        (i.e. the file is a 'true dicom' one)
bool DICOMIStream::ReadDICM()
{
  bool r = false;
  char dicm[128+4];
  IStream::Read(dicm, 128+4);
  if( dicm[124+4] == 'D'
       && dicm[125+4] == 'I'
       && dicm[126+4] == 'C'
       && dicm[127+4] == 'M')
    {
    r = true; // Sometime not everything is set to zero: D_CLUNIE_VL4_RLE.dcm
    // It's not clearly specify that the 128 first bytes *must* be set to Zero
    // But usually it is report only when compiled in Debug mode

    // Well... It's clearly specified the 128 first bytes are reserved 
    //         for future (?) use.    
#ifndef NDEBUG
    int i;
    for(i=0; i<128; ++i)
      if(dicm[i] != '\0' )
        {
        gdcmDebugMacro( "Garbage in the DICOM Header" );
        break;
        }
    if( i == 128 )
      {
      gdcmDebugMacro( "Real clean HEADER" );
      }
#endif
    }

  return r;
}

// Once our heuristic found
template<class DEType>
void CheckNegociatedTS(gdcm::DICOMIStream &is)
{
  DEType de;
  DataElement &de_tag = de;
  while( is.Read(de_tag) )
    {
    is.Read(de);
    gdcmDebugMacro( de );
    }
}


void DICOMIStream::ReadNonStandardDataElements()
{
  // Standard Data Elements have an even Group Number that is not
  // -(0000,eeee)
  // -(0002,eeee)
  // -(0004,eeee)
  // -(0006,eeee)
  // Ok we are after any DICOM V3 header, starting the first element
  FindNegociatedTS();
  if( NegociatedTS == Explicit )
    {
    // So far we only found the potential TS
    ExplicitDataElement de;
    DataElement &de_tag = de;
    const gdcm::Tag t(0x0002,0x0010);
    gdcm::TS::TSType ts = TS::TS_END;
    while( Read(de_tag) )
      {
      gdcmDebugMacro( "Tag: " << de_tag.GetTag() );
      assert( de_tag.GetTag().GetGroup() <= 0x0010
           || de_tag.GetTag().GetGroup() == 0x0800 ); // Byte Swap problem

      if( de_tag.GetTag().GetGroup() <= 0x0002 )
        {
        Read(de);
        gdcmDebugMacro( de );
        if( de_tag.GetTag() == t )
          {
          gdcmDebugMacro( "TS=" << de.GetValue().GetPointer() );
          ts = gdcm::TS::GetTSType( de.GetValue().GetPointer() );
          assert( ts != TS::TS_END );
          bool isDataSetEncoded = TS::IsDataSetEncoded( ts );
          if( isDataSetEncoded )
            {
            // FIXME gdcm2 does not deal with deflate DataSet
            Seekg(0, std::ios::end);
            }
          }
        }
      else
        {
        // Ok seek back, since we only read de_tag, we need to seek back 4 bytes:
        assert( de_tag.GetLength() == 4 );
        Seekg(-4, std::ios::cur);
        bool isImplicit = TS::IsImplicit( ts );
        if( isImplicit )
          {
          NegociatedTS = DICOMIStream::Implicit;
          }
        bool isBigEndian = TS::IsBigEndian( ts );
        if( isBigEndian )
          {
          SwapCode = SC::BigEndian;
          }
        break;
        }
      }
    }
}

/// \brief Sets the SwapCode (BigEndian, ...) and NegociatedTS (implVR, explVR)
void DICOMIStream::FindNegociatedTS()
{
  // Stream is passed the DICM header
  if( !ReadDICM() )
    {
    gdcmDebugMacro( "Not a DICOM V3 file" );
    IStream::Seekg(0, std::ios::beg);
    }
  
  // The idea being we try multiple heuristics until we are happy ... 
  // and then keep our finger cross 
  Tag t;
  Read(t);
  assert( t.GetGroup() < 0x6000 ); // Magic number
  /// \TODO fixme breaks on : gdcmData/LIBIDO-16-ACR_NEMA-Volume.dcm
  //assert( t.GetGroup() < 0x0090 ); //Cannot start whith a group > 0008!   
  if( ! (t.GetGroup() % 2) )
    {
    // Purposely not Re-use ReadVR since we can read VR_END
    char vr_str[3];
    IStream::Read(vr_str, 2);
    vr_str[2] = '\0';
    VR::VRType vr = VR::GetVRType(vr_str);
    if( vr != VR::VR_END )
      {
      assert( vr == VR::UL
           || vr == VR::OB
           || vr == VR::UI
           /*|| vr == VR::CS*/ );
      NegociatedTS = Explicit;
      }
    else
      {
      assert( !(VR::IsSwap(vr_str)));
      IStream::Seekg(-2, std::ios::cur); // Seek back
      if( t.GetElement() == 0x0000 )
        {
        uint32_t group_length;
        assert( SwapCode == SC::Unknown );
        Read(group_length);
        switch(group_length)
          {
        case 0x00040000 :
          SwapCode = SC::BadLittleEndian; // 3412
          break;
        case 0x04000000 :
          SwapCode = SC::BigEndian;       // 4321
          break;  
        case 0x00000400 :
          SwapCode = SC::BadBigEndian;    // 2143
          break;
        case 0x00000004 :
          SwapCode = SC::LittleEndian;    // 1234
          break;
        default:
          abort();
          }
        Seekg(0, std::ios::beg);
        gdcmDebugMacro( "T=" << Tellg() );
        if(!ReadDICM())
          IStream::Seekg(0, std::ios::beg);
        gdcmDebugMacro( "T=" << Tellg() );
        Read(t);
        }
      NegociatedTS = Implicit;
      }
    }
  else
    {
    gdcmWarningMacro( "Start with private element" );
    char vr_str[3];
    IStream::Read(vr_str, 2);
    vr_str[2] = '\0';
    VR::VRType vr = VR::GetVRType(vr_str);
    if( vr != VR::VR_END )
      NegociatedTS = Explicit;
    else
      {
      assert( !(VR::IsSwap(vr_str)));
      NegociatedTS = Implicit;
      }
    }

  // When we return we moved back the stream after the DICM header
  IStream::Seekg(0, std::ios::beg);
  if( !ReadDICM() )
    {
    IStream::Seekg(0, std::ios::beg);
    }
}
  

}

