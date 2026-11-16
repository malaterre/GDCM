/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmItem.h"
#include "gdcmReader.h"
#include "gdcmTrace.h"

#include <iostream>
#include <sstream>
#include <string>

// Builds an Explicit VR Little Endian Part 10 file in memory whose data set holds
// `depth` levels of nested Sequence of Items, all of undefined length.
namespace
{

void put16(std::string &s, unsigned int v)
{
  s += static_cast<char>(v & 0xff);
  s += static_cast<char>((v >> 8) & 0xff);
}

void put32(std::string &s, unsigned int v)
{
  put16(s, v & 0xffff);
  put16(s, (v >> 16) & 0xffff);
}

void putTag(std::string &s, unsigned int group, unsigned int element)
{
  put16(s, group);
  put16(s, element);
}

// Short-form explicit VR element; values are padded to even length with NUL.
void putShort(std::string &s, unsigned int group, unsigned int element,
  const char vr[2], std::string value)
{
  if( value.size() % 2 ) value += '\0';
  putTag(s, group, element);
  s += vr[0];
  s += vr[1];
  put16(s, static_cast<unsigned int>(value.size()));
  s += value;
}

std::string MakeNestedFile(unsigned int depth)
{
  std::string meta;
  {
  std::string ver;
  ver += '\0';
  ver += '\1';
  putTag(meta, 0x0002, 0x0001); // File Meta Information Version, OB
  meta += "OB";
  put16(meta, 0);
  put32(meta, 2);
  meta += ver;
  }
  putShort(meta, 0x0002, 0x0002, "UI", "1.2.840.10008.5.1.4.1.1.7");
  putShort(meta, 0x0002, 0x0003, "UI", "1.2.3.4");
  putShort(meta, 0x0002, 0x0010, "UI", "1.2.840.10008.1.2.1");

  std::string file(128, '\0');
  file += "DICM";
  putTag(file, 0x0002, 0x0000); // File Meta Information Group Length, UL
  file += "UL";
  put16(file, 4);
  put32(file, static_cast<unsigned int>(meta.size()));
  file += meta;

  putShort(file, 0x0008, 0x0016, "UI", "1.2.840.10008.5.1.4.1.1.7");
  putShort(file, 0x0008, 0x0018, "UI", "1.2.3.4");
  for( unsigned int i = 0; i < depth; ++i )
    {
    putTag(file, 0x0040, 0xa730); // Content Sequence, SQ, undefined length
    file += "SQ";
    put16(file, 0);
    put32(file, 0xffffffff);
    putTag(file, 0xfffe, 0xe000); // Item, undefined length
    put32(file, 0xffffffff);
    }
  for( unsigned int i = 0; i < depth; ++i )
    {
    putTag(file, 0xfffe, 0xe00d); // Item Delimitation Item
    put32(file, 0);
    putTag(file, 0xfffe, 0xe0dd); // Sequence Delimitation Item
    put32(file, 0);
    }
  return file;
}

bool ReadFromMemory(const std::string &file)
{
  std::istringstream is(file);
  gdcm::Reader reader;
  reader.SetStream(is);
  return reader.Read();
}

} // end namespace

int TestParseDepthGuard(int, char *[])
{
  int ret = 0;
  const unsigned int limit = gdcm::ParseDepthGuard::GetLimit();
  if( limit == 0 )
    {
    std::cerr << "default limit must not be 0" << std::endl;
    return 1;
    }

  // Nesting up to the limit reads normally.
  if( !ReadFromMemory( MakeNestedFile(limit) ) )
    {
    std::cerr << "depth " << limit << " should be readable" << std::endl;
    ++ret;
    }

  // Expected failures below log an error; keep the test output quiet.
  gdcm::Trace::ErrorOff();
  gdcm::Trace::WarningOff();

  // One level past the limit fails cleanly instead of being recovered by an
  // alternate decoder.
  if( ReadFromMemory( MakeNestedFile(limit + 1) ) )
    {
    std::cerr << "depth " << limit + 1 << " should be rejected" << std::endl;
    ++ret;
    }

  // Deep enough to exhaust the native stack without the guard.
  if( ReadFromMemory( MakeNestedFile(200000) ) )
    {
    std::cerr << "depth 200000 should be rejected" << std::endl;
    ++ret;
    }

  // A rejected read must leave the per-thread depth at zero: reading at the
  // limit has to work again afterwards.
  if( !ReadFromMemory( MakeNestedFile(limit) ) )
    {
    std::cerr << "depth counter not restored after a rejected read" << std::endl;
    ++ret;
    }

  // 0 is not a valid limit and leaves the current one in place.
  if( gdcm::ParseDepthGuard::SetLimit(0) || gdcm::ParseDepthGuard::GetLimit() != limit )
    {
    std::cerr << "SetLimit(0) must be ignored" << std::endl;
    ++ret;
    }

  // A raised limit takes effect.
  if( !gdcm::ParseDepthGuard::SetLimit(limit + 10)
    || !ReadFromMemory( MakeNestedFile(limit + 1) ) )
    {
    std::cerr << "raised limit not honoured" << std::endl;
    ++ret;
    }
  gdcm::ParseDepthGuard::SetLimit(limit);

  gdcm::Trace::ErrorOn();
  gdcm::Trace::WarningOn();
  return ret;
}
