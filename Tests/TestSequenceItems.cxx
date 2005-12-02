#include "gdcmSequenceItems.txx"

template<class DEType>
void TestInstanciation()
{
  gdcm::SequenceItems<DEType> si;
  std::cout << si << std::endl;
}

template<class DEType>
void PrintEmptySequenceItems()
{
  gdcm::SequenceItems<DEType> si;
  std::cout << si << std::endl;
}

int TestSequenceItems(int , char *[])
{
  TestInstanciation<gdcm::ExplicitDataElement>();
  TestInstanciation<gdcm::ImplicitDataElement>();

  PrintEmptySequenceItems<gdcm::ExplicitDataElement>();
  PrintEmptySequenceItems<gdcm::ImplicitDataElement>();

  typedef gdcm::ExplicitDataElement DEType;
  gdcm::SequenceItems<DEType> sde;
  if( !sde.IsUndefinedLength() )
    return 1;

  gdcm::Item<DEType> si;
  sde.AddItem(si);
  sde.AddItem(si);

  DEType de1;
  DEType de2;
  de2.SetTag(gdcm::Tag(0x1234,0x5678));
  si.AddDataElement(de1);
  si.AddDataElement(de2);

  std::cout << "Printing SQ:" << std::endl;
  std::cout << sde << std::endl;

  return 0;
}
