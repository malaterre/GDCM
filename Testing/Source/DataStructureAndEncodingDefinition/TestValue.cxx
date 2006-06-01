#include "gdcmByteValue.h"
#include "gdcmSequenceOfItems.h"

void PrintStream(std::istream &is)
{
  char c;
  while(is.get(c))
    {
    std::cout << (int)c << std::endl;
    }
}

int CheckStream(std::istream &is, int size)
{
  char c;
  int t = 0;
  while(is.get(c) && (int)c == t)
    {
    //std::cout << (int)c << std::endl;
    ++t;
    }
  return t != size;
}

int TestValue(int , char *[])
{
  int r = 0;
  gdcm::Value *v;
  gdcm::SequenceOfItems si;
  gdcm::ByteValue bv;
  v = &si;
  v = &bv;

  const int size = 128;
  char buffer[size];
  for(int i=0; i<size;++i)
    {
    buffer[i] = static_cast<char>(i);
    }
  std::stringstream ss;
  ss.write(buffer, size);
  //PrintStream(ss);

  v->SetLength( size );
  v->Read(ss);
  std::stringstream ss2;
  v->Write(ss2);
  //PrintStream(ss2);
  r += CheckStream(ss2, size);

  return r;
}
