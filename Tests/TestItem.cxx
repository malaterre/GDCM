#include "gdcmItem.txx"

template<class DEType>
void PrintEmptyItem()
{
  gdcm::Item<DEType> i(0);
  std::cout << i << std::endl;
}

template<class DEType>
void PrintEmptyUndefinedItem()
{
  gdcm::Item<DEType> i; //(0xFFFFFFFF);
  std::cout << i << std::endl;
}

template<class DEType>
void FillDummyValues(gdcm::Item<DEType> &item)
{
  DEType d;
  for(int i=0; i<10; ++i)
    {
    d.SetTag(gdcm::Tag(i,i));
//    if( i%2 ) d.SetVR( gdcm::VR::OB );
//    else      d.SetVR( gdcm::VR::OB );
    item.AddDataElement(d);
    }
}

template<class DEType>
void PrintItem()
{
  gdcm::Item<DEType> i(0);
  FillDummyValues(i);
  std::cout << i << std::endl;
}

template<class DEType>
void PrintUndefinedItem()
{
  gdcm::Item<DEType> i; //(0xFFFFFFFF);
  FillDummyValues(i);
  std::cout << i << std::endl;
}

int TestItem(int , char *[])
{
  std::cout << "Explicit" << std::endl;
  PrintEmptyItem<gdcm::ExplicitDataElement>();

  std::cout << "Implicit" << std::endl;
  PrintEmptyItem<gdcm::ImplicitDataElement>();

  std::cout << "Explicit" << std::endl;
  PrintEmptyUndefinedItem<gdcm::ExplicitDataElement>();

  std::cout << "Implicit" << std::endl;
  PrintEmptyUndefinedItem<gdcm::ImplicitDataElement>();

  std::cout << "Explicit" << std::endl;
  PrintItem<gdcm::ExplicitDataElement>();

  std::cout << "Implicit" << std::endl;
  PrintItem<gdcm::ImplicitDataElement>();

  std::cout << "Explicit" << std::endl;
  PrintUndefinedItem<gdcm::ExplicitDataElement>();

  std::cout << "Implicit" << std::endl;
  PrintUndefinedItem<gdcm::ImplicitDataElement>();

  return 0;
}
