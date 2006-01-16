#include "gdcmExplicitDataElement.h"
#include "gdcmSequenceOfItems.txx"
#include "gdcmDict.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
DICOMOStream& operator<<(DICOMOStream &_os, const ExplicitDataElement &_val)
{
  return _val.Write(_os);
}

DICOMOStream& ExplicitDataElement::Write(DICOMOStream &_os) const
{
  //const DataElement &de = 
  //_os << de;
  _os.Write(VRField);
  // See PS 3.5, Date Element Structure With Explicit VR
  if( VRField == VR::OB
   || VRField == VR::OW
   || VRField == VR::OF
   || VRField == VR::SQ
   || VRField == VR::UN )
    {
    uint16_t check = 0x0;
    _os.Write(check);
    // Write Value Length (32bits)
    _os.Write(ValueLengthField);
    }
  else if( VRField == VR::UT )
    {
    uint16_t check = 0x0;
    _os.Write(check);
    // Write Value Length (32bits)
    assert( ValueLengthField != 0xFFFFFFFF );
    _os.Write(ValueLengthField);
    }
  else
    {
    uint16_t vl = ValueLengthField;
    // Write Value Length (16bits)
    _os.Write(vl);
    }
  // We have the length we should be able to write the value
  _os.Write(ValueField);
  return _os;
}

//-----------------------------------------------------------------------------
DICOMIStream& operator>>(DICOMIStream &_os, ExplicitDataElement &_val)
{
  return _val.Read(_os);
}

DICOMIStream& ExplicitDataElement::Read(DICOMIStream &_os)
{
  // See PS 3.5, Date Element Structure With Explicit VR
  // Read Tag
  //if( !_os.Read(TagField) ) return _os;
  //static Dict d;
  //const DictEntry &de = d.GetDictEntry(TagField);
  // Read VR
  if( !(_os.Read(VRField)) ) return _os;
//  if( !(de.GetVR() & VRField) && de.GetVR() != VR::INVALID )
//    {
//    std::cerr << "BUGGY VR for Tag: " << TagField << " : " << VR::GetVRString(VRField)
//      << " should be: " << VR::GetVRString(de.GetVR()) << std::endl;
//    }
  if( VRField == VR::OB
   || VRField == VR::OW
   || VRField == VR::OF
   || VRField == VR::SQ
   || VRField == VR::UN )
    {
    uint16_t check;
    _os.Read(check);
    assert( check == 0x0 );
    // Read Value Length (32bits)
    _os.Read(ValueLengthField);
    }
  else if( VRField == VR::UT )
    {
    uint16_t check;
    _os.Read(check);
    assert( check == 0x0 );
    // Read Value Length (32bits)
    _os.Read(ValueLengthField);
    assert( ValueLengthField != 0xFFFFFFFF );
    }
  else
    {
    // Two steps since ValueLengthField is 32 bits, we need to declare a 16bits int first
    uint16_t vl;
    // Read Value Length (16bits)
    _os.Read(vl);
    if( VRField == VR::UL )
      {
      if(vl == 6)
        {
        std::cerr << "BUGGY HEADER: vl=6 should be 4" << std::endl;
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
//#define BIG_HACK2
#ifdef BIG_HACK // Trying to read NM_FromJulius_Caesar.dcm
    const Tag bug(0x0054,0x0200);
    if( TagField == bug )
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
      if(TagField == bug)
        {
        assert( vl == 6 );
        vl = 7;
        }
#endif
    ValueLengthField = vl;
    }
  // Read the Value
  if( VRField == VR::SQ )
    {
    // Check wether or not this is an undefined length sequence
    SequenceOfItems<ExplicitDataElement> si( ValueLengthField  );
    _os >> si;
    }
  else if( ValueLengthField == 0xFFFFFFFF )
    {
    // Ok this is Pixel Data fragmented...
    const Tag pixelData(0x7fe0,0x0010);
    assert( VRField == VR::OB 
         || VRField == VR::OW );
    assert( TagField == pixelData );
    SequenceOfItems<ExplicitDataElement> si;
    _os >> si;
    }
  else
    {
    assert (ValueLengthField != 0xFFFF ); // ??
    // We have the length we should be able to read the value
    if( ValueLengthField < 0xfff )
      {
      ValueField.SetLength(ValueLengthField); // perform realloc
      _os.Read(ValueField);
      }
    else
      {
#ifdef BIG_HACK2
      ValueField.SetLength(ValueLengthField);
      _os.Read(ValueField);
      std::ofstream f("/tmp/pixel.raw");
      f.write(ValueField.GetPointer(), ValueField.GetLength());
      f.close();
      _os.Seekg(0, std::ios::end); // FIXME garbage at the end...
#else
      _os.Seekg(ValueLengthField, std::ios::cur);
#endif
      }
    }

  return _os;
}

} // end namespace gdcm
