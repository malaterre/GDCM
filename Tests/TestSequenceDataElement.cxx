#include "gdcmSequenceItems.txx"
#include "gdcmExplicitDataElement.h"
#include "gdcmSequenceItem.txx"

void TestInstanciation()
{
  typedef gdcm::ExplicitDataElement DEType;
  gdcm::SequenceItems<DEType> sde;
  std::cout << sde << std::endl;

  typedef gdcm::ImplicitDataElement DEType2;
  gdcm::SequenceItems<DEType2> sde2;
  std::cout << sde2 << std::endl;
}

int TestSequenceDataElement(int , char *[])
{
  TestInstanciation();

  typedef gdcm::ExplicitDataElement DEType;
  gdcm::SequenceItems<DEType> sde;
  if( !sde.IsUndefinedLength() )
    return 1;

  gdcm::SequenceItem<DEType> si;
  sde.AddSequenceItem(si);
  sde.AddSequenceItem(si);

  DEType de1;
  DEType de2;
  de2.SetTag(gdcm::Tag(0x1234,0x5678));
  si.AddDataElement(de1);
  si.AddDataElement(de2);

  std::cout << "Printing SQ:" << std::endl;
  std::cout << sde << std::endl;

  return 0;
}
