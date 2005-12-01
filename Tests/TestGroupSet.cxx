#include "gdcmGroupSet.txx"
#include "gdcmGroup.txx"
#include "gdcmVR.h"

int TestGroupSet(int , char *[])
{
  typedef gdcm::ExplicitDataElement DEType;
  gdcm::GroupSet<DEType> gs;

  for(int i=0; i<=10; i+=2)
    {
    gdcm::Group<DEType> g(i);
    for(int j=0; j<=10; j++)
      {
      DEType de;
      de.SetTag(gdcm::Tag(i,j));
      de.SetVR( gdcm::VR::UL );
      g.AddDataElement(de);
      }
    gs.AppendGroup(g);
    }

  //std::cout << g << std::endl;
  std::cout << "Printing GroupSet:" << std::endl;
  //std::cout << gs << std::endl;


  // Test if Inserting a group works:
  gdcm::Group<DEType> g1(0x0001);
  gs.InsertGroup(g1);
  gdcm::Group<DEType> g23(0x0023);
  gs.InsertGroup(g23);
  gdcm::Group<DEType> g7(0x0007);
  gs.InsertGroup(g7);
  gdcm::Group<DEType> g8(0x0008);
  gs.InsertGroup(g8);

  //gs.AppendGroup(g8);

  //std::cout << gs << std::endl;

  gdcm::GroupSet<DEType>::ConstIterator it = gs.Begin();
  for(; it != gs.End();
    ++it)
    {
    std::cout << *it << std::endl;
    }

  return 0;
}
