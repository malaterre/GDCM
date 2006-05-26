#include "gdcmVR.h"

int TestVR(int, char *[])
{
  // avoid INVALID = 0
  for(int i = 1; i < 27; ++i)
    {
    gdcm::VR::VRType t = (gdcm::VR::VRType)(1 << i);
    if( gdcm::VR::IsASCII( t ) != gdcm::VR::IsASCII2( t ) )
      {
      std::cerr << t << std::endl;
      return 1;
      }
    //if( gdcm::VR::IsBinary( t ) != gdcm::VR::IsBinary2( t ) )
    //  {
    //  std::cerr << t << std::endl;
    ////  return 1;
    //  }
    }

  return 0;
}
