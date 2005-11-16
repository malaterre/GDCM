#include "gdcmTS.h"
#include <assert.h>
#include <string.h>

namespace gdcm
{

static const char *TSStrings[] = {
    // Implicit VR Little Endian
  "1.2.840.10008.1.2",
  // Implicit VR Big Endian DLX (G.E Private)
  "1.2.840.113619.5.2",
  // Explicit VR Little Endian
  "1.2.840.10008.1.2.1",
  // Deflated Explicit VR Little Endian
  "1.2.840.10008.1.2.1.99",
  // Explicit VR Big Endian
  "1.2.840.10008.1.2.2",
  // JPEG Baseline (Process 1)
  "1.2.840.10008.1.2.4.50",
  // JPEG Extended (Process 2 & 4)
  "1.2.840.10008.1.2.4.51",
  // JPEG Extended (Process 3 & 5)
  "1.2.840.10008.1.2.4.52",
  // JPEG Spectral Selection, Non-Hierarchical (Process 6 & 8)
  "1.2.840.10008.1.2.4.53",
  // JPEG Full Progression, Non-Hierarchical (Process 10 & 12)
  "1.2.840.10008.1.2.4.55",
  // JPEG Lossless, Non-Hierarchical (Process 14)
  "1.2.840.10008.1.2.4.57",
  // JPEG Lossless, Hierarchical, First-Order Prediction (Process 14,
  //                                                       [Selection Value 1])
  "1.2.840.10008.1.2.4.70",
  // JPEG-LS Lossless Image Compression
  "1.2.840.10008.1.2.4.80",
  // JPEG-LS Lossy (Near-Lossless) Image Compression
  "1.2.840.10008.1.2.4.81",
  // JPEG 2000 Lossless
  "1.2.840.10008.1.2.4.90",
  // JPEG 2000
  "1.2.840.10008.1.2.4.91",
  // RLE Lossless
  "1.2.840.10008.1.2.5",
  // MPEG2 Main Profile @ Main Level
  "1.2.840.10008.1.2.4.100",
  // Unknown
  "Unknown Transfer Syntax", // Pretty sure we never use this case...
  0 // Compilers have no obligation to finish by NULL, do it ourself
};

const char* TS::GetTSString(const TSType &ts)
{
  assert( ts < TS_END );
  return TSStrings[(int)ts];
}

// FIXME IsJPEG and IsMPEG and real bad implementation... NEED TO REDO
bool TS::IsMPEG(const TSType &ts)
{
  const char *s = GetTSString(ts);
  const char mpeg[] = "1.2.840.10008.1.2.4.100"; // special case
  if( strcmp(s, mpeg) == 0)
    return true;
  return false;
}

bool TS::IsJPEG(const TSType &ts)
{
  const char *s = GetTSString(ts);
  const char jpeg[] = "1.2.840.10008.1.2.4";
  const char mpeg[] = "1.2.840.10008.1.2.4.100"; // special case
  if( strcmp(s, mpeg) == 0)
    return false;
  if( strncmp(s, jpeg, strlen(jpeg)) == 0)
    return true;
  return false;
}

} // end namespace gdcm
