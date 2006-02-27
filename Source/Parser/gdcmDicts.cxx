#include "gdcmDicts.h"

namespace gdcm
{

Dicts::Dicts()
{
  PublicType = DICOMV3_DICT;
  //PublicDicts.resize(3, Dict() );
}

Dicts::~Dicts()
{
}

void Dicts::AddPublicDict(const Dict& dict)
{
  (void)dict;
  //PublicDicts.push_back( dict );
}

void Dicts::SetPublicType(int type)
{
  PublicType = type;
}

const Dict &Dicts::GetPublicDict() const
{
  //assert( PublicType < PublicDicts.size() );
  return PublicDicts[PublicType];
}

void Dicts::AddPrivateDict(const Dict& dict)
{
  (void)dict;
  //PrivateDicts.push_back( dict );
}

void Dicts::SetPrivateType(const char *type)
{
  PrivateType = type;
}

const Dict &Dicts::GetPrivateDict()
{
  abort();
  return PrivateDicts[0];
}

} // end namespace gdcm
