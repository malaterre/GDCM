#include "gdcmTag.h"
#include "gdcmDICOMIStream.h"
#include "gdcmDICOMOStream.h"
#include <fstream>

// Purpose of this test is to make sure we can read and write a gdcm::Tag
int TestTagIO(int , char *[])
{
  //----------------------------------------------------------
  // Conventional
  std::cout << "Constructor with uint32_t:" << std::hex << 0x12345678 
            << std::endl;
  gdcm::Tag t0(0x12345678);
  std::cout << "t0 : " << t0 << std::endl;
  std::cout << std::hex << "t0.GetElementTag() : " << t0.GetElementTag() 
            << std::endl;
  uint32_t u1_32 = t0.GetElementTag();	    
  std::cout << std::hex << "u1_32 : " << u1_32 
            << std::endl;
	    
  std::cout << "Constructor with 2 x uint16_t:" << 0x1234<< "," << 0x5678
            << std::endl;	    
  gdcm::Tag t(0x1234, 0x5678);
  std::cout << "t : " << t << std::endl;
  std::cout << std::hex << "t.GetElementTag() : " << t.GetElementTag() 
            << std::endl;

  //----------------------------------------------------------
  // Write+Read a Tag using write()+read() std::ofstream methods 
  std::ofstream f( "/tmp/bla.bin", std::ios::binary);
  if( !f )
    {
    std::cerr << "Problem opening the file" << std::endl;
    return 1;
    }
  uint32_t tag = t.GetElementTag();
  std::cout << std::hex << "uint32_t tag : " << tag << std::endl; 
  f.write( (char*)&tag, sizeof(uint32_t));
  f.close();

  std::ifstream i( "/tmp/bla.bin", std::ios::binary);
  if( !i )
    {
    std::cerr << "Problem opening the file" << std::endl;
    return 1;
    }
  uint32_t itag;
  i.read((char*)&itag, sizeof(uint32_t));
  i.close();
  
  std::cout << "Just to inform : uint32_t read value=" << itag ; 
  std::cout << " stored in RAM as :";  
  for (unsigned int j=0;j<sizeof(uint32_t);j++) 
  {
     std::cout << std::hex <<"[" <<(uint32_t)((uint8_t*)&itag)[j] << "] " ;
  }
   std::cout << std::endl;
   
  gdcm::Tag it(itag);

  if( t != it )
    {
    std::cerr << "t=  " << t  << std::endl;
    std::cerr << "it= " << it << std::endl;
    return 1;
    }
    else
    {
    std::cout << "OK :";    
    std::cout << " t=  " << t ;
    std::cout << " it= " << it << std::endl;
    }
  //----------------------------------------------------------
  // Same test using the std::ofstream::write method + gdcm::DICOMIStream class
  gdcm::Tag o;
  gdcm::DICOMIStream gi;
  gi.SetFileName( "/tmp/bla.bin" );
  gi.Open();
  gi.Read(o);
  gi.Close();

  if( o != t )
    {
    std::cerr << "t= " << t << std::endl;
    std::cerr << "o= " << o << std::endl;
    //return 1;
    }

  //----------------------------------------------------------
  // Same test using the gdcm::DICOMOStream + gdcm::DICOMIStream classes
  gdcm::DICOMOStream go;
  go.SetFileName( "/tmp/bla2.bin" );
  go.Open();
  go.Write(t);
  go.Close();

  gdcm::Tag o2;
  gdcm::DICOMIStream gi2;
  gi2.SetFileName( "/tmp/bla.bin" );
  gi2.Open();
  gi2.Read(o2);
  gi2.Close();

  if( o2 != t )
    {
    std::cerr << "t= "  << t  << std::endl;
    std::cerr << "o2= " << o2 << std::endl;
    return 1;
    }

  std::cout << "t : " << t  << std::endl;
  std::cout << "it: " << it << std::endl;
  std::cout << "o : " << o  << std::endl;
  std::cout << "o2: " << o2 << std::endl;

  return 0;
}
