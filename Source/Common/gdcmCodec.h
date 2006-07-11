#ifndef __gdcmCodec_h
#define __gdcmCodec_h

#include "gdcmCoder.h"
#include "gdcmDecoder.h"

namespace gdcm
{

class Codec : public Coder, public Decoder
{
};

} // end namespace gdcm

#endif //__gdcmCodec_h
