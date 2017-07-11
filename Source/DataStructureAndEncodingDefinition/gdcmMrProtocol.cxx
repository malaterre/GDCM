/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmMrProtocol.h"

#include <map>

namespace gdcm
{

struct MrProtocol::Element {
};

typedef std::map< std::string, std::string > MyMapType;
struct MrProtocol::Internals {
  MyMapType mymap;
  int version;
};

MrProtocol::MrProtocol( const ByteValue * bv, int version )
{
  if( bv )
  {
    std::string str(bv->GetPointer(), bv->GetLength());
    std::istringstream is(str);
    std::string s;
    Pimpl = new MrProtocol::Internals;
    Pimpl->version = version;
    MyMapType &mymap = Pimpl->mymap;
    while( std::getline(is, s ) )
    {
      std::string::size_type pos = s.find( '=' );
      if( pos != std::string::npos )
      {
        std::string sub1 = s.substr(0, pos);
        sub1.erase( sub1.find_last_not_of(' ') + 1);
        std::string sub2 = s.substr(pos+1); // skip the '=' char
        sub2.erase( 0, sub2.find_first_not_of(' '));
        //std::cout << sub1 << std::endl;
        mymap.insert( MyMapType::value_type(sub1, sub2) );
      }
      else
      {
        // ### ASCCONV BEGIN ###
        // ### ASCCONV END ###
      }
    }
  }
  else
  {
    Pimpl = NULL;
  }
}

MrProtocol::~MrProtocol()
{
  delete Pimpl;
}

int MrProtocol::GetVersion() const
{
  return 0;
}

static inline std::string trim(std::string str)
{
  str.erase(0, str.find_first_not_of('"'));
  str.erase(str.find_last_not_of('"')+1);
  return str;
}

void MrProtocol::Print(std::ostream &os) const
{
  if( Pimpl )
  {
    os << "MrProtocolVersion: " << Pimpl->version << std::endl;
    MyMapType &mymap = Pimpl->mymap;
    for( MyMapType::const_iterator it = mymap.begin();
        it != mymap.end(); ++it)
    {
      os << it->first << " : " << trim(std::string(it->second)) << std::endl;
    }
  }
}

const char * MrProtocol::GetMrProtocolByName(const char *name)
{
  if( name )
  {
    MyMapType &mymap = Pimpl->mymap;
    MyMapType::const_iterator it = mymap.find ( name );
    if( it == mymap.end() ) return NULL;
    return it->second.c_str();
  }
  return NULL;
}

bool MrProtocol::FindMrProtocolByName(const char *name)
{
  if( name )
  {
    MyMapType &mymap = Pimpl->mymap;
    MyMapType::const_iterator it = mymap.find ( name );
    if( it != mymap.end() ) return true;
  }
  return false;
}

} // end namespace gdcm
