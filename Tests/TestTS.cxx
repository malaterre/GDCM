#include "gdcmTS.h"
#include <iostream>

int TestTS(int , char *[])
{
  int n = (int)gdcm::TS::TS_END;
  gdcm::TS::TSType ts;
  for(int i=0; i<n; ++i)
    {
    ts = (gdcm::TS::TSType)i;
    std::cout << ts << "\t->\t" << gdcm::TS::GetTSString(ts) << std::endl;
    }

  // JPEG
  ts = gdcm::TS::JPEGLSNearLossless;
  if( !gdcm::TS::IsJPEG(ts) )
    return 1;
  ts = gdcm::TS::MPEG2MainProfile;
  if( gdcm::TS::IsJPEG(ts) )
    return 1;
  ts = gdcm::TS::RLELossless;
  if( gdcm::TS::IsJPEG(ts) )
    return 1;

  // MPEG
  ts = gdcm::TS::MPEG2MainProfile;
  if( !gdcm::TS::IsMPEG(ts) )
    return 1;
  ts = gdcm::TS::RLELossless;
  if( gdcm::TS::IsMPEG(ts) )
    return 1;

  return 0;
}
