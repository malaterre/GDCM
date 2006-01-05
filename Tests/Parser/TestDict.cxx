#include "gdcmDict.h"

int TestDict(int , char *[])
{
  gdcm::Dict d;
  const gdcm::Tag t1(0x5600, 0x0000); //, "UL" , "1" , "Group Length"}, 
  const gdcm::Tag t2(0x5600, 0x0010); //, "OF" , "1" , "First Order Phase Correction Angle"}, 
  const gdcm::Tag t3(0x5600, 0x0020); //, "OF" , "1" , "Spectroscopy Data"}, 
  const gdcm::Tag t4(0x5400, 0x0110); //, "OB or OW" , "1" , "Channel Minimum Value"}, 
  std::cout << d << std::endl;

  const gdcm::DictEntry &de1 = d.GetDictEntry(t1);
  std::cout << de1 << std::endl;
  const gdcm::DictEntry &de2 = d.GetDictEntry(t2);
  std::cout << de2 << std::endl;
  const gdcm::DictEntry &de3 = d.GetDictEntry(t3);
  std::cout << de3 << std::endl;
  const gdcm::DictEntry &de4 = d.GetDictEntry(t4);
  std::cout << de4 << std::endl;
  return 0;
}
