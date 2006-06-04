#include "gdcmReader.h"
#include "gdcmTrace.h"
#include "gdcmVR.h"

namespace gdcm
{

/// \brief tells us if "DICM" is found as position 128 
///        (i.e. the file is a 'true dicom' one)
/// If not found then seek back at beginning of file (could be malinkroft
/// or old ACRNEMA with no preamble
/// \precondition we are at the beginning of file
/// \postcondition we are at the beginning of the DataSet or 
/// Meta Information Header
bool Reader::ReadPreamble()
{
  bool r = false;
  char dicm[128+4];
  Stream.Read(dicm, 128+4);
  if( dicm[128+0] == 'D'
   && dicm[128+1] == 'I'
   && dicm[128+2] == 'C'
   && dicm[128+3] == 'M')
    {
    r = true;
    }
  if(!r)
    {
    gdcmDebugMacro( "Not a DICOM V3 file" );
    Stream.Seekg(0, std::ios::beg);
    }

  return r;
}

/// \brief read the DICOM Meta Information Header
/// Find out the TransferSyntax used (default: Little Endian Explicit)
/// \precondition we are at the start of group 0x0002 (after preamble)
/// \postcondition we are at the beginning of the DataSet
void Reader::ReadMetaInformation()
{
  // The idea being we try multiple heuristics until we are happy ... 
  // and then keep our finger cross 
  Tag t;
  t.Read(Stream);
  assert( t.GetGroup() < 0x6000 ); // Magic number
  /// \TODO fixme breaks on : gdcmData/LIBIDO-16-ACR_NEMA-Volume.dcm
  //assert( t.GetGroup() < 0x0090 ); //Cannot start whith a group > 0008!   
  if( ! (t.GetGroup() % 2) )
    {
    // Purposely not Re-use ReadVR since we can read VR_END
    char vr_str[3];
    Stream.Read(vr_str, 2);
    vr_str[2] = '\0';
    VR::VRType vr = VR::GetVRType(vr_str);
    if( vr != VR::VR_END )
      {
      assert( vr == VR::UL
           || vr == VR::OB
           || vr == VR::UI
           /*|| vr == VR::CS*/ );
      MetaInformationTS = Explicit;
      }
    else
      {
      assert( !(VR::IsSwap(vr_str)));
      Stream.Seekg(-2, std::ios::cur); // Seek back
      if( t.GetElement() == 0x0000 )
        {
        VL group_length;
        assert( Stream.GetSwapCode() == SwapCode::Unknown );
        group_length.Read(Stream);
        SwapCode sc;
        switch(group_length)
          {
        case 0x00040000 :
          sc = SwapCode::BadLittleEndian; // 3412
          break;
        case 0x04000000 :
          sc = SwapCode::BigEndian;       // 4321
          break;  
        case 0x00000400 :
          sc = SwapCode::BadBigEndian;    // 2143
          break;
        case 0x00000004 :
          sc = SwapCode::LittleEndian;    // 1234
          break;
        default:
          abort();
          }
        Stream.Seekg(0, std::ios::beg);
        gdcmDebugMacro( "T=" << Stream.Tellg() );
        //if(!Stream.ReadDICM())
        //  IStream::Seekg(0, std::ios::beg);
        gdcmDebugMacro( "T=" << Stream.Tellg() );
        t.Read(Stream);
        }
      MetaInformationTS = Implicit;
      }
    }
  else
    {
    gdcmWarningMacro( "Start with private element" );
    //VR vr;
    //vr.Read(Stream);
    //VR::VRType vr = VR::GetVRType(vr_str);
    //if( vr != VR::VR_END )
    //  NegociatedTS = Explicit;
    //else
    //  {
    //  assert( !(VR::IsSwap(vr_str)));
    //  NegociatedTS = Implicit;
    //  }
    }

  // When we return we moved back the stream after the DICM header
  Stream.Seekg(0, std::ios::beg);
  if( !ReadPreamble() )
    {
    Stream.Seekg(0, std::ios::beg);
    }
}

int Reader::Read()
{
  return 0;
}

} // end namespace gdcm
