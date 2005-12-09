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

  // FIXME What if people wants to pass 17 values.... it will always be 32...
  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM1_32> f32  = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f32.Print(std::cout);
  f32.Write(std::cout);
  std::cout << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM1_99> f99 = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f99.Print(std::cout);
  f99.Write(std::cout);
  std::cout << std::endl;

  // This one also should not compile
  // gdcm::DICOMType<gdcm::VR::FL, 100> f100 = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  
  // A dummy user might be suprised by this one, since 7 is actually VM8 ...
  // I should maybe give a real value to the VM with integral type
  //gdcm::DICOMType<gdcm::VR::FL, 7> f100 = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  //f100.Print(std::cout);


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

void TestFloatN()
{
  // This one should not compile:
  // gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM1_n> fn = {0,0};

  static float tab[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
  const int len = 13;
  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM1_n> fn;
  fn.SetLength(0);
  fn.SetLength(len);
  fn.SetArray(tab, len);
  fn.Print(std::cout);
  fn.Write(std::cout);
  std::cout << std::endl;

  // Test Read
  std::ostringstream os;
  fn.Write(os);

  std::istringstream is;
  is.str(os.str());
  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM1_n> ff;
  ff.SetLength(len);
  ff.Read(is);
  ff.Print(std::cout);
  ff.Write(std::cout);
  std::cout << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM1_n> copy = ff;
  ff.Print(std::cout);
  ff.Write(std::cout);
  std::cout << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM2_n> f2n;
  f2n.SetLength(1);
  std::cout << f2n.GetLength() << std::endl;

  gdcm::DICOMType<gdcm::VR::FL, gdcm::VM::VM3_3n> f3n3;
  f3n3.SetLength(3);
  f3n3.SetLength(4);
  std::cout << f3n3.GetLength() << std::endl;
}

void TestAS()
{
  //gdcm::DICOMType<gdcm::VR::AS, gdcm::VM::VM1> as1 = "abcd";
//  gdcm::DICOMType<gdcm::VR::AS, gdcm::VM::VM1> as1 = "abcd";
}

int TestDICOMType(int , char *[])
{
  TestFloat();
  TestFloatN();
  return 0;
}


