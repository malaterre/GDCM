#include "gdcmItem.h"

int TestItem(int argc, char *argv[])
{
  gdcm::Item item;
  std::cout << item << std::endl;

  return 0;
}
