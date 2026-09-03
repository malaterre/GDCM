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
#include "gdcmSwapper.h"

#include <sstream>
#include <new>

// CVE-2026-3650: Verify that crafted DICOM data elements with a Value Length
// exceeding the remaining stream size are rejected without attempting the
// allocation.

static int TestExplicitVR()
{
  // Explicit VR data element: Tag (0008,0060), VR = OB, VL = 1 GB, 10 bytes data
  std::stringstream ss;
  const uint16_t group = 0x0008;
  const uint16_t element = 0x0060;
  ss.write(reinterpret_cast<const char*>(&group), 2);
  ss.write(reinterpret_cast<const char*>(&element), 2);
  ss.write("OB", 2);
  const uint16_t reserved = 0;
  ss.write(reinterpret_cast<const char*>(&reserved), 2);
  const uint32_t vl = 0x40000000;
  ss.write(reinterpret_cast<const char*>(&vl), 4);
  const char data[10] = {};
  ss.write(data, sizeof(data));

  gdcm::ExplicitDataElement de;
  try
    {
    de.Read<gdcm::SwapperNoOp>(ss);
    std::cerr << "ERROR: ExplicitDataElement::Read should have thrown" << std::endl;
    return 1;
    }
  catch(const gdcm::Exception &)
    {
    return 0;
    }
  catch(const std::bad_alloc &)
    {
    std::cerr << "ERROR: ExplicitDataElement allocated memory for oversized VL" << std::endl;
    return 1;
    }
  catch(...)
    {
    std::cerr << "ERROR: ExplicitDataElement::Read threw unexpected exception" << std::endl;
    return 1;
    }
}

static int TestImplicitVR()
{
  // Implicit VR data element: Tag (0008,0060), VL = 1 GB, 10 bytes data
  std::stringstream ss;
  const uint16_t group = 0x0008;
  const uint16_t element = 0x0060;
  ss.write(reinterpret_cast<const char*>(&group), 2);
  ss.write(reinterpret_cast<const char*>(&element), 2);
  const uint32_t vl = 0x40000000;
  ss.write(reinterpret_cast<const char*>(&vl), 4);
  const char data[10] = {};
  ss.write(data, sizeof(data));

  gdcm::ImplicitDataElement de;
  try
    {
    de.Read<gdcm::SwapperNoOp>(ss);
    std::cerr << "ERROR: ImplicitDataElement::Read should have thrown" << std::endl;
    return 1;
    }
  catch(const gdcm::Exception &)
    {
    return 0;
    }
  catch(const std::bad_alloc &)
    {
    std::cerr << "ERROR: ImplicitDataElement allocated memory for oversized VL" << std::endl;
    return 1;
    }
  catch(...)
    {
    std::cerr << "ERROR: ImplicitDataElement::Read threw unexpected exception" << std::endl;
    return 1;
    }
}

static int TestFragment()
{
  // Fragment: Item tag (fffe,e000), VL = 1 GB, 10 bytes data
  std::stringstream ss;
  const uint16_t group = 0xfffe;
  const uint16_t element = 0xe000;
  ss.write(reinterpret_cast<const char*>(&group), 2);
  ss.write(reinterpret_cast<const char*>(&element), 2);
  const uint32_t vl = 0x40000000;
  ss.write(reinterpret_cast<const char*>(&vl), 4);
  const char data[10] = {};
  ss.write(data, sizeof(data));

  gdcm::Fragment frag;
  try
    {
    frag.Read<gdcm::SwapperNoOp>(ss);
    std::cerr << "ERROR: Fragment::Read should have thrown" << std::endl;
    return 1;
    }
  catch(const gdcm::Exception &)
    {
    return 0;
    }
  catch(const std::bad_alloc &)
    {
    std::cerr << "ERROR: Fragment allocated memory for oversized VL" << std::endl;
    return 1;
    }
  catch(...)
    {
    std::cerr << "ERROR: Fragment::Read threw unexpected exception" << std::endl;
    return 1;
    }
}

int TestCVE20263650(int, char *[])
{
  int ret = 0;
  ret += TestExplicitVR();
  ret += TestImplicitVR();
  ret += TestFragment();
  return ret;
}
