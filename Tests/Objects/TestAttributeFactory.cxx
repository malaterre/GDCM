#include "gdcmAttributeFactory.h"
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
  //gdcm::AttributeFactory<gdcm::VR::FL, 0> f0;
  //f0.Print(std::cout);

  std::stringstream ss;
  //const float *p[] = {{ 2.5f }};
  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM1> f1 = {2.5f}; //Randomize<float,1>();
  f1.Print(std::cout);
  std::cout << std::endl;
  f1.Write(ss);
  f1.Read(ss);
  f1.Print(std::cout);
  std::cout << std::endl;

  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM2> f2  = { 2.5f, 3.5f};
  f2.Print(std::cout);
  std::cout << std::endl;
  f2.Write(ss);
  f2.Read(ss);
  f2.Print(std::cout);
  std::cout << std::endl;

#if 0
  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM3> f3  = { 2.5f, 3.5f, 4.5f};
  f3.Print(std::cout);
  f3.Write(std::cout);
  std::cout << std::endl;

  // The following is allowed in C++, a zero default initialization is done by the compiler
  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM4> f4  = { 2.5f, 3.5f, 4.5f};
  f4.Print(std::cout);
  f4.Write(std::cout);
  std::cout << std::endl;

  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM5> f5  = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f };
  f5.Print(std::cout);
  f5.Write(std::cout);
  std::cout << std::endl;

  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM6> f6  = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f6.Print(std::cout);
  f6.Write(std::cout);
  std::cout << std::endl;

  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM8> f8  = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f8.Print(std::cout);
  f8.Write(std::cout);
  std::cout << std::endl;

  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM16> f16  = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f16.Print(std::cout);
  f16.Write(std::cout);
  std::cout << std::endl;

  // FIXME What if people wants to pass 17 values.... it will always be 32...
  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM1_32> f32  = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f32.Print(std::cout);
  f32.Write(std::cout);
  std::cout << std::endl;
#endif

  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM1_99> f99 = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  f99.Print(std::cout);
  std::cout << std::endl;
  f99.Write(ss);
  f99.Read(ss);
  f99.Print(std::cout);
  std::cout << std::endl;

  // This one also should not compile
  // gdcm::AttributeFactory<gdcm::VR::FL, 100> f100 = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  
  // A dummy user might be suprised by this one, since 7 is actually VM8 ...
  // I should maybe give a real value to the VM with integral type
  //gdcm::AttributeFactory<gdcm::VR::FL, 7> f100 = { 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f };
  //f100.Print(std::cout);


  // Test Read
  std::ostringstream os;
  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM6> f = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f };
  f.Write(os);

  std::istringstream is;
  is.str(os.str());
  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM6> ff;
  ff.Read(is);
  ff.Print(std::cout);
  std::cout << std::endl;
}

void TestFloatN()
{
  // This one should not compile:
  // gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM1_n> fn = {0,0};
  std::cout << "TestFloatN" << std::endl;

  static float tab[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
  const int len = 13;
  std::stringstream ss;
  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM1_n> fn;
  fn.SetLength(0);
  fn.SetLength(len);
  fn.SetArray(tab, len, true);
  fn.Print(std::cout);
  std::cout << std::endl;
  fn.Write(ss);
  fn.Read(ss);
  fn.Print(std::cout);
  std::cout << std::endl;

  // Test Read
  std::ostringstream os;
  fn.Write(os);

  std::istringstream is;
  is.str(os.str());
  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM1_n> ff;
  ff.SetLength(len);
  ff.Read(is);
  ff.Print(std::cout);
  //ff.Write(std::cout);
  std::cout << std::endl;

  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM1_n> copy = ff;
  ff.Print(std::cout);
  //ff.Write(std::cout);
  std::cout << std::endl;

  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM2_n> f2n;
  f2n.SetLength(1);
  std::cout << f2n.GetLength() << std::endl;

  gdcm::AttributeFactory<gdcm::VR::FL, gdcm::VM::VM3_3n> f3n3;
  f3n3.SetLength(3);
  f3n3.SetLength(4);
  std::cout << f3n3.GetLength() << std::endl;
}

void TestAS()
{
  //gdcm::AttributeFactory<gdcm::VR::AS, gdcm::VM::VM1> as1 = "abcd";
//  gdcm::AttributeFactory<gdcm::VR::AS, gdcm::VM::VM1> as1 = "abcd";
}

void TestPN()
{
  /*
   * istream becomes invalid if one do the following:
   * std::istringstream is;
   * is.str( "1 2 3" );
   * int a;
   * while( is >> a );
   * //is.clear(); // Important
   * is.str( "1.0 2.0" );
   * double d;
   * while( is >> d ); // nothing is done !
   */
  std::stringstream ss;
  gdcm::AttributeFactory<gdcm::VR::PN, gdcm::VM::VM1> pn1("Marc^Simon");
  pn1.Print(std::cout);
  std::cout << std::endl;
  pn1.Write(ss);
  pn1.Read(ss);
  pn1.Print(std::cout);
  std::cout << std::endl;

  ss.clear();
  gdcm::AttributeFactory<gdcm::VR::PN, gdcm::VM::VM1> pn2 = "Simon^Marc";
  pn2.Print(std::cout);
  std::cout << std::endl;
  pn2.Write(ss);
  pn2.Read(ss);
  pn2.Print(std::cout);
  std::cout << std::endl;

  ss.clear();
  gdcm::AttributeFactory<gdcm::VR::PN, gdcm::VM::VM2> pn3 = 
    "Simon^Marc\\Marc^Simon";
  pn3.Print(std::cout);
  std::cout << std::endl;
  pn3.Write(ss);
  pn3.Read(ss);
  pn3.Print(std::cout);
  std::cout << std::endl;
}

int TestAttributeFactory(int , char *[])
{
  TestFloat();
  TestFloatN();
  TestPN();

  return 0;
}


