/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*
 * Test for CVE-2025-52582 / SourceForge bug #575.
 *
 * GrabOverlayFromPixelData used to compute the loop end pointer from
 * Rows*Columns without checking against the actual pixel data buffer
 * size, causing an out-of-bounds read when a malformed DICOM file
 * provides a small pixel data element but large overlay dimensions.
 *
 * This test confirms that both the 8-bit and 16-bit paths reject the
 * mismatch gracefully (return false) instead of reading past the buffer.
 */
#include "gdcmOverlay.h"
#include "gdcmDataSet.h"
#include "gdcmDataElement.h"
#include "gdcmTag.h"
#include "gdcmByteValue.h"

#include <vector>
#include <iostream>

static int TestGrabOverlay8BitOOB()
{
  // Set up an overlay claiming 64x64 pixels (ovlength = 64*64/8 = 512,
  // loop length = 512*8 = 4096 bytes) but provide only 16 bytes of pixel
  // data.  Without the fix the loop would read 4096 bytes starting at a
  // 16-byte buffer.
  gdcm::Overlay ov;
  ov.SetGroup(0x6000);
  ov.SetRows(64);
  ov.SetColumns(64);
  ov.SetBitsAllocated(8);
  ov.SetBitPosition(0);

  // Build a DataSet with a tiny PixelData element
  gdcm::DataSet ds;
  gdcm::DataElement pixelDE(gdcm::Tag(0x7fe0, 0x0010));
  std::vector<char> tinyBuf(16, 0); // 16 bytes, much smaller than needed
  pixelDE.SetByteValue(tinyBuf.data(), gdcm::VL(static_cast<uint32_t>(tinyBuf.size())));
  ds.Insert(pixelDE);

  // Must return false — the buffer is too small
  if (ov.GrabOverlayFromPixelData(ds))
    {
    std::cerr << "TestGrabOverlay8BitOOB: expected failure but got success" << std::endl;
    return 1;
    }
  return 0;
}

static int TestGrabOverlay16BitOOB()
{
  // 16-bit path: overlay 64x64, loop needs 512*8*2 = 8192 bytes but
  // buffer is only 32 bytes.
  gdcm::Overlay ov;
  ov.SetGroup(0x6000);
  ov.SetRows(64);
  ov.SetColumns(64);
  ov.SetBitsAllocated(16);
  ov.SetBitPosition(12);

  gdcm::DataSet ds;
  gdcm::DataElement pixelDE(gdcm::Tag(0x7fe0, 0x0010));
  std::vector<char> tinyBuf(32, 0);
  pixelDE.SetByteValue(tinyBuf.data(), gdcm::VL(static_cast<uint32_t>(tinyBuf.size())));
  ds.Insert(pixelDE);

  if (ov.GrabOverlayFromPixelData(ds))
    {
    std::cerr << "TestGrabOverlay16BitOOB: expected failure but got success" << std::endl;
    return 1;
    }
  return 0;
}

static int TestGrabOverlayValidSmall()
{
  // Sanity: a valid small overlay should still succeed.
  // 8x8 overlay, BitsAllocated=8 → ovlength=8, loop needs 64 bytes.
  gdcm::Overlay ov;
  ov.SetGroup(0x6000);
  ov.SetRows(8);
  ov.SetColumns(8);
  ov.SetBitsAllocated(8);
  ov.SetBitPosition(0);

  gdcm::DataSet ds;
  gdcm::DataElement pixelDE(gdcm::Tag(0x7fe0, 0x0010));
  std::vector<char> buf(64, 0); // exactly the right size
  pixelDE.SetByteValue(buf.data(), gdcm::VL(static_cast<uint32_t>(buf.size())));
  ds.Insert(pixelDE);

  if (!ov.GrabOverlayFromPixelData(ds))
    {
    std::cerr << "TestGrabOverlayValidSmall: expected success but got failure" << std::endl;
    return 1;
    }
  return 0;
}

int TestOverlayGrabOOB(int, char *[])
{
  int ret = 0;
  ret += TestGrabOverlay8BitOOB();
  ret += TestGrabOverlay16BitOOB();
  ret += TestGrabOverlayValidSmall();
  return ret;
}
