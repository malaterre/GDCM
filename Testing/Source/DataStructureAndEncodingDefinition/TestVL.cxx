#include "gdcmVL.h"

int TestVL(int, char *[])
{
  gdcm::VL vl;
  if( vl != 0 )
    {
    return 1;
    }

  return 0;
}
