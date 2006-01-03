#include "gdcmSequenceOfItems.txx"

template<class DEType>
void TestInstanciation()
{
  gdcm::SequenceOfItems<DEType> si;
  std::cout << si << std::endl;
}

template<class DEType>
void PrintEmptySequenceOfItems()
{
  gdcm::SequenceOfItems<DEType> si;
  std::cout << si << std::endl;
}

int TestSequenceOfItems(int , char *[])
{
  TestInstanciation<gdcm::ExplicitDataElement>();
  TestInstanciation<gdcm::ImplicitDataElement>();

  PrintEmptySequenceOfItems<gdcm::ExplicitDataElement>();
  PrintEmptySequenceOfItems<gdcm::ImplicitDataElement>();

  typedef gdcm::ExplicitDataElement DEType;
  gdcm::SequenceOfItems<DEType> sde;
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
