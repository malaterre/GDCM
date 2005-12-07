#include "gdcmExplicitDataElement.h"
#include "gdcmSequenceItems.txx"
#include "gdcmDict.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
DICOMOStream& operator<<(DICOMOStream &_os, const ExplicitDataElement &_val)
{
  //const DataElement &de = _val;
  //_os << de;
  _os.Write(_val.VRField);
  // See PS 3.5, Date Element Structure With Explicit VR
  if( _val.VRField == VR::OB
   || _val.VRField == VR::OW
   || _val.VRField == VR::OF
   || _val.VRField == VR::SQ
   || _val.VRField == VR::UN )
    {
    uint16_t check = 0x0;
    _os.Write(check);
    // Write Value Length (32bits)
    _os.Write(_val.ValueLengthField);
    }
  else if( _val.VRField == VR::UT )
    {
    uint16_t check = 0x0;
    _os.Write(check);
    // Write Value Length (32bits)
    assert( _val.ValueLengthField != 0xFFFFFFFF );
    _os.Write(_val.ValueLengthField);
    }
  else
    {
    uint16_t vl = _val.ValueLengthField;
    // Write Value Length (16bits)
    _os.Write(vl);
    }
  // We have the length we should be able to write the value
  _os.Write(_val.ValueField);
  return _os;
}

//-----------------------------------------------------------------------------
DICOMIStream& operator>>(DICOMIStream &_os, ExplicitDataElement &_val)
{
  // See PS 3.5, Date Element Structure With Explicit VR
  // Read Tag
  //if( !_os.Read(_val.TagField) ) return _os;
  //static Dict d;
  //const DictEntry &de = d.GetDictEntry(_val.TagField);
  // Read VR
  if( !(_os.Read(_val.VRField)) ) return _os;
//  if( !(de.GetVR() & _val.VRField) && de.GetVR() != VR::INVALID )
//    {
//    std::cerr << "BUGGY VR for Tag: " << _val.TagField << " : " << VR::GetVRString(_val.VRField)
//      << " should be: " << VR::GetVRString(de.GetVR()) << std::endl;
//    }
  if( _val.VRField == VR::OB
   || _val.VRField == VR::OW
   || _val.VRField == VR::OF
   || _val.VRField == VR::SQ
   || _val.VRField == VR::UN )
    {
    uint16_t check;
    _os.Read(check);
    assert( check == 0x0 );
    // Read Value Length (32bits)
    _os.Read(_val.ValueLengthField);
    }
  else if( _val.VRField == VR::UT )
    {
    uint16_t check;
    _os.Read(check);
    assert( check == 0x0 );
    // Read Value Length (32bits)
    _os.Read(_val.ValueLengthField);
    assert( _val.ValueLengthField != 0xFFFFFFFF );
    }
  else
    {
    // Two steps since ValueLengthField is 32 bits, we need to declare a 16bits int first
    uint16_t vl;
    // Read Value Length (16bits)
    _os.Read(vl);
    if( _val.VRField == VR::UL )
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
    if( _val.TagField == bug )
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
      if(_val.TagField == bug)
        {
        assert( vl == 6 );
        vl = 7;
        }
#endif
    _val.ValueLengthField = vl;
    }
  // Read the Value
  if( _val.VRField == VR::SQ )
    {
    // Check wether or not this is an undefined length sequence
    SequenceItems<ExplicitDataElement> si( _val.ValueLengthField  );
    _os >> si;
    }
  else if( _val.ValueLengthField == 0xFFFFFFFF )
    {
    // Ok this is Pixel Data fragmented...
    const Tag pixelData(0x7fe0,0x0010);
    assert( _val.VRField == VR::OB 
         || _val.VRField == VR::OW );
    assert( _val.TagField == pixelData );
    SequenceItems<ExplicitDataElement> si;
    _os >> si;
    }
  else
    {
    assert (_val.ValueLengthField != 0xFFFF ); // ??
    // We have the length we should be able to read the value
    if( _val.ValueLengthField < 0xfff )
      {
      _val.ValueField.SetLength(_val.ValueLengthField); // perform realloc
      _os.Read(_val.ValueField);
      }
    else
      {
#ifdef BIG_HACK2
      _val.ValueField.SetLength(_val.ValueLengthField);
      _os.Read(_val.ValueField);
      std::ofstream f("/tmp/pixel.raw");
      f.write(_val.ValueField.GetPointer(), _val.ValueField.GetLength());
      f.close();
      _os.Seekg(0, std::ios::end); // FIXME garbage at the end...
#else
      _os.Seekg(_val.ValueLengthField, std::ios::cur);
#endif
      }
    }

  return _os;
}

} // end namespace gdcm
