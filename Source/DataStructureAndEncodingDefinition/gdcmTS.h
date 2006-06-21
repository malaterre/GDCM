#ifndef __gdcmTS_h
#define __gdcmTS_h

//#include "gdcmTransferSyntax.h" // Generated File from TransferSyntax.dic
#include "gdcmType.h"
#include "gdcmSwapCode.h"

namespace gdcm
{

/**
 * \brief Class to manipulate Transfer Syntax
 * \note
 * TRANSFER SYNTAX (Standard and Private): A set of encoding rules that
 * allow Application Entities to unambiguously negotiate the encoding 
 * techniques (e.g., Data Element structure, byte ordering, compression) 
 * they are able to support, thereby allowing these Application Entities
 * to communicate.
 * \TODO: The implementation is completely retarded
 * We need: IsSupported
 * We need preprocess of raw/xml file
 * We need GetFullName()
 */
class GDCM_EXPORT TS
{
public:
  typedef enum {
    Unknown = 0,
    Explicit,
    Implicit
  } NegociatedType;

#error redo TS to be a real class and not a type
  // TODO
  typedef enum {
    PixelSpacing,
    ImagerPixelSpacing,
    PixelAspectRatio
  } ImageSpacingType;
  ImageSpacingType GetImageSpacing();

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
    ImplicitVRBigEndianACRNEMA,
    TS_END
  } TSType;

  // Return the string as written in the official DICOM dict from 
  // a custom enum type
  static const char* GetTSString(const TSType &ts);
  static const TSType GetTSType(const char *str);

  static NegociatedType GetNegociatedType(const TSType &ts);
  static SwapCode GetSwapCode(const TSType &ts);

protected:
  // TODO are those function actually usefull ?
  static bool IsJPEG(const TSType &ts);
  static bool IsMPEG(const TSType &ts);
  static bool IsExplicit(const TSType &ts);
  static bool IsImplicit(const TSType &ts);
  static bool IsLittleEndian(const TSType &ts);
  static bool IsBigEndian(const TSType &ts);


  // Very special case of the DICOM specification the *whole* dataset
  // is encoded (typically compressed using the deflate algorithm)
  // therefore you cannot parse the file out of the box without
  // first uncompressing it (expensive operation)
  // TODO: Can we partially uncompress in LZW ?
  static bool IsDataSetEncoded(const TSType &ts);

//private:
//  TSType TSField;
};

} // end namespace gdcm

#endif //__gdcmTS_h
