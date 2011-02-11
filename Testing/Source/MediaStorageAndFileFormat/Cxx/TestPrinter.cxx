/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmReader.h"
#include "gdcmPrinter.h"
#include "gdcmFilename.h"
#include "gdcmTesting.h"

// the following list has been generated using gdcm, git: df760b9d8b3c9b280ad423153c649190f6e21204
// This correspond to the commit just before:
// BUG: an explicit length VR=SQ dataelement would not have been loaded as
// expected and a call to GetSequenceOfItems would fails. Thus downstream filter
// would fail load the SQ as expected. Introducing the more robust interface:
// GetValueAsSQ to solve that issue.
static const char * const printmd5[][2] = {
{ "a19bffac370df32acbf6b4991d1cbafe" , "00191113.dcm" } ,
{ "28f356915bc519137e2555db87e9914e" , "012345.002.050.dcm" } ,
{ "94f8c6ab090bdc11e61625bfc2dd39b7" , "05115014-mr-siemens-avanto-syngo-with-palette-icone.dcm" } ,
{ "20c11831c616eb121a405cd73de5cba2" , "05148044-mr-siemens-avanto-syngo.dcm" } ,
{ "ec10dcbf1b13ace8a6c0cc5b24c6c870" , "3E768EB7.dcm" } ,
{ "fde1da68a1707dcc687ddffd57e6b3c3" , "ACUSON-24-YBR_FULL-RLE-b.dcm" } ,
{ "a27c6628d6379783a3be223481d5cba4" , "ACUSON-24-YBR_FULL-RLE.dcm" } ,
{ "9f3aa114b955a812942f815b6b456eaf" , "ALOKA_SSD-8-MONO2-RLE-SQ.dcm" } ,
// MM: Check on Fri Jan 21 08:54:17 CET 2011, for AMIInvalidPrivateDefinedLengthSQasUN.dcm
{ "7e7c192969966d13823aff31482fd66e" , "AMIInvalidPrivateDefinedLengthSQasUN.dcm" } ,
{ "9bd2c821bdc3a53b5a6a09b581ef3b9c" , "BugGDCM2_UndefItemWrongVL.dcm" } ,
{ "6d2af85d2af299c223b684538d42d9e5" , "CR-MONO1-10-chest.dcm" } ,
{ "820d45cefd528e011921ea129bec9084" , "CT_16b_signed-UsedBits13.dcm" } ,
{ "2c956e431c1eb19464519a7101134848" , "CT-MONO2-12-lomb-an2.acr" } ,
{ "0e4137f63819c706dfa370405d662c79" , "CT-MONO2-16-ankle.dcm" } ,
{ "f00a663066627e7ecdd1a7379137d396" , "CT-MONO2-16-brain.dcm" } ,
{ "87eadd3a3460c13593c9468bc533aa58" , "CT-MONO2-16-chest.dcm" } ,
{ "8b0efbe7cfd72a7d14cef44683fbacab" , "CT-MONO2-16-ort.dcm" } ,
{ "32c8e40e0726bbcc374f20771d37a312" , "CT-MONO2-8-abdo.dcm" } ,
{ "c5ffd15172c43b200e3654d5e3e45f3e" , "CT-SIEMENS-Icone-With-PaletteColor.dcm" } ,
{ "c1fcd1d9d218c03007a868fc2e22ba1a" , "CT-SIEMENS-MissingPixelDataInIconSQ.dcm" } ,
{ "a46ca467a0df5e1c71c8017b6b6768e7" , "D_CLUNIE_CT1_J2KI.dcm" } ,
{ "d2698545b07ad721faa71fdc1cf4a35d" , "D_CLUNIE_CT1_J2KR.dcm" } ,
{ "78f619a764a94a2c2bdc084d53ad2577" , "D_CLUNIE_CT1_JPLL.dcm" } ,
{ "4aaa4a602d7a1fd80c023acba36d6a84" , "D_CLUNIE_CT1_RLE.dcm" } ,
{ "9ee24f3a3291cd86f0bc78fddc3417e7" , "D_CLUNIE_CT2_JPLL.dcm" } ,
{ "b01b2b28aa3caa945b05865a9c440349" , "D_CLUNIE_CT2_RLE.dcm" } ,
{ "7d6531dc92c53ad25835b75fa5505b66" , "D_CLUNIE_MR1_JPLL.dcm" } ,
{ "e8a970a1c861192331a98162146ee0f9" , "D_CLUNIE_MR1_JPLY.dcm" } ,
{ "6f8b7b128c86c5a670a284e7eac38391" , "D_CLUNIE_MR1_RLE.dcm" } ,
{ "b770b1ca257d7c1c885f69a5a1b58808" , "D_CLUNIE_MR2_JPLL.dcm" } ,
{ "da74aefef4e8ac49dbe1a4dd3b1dcb26" , "D_CLUNIE_MR2_JPLY.dcm" } ,
{ "023eb2a9ecbfd3c04bb148ec339865f0" , "D_CLUNIE_MR2_RLE.dcm" } ,
{ "923d4103e1b063db6ed895fb67395750" , "D_CLUNIE_MR3_JPLL.dcm" } ,
{ "11b9cfc714d6f8eadc7b8b9c871f7b7d" , "D_CLUNIE_MR3_JPLY.dcm" } ,
{ "6773ea516bf525ed1278d23e402a4e78" , "D_CLUNIE_MR3_RLE.dcm" } ,
{ "1646ec013060ef3f261849db705f80f3" , "D_CLUNIE_MR4_JPLL.dcm" } ,
{ "fbbfe4caab2179641bd0de5d8ccf79ae" , "D_CLUNIE_MR4_JPLY.dcm" } ,
{ "fafdb8499580e59c2f6d9047894272ea" , "D_CLUNIE_MR4_RLE.dcm" } ,
{ "bc35454da5d8c0825236ccae83adcb82" , "D_CLUNIE_NM1_JPLL.dcm" } ,
{ "03527dbfa9b0b82fee7d6eb601abf470" , "D_CLUNIE_NM1_JPLY.dcm" } ,
{ "9488a473e2cd1fc981f36643e7dc1b82" , "D_CLUNIE_NM1_RLE.dcm" } ,
{ "d9da8798488b1c825dbd4ef940e386b9" , "D_CLUNIE_RG1_JPLL.dcm" } ,
{ "68a498853d26cce827eefb0f8be3581d" , "D_CLUNIE_RG1_RLE.dcm" } ,
{ "9f652b621320650c6be743b6bafcf539" , "D_CLUNIE_RG2_JPLL.dcm" } ,
{ "1f0e2edba097f4491b7d45fed604729d" , "D_CLUNIE_RG2_JPLY.dcm" } ,
{ "403e0e40507608cdcd61ee461de91226" , "D_CLUNIE_RG2_RLE.dcm" } ,
{ "73ecf348f874e7fb69f5dbfb4637979e" , "D_CLUNIE_RG3_JPLL.dcm" } ,
{ "b97b49d7f0bc3a3c3cb421292d8f13b5" , "D_CLUNIE_RG3_JPLY.dcm" } ,
{ "ec7dcf6857238547f0fb43f51317b05f" , "D_CLUNIE_RG3_RLE.dcm" } ,
{ "af35b9ad269b8a37df3d25389655272e" , "D_CLUNIE_SC1_JPLY.dcm" } ,
{ "50f92b02a370e2858632dfde330a2881" , "D_CLUNIE_SC1_RLE.dcm" } ,
{ "ad377bc5cc50cb1b6312e9035417b2f1" , "D_CLUNIE_US1_RLE.dcm" } ,
{ "e6ea16c1ba4a8e8f97383811fd91288a" , "D_CLUNIE_VL1_RLE.dcm" } ,
{ "291ac2ee3c48a76ae0ab9a095199997c" , "D_CLUNIE_VL2_RLE.dcm" } ,
{ "91c92c4d1330c283012d2bdd3a91dc2f" , "D_CLUNIE_VL3_RLE.dcm" } ,
{ "fcc44b14754a56879e0f3afc8161c1c0" , "D_CLUNIE_VL4_RLE.dcm" } ,
{ "d7ded36c6827f41d61790bed41b963e3" , "D_CLUNIE_VL6_RLE.dcm" } ,
{ "75801e9732698ea89740f935052f28d6" , "D_CLUNIE_XA1_JPLL.dcm" } ,
{ "79d8daf6837a4b5aefaa963b1fb88df1" , "D_CLUNIE_XA1_JPLY.dcm" } ,
{ "e2bda8297745ab7a77ca84242ad4c980" , "D_CLUNIE_XA1_RLE.dcm" } ,
{ "bb52d9f7a9116c87103066dd18a60e68" , "D_CLUNIE_CT1_JLSN.dcm" } ,
{ "8984d6319cd913d0f88fdb61989412f2" , "D_CLUNIE_CT1_JLSL.dcm" } ,
{ "4ef94d44a83066b80b39d254fb2a1c28" , "DCMTK_JPEGExt_12Bits.dcm" } ,
{ "d982dca9cc6c9db94a6233ca76e52f26" , "DermaColorLossLess.dcm" } ,
{ "ee354d9b221360982f15b630e1fdb046" , "DICOMDIR" } ,
{ "3082f3a587959183b5c24ae8d7ec5b08" , "dicomdir_Acusson_WithPrivate_WithSR" } ,
{ "9934ab3c8adca82cad0fe8997b6c5cd3" , "DICOMDIR_MR_B_VA12A" } ,
{ "f66c6315c53ce8e6a0fe8ba93d7f85a3" , "DICOMDIR-Philips-EasyVision-4200-Entries" } ,
{ "4254e4123245565e43a86e191acff01b" , "dicomdir_Pms_With_heavy_embedded_sequence" } ,
{ "9afc3c3e9d208292430b45867a9981e1" , "dicomdir_Pms_WithVisit_WithPrivate_WithStudyComponents" } ,
{ "356f30be965bbe4e335a56c6c5fe1928" , "dicomdir_With_embedded_icons" } ,
{ "d174a9f2dea0da9e013eb3180317ebbc" , "DMCPACS_ExplicitImplicit_BogusIOP.dcm" } ,
{ "9a0fe39ec08581ad5e07966023225d33" , "DX_GE_FALCON_SNOWY-VOI.dcm" } ,
{ "1cbeb77ea2d6e0171dd38e0d6d5cb0b9" , "DX_J2K_0Padding.dcm" } ,
{ "3493bf0e698798529fde6ef488289879" , "ELSCINT1_JP2vsJ2K.dcm" } ,
{ "8f5581be656bd6f1ab6c9ec94f302284" , "ELSCINT1_LOSSLESS_RICE.dcm" } ,
{ "54f138a1aa6819ec1560a7ed344cde1a" , "ELSCINT1_PMSCT_RLE1.dcm" } ,
{ "c90e737452eb2693d7af15ec8d077210" , "ExplicitVRforPublicElementsImplicitVRforShadowElements.dcm" } ,
{ "3199cd21166043d619209d7a2073fb56" , "fffc0000UN.dcm" } ,
{ "9b426b02521cbc2f3ee25ab383ca835e" , "FUJI-10-MONO1-ACR_NEMA_2.dcm" } ,
{ "678c2cb20ae5c8db45ac6fd8ed36e0c0" , "gdcm-ACR-LibIDO.acr" } ,
{ "b808c747b59f9d1a91a01491103abea5" , "gdcm-CR-DCMTK-16-NonSamplePerPix.dcm" } ,
{ "e7b5089a2a007221993ee5a7e6d44959" , "gdcm-JPEG-Extended.dcm" } ,
{ "20894653d750b4edf6034258a8dc3cf7" , "gdcm-JPEG-LossLess3a.dcm" } ,
{ "5011206e2a744c8a6f2cedb1ff7e5e11" , "gdcm-JPEG-LossLessThoravision.dcm" } ,
{ "9a70209e955acef6a65aa13edebc0b09" , "gdcm-MR-PHILIPS-16-Multi-Seq.dcm" } ,
{ "5156ad3b72556dfd8de94b348c6c95a6" , "gdcm-MR-PHILIPS-16-NonSquarePixels.dcm" } ,
{ "0f1ccdbb08b15c5b31f207410195136e" , "gdcm-MR-SIEMENS-16-2.acr" } ,
{ "48c49a7a41a7efea9ea0eadcd89ac9fa" , "gdcm-US-ALOKA-16.dcm" } ,
{ "9e9f42e825db2951519320c2e907d936" , "GE_CT_With_Private_compressed-icon.dcm" } ,
{ "9e126a24f81534e1cd653f16739a6192" , "GE_DLX-8-MONO2-Multiframe.dcm" } ,
{ "48565dfe4c2d72ff12e6257a29a5a917" , "GE_DLX-8-MONO2-Multiframe-Jpeg_Lossless.dcm" } ,
{ "61ca6c5115e6f74565f6f2ca06647444" , "GE_DLX-8-MONO2-PrivateSyntax.dcm" } ,
{ "2ed065d325227d88abfaaa7b6b693b75" , "GE_GENESIS-16-MONO2-Uncompressed-UnusualVR.dcm" } ,
{ "8d398fce426d3a248d8c3f7582e3751d" , "GE_GENESIS-16-MONO2-WrongLengthItem.dcm" } ,
{ "e854973d5aa7ad3ae6adcaa8cf9ef170" , "GE_LOGIQBook-8-RGB-HugePreview.dcm" } ,
{ "e2813fcfdd414f256ac2a8a2002d9257" , "GE_MR_0025xx1bProtocolDataBlock.dcm" } ,
{ "d5efa34d8091e1ad04683eefb41f33c7" , "GE_RHAPSODE-16-MONO2-JPEG-Fragments.dcm" } ,
{ "d41d8cd98f00b204e9800998ecf8427e" , "IM-0001-0066.dcm" } ,
{ "cd085d783924d8a7fa2270ff40c6dc3e" , "ITK_GDCM124_MultiframeSecondaryCaptureInvalid.dcm" } ,
{ "b47e43977843d8ceae0fcd957baf2692" , "JDDICOM_Sample2.dcm" } ,
{ "132cb5de391304c8a4f7653118d72d99" , "JDDICOM_Sample2-dcmdjpeg.dcm" } ,
{ "26d62bfecd2133f20a8d622c9fe15b9a" , "JPEGDefinedLengthSequenceOfFragments.dcm" } ,
{ "9c0548b6cc474c309686cfc3bdff7723" , "JPEG_LossyYBR.dcm" } ,
{ "aabb6942cee8e8d2ecbd8706e6c10a53" , "KODAK-12-MONO1-Odd_Terminated_Sequence.dcm" } ,
{ "492ba4d8a4b904a15a4f14fe35b31a16" , "KODAK_CompressedIcon.dcm" } ,
{ "9a085a611f192d6939b992be4e02fc8f" , "LEADTOOLS_FLOWERS-16-MONO2-JpegLossless.dcm" } ,
{ "4c884d7e06658c53275c932358e83f50" , "LEADTOOLS_FLOWERS-16-MONO2-RLE.dcm" } ,
{ "b879261a881099f66c6417487b5727e6" , "LEADTOOLS_FLOWERS-16-MONO2-Uncompressed.dcm" } ,
{ "792f30183573b0a228a8d372de1fd3e2" , "LEADTOOLS_FLOWERS-24-RGB-JpegLossless.dcm" } ,
{ "9163d48f9b103792d7cc2401bd880efc" , "LEADTOOLS_FLOWERS-24-RGB-JpegLossy.dcm" } ,
{ "0b88e68d7629601e885db6126bdec0e5" , "LEADTOOLS_FLOWERS-24-RGB-Uncompressed.dcm" } ,
{ "3cbcc077573136a5cc96bd9cc4c6d42e" , "LEADTOOLS_FLOWERS-8-MONO2-JpegLossy.dcm" } ,
{ "a3074d046c5f382f62e6ee6b3f9561ea" , "LEADTOOLS_FLOWERS-8-MONO2-RLE.dcm" } ,
{ "b31da32c67ac695376cc928150be98d2" , "LEADTOOLS_FLOWERS-8-MONO2-Uncompressed.dcm" } ,
{ "ea9f4285ce92f9db2e349c7132fb849e" , "LEADTOOLS_FLOWERS-8-PAL-RLE.dcm" } ,
{ "9bac4c50cd8afce8f9995cefd542760f" , "LEADTOOLS_FLOWERS-8-PAL-Uncompressed.dcm" } ,
{ "b33f1a1050fc7135295a02627be88514" , "libido1.0-vol.acr" } ,
{ "05fe8714421e16371d62ae2c280b7107" , "LIBIDO-16-ACR_NEMA-Volume.dcm" } ,
{ "04a35a16ab40fd3ed7708ce9a4022a3c" , "LIBIDO-24-ACR_NEMA-Rectangle.dcm" } ,
{ "9eb0ef9c007c7bae9bbf6b056957edc7" , "LIBIDO-8-ACR_NEMA-Lena_128_128.acr" } ,
{ "e39e4923be2d8bb2fb19c6c8deae216f" , "LJPEG_BuginGDCM12.dcm" } ,
{ "e630b285247cd5197deb6bd958ea4e12" , "MARCONI_MxTWin-12-MONO2-JpegLossless-ZeroLengthSQ.dcm" } ,
{ "d257376f880ceeda31b5c3de869e3edb" , "MAROTECH_CT_JP2Lossy.dcm" } ,
{ "497d6ea45b8f3f7f6a3bf8125dcc43b1" , "MR16BitsAllocated_8BitsStored.dcm" } ,
{ "5b23ccf10ad6358b253a7ec185deb2a9" , "MR-Brucker-CineTagging-NonSquarePixels.dcm" } ,
{ "a75dfbf0919ce81cb02c43dab9efebbe" , "MR_ELSCINT1_00e1_1042_SQ_feff_00e0_Item.dcm" } ,
{ "c5042379519ac6b25df96b4ada96e9b1" , "MR_GE_with_Private_Compressed_Icon_0009_1110.dcm" } ,
{ "299776ad327c80f5caed305943f26041" , "MR-MONO2-12-an2.acr" } ,
{ "b4058b67ec1eb3d3d3acde27d51eb24a" , "MR-MONO2-12-angio-an1.acr" } ,
{ "f782f6ea25928310bd69c3ca5c6a97d2" , "MR-MONO2-12-shoulder.dcm" } ,
{ "7f6bccb00b34a7d277eacaffd2bb0362" , "MR-MONO2-16-head.dcm" } ,
{ "9bd4d79cc59c66b19c21577e12cd6226" , "MR-MONO2-8-16x-heart.dcm" } ,
{ "4763db7ab25c451f7162ddf6258b238f" , "MR_Philips-Intera_BreaksNOSHADOW.dcm" } ,
{ "d88c879b5c7a8d4e3f20f177df94a76d" , "MR_Philips_Intera_No_PrivateSequenceImplicitVR.dcm" } ,
{ "abce00bceef1711dca51e26950fc7a61" , "MR_Philips_Intera_PrivateSequenceExplicitVR_in_SQ_2001_e05f_item_wrong_lgt_use_NOSHADOWSEQ.dcm" } ,
{ "9b80a64ce87ac061b185991cb046c64c" , "MR_Philips_Intera_PrivateSequenceImplicitVR.dcm" } ,
{ "27af4f8d827b0a7863ee724c401145d9" , "MR_Philips_Intera_SwitchIndianess_noLgtSQItem_in_trueLgtSeq.dcm" } ,
{ "5797c9dfe94e4a4bccfbf81ab0aaa957" , "MR-SIEMENS-DICOM-WithOverlays.dcm" } ,
{ "df28467760104edc923d0625a0e2a778" , "MR-SIEMENS-DICOM-WithOverlays-extracted-overlays.dcm" } ,
{ "bf324a1c91d3a09d9136f54f5910e570" , "MR_SIEMENS_forceLoad29-1010_29-1020.dcm" } ,
{ "9d8b55ae15d62e35ec861132f80f3f17" , "MR_Spectroscopy_SIEMENS_OF.dcm" } ,
{ "1a5646a7b05840813c067d8c8dfa507e" , "NM-MONO2-16-13x-heart.dcm" } ,
{ "8d8c3b8eb830b57b162e7c9f2d64b214" , "OsirixFake16BitsStoredFakeSpacing.dcm" } ,
{ "bf793beb0e96f2399e467409e3cf5311" , "OT-MONO2-8-a7.dcm" } ,
{ "7f4cddc9a88f8c5147b89f769eb1cae7" , "OT-PAL-8-face.dcm" } ,
{ "5fce2728bd9457d4fc1224a374829e2f" , "PET-cardio-Multiframe-Papyrus.dcm" } ,
{ "071b840050588d14fde61646e058e1c6" , "PHILIPS_Brilliance_ExtraBytesInOverlay.dcm" } ,
{ "e6fffe81f8cf9a4f4b852b7599668821" , "PHILIPS_GDCM12xBug2.dcm" } ,
{ "d86e618d5f4e46f8bc2f14c23b10ec81" , "PHILIPS_GDCM12xBug.dcm" } ,
{ "fcb350ba5067d2a270ced2716653839b" , "PHILIPS_Gyroscan-12-Jpeg_Extended_Process_2_4.dcm" } ,
{ "d335e74b45c8381ce73965ee3aad4c14" , "PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm" } ,
{ "ea5cfb4c8ef6d41db52817ddd83223f1" , "PHILIPS_Gyroscan-8-MONO2-Odd_Sequence.dcm" } ,
{ "7c2c337ea316be2575a4a892b7ecd02f" , "PHILIPS_Intera-16-MONO2-Uncompress.dcm" } ,
{ "4f34474ed72e6a5960fc4691e588f8e0" , "PICKER-16-MONO2-Nested_icon.dcm" } ,
{ "629da04611e097e2cc532d6fe5e6454d" , "PICKER-16-MONO2-No_DicomV3_Preamble.dcm" } ,
{ "df9760cfb62c7ca0d34631c67e3c0c1c" , "PrivateGEImplicitVRBigEndianTransferSyntax16Bits.dcm" } ,
{ "6dc48ff6f48d3c09db2fe877630ab003" , "RadBWLossLess.dcm" } ,
{ "c2f13224f3f0bc3aa8bbfa6f4a0a23ec" , "rle16loo.dcm" } ,
{ "bd5d9b2f994cfc0c6a95cca8c586533a" , "rle16sti.dcm" } ,
{ "631c5bb2e2f046215999072d13316363" , "SIEMENS-12-Jpeg_Process_2_4-Lossy-a.dcm" } ,
{ "593324f844b730f77bb4a337f51f3b3d" , "SIEMENS_CSA2.dcm" } ,
{ "a65ce69a3cafe393ea3da9daf022f4de" , "SIEMENS_GBS_III-16-ACR_NEMA_1.acr" } ,
{ "1178591e4f393fe007827898c9be7595" , "SIEMENS_GBS_III-16-ACR_NEMA_1-ULis2Bytes.dcm" } ,
{ "a26065c162b9afc8a80a03136c90d964" , "SIEMENS_ImageLocationUN.dcm" } ,
{ "0f1ccdbb08b15c5b31f207410195136e" , "SIEMENS_MAGNETOM-12-ACR_NEMA_2-Modern.dcm" } ,
{ "bd3192fceb97c99234588f4dc0ede9a1" , "SIEMENS_MAGNETOM-12-MONO2-FileSeq0.dcm" } ,
{ "21fd55d395dd07103824ce1c9e81a478" , "SIEMENS_MAGNETOM-12-MONO2-FileSeq1.dcm" } ,
{ "c3cab40fd34aebaa7f4fe7d1365e7d23" , "SIEMENS_MAGNETOM-12-MONO2-FileSeq2.dcm" } ,
{ "4d94d892c1c017410f6daab39a6367f3" , "SIEMENS_MAGNETOM-12-MONO2-FileSeq3.dcm" } ,
{ "417457750452158c40f7257f0523feea" , "SIEMENS_MAGNETOM-12-MONO2-GDCM12-VRUN.dcm" } ,
{ "a15300a90340c4b4c8d15af91a7cb71e" , "SIEMENS_MAGNETOM-12-MONO2-Uncompressed.dcm" } ,
{ "90102b10f80b6490209717435321c542" , "SIEMENS_MAGNETOM-12-MONO2-VRUN.dcm" } ,
{ "9ca5aebcd31ea271799858c32df18524" , "SIEMENS_MOSAIC_12BitsStored-16BitsJPEG.dcm" } ,
{ "be0b7098b442990aebf3364d747af482" , "SIEMENS-MR-RGB-16Bits.dcm" } ,
{ "47510716d1038c4764f672ece69f2e3c" , "SIEMENS_SOMATOM-12-ACR_NEMA-ZeroLengthUs.acr" } ,
{ "5fc4be2074b6186d3993818cd1baeb89" , "SIEMENS_Sonata-12-MONO2-SQ.dcm" } ,
{ "c56ae357244ed3d4203c2b28fe3ab447" , "SIEMENS_Sonata-16-MONO2-Value_Multiplicity.dcm" } ,
{ "7176eb4ec64dab63578eb6826318c87d" , "SignedShortLosslessBug.dcm" } ,
{ "ba40a5d86160fb17474759e7408c5326" , "simpleImageWithIcon.dcm" } ,
{ "2987c857782490447714cf647de007b4" , "test.acr" } ,
{ "0c2c475f6d21ae0aeadbf16565dcdbc4" , "TG18-CH-2k-01.dcm" } ,
{ "e8cc7ed19eedf9bed9ab60683f3dbfa1" , "THERALYS-12-MONO2-Uncompressed-Even_Length_Tag.dcm" } ,
{ "beda2947fcc433aa0c694377a23b553d" , "TheralysGDCM120Bug.dcm" } ,
{ "e8819809884c214fe78ee2b227417e5c" , "TOSHIBA_MRT150-16-MONO2-ACR_NEMA_2.dcm" } ,
{ "e6e83ba0c5435ad355767cd5eb9512b6" , "undefined_length_un_vr.dcm" } ,
{ "ec1a38a5d00cab38c58b906cad9b8103" , "US-GE-4AICL142.dcm" } ,
{ "b894d6f1bf24b583fde241ee0b2cf3d5" , "US-IRAD-NoPreambleStartWith0003.dcm" } ,
{ "d9ede0f035b532025cf47630f350ea22" , "US-IRAD-NoPreambleStartWith0005.dcm" } ,
{ "17222122d388f2c1185884c644c041db" , "US-MONO2-8-8x-execho.dcm" } ,
{ "d58a4930f5b436939d297730b883d5b9" , "US-PAL-8-10x-echo.dcm" } ,
{ "e0552f839d327506c32c4b9ceeb56459" , "US-RGB-8-epicard.dcm" } ,
{ "77bd6ff6dcac8e4fb763253e047dbdd2" , "US-RGB-8-esopecho.dcm" } ,
{ "7a3535f869f4a450b8de3d73a268e713" , "XA-MONO2-8-12x-catheter.dcm" } ,
  { 0 ,0 }
};

int TestPrint(const char *filename, bool verbose= false)
{
  gdcm::Reader r;
  r.SetFileName( filename );
  if( !r.Read() )
    {
    return 1;
    }

  gdcm::Printer print;
  print.SetFile( r.GetFile() );
  std::ostringstream out;
  if( verbose )
    print.Print( std::cout );
  print.Print( out );

  std::string buf = out.str();
  char digest[33];
  gdcm::Testing::ComputeMD5(&buf[0], buf.size(), digest);

  gdcm::Filename fn( filename );
  const char *name = fn.GetName();

  unsigned int i = 0;
  const char *p = printmd5[i][1];
  while( p != 0 )
    {
    if( strcmp( name, p ) == 0 )
      {
      break;
      }
    ++i;
    p = printmd5[i][1];
    }

  const char *refmd5 = printmd5[i][0];
  if( !refmd5 )
    {
    std::cerr << "Problem with : " << name << " missing md5= " << digest << std::endl;
    return 1;
    }
  if( strcmp( refmd5, digest) )
    {
    std::cerr << "Problem with : " << name << " " << refmd5 << " vs " << digest << std::endl;
    return 1;
    }

  return 0;
}


int TestPrinter(int argc, char *argv[])
{
  if( argc == 2 )
    {
    const char *filename = argv[1];
    return TestPrint(filename, true);
    }

  // else
  int r = 0, i = 0;
  gdcm::Trace::DebugOff();
  gdcm::Trace::WarningOff();
  const char *filename;
  const char * const *filenames = gdcm::Testing::GetFileNames();
  while( (filename = filenames[i]) )
    {
    r += TestPrint( filename );
    ++i;
    }

  return r;
}
