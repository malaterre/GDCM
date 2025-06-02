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
template <typename T>
static const DataSet &GetNestedDataSet(const DataSet &ds, const T &path) {
  const DataElement &de = ds.GetDataElement(path);
  SmartPointer<SequenceOfItems> sqi = de.GetValueAsSQ();
  gdcm_assert(sqi && sqi->GetNumberOfItems() == 1);
  const Item &item = sqi->GetItem(1);
  const DataSet &subds = item.GetNestedDataSet();
  return subds;
}
template <typename T>
static bool IsTagIn(const DataSet &ds, const T &pt) {
  return ds.FindDataElement(pt);
}
template <typename T1, typename T2>
static bool IsTagIn(const DataSet &ds, const T1 &path, const T2 &pt) {
  const DataSet &subds = GetNestedDataSet(ds, path);
  return subds.FindDataElement(pt);
}
template <typename T>
static bool IsTagEmpty(const DataSet &ds, const T &pt) {
  if (!ds.FindDataElement(pt)) return false;
  const DataElement &de = ds.GetDataElement(pt);
  return de.IsEmpty();
}
template <typename T1, typename T2>
static bool IsTagEmpty(const DataSet &ds, const T1 &path, const T2 &pt) {
  const DataSet &subds = GetNestedDataSet(ds, path);
  if (!subds.FindDataElement(pt)) return false;
  const DataElement &de = subds.GetDataElement(pt);
  return de.IsEmpty();
}
}  // namespace gdcm

struct TestCleaner4Impl {
  virtual ~TestCleaner4Impl() = default;
  virtual bool check_before(gdcm::DataSet &ds) = 0;
  virtual bool check_after(gdcm::DataSet &ds, bool preservePatientName) = 0;
  int run(std::string const &filename, std::string const &outfilename,
          bool useDPath, bool preservePatientName = false) {
    using namespace gdcm;

    // Setup DPath
    DPath dpath1, dpath2;
    if (useDPath) {
    }
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

      if (!check_before(ds)) {
        std::cerr << "Test not setup correctly" << std::endl;
        return 1;
      }

      Cleaner cleaner;
      cleaner.SetFile(file);
      cleaner.RemoveAllGroupLength(false);
      if (preservePatientName) {
        DPath dpath;
        dpath.ConstructFromString("\\0010,0010");
        cleaner.Preserve(dpath);
      }
      if (useDPath) {
        if (!cleaner.Empty(dpath1)) {
          return 1;
        }
      } else {
        if (!cleaner.Empty(VR(VR::PN))) {
          return 1;
        }
      }
      if (!cleaner.Clean()) {
        return 1;
      }

      Writer writer;
      writer.SetFileName(outfilename.c_str());
      writer.SetFile(cleaner.GetFile());
#if 0
  gdcm::FileMetaInformation::SetSourceApplicationEntityTitle("gdcmconv");
      file.GetHeader().Clear();
      writer.SetCheckFileMetaInformation(true);
#endif
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
      if (!check_after(ds, preservePatientName)) {
        std::cerr << "At least one tag was not empty" << std::endl;
        return 1;
      }
    }
    return 0;
  }
};

struct TestCleaner4Impl1 : public TestCleaner4Impl {
  bool check_before(gdcm::DataSet &ds) override {
    const gdcm::Tag t1(0x0008, 0x0090);  //
    const gdcm::Tag t2(0x0008, 0x1050);  //
    const gdcm::Tag t3(0x0008, 0x1070);  //
    const gdcm::Tag t4(0x0010, 0x0010);  //
    {
      const bool b1 = IsTagIn(ds, t1);
      const bool b2 = IsTagIn(ds, t2);
      const bool b3 = IsTagIn(ds, t3);
      const bool b4 = IsTagIn(ds, t4);
      if (!b1 || !b2 || !b3 || !b4) {
        return false;
      }
    }
    {
      const bool b1 = IsTagEmpty(ds, t1);
      const bool b2 = IsTagEmpty(ds, t2);
      const bool b3 = IsTagEmpty(ds, t3);
      const bool b4 = IsTagEmpty(ds, t4);
      if (b1 || b2 || b3 || b4) {
        return false;
      }
    }
    return true;
  }
  bool check_after(gdcm::DataSet &ds, bool /*preservePatientName*/) override {
    const gdcm::Tag t1(0x0008, 0x0090);  //
    const gdcm::Tag t2(0x0008, 0x1050);  //
    const gdcm::Tag t3(0x0008, 0x1070);  //
    const gdcm::Tag t4(0x0010, 0x0010);  //
    const bool b1 = IsTagEmpty(ds, t1);
    const bool b2 = IsTagEmpty(ds, t2);
    const bool b3 = IsTagEmpty(ds, t3);
    const bool b4 = IsTagEmpty(ds, t4);

    if (!b1 || !b2 || !b3 || !b4) {
      return false;
    }
    return true;
  }
};

struct TestCleaner4Impl2 : public TestCleaner4Impl {
  bool check_before(gdcm::DataSet &ds) override {
    const gdcm::Tag t1(0x0008, 0x0090);  //     PN      6       EU^^^^
    const gdcm::Tag t2(0x0008, 0x1050);  //     PN      4       ^^^^
    const gdcm::Tag t3(0x0008, 0x1060);  //     PN      16      DR.H.DOOLITTLER
    const gdcm::Tag t4(0x0008, 0x1070);  //     PN      4       CNA
    const gdcm::Tag t5(0x0010, 0x0010);  //     PN      16      ABCDEF^GHIJK^^MR
    const gdcm::Tag t6(0x0032, 0x1032);  //     PN      10      EMERG-UNIT
    {
      const bool b1 = IsTagIn(ds, t1);
      const bool b2 = IsTagIn(ds, t2);
      const bool b3 = IsTagIn(ds, t3);
      const bool b4 = IsTagIn(ds, t4);
      const bool b5 = IsTagIn(ds, t5);
      const bool b6 = IsTagIn(ds, t6);
      if (!b1 || !b2 || !b3 || !b4 || !b5 || !b6) {
        return false;
      }
    }
    {
      const bool b1 = IsTagEmpty(ds, t1);
      const bool b2 = IsTagEmpty(ds, t2);
      const bool b3 = IsTagEmpty(ds, t3);
      const bool b4 = IsTagEmpty(ds, t4);
      const bool b5 = IsTagEmpty(ds, t5);
      const bool b6 = IsTagEmpty(ds, t6);
      if (b1 || b2 || b3 || b4 || b5 || b6) {
        return false;
      }
    }
    return true;
  }
  bool check_after(gdcm::DataSet &ds, bool /*preservePatientName*/) override {
    const gdcm::Tag t1(0x0008, 0x0090);  //     PN      6       EU^^^^
    const gdcm::Tag t2(0x0008, 0x1050);  //     PN      4       ^^^^
    const gdcm::Tag t3(0x0008, 0x1060);  //     PN      16      DR.H.DOOLITTLER
    const gdcm::Tag t4(0x0008, 0x1070);  //     PN      4       CNA
    const gdcm::Tag t5(0x0010, 0x0010);  //     PN      16      ABCDEF^GHIJK^^MR
    const gdcm::Tag t6(0x0032, 0x1032);  //     PN      10      EMERG-UNIT
    const bool b1 = IsTagEmpty(ds, t1);
    const bool b2 = IsTagEmpty(ds, t2);
    const bool b3 = IsTagEmpty(ds, t3);
    const bool b4 = IsTagEmpty(ds, t4);
    const bool b5 = IsTagEmpty(ds, t5);
    const bool b6 = IsTagEmpty(ds, t6);

    if (!b1 || !b2 || !b3 || !b4 || !b5 || !b6) {
      return false;
    }
    return true;
  }
};

struct TestCleaner4Impl3 : public TestCleaner4Impl {
  bool check_before(gdcm::DataSet &ds) override {
    const gdcm::Tag t1(0x0008, 0x0090);  //
    const gdcm::Tag t2(0x0008, 0x1070);  //
    const gdcm::Tag t3(0x0010, 0x0010);  //
    const gdcm::PrivateTag path1(0x2001, 0x00, "Philips Imaging DD 129");
    const gdcm::Tag t4(0x0070, 0x0084);                                     //
    const gdcm::PrivateTag pt5(0x2005, 0x91, "Philips MR Imaging DD 004");  //
    {
      const bool b1 = IsTagIn(ds, t1);
      const bool b2 = IsTagIn(ds, t2);
      const bool b3 = IsTagIn(ds, t3);
      const bool b4 = IsTagIn(ds, path1, t4);
      const bool b5 = IsTagIn(ds, pt5);
      if (!b1 || !b2 || !b3 || !b4 || !b5) {
        return false;
      }
    }
    {
      const bool b1 = IsTagEmpty(ds, t1);
      const bool b2 = IsTagEmpty(ds, t2);
      const bool b3 = IsTagEmpty(ds, t3);
      const bool b4 = IsTagEmpty(ds, path1, t4);
      const bool b5 = IsTagEmpty(ds, pt5);
      if (!b1 || !b2 || b3 || b4 || !b5) {
        return false;
      }
    }
    return true;
  }
  bool check_after(gdcm::DataSet &ds, bool /*preservePatientName*/) override {
    const gdcm::Tag t1(0x0008, 0x0090);  //
    const gdcm::Tag t2(0x0008, 0x1070);  //
    const gdcm::Tag t3(0x0010, 0x0010);  //
    const gdcm::PrivateTag path1(0x2001, 0x00, "Philips Imaging DD 129");
    const gdcm::Tag t4(0x0070, 0x0084);                                     //
    const gdcm::PrivateTag pt5(0x2005, 0x91, "Philips MR Imaging DD 004");  //
    const bool b1 = IsTagEmpty(ds, t1);
    const bool b2 = IsTagEmpty(ds, t2);
    const bool b3 = IsTagEmpty(ds, t3);
    const bool b4 = IsTagEmpty(ds, path1, t4);
    const bool b5 = IsTagEmpty(ds, pt5);

    if (!b1 || !b2 || !b3 || !b4 || !b5) {
      return false;
    }
    return true;
  }
};

struct TestCleaner4Impl4 : public TestCleaner4Impl {
  bool check_before(gdcm::DataSet &ds) override {
    const gdcm::Tag t1(0x0008, 0x0090);  //
    const gdcm::Tag t2(0x0008, 0x1070);  //
    const gdcm::Tag t3(0x0010, 0x0010);  //
    const gdcm::PrivateTag path1(0xe1, 0x39, "ELSCINT1");
    const gdcm::Tag t4(0x0008, 0x0090);  //
    const gdcm::Tag t5(0x0032, 0x1032);  //
    {
      const bool b1 = IsTagIn(ds, t1);
      const bool b2 = IsTagIn(ds, t2);
      const bool b3 = IsTagIn(ds, t3);
      const bool b4 = IsTagIn(ds, path1, t4);
      const bool b5 = IsTagIn(ds, path1, t5);
      if (!b1 || !b2 || !b3 || !b4 || !b5) {
        return false;
      }
    }
    {
      const bool b1 = IsTagEmpty(ds, t1);
      const bool b2 = IsTagEmpty(ds, t2);
      const bool b3 = IsTagEmpty(ds, t3);
      const bool b4 = IsTagEmpty(ds, path1, t4);
      const bool b5 = IsTagEmpty(ds, path1, t5);
      if (!b1 || b2 || b3 || !b4 || !b5) {
        return false;
      }
    }
    return true;
  }
  bool check_after(gdcm::DataSet &ds, bool preservePatientName) override {
    const gdcm::Tag t1(0x0008, 0x0090);  //
    const gdcm::Tag t2(0x0008, 0x1070);  //
    const gdcm::Tag t3(0x0010, 0x0010);  //
    const gdcm::PrivateTag path1(0xe1, 0x39, "ELSCINT1");
    const gdcm::Tag t4(0x0008, 0x0090);  //
    const gdcm::Tag t5(0x0032, 0x1032);  //
    const bool b1 = IsTagEmpty(ds, t1);
    const bool b2 = IsTagEmpty(ds, t2);
    const bool b3 =
        preservePatientName ? !IsTagEmpty(ds, t3) : IsTagEmpty(ds, t3);
    const bool b4 = IsTagEmpty(ds, path1, t4);
    const bool b5 = IsTagEmpty(ds, path1, t5);

    if (!b1 || !b2 || !b3 || !b4 || !b5) {
      gdcm_assert(0);
      return false;
    }
    return true;
  }
};

int TestCleaner4(int, char *[]) {
  using namespace gdcm;
  const char *directory = gdcm::Testing::GetDataRoot();
  std::string sfilename1 =
      std::string(directory) + "/GE_DLX-8-MONO2-Multiframe.dcm";  // implicit
  const char *filename1 = sfilename1.c_str();
  std::string sfilename2 =
      std::string(directory) + "/JPEGInvalidSecondFrag.dcm";  // OB => PN
  const char *filename2 = sfilename2.c_str();
  std::string sfilename3 =
      std::string(directory) + "/undefined_length_un_vr.dcm";  // => nested
  const char *filename3 = sfilename3.c_str();
  std::string sfilename4 =
      std::string(directory) + "/MAROTECH_CT_JP2Lossy.dcm";  // => nested
  const char *filename4 = sfilename4.c_str();

  // Create directory first:
  const char subdir[] = "TestCleaner4";
  std::string tmpdir = Testing::GetTempDirectory(subdir);
  if (!System::FileIsDirectory(tmpdir.c_str())) {
    System::MakeDirectory(tmpdir.c_str());
  }
  std::string outfilename1 = Testing::GetTempFilename(filename1, subdir);
  std::string outfilename2 = Testing::GetTempFilename(filename2, subdir);
  std::string outfilename3 = Testing::GetTempFilename(filename3, subdir);
  std::string outfilename4 = Testing::GetTempFilename(filename4, subdir);

  TestCleaner4Impl1 testCleaner1;
  TestCleaner4Impl2 testCleaner2;
  TestCleaner4Impl3 testCleaner3;
  TestCleaner4Impl4 testCleaner4;
  int res1 = testCleaner1.run(filename1, outfilename1, false);
  int res2 = testCleaner2.run(filename2, outfilename2, false);
  int res3 = testCleaner3.run(filename3, outfilename3, false);
  int res4 = testCleaner4.run(filename4, outfilename4, false, false);
  int res5 = testCleaner4.run(filename4, outfilename4, false, true);

  return res1 + res2 + res3 + res4 + res5;
}
