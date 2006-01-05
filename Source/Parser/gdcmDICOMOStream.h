
#ifndef __gdcmDICOMOStream_h
#define __gdcmDICOMOStream_h

#include "gdcmOStream.h"
#include "gdcmTag.h"
#include "gdcmVR.h"
#include "gdcmValue.h"


namespace gdcm
{
/**
 * \brief Wrapper around ofstream
 * \note bla
 */
class GDCM_EXPORT DICOMOStream : public OStream
{
public:
  // Write a tag from the IStream
  OStream &Write(const Tag &t);

  // Write a VR from the IStream
  OStream &Write(const VR::VRType &t);

  // Write a uin16_t from the Stream
  OStream &Write(const uint16_t &vl);

  // Write a uin32_t from the Stream
  OStream &Write(const uint32_t &vl);

  // Write a Value from the Stream
  OStream &Write(const Value &v);

  // Write a true DICOM V3 header
  OStream &WriteDICM();
};

}

#endif //__gdcmDICOMOStream_h
