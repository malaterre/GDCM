#include "gdcmIStream.h"

namespace gdcm
{

IStream &IStream::Read(Tag &t)
{
  assert( !(!InternalStream) );
  assert( sizeof(t) == 4 );
  InternalStream.read((char*)(&t.ElementTag.tag), 4);
  return *this;
}

IStream &IStream::Read(VR::VRType &vr)
{
  assert( !(!InternalStream) );
  char vr_str[3];
  InternalStream.read(vr_str, 2);
  vr_str[2] = '\0';
  vr = VR::GetVRType(vr_str);
  return *this;
}

IStream &IStream::Read(uint16_t &vl)
{
  assert( !(!InternalStream) );
  char vl_str[2];
  InternalStream.read(vl_str,2);
  vl = *((uint16_t*)(vl_str));
  return *this;
}

IStream &IStream::Read(uint32_t &vl)
{
  assert( !(!InternalStream) );
  char vl_str[4];
  InternalStream.read(vl_str,4);
  vl = *((uint32_t*)(vl_str));
  return *this;
}

IStream &IStream::Read(Value &v, uint32_t length)
{
  assert( !(!InternalStream) );
  v.SetLength(length); // perform realloc
  InternalStream.read(v.Internal, length);
  return *this;
}

IStream &IStream::ReadDICM()
{
  assert( !(!InternalStream) );
  char dicm[128+4];
  InternalStream.read(dicm, 128+4);
  assert( dicm[124+4] == 'D'
       && dicm[125+4] == 'I'
       && dicm[126+4] == 'C'
       && dicm[127+4] == 'M');
  return *this;
}

}

