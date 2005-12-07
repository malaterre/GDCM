#include "gdcmDICOMType.h"
#include "gdcmVR.h"
#include "gdcmVM.h"

template<class T, int N>
inline const T* Randomize()
{
  T array[N];
  for(int i=0; i<N; i++)
    array = (T)i;
  return array;
}

// FIXME TODO
void TestDouble() {}
void TestUnsignedShort() {}
void TestSignedShort() {}
void TestUnsignedLong() {}
void TestSignedLong() {}

void TestFloat()
{
  // This one should not compile, it would be nice to have a test for that...
  //gdcm::DICOMType<gdcm::VR::FL, 0> f0;
  //f0.Print(std::cout);

  //const float *p[] = {{ 2.5f }};
  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM1> f1 = {2.5f}; //Randomize<float,1>();
  f1.Print(std::cout);
  f1.Write(std::cout);
  std::cout << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM2> f2  = { 2.5f, 3.5f};
  f2.Print(std::cout);
  f2.Write(std::cout);
  std::cout << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM3> f3  = { 2.5f, 3.5f, 4.5f};
  f3.Print(std::cout);
  f3.Write(std::cout);
  std::cout << std::endl;

  // The following is allowed in C++, a zero default initialization is done by the compiler
  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM4> f4  = { 2.5f, 3.5f, 4.5f};
  f4.Print(std::cout);
  f4.Write(std::cout);
  std::cout << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM5> f5  = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f };
  f5.Print(std::cout);
  f5.Write(std::cout);
  std::cout << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM6> f6  = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f6.Print(std::cout);
  f6.Write(std::cout);
  std::cout << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM8> f8  = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f8.Print(std::cout);
  f8.Write(std::cout);
  std::cout << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM16> f16  = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f16.Print(std::cout);
  f16.Write(std::cout);
  std::cout << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM1_32> f32  = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f32.Print(std::cout);
  f32.Write(std::cout);
  std::cout << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM1_99> f99 = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f99.Print(std::cout);
  f99.Write(std::cout);
  std::cout << std::endl;


  // Test Read
  std::ostringstream os;
  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM6> f = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f };
  f.Write(os);

  std::istringstream is;
  is.str(os.str());
  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM6> ff;
  ff.Read(is);
  ff.Print(std::cout);
  ff.Write(std::cout);
  std::cout << std::endl;

}

int TestDICOMType(int , char *[])
{
  TestFloat();
  return 0;
}


