/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmVR.h"

#include <string>

static int TestEnumString(std::string const & rep, gdcm::VR::VRType vr)
{
  const std::string & odstr = rep;
  gdcm::VR::VRType od = gdcm::VR::GetVRTypeFromFile(odstr.c_str());
  if( od != vr ) return 1;
  const char *odcstr = gdcm::VR::GetVRStringFromFile(vr);
  if( odstr != odcstr ) return 1;
  od = gdcm::VR::GetVRType(odstr.c_str());
  if( od != vr ) return 1;
  odcstr = gdcm::VR::GetVRString(vr);
  if( !gdcm::VR::IsValid(odstr.c_str())) return 1;
  return 0;
}

// Not used...
int verify()
{
  // avoid INVALID = 0
  for(int i = 1; i < 27; ++i)
    {
    gdcm::VR t = (gdcm::VR::VRType)(1 << i);
    if( gdcm::VR::IsASCII( t ) != gdcm::VR::IsASCII2( t ) )
      {
      std::cerr << t << std::endl;
      return 1;
      }
    //if( gdcm::VR::IsBinary( t ) != gdcm::VR::IsBinary2( t ) )
    //  {
    //  std::cerr << t << std::endl;
    ////  return 1;
    //  }
    }
  return 0;
}

int TestValue()
{
  int k = 0;
  gdcm::VR vr;
  vr = gdcm::VR::INVALID; // = 0,
  if( (int)vr != 0 )
    return 1;
  vr = gdcm::VR::AE; // = 1,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::AS; // = 2,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::AT; // = 4,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::CS; // = 8,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::DA; // = 16,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::DS; // = 32,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::DT; // = 64,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::FD; // = 256,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::FL; // = 128,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::IS; // = 512,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::LO; // = 1024,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::LT; // = 2048,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::OB; // = 4096,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::OF; // = 8192,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::OW; // = 16384,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::PN; // = 32768,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::SH; // = 65536,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::SL; // = 131072,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::SQ; // = 262144,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::SS; // = 524288,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::ST; // = 1048576,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::TM; // = 2097152,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::UI; // = 4194304,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::UL; // = 8388608,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::UN; // = 16777216,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::US; // = 33554432,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::UT; // = 67108864,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::OD; // = 134217728,
  if( (int)vr != (1 << k++) )
    return 1;
  vr = gdcm::VR::OL; // = 268435456,
  if( (int)vr != (1 << k++) )
    return 1;

  return 0;
}

int TestVR(int, char *[])
{
  enum {
   V1 = 0ULL,
   V2 = 4294967295ULL
  } E4;
  std::cout << sizeof E4 << std::endl;
  enum {
   V3 = 0ULL,
   V4 = 4294967296ULL
  } E8;
  enum : long long {
   V5 = 0ULL,
   V6 = 4294967296ULL
  } E8ll;
  std::cout << sizeof E8 << std::endl;
  if( sizeof E4 != 4 ) {
    std::cerr << "E4 is: " << sizeof E4 << std::endl;
    return 1;
  }
  if( sizeof E8 != 8 ) {
    // bad bad compiler
    std::cerr << "E8 is: " << sizeof E8 << std::endl;
  }
  if( sizeof E8ll != 8 ) {
    std::cerr << "E8ll is: " << sizeof E8 << std::endl;
    return 1;
  }

  if( TestValue() )
    return 1;

  gdcm::VR vr = gdcm::VR::INVALID;
  const char *inv = gdcm::VR::GetVRString(vr);
  std::cout << 0 << "," << inv << std::endl;
  int i;
  for(i=0; i<27; i++)
    {
    int j = 1 << i;
    //int k = gdcm::VR::GetIndex((gdcm::VR::VRType)j);
    std::cout << "2^" << i << "=" << (int)j << "," << gdcm::VR::GetVRString((gdcm::VR::VRType)j) << std::endl;
    }

  vr = gdcm::VR::OB_OW;
  //int k = gdcm::VR::GetIndex(vr);
  std::cout << i++ << "," << gdcm::VR::GetVRString(vr) << std::endl;
  vr = gdcm::VR::US_SS;
  //k = gdcm::VR::GetIndex(vr);
  std::cout << i++ << "," << gdcm::VR::GetVRString(vr) << std::endl;
  vr = gdcm::VR::US_SS_OW;
  //k = gdcm::VR::GetIndex(vr);
  std::cout << i++ << "," << gdcm::VR::GetVRString(vr) << std::endl;

  std::string s = "OB";
  vr = gdcm::VR::GetVRType(s.c_str());
  if( s != gdcm::VR::GetVRString(vr))
    return 1;
  s = "UT";
  vr = gdcm::VR::GetVRType(s.c_str());
  if( s != gdcm::VR::GetVRString(vr))
    return 1;
  std::string s2 = "OB or OW";
  gdcm::VR ob_ow = gdcm::VR::OB_OW;
  vr = gdcm::VR::GetVRType(s2.c_str());
  if( vr != ob_ow )
    return 1;
  if( s2 != gdcm::VR::GetVRString(vr))
    return 1;
  // Check that "OB" is in "OB or OW"
  s = "OB";
  if( !gdcm::VR::IsValid(s.c_str(), vr) )
    return 1;
  std::string s3 = "US or SS or OW";
  vr = gdcm::VR::GetVRType(s3.c_str());
  // Check that "OB" is not in "US or SS or OW"
  if( gdcm::VR::IsValid(s.c_str(), vr) )
    return 1;
  s = "XX"; //invalid
  vr = gdcm::VR::GetVRType(s.c_str());
  if( vr != gdcm::VR::VR_END )
    return 1;
  const char *t = gdcm::VR::GetVRString(vr);
  if( t != nullptr )
    return 1;

  s = "??"; //invalid
  vr = gdcm::VR::GetVRType(s.c_str());
  if( vr != gdcm::VR::INVALID)
    return 1;

  // Test Partial Match
  s = "US or SS";
  vr = gdcm::VR::GetVRType(s.c_str());
  if( vr == gdcm::VR::US )
    return 1;

{
  vr = gdcm::VR::AE;
  if( vr & gdcm::VR::VRASCII )
    {
    std::cout << vr << " is ASCII\n";
    }
  else
    {
    return 1;
    }
  vr = gdcm::VR::UI;
  if( vr & gdcm::VR::VRASCII )
    {
    std::cout << vr << " is ASCII\n";
    }
  else
    {
    return 1;
    }
  vr = gdcm::VR::OB;
  if( vr & gdcm::VR::VRBINARY )
    {
    std::cout << vr << " is Binary\n";
    }
  else
    {
    return 1;
    }
  vr = gdcm::VR::UI;
  if( vr & (gdcm::VR::OB | gdcm::VR::OF | gdcm::VR::OW /*| gdcm::VR::SQ*/ | gdcm::VR::UN) )
    {
    return 1;
    }
}


  // Let's check the & operator
{
  vr = gdcm::VR::OB;
  if( !( vr.Compatible( gdcm::VR::OB_OW ) ) )
    {
    return 1;
    }
//  if( !( vr.Compatible( gdcm::VR::INVALID) ) )
//    {
//    return 1;
//    }
}
  // Make sure VR::UT is the last valid VR that can be found in a file:
  //if( gdcm::VR::OB_OW <= gdcm::VR::UT ) return 1;
  //else if( gdcm::VR::US_SS <= gdcm::VR::UT ) return 1;
  //else if( gdcm::VR::US_SS_OW <= gdcm::VR::UT ) return 1;
  //else if( gdcm::VR::VL32 <= gdcm::VR::UT ) return 1;

  if( TestEnumString("OD", gdcm::VR::OD ) == 1 ) return 1;
  if( TestEnumString("OL", gdcm::VR::OL ) == 1 ) return 1;
  if( TestEnumString("UC", gdcm::VR::UC ) == 1 ) return 1;
  if( TestEnumString("UR", gdcm::VR::UR ) == 1 ) return 1;
  if( TestEnumString("OV", gdcm::VR::OV ) == 1 ) return 1;
  if( TestEnumString("SV", gdcm::VR::SV ) == 1 ) return 1;
  if( TestEnumString("UV", gdcm::VR::UV ) == 1 ) return 1;

  return 0;
}
