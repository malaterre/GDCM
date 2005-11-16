
#include "gdcmOStream.h"

namespace gdcm
{
OStream& OStream::Write(const Tag &t)
{
  assert( !(!InternalStream) );
  assert( sizeof(t) == 4 );
  InternalStream.write((char*)(&t.ElementTag.tag), 4);
  return *this;
}

OStream& OStream::Write(const VR::VRType &vr)
{
  assert( !(!InternalStream) );
  const char *vr_str = VR::GetVRString(vr);
  assert( strlen(vr_str) == 2 );
  InternalStream.write(vr_str, 2);
  return *this;
}

OStream& OStream::Write(const uint16_t &vl)
{
  assert( !(!InternalStream) );
  InternalStream.write((char*)(&vl), 2);
  return *this;
}

OStream& OStream::Write(const uint32_t &vl)
{
  assert( !(!InternalStream) );
  InternalStream.write((char*)(&vl), 4);
  return *this;
}

OStream& OStream::Write(const Value &v)
{
  assert( !(!InternalStream) );
  InternalStream.write(v.Internal, v.Length);
  return *this;
}


}

