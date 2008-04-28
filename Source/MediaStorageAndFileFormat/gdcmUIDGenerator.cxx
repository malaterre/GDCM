/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmUIDGenerator.h"
#include "gdcmTrace.h"
#include "gdcmSystem.h"

#include "uuid/uuid.h"

namespace gdcm
{

const char UIDGenerator::GDCM_UID[] = "1.2.826.0.1.3680043.2.1143";
std::string UIDGenerator::Root = GetGDCMUID();
// The following contains the *encoded* hardware address (not the raw as in ipconfig/ifconfig)
std::string UIDGenerator::EncodedHardwareAddress; // = System::GetHardwareAddress();

const char *UIDGenerator::GetGDCMUID()
{
  return GDCM_UID;
}

const char* UIDGenerator::Generate()
{
  Unique = GetRoot();
  if( Unique.empty() )
    {
    // Seriously...
    return NULL;
    }
  // We need to convert a 6 digit number from base 256 to base 10, using integer
  // would requires a 48bits one. To avoid this we have to reimplement the div + modulo 
  // with string only
  if( EncodedHardwareAddress.empty() )
    {
    unsigned char node[6];
    int res = System::GetHardwareAddress(node);
    assert( res );
    char buffer[15]; // 15 is max possible when all node[i] == 255
    int len = System::EncodeBytes(buffer, node, sizeof(node));
    assert( strlen(buffer) < 15 );
    EncodedHardwareAddress = buffer;
    if( EncodedHardwareAddress.empty() )
      {
      // ethernet cable is not plugged, do not allow creating UIDs
      return NULL;
      }
    }
  assert( !EncodedHardwareAddress.empty() ); // programmer error
  Unique += ".";
  Unique += EncodedHardwareAddress;
  Unique += ".";
  char datetime[18];
  int res = System::GetCurrentDateTime(datetime);
  if( !res )
    {
    // Not sure how this is supposed to happen...
    return NULL;
    }
  assert( strlen(datetime) < 18 );
  Unique += datetime;
  // Also add a mini random number just in case:
  // FIXME: I choose 2 bytes for the random number, since GDCM Root UID is so long, and harware address can take up
  // to 15 bytes, case 255.255.255.255.255.255 <-> 281474976710655
  // But a better approach to dynamically calculate the max size for random bits...
  uuid_t out;
  uuid_generate(out);
  char randbytesbuf[40];
  res = System::EncodeBytes(randbytesbuf, out, sizeof(out));
  assert( strlen(randbytesbuf) < 40 );
  std::string randbytes = randbytesbuf;

  Unique += ".";
  std::string::size_type len = Unique.size();
  std::string::size_type rb_len = randbytes.size();
  if( randbytes.empty() )
    {
    // That's bad...
    return NULL;
    }
  assert( len < 64 );
  // randbytes might be a little too long, let's check
  // if too long: take the lower bits
  randbytes = randbytes.substr( rb_len - (64 - len) , 64 - len );

  std::string::size_type zeropos = randbytes.find_first_not_of('0');
#define RAND_VERSION
#ifdef RAND_VERSION
  if( zeropos == std::string::npos )
    {
    // All 0 ...
    Unique += "0";
    }
  else
    {
    // Takes everything after the 0
    Unique += randbytes.c_str() + zeropos;
    }
#else
  pid_t processid = getpid();
  std::ostringstream os;
  os << processid;
  Unique += os.str();
  Unique += ".";
  os.str("");
  pthread_t threadid = pthread_self();
  os << threadid;
  Unique += os.str();
#endif

  assert( IsValid( Unique.c_str() ) );

  return Unique.c_str();
}

bool UIDGenerator::IsValid(const char *uid_)
{
  /*
  9.1 UID ENCODING RULES
  The DICOM UID encoding rules are defined as follows:
  - Each component of a UID is a number and shall consist of one or more digits. The first digit of
  each component shall not be zero unless the component is a single digit.
  Note: Registration authorities may distribute components with non-significant leading zeroes. The leading
  zeroes should be ignored when being encoded (ie. ¿00029¿ would be encoded ¿29¿).
  - Each component numeric value shall be encoded using the characters 0-9 of the Basic G0 Set
  of the International Reference Version of ISO 646:1990 (the DICOM default character
  repertoire).
  - Components shall be separated by the character "." (2EH).
  - If ending on an odd byte boundary, except when used for network negotiation (See PS 3.8),
  one trailing NULL (00H), as a padding character, shall follow the last component in order to
  align the UID on an even byte boundary.
  - UID's, shall not exceed 64 total characters, including the digits of each component, separators
  between components, and the NULL (00H) padding character if needed.
  */

  /*
   * FIXME: This is not clear in the standard, but I believe a trailing '.' is not allowed since
   * this is considered as a separator for components
   */

  std::string uid = uid_;
  if( uid.size() > 64 )
    {
    return false;
    }
  if( uid[uid.size()-1] == '.' ) // important to do that first
    {
    return false;
    }
  std::string::size_type i = 0;
  for(; i < uid.size(); ++i)
    {
    if( uid[i] == '.' ) // if test is true we are garantee that next char is valid (see previous check)
      {
      // check that next character is neither '0' (except single number) not '.'
      if( uid[i+1] == '.' )
        {
        return false;
        }
      else if( uid[i+1] == '0' ) // character is garantee to exist since '.' is not last char
        {
        // Need to check first if we are not at the end of string
        if( i+2 != uid.size() && uid[i+2] != '.' )
          {
          return false;
          }
        }
      }
    else if ( !isdigit( (unsigned char)uid[i] ) )
      {
      return false;
      }
    }
  // no error found !
  return true;
}


} // end namespace gdcm
