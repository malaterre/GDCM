/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmCSAHeader.h"
#include "gdcmCleaner.h"
#include "gdcmFilename.h"
#include "gdcmReader.h"
#include "gdcmSmartPointer.h"
#include "gdcmSystem.h"
#include "gdcmTesting.h"
#include "gdcmWriter.h"

namespace gdcm {
static std::pair<std::string, std::string> ComputeMD5CSADecoded(
    const DataSet &ds, const PrivateTag &pt) {
  std::pair<std::string, std::string> ret;
  CSAHeader csa;
  char digest1[33];
  char digest2[33];
  if (ds.FindDataElement(pt)) {
    const DataElement &de = ds.GetDataElement(pt);
    const ByteValue *bv = de.GetByteValue();
    if (!Testing::ComputeMD5(bv->GetPointer(), bv->GetLength(), digest1))
      return ret;
    if (!csa.LoadFromDataElement(de)) return ret;
    if (csa.GetFormat() != CSAHeader::SV10) return ret;
    std::ostringstream os;
    csa.Print(os);
    std::string str = os.str();
    if (!Testing::ComputeMD5(str.c_str(), str.size(), digest2)) return ret;
    ret.first = digest1;
    ret.second = digest2;
  }
  return ret;
}
}  // namespace gdcm

int TestCleaner1Impl(std::string const &filename,
                     std::string const &outfilename, bool useDPath) {
  using namespace gdcm;
  // reference digest of decoded csa:
  const std::string ref1 = "ff225133ae107e4e8ee0ba1972016e0c";
  const std::string ref2 = "860bf885643a9a40e6d4bd468f8fd6c4";

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

    const std::string raw1 = "42efe9d2b2611d88039ce76a0d5eeb42";
    const std::string raw2 = "938bbc5c001fb24e37b97dbffbd83ff7";

    CSAHeader csa;
    const PrivateTag &t1 = csa.GetCSAImageHeaderInfoTag();
    const PrivateTag &t2 = csa.GetCSASeriesHeaderInfoTag();
    const std::pair<std::string, std::string> digests1 =
        ComputeMD5CSADecoded(ds, t1);
    const std::pair<std::string, std::string> digests2 =
        ComputeMD5CSADecoded(ds, t2);
    if (digests1.first != raw1 || digests2.first != raw2) {
      std::cerr << "bogus digest" << std::endl;
      return 1;
    }
    if (digests1.second != ref1 || digests2.second != ref2) {
      std::cerr << "bogus digest" << std::endl;
      return 1;
    }

    // Setup DPath
    DPath dpath1, dpath2;
    if (!dpath1.ConstructFromString("/0029,10,SIEMENS CSA HEADER") ||
        !dpath2.ConstructFromString("/0029,20,SIEMENS CSA HEADER")) {
      return 1;
    }

    Cleaner cleaner;
    cleaner.SetFile(file);
    if (useDPath) {
      if (!cleaner.Scrub(dpath1)) {
        return 1;
      }
      if (!cleaner.Scrub(dpath2)) {
        return 1;
      }
    } else {
      if (!cleaner.Scrub(t1)) {
        return 1;
      }
      if (!cleaner.Scrub(t2)) {
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

    const std::string raw1 = "c712f47d79928578a724f36420342fc1";
    const std::string raw2 = "3a33733b8dc87cb5f80eccf0aeb784f5";

    CSAHeader csa;
    const PrivateTag &t1 = csa.GetCSAImageHeaderInfoTag();
    const PrivateTag &t2 = csa.GetCSASeriesHeaderInfoTag();
    const std::pair<std::string, std::string> digests1 =
        ComputeMD5CSADecoded(ds, t1);
    const std::pair<std::string, std::string> digests2 =
        ComputeMD5CSADecoded(ds, t2);
    if (digests1.first != raw1 || digests2.first != raw2) {
      std::cerr << "bogus digest" << std::endl;
      return 1;
    }
    if (digests1.second != ref1 || digests2.second != ref2) {
      std::cerr << "bogus digest" << std::endl;
      return 1;
    }
  }
  return 0;
}

int TestCleaner1(int, char *[]) {
  using namespace gdcm;
  const char *directory = gdcm::Testing::GetDataRoot();
  std::string sfilename = std::string(directory) + "/SIEMENS_CSA2.dcm";
  const char *filename = sfilename.c_str();

  // Create directory first:
  const char subdir[] = "TestCleaner1";
  std::string tmpdir = Testing::GetTempDirectory(subdir);
  if (!System::FileIsDirectory(tmpdir.c_str())) {
    System::MakeDirectory(tmpdir.c_str());
  }
  std::string outfilename = Testing::GetTempFilename(filename, subdir);

  int res1 = TestCleaner1Impl(filename, outfilename, true);
  int res2 = TestCleaner1Impl(filename, outfilename, false);

  return res1 + res2;
}
