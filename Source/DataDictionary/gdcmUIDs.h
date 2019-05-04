// Arrays can be generated
// $ xsltproc UIDToC++.xsl Part6.xml > tmp.cxx
// they may be not backward compatible (retired,
// manually added in the past, etc.) and
// don't contain private elements, have to be reviewed

/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef GDCMUIDS_H
#define GDCMUIDS_H

#include "gdcmTypes.h"

namespace gdcm
{

/**
 * \brief all known uids
 */
class GDCM_EXPORT UIDs
{
public:
  typedef enum {
uid_1_2_840_10008_1_1 = 1, // Verification SOP Class
uid_1_2_840_10008_1_2 = 2, // Implicit VR Little Endian: Default Transfer Syntax for DICOM
uid_1_2_840_10008_1_2_1 = 3, // Explicit VR Little Endian
uid_1_2_840_10008_1_2_1_99 = 4, // Deflated Explicit VR Little Endian
uid_1_2_840_10008_1_2_2 = 5, // Explicit VR Big Endian
uid_1_2_840_10008_1_2_4_50 = 6, // JPEG Baseline (Process 1): Default Transfer Syntax for Lossy JPEG 8 Bit Image Compression
uid_1_2_840_10008_1_2_4_51 = 7, // JPEG Extended (Process 2 & 4): Default Transfer Syntax for Lossy JPEG 12 Bit Image Compression (Process 4 only)
uid_1_2_840_10008_1_2_4_52 = 8, // JPEG Extended (Process 3 & 5)
uid_1_2_840_10008_1_2_4_53 = 9, // JPEG Spectral Selection, Non-Hierarchical (Process 6 & 8)
uid_1_2_840_10008_1_2_4_54 = 10, // JPEG Spectral Selection, Non-Hierarchical (Process 7 & 9)
uid_1_2_840_10008_1_2_4_55 = 11, // JPEG Full Progression, Non-Hierarchical (Process 10 & 12)
uid_1_2_840_10008_1_2_4_56 = 12, // JPEG Full Progression, Non-Hierarchical (Process 11 & 13)
uid_1_2_840_10008_1_2_4_57 = 13, // JPEG Lossless, Non-Hierarchical (Process 14)
uid_1_2_840_10008_1_2_4_58 = 14, // JPEG Lossless, Non-Hierarchical (Process 15)
uid_1_2_840_10008_1_2_4_59 = 15, // JPEG Extended, Hierarchical (Process 16 & 18)
uid_1_2_840_10008_1_2_4_60 = 16, // JPEG Extended, Hierarchical (Process 17 & 19)
uid_1_2_840_10008_1_2_4_61 = 17, // JPEG Spectral Selection, Hierarchical (Process 20 & 22)
uid_1_2_840_10008_1_2_4_62 = 18, // JPEG Spectral Selection, Hierarchical (Process 21 & 23)
uid_1_2_840_10008_1_2_4_63 = 19, // JPEG Full Progression, Hierarchical (Process 24 & 26)
uid_1_2_840_10008_1_2_4_64 = 20, // JPEG Full Progression, Hierarchical (Process 25 & 27)
uid_1_2_840_10008_1_2_4_65 = 21, // JPEG Lossless, Hierarchical (Process 28)
uid_1_2_840_10008_1_2_4_66 = 22, // JPEG Lossless, Hierarchical (Process 29)
uid_1_2_840_10008_1_2_4_70 = 23, // JPEG Lossless, Non-Hierarchical, First-Order Prediction (Process 14 [Selection Value 1]): Default Transfer Syntax for Lossless JPEG Image Compression
uid_1_2_840_10008_1_2_4_80 = 24, // JPEG-LS Lossless Image Compression
uid_1_2_840_10008_1_2_4_81 = 25, // JPEG-LS Lossy (Near-Lossless) Image Compression
uid_1_2_840_10008_1_2_4_90 = 26, // JPEG 2000 Image Compression (Lossless Only)
uid_1_2_840_10008_1_2_4_91 = 27, // JPEG 2000 Image Compression
uid_1_2_840_10008_1_2_4_92 = 28, // JPEG 2000 Part 2 Multi-component Image Compression (Lossless Only)
uid_1_2_840_10008_1_2_4_93 = 29, // JPEG 2000 Part 2 Multi-component Image Compression
uid_1_2_840_10008_1_2_4_94 = 30, // JPIP Referenced
uid_1_2_840_10008_1_2_4_95 = 31, // JPIP Referenced Deflate
uid_1_2_840_10008_1_2_4_100 = 32, // MPEG2 Main Profile @ Main Level
uid_1_2_840_10008_1_2_4_101 = 33, // MPEG2 Main Profile @ High Level
uid_1_2_840_10008_1_2_4_102 = 34, // MPEG-4 AVC/H.264 High Profile @ Level 4.1
uid_1_2_840_10008_1_2_4_103 = 35, // MPEG-4 AVC/H.264 BD-compatible High Profile @ Level 4.1
uid_1_2_840_10008_1_2_4_104 = 36, // MPEG-4 AVC/H.264 High Profile @ Level 4.2 For 2D Video
uid_1_2_840_10008_1_2_4_105 = 37, // MPEG-4 AVC/H.264 High Profile @ Level 4.2 For 3D Video
uid_1_2_840_10008_1_2_4_106 = 38, // MPEG-4 AVC/H.264 Stereo High Profile @ Level 4.2
uid_1_2_840_10008_1_2_4_107 = 39, // HEVC/H.265 Main Profile @ Level 5.1
uid_1_2_840_10008_1_2_4_108 = 40, // HEVC/H.265 Main 10 Profile @ Level 5.1
uid_1_2_840_10008_1_2_5 = 41, // RLE Lossless
uid_1_2_840_10008_1_2_6_1 = 42, // RFC 2557 MIME encapsulation
uid_1_2_840_10008_1_2_6_2 = 43, // XML Encoding
uid_1_2_840_10008_1_3_10 = 44, // Media Storage Directory Storage
uid_1_2_840_10008_1_4_1_1 = 45, // Talairach Brain Atlas Frame of Reference
uid_1_2_840_10008_1_4_1_2 = 46, // SPM2 T1 Frame of Reference
uid_1_2_840_10008_1_4_1_3 = 47, // SPM2 T2 Frame of Reference
uid_1_2_840_10008_1_4_1_4 = 48, // SPM2 PD Frame of Reference
uid_1_2_840_10008_1_4_1_5 = 49, // SPM2 EPI Frame of Reference
uid_1_2_840_10008_1_4_1_6 = 50, // SPM2 FIL T1 Frame of Reference
uid_1_2_840_10008_1_4_1_7 = 51, // SPM2 PET Frame of Reference
uid_1_2_840_10008_1_4_1_8 = 52, // SPM2 TRANSM Frame of Reference
uid_1_2_840_10008_1_4_1_9 = 53, // SPM2 SPECT Frame of Reference
uid_1_2_840_10008_1_4_1_10 = 54, // SPM2 GRAY Frame of Reference
uid_1_2_840_10008_1_4_1_11 = 55, // SPM2 WHITE Frame of Reference
uid_1_2_840_10008_1_4_1_12 = 56, // SPM2 CSF Frame of Reference
uid_1_2_840_10008_1_4_1_13 = 57, // SPM2 BRAINMASK Frame of Reference
uid_1_2_840_10008_1_4_1_14 = 58, // SPM2 AVG305T1 Frame of Reference
uid_1_2_840_10008_1_4_1_15 = 59, // SPM2 AVG152T1 Frame of Reference
uid_1_2_840_10008_1_4_1_16 = 60, // SPM2 AVG152T2 Frame of Reference
uid_1_2_840_10008_1_4_1_17 = 61, // SPM2 AVG152PD Frame of Reference
uid_1_2_840_10008_1_4_1_18 = 62, // SPM2 SINGLESUBJT1 Frame of Reference
uid_1_2_840_10008_1_4_2_1 = 63, // ICBM 452 T1 Frame of Reference
uid_1_2_840_10008_1_4_2_2 = 64, // ICBM Single Subject MRI Frame of Reference
uid_1_2_840_10008_1_5_1 = 65, // Hot Iron Color Palette SOP Instance
uid_1_2_840_10008_1_5_2 = 66, // PET Color Palette SOP Instance
uid_1_2_840_10008_1_5_3 = 67, // Hot Metal Blue Color Palette SOP Instance
uid_1_2_840_10008_1_5_4 = 68, // PET 20 Step Color Palette SOP Instance
uid_1_2_840_10008_1_5_5 = 69, // Spring Color Palette SOP Instance
uid_1_2_840_10008_1_5_6 = 70, // Summer Color Palette SOP Instance
uid_1_2_840_10008_1_5_7 = 71, // Fall Color Palette SOP Instance
uid_1_2_840_10008_1_5_8 = 72, // Winter Color Palette SOP Instance
uid_1_2_840_10008_1_9 = 73, // Basic Study Content Notification SOP Class
uid_1_2_840_10008_1_20 = 74, // Papyrus 3 Implicit VR Little Endian
uid_1_2_840_10008_1_20_1 = 75, // Storage Commitment Push Model SOP Class
uid_1_2_840_10008_1_20_1_1 = 76, // Storage Commitment Push Model SOP Instance
uid_1_2_840_10008_1_20_2 = 77, // Storage Commitment Pull Model SOP Class
uid_1_2_840_10008_1_20_2_1 = 78, // Storage Commitment Pull Model SOP Instance
uid_1_2_840_10008_1_40 = 79, // Procedural Event Logging SOP Class
uid_1_2_840_10008_1_40_1 = 80, // Procedural Event Logging SOP Instance
uid_1_2_840_10008_1_42 = 81, // Substance Administration Logging SOP Class
uid_1_2_840_10008_1_42_1 = 82, // Substance Administration Logging SOP Instance
uid_1_2_840_10008_2_6_1 = 83, // DICOM UID Registry
uid_1_2_840_10008_2_16_4 = 84, // DICOM Controlled Terminology
uid_1_2_840_10008_2_16_5 = 85, // Adult Mouse Anatomy Ontology
uid_1_2_840_10008_2_16_6 = 86, // Uberon Ontology
uid_1_2_840_10008_2_16_7 = 87, // Integrated Taxonomic Information System (ITIS) Taxonomic Serial Number (TSN)
uid_1_2_840_10008_2_16_8 = 88, // Mouse Genome Initiative (MGI)
uid_1_2_840_10008_2_16_9 = 89, // PubChem Compound CID
uid_1_2_840_10008_2_16_10 = 90, // ICD-11
uid_1_2_840_10008_2_16_11 = 91, // New York University Melanoma Clinical Cooperative Group
uid_1_2_840_10008_2_16_12 = 92, // Mayo Clinic Non-radiological Images Specific Body Structure Anatomical Surface Region Guide
uid_1_2_840_10008_2_16_13 = 93, // Image Biomarker Standardisation Initiative
uid_1_2_840_10008_2_16_14 = 94, // Radiomics Ontology
uid_1_2_840_10008_3_1_1_1 = 95, // DICOM Application Context Name
uid_1_2_840_10008_3_1_2_1_1 = 96, // Detached Patient Management SOP Class
uid_1_2_840_10008_3_1_2_1_4 = 97, // Detached Patient Management Meta SOP Class
uid_1_2_840_10008_3_1_2_2_1 = 98, // Detached Visit Management SOP Class
uid_1_2_840_10008_3_1_2_3_1 = 99, // Detached Study Management SOP Class
uid_1_2_840_10008_3_1_2_3_2 = 100, // Study Component Management SOP Class
uid_1_2_840_10008_3_1_2_3_3 = 101, // Modality Performed Procedure Step SOP Class
uid_1_2_840_10008_3_1_2_3_4 = 102, // Modality Performed Procedure Step Retrieve SOP Class
uid_1_2_840_10008_3_1_2_3_5 = 103, // Modality Performed Procedure Step Notification SOP Class
uid_1_2_840_10008_3_1_2_5_1 = 104, // Detached Results Management SOP Class
uid_1_2_840_10008_3_1_2_5_4 = 105, // Detached Results Management Meta SOP Class
uid_1_2_840_10008_3_1_2_5_5 = 106, // Detached Study Management Meta SOP Class
uid_1_2_840_10008_3_1_2_6_1 = 107, // Detached Interpretation Management SOP Class
uid_1_2_840_10008_4_2 = 108, // Storage Service Class
uid_1_2_840_10008_5_1_1_1 = 109, // Basic Film Session SOP Class
uid_1_2_840_10008_5_1_1_2 = 110, // Basic Film Box SOP Class
uid_1_2_840_10008_5_1_1_4 = 111, // Basic Grayscale Image Box SOP Class
uid_1_2_840_10008_5_1_1_4_1 = 112, // Basic Color Image Box SOP Class
uid_1_2_840_10008_5_1_1_4_2 = 113, // Referenced Image Box SOP Class
uid_1_2_840_10008_5_1_1_9 = 114, // Basic Grayscale Print Management Meta SOP Class
uid_1_2_840_10008_5_1_1_9_1 = 115, // Referenced Grayscale Print Management Meta SOP Class
uid_1_2_840_10008_5_1_1_14 = 116, // Print Job SOP Class
uid_1_2_840_10008_5_1_1_15 = 117, // Basic Annotation Box SOP Class
uid_1_2_840_10008_5_1_1_16 = 118, // Printer SOP Class
uid_1_2_840_10008_5_1_1_16_376 = 119, // Printer Configuration Retrieval SOP Class
uid_1_2_840_10008_5_1_1_17 = 120, // Printer SOP Instance
uid_1_2_840_10008_5_1_1_17_376 = 121, // Printer Configuration Retrieval SOP Instance
uid_1_2_840_10008_5_1_1_18 = 122, // Basic Color Print Management Meta SOP Class
uid_1_2_840_10008_5_1_1_18_1 = 123, // Referenced Color Print Management Meta SOP Class
uid_1_2_840_10008_5_1_1_22 = 124, // VOI LUT Box SOP Class
uid_1_2_840_10008_5_1_1_23 = 125, // Presentation LUT SOP Class
uid_1_2_840_10008_5_1_1_24 = 126, // Image Overlay Box SOP Class
uid_1_2_840_10008_5_1_1_24_1 = 127, // Basic Print Image Overlay Box SOP Class
uid_1_2_840_10008_5_1_1_25 = 128, // Print Queue SOP Instance
uid_1_2_840_10008_5_1_1_26 = 129, // Print Queue Management SOP Class
uid_1_2_840_10008_5_1_1_27 = 130, // Stored Print Storage SOP Class
uid_1_2_840_10008_5_1_1_29 = 131, // Hardcopy Grayscale Image Storage SOP Class
uid_1_2_840_10008_5_1_1_30 = 132, // Hardcopy Color Image Storage SOP Class
uid_1_2_840_10008_5_1_1_31 = 133, // Pull Print Request SOP Class
uid_1_2_840_10008_5_1_1_32 = 134, // Pull Stored Print Management Meta SOP Class
uid_1_2_840_10008_5_1_1_33 = 135, // Media Creation Management SOP Class UID
uid_1_2_840_10008_5_1_1_40 = 136, // Display System SOP Class
uid_1_2_840_10008_5_1_1_40_1 = 137, // Display System SOP Instance
uid_1_2_840_10008_5_1_4_1_1_1 = 138, // Computed Radiography Image Storage
uid_1_2_840_10008_5_1_4_1_1_1_1 = 139, // Digital X-Ray Image Storage - For Presentation
uid_1_2_840_10008_5_1_4_1_1_1_1_1 = 140, // Digital X-Ray Image Storage - For Processing
uid_1_2_840_10008_5_1_4_1_1_1_2 = 141, // Digital Mammography X-Ray Image Storage - For Presentation
uid_1_2_840_10008_5_1_4_1_1_1_2_1 = 142, // Digital Mammography X-Ray Image Storage - For Processing
uid_1_2_840_10008_5_1_4_1_1_1_3 = 143, // Digital Intra-Oral X-Ray Image Storage - For Presentation
uid_1_2_840_10008_5_1_4_1_1_1_3_1 = 144, // Digital Intra-Oral X-Ray Image Storage - For Processing
uid_1_2_840_10008_5_1_4_1_1_2 = 145, // CT Image Storage
uid_1_2_840_10008_5_1_4_1_1_2_1 = 146, // Enhanced CT Image Storage
uid_1_2_840_10008_5_1_4_1_1_2_2 = 147, // Legacy Converted Enhanced CT Image Storage
uid_1_2_840_10008_5_1_4_1_1_3 = 148, // Ultrasound Multi-frame Image Storage
uid_1_2_840_10008_5_1_4_1_1_3_1 = 149, // Ultrasound Multi-frame Image Storage
uid_1_2_840_10008_5_1_4_1_1_4 = 150, // MR Image Storage
uid_1_2_840_10008_5_1_4_1_1_4_1 = 151, // Enhanced MR Image Storage
uid_1_2_840_10008_5_1_4_1_1_4_2 = 152, // MR Spectroscopy Storage
uid_1_2_840_10008_5_1_4_1_1_4_3 = 153, // Enhanced MR Color Image Storage
uid_1_2_840_10008_5_1_4_1_1_4_4 = 154, // Legacy Converted Enhanced MR Image Storage
uid_1_2_840_10008_5_1_4_1_1_5 = 155, // Nuclear Medicine Image Storage
uid_1_2_840_10008_5_1_4_1_1_6 = 156, // Ultrasound Image Storage
uid_1_2_840_10008_5_1_4_1_1_6_1 = 157, // Ultrasound Image Storage
uid_1_2_840_10008_5_1_4_1_1_6_2 = 158, // Enhanced US Volume Storage
uid_1_2_840_10008_5_1_4_1_1_7 = 159, // Secondary Capture Image Storage
uid_1_2_840_10008_5_1_4_1_1_7_1 = 160, // Multi-frame Single Bit Secondary Capture Image Storage
uid_1_2_840_10008_5_1_4_1_1_7_2 = 161, // Multi-frame Grayscale Byte Secondary Capture Image Storage
uid_1_2_840_10008_5_1_4_1_1_7_3 = 162, // Multi-frame Grayscale Word Secondary Capture Image Storage
uid_1_2_840_10008_5_1_4_1_1_7_4 = 163, // Multi-frame True Color Secondary Capture Image Storage
uid_1_2_840_10008_5_1_4_1_1_8 = 164, // Standalone Overlay Storage
uid_1_2_840_10008_5_1_4_1_1_9 = 165, // Standalone Curve Storage
uid_1_2_840_10008_5_1_4_1_1_9_1 = 166, // Waveform Storage - Trial
uid_1_2_840_10008_5_1_4_1_1_9_1_1 = 167, // 12-lead ECG Waveform Storage
uid_1_2_840_10008_5_1_4_1_1_9_1_2 = 168, // General ECG Waveform Storage
uid_1_2_840_10008_5_1_4_1_1_9_1_3 = 169, // Ambulatory ECG Waveform Storage
uid_1_2_840_10008_5_1_4_1_1_9_2_1 = 170, // Hemodynamic Waveform Storage
uid_1_2_840_10008_5_1_4_1_1_9_3_1 = 171, // Cardiac Electrophysiology Waveform Storage
uid_1_2_840_10008_5_1_4_1_1_9_4_1 = 172, // Basic Voice Audio Waveform Storage
uid_1_2_840_10008_5_1_4_1_1_9_4_2 = 173, // General Audio Waveform Storage
uid_1_2_840_10008_5_1_4_1_1_9_5_1 = 174, // Arterial Pulse Waveform Storage
uid_1_2_840_10008_5_1_4_1_1_9_6_1 = 175, // Respiratory Waveform Storage
uid_1_2_840_10008_5_1_4_1_1_10 = 176, // Standalone Modality LUT Storage
uid_1_2_840_10008_5_1_4_1_1_11 = 177, // Standalone VOI LUT Storage
uid_1_2_840_10008_5_1_4_1_1_11_1 = 178, // Grayscale Softcopy Presentation State Storage
uid_1_2_840_10008_5_1_4_1_1_11_2 = 179, // Color Softcopy Presentation State Storage
uid_1_2_840_10008_5_1_4_1_1_11_3 = 180, // Pseudo-Color Softcopy Presentation State Storage
uid_1_2_840_10008_5_1_4_1_1_11_4 = 181, // Blending Softcopy Presentation State Storage
uid_1_2_840_10008_5_1_4_1_1_11_5 = 182, // XA/XRF Grayscale Softcopy Presentation State Storage
uid_1_2_840_10008_5_1_4_1_1_11_6 = 183, // Grayscale Planar MPR Volumetric Presentation State Storage
uid_1_2_840_10008_5_1_4_1_1_11_7 = 184, // Compositing Planar MPR Volumetric Presentation State Storage
uid_1_2_840_10008_5_1_4_1_1_11_8 = 185, // Advanced Blending Presentation State Storage
uid_1_2_840_10008_5_1_4_1_1_11_9 = 186, // Volume Rendering Volumetric Presentation State Storage
uid_1_2_840_10008_5_1_4_1_1_11_10 = 187, // Segmented Volume Rendering Volumetric Presentation State Storage
uid_1_2_840_10008_5_1_4_1_1_11_11 = 188, // Multiple Volume Rendering Volumetric Presentation State Storage
uid_1_2_840_10008_5_1_4_1_1_12_1 = 189, // X-Ray Angiographic Image Storage
uid_1_2_840_10008_5_1_4_1_1_12_1_1 = 190, // Enhanced XA Image Storage
uid_1_2_840_10008_5_1_4_1_1_12_2 = 191, // X-Ray Radiofluoroscopic Image Storage
uid_1_2_840_10008_5_1_4_1_1_12_2_1 = 192, // Enhanced XRF Image Storage
uid_1_2_840_10008_5_1_4_1_1_12_3 = 193, // X-Ray Angiographic Bi-Plane Image Storage
uid_1_2_840_10008_5_1_4_1_1_12_77 = 194, // 
uid_1_2_840_10008_5_1_4_1_1_13_1_1 = 195, // X-Ray 3D Angiographic Image Storage
uid_1_2_840_10008_5_1_4_1_1_13_1_2 = 196, // X-Ray 3D Craniofacial Image Storage
uid_1_2_840_10008_5_1_4_1_1_13_1_3 = 197, // Breast Tomosynthesis Image Storage
uid_1_2_840_10008_5_1_4_1_1_13_1_4 = 198, // Breast Projection X-Ray Image Storage - For Presentation
uid_1_2_840_10008_5_1_4_1_1_13_1_5 = 199, // Breast Projection X-Ray Image Storage - For Processing
uid_1_2_840_10008_5_1_4_1_1_14_1 = 200, // Intravascular Optical Coherence Tomography Image Storage - For Presentation
uid_1_2_840_10008_5_1_4_1_1_14_2 = 201, // Intravascular Optical Coherence Tomography Image Storage - For Processing
uid_1_2_840_10008_5_1_4_1_1_20 = 202, // Nuclear Medicine Image Storage
uid_1_2_840_10008_5_1_4_1_1_30 = 203, // Parametric Map Storage
uid_1_2_840_10008_5_1_4_1_1_40 = 204, // 
uid_1_2_840_10008_5_1_4_1_1_66 = 205, // Raw Data Storage
uid_1_2_840_10008_5_1_4_1_1_66_1 = 206, // Spatial Registration Storage
uid_1_2_840_10008_5_1_4_1_1_66_2 = 207, // Spatial Fiducials Storage
uid_1_2_840_10008_5_1_4_1_1_66_3 = 208, // Deformable Spatial Registration Storage
uid_1_2_840_10008_5_1_4_1_1_66_4 = 209, // Segmentation Storage
uid_1_2_840_10008_5_1_4_1_1_66_5 = 210, // Surface Segmentation Storage
uid_1_2_840_10008_5_1_4_1_1_66_6 = 211, // Tractography Results Storage
uid_1_2_840_10008_5_1_4_1_1_67 = 212, // Real World Value Mapping Storage
uid_1_2_840_10008_5_1_4_1_1_68_1 = 213, // Surface Scan Mesh Storage
uid_1_2_840_10008_5_1_4_1_1_68_2 = 214, // Surface Scan Point Cloud Storage
uid_1_2_840_10008_5_1_4_1_1_77_1 = 215, // VL Image Storage - Trial
uid_1_2_840_10008_5_1_4_1_1_77_2 = 216, // VL Multi-frame Image Storage - Trial
uid_1_2_840_10008_5_1_4_1_1_77_1_1 = 217, // VL Endoscopic Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_1_1 = 218, // Video Endoscopic Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_2 = 219, // VL Microscopic Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_2_1 = 220, // Video Microscopic Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_3 = 221, // VL Slide-Coordinates Microscopic Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_4 = 222, // VL Photographic Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_4_1 = 223, // Video Photographic Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_5_1 = 224, // Ophthalmic Photography 8 Bit Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_5_2 = 225, // Ophthalmic Photography 16 Bit Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_5_3 = 226, // Stereometric Relationship Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_5_4 = 227, // Ophthalmic Tomography Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_5_5 = 228, // Wide Field Ophthalmic Photography Stereographic Projection Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_5_6 = 229, // Wide Field Ophthalmic Photography 3D Coordinates Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_5_7 = 230, // Ophthalmic Optical Coherence Tomography En Face Image Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_5_8 = 231, // Ophthalmic Optical Coherence Tomography B-scan Volume Analysis Storage
uid_1_2_840_10008_5_1_4_1_1_77_1_6 = 232, // VL Whole Slide Microscopy Image Storage
uid_1_2_840_10008_5_1_4_1_1_78_1 = 233, // Lensometry Measurements Storage
uid_1_2_840_10008_5_1_4_1_1_78_2 = 234, // Autorefraction Measurements Storage
uid_1_2_840_10008_5_1_4_1_1_78_3 = 235, // Keratometry Measurements Storage
uid_1_2_840_10008_5_1_4_1_1_78_4 = 236, // Subjective Refraction Measurements Storage
uid_1_2_840_10008_5_1_4_1_1_78_5 = 237, // Visual Acuity Measurements Storage
uid_1_2_840_10008_5_1_4_1_1_78_6 = 238, // Spectacle Prescription Report Storage
uid_1_2_840_10008_5_1_4_1_1_78_7 = 239, // Ophthalmic Axial Measurements Storage
uid_1_2_840_10008_5_1_4_1_1_78_8 = 240, // Intraocular Lens Calculations Storage
uid_1_2_840_10008_5_1_4_1_1_79_1 = 241, // Macular Grid Thickness and Volume Report Storage
uid_1_2_840_10008_5_1_4_1_1_80_1 = 242, // Ophthalmic Visual Field Static Perimetry Measurements Storage
uid_1_2_840_10008_5_1_4_1_1_81_1 = 243, // Ophthalmic Thickness Map Storage
uid_1_2_840_10008_5_1_4_1_1_82_1 = 244, // Corneal Topography Map Storage
uid_1_2_840_10008_5_1_4_1_1_88_1 = 245, // Text SR Storage - Trial
uid_1_2_840_10008_5_1_4_1_1_88_2 = 246, // Audio SR Storage - Trial
uid_1_2_840_10008_5_1_4_1_1_88_3 = 247, // Detail SR Storage - Trial
uid_1_2_840_10008_5_1_4_1_1_88_4 = 248, // Comprehensive SR Storage - Trial
uid_1_2_840_10008_5_1_4_1_1_88_11 = 249, // Basic Text SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_22 = 250, // Enhanced SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_33 = 251, // Comprehensive SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_34 = 252, // Comprehensive 3D SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_35 = 253, // Extensible SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_40 = 254, // Procedure Log Storage
uid_1_2_840_10008_5_1_4_1_1_88_50 = 255, // Mammography CAD SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_59 = 256, // Key Object Selection Document Storage
uid_1_2_840_10008_5_1_4_1_1_88_65 = 257, // Chest CAD SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_67 = 258, // X-Ray Radiation Dose SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_68 = 259, // Radiopharmaceutical Radiation Dose SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_69 = 260, // Colon CAD SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_70 = 261, // Implantation Plan SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_71 = 262, // Acquisition Context SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_72 = 263, // Simplified Adult Echo SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_73 = 264, // Patient Radiation Dose SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_74 = 265, // Planned Imaging Agent Administration SR Storage
uid_1_2_840_10008_5_1_4_1_1_88_75 = 266, // Performed Imaging Agent Administration SR Storage
uid_1_2_840_10008_5_1_4_1_1_90_1 = 267, // Content Assessment Results Storage
uid_1_2_840_10008_5_1_4_1_1_104_1 = 268, // Encapsulated PDF Storage
uid_1_2_840_10008_5_1_4_1_1_104_2 = 269, // Encapsulated CDA Storage
uid_1_2_840_10008_5_1_4_1_1_104_3 = 270, // Encapsulated STL Storage
uid_1_2_840_10008_5_1_4_1_1_128 = 271, // Positron Emission Tomography Image Storage
uid_1_2_840_10008_5_1_4_1_1_128_1 = 272, // Legacy Converted Enhanced PET Image Storage
uid_1_2_840_10008_5_1_4_1_1_129 = 273, // Standalone PET Curve Storage
uid_1_2_840_10008_5_1_4_1_1_130 = 274, // Enhanced PET Image Storage
uid_1_2_840_10008_5_1_4_1_1_131 = 275, // Basic Structured Display Storage
uid_1_2_840_10008_5_1_4_1_1_200_1 = 276, // CT Defined Procedure Protocol Storage
uid_1_2_840_10008_5_1_4_1_1_200_2 = 277, // CT Performed Procedure Protocol Storage
uid_1_2_840_10008_5_1_4_1_1_200_3 = 278, // Protocol Approval Storage
uid_1_2_840_10008_5_1_4_1_1_200_4 = 279, // Protocol Approval Information Model - FIND
uid_1_2_840_10008_5_1_4_1_1_200_5 = 280, // Protocol Approval Information Model - MOVE
uid_1_2_840_10008_5_1_4_1_1_200_6 = 281, // Protocol Approval Information Model - GET
uid_1_2_840_10008_5_1_4_1_1_481_1 = 282, // RT Image Storage
uid_1_2_840_10008_5_1_4_1_1_481_2 = 283, // RT Dose Storage
uid_1_2_840_10008_5_1_4_1_1_481_3 = 284, // RT Structure Set Storage
uid_1_2_840_10008_5_1_4_1_1_481_4 = 285, // RT Beams Treatment Record Storage
uid_1_2_840_10008_5_1_4_1_1_481_5 = 286, // RT Plan Storage
uid_1_2_840_10008_5_1_4_1_1_481_6 = 287, // RT Brachy Treatment Record Storage
uid_1_2_840_10008_5_1_4_1_1_481_7 = 288, // RT Treatment Summary Record Storage
uid_1_2_840_10008_5_1_4_1_1_481_8 = 289, // RT Ion Plan Storage
uid_1_2_840_10008_5_1_4_1_1_481_9 = 290, // RT Ion Beams Treatment Record Storage
uid_1_2_840_10008_5_1_4_1_1_481_10 = 291, // RT Physician Intent Storage
uid_1_2_840_10008_5_1_4_1_1_481_11 = 292, // RT Segment Annotation Storage
uid_1_2_840_10008_5_1_4_1_1_501_1 = 293, // DICOS CT Image Storage
uid_1_2_840_10008_5_1_4_1_1_501_2_1 = 294, // DICOS Digital X-Ray Image Storage - For Presentation
uid_1_2_840_10008_5_1_4_1_1_501_2_2 = 295, // DICOS Digital X-Ray Image Storage - For Processing
uid_1_2_840_10008_5_1_4_1_1_501_3 = 296, // DICOS Threat Detection Report Storage
uid_1_2_840_10008_5_1_4_1_1_501_4 = 297, // DICOS 2D AIT Storage
uid_1_2_840_10008_5_1_4_1_1_501_5 = 298, // DICOS 3D AIT Storage
uid_1_2_840_10008_5_1_4_1_1_501_6 = 299, // DICOS Quadrupole Resonance (QR) Storage
uid_1_2_840_10008_5_1_4_1_1_601_1 = 300, // Eddy Current Image Storage
uid_1_2_840_10008_5_1_4_1_1_601_2 = 301, // Eddy Current Multi-frame Image Storage
uid_1_2_840_10008_5_1_4_1_2_1_1 = 302, // Patient Root Query/Retrieve Information Model - FIND
uid_1_2_840_10008_5_1_4_1_2_1_2 = 303, // Patient Root Query/Retrieve Information Model - MOVE
uid_1_2_840_10008_5_1_4_1_2_1_3 = 304, // Patient Root Query/Retrieve Information Model - GET
uid_1_2_840_10008_5_1_4_1_2_2_1 = 305, // Study Root Query/Retrieve Information Model - FIND
uid_1_2_840_10008_5_1_4_1_2_2_2 = 306, // Study Root Query/Retrieve Information Model - MOVE
uid_1_2_840_10008_5_1_4_1_2_2_3 = 307, // Study Root Query/Retrieve Information Model - GET
uid_1_2_840_10008_5_1_4_1_2_3_1 = 308, // Patient/Study Only Query/Retrieve Information Model - FIND
uid_1_2_840_10008_5_1_4_1_2_3_2 = 309, // Patient/Study Only Query/Retrieve Information Model - MOVE
uid_1_2_840_10008_5_1_4_1_2_3_3 = 310, // Patient/Study Only Query/Retrieve Information Model - GET
uid_1_2_840_10008_5_1_4_1_2_4_2 = 311, // Composite Instance Root Retrieve - MOVE
uid_1_2_840_10008_5_1_4_1_2_4_3 = 312, // Composite Instance Root Retrieve - GET
uid_1_2_840_10008_5_1_4_1_2_5_3 = 313, // Composite Instance Retrieve Without Bulk Data - GET
uid_1_2_840_10008_5_1_4_20_1 = 314, // Defined Procedure Protocol Information Model - FIND
uid_1_2_840_10008_5_1_4_20_2 = 315, // Defined Procedure Protocol Information Model - MOVE
uid_1_2_840_10008_5_1_4_20_3 = 316, // Defined Procedure Protocol Information Model - GET
uid_1_2_840_10008_5_1_4_31 = 317, // Modality Worklist Information Model - FIND
uid_1_2_840_10008_5_1_4_32 = 318, // General Purpose Worklist Management Meta SOP Class
uid_1_2_840_10008_5_1_4_32_1 = 319, // General Purpose Worklist Information Model - FIND
uid_1_2_840_10008_5_1_4_32_2 = 320, // General Purpose Scheduled Procedure Step SOP Class
uid_1_2_840_10008_5_1_4_32_3 = 321, // General Purpose Performed Procedure Step SOP Class
uid_1_2_840_10008_5_1_4_33 = 322, // Instance Availability Notification SOP Class
uid_1_2_840_10008_5_1_4_34_1 = 323, // RT Beams Delivery Instruction Storage - Trial
uid_1_2_840_10008_5_1_4_34_2 = 324, // RT Conventional Machine Verification - Trial
uid_1_2_840_10008_5_1_4_34_3 = 325, // RT Ion Machine Verification - Trial
uid_1_2_840_10008_5_1_4_34_4 = 326, // Unified Worklist and Procedure Step Service Class - Trial
uid_1_2_840_10008_5_1_4_34_4_1 = 327, // Unified Procedure Step - Push SOP Class - Trial
uid_1_2_840_10008_5_1_4_34_4_2 = 328, // Unified Procedure Step - Watch SOP Class - Trial
uid_1_2_840_10008_5_1_4_34_4_3 = 329, // Unified Procedure Step - Pull SOP Class - Trial
uid_1_2_840_10008_5_1_4_34_4_4 = 330, // Unified Procedure Step - Event SOP Class - Trial
uid_1_2_840_10008_5_1_4_34_5 = 331, // UPS Global Subscription SOP Instance
uid_1_2_840_10008_5_1_4_34_5_1 = 332, // UPS Filtered Global Subscription SOP Instance
uid_1_2_840_10008_5_1_4_34_6 = 333, // Unified Worklist and Procedure Step Service Class
uid_1_2_840_10008_5_1_4_34_6_1 = 334, // Unified Procedure Step - Push SOP Class
uid_1_2_840_10008_5_1_4_34_6_2 = 335, // Unified Procedure Step - Watch SOP Class
uid_1_2_840_10008_5_1_4_34_6_3 = 336, // Unified Procedure Step - Pull SOP Class
uid_1_2_840_10008_5_1_4_34_6_4 = 337, // Unified Procedure Step - Event SOP Class
uid_1_2_840_10008_5_1_4_34_7 = 338, // RT Beams Delivery Instruction Storage
uid_1_2_840_10008_5_1_4_34_8 = 339, // RT Conventional Machine Verification
uid_1_2_840_10008_5_1_4_34_9 = 340, // RT Ion Machine Verification
uid_1_2_840_10008_5_1_4_34_10 = 341, // RT Brachy Application Setup Delivery Instruction Storage
uid_1_2_840_10008_5_1_4_37_1 = 342, // General Relevant Patient Information Query
uid_1_2_840_10008_5_1_4_37_2 = 343, // Breast Imaging Relevant Patient Information Query
uid_1_2_840_10008_5_1_4_37_3 = 344, // Cardiac Relevant Patient Information Query
uid_1_2_840_10008_5_1_4_38_1 = 345, // Hanging Protocol Storage
uid_1_2_840_10008_5_1_4_38_2 = 346, // Hanging Protocol Information Model - FIND
uid_1_2_840_10008_5_1_4_38_3 = 347, // Hanging Protocol Information Model - MOVE
uid_1_2_840_10008_5_1_4_38_4 = 348, // Hanging Protocol Information Model - GET
uid_1_2_840_10008_5_1_4_39_1 = 349, // Color Palette Storage
uid_1_2_840_10008_5_1_4_39_2 = 350, // Color Palette Query/Retrieve Information Model - FIND
uid_1_2_840_10008_5_1_4_39_3 = 351, // Color Palette Query/Retrieve Information Model - MOVE
uid_1_2_840_10008_5_1_4_39_4 = 352, // Color Palette Query/Retrieve Information Model - GET
uid_1_2_840_10008_5_1_4_41 = 353, // Product Characteristics Query SOP Class
uid_1_2_840_10008_5_1_4_42 = 354, // Substance Approval Query SOP Class
uid_1_2_840_10008_5_1_4_43_1 = 355, // Generic Implant Template Storage
uid_1_2_840_10008_5_1_4_43_2 = 356, // Generic Implant Template Information Model - FIND
uid_1_2_840_10008_5_1_4_43_3 = 357, // Generic Implant Template Information Model - MOVE
uid_1_2_840_10008_5_1_4_43_4 = 358, // Generic Implant Template Information Model - GET
uid_1_2_840_10008_5_1_4_44_1 = 359, // Implant Assembly Template Storage
uid_1_2_840_10008_5_1_4_44_2 = 360, // Implant Assembly Template Information Model - FIND
uid_1_2_840_10008_5_1_4_44_3 = 361, // Implant Assembly Template Information Model - MOVE
uid_1_2_840_10008_5_1_4_44_4 = 362, // Implant Assembly Template Information Model - GET
uid_1_2_840_10008_5_1_4_45_1 = 363, // Implant Template Group Storage
uid_1_2_840_10008_5_1_4_45_2 = 364, // Implant Template Group Information Model - FIND
uid_1_2_840_10008_5_1_4_45_3 = 365, // Implant Template Group Information Model - MOVE
uid_1_2_840_10008_5_1_4_45_4 = 366, // Implant Template Group Information Model - GET
uid_1_2_840_10008_7_1_1 = 367, // Native DICOM Model
uid_1_2_840_10008_7_1_2 = 368, // Abstract Multi-Dimensional Image Model
uid_1_2_840_10008_8_1_1 = 369, // DICOM Content Mapping Resource
uid_1_2_840_10008_15_0_3_1 = 370, // dicomDeviceName
uid_1_2_840_10008_15_0_3_2 = 371, // dicomDescription
uid_1_2_840_10008_15_0_3_3 = 372, // dicomManufacturer
uid_1_2_840_10008_15_0_3_4 = 373, // dicomManufacturerModelName
uid_1_2_840_10008_15_0_3_5 = 374, // dicomSoftwareVersion
uid_1_2_840_10008_15_0_3_6 = 375, // dicomVendorData
uid_1_2_840_10008_15_0_3_7 = 376, // dicomAETitle
uid_1_2_840_10008_15_0_3_8 = 377, // dicomNetworkConnectionReference
uid_1_2_840_10008_15_0_3_9 = 378, // dicomApplicationCluster
uid_1_2_840_10008_15_0_3_10 = 379, // dicomAssociationInitiator
uid_1_2_840_10008_15_0_3_11 = 380, // dicomAssociationAcceptor
uid_1_2_840_10008_15_0_3_12 = 381, // dicomHostname
uid_1_2_840_10008_15_0_3_13 = 382, // dicomPort
uid_1_2_840_10008_15_0_3_14 = 383, // dicomSOPClass
uid_1_2_840_10008_15_0_3_15 = 384, // dicomTransferRole
uid_1_2_840_10008_15_0_3_16 = 385, // dicomTransferSyntax
uid_1_2_840_10008_15_0_3_17 = 386, // dicomPrimaryDeviceType
uid_1_2_840_10008_15_0_3_18 = 387, // dicomRelatedDeviceReference
uid_1_2_840_10008_15_0_3_19 = 388, // dicomPreferredCalledAETitle
uid_1_2_840_10008_15_0_3_20 = 389, // dicomTLSCyphersuite
uid_1_2_840_10008_15_0_3_21 = 390, // dicomAuthorizedNodeCertificateReference
uid_1_2_840_10008_15_0_3_22 = 391, // dicomThisNodeCertificateReference
uid_1_2_840_10008_15_0_3_23 = 392, // dicomInstalled
uid_1_2_840_10008_15_0_3_24 = 393, // dicomStationName
uid_1_2_840_10008_15_0_3_25 = 394, // dicomDeviceSerialNumber
uid_1_2_840_10008_15_0_3_26 = 395, // dicomInstitutionName
uid_1_2_840_10008_15_0_3_27 = 396, // dicomInstitutionAddress
uid_1_2_840_10008_15_0_3_28 = 397, // dicomInstitutionDepartmentName
uid_1_2_840_10008_15_0_3_29 = 398, // dicomIssuerOfPatientID
uid_1_2_840_10008_15_0_3_30 = 399, // dicomPreferredCallingAETitle
uid_1_2_840_10008_15_0_3_31 = 400, // dicomSupportedCharacterSet
uid_1_2_840_10008_15_0_4_1 = 401, // dicomConfigurationRoot
uid_1_2_840_10008_15_0_4_2 = 402, // dicomDevicesRoot
uid_1_2_840_10008_15_0_4_3 = 403, // dicomUniqueAETitlesRegistryRoot
uid_1_2_840_10008_15_0_4_4 = 404, // dicomDevice
uid_1_2_840_10008_15_0_4_5 = 405, // dicomNetworkAE
uid_1_2_840_10008_15_0_4_6 = 406, // dicomNetworkConnection
uid_1_2_840_10008_15_0_4_7 = 407, // dicomUniqueAETitle
uid_1_2_840_10008_15_0_4_8 = 408, // dicomTransferCapability
uid_1_2_840_10008_15_1_1 = 409, // Universal Coordinated Time

/////////////////////////////////////////////////////////////////////////
//
//
//
// Optionally private UIDs
//
#if 0
uid_1_2_840_113619_4_2,
uid_1_2_840_113619_4_3,
uid_1_3_12_2_1107_5_9_1,
uid_1_2_840_113619_4_26,
uid_1_2_840_113619_4_30,
uid_2_16_840_1_113709_1_5_1,
uid_2_16_840_1_113709_1_2_2,
uid_1_2_840_113543_6_6_1_3_10002,
uid_1_2_392_200036_9116_7_8_1_1_1,
uid_1_2_392_200036_9125_1_1_2,
uid_1_2_840_113619_4_27,
uid_1_3_46_670589_11_0_0_12_1,
uid_1_3_46_670589_11_0_0_12_2,
uid_1_3_46_670589_11_0_0_12_4,
uid_1_3_46_670589_2_3_1_1,
uid_1_3_46_670589_2_4_1_1,
uid_1_3_46_670589_2_5_1_1,
uid_1_3_46_670589_5_0_1,
uid_1_3_46_670589_5_0_1_1,
uid_1_3_46_670589_5_0_10,
uid_1_3_46_670589_5_0_11,
uid_1_3_46_670589_5_0_11_1,
uid_1_3_46_670589_5_0_12,
uid_1_3_46_670589_5_0_13,
uid_1_3_46_670589_5_0_14,
uid_1_3_46_670589_5_0_2,
uid_1_3_46_670589_5_0_2_1,
uid_1_3_46_670589_5_0_3,
uid_1_3_46_670589_5_0_3_1,
uid_1_3_46_670589_5_0_4,
uid_1_3_46_670589_5_0_7,
uid_1_3_46_670589_5_0_8,
uid_1_3_46_670589_5_0_9,
uid_1_2_752_24_3_7_6,
uid_1_2_752_24_3_7_7,
uid_1_2_840_113619_5_2,
uid_1_3_46_670589_33_1_4_1
#endif
//
//
//
//
//
/////////////////////////////////////////////////////////////////////////

} TSType;

  typedef enum {
VerificationSOPClass = 1, // Verification SOP Class
ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM = 2, // Implicit VR Little Endian: Default Transfer Syntax for DICOM
ExplicitVRLittleEndian = 3, // Explicit VR Little Endian
DeflatedExplicitVRLittleEndian = 4, // Deflated Explicit VR Little Endian
ExplicitVRBigEndian = 5, // Explicit VR Big Endian (retired)
JPEGBaselineProcess1DefaultTransferSyntaxforLossyJPEG8BitImageCompression = 6, // JPEG Baseline (Process 1): Default Transfer Syntax for Lossy JPEG 8 Bit Image Compression
JPEGExtendedProcess24DefaultTransferSyntaxforLossyJPEG12BitImageCompressionProcess4only = 7, // JPEG Extended (Process 2 & 4): Default Transfer Syntax for Lossy JPEG 12 Bit Image Compression (Process 4 only)
JPEGExtendedProcess35Retired = 8, // JPEG Extended (Process 3 & 5)
JPEGSpectralSelectionNonHierarchicalProcess68Retired = 9, // JPEG Spectral Selection, Non-Hierarchical (Process 6 & 8)
JPEGSpectralSelectionNonHierarchicalProcess79Retired = 10, // JPEG Spectral Selection, Non-Hierarchical (Process 7 & 9)
JPEGFullProgressionNonHierarchicalProcess1012Retired = 11, // JPEG Full Progression, Non-Hierarchical (Process 10 & 12)
JPEGFullProgressionNonHierarchicalProcess1113Retired = 12, // JPEG Full Progression, Non-Hierarchical (Process 11 & 13)
JPEGLosslessNonHierarchicalProcess14 = 13, // JPEG Lossless, Non-Hierarchical (Process 14)
JPEGLosslessNonHierarchicalProcess15Retired = 14, // JPEG Lossless, Non-Hierarchical (Process 15)
JPEGExtendedHierarchicalProcess1618Retired = 15, // JPEG Extended, Hierarchical (Process 16 & 18)
JPEGExtendedHierarchicalProcess1719Retired = 16, // JPEG Extended, Hierarchical (Process 17 & 19)
JPEGSpectralSelectionHierarchicalProcess2022Retired = 17, // JPEG Spectral Selection, Hierarchical (Process 20 & 22)
JPEGSpectralSelectionHierarchicalProcess2123Retired = 18, // JPEG Spectral Selection, Hierarchical (Process 21 & 23)
JPEGFullProgressionHierarchicalProcess2426Retired = 19, // JPEG Full Progression, Hierarchical (Process 24 & 26)
JPEGFullProgressionHierarchicalProcess2527Retired = 20, // JPEG Full Progression, Hierarchical (Process 25 & 27)
JPEGLosslessHierarchicalProcess28Retired = 21, // JPEG Lossless, Hierarchical (Process 28)
JPEGLosslessHierarchicalProcess29Retired = 22, // JPEG Lossless, Hierarchical (Process 29)
JPEGLosslessNonHierarchicalFirstOrderPredictionProcess14SelectionValue1DefaultTransferSyntaxforLosslessJPEGImageCompression = 23, // JPEG Lossless, Non-Hierarchical, First-Order Prediction (Process 14 [Selection Value 1]): Default Transfer Syntax for Lossless JPEG Image Compression
JPEGLSLosslessImageCompression = 24, // JPEG-LS Lossless Image Compression
JPEGLSLossyNearLosslessImageCompression = 25, // JPEG-LS Lossy (Near-Lossless) Image Compression
JPEG2000ImageCompressionLosslessOnly = 26, // JPEG 2000 Image Compression (Lossless Only)
JPEG2000ImageCompression = 27, // JPEG 2000 Image Compression
JPEG2000Part2MulticomponentImageCompressionLosslessOnly = 28, // JPEG 2000 Part 2 Multi-component Image Compression (Lossless Only)
JPEG2000Part2MulticomponentImageCompression = 29, // JPEG 2000 Part 2 Multi-component Image Compression
JPIPReferenced = 30, // JPIP Referenced
JPIPReferencedDeflate = 31, // JPIP Referenced Deflate
MPEG2MainProfileMainLevel = 32, // MPEG2 Main Profile @ Main Level
MPEG2MainProfileHighLevel = 33, // MPEG2 Main Profile @ High Level
MPEG4AVCH_264HighProfileLevel4_1 = 34, // MPEG-4 AVC/H.264 High Profile @ Level 4.1
MPEG4AVCH_264BDcompatibleHighProfileLevel4_1 = 35, // MPEG-4 AVC/H.264 BD-compatible High Profile @ Level 4.1
MPEG4AVCH_264HighProfileLevel4_2For2DVideo = 36, // MPEG-4 AVC/H.264 High Profile @ Level 4.2 For 2D Video
MPEG4AVCH_264HighProfileLevel4_2For3DVideo = 37, // MPEG-4 AVC/H.264 High Profile @ Level 4.2 For 3D Video
MPEG4AVCH_264StereoHighProfileLevel4_2 = 38, // MPEG-4 AVC/H.264 Stereo High Profile @ Level 4.2
HEVCH_265MainProfileLevel5_1 = 39, // HEVC/H.265 Main Profile @ Level 5.1
HEVCH_265Main10ProfileLevel5_1 = 40, // HEVC/H.265 Main 10 Profile @ Level 5.1
RLELossless = 41, // RLE Lossless
RFC2557MIMEencapsulation = 42, // RFC 2557 MIME encapsulation  (retired)
XMLEncoding = 43, // XML Encoding (retired)
MediaStorageDirectoryStorage = 44, // Media Storage Directory Storage
TalairachBrainAtlasFrameofReference = 45, // Talairach Brain Atlas Frame of Reference
SPM2T1FrameofReference = 46, // SPM2 T1 Frame of Reference
SPM2T2FrameofReference = 47, // SPM2 T2 Frame of Reference
SPM2PDFrameofReference = 48, // SPM2 PD Frame of Reference
SPM2EPIFrameofReference = 49, // SPM2 EPI Frame of Reference
SPM2FILT1FrameofReference = 50, // SPM2 FIL T1 Frame of Reference
SPM2PETFrameofReference = 51, // SPM2 PET Frame of Reference
SPM2TRANSMFrameofReference = 52, // SPM2 TRANSM Frame of Reference
SPM2SPECTFrameofReference = 53, // SPM2 SPECT Frame of Reference
SPM2GRAYFrameofReference = 54, // SPM2 GRAY Frame of Reference
SPM2WHITEFrameofReference = 55, // SPM2 WHITE Frame of Reference
SPM2CSFFrameofReference = 56, // SPM2 CSF Frame of Reference
SPM2BRAINMASKFrameofReference = 57, // SPM2 BRAINMASK Frame of Reference
SPM2AVG305T1FrameofReference = 58, // SPM2 AVG305T1 Frame of Reference
SPM2AVG152T1FrameofReference = 59, // SPM2 AVG152T1 Frame of Reference
SPM2AVG152T2FrameofReference = 60, // SPM2 AVG152T2 Frame of Reference
SPM2AVG152PDFrameofReference = 61, // SPM2 AVG152PD Frame of Reference
SPM2SINGLESUBJT1FrameofReference = 62, // SPM2 SINGLESUBJT1 Frame of Reference
ICBM452T1FrameofReference = 63, // ICBM 452 T1 Frame of Reference
ICBMSingleSubjectMRIFrameofReference = 64, // ICBM Single Subject MRI Frame of Reference
HotIronColorPaletteSOPInstance = 65, // Hot Iron Color Palette SOP Instance
PETColorPaletteSOPInstance = 66, // PET Color Palette SOP Instance
HotMetalBlueColorPaletteSOPInstance = 67, // Hot Metal Blue Color Palette SOP Instance
PET20StepColorPaletteSOPInstance = 68, // PET 20 Step Color Palette SOP Instance
SpringColorPaletteSOPInstance = 69, // Spring Color Palette SOP Instance
SummerColorPaletteSOPInstance = 70, // Summer Color Palette SOP Instance
FallColorPaletteSOPInstance = 71, // Fall Color Palette SOP Instance
WinterColorPaletteSOPInstance = 72, // Winter Color Palette SOP Instance
BasicStudyContentNotificationSOPClassRetired = 73, // Basic Study Content Notification SOP Class
Papyrus3ImplicitVRLittleEndianRetired = 74, // Papyrus 3 Implicit VR Little Endian
StorageCommitmentPushModelSOPClass = 75, // Storage Commitment Push Model SOP Class
StorageCommitmentPushModelSOPInstance = 76, // Storage Commitment Push Model SOP Instance
StorageCommitmentPullModelSOPClassRetired = 77, // Storage Commitment Pull Model SOP Class
StorageCommitmentPullModelSOPInstanceRetired = 78, // Storage Commitment Pull Model SOP Instance
ProceduralEventLoggingSOPClass = 79, // Procedural Event Logging SOP Class
ProceduralEventLoggingSOPInstance = 80, // Procedural Event Logging SOP Instance
SubstanceAdministrationLoggingSOPClass = 81, // Substance Administration Logging SOP Class
SubstanceAdministrationLoggingSOPInstance = 82, // Substance Administration Logging SOP Instance
DICOMUIDRegistry = 83, // DICOM UID Registry
DICOMControlledTerminology = 84, // DICOM Controlled Terminology
AdultMouseAnatomyOntology = 85, // Adult Mouse Anatomy Ontology
UberonOntology = 86, // Uberon Ontology
IntegratedTaxonomicInformationSystemITISTaxonomicSerialNumberTSN = 87, // Integrated Taxonomic Information System (ITIS) Taxonomic Serial Number (TSN)
MouseGenomeInitiativeMGI = 88, // Mouse Genome Initiative (MGI)
PubChemCompoundCID = 89, // PubChem Compound CID
ICD11 = 90, // ICD-11
NewYorkUniversityMelanomaClinicalCooperativeGroup = 91, // New York University Melanoma Clinical Cooperative Group
MayoClinicNonradiologicalImagesSpecificBodyStructureAnatomicalSurfaceRegionGuide = 92, // Mayo Clinic Non-radiological Images Specific Body Structure Anatomical Surface Region Guide
ImageBiomarkerStandardisationInitiative = 93, // Image Biomarker Standardisation Initiative
RadiomicsOntology = 94, // Radiomics Ontology
DICOMApplicationContextName = 95, // DICOM Application Context Name
DetachedPatientManagementSOPClassRetired = 96, // Detached Patient Management SOP Class
DetachedPatientManagementMetaSOPClassRetired = 97, // Detached Patient Management Meta SOP Class
DetachedVisitManagementSOPClassRetired = 98, // Detached Visit Management SOP Class
DetachedStudyManagementSOPClassRetired = 99, // Detached Study Management SOP Class
StudyComponentManagementSOPClassRetired = 100, // Study Component Management SOP Class
ModalityPerformedProcedureStepSOPClass = 101, // Modality Performed Procedure Step SOP Class
ModalityPerformedProcedureStepRetrieveSOPClass = 102, // Modality Performed Procedure Step Retrieve SOP Class
ModalityPerformedProcedureStepNotificationSOPClass = 103, // Modality Performed Procedure Step Notification SOP Class
DetachedResultsManagementSOPClassRetired = 104, // Detached Results Management SOP Class
DetachedResultsManagementMetaSOPClassRetired = 105, // Detached Results Management Meta SOP Class
DetachedStudyManagementMetaSOPClassRetired = 106, // Detached Study Management Meta SOP Class
DetachedInterpretationManagementSOPClassRetired = 107, // Detached Interpretation Management SOP Class
StorageServiceClass = 108, // Storage Service Class
BasicFilmSessionSOPClass = 109, // Basic Film Session SOP Class
BasicFilmBoxSOPClass = 110, // Basic Film Box SOP Class
BasicGrayscaleImageBoxSOPClass = 111, // Basic Grayscale Image Box SOP Class
BasicColorImageBoxSOPClass = 112, // Basic Color Image Box SOP Class
ReferencedImageBoxSOPClassRetired = 113, // Referenced Image Box SOP Class
BasicGrayscalePrintManagementMetaSOPClass = 114, // Basic Grayscale Print Management Meta SOP Class
ReferencedGrayscalePrintManagementMetaSOPClassRetired = 115, // Referenced Grayscale Print Management Meta SOP Class
PrintJobSOPClass = 116, // Print Job SOP Class
BasicAnnotationBoxSOPClass = 117, // Basic Annotation Box SOP Class
PrinterSOPClass = 118, // Printer SOP Class
PrinterConfigurationRetrievalSOPClass = 119, // Printer Configuration Retrieval SOP Class
PrinterSOPInstance = 120, // Printer SOP Instance
PrinterConfigurationRetrievalSOPInstance = 121, // Printer Configuration Retrieval SOP Instance
BasicColorPrintManagementMetaSOPClass = 122, // Basic Color Print Management Meta SOP Class
ReferencedColorPrintManagementMetaSOPClassRetired = 123, // Referenced Color Print Management Meta SOP Class
VOILUTBoxSOPClass = 124, // VOI LUT Box SOP Class
PresentationLUTSOPClass = 125, // Presentation LUT SOP Class
ImageOverlayBoxSOPClassRetired = 126, // Image Overlay Box SOP Class
BasicPrintImageOverlayBoxSOPClassRetired = 127, // Basic Print Image Overlay Box SOP Class
PrintQueueSOPInstanceRetired = 128, // Print Queue SOP Instance
PrintQueueManagementSOPClassRetired = 129, // Print Queue Management SOP Class
StoredPrintStorageSOPClassRetired = 130, // Stored Print Storage SOP Class
HardcopyGrayscaleImageStorageSOPClassRetired = 131, // Hardcopy Grayscale Image Storage SOP Class
HardcopyColorImageStorageSOPClassRetired = 132, // Hardcopy Color Image Storage SOP Class
PullPrintRequestSOPClassRetired = 133, // Pull Print Request SOP Class
PullStoredPrintManagementMetaSOPClassRetired = 134, // Pull Stored Print Management Meta SOP Class
MediaCreationManagementSOPClassUID = 135, // Media Creation Management SOP Class UID
DisplaySystemSOPClass = 136, // Display System SOP Class
DisplaySystemSOPInstance = 137, // Display System SOP Instance
ComputedRadiographyImageStorage = 138, // Computed Radiography Image Storage
DigitalXRayImageStorageForPresentation = 139, // Digital X-Ray Image Storage - For Presentation
DigitalXRayImageStorageForProcessing = 140, // Digital X-Ray Image Storage - For Processing
DigitalMammographyXRayImageStorageForPresentation = 141, // Digital Mammography X-Ray Image Storage - For Presentation
DigitalMammographyXRayImageStorageForProcessing = 142, // Digital Mammography X-Ray Image Storage - For Processing
DigitalIntraoralXRayImageStorageForPresentation = 143, // Digital Intra-Oral X-Ray Image Storage - For Presentation
DigitalIntraoralXRayImageStorageForProcessing = 144, // Digital Intra-Oral X-Ray Image Storage - For Processing
CTImageStorage = 145, // CT Image Storage
EnhancedCTImageStorage = 146, // Enhanced CT Image Storage
LegacyConvertedEnhancedCTImageStorage = 147, // Legacy Converted Enhanced CT Image Storage
UltrasoundMultiframeImageStorageRetired = 148, // Ultrasound Multi-frame Image Storage
UltrasoundMultiframeImageStorage = 149, // Ultrasound Multi-frame Image Storage
MRImageStorage = 150, // MR Image Storage
EnhancedMRImageStorage = 151, // Enhanced MR Image Storage
MRSpectroscopyStorage = 152, // MR Spectroscopy Storage
EnhancedMRColorImageStorage = 153, // Enhanced MR Color Image Storage
LegacyConvertedEnhancedMRImageStorage = 154, // Legacy Converted Enhanced MR Image Storage
NuclearMedicineImageStorageRetired = 155, // Nuclear Medicine Image Storage
UltrasoundImageStorageRetired = 156, // Ultrasound Image Storage
UltrasoundImageStorage = 157, // Ultrasound Image Storage
EnhancedUSVolumeStorage = 158, // Enhanced US Volume Storage
SecondaryCaptureImageStorage = 159, // Secondary Capture Image Storage
MultiframeSingleBitSecondaryCaptureImageStorage = 160, // Multi-frame Single Bit Secondary Capture Image Storage
MultiframeGrayscaleByteSecondaryCaptureImageStorage = 161, // Multi-frame Grayscale Byte Secondary Capture Image Storage
MultiframeGrayscaleWordSecondaryCaptureImageStorage = 162, // Multi-frame Grayscale Word Secondary Capture Image Storage
MultiframeTrueColorSecondaryCaptureImageStorage = 163, // Multi-frame True Color Secondary Capture Image Storage
StandaloneOverlayStorageRetired = 164, // Standalone Overlay Storage
StandaloneCurveStorageRetired = 165, // Standalone Curve Storage
WaveformStorageTrialRetired = 166, // Waveform Storage - Trial
ECG12leadWaveformStorage = 167, // 12-lead ECG Waveform Storage
GeneralECGWaveformStorage = 168, // General ECG Waveform Storage
AmbulatoryECGWaveformStorage = 169, // Ambulatory ECG Waveform Storage
HemodynamicWaveformStorage = 170, // Hemodynamic Waveform Storage
CardiacElectrophysiologyWaveformStorage = 171, // Cardiac Electrophysiology Waveform Storage
BasicVoiceAudioWaveformStorage = 172, // Basic Voice Audio Waveform Storage
GeneralAudioWaveformStorage = 173, // General Audio Waveform Storage
ArterialPulseWaveformStorage = 174, // Arterial Pulse Waveform Storage
RespiratoryWaveformStorage = 175, // Respiratory Waveform Storage
StandaloneModalityLUTStorageRetired = 176, // Standalone Modality LUT Storage
StandaloneVOILUTStorageRetired = 177, // Standalone VOI LUT Storage
GrayscaleSoftcopyPresentationStateStorageSOPClass = 178, // Grayscale Softcopy Presentation State Storage
ColorSoftcopyPresentationStateStorageSOPClass = 179, // Color Softcopy Presentation State Storage
PseudoColorSoftcopyPresentationStateStorageSOPClass = 180, // Pseudo-Color Softcopy Presentation State Storage
BlendingSoftcopyPresentationStateStorageSOPClass = 181, // Blending Softcopy Presentation State Storage
XAXRFGrayscaleSoftcopyPresentationStateStorage = 182, // XA/XRF Grayscale Softcopy Presentation State Storage
GrayscalePlanarMPRVolumetricPresentationStateStorage = 183, // Grayscale Planar MPR Volumetric Presentation State Storage
CompositingPlanarMPRVolumetricPresentationStateStorage = 184, // Compositing Planar MPR Volumetric Presentation State Storage
AdvancedBlendingPresentationStateStorage = 185, // Advanced Blending Presentation State Storage
VolumeRenderingVolumetricPresentationStateStorage = 186, // Volume Rendering Volumetric Presentation State Storage
SegmentedVolumeRenderingVolumetricPresentationStateStorage = 187, // Segmented Volume Rendering Volumetric Presentation State Storage
MultipleVolumeRenderingVolumetricPresentationStateStorage = 188, // Multiple Volume Rendering Volumetric Presentation State Storage
XRayAngiographicImageStorage = 189, // X-Ray Angiographic Image Storage
EnhancedXAImageStorage = 190, // Enhanced XA Image Storage
XRayRadiofluoroscopicImageStorage = 191, // X-Ray Radiofluoroscopic Image Storage
EnhancedXRFImageStorage = 192, // Enhanced XRF Image Storage
XRayAngiographicBiPlaneImageStorageRetired = 193, // X-Ray Angiographic Bi-Plane Image Storage
Retired1 = 194, // 
XRay3DAngiographicImageStorage = 195, // X-Ray 3D Angiographic Image Storage
XRay3DCraniofacialImageStorage = 196, // X-Ray 3D Craniofacial Image Storage
BreastTomosynthesisImageStorage = 197, // Breast Tomosynthesis Image Storage
BreastProjectionXRayImageStorageForPresentation = 198, // Breast Projection X-Ray Image Storage - For Presentation
BreastProjectionXRayImageStorageForProcessing = 199, // Breast Projection X-Ray Image Storage - For Processing
IntravascularOpticalCoherenceTomographyImageStorageForPresentation = 200, // Intravascular Optical Coherence Tomography Image Storage - For Presentation
IntravascularOpticalCoherenceTomographyImageStorageForProcessing = 201, // Intravascular Optical Coherence Tomography Image Storage - For Processing
NuclearMedicineImageStorage = 202, // Nuclear Medicine Image Storage
ParametricMapStorage = 203, // Parametric Map Storage
Retired2 = 204, // 
RawDataStorage = 205, // Raw Data Storage
SpatialRegistrationStorage = 206, // Spatial Registration Storage
SpatialFiducialsStorage = 207, // Spatial Fiducials Storage
DeformableSpatialRegistrationStorage = 208, // Deformable Spatial Registration Storage
SegmentationStorage = 209, // Segmentation Storage
SurfaceSegmentationStorage = 210, // Surface Segmentation Storage
TractographyResultsStorage = 211, // Tractography Results Storage
RealWorldValueMappingStorage = 212, // Real World Value Mapping Storage
SurfaceScanMeshStorage = 213, // Surface Scan Mesh Storage
SurfaceScanPointCloudStorage = 214, // Surface Scan Point Cloud Storage
VLImageStorageTrialRetired = 215, // VL Image Storage - Trial
VLMultiframeImageStorageTrialRetired = 216, // VL Multi-frame Image Storage - Trial
VLEndoscopicImageStorage = 217, // VL Endoscopic Image Storage
VideoEndoscopicImageStorage = 218, // Video Endoscopic Image Storage
VLMicroscopicImageStorage = 219, // VL Microscopic Image Storage
VideoMicroscopicImageStorage = 220, // Video Microscopic Image Storage
VLSlideCoordinatesMicroscopicImageStorage = 221, // VL Slide-Coordinates Microscopic Image Storage
VLPhotographicImageStorage = 222, // VL Photographic Image Storage
VideoPhotographicImageStorage = 223, // Video Photographic Image Storage
OphthalmicPhotography8BitImageStorage = 224, // Ophthalmic Photography 8 Bit Image Storage
OphthalmicPhotography16BitImageStorage = 225, // Ophthalmic Photography 16 Bit Image Storage
StereometricRelationshipStorage = 226, // Stereometric Relationship Storage
OphthalmicTomographyImageStorage = 227, // Ophthalmic Tomography Image Storage
WideFieldOphthalmicPhotographyStereographicProjectionImageStorage = 228, // Wide Field Ophthalmic Photography Stereographic Projection Image Storage
WideFieldOphthalmicPhotography3DCoordinatesImageStorage = 229, // Wide Field Ophthalmic Photography 3D Coordinates Image Storage
OphthalmicOpticalCoherenceTomographyEnFaceImageStorage = 230, // Ophthalmic Optical Coherence Tomography En Face Image Storage
OphthalmicOpticalCoherenceTomographyBscanVolumeAnalysisStorage = 231, // Ophthalmic Optical Coherence Tomography B-scan Volume Analysis Storage
VLWholeSlideMicroscopyImageStorage = 232, // VL Whole Slide Microscopy Image Storage
LensometryMeasurementsStorage = 233, // Lensometry Measurements Storage
AutorefractionMeasurementsStorage = 234, // Autorefraction Measurements Storage
KeratometryMeasurementsStorage = 235, // Keratometry Measurements Storage
SubjectiveRefractionMeasurementsStorage = 236, // Subjective Refraction Measurements Storage
VisualAcuityMeasurementsStorage = 237, // Visual Acuity Measurements Storage
SpectaclePrescriptionReportStorage = 238, // Spectacle Prescription Report Storage
OphthalmicAxialMeasurementsStorage = 239, // Ophthalmic Axial Measurements Storage
IntraocularLensCalculationsStorage = 240, // Intraocular Lens Calculations Storage
MacularGridThicknessandVolumeReportStorage = 241, // Macular Grid Thickness and Volume Report Storage
OphthalmicVisualFieldStaticPerimetryMeasurementsStorage = 242, // Ophthalmic Visual Field Static Perimetry Measurements Storage
OphthalmicThicknessMapStorage = 243, // Ophthalmic Thickness Map Storage
CornealTopographyMapStorage = 244, // Corneal Topography Map Storage
TextSRStorageTrialRetired = 245, // Text SR Storage - Trial
AudioSRStorageTrialRetired = 246, // Audio SR Storage - Trial
DetailSRStorageTrialRetired = 247, // Detail SR Storage - Trial
ComprehensiveSRStorageTrialRetired = 248, // Comprehensive SR Storage - Trial
BasicTextSRStorage = 249, // Basic Text SR Storage
EnhancedSRStorage = 250, // Enhanced SR Storage
ComprehensiveSRStorage = 251, // Comprehensive SR Storage
Comprehensive3DSRStorage = 252, // Comprehensive 3D SR Storage
ExtensibleSRStorage = 253, // Extensible SR Storage
ProcedureLogStorage = 254, // Procedure Log Storage
MammographyCADSRStorage = 255, // Mammography CAD SR Storage
KeyObjectSelectionDocumentStorage = 256, // Key Object Selection Document Storage
ChestCADSRStorage = 257, // Chest CAD SR Storage
XRayRadiationDoseSRStorage = 258, // X-Ray Radiation Dose SR Storage
RadiopharmaceuticalRadiationDoseSRStorage = 259, // Radiopharmaceutical Radiation Dose SR Storage
ColonCADSRStorage = 260, // Colon CAD SR Storage
ImplantationPlanSRStorage = 261, // Implantation Plan SR Storage
AcquisitionContextSRStorage = 262, // Acquisition Context SR Storage
SimplifiedAdultEchoSRStorage = 263, // Simplified Adult Echo SR Storage
PatientRadiationDoseSRStorage = 264, // Patient Radiation Dose SR Storage
PlannedImagingAgentAdministrationSRStorage = 265, // Planned Imaging Agent Administration SR Storage
PerformedImagingAgentAdministrationSRStorage = 266, // Performed Imaging Agent Administration SR Storage
ContentAssessmentResultsStorage = 267, // Content Assessment Results Storage
EncapsulatedPDFStorage = 268, // Encapsulated PDF Storage
EncapsulatedCDAStorage = 269, // Encapsulated CDA Storage
EncapsulatedSTLStorage = 270, // Encapsulated STL Storage
PositronEmissionTomographyImageStorage = 271, // Positron Emission Tomography Image Storage
LegacyConvertedEnhancedPETImageStorage = 272, // Legacy Converted Enhanced PET Image Storage
StandalonePETCurveStorageRetired = 273, // Standalone PET Curve Storage
EnhancedPETImageStorage = 274, // Enhanced PET Image Storage
BasicStructuredDisplayStorage = 275, // Basic Structured Display Storage
CTDefinedProcedureProtocolStorage = 276, // CT Defined Procedure Protocol Storage
CTPerformedProcedureProtocolStorage = 277, // CT Performed Procedure Protocol Storage
ProtocolApprovalStorage = 278, // Protocol Approval Storage
ProtocolApprovalInformationModelFIND = 279, // Protocol Approval Information Model - FIND
ProtocolApprovalInformationModelMOVE = 280, // Protocol Approval Information Model - MOVE
ProtocolApprovalInformationModelGET = 281, // Protocol Approval Information Model - GET
RTImageStorage = 282, // RT Image Storage
RTDoseStorage = 283, // RT Dose Storage
RTStructureSetStorage = 284, // RT Structure Set Storage
RTBeamsTreatmentRecordStorage = 285, // RT Beams Treatment Record Storage
RTPlanStorage = 286, // RT Plan Storage
RTBrachyTreatmentRecordStorage = 287, // RT Brachy Treatment Record Storage
RTTreatmentSummaryRecordStorage = 288, // RT Treatment Summary Record Storage
RTIonPlanStorage = 289, // RT Ion Plan Storage
RTIonBeamsTreatmentRecordStorage = 290, // RT Ion Beams Treatment Record Storage
RTPhysicianIntentStorage = 291, // RT Physician Intent Storage
RTSegmentAnnotationStorage = 292, // RT Segment Annotation Storage
DICOSCTImageStorage = 293, // DICOS CT Image Storage
DICOSDigitalXRayImageStorageForPresentation = 294, // DICOS Digital X-Ray Image Storage - For Presentation
DICOSDigitalXRayImageStorageForProcessing = 295, // DICOS Digital X-Ray Image Storage - For Processing
DICOSThreatDetectionReportStorage = 296, // DICOS Threat Detection Report Storage
DICOS2DAITStorage = 297, // DICOS 2D AIT Storage
DICOS3DAITStorage = 298, // DICOS 3D AIT Storage
DICOSQuadrupoleResonanceQRStorage = 299, // DICOS Quadrupole Resonance (QR) Storage
EddyCurrentImageStorage = 300, // Eddy Current Image Storage
EddyCurrentMultiframeImageStorage = 301, // Eddy Current Multi-frame Image Storage
PatientRootQueryRetrieveInformationModelFIND = 302, // Patient Root Query/Retrieve Information Model - FIND
PatientRootQueryRetrieveInformationModelMOVE = 303, // Patient Root Query/Retrieve Information Model - MOVE
PatientRootQueryRetrieveInformationModelGET = 304, // Patient Root Query/Retrieve Information Model - GET
StudyRootQueryRetrieveInformationModelFIND = 305, // Study Root Query/Retrieve Information Model - FIND
StudyRootQueryRetrieveInformationModelMOVE = 306, // Study Root Query/Retrieve Information Model - MOVE
StudyRootQueryRetrieveInformationModelGET = 307, // Study Root Query/Retrieve Information Model - GET
PatientStudyOnlyQueryRetrieveInformationModelFINDRetired = 308, // Patient/Study Only Query/Retrieve Information Model - FIND
PatientStudyOnlyQueryRetrieveInformationModelMOVERetired = 309, // Patient/Study Only Query/Retrieve Information Model - MOVE
PatientStudyOnlyQueryRetrieveInformationModelGETRetired = 310, // Patient/Study Only Query/Retrieve Information Model - GET
CompositeInstanceRootRetrieveMOVE = 311, // Composite Instance Root Retrieve - MOVE
CompositeInstanceRootRetrieveGET = 312, // Composite Instance Root Retrieve - GET
CompositeInstanceRetrieveWithoutBulkDataGET = 313, // Composite Instance Retrieve Without Bulk Data - GET
DefinedProcedureProtocolInformationModelFIND = 314, // Defined Procedure Protocol Information Model - FIND
DefinedProcedureProtocolInformationModelMOVE = 315, // Defined Procedure Protocol Information Model - MOVE
DefinedProcedureProtocolInformationModelGET = 316, // Defined Procedure Protocol Information Model - GET
ModalityWorklistInformationModelFIND = 317, // Modality Worklist Information Model - FIND
GeneralPurposeWorklistManagementMetaSOPClass = 318, // General Purpose Worklist Management Meta SOP Class (retired)
GeneralPurposeWorklistInformationModelFIND = 319, // General Purpose Worklist Information Model - FIND (retired)
GeneralPurposeScheduledProcedureStepSOPClass = 320, // General Purpose Scheduled Procedure Step SOP Class (retired)
GeneralPurposePerformedProcedureStepSOPClass = 321, // General Purpose Performed Procedure Step SOP Class (retired)
InstanceAvailabilityNotificationSOPClass = 322, // Instance Availability Notification SOP Class
RTBeamsDeliveryInstructionStorageSupplement74FrozenDraft = 323, // RTBeamsDeliveryInstructionStorageTrialRetired
RTConventionalMachineVerificationSupplement74FrozenDraft = 324, // RTConventionalMachineVerificationTrialRetired
RTIonMachineVerificationSupplement74FrozenDraft = 325, // RTIonMachineVerificationTrialRetired
UnifiedWorklistandProcedureStepSOPInstance = 326, // UnifiedWorklistandProcedureStepServiceClassTrialRetired
UnifiedProcedureStepPushSOPClassTrialRetired = 327, // Unified Procedure Step - Push SOP Class - Trial
UnifiedProcedureStepWatchSOPClassTrialRetired = 328, // Unified Procedure Step - Watch SOP Class - Trial
UnifiedProcedureStepPullSOPClassTrialRetired = 329, // Unified Procedure Step - Pull SOP Class - Trial
UnifiedProcedureStepEventSOPClassTrialRetired = 330, // Unified Procedure Step - Event SOP Class - Trial
UPSGlobalSubscriptionSOPInstance = 331, // UPS Global Subscription SOP Instance
UPSFilteredGlobalSubscriptionSOPInstance = 332, // UPS Filtered Global Subscription SOP Instance
UnifiedWorklistandProcedureStepServiceClass = 333, // Unified Worklist and Procedure Step Service Class
UnifiedProcedureStepPushSOPClass = 334, // Unified Procedure Step - Push SOP Class
UnifiedProcedureStepWatchSOPClass = 335, // Unified Procedure Step - Watch SOP Class
UnifiedProcedureStepPullSOPClass = 336, // Unified Procedure Step - Pull SOP Class
UnifiedProcedureStepEventSOPClass = 337, // Unified Procedure Step - Event SOP Class
RTBeamsDeliveryInstructionStorage = 338, // RT Beams Delivery Instruction Storage
RTConventionalMachineVerification = 339, // RT Conventional Machine Verification
RTIonMachineVerification = 340, // RT Ion Machine Verification
RTBrachyApplicationSetupDeliveryInstructionStorage = 341, // RT Brachy Application Setup Delivery Instruction Storage
GeneralRelevantPatientInformationQuery = 342, // General Relevant Patient Information Query
BreastImagingRelevantPatientInformationQuery = 343, // Breast Imaging Relevant Patient Information Query
CardiacRelevantPatientInformationQuery = 344, // Cardiac Relevant Patient Information Query
HangingProtocolStorage = 345, // Hanging Protocol Storage
HangingProtocolInformationModelFIND = 346, // Hanging Protocol Information Model - FIND
HangingProtocolInformationModelMOVE = 347, // Hanging Protocol Information Model - MOVE
HangingProtocolInformationModelGET = 348, // Hanging Protocol Information Model - GET
ColorPaletteStorage = 349, // Color Palette Storage
ColorPaletteQueryRetrieveInformationModelFIND = 350, // Color Palette Query/Retrieve Information Model - FIND
ColorPaletteQueryRetrieveInformationModelMOVE = 351, // Color Palette Query/Retrieve Information Model - MOVE
ColorPaletteQueryRetrieveInformationModelGET = 352, // Color Palette Query/Retrieve Information Model - GET
ProductCharacteristicsQuerySOPClass = 353, // Product Characteristics Query SOP Class
SubstanceApprovalQuerySOPClass = 354, // Substance Approval Query SOP Class
GenericImplantTemplateStorage = 355, // Generic Implant Template Storage
GenericImplantTemplateInformationModelFIND = 356, // Generic Implant Template Information Model - FIND
GenericImplantTemplateInformationModelMOVE = 357, // Generic Implant Template Information Model - MOVE
GenericImplantTemplateInformationModelGET = 358, // Generic Implant Template Information Model - GET
ImplantAssemblyTemplateStorage = 359, // Implant Assembly Template Storage
ImplantAssemblyTemplateInformationModelFIND = 360, // Implant Assembly Template Information Model - FIND
ImplantAssemblyTemplateInformationModelMOVE = 361, // Implant Assembly Template Information Model - MOVE
ImplantAssemblyTemplateInformationModelGET = 362, // Implant Assembly Template Information Model - GET
ImplantTemplateGroupStorage = 363, // Implant Template Group Storage
ImplantTemplateGroupInformationModelFIND = 364, // Implant Template Group Information Model - FIND
ImplantTemplateGroupInformationModelMOVE = 365, // Implant Template Group Information Model - MOVE
ImplantTemplateGroupInformationModelGET = 366, // Implant Template Group Information Model - GET
NativeDICOMModel = 367, // Native DICOM Model
AbstractMultiDimensionalImageModel = 368, // Abstract Multi-Dimensional Image Model
DICOMContentMappingResource = 369, // DICOM Content Mapping Resource
dicomDeviceName = 370, // dicomDeviceName
dicomDescription = 371, // dicomDescription
dicomManufacturer = 372, // dicomManufacturer
dicomManufacturerModelName = 373, // dicomManufacturerModelName
dicomSoftwareVersion = 374, // dicomSoftwareVersion
dicomVendorData = 375, // dicomVendorData
dicomAETitle = 376, // dicomAETitle
dicomNetworkConnectionReference = 377, // dicomNetworkConnectionReference
dicomApplicationCluster = 378, // dicomApplicationCluster
dicomAssociationInitiator = 379, // dicomAssociationInitiator
dicomAssociationAcceptor = 380, // dicomAssociationAcceptor
dicomHostname = 381, // dicomHostname
dicomPort = 382, // dicomPort
dicomSOPClass = 383, // dicomSOPClass
dicomTransferRole = 384, // dicomTransferRole
dicomTransferSyntax = 385, // dicomTransferSyntax
dicomPrimaryDeviceType = 386, // dicomPrimaryDeviceType
dicomRelatedDeviceReference = 387, // dicomRelatedDeviceReference
dicomPreferredCalledAETitle = 388, // dicomPreferredCalledAETitle
dicomTLSCyphersuite = 389, // dicomTLSCyphersuite
dicomAuthorizedNodeCertificateReference = 390, // dicomAuthorizedNodeCertificateReference
dicomThisNodeCertificateReference = 391, // dicomThisNodeCertificateReference
dicomInstalled = 392, // dicomInstalled
dicomStationName = 393, // dicomStationName
dicomDeviceSerialNumber = 394, // dicomDeviceSerialNumber
dicomInstitutionName = 395, // dicomInstitutionName
dicomInstitutionAddress = 396, // dicomInstitutionAddress
dicomInstitutionDepartmentName = 397, // dicomInstitutionDepartmentName
dicomIssuerOfPatientID = 398, // dicomIssuerOfPatientID
dicomPreferredCallingAETitle = 399, // dicomPreferredCallingAETitle
dicomSupportedCharacterSet = 400, // dicomSupportedCharacterSet
dicomConfigurationRoot = 401, // dicomConfigurationRoot
dicomDevicesRoot = 402, // dicomDevicesRoot
dicomUniqueAETitlesRegistryRoot = 403, // dicomUniqueAETitlesRegistryRoot
dicomDevice = 404, // dicomDevice
dicomNetworkAE = 405, // dicomNetworkAE
dicomNetworkConnection = 406, // dicomNetworkConnection
dicomUniqueAETitle = 407, // dicomUniqueAETitle
dicomTransferCapability = 408, // dicomTransferCapability
UniversalCoordinatedTime = 409, // Universal Coordinated Time

/////////////////////////////////////////////////////////////////////////
//
//
//
// Optionally private UIDs
//
#if 0
Private_1_2_840_113619_4_2,
Private_1_2_840_113619_4_3,
Private_1_3_12_2_1107_5_9_1,
Private_1_2_840_113619_4_26,
Private_1_2_840_113619_4_30,
Private_2_16_840_1_113709_1_5_1,
Private_2_16_840_1_113709_1_2_2,
Private_1_2_840_113543_6_6_1_3_10002,
Private_1_2_392_200036_9116_7_8_1_1_1,
Private_1_2_392_200036_9125_1_1_2,
Private_1_2_840_113619_4_27,
Private_1_3_46_670589_11_0_0_12_1,
Private_1_3_46_670589_11_0_0_12_2,
Private_1_3_46_670589_11_0_0_12_4,
Private_1_3_46_670589_2_3_1_1,
Private_1_3_46_670589_2_4_1_1,
Private_1_3_46_670589_2_5_1_1,
Private_1_3_46_670589_5_0_1,
Private_1_3_46_670589_5_0_1_1,
Private_1_3_46_670589_5_0_10,
Private_1_3_46_670589_5_0_11,
Private_1_3_46_670589_5_0_11_1,
Private_1_3_46_670589_5_0_12,
Private_1_3_46_670589_5_0_13,
Private_1_3_46_670589_5_0_14,
Private_1_3_46_670589_5_0_2,
Private_1_3_46_670589_5_0_2_1,
Private_1_3_46_670589_5_0_3,
Private_1_3_46_670589_5_0_3_1,
Private_1_3_46_670589_5_0_4,
Private_1_3_46_670589_5_0_7,
Private_1_3_46_670589_5_0_8,
Private_1_3_46_670589_5_0_9,
Private_1_2_752_24_3_7_6,
Private_1_2_752_24_3_7_7,
Private_1_2_840_113619_5_2,
Private_1_3_46_670589_33_1_4_1
#endif
//
//
//
//
//
/////////////////////////////////////////////////////////////////////////

} TSName;


  typedef const char* const (*TransferSyntaxStringsType)[2];
  static TransferSyntaxStringsType GetTransferSyntaxStrings();
  static const char * const *GetTransferSyntaxString(unsigned int ts);
  static unsigned int GetNumberOfTransferSyntaxStrings();


  // TODO: Because I would like a dual signature for TSType and TSName, C++ won't let me do it...
  static const char* GetUIDString(/*TSType*/ unsigned int ts);
  static const char* GetUIDName(/*TSType*/ unsigned int ts);

  /// Initialize object from a string (a uid number)
  /// return false on error, and internal state is set to 0
  bool SetFromUID(const char *str);

  /// When object is Initialize function return the well known name associated with uid
  /// return NULL when not initialized
  const char *GetName() const;

  /// When object is Initialize function return the uid
  /// return NULL when not initialized
  const char *GetString() const;

  operator TSType () const { return TSField; }

private:
  TSType TSField;
};
//-----------------------------------------------------------------------------
inline std::ostream &operator<<(std::ostream &_os, const UIDs &uid)
{
  _os << uid.GetString() << " -> " << uid.GetName();
  return _os;

}

} // end namespace gdcm

#endif //GDCMUIDS_H
