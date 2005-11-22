#include "gdcmDICOMIStream.h"
#include "gdcmVR.h"
#include "gdcmByteSwap.txx"
#include "gdcmDataElement.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmTS.h"

namespace gdcm
{

IStream &DICOMIStream::Read(Tag &t)
{
  assert( sizeof(t) == 4 );
  IStream::Read((char*)(&t.ElementTag.tag), 4);
  //assert(!(t.GetGroup()%2));
  ByteSwap<uint16_t>::SwapRangeFromSwapCodeIntoSystem(t.ElementTag.tags, SwapCode, 2);
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
  ByteSwap<char>::SwapRangeFromSwapCodeIntoSystem((char*)(&vl_str), SwapCode, 2);
  vl = *((uint16_t*)(vl_str));
  return *this;
}

IStream &DICOMIStream::Read(uint32_t &vl)
{
  char vl_str[4];
  IStream::Read(vl_str,4);
  vl = *((uint32_t*)(vl_str));
  ByteSwap<uint32_t>::SwapFromSwapCodeIntoSystem(vl, SwapCode);
  return *this;
}

IStream &DICOMIStream::Read(Value &v)
{
  uint32_t length = v.GetLength();
  assert( length != 0xFFFFFFFF );
  return IStream::Read(v.Internal, length);
}

void DICOMIStream::Initialize()
{
  //FindNegociatedTS();
  ReadNonStandardDataElements();
  std::cerr << "NegociatedTS: " << NegociatedTS << std::endl;
  std::cerr << "SwapCode: " << SwapCode << std::endl;
}

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
    int i;
    for(i=0; i<128; ++i)
      if(dicm[i] != '\0' )
        {
        std::cerr << "Garbage in the DICOM Header" << std::endl;
        break;
        }
    if( i == 128 )
      {
      std::cerr << "Real clean HEADER" << std::endl;
      }
    }

  return r;
}

// Once our heuristic found
template<class DEType>
void CheckNegociatedTS(gdcm::DICOMIStream &is)
{
  DEType de;
  DataElement &de_tag = de;
  while( is >> de_tag )
    {
    is >> de;
    std::cout << de << std::endl;
   }
}


void DICOMIStream::ReadNonStandardDataElements()
{
  // Standatyd Data Elements have an even Group Number that is not
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
  while( *this >> de_tag )
    {
    if( de_tag.GetTag().GetGroup() < 0x0007 )
      {
      *this >> de;
      std::cout << "Debug: " << de << std::endl;
      if( de_tag.GetTag() == t )
        {
        gdcm::TS::TSType ts = gdcm::TS::GetTSType( de.GetValue().GetPointer() );
        //NegociatedTS = Explicit;
        bool isImplicit = gdcm::TS::IsImplicit( ts );
        if( isImplicit )
          {
          NegociatedTS = Implicit;
          }
        //bool isBigEndian = gdcm::TS::IsBigEndian( ts );
        //if( isBigEndian )
        //  {
        //  SwapCode = BigEndian;
        //  }
        }
      }
    else
      {
      // Ok seek back...
      Seekg(-4, std::ios::cur);
      break;
      }
    }
    }
}

void DICOMIStream::FindNegociatedTS()
{
  // Stream is passed the DICM header
  if( !ReadDICM() )
    {
    std::cerr << "Not a DICOM V3 file" << std::endl;
    IStream::Seekg(0, std::ios::beg);
    }
  
  // The idea being we try multiple heuristique until we are happy ... and then
  // keep our finger cross 
  Tag t;
  Read(t);
  assert( t.GetGroup() < 0x6000 ); // Magic number
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
        Read(group_length);
        switch(group_length)
          {
        case 0x00040000 :
          SwapCode = BadLittleEndian;
          break;
        case 0x04000000 :
          SwapCode = BigEndian;
          break;
        case 0x00000400 :
          SwapCode = BadBigEndian;
          break;
        case 0x00000004 :
          SwapCode = LittleEndian;
          break;
        default:
          abort();
          }
        Seekg(0, std::ios::beg);
        std::cerr << "T=" << Tellg() << std::endl;
        if(!ReadDICM())
          IStream::Seekg(0, std::ios::beg);
        std::cerr << "T=" << Tellg() << std::endl;
        Read(t);
        }
      NegociatedTS = Implicit;
      }
    }
  else
    {
    std::cerr << "Start with private element" << std::endl;
    char vr_str[3];
    IStream::Read(vr_str, 2);
    vr_str[2] = '\0';
    VR::VRType vr = VR::GetVRType(vr_str);
    if( vr != VR::VR_END )
      NegociatedTS = Explicit;
    else
      NegociatedTS = Implicit;
    }

  // When we return we moved back the stream after the DICM header
  IStream::Seekg(0, std::ios::beg);
  if( !ReadDICM() )
    {
    IStream::Seekg(0, std::ios::beg);
    }
}
  

}

