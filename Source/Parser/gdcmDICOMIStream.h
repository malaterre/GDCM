
#ifndef __gdcmDICOMIStream_h
#define __gdcmDICOMIStream_h

#include "gdcmIStream.h"
#include "gdcmTag.h"
#include "gdcmVR.h"
#include "gdcmValue.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmItem.h"
#include "gdcmGroup.h"
#include <exception>

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
  ~DICOMIStream() {};

  // The following methods are public.
  // DO NOT EXPECT TO REMAIN LIKE THAT
  // indeed there is multiple problem:
  // - Expose to much of internals for users
  // - VS6 cannot deal with templated method in non-templated class
  // Read a tag from the IStream
  IStream &Read(Tag &t) throw (std::exception);

  // Read a VR from the IStream
  IStream &Read(VR::VRType &t);

  // Read a uin16_t from the Stream
  IStream &Read(uint16_t &vl);

  // Read a uin32_t from the Stream
  IStream &Read(uint32_t &vl);

  // Read a Value from the Stream
  // The Value cannot be Undefined Length
  IStream &Read(Value &v);

  IStream& Read(DataElement& da);
  IStream& Read(ExplicitDataElement &xda);
  IStream& Read(ImplicitDataElement &ida);
  template<class DEType>
  IStream& Read(SequenceOfItems<DEType> &_sq);
  template<class DEType>
  DICOMIStream& Read(Item<DEType> &_val);
  template<class DEType>
  IStream& Read(Group<DEType> &_val);

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

} // end namespace gdcm

#endif //__gdcmDICOMIStream_h
