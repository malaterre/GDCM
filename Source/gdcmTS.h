#ifndef __gdcmTS_h
#define __gdcmTS_h

//#include "gdcmTransferSyntax.h" // Generated File from TransferSyntax.dic
#include "gdcmType.h"

namespace gdcm
{

class TS
{
public:
  typedef enum {
    ImplicitVRLittleEndian = 0,
    ImplicitVRBigEndianPrivateGE,
    ExplicitVRLittleEndian,
    DeflatedExplicitVRLittleEndian,
    ExplicitVRBigEndian,
    JPEGBaselineProcess1,
    JPEGExtendedProcess2_4,
    JPEGExtendedProcess3_5,
    JPEGSpectralSelectionProcess6_8,
    JPEGFullProgressionProcess10_12,
    JPEGLosslessProcess14,
    JPEGLosslessProcess14_1,
    JPEGLSLossless,
    JPEGLSNearLossless,
    JPEG2000Lossless,
    JPEG2000,
    RLELossless,
    MPEG2MainProfile,
    TS_END
  } TSType;

  // Return the string as written in the official DICOM dict from 
  // a custom enum type
  static const char* GetTSString(const TSType &ts);
  static const TSType GetTSType(const char *str);
  static bool IsJPEG(const TSType &ts);
  static bool IsMPEG(const TSType &ts);
  static bool IsImplicit(const TSType &ts);
  static bool IsBigEndian(const TSType &ts);

};

} // end namespace gdcm

#endif //__gdcmTS_h
