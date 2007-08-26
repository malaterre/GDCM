#include <iostream>

struct A
{
  float Internal;
};

struct B
{
  float Internal[1];
};

int TestElement4(int, char *[])
{
  std::cout << sizeof( A ) << std::endl;
  std::cout << sizeof( B ) << std::endl;

  return 0;
}
