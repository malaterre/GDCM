#include "gdcmTag.h"

int TestTag(int , char * [])
{
  gdcm::Tag t1;
  gdcm::Tag t2(0,0);
  if (t1[0] != 0 )
    return 1;
  if (t1[1] != 0 )
    return 1;
  if (t2[0] != 0 )
    return 1;
  if (t2[1] != 0 )
    return 1;
  if ( !(t1 == t2) )
    return 1;
  if ( t1 != t2 )
    return 1;
  if ( t1 < t2 )
    return 1;

  const uint16_t group = 0x1234;
  const uint16_t element = 0x5678;
  const gdcm::Tag t3(group, element);
  if( t3.GetGroup() != t3[0] )
    return 1;
  if( t3.GetElement() != t3[1] )
    return 1;
  if ( !(t3 == gdcm::Tag(group, element)) )
    return 1;
  if ( t3 != gdcm::Tag(group, element) )
    return 1;
  if( t3[0] == t3[1] )
    return 1;
  if( t3 < t1 )
    return 1;

  const uint32_t tag = 0x56781234;
  const gdcm::Tag t4(tag);
  if( t4.GetGroup() != group )
    return 1;
  if( t4.GetElement() != element )
    return 1;
  if ( !(t4 == gdcm::Tag(group, element)) )
    return 1;
  if ( t4 != gdcm::Tag(group, element) )
    return 1;
  if( t4[0] == t3[1] )
    return 1;
  if( t4 != t3 )
    return 1;
  if( !(t4 == t3) )
    return 1;
  if( t4.GetElementTag() != tag )
    return 1;
  if( t3 < t4 )
    return 1;

  std::cout << "T1: " << t1 << std::endl;
  std::cout << "T2: " << t2 << std::endl;
  std::cout << "T3: " << t3 << std::endl;
  std::cout << "T4: " << t4 << std::endl;

  return 0;
}
