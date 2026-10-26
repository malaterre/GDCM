/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmFragment.h"
#include "gdcmReader.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSwapper.h"
#include "gdcmConfigure.h"

#include <cstring>
#include <sstream>
#include <string>

#if defined(__has_feature)
#if __has_feature(address_sanitizer) || __has_feature(thread_sanitizer)
#define GDCM_TEST_SANITIZED
#endif
#endif
#if defined(__SANITIZE_ADDRESS__) || defined(__SANITIZE_THREAD__)
#define GDCM_TEST_SANITIZED
#endif

#if defined(__linux__) && !defined(GDCM_TEST_SANITIZED)
#define GDCM_TEST_LIMIT_ADDRESS_SPACE
#include <cstdio>
#include <sys/resource.h>
#include <unistd.h>
#endif

namespace
{
const uint32_t HugeLength = 0xfffffff0;

void WriteTag(std::ostream &os, uint16_t group, uint16_t element)
{
  os.write(reinterpret_cast<const char*>(&group), 2);
  os.write(reinterpret_cast<const char*>(&element), 2);
}

void WriteU32(std::ostream &os, uint32_t v)
{
  os.write(reinterpret_cast<const char*>(&v), 4);
}

void WriteExplicitOB(std::ostream &os, uint32_t vl)
{
  WriteTag(os, 0x0009, 0x1010);
  os.write("OB\0\0", 4);
  WriteU32(os, vl);
}

// Without a cap an allocation of HugeLength can succeed on a large machine
// and leave the old code path indistinguishable from the fixed one.
void LimitAddressSpace()
{
#if defined(GDCM_TEST_LIMIT_ADDRESS_SPACE)
  unsigned long pages = 0;
  if( FILE *f = std::fopen("/proc/self/statm", "r") )
    {
    if( std::fscanf(f, "%lu", &pages) != 1 ) pages = 0;
    std::fclose(f);
    }
  if( pages )
    {
    struct rlimit rl;
    rl.rlim_cur = rl.rlim_max =
      pages * static_cast<rlim_t>(sysconf(_SC_PAGESIZE)) + (rlim_t(1) << 30);
    setrlimit(RLIMIT_AS, &rl);
    }
#endif
}

bool IsAllocationFailure(const gdcm::Exception &ex)
{
  return std::strstr(ex.what(), "Impossible to allocate") != nullptr;
}

int TestExplicitHugeLength()
{
  std::stringstream ss;
  WriteExplicitOB(ss, HugeLength);
  ss.write("0123456789", 10);
  gdcm::ExplicitDataElement de;
  try
    {
    de.Read<gdcm::SwapperNoOp>(ss);
    }
  catch( const gdcm::ParseException & )
    {
    if( !ss.fail() || !ss.eof() )
      {
      std::cerr << "Explicit: stream not left as a short read leaves it" << std::endl;
      return 1;
      }
    return 0;
    }
  catch( const gdcm::Exception &ex )
    {
    std::cerr << "Explicit: " << (IsAllocationFailure(ex) ? "allocated " : "unexpected ")
      << ex.what() << std::endl;
    return 1;
    }
  std::cerr << "Explicit: read succeeded" << std::endl;
  return 1;
}

int TestImplicitHugeLength()
{
  std::stringstream ss;
  WriteTag(ss, 0x0009, 0x1010);
  WriteU32(ss, HugeLength);
  ss.write("0123456789", 10);
  gdcm::ImplicitDataElement de;
  try
    {
    de.Read<gdcm::SwapperNoOp>(ss);
    }
  catch( const gdcm::Exception &ex )
    {
    if( IsAllocationFailure(ex) )
      {
      std::cerr << "Implicit: allocated " << ex.what() << std::endl;
      return 1;
      }
    return 0;
    }
  std::cerr << "Implicit: read succeeded" << std::endl;
  return 1;
}

int TestFragmentHugeLength()
{
  std::stringstream ss;
  WriteTag(ss, 0xfffe, 0xe000);
  WriteU32(ss, HugeLength);
  ss.write("0123456789", 10);
  gdcm::Fragment frag;
  try
    {
    frag.Read<gdcm::SwapperNoOp>(ss);
    }
  catch( const gdcm::ParseException & )
    {
    // Decoders size buffers from the fragment length, so it must match the bytes kept.
    const gdcm::ByteValue *bv = frag.GetByteValue();
    if( frag.GetVL() != 10 || !bv || bv->GetLength() != 10
      || std::memcmp(bv->GetPointer(), "0123456789", 10) != 0 )
      {
      std::cerr << "Fragment: truncated fragment has VL " << frag.GetVL() << ", expected the 10 bytes that remain" << std::endl;
      return 1;
      }
    return 0;
    }
  catch( const gdcm::Exception &ex )
    {
    std::cerr << "Fragment: " << ex.what() << std::endl;
    return 1;
    }
  std::cerr << "Fragment: read succeeded" << std::endl;
  return 1;
}

// The fragment keeps the bytes that remain, an odd count rounded down
// where ByteValue rejects odd lengths.
int TestFragmentRemainder(const std::string &tail, bool backtrack)
{
  std::stringstream ss;
  WriteTag(ss, 0xfffe, 0xe000);
  WriteU32(ss, HugeLength);
  ss.write(tail.data(), tail.size());
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  const size_t kept = tail.size();
#else
  const size_t kept = tail.size() & ~size_t(1);
#endif
  gdcm::Fragment frag;
  try
    {
    if( backtrack )
      frag.ReadBacktrack<gdcm::SwapperNoOp>(ss);
    else
      frag.Read<gdcm::SwapperNoOp>(ss);
    }
  catch( const gdcm::ParseException & )
    {
    const gdcm::ByteValue *bv = frag.GetByteValue();
    if( frag.GetVL() != kept || !bv || bv->GetLength() != kept
      || std::memcmp(bv->GetPointer(), tail.data(), kept) != 0 )
      {
      std::cerr << "Fragment remainder " << tail.size() << (backtrack ? " (backtrack)" : "")
        << ": VL " << frag.GetVL() << ", expected " << kept << std::endl;
      return 1;
      }
    return 0;
    }
  catch( const gdcm::Exception &ex )
    {
    std::cerr << "Fragment remainder " << tail.size() << ": " << ex.what() << std::endl;
    return 1;
    }
  std::cerr << "Fragment remainder " << tail.size() << ": read succeeded" << std::endl;
  return 1;
}

void WriteExplicitElement(std::ostream &os, uint16_t group, uint16_t element,
                          const char *vr, const std::string &value)
{
  WriteTag(os, group, element);
  os.write(vr, 2);
  const uint16_t vl = static_cast<uint16_t>(value.size());
  os.write(reinterpret_cast<const char*>(&vl), 2);
  os.write(value.data(), value.size());
}

// gdcm::Reader keeps a truncated last fragment with a length that matches its bytes.
int TestReaderTruncatedLastFragment()
{
  const std::string ts = "1.2.840.10008.1.2.4.50";
  std::stringstream ss;
  ss.write(std::string(128, '\0').data(), 128);
  ss.write("DICM", 4);
  WriteExplicitElement(ss, 0x0002, 0x0010, "UI", ts);
  WriteTag(ss, 0x7fe0, 0x0010);
  ss.write("OB\0\0", 4);
  WriteU32(ss, 0xffffffff);
  WriteTag(ss, 0xfffe, 0xe000);
  WriteU32(ss, 0);
  WriteTag(ss, 0xfffe, 0xe000);
  WriteU32(ss, 4);
  ss.write("\xff\xd8\xff\xd9", 4);
  WriteTag(ss, 0xfffe, 0xe000);
  WriteU32(ss, HugeLength);
  ss.write("0123456789", 10);

  gdcm::Reader reader;
  reader.SetStream(ss);
  try
    {
    if( !reader.Read() )
      {
      std::cerr << "Reader: Read failed" << std::endl;
      return 1;
      }
    }
  catch( const gdcm::Exception &ex )
    {
    std::cerr << "Reader: " << ex.what() << std::endl;
    return 1;
    }
  const gdcm::DataSet &ds = reader.GetFile().GetDataSet();
  if( !ds.FindDataElement(gdcm::Tag(0x7fe0,0x0010)) )
    {
    std::cerr << "Reader: no Pixel Data" << std::endl;
    return 1;
    }
  const gdcm::SequenceOfFragments *sqf =
    ds.GetDataElement(gdcm::Tag(0x7fe0,0x0010)).GetSequenceOfFragments();
  if( !sqf || sqf->GetNumberOfFragments() != 2 )
    {
    std::cerr << "Reader: expected 2 fragments, have "
      << (sqf ? sqf->GetNumberOfFragments() : 0) << std::endl;
    return 1;
    }
  const gdcm::Fragment &last = sqf->GetFragment(1);
  const gdcm::ByteValue *bv = last.GetByteValue();
  if( last.GetVL() != 10 || !bv || bv->GetLength() != 10
    || std::memcmp(bv->GetPointer(), "0123456789", 10) != 0 )
    {
    std::cerr << "Reader: last fragment has VL " << last.GetVL() << ", expected 10" << std::endl;
    return 1;
    }
  return 0;
}

// A length that overruns what remains but fits in the stream keeps the
// historical read-then-fail behavior.
int TestOverrunWithinStream()
{
  const std::string prefix(4 * 1024 * 1024, '\0');
  std::stringstream ss;
  ss.write(prefix.data(), prefix.size());
  WriteExplicitOB(ss, 3 * 1024 * 1024);
  ss.write(prefix.data(), 1024 * 1024);
  ss.seekg(prefix.size());
  gdcm::ExplicitDataElement de;
  try
    {
    de.Read<gdcm::SwapperNoOp>(ss);
    }
  catch( const gdcm::ParseException & )
    {
    return 0;
    }
  std::cerr << "Overrun: expected a ParseException" << std::endl;
  return 1;
}

int TestTruncatedPixelData()
{
#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
  std::stringstream ss;
  WriteTag(ss, 0x7fe0, 0x0010);
  ss.write("OW\0\0", 4);
  WriteU32(ss, 8 * 1024 * 1024);
  ss.write("0123456789", 10);
  gdcm::ExplicitDataElement de;
  try
    {
    de.Read<gdcm::SwapperNoOp>(ss);
    }
  catch( const gdcm::Exception &ex )
    {
    std::cerr << "Truncated Pixel Data: " << ex.what() << std::endl;
    return 1;
    }
  if( de.GetVL() != 10 )
    {
    std::cerr << "Truncated Pixel Data: VL " << de.GetVL() << ", expected 10" << std::endl;
    return 1;
    }
#endif
  return 0;
}

int TestLargeValueStillReads()
{
  const uint32_t vl = 2 * 1024 * 1024;
  const std::string payload(vl, 'x');
  std::stringstream ss;
  WriteExplicitOB(ss, vl);
  ss.write(payload.data(), payload.size());
  WriteExplicitOB(ss, 2);
  ss.write("ok", 2);
  gdcm::ExplicitDataElement de1, de2;
  try
    {
    de1.Read<gdcm::SwapperNoOp>(ss);
    de2.Read<gdcm::SwapperNoOp>(ss);
    }
  catch( const gdcm::Exception &ex )
    {
    std::cerr << "Large value: " << ex.what() << std::endl;
    return 1;
    }
  const gdcm::ByteValue *bv = de2.GetByteValue();
  if( de1.GetVL() != vl || !bv || std::memcmp(bv->GetPointer(), "ok", 2) != 0 )
    {
    std::cerr << "Large value: stream position not restored" << std::endl;
    return 1;
    }
  return 0;
}
} // end anonymous namespace

int TestCVE20263650(int, char *[])
{
  LimitAddressSpace();
  int ret = 0;
  ret += TestExplicitHugeLength();
  ret += TestImplicitHugeLength();
  ret += TestFragmentHugeLength();
  ret += TestFragmentRemainder("012345678", false);
  ret += TestFragmentRemainder("", false);
  ret += TestFragmentRemainder("0123456789", true);
  ret += TestReaderTruncatedLastFragment();
  ret += TestOverrunWithinStream();
  ret += TestTruncatedPixelData();
  ret += TestLargeValueStillReads();
  return ret;
}
