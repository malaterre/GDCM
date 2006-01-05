
#include "gdcmDICOMOStream.h"

namespace gdcm
{
OStream& DICOMOStream::Write(const Tag &t)
{
  assert( sizeof(t) == 4 );
  return OStream::Write((char*)(&t.ElementTag.tag), 4);
}

OStream& DICOMOStream::Write(const VR::VRType &vr)
{
  const char *vr_str = VR::GetVRString(vr);
  assert( strlen(vr_str) == 2 );
  return OStream::Write(vr_str, 2);
}

OStream& DICOMOStream::Write(const uint16_t &vl)
{
  return OStream::Write((char*)(&vl), 2);
}

OStream& DICOMOStream::Write(const uint32_t &vl)
{
  return OStream::Write((char*)(&vl), 4);
}

OStream& DICOMOStream::Write(const Value &v)
{
  return OStream::Write(v.Internal, v.Length);
}

OStream &DICOMOStream::WriteDICM()
{
  char dicm[128+4];
  memset(dicm,0,128);
  dicm[128] = 'D';
  dicm[129] = 'I';
  dicm[130] = 'C';
  dicm[131] = 'M';
  assert( dicm[124+4] == 'D'
       && dicm[125+4] == 'I'
       && dicm[126+4] == 'C'
       && dicm[127+4] == 'M');
  OStream::Write(dicm, 128+4);
  return *this;
}

}

