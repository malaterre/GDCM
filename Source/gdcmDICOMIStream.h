
#ifndef __gdcmDICOMIStream_h
#define __gdcmDICOMIStream_h

#include "gdcmIStream.h"
#include "gdcmTag.h"
#include "gdcmVR.h"
#include "gdcmValue.h"

namespace gdcm
{
/**
 * \brief Specialization of IFStream to read DICOM struct
 *
 * Detailled description here
 * \note bla
 */
class GDCM_EXPORT DICOMIStream : public IStream
{
public:
  DICOMIStream() { NegociatedTS = Unknown; }

  // Read a tag from the IStream
  IStream &Read(Tag &t);

  // Read a VR from the IStream
  IStream &Read(VR::VRType &t);

  // Read a uin16_t from the Stream
  IStream &Read(uint16_t &vl);

  // Read a uin32_t from the Stream
  IStream &Read(uint32_t &vl);

  // Read a Value from the Stream
  // The Value cannot be Undefined Length
  IStream &Read(Value &v);

  void Initialize();

  typedef enum {
    Unknown = 0,
    Implicit,
    Explicit
    } NegociatedTSType;

  NegociatedTSType GetNegociatedTS() { 
    assert( NegociatedTS != Unknown );
    return NegociatedTS; } ;

protected:
  // Read a true DICOM V3 header
  bool ReadDICM();

  void FindNegociatedTS();
  void ReadNonStandardDataElements();

  NegociatedTSType NegociatedTS;
};

}

#endif //__gdcmDICOMIStream_h
