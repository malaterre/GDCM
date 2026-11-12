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
#include "gdcmDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmFile.h"
#include "gdcmSmartPointer.h"

#include <cstring>
#include <iostream>

// SV10 signature, one element announced, then truncated: scrub must fail.
static const char truncated_sv10[] = "SV10\4\3\2\1\1\0\0\0\x4d\0\0\0";

static void AddElement(gdcm::DataSet &ds, const gdcm::Tag &tag,
                       const gdcm::VR &vr, const char *bytes, size_t len) {
  gdcm::DataElement de(tag);
  de.SetVR(vr);
  de.SetByteValue(bytes, (uint32_t)len);
  ds.Replace(de);
}

// imageDecl, seriesDecl: values of the CSA Image and Series Header Type
// attributes, or nullptr for none
static int TestCleaner5Impl(const char *imageDecl, const char *seriesDecl,
                            bool emptyWhenScrubFails, bool expectSuccess) {
  using namespace gdcm;
  SmartPointer<File> file = new File;
  DataSet &ds = file->GetDataSet();
  static const char creator[] = "SIEMENS CSA HEADER";
  AddElement(ds, Tag(0x0029, 0x0010), VR::LO, creator, strlen(creator));
  if (imageDecl) {
    AddElement(ds, Tag(0x0029, 0x1008), VR::CS, imageDecl, strlen(imageDecl));
  }
  if (seriesDecl) {
    AddElement(ds, Tag(0x0029, 0x1018), VR::CS, seriesDecl,
               strlen(seriesDecl));
  }
  const Tag image(0x0029, 0x1010);
  const Tag series(0x0029, 0x1020);
  AddElement(ds, image, VR::OB, truncated_sv10, sizeof truncated_sv10 - 1);
  AddElement(ds, series, VR::OB, truncated_sv10, sizeof truncated_sv10 - 1);

  // Scrub one header at a time so that both code paths get exercised:
  const PrivateTag pts[] = {CSAHeader::GetCSAImageHeaderInfoTag(),
                            CSAHeader::GetCSASeriesHeaderInfoTag()};
  const Tag tags[] = {image, series};
  for (int i = 0; i < 2; ++i) {
    Cleaner cleaner;
    cleaner.SetFile(*file);
    cleaner.EmptyWhenScrubFails(emptyWhenScrubFails);
    if (!cleaner.Scrub(pts[i])) {
      std::cerr << "Could not Scrub: " << pts[i] << std::endl;
      return 1;
    }
    const char *declaration = i == 0 ? imageDecl : seriesDecl;
    const bool success = cleaner.Clean();
    if (success != expectSuccess) {
      std::cerr << "Clean returned " << success << " for " << pts[i]
                << " declaration: " << (declaration ? declaration : "(none)")
                << " EmptyWhenScrubFails: " << emptyWhenScrubFails
                << std::endl;
      return 1;
    }
    const DataSet &out = cleaner.GetFile().GetDataSet();
    if (!out.FindDataElement(tags[i])) {
      std::cerr << "Missing: " << tags[i] << std::endl;
      return 1;
    }
    const bool empty = out.GetDataElement(tags[i]).IsEmpty();
    if (empty != (emptyWhenScrubFails && expectSuccess)) {
      std::cerr << "Unexpected content for " << pts[i]
                << " declaration: " << (declaration ? declaration : "(none)")
                << " EmptyWhenScrubFails: " << emptyWhenScrubFails
                << std::endl;
      return 1;
    }
  }
  return 0;
}

int TestCleaner5(int, char *[]) {
  int res = 0;
  // Header Type declared:
  res += TestCleaner5Impl("MR", "MR", true, true);
  res += TestCleaner5Impl("MR", "MR", false, false);
  // Header Type removed, SV10 signature only:
  res += TestCleaner5Impl(nullptr, nullptr, true, true);
  res += TestCleaner5Impl(nullptr, nullptr, false, false);
  // Header Type unknown, SV10 signature only:
  res += TestCleaner5Impl("UNKNOWN", "UNKNOWN", true, true);
  res += TestCleaner5Impl("UNKNOWN", "UNKNOWN", false, false);
  // Recognized non-SV10 type carrying an SV10 signature stays an error:
  res += TestCleaner5Impl("SOM 5", "SOM 7 DEV", true, false);
  res += TestCleaner5Impl("SOM 5", "SOM 7 DEV", false, false);
  return res;
}
