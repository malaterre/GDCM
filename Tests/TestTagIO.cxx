#include "gdcmTag.h"
#include "gdcmIStream.h"
#include "gdcmOStream.h"
#include <fstream>

// Purpose of this test is to make sure we can read and write a gdcm::Tag
int TestTagIO(int , char *[])
{
  //----------------------------------------------------------
  // Conventional
  gdcm::Tag t(0x1234, 0x5678);
  std::ofstream f( "/tmp/bla.bin", std::ios::binary);
  if( !f )
    {
    std::cerr << "Problem opening the file" << std::endl;
    return 1;
    }
  uint32_t tag = t.GetElementTag(); 
  f.write( (char*)&tag, sizeof(tag));
  f.close();

  std::ifstream i( "/tmp/bla.bin", std::ios::binary);
  if( !i )
    {
    std::cerr << "Problem opening the file" << std::endl;
    return 1;
    }
  uint32_t itag;
  i.read((char*)&itag, sizeof(itag));
  i.close();
  gdcm::Tag it(itag);

  if( t != it )
    {
    std::cerr << "t= " << t << std::endl;
    std::cerr << "it= " << it << std::endl;
    return 1;
    }

  //----------------------------------------------------------
  // Same test using the gdcm::IStream class
  gdcm::Tag o;
  gdcm::IStream gi;
  gi.SetFileName( "/tmp/bla.bin" );
  gi.Open();
  gi.Read(o);
  gi.Close();

  if( o != t )
    {
    std::cerr << "t= " << t << std::endl;
    std::cerr << "o= " << o << std::endl;
    return 1;
    }

  //----------------------------------------------------------
  // Same test using the gdcm::IStream class
  gdcm::OStream go;
  go.SetFileName( "/tmp/bla2.bin" );
  go.Open();
  go.Write(t);
  go.Close();

  gdcm::Tag o2;
  gdcm::IStream gi2;
  gi2.SetFileName( "/tmp/bla.bin" );
  gi2.Open();
  gi2.Read(o2);
  gi2.Close();

  if( o2 != t )
    {
    std::cerr << "t= " << t << std::endl;
    std::cerr << "o2= " << o2 << std::endl;
    return 1;
    }

  std::cout << "t : " << t << std::endl;
  std::cout << "it: " << it << std::endl;
  std::cout << "o : " << o << std::endl;
  std::cout << "o2: " << o2 << std::endl;

  return 0;
}
