#include "gdcmDictEntry.h"

int TestDictEntry(int , char *[])
{
  gdcm::DictEntry de("DICOM Name",(gdcm::VR::VRType)0,(gdcm::VM::VMType)0);
  std::cout << de << std::endl;

  return 0;
}
