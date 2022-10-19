/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmEquipmentManufacturer.h"
#include "gdcmFilename.h"
#include "gdcmReader.h"

#include "gdcmTesting.h"

static int TestEquipmentManufacturerFunc(const char *filename,
                                         bool verbose = false) {
  if (verbose) std::cerr << "Reading: " << filename << std::endl;
  const gdcm::Tag pixeldata(0x7fe0, 0x0010);
  gdcm::Reader reader;
  reader.SetFileName(filename);
  if (!reader.ReadUpToTag(pixeldata)) {
    std::cerr << "TestReadError: Failed to read: " << filename << std::endl;
    return 1;
  }

  gdcm::File &file = reader.GetFile();
  gdcm::MediaStorage ms;
  ms.SetFromFile(file);
  if (ms == gdcm::MediaStorage::MediaStorageDirectoryStorage)
    return 0;  // skip DICOMDIR

  gdcm::Filename fn(filename);
  const char *name = fn.GetName();
  // Special handling:
  if (strcmp(name, "OsirixFake16BitsStoredFakeSpacing.dcm") == 0 ||
      strcmp(name, "simpleImageWithIcon.dcm") == 0 ||
      strcmp(name, "rle16sti.dcm") == 0 || strcmp(name, "rle16loo.dcm") == 0 ||
      strcmp(name, "gdcm-CR-DCMTK-16-NonSamplePerPix.dcm") == 0 ||
      strcmp(name, "XA-MONO2-8-12x-catheter.dcm") == 0 ||
      strcmp(name, "US-RGB-8-esopecho.dcm") == 0 ||
      strcmp(name, "US-PAL-8-10x-echo.dcm") == 0 ||
      strcmp(name, "US-MONO2-8-8x-execho.dcm") == 0 ||
      strcmp(name, "THERALYS-12-MONO2-Uncompressed-Even_Length_Tag.dcm") == 0 ||
      strcmp(name, "SignedShortLosslessBug.dcm") == 0 ||
      strcmp(name, "SC16BitsAllocated_8BitsStoredJPEG.dcm") == 0 ||
      strcmp(name, "SC16BitsAllocated_8BitsStoredJ2K.dcm") == 0 ||
      strcmp(name, "RadBWLossLess.dcm") == 0 ||
      strcmp(name, "RLEDebianBug816607Orig.dcm") == 0 ||
      strcmp(name, "DermaColorLossLess.dcm") == 0 ||
      strcmp(name, "00191113.dcm") == 0 || strcmp(name, "test.acr") == 0 ||
      strcmp(name, "MARCONI_MxTWin-12-MONO2-JpegLossless-ZeroLengthSQ.dcm") ==
          0 ||
      strcmp(name, "PICKER-16-MONO2-Nested_icon.dcm") == 0 ||
      strcmp(name, "MR_ELSCINT1_00e1_1042_SQ_feff_00e0_Item.dcm") == 0 ||
      strcmp(name, "PrivateGEImplicitVRBigEndianTransferSyntax16Bits.dcm") ==
          0 ||
      strcmp(name, "LIBIDO-8-ACR_NEMA-Lena_128_128.acr") == 0 ||
      strcmp(name, "gdcm-ACR-LibIDO.acr") == 0 ||
      strcmp(name, "libido1.0-vol.acr") == 0 ||
      strcmp(name, "DCMTK_JPEGExt_12Bits.dcm") == 0 ||
      strcmp(name, "DMCPACS_ExplicitImplicit_BogusIOP.dcm") == 0 ||
      strcmp(name, "DX_J2K_0Padding.dcm") == 0 ||
      strcmp(name, "GDCMJ2K_TextGBR.dcm") == 0 ||
      strcmp(name, "ITK_GDCM124_MultiframeSecondaryCaptureInvalid.dcm") == 0 ||
      strcmp(name, "JPEGLS_CharLS_10742.dcm") == 0 ||
      strcmp(name, "JPEGLosslessYBR_FULL_422.dcm") == 0 ||
      strcmp(name, "JPEGLosslessSeNonZero.dcm") == 0 ||
      strcmp(name, "US-YBR_FULL_422-EVRLE.dcm") == 0 ||
      strcmp(name, "LIBIDO-24-ACR_NEMA-Rectangle.dcm") == 0 ||
      strcmp(name, "MR-Brucker-CineTagging-NonSquarePixels.dcm") == 0 ||
      strcmp(name, "MR16BitsAllocated_8BitsStored.dcm") == 0 ||
      strcmp(name, "NM-MONO2-16-13x-heart.dcm") == 0 ||
      strcmp(name, "NM-PAL-16-PixRep1.dcm") == 0 ||
      strcmp(name, "NM_Kakadu44_SOTmarkerincons.dcm") == 0 ||
      strcmp(name, "PICKER-16-MONO2-No_DicomV3_Preamble.dcm") == 0 ||
      strcmp(name, "OT-PAL-8-face.dcm") == 0 ||
      strcmp(name, "TG18-CH-2k-01.dcm") == 0                     // wotsit ?
      || strcmp(name, "HardcopyColor_YBR_RCT_J2K_PC1.dcm") == 0  // RamSoft Inc.
      || strncmp(name, "D_CLUNIE", 8) == 0                       // D_CLUNIE*
      || strncmp(name, "LEADTOOLS_FLOWERS", 17) == 0  // LEADTOOLS_FLOWERS*
      || strncmp(name, "JDDICOM", 7) == 0             // JDDICOM*
      || strncmp(name, "JPEGNote", 8) == 0            // JPEGNote*
      || strncmp(name, "KODAK", 5) == 0               // KODAK*
      || strncmp(name, "DICOMDIR", 8) == 0            // DICOMDIR*
      || strncmp(name, "dicomdir", 8) == 0            // dicomdir*
  ) {
    if (verbose) std::cout << "skip: " << filename << std::endl;
    return 0;
  }

  gdcm::DataSet &ds = file.GetDataSet();
  gdcm::EquipmentManufacturer::Type manufacturer =
      gdcm::EquipmentManufacturer::Compute(ds);
  if (verbose) {
    std::cout << "Found: "
              << gdcm::EquipmentManufacturer::TypeToString(manufacturer)
              << " -> " << manufacturer << std::endl;
  }
  if (manufacturer == gdcm::EquipmentManufacturer::UNKNOWN) {
    std::cerr << "Unknown: " << filename << std::endl;
    return 1;
  }
  ds.Remove(gdcm::Tag(0x8, 0x70));
  gdcm::EquipmentManufacturer::Type manufacturer2 =
      gdcm::EquipmentManufacturer::Compute(ds);
  if (manufacturer2 == gdcm::EquipmentManufacturer::UNKNOWN) {
    if (strcmp(name, "gdcm-US-ALOKA-16.dcm") == 0 ||
        strcmp(name, "US-RGB-8-epicard.dcm") == 0 ||
        strcmp(name, "OT-MONO2-8-a7.dcm") == 0 ||
        strcmp(name, "MR-MONO2-8-16x-heart.dcm") == 0 ||
        strcmp(name, "MR-MONO2-16-head.dcm") == 0 ||
        strcmp(name, "MR-MONO2-12-shoulder.dcm") == 0 ||
        strcmp(name, "MR-MONO2-12-an2.acr") == 0 ||
        strcmp(name, "LJPEG_BuginGDCM12.dcm") == 0 ||
        strcmp(name, "ELSCINT1_PMSCT_RLE1.dcm") == 0 ||
        strcmp(name, "ELSCINT1_JP2vsJ2K.dcm") == 0 ||
        strcmp(name, "MAROTECH_CT_JP2Lossy.dcm") == 0 ||
        strcmp(name, "ALOKA_SSD-8-MONO2-RLE-SQ.dcm") == 0 ||
        strcmp(name, "CR-MONO1-10-chest.dcm") == 0 ||
        strcmp(name, "CT-MONO2-12-lomb-an2.acr") == 0 ||
        strcmp(name, "CT-MONO2-16-ankle.dcm") == 0 ||
        strcmp(name, "CT-MONO2-8-abdo.dcm") == 0 ||
        strcmp(name, "CT-MONO2-16-ort.dcm") == 0 ||
        strcmp(name, "CT-MONO2-16-chest.dcm") == 0 ||
        strcmp(name, "CT-MONO2-16-brain.dcm") == 0 ||
        strcmp(name, "EnhancedWithIPPPerFrameIOPShared.dcm") == 0 ||
        strcmp(name, "FUJI-10-MONO1-ACR_NEMA_2.dcm") == 0 ||
        strcmp(name, "JPEGDefinedLengthSequenceOfFragments.dcm") == 0 ||
        strcmp(name, "IM-0001-0066.CommandTag00.dcm") == 0 ||
        strcmp(name, "GE_GENESIS-16-MONO2-WrongLengthItem.dcm") == 0 ||
        strcmp(name, "MR_Spectroscopy_SIEMENS_OF.dcm") == 0 ||
        strcmp(name, "US-IRAD-NoPreambleStartWith0005.dcm") == 0 ||
        strcmp(name, "US-IRAD-NoPreambleStartWith0003.dcm") == 0 ||
        strcmp(name, "PHILIPS_Brilliance_ExtraBytesInOverlay.dcm") == 0 ||
        strcmp(name, "TOSHIBA_MRT150-16-MONO2-ACR_NEMA_2.dcm") == 0 ||
        strcmp(name, "fffc0000UN.dcm") == 0) {
    } else {
      std::cerr << "Unknown2: " << filename << std::endl;
      return 1;
    }
  } else if (manufacturer2 != manufacturer) {
    std::cerr << "Incompatible: " << filename << std::endl;
    return 1;
  }

  return 0;
}

int TestEquipmentManufacturer(int argc, char *argv[]) {
  if (argc == 2) {
    const char *filename = argv[1];
    return TestEquipmentManufacturerFunc(filename, true);
  }

  // else
  // First of get rid of warning/debug message
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  int r = 0, i = 0;
  const char *filename;
  const char *const *filenames = gdcm::Testing::GetFileNames();
  while ((filename = filenames[i])) {
    r += TestEquipmentManufacturerFunc(filename);
    ++i;
  }

  return r;
}
