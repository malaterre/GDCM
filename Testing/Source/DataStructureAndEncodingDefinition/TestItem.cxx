#include "gdcmItem.h"

int TestItem(int , char *[])
{
  gdcm::Item item;
  std::cout << item << std::endl;

  return 0;
}
