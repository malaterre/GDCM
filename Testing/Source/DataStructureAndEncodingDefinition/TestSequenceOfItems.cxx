#include "gdcmSequenceOfItems.h"

int TestSequenceOfItems(int, char *[])
{
  gdcm::SequenceOfItems si;
  std::cout << si << std::endl;

  return 0;
}
