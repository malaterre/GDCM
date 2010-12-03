/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
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
{ "5f454449f557a87987dbb65d3cb7166a" , "012345.002.050.dcm" } ,
{ "94f8c6ab090bdc11e61625bfc2dd39b7" , "05115014-mr-siemens-avanto-syngo-with-palette-icone.dcm" } ,
{ "20c11831c616eb121a405cd73de5cba2" , "05148044-mr-siemens-avanto-syngo.dcm" } ,
{ "ec10dcbf1b13ace8a6c0cc5b24c6c870" , "3E768EB7.dcm" } ,
{ "fde1da68a1707dcc687ddffd57e6b3c3" , "ACUSON-24-YBR_FULL-RLE-b.dcm" } ,
{ "a27c6628d6379783a3be223481d5cba4" , "ACUSON-24-YBR_FULL-RLE.dcm" } ,
{ "9e98daa40dc5282afea4d34336a64666" , "ALOKA_SSD-8-MONO2-RLE-SQ.dcm" } ,
{ "3964c590f7046352a5ae34e9345a0a61" , "AMIInvalidPrivateDefinedLengthSQasUN.dcm" } ,
{ "d41d8cd98f00b204e9800998ecf8427e" , "BugGDCM2_UndefItemWrongVL.dcm" } ,
{ "6d2af85d2af299c223b684538d42d9e5" , "CR-MONO1-10-chest.dcm" } ,
{ "a899bd3c8c3eb38d9747c5617569528d" , "CT_16b_signed-UsedBits13.dcm" } ,
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
{ "5312abe97926da2d650bf4de5ea4f54f" , "D_CLUNIE_MR3_JPLL.dcm" } ,
{ "c3a0809d2ab8c983ac902b0005c1ea0b" , "D_CLUNIE_MR3_JPLY.dcm" } ,
{ "fa14406b8f52514b0ff196d04fa91bea" , "D_CLUNIE_MR3_RLE.dcm" } ,
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
{ "dc23864378e837d3602637bd9c99f24b" , "D_CLUNIE_SC1_JPLY.dcm" } ,
{ "06fe442d849f61665f69b3a782f44de3" , "D_CLUNIE_SC1_RLE.dcm" } ,
{ "ad377bc5cc50cb1b6312e9035417b2f1" , "D_CLUNIE_US1_RLE.dcm" } ,
{ "e6ea16c1ba4a8e8f97383811fd91288a" , "D_CLUNIE_VL1_RLE.dcm" } ,
{ "291ac2ee3c48a76ae0ab9a095199997c" , "D_CLUNIE_VL2_RLE.dcm" } ,
{ "91c92c4d1330c283012d2bdd3a91dc2f" , "D_CLUNIE_VL3_RLE.dcm" } ,
{ "fcc44b14754a56879e0f3afc8161c1c0" , "D_CLUNIE_VL4_RLE.dcm" } ,
{ "d7ded36c6827f41d61790bed41b963e3" , "D_CLUNIE_VL6_RLE.dcm" } ,
{ "75801e9732698ea89740f935052f28d6" , "D_CLUNIE_XA1_JPLL.dcm" } ,
{ "79d8daf6837a4b5aefaa963b1fb88df1" , "D_CLUNIE_XA1_JPLY.dcm" } ,
{ "e2bda8297745ab7a77ca84242ad4c980" , "D_CLUNIE_XA1_RLE.dcm" } ,
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
{ "384be0fbf581078184876d84d585cc34" , "DX_GE_FALCON_SNOWY-VOI.dcm" } ,
{ "1cbeb77ea2d6e0171dd38e0d6d5cb0b9" , "DX_J2K_0Padding.dcm" } ,
{ "3493bf0e698798529fde6ef488289879" , "ELSCINT1_JP2vsJ2K.dcm" } ,
{ "8f5581be656bd6f1ab6c9ec94f302284" , "ELSCINT1_LOSSLESS_RICE.dcm" } ,
{ "54f138a1aa6819ec1560a7ed344cde1a" , "ELSCINT1_PMSCT_RLE1.dcm" } ,
{ "18e05fe8d373ac875b08b3468a28959b" , "ExplicitVRforPublicElementsImplicitVRforShadowElements.dcm" } ,
{ "3199cd21166043d619209d7a2073fb56" , "fffc0000UN.dcm" } ,
{ "9b426b02521cbc2f3ee25ab383ca835e" , "FUJI-10-MONO1-ACR_NEMA_2.dcm" } ,
{ "678c2cb20ae5c8db45ac6fd8ed36e0c0" , "gdcm-ACR-LibIDO.acr" } ,
{ "b808c747b59f9d1a91a01491103abea5" , "gdcm-CR-DCMTK-16-NonSamplePerPix.dcm" } ,
{ "e7b5089a2a007221993ee5a7e6d44959" , "gdcm-JPEG-Extended.dcm" } ,
{ "20894653d750b4edf6034258a8dc3cf7" , "gdcm-JPEG-LossLess3a.dcm" } ,
{ "5011206e2a744c8a6f2cedb1ff7e5e11" , "gdcm-JPEG-LossLessThoravision.dcm" } ,
{ "aac111c65e51b61b63396ba227f75b3c" , "gdcm-MR-PHILIPS-16-Multi-Seq.dcm" } ,
{ "ae77e2e89fbe9f14080d06566f61be55" , "gdcm-MR-PHILIPS-16-NonSquarePixels.dcm" } ,
{ "9e64e55fc955b6323350487c9e9f92e4" , "gdcm-MR-SIEMENS-16-2.acr" } ,
{ "c8f971a788dabe50174080dc07f768dd" , "gdcm-US-ALOKA-16.dcm" } ,
{ "344cc60e30dce52b6b249616f1b6be34" , "GE_CT_With_Private_compressed-icon.dcm" } ,
{ "db9d5c273696ddd5c97235e4ecfde6c7" , "GE_DLX-8-MONO2-Multiframe.dcm" } ,
{ "3ace577106c6b68a18b1b1c7da294776" , "GE_DLX-8-MONO2-Multiframe-Jpeg_Lossless.dcm" } ,
{ "8796272a4a72ba995b558aad4111dce1" , "GE_DLX-8-MONO2-PrivateSyntax.dcm" } ,
{ "40197c524df4913601d1188a5281ca61" , "GE_GENESIS-16-MONO2-Uncompressed-UnusualVR.dcm" } ,
{ "78e714e2a119a44974ee11ad35abc7c6" , "GE_GENESIS-16-MONO2-WrongLengthItem.dcm" } ,
{ "6c8bc55de8824d273993328bde39ed06" , "GE_LOGIQBook-8-RGB-HugePreview.dcm" } ,
{ "c239ad29946fc31731123da9ca10df46" , "GE_MR_0025xx1bProtocolDataBlock.dcm" } ,
{ "d5efa34d8091e1ad04683eefb41f33c7" , "GE_RHAPSODE-16-MONO2-JPEG-Fragments.dcm" } ,
{ "d41d8cd98f00b204e9800998ecf8427e" , "IM-0001-0066.dcm" } ,
{ "cd085d783924d8a7fa2270ff40c6dc3e" , "ITK_GDCM124_MultiframeSecondaryCaptureInvalid.dcm" } ,
{ "b47e43977843d8ceae0fcd957baf2692" , "JDDICOM_Sample2.dcm" } ,
{ "132cb5de391304c8a4f7653118d72d99" , "JDDICOM_Sample2-dcmdjpeg.dcm" } ,
{ "26d62bfecd2133f20a8d622c9fe15b9a" , "JPEGDefinedLengthSequenceOfFragments.dcm" } ,
{ "9c0548b6cc474c309686cfc3bdff7723" , "JPEG_LossyYBR.dcm" } ,
{ "aabb6942cee8e8d2ecbd8706e6c10a53" , "KODAK-12-MONO1-Odd_Terminated_Sequence.dcm" } ,
{ "492ba4d8a4b904a15a4f14fe35b31a16" , "KODAK_CompressedIcon.dcm" } ,
{ "c733ceb4b8f026e29aaaff845872d98f" , "LEADTOOLS_FLOWERS-16-MONO2-JpegLossless.dcm" } ,
{ "1c40fbf3bc10bc10997b5febaaa2a130" , "LEADTOOLS_FLOWERS-16-MONO2-RLE.dcm" } ,
{ "750fee1e6f032bdd0c5a645f4fa60076" , "LEADTOOLS_FLOWERS-16-MONO2-Uncompressed.dcm" } ,
{ "90feead61cf0c9dd4d6752e1daebf236" , "LEADTOOLS_FLOWERS-24-RGB-JpegLossless.dcm" } ,
{ "31e2d8eb908124552cccd2cc9a3163f1" , "LEADTOOLS_FLOWERS-24-RGB-JpegLossy.dcm" } ,
{ "accbcdf1ea7d618774ea2717f591e3f5" , "LEADTOOLS_FLOWERS-24-RGB-Uncompressed.dcm" } ,
{ "9645d91a51a0b7f9b1e3c0583a48237c" , "LEADTOOLS_FLOWERS-8-MONO2-JpegLossy.dcm" } ,
{ "81faec8610f3d6af685929a2d1a233f4" , "LEADTOOLS_FLOWERS-8-MONO2-RLE.dcm" } ,
{ "cfda819277644393773107eb5a17718c" , "LEADTOOLS_FLOWERS-8-MONO2-Uncompressed.dcm" } ,
{ "fcb90ada06fdc12351bf34334171a210" , "LEADTOOLS_FLOWERS-8-PAL-RLE.dcm" } ,
{ "76fd0bda1efd513ef08cbf43094dff25" , "LEADTOOLS_FLOWERS-8-PAL-Uncompressed.dcm" } ,
{ "b33f1a1050fc7135295a02627be88514" , "libido1.0-vol.acr" } ,
{ "05fe8714421e16371d62ae2c280b7107" , "LIBIDO-16-ACR_NEMA-Volume.dcm" } ,
{ "04a35a16ab40fd3ed7708ce9a4022a3c" , "LIBIDO-24-ACR_NEMA-Rectangle.dcm" } ,
{ "9eb0ef9c007c7bae9bbf6b056957edc7" , "LIBIDO-8-ACR_NEMA-Lena_128_128.acr" } ,
{ "e39e4923be2d8bb2fb19c6c8deae216f" , "LJPEG_BuginGDCM12.dcm" } ,
{ "18e657fd8b160d69fba39449c0ba2fed" , "MARCONI_MxTWin-12-MONO2-JpegLossless-ZeroLengthSQ.dcm" } ,
{ "323582eda1e7349d980bee4368331d19" , "MAROTECH_CT_JP2Lossy.dcm" } ,
{ "497d6ea45b8f3f7f6a3bf8125dcc43b1" , "MR16BitsAllocated_8BitsStored.dcm" } ,
{ "5b23ccf10ad6358b253a7ec185deb2a9" , "MR-Brucker-CineTagging-NonSquarePixels.dcm" } ,
{ "efb94efa82833d1d5a0e1a132b9aae3b" , "MR_ELSCINT1_00e1_1042_SQ_feff_00e0_Item.dcm" } ,
{ "183916cc5947fd08dd846ba3e2cd7242" , "MR_GE_with_Private_Compressed_Icon_0009_1110.dcm" } ,
{ "299776ad327c80f5caed305943f26041" , "MR-MONO2-12-an2.acr" } ,
{ "b4058b67ec1eb3d3d3acde27d51eb24a" , "MR-MONO2-12-angio-an1.acr" } ,
{ "f782f6ea25928310bd69c3ca5c6a97d2" , "MR-MONO2-12-shoulder.dcm" } ,
{ "bb749bca66c96a81b92fb5f9bb4d57ae" , "MR-MONO2-16-head.dcm" } ,
{ "9bd4d79cc59c66b19c21577e12cd6226" , "MR-MONO2-8-16x-heart.dcm" } ,
{ "4763db7ab25c451f7162ddf6258b238f" , "MR_Philips-Intera_BreaksNOSHADOW.dcm" } ,
{ "185dd347d38424cc5085c1741223ca8a" , "MR_Philips_Intera_No_PrivateSequenceImplicitVR.dcm" } ,
{ "094f9a58fa555330f00d9784a24a5e04" , "MR_Philips_Intera_PrivateSequenceExplicitVR_in_SQ_2001_e05f_item_wrong_lgt_use_NOSHADOWSEQ.dcm" } ,
{ "49bcc77b22fee6f9304703af825d214d" , "MR_Philips_Intera_PrivateSequenceImplicitVR.dcm" } ,
{ "f26565ceee91b0ddf603608ced49042d" , "MR_Philips_Intera_SwitchIndianess_noLgtSQItem_in_trueLgtSeq.dcm" } ,
{ "5797c9dfe94e4a4bccfbf81ab0aaa957" , "MR-SIEMENS-DICOM-WithOverlays.dcm" } ,
{ "df28467760104edc923d0625a0e2a778" , "MR-SIEMENS-DICOM-WithOverlays-extracted-overlays.dcm" } ,
{ "410281597cc59494d761beac2232e8ab" , "MR_SIEMENS_forceLoad29-1010_29-1020.dcm" } ,
{ "406a2294caf6eb5f672a47fbcdf6b1af" , "MR_Spectroscopy_SIEMENS_OF.dcm" } ,
{ "1a5646a7b05840813c067d8c8dfa507e" , "NM-MONO2-16-13x-heart.dcm" } ,
{ "be9c6e57e78393edb4e119cb2729a017" , "OsirixFake16BitsStoredFakeSpacing.dcm" } ,
{ "bf793beb0e96f2399e467409e3cf5311" , "OT-MONO2-8-a7.dcm" } ,
{ "7f4cddc9a88f8c5147b89f769eb1cae7" , "OT-PAL-8-face.dcm" } ,
{ "5fce2728bd9457d4fc1224a374829e2f" , "PET-cardio-Multiframe-Papyrus.dcm" } ,
{ "dcf6fa4ff472d4f29ae0892f1ab192ae" , "PHILIPS_Brilliance_ExtraBytesInOverlay.dcm" } ,
{ "65010b18b3fd7e8d4df0b97cfb543c02" , "PHILIPS_GDCM12xBug2.dcm" } ,
{ "ed33d24414edfd3619c734c19ef31e1e" , "PHILIPS_GDCM12xBug.dcm" } ,
{ "fcb350ba5067d2a270ced2716653839b" , "PHILIPS_Gyroscan-12-Jpeg_Extended_Process_2_4.dcm" } ,
{ "10e457cb89cfa6f949f2e8727223419f" , "PHILIPS_Gyroscan-12-MONO2-Jpeg_Lossless.dcm" } ,
{ "99af15b3212778af66617830a74332a7" , "PHILIPS_Gyroscan-8-MONO2-Odd_Sequence.dcm" } ,
{ "67a9f2cb62a5261dbbdc235aecf792b1" , "PHILIPS_Intera-16-MONO2-Uncompress.dcm" } ,
{ "4f34474ed72e6a5960fc4691e588f8e0" , "PICKER-16-MONO2-Nested_icon.dcm" } ,
{ "629da04611e097e2cc532d6fe5e6454d" , "PICKER-16-MONO2-No_DicomV3_Preamble.dcm" } ,
{ "07f319ba477d9871cf3923ec1d00a9ce" , "PrivateGEImplicitVRBigEndianTransferSyntax16Bits.dcm" } ,
{ "6dc48ff6f48d3c09db2fe877630ab003" , "RadBWLossLess.dcm" } ,
{ "c2f13224f3f0bc3aa8bbfa6f4a0a23ec" , "rle16loo.dcm" } ,
{ "bd5d9b2f994cfc0c6a95cca8c586533a" , "rle16sti.dcm" } ,
{ "631c5bb2e2f046215999072d13316363" , "SIEMENS-12-Jpeg_Process_2_4-Lossy-a.dcm" } ,
{ "9eb576e20821d679c2feea1b92d9c26f" , "SIEMENS_CSA2.dcm" } ,
{ "a65ce69a3cafe393ea3da9daf022f4de" , "SIEMENS_GBS_III-16-ACR_NEMA_1.acr" } ,
{ "1178591e4f393fe007827898c9be7595" , "SIEMENS_GBS_III-16-ACR_NEMA_1-ULis2Bytes.dcm" } ,
{ "352cc53db896a0000b266ef62f2716a2" , "SIEMENS_ImageLocationUN.dcm" } ,
{ "9e64e55fc955b6323350487c9e9f92e4" , "SIEMENS_MAGNETOM-12-ACR_NEMA_2-Modern.dcm" } ,
{ "e233d618194797a72942791c59dbd5f9" , "SIEMENS_MAGNETOM-12-MONO2-FileSeq0.dcm" } ,
{ "2e89c063c5b6219fce4c4d792e74245a" , "SIEMENS_MAGNETOM-12-MONO2-FileSeq1.dcm" } ,
{ "5b591c20bcd9dd58a6855d44d03e3240" , "SIEMENS_MAGNETOM-12-MONO2-FileSeq2.dcm" } ,
{ "dfbac0614e1efd4c2c1e52d803262e9c" , "SIEMENS_MAGNETOM-12-MONO2-FileSeq3.dcm" } ,
{ "417457750452158c40f7257f0523feea" , "SIEMENS_MAGNETOM-12-MONO2-GDCM12-VRUN.dcm" } ,
{ "9342693510155452afcba1a2634caa78" , "SIEMENS_MAGNETOM-12-MONO2-Uncompressed.dcm" } ,
{ "90102b10f80b6490209717435321c542" , "SIEMENS_MAGNETOM-12-MONO2-VRUN.dcm" } ,
{ "39f786eeb0138ad4f36b59c20426de50" , "SIEMENS_MOSAIC_12BitsStored-16BitsJPEG.dcm" } ,
{ "be0b7098b442990aebf3364d747af482" , "SIEMENS-MR-RGB-16Bits.dcm" } ,
{ "47510716d1038c4764f672ece69f2e3c" , "SIEMENS_SOMATOM-12-ACR_NEMA-ZeroLengthUs.acr" } ,
{ "5fc4be2074b6186d3993818cd1baeb89" , "SIEMENS_Sonata-12-MONO2-SQ.dcm" } ,
{ "c56ae357244ed3d4203c2b28fe3ab447" , "SIEMENS_Sonata-16-MONO2-Value_Multiplicity.dcm" } ,
{ "7176eb4ec64dab63578eb6826318c87d" , "SignedShortLosslessBug.dcm" } ,
{ "ba40a5d86160fb17474759e7408c5326" , "simpleImageWithIcon.dcm" } ,
{ "2987c857782490447714cf647de007b4" , "test.acr" } ,
{ "da22013ebccaff9776bcc4f6d8410908" , "TG18-CH-2k-01.dcm" } ,
{ "e8cc7ed19eedf9bed9ab60683f3dbfa1" , "THERALYS-12-MONO2-Uncompressed-Even_Length_Tag.dcm" } ,
{ "8714b820cf8d4c8c67b01c94fbcfe8e2" , "TheralysGDCM120Bug.dcm" } ,
{ "e8819809884c214fe78ee2b227417e5c" , "TOSHIBA_MRT150-16-MONO2-ACR_NEMA_2.dcm" } ,
{ "8072c6d1d917e551490584bdaba4c1aa" , "undefined_length_un_vr.dcm" } ,
{ "9f154301c7d824f4e0d0162487ec076f" , "US-GE-4AICL142.dcm" } ,
{ "12e9aad7dece3da37f5f55cea59ab52b" , "US-IRAD-NoPreambleStartWith0003.dcm" } ,
{ "89c6059d75f59f6e33bb9ebcab7f9a0f" , "US-IRAD-NoPreambleStartWith0005.dcm" } ,
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
