/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkGDCMImageReader.h"

#include "vtkImageData.h"
#include "vtkMultiThreader.h"
#include "vtkMedicalImageProperties.h"

#include "gdcmTesting.h"
#include "gdcmFilename.h"
#include "gdcmSystem.h"
#include "gdcmTrace.h"
#include "gdcmImageReader.h"

#ifndef vtkFloatingPointType
#define vtkFloatingPointType float
#endif

// See TestImageReader + lossydump = true to generate this list:
struct LossyFile
{
  int lossyflag;
  const char *filename;
};

static const LossyFile gdcmLossyFilenames[] = {
{ 0,"SIEMENS_SOMATOM-12-ACR_NEMA-ZeroLengthUs.acr" },
{ 0,"MR-MONO2-12-an2.acr" },
{ 0,"gdcm-ACR-LibIDO.acr" },
{ 0,"test.acr" },
{ 0,"MR-MONO2-12-angio-an1.acr" },
{ 0,"LIBIDO-8-ACR_NEMA-Lena_128_128.acr" },
{ 0,"libido1.0-vol.acr" },
{ 0,"gdcm-MR-SIEMENS-16-2.acr" },
{ 0,"CT-MONO2-12-lomb-an2.acr" },
{ 0,"LEADTOOLS_FLOWERS-8-PAL-Uncompressed.dcm" },
{ 0,"00191113.dcm" },
{ 0,"SignedShortLosslessBug.dcm" },
{ 0,"gdcm-MR-PHILIPS-16-NonSquarePixels.dcm" },
{ 0,"MARCONI_MxTWin-12-MONO2-JpegLossless-ZeroLengthSQ.dcm" },
{ 0,"ACUSON-24-YBR_FULL-RLE.dcm" },
{ 0,"D_CLUNIE_VL2_RLE.dcm" },
{ 0,"MR_Philips_Intera_No_PrivateSequenceImplicitVR.dcm" },
{ 0,"MR_Philips-Intera_BreaksNOSHADOW.dcm" },
{ 0,"D_CLUNIE_MR2_JPLL.dcm" },
{ 0,"D_CLUNIE_XA1_JPLL.dcm" },
{ 0,"JPEG_LossyYBR.dcm" },
{ 0,"ALOKA_SSD-8-MONO2-RLE-SQ.dcm" },
{ 0,"PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm" },
{ 0,"MR-MONO2-12-shoulder.dcm" },
{ 0,"D_CLUNIE_RG3_JPLY.dcm" },
{ 1,"PHILIPS_Gyroscan-12-Jpeg_Extended_Process_2_4.dcm" },
{ 0,"MR-MONO2-8-16x-heart.dcm" },
{ 0,"SIEMENS_ImageLocationUN.dcm" },
{ 0,"US-PAL-8-10x-echo.dcm" },
{ 0,"PHILIPS_Brilliance_ExtraBytesInOverlay.dcm" },
{ 0,"SIEMENS_MAGNETOM-12-MONO2-Uncompressed.dcm" },
{ 0,"LEADTOOLS_FLOWERS-8-PAL-RLE.dcm" },
{ 0,"US-RGB-8-esopecho.dcm" },
{ 0,"GE_RHAPSODE-16-MONO2-JPEG-Fragments.dcm" },
{ 0,"CT-SIEMENS-Icone-With-PaletteColor.dcm" },
{ 0,"LEADTOOLS_FLOWERS-16-MONO2-Uncompressed.dcm" },
{ 0,"FUJI-10-MONO1-ACR_NEMA_2.dcm" },
{ 0,"D_CLUNIE_CT1_RLE.dcm" },
{ 0,"undefined_length_un_vr.dcm" },
{ 0,"D_CLUNIE_MR4_JPLL.dcm" },
{ 0,"DCMTK_JPEGExt_12Bits.dcm" },
{ 0,"CT_16b_signed-UsedBits13.dcm" },
{ 0,"DX_J2K_0Padding.dcm" },
{ 0,"KODAK_CompressedIcon.dcm" },
{ 0,"D_CLUNIE_CT2_JPLL.dcm" },
{ 0,"DermaColorLossLess.dcm" },
{ 0,"GE_GENESIS-16-MONO2-Uncompressed-UnusualVR.dcm" },
{ 0,"D_CLUNIE_NM1_JPLY.dcm" },
{ 0,"MR_Philips_Intera_SwitchIndianess_noLgtSQItem_in_trueLgtSeq.dcm" },
{ 0,"LEADTOOLS_FLOWERS-24-RGB-JpegLossy.dcm" },
{ 0,"D_CLUNIE_CT1_J2KR.dcm" },
{ 0,"LEADTOOLS_FLOWERS-16-MONO2-RLE.dcm" },
{ 0,"US-RGB-8-epicard.dcm" },
{ 0,"D_CLUNIE_MR3_RLE.dcm" },
{ 0,"LEADTOOLS_FLOWERS-8-MONO2-Uncompressed.dcm" },
{ 0,"US-IRAD-NoPreambleStartWith0005.dcm" },
{ 0,"D_CLUNIE_RG2_JPLL.dcm" },
{ 0,"DMCPACS_ExplicitImplicit_BogusIOP.dcm" },
{ 0,"MR_ELSCINT1_00e1_1042_SQ_feff_00e0_Item.dcm" },
{ 0,"MR-SIEMENS-DICOM-WithOverlays.dcm" },
{ 0,"SIEMENS_MOSAIC_12BitsStored-16BitsJPEG.dcm" },
{ 0,"JDDICOM_Sample2-dcmdjpeg.dcm" },
{ 0,"SIEMENS_MAGNETOM-12-MONO2-FileSeq2.dcm" },
{ 0,"D_CLUNIE_MR3_JPLY.dcm" },
{ 0,"MR_Philips_Intera_PrivateSequenceExplicitVR_in_SQ_2001_e05f_item_wrong_lgt_use_NOSHADOWSEQ.dcm" },
{ 0,"TheralysGDCM120Bug.dcm" },
{ 0,"PrivateGEImplicitVRBigEndianTransferSyntax16Bits.dcm" },
{ 0,"US-GE-4AICL142.dcm" },
{ 0,"3E768EB7.dcm" },
{ 0,"SIEMENS_Sonata-16-MONO2-Value_Multiplicity.dcm" },
{ 0,"GE_MR_0025xx1bProtocolDataBlock.dcm" },
{ 0,"MR_GE_with_Private_Compressed_Icon_0009_1110.dcm" },
{ 0,"ExplicitVRforPublicElementsImplicitVRforShadowElements.dcm" },
{ 0,"D_CLUNIE_SC1_JPLY.dcm" },
{ 0,"CT-MONO2-16-chest.dcm" },
{ 0,"D_CLUNIE_MR4_RLE.dcm" },
{ 0,"SIEMENS_MAGNETOM-12-MONO2-FileSeq1.dcm" },
{ 1,"ELSCINT1_JP2vsJ2K.dcm" },
{ 0,"D_CLUNIE_CT2_RLE.dcm" },
{ 0,"D_CLUNIE_MR2_RLE.dcm" },
{ 0,"OT-MONO2-8-a7.dcm" },
{ 0,"MR-MONO2-16-head.dcm" },
{ 0,"PICKER-16-MONO2-No_DicomV3_Preamble.dcm" },
{ 0,"gdcm-JPEG-Extended.dcm" },
{ 0,"BugGDCM2_UndefItemWrongVL.dcm" },
{ 0,"D_CLUNIE_MR1_RLE.dcm" },
{ 0,"PICKER-16-MONO2-Nested_icon.dcm" },
{ 0,"D_CLUNIE_VL4_RLE.dcm" },
{ 0,"D_CLUNIE_RG1_RLE.dcm" },
{ 0,"JDDICOM_Sample2.dcm" },
{ 0,"SIEMENS_MAGNETOM-12-MONO2-FileSeq3.dcm" },
{ 0,"CT-MONO2-8-abdo.dcm" },
{ 0,"D_CLUNIE_SC1_RLE.dcm" },
{ 0,"LEADTOOLS_FLOWERS-24-RGB-JpegLossless.dcm" },
{ 0,"D_CLUNIE_RG3_JPLL.dcm" },
{ 0,"SIEMENS_CSA2.dcm" },
{ 0,"LJPEG_BuginGDCM12.dcm" },
{ 0,"CT-SIEMENS-MissingPixelDataInIconSQ.dcm" },
{ 0,"05115014-mr-siemens-avanto-syngo-with-palette-icone.dcm" },
{ 0,"GE_CT_With_Private_compressed-icon.dcm" },
{ 0,"D_CLUNIE_XA1_JPLY.dcm" },
{ 0,"012345.002.050.dcm" },
{ 0,"TOSHIBA_MRT150-16-MONO2-ACR_NEMA_2.dcm" },
{ 0,"LEADTOOLS_FLOWERS-8-MONO2-JpegLossy.dcm" },
{ 0,"gdcm-US-ALOKA-16.dcm" },
{ 0,"THERALYS-12-MONO2-Uncompressed-Even_Length_Tag.dcm" },
{ 0,"D_CLUNIE_CT1_JPLL.dcm" },
{ 0,"rle16loo.dcm" },
{ 0,"D_CLUNIE_US1_RLE.dcm" },
{ 0,"LEADTOOLS_FLOWERS-8-MONO2-RLE.dcm" },
{ 0,"RadBWLossLess.dcm" },
{ 0,"D_CLUNIE_MR1_JPLY.dcm" },
{ 0,"GE_DLX-8-MONO2-PrivateSyntax.dcm" },
{ 0,"gdcm-JPEG-LossLess3a.dcm" },
{ 0,"TG18-CH-2k-01.dcm" },
{ 0,"OT-PAL-8-face.dcm" },
{ 0,"D_CLUNIE_NM1_RLE.dcm" },
{ 0,"rle16sti.dcm" },
{ 0,"GE_GENESIS-16-MONO2-WrongLengthItem.dcm" },
{ 1,"D_CLUNIE_CT1_J2KI.dcm" },
{ 0,"SIEMENS_MAGNETOM-12-MONO2-FileSeq0.dcm" },
{ 0,"LEADTOOLS_FLOWERS-24-RGB-Uncompressed.dcm" },
{ 0,"D_CLUNIE_MR4_JPLY.dcm" },
{ 0,"D_CLUNIE_RG3_RLE.dcm" },
{ 0,"SIEMENS-12-Jpeg_Process_2_4-Lossy-a.dcm" },
{ 0,"CT-MONO2-16-brain.dcm" },
{ 0,"D_CLUNIE_RG2_JPLY.dcm" },
{ 1,"MAROTECH_CT_JP2Lossy.dcm" },
{ 0,"D_CLUNIE_MR1_JPLL.dcm" },
{ 0,"ITK_GDCM124_MultiframeSecondaryCaptureInvalid.dcm" },
{ 0,"SIEMENS_MAGNETOM-12-ACR_NEMA_2-Modern.dcm" },
{ 0,"MR_SIEMENS_forceLoad29-1010_29-1020.dcm" },
{ 0,"simpleImageWithIcon.dcm" },
{ 0,"D_CLUNIE_MR3_JPLL.dcm" },
{ 0,"D_CLUNIE_RG1_JPLL.dcm" },
{ 0,"US-MONO2-8-8x-execho.dcm" },
{ 0,"XA-MONO2-8-12x-catheter.dcm" },
{ 0,"GE_LOGIQBook-8-RGB-HugePreview.dcm" },
{ 0,"gdcm-MR-PHILIPS-16-Multi-Seq.dcm" },
{ 0,"D_CLUNIE_XA1_RLE.dcm" },
{ 0,"NM-MONO2-16-13x-heart.dcm" },
{ 0,"gdcm-JPEG-LossLessThoravision.dcm" },
{ 0,"GE_DLX-8-MONO2-Multiframe.dcm" },
{ 0,"PHILIPS_Intera-16-MONO2-Uncompress.dcm" },
{ 0,"D_CLUNIE_MR2_JPLY.dcm" },
{ 0,"05148044-mr-siemens-avanto-syngo.dcm" },
{ 0,"D_CLUNIE_VL3_RLE.dcm" },
{ 0,"D_CLUNIE_RG2_RLE.dcm" },
{ 0,"SIEMENS_MAGNETOM-12-MONO2-GDCM12-VRUN.dcm" },
{ 0,"KODAK-12-MONO1-Odd_Terminated_Sequence.dcm" },
{ 0,"SIEMENS-MR-RGB-16Bits.dcm" },
{ 0,"CR-MONO1-10-chest.dcm" },
{ 0,"DX_GE_FALCON_SNOWY-VOI.dcm" },
{ 0,"US-IRAD-NoPreambleStartWith0003.dcm" },
{ 0,"MR-Brucker-CineTagging-NonSquarePixels.dcm" },
{ 0,"D_CLUNIE_VL6_RLE.dcm" },
{ 0,"MR_Philips_Intera_PrivateSequenceImplicitVR.dcm" },
{ 0,"fffc0000UN.dcm" },
{ 0,"SIEMENS_Sonata-12-MONO2-SQ.dcm" },
{ 0,"ACUSON-24-YBR_FULL-RLE-b.dcm" },
{ 0,"CT-MONO2-16-ankle.dcm" },
{ 0,"GE_DLX-8-MONO2-Multiframe-Jpeg_Lossless.dcm" },
{ 0,"CT-MONO2-16-ort.dcm" },
{ 0,"LEADTOOLS_FLOWERS-16-MONO2-JpegLossless.dcm" },
{ 0,"D_CLUNIE_NM1_JPLL.dcm" },
{ 0,"D_CLUNIE_VL1_RLE.dcm" },
{ 0,"SIEMENS_MAGNETOM-12-MONO2-VRUN.dcm" },
{ 0,"00191113.dcm" },
{ 0,"TestVRSQUN2.dcm" },
{ 0,"PHILIPS_GDCM12xBug.dcm"},
{ 0,"PHILIPS_GDCM12xBug2.dcm"},
{ 0, NULL }
};

static int GetLossyFlagFromFilename(const char *filename)
{
  gdcm::Filename fn = filename;
  const char *file = fn.GetName();
  const LossyFile *pfiles = gdcmLossyFilenames;
  while( pfiles->filename && strcmp(pfiles->filename, file) != 0 )
    {
    ++pfiles;
    }
  assert( pfiles->filename ); // need to update ref table
  return pfiles->lossyflag;
}


int TestvtkGDCMImageReaderIsLossyFunc(const char *filename, bool verbose = false)
{
  gdcm::Filename fn = filename;
  vtkGDCMImageReader *reader = vtkGDCMImageReader::New();
  int canread = reader->CanReadFile( filename );
  int res = 0;
  if( canread )
    {
    reader->SetFileName( filename );
    reader->Update();
    if( verbose )
      {
      reader->GetOutput()->Print( cout );
      reader->GetMedicalImageProperties()->Print( cout );
      }
    int reflossy = GetLossyFlagFromFilename( filename );
    if( reader->GetLossyFlag() != reflossy )
      {
      std::cerr << "Mismatch for " << filename << std::endl;
      ++res;
      }
    }
  else
    {
    std::cerr << "Could not read: " << filename << std::endl;
    //++res;
    }

  return res;
}

int TestvtkGDCMImageReaderIsLossy(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestvtkGDCMImageReaderIsLossyFunc(filename, true);
    }

  // else
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  gdcm::Trace::ErrorOff();
  int r = 0, i = 0;
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestvtkGDCMImageReaderIsLossyFunc( filename );
    ++i;
    }

  return r;
}

