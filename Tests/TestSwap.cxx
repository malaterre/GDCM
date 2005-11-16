#include "gdcmSwap.txx"

int TestSwap(int , char *[])
{
  uint16_t t = 0x1234;
  uint16_t st = Swap<short>(t);
  if( t != 0x3412 )
    return 1;

  return 0;
}
