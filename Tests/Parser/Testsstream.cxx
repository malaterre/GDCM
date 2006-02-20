#include <iostream>
#include <sstream>

int main()
{
  const char s[] = "&\0\0\0";
  uint32_t n = 0;
  memcpy(&n, s, 4);
  std::cout << n << std::endl;
  std::istringstream is;
  is.str( s );
  uint32_t nn = 0;
  is >> nn;
  std::cout << nn << std::endl;
  return 0;
}
