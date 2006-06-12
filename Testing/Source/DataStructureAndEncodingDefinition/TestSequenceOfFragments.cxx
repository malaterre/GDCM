#include "gdcmSequenceOfFragments.h"

int TestSequenceOfFragments(int, char *[])
{
  gdcm::SequenceOfFragments sf;
  std::cout << sf << std::endl;

  return 0;
}
