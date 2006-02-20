#include <iostream>
#include <sstream>

int main()
{
  const char s[] = "\0&\0\0";
  uint32_t n = 0;
  memcpy(&n, s, 4);
  std::cout << n << std::endl;

  // Binary version
  uint32_t nn = 0;
  std::istringstream is;
  is.str( std::string(s,4) );
  is.read( reinterpret_cast<char*>(&nn), 4);
  std::cout << is.str() << "->" << nn << std::endl;

  // output stream seems to work
  std::ostringstream os;
  os.write( reinterpret_cast<char*>(&n), 4);
  std::cout << n << "->" << os.str() << std::endl;
  const char *p = os.str().c_str();
  std::cout << (p[0] == s[0]) << std::endl;
  std::cout << (p[1] == s[1]) << std::endl;
  std::cout << (p[2] == s[2]) << std::endl;
  std::cout << (p[3] == s[3]) << std::endl;

  return 0;
}
