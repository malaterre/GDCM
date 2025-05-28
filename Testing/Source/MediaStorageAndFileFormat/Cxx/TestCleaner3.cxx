/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmCleaner.h"
#include "gdcmFilename.h"
#include "gdcmReader.h"
#include "gdcmSmartPointer.h"
#include "gdcmSystem.h"
#include "gdcmTesting.h"
#include "gdcmWriter.h"

namespace gdcm {
static const DataSet &GetNestedDataSet(const DataSet &ds,
                                       const PrivateTag &path) {
  const DataElement &de = ds.GetDataElement(path);
  SmartPointer<SequenceOfItems> sqi = de.GetValueAsSQ();
  gdcm_assert(sqi && sqi->GetNumberOfItems() == 1);
  const Item &item = sqi->GetItem(1);
  const DataSet &subds = item.GetNestedDataSet();
  return subds;
}
static bool IsTagIn(const DataSet &ds, const PrivateTag &path,
                    const PrivateTag &pt) {
  const DataSet &subds = GetNestedDataSet(ds, path);
  return subds.FindDataElement(pt);
}
}  // namespace gdcm

int TestCleaner3Impl(std::string const &filename,
                     std::string const &outfilename, bool useDPath) {
  using namespace gdcm;

  // Setup DPath
  DPath dpath1, dpath2;
  PrivateTag pt1, pt2;
  // This attribute is a SQ. make sure we can Empty a SQ:
  static const char ref1[] = "0029,e0,SPI-P-Private_ICS Release 1;4";
  static const char ref2[] = "0029,00,SPI-P-Private_ICS Release 1;1";
  if (useDPath) {
    if (!dpath1.ConstructFromString(ref1)) {
      return 1;
    }
    if (!dpath2.ConstructFromString(ref2)) {
      return 1;
    }
  }
  if (!pt1.ReadFromCommaSeparatedString(ref1)) {
    return 1;
  }
  if (!pt2.ReadFromCommaSeparatedString(ref2)) {
    return 1;
  }
  PrivateTag path1(0x0029, 0xf, "SPI-P-Private_ICS Release 1");
  PrivateTag path2(0x0029, 0xcd, "SPI-P-Private_ICS Release 1;1");
  PrivateTag path3(0x0029, 0x1b, "SPI-P-Private_ICS Release 1");
  PrivateTag path4(0x0029, 0x4c, "SPI-P-Private_ICS Release 1");
  // first pass
  {
    Reader reader;
    reader.SetFileName(filename.c_str());
    if (!reader.Read()) {
      std::cerr << "Could not read: " << filename << std::endl;
      return 1;
    }

    File &file = reader.GetFile();
    DataSet &ds = file.GetDataSet();

    const bool b0 = IsTagIn(ds, path4, pt1);

    const bool b1 = IsTagIn(ds, path1, pt2);
    const DataSet &ds1 = GetNestedDataSet(ds, path1);
    const bool b2 = IsTagIn(ds1, path2, pt2);
    const bool b3 = IsTagIn(ds, path3, pt2);
    const bool b4 = IsTagIn(ds, path4, pt2);
    if (!b0 || !b1 || !b2 || !b3 || !b4) {
      std::cerr << "Test not setup correctly" << std::endl;
      return 1;
    }

    Cleaner cleaner;
    cleaner.SetFile(file);
    cleaner.RemoveAllGroupLength(false);
    if (useDPath) {
      if (!cleaner.Remove(dpath1)) {
        return 1;
      }
      if (!cleaner.Remove(dpath2)) {
        return 1;
      }
    } else {
      if (!cleaner.Remove(pt1)) {
        return 1;
      }
      if (!cleaner.Remove(pt2)) {
        return 1;
      }
    }
    if (!cleaner.Clean()) {
      return 1;
    }

    Writer writer;
    writer.SetFileName(outfilename.c_str());
    writer.SetFile(cleaner.GetFile());
    if (!writer.Write()) {
      std::cerr << "Failed to write: " << outfilename << std::endl;
      return 1;
    }
  }

  // re-read, written out:
  {
    Reader reader;
    reader.SetFileName(outfilename.c_str());
    if (!reader.Read()) {
      std::cerr << "Could not read: " << outfilename << std::endl;
      return 1;
    }

    File &file = reader.GetFile();
    DataSet &ds = file.GetDataSet();

    const bool b0 = IsTagIn(ds, path4, pt1);
    const bool b1 = IsTagIn(ds, path1, pt2);
    const DataSet &ds1 = GetNestedDataSet(ds, path1);
    const bool b2 = IsTagIn(ds1, path2, pt2);
    const bool b3 = IsTagIn(ds, path3, pt2);
    const bool b4 = IsTagIn(ds, path4, pt2);
    if (b0 || b1 || b2 || b3 || b4) {
      std::cerr << "At least one tag was not removed" << std::endl;
      return 1;
    }
  }
  return 0;
}

int TestCleaner3(int, char *[]) {
  using namespace gdcm;
  const char *directory = gdcm::Testing::GetDataRoot();
  std::string sfilename =
      std::string(directory) + "/PhilipsInteraSeqTermInvLen.dcm";
  const char *filename = sfilename.c_str();

  // Create directory first:
  const char subdir[] = "TestCleaner3";
  std::string tmpdir = Testing::GetTempDirectory(subdir);
  if (!System::FileIsDirectory(tmpdir.c_str())) {
    System::MakeDirectory(tmpdir.c_str());
  }
  std::string outfilename = Testing::GetTempFilename(filename, subdir);

  int res1 = 0;  // TestCleaner3Impl(filename, outfilename, true);
  int res2 = TestCleaner3Impl(filename, outfilename, false);

  return res1 + res2;
}
