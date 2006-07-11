#include "gdcmSequenceOfItems.h"

int TestSequenceOfItems(int, char *[])
{
  gdcm::SequenceOfItems si(gdcm::TS::Explicit);
  std::cout << si << std::endl;

  return 0;
}
