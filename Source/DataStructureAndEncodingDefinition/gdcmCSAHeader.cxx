/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmCSAHeader.h"
#include "gdcmPrivateTag.h"
#include "gdcmDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmSwapper.h"

namespace gdcm
{
/*
 * http://www.enac.northwestern.edu/~tew/archives/2003/02/25/incomplete-dicom-headers/
 * http://www.nmr.mgh.harvard.edu/~rudolph/software/vox2ras/download/vox2ras_rsolve.m
 * http://www.mail-archive.com/freesurfer@nmr.mgh.harvard.edu/msg03409.html
 *
 * Pretty good link:
 * http://www.mmrrcc.upenn.edu/CAMRIS/cfn/dicomhdr.html
 */

/*
 * SIEMENS-JPEG-CorruptFragClean.dcm (0029,xx10):
 * (0000,0005) FD (??) 337.625                              # 8,? (1)
 * (0000,0006) FD (??) 4.665                                # 8,? (1)
 * (0000,0007) SL (??) 955                                  # 4,? (1)
 * (0000,0008) SL (??) 200                                  # 4,? (1)
 * (0000,000c) FD (??) 4                                    # 8,? (1)
 * (0000,000d) SL (??) 2                                    # 4,? (1)
 * (0000,0013) SL (??) 337                                  # 4,? (1)
 * (0000,0014) SL (??) 0                                    # 4,? (1)
 * (0000,0016) SL (??) 50                                   # 4,? (1)
 * (0000,0018) SL (??) 672                                  # 4,? (1)
 * (0000,001d) LT (??) [N.E.C.K]                            # 8,? (1)
 * (0000,001e) FD (??) 160                                  # 8,? (1)
 * (0000,001f) FD (??) 0                                    # 8,? (1)
 * (0000,0020) FD (??) 3                                    # 8,? (1)
 * (0000,0021) SL (??) 1                                    # 4,? (1)
 * (0000,0022) SL (??) 11                                   # 4,? (1)
 * (0000,0025) SL (??) 8                                    # 4,? (1)
 * (0000,0027) FD (??) 60                                   # 8,? (1)
 * (0000,0028) SL (??) 292                                  # 4,? (1)
 * (0000,0029) SL (??) 0                                    # 4,? (1)
 * (0000,002c) SL (??) 200                                  # 4,? (1)
 * (0000,002d) SL (??) 0                                    # 4,? (1)
 * (0000,002e) SL (??) 0                                    # 4,? (1)
 * (0000,002f) FD (??) 1                                    # 8,? (1)
 * (ffff,ffff) CS (??) [END!      ]                         # 10,? (1)
 */

struct DataSetFormatEntry
{
  Tag t;
  VR  vr;
};

static DataSetFormatEntry DataSetFormatDict[] = {
 { Tag(0x0000,0x0004),VR::LT },
 { Tag(0x0000,0x0005),VR::FD },
 { Tag(0x0000,0x0006),VR::FD },
 { Tag(0x0000,0x0007),VR::SL },
 { Tag(0x0000,0x0008),VR::SL },
 { Tag(0x0000,0x000c),VR::FD },
 { Tag(0x0000,0x000d),VR::SL },
 { Tag(0x0000,0x000e),VR::SL },
 { Tag(0x0000,0x0012),VR::FD },
 { Tag(0x0000,0x0013),VR::SL },
 { Tag(0x0000,0x0014),VR::SL },
 { Tag(0x0000,0x0016),VR::SL },
 { Tag(0x0000,0x0018),VR::SL },
 { Tag(0x0000,0x001a),VR::SL },
 { Tag(0x0000,0x001d),VR::LT }, // Defined Terms: [A.B.D.O.M.E.N], [C.H.E.S.T], [E.X.T.R.E.M.I.T.Y], [H.E.A.D], [N.E.C.K], [P.E.L.V.I.S], [S.P.I.N.E]
 { Tag(0x0000,0x001e),VR::FD },
 { Tag(0x0000,0x001f),VR::FD },
 { Tag(0x0000,0x0020),VR::FD },
 { Tag(0x0000,0x0021),VR::SL },
 { Tag(0x0000,0x0022),VR::SL },
 { Tag(0x0000,0x0025),VR::SL },
 { Tag(0x0000,0x0026),VR::FD },
 { Tag(0x0000,0x0027),VR::FD },
 { Tag(0x0000,0x0028),VR::SL },
 { Tag(0x0000,0x0029),VR::SL },
 { Tag(0x0000,0x002b),VR::LT },
 { Tag(0x0000,0x002c),VR::SL },
 { Tag(0x0000,0x002d),VR::SL },
 { Tag(0x0000,0x002e),VR::SL },
 { Tag(0x0000,0x002f),VR::FD },
 { Tag(0x0000,0x0030),VR::LT },
 { Tag(0x0000,0x0033),VR::SL },
 { Tag(0x0000,0x0035),VR::SL },
 { Tag(0x0000,0x0036),VR::CS },
 { Tag(0x0000,0x0037),VR::SL },
 { Tag(0x0000,0x0038),VR::SL },
 { Tag(0x0000,0x0039),VR::SL },
 { Tag(0x0000,0x003a),VR::FD },
 { Tag(0x0000,0x003b),VR::SL },
 { Tag(0x0000,0x003c),VR::SL },
 { Tag(0x0000,0x003d),VR::FD },
 { Tag(0x0000,0x003e),VR::SL },
 { Tag(0x0000,0x003f),VR::SL },
 { Tag(0x0000,0x0101),VR::FD },
 { Tag(0x0000,0x0102),VR::FD },
 { Tag(0x0000,0x0103),VR::FD },
 { Tag(0x0000,0x0105),VR::IS },
 { Tag(0x0006,0x0006),VR::FD },
 { Tag(0x0006,0x0007),VR::FD },
 { Tag(0x0006,0x0008),VR::CS },
 { Tag(0x0006,0x000a),VR::LT },
 { Tag(0x0006,0x000b),VR::CS },
 { Tag(0x0006,0x000c),VR::FD },
 { Tag(0x0006,0x000e),VR::CS },
 { Tag(0x0006,0x000f),VR::SL },
 { Tag(0x0006,0x0024),VR::FD },
 { Tag(0xffff,0xffff),VR::CS }, // ENDS!
};

/*
 * http://www.healthcare.siemens.com/magnetom/phoenix-gallery/orthopedics/images/phoenix/29642762.ima
Image shadow data (0029,xx10)

0 - 'EchoLinePosition' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '427     '
1 - 'EchoColumnPosition' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '224     '
2 - 'EchoPartitionPosition' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '8       '
3 - 'UsedChannelMask' VM 1, VR UL, SyngoDT 9, NoOfItems 6, Data '63      '
4 - 'Actual3DImaPartNumber' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
5 - 'ICE_Dims' VM 1, VR LO, SyngoDT 19, NoOfItems 6, Data 'X_1_1_1_1_1_1_1_1_1_1_1_41'
6 - 'B_value' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
7 - 'Filter1' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
8 - 'Filter2' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
9 - 'ProtocolSliceNumber' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '6       '
10 - 'RealDwellTime' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '8600    '
11 - 'PixelFile' VM 1, VR UN, SyngoDT 0, NoOfItems 0, Data
12 - 'PixelFileName' VM 1, VR UN, SyngoDT 0, NoOfItems 0, Data
13 - 'SliceMeasurementDuration' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '338142.50000000'
14 - 'SequenceMask' VM 1, VR UL, SyngoDT 9, NoOfItems 6, Data '134217728'
15 - 'AcquisitionMatrixText' VM 1, VR SH, SyngoDT 22, NoOfItems 6, Data '421*448s'
16 - 'MeasuredFourierLines' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '0       '
17 - 'FlowEncodingDirection' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
18 - 'FlowVenc' VM 1, VR FD, SyngoDT 4, NoOfItems 0, Data
19 - 'PhaseEncodingDirectionPositive' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '1       '
20 - 'NumberOfImagesInMosaic' VM 1, VR US, SyngoDT 10, NoOfItems 0, Data
21 - 'DiffusionGradientDirection' VM 3, VR FD, SyngoDT 4, NoOfItems 0, Data
22 - 'ImageGroup' VM 1, VR US, SyngoDT 10, NoOfItems 0, Data
23 - 'SliceNormalVector' VM 3, VR FD, SyngoDT 4, NoOfItems 0, Data
24 - 'DiffusionDirectionality' VM 1, VR CS, SyngoDT 16, NoOfItems 0, Data
25 - 'TimeAfterStart' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '0.00000000'
26 - 'FlipAngle' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
27 - 'SequenceName' VM 1, VR SH, SyngoDT 22, NoOfItems 0, Data
28 - 'RepetitionTime' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
29 - 'EchoTime' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
30 - 'NumberOfAverages' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
31 - 'VoxelThickness' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
32 - 'VoxelPhaseFOV' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
33 - 'VoxelReadoutFOV' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
34 - 'VoxelPositionSag' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
35 - 'VoxelPositionCor' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
36 - 'VoxelPositionTra' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
37 - 'VoxelNormalSag' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
38 - 'VoxelNormalCor' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
39 - 'VoxelNormalTra' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
40 - 'VoxelInPlaneRot' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
41 - 'ImagePositionPatient' VM 3, VR DS, SyngoDT 3, NoOfItems 0, Data
42 - 'ImageOrientationPatient' VM 6, VR DS, SyngoDT 3, NoOfItems 0, Data
43 - 'PixelSpacing' VM 2, VR DS, SyngoDT 3, NoOfItems 0, Data
44 - 'SliceLocation' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
45 - 'SliceThickness' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
46 - 'SpectrumTextRegionLabel' VM 1, VR SH, SyngoDT 22, NoOfItems 0, Data
47 - 'Comp_Algorithm' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
48 - 'Comp_Blended' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
49 - 'Comp_ManualAdjusted' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
50 - 'Comp_AutoParam' VM 1, VR LT, SyngoDT 20, NoOfItems 0, Data
51 - 'Comp_AdjustedParam' VM 1, VR LT, SyngoDT 20, NoOfItems 0, Data
52 - 'Comp_JobID' VM 1, VR LT, SyngoDT 20, NoOfItems 0, Data
53 - 'FMRIStimulInfo' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
54 - 'FlowEncodingDirectionString' VM 1, VR SH, SyngoDT 22, NoOfItems 0, Data
55 - 'RepetitionTimeEffective' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
56 - 'CsiImagePositionPatient' VM 3, VR DS, SyngoDT 3, NoOfItems 0, Data
57 - 'CsiImageOrientationPatient' VM 6, VR DS, SyngoDT 3, NoOfItems 0, Data
58 - 'CsiPixelSpacing' VM 2, VR DS, SyngoDT 3, NoOfItems 0, Data
59 - 'CsiSliceLocation' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
60 - 'CsiSliceThickness' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
61 - 'OriginalSeriesNumber' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
62 - 'OriginalImageNumber' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
63 - 'ImaAbsTablePosition' VM 3, VR SL, SyngoDT 7, NoOfItems 6, Data '0       '\'0       '\'-1952   '
64 - 'NonPlanarImage' VM 1, VR US, SyngoDT 10, NoOfItems 6, Data '1       '
65 - 'MoCoQMeasure' VM 1, VR US, SyngoDT 10, NoOfItems 0, Data
66 - 'LQAlgorithm' VM 1, VR SH, SyngoDT 22, NoOfItems 0, Data
67 - 'SlicePosition_PCS' VM 3, VR FD, SyngoDT 4, NoOfItems 6, Data '-47.43732992'\'-135.75159147'\'19.57638496'
68 - 'RBMoCoTrans' VM 3, VR FD, SyngoDT 4, NoOfItems 0, Data
69 - 'RBMoCoRot' VM 3, VR FD, SyngoDT 4, NoOfItems 0, Data
70 - 'MultistepIndex' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '0       '
71 - 'ImaRelTablePosition' VM 3, VR IS, SyngoDT 6, NoOfItems 6, Data '0       '\'0       '\'39      '
72 - 'ImaCoilString' VM 1, VR LO, SyngoDT 19, NoOfItems 6, Data 'T:BO1,2'
73 - 'RFSWDDataType' VM 1, VR SH, SyngoDT 22, NoOfItems 6, Data 'measured'
74 - 'GSWDDataType' VM 1, VR SH, SyngoDT 22, NoOfItems 6, Data 'measured'
75 - 'NormalizeManipulated' VM 1, VR IS, SyngoDT 6, NoOfItems 0, Data
76 - 'ImaPATModeText' VM 1, VR LO, SyngoDT 19, NoOfItems 6, Data 'p2'
77 - 'B_matrix' VM 6, VR FD, SyngoDT 4, NoOfItems 0, Data
78 - 'BandwidthPerPixelPhaseEncode' VM 1, VR FD, SyngoDT 4, NoOfItems 0, Data
79 - 'FMRIStimulLevel' VM 1, VR FD, SyngoDT 4, NoOfItems 0, Data
Series shadow data (0029,xx20)

0 - 'UsedPatientWeight' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '72      '
1 - 'NumberOfPrescans' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '0       '
2 - 'TransmitterCalibration' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '541.65400000'
3 - 'PhaseGradientAmplitude' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '0.00000000'
4 - 'ReadoutGradientAmplitude' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '0.00000000'
5 - 'SelectionGradientAmplitude' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '0.00000000'
6 - 'GradientDelayTime' VM 3, VR DS, SyngoDT 3, NoOfItems 6, Data '13.00000000'\'14.00000000'\'10.00000000'
7 - 'RfWatchdogMask' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '0       '
8 - 'RfPowerErrorIndicator' VM 1, VR DS, SyngoDT 3, NoOfItems 0, Data
9 - 'SarWholeBody' VM 3, VR DS, SyngoDT 3, NoOfItems 0, Data
10 - 'Sed' VM 3, VR DS, SyngoDT 3, NoOfItems 6, Data '1000000.00000000'\'725.84052985'\'725.71234997'
11 - 'SequenceFileOwner' VM 1, VR SH, SyngoDT 22, NoOfItems 6, Data 'SIEMENS'
12 - 'Stim_mon_mode' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '2       '
13 - 'Operation_mode_flag' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '2       '
14 - 'dBdt_max' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '0.00000000'
15 - 't_puls_max' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '0.00000000'
16 - 'dBdt_thresh' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '0.00000000'
17 - 'dBdt_limit' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '0.00000000'
18 - 'SW_korr_faktor' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '1.00000000'
19 - 'Stim_max_online' VM 3, VR DS, SyngoDT 3, NoOfItems 6, Data '2.14339137'\'17.54720879'\'0.45053142'
20 - 'Stim_max_ges_norm_online' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '0.63422704'
21 - 'Stim_lim' VM 3, VR DS, SyngoDT 3, NoOfItems 6, Data '45.73709869'\'27.64929962'\'31.94370079'
22 - 'Stim_faktor' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '1.00000000'
23 - 'CoilForGradient' VM 1, VR SH, SyngoDT 22, NoOfItems 6, Data 'void'
24 - 'CoilForGradient2' VM 1, VR SH, SyngoDT 22, NoOfItems 6, Data 'AS092'
25 - 'CoilTuningReflection' VM 2, VR DS, SyngoDT 3, NoOfItems 0, Data
26 - 'CoilId' VM 0, VR IS, SyngoDT 6, NoOfItems 12, Data '255     '\'83      '\'238     '\'238     '\'238     '\'238     '\'238     '\'177     '\'238     '\'178     '\'238     '
27 - 'MiscSequenceParam' VM 38, VR IS, SyngoDT 6, NoOfItems 42, Data '0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '\'1086    '\'0       '\'0       '\'0       '\'0       '\'0       '\'0       '
28 - 'MrProtocolVersion' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '0       '
29 - 'DataFileName' VM 1, VR LO, SyngoDT 19, NoOfItems 0, Data
30 - 'RepresentativeImage' VM 1, VR UI, SyngoDT 25, NoOfItems 0, Data
31 - 'PositivePCSDirections' VM 1, VR SH, SyngoDT 22, NoOfItems 6, Data '+LPH'
32 - 'RelTablePosition' VM 3, VR IS, SyngoDT 6, NoOfItems 6, Data '0       '\'0       '\'39      '
33 - 'ReadoutOS' VM 1, VR FD, SyngoDT 4, NoOfItems 6, Data '2.00000000'
34 - 'LongModelName' VM 1, VR LO, SyngoDT 19, NoOfItems 6, Data 'TrioTim'
35 - 'SliceArrayConcatenations' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '1       '
36 - 'SliceResolution' VM 1, VR DS, SyngoDT 3, NoOfItems 6, Data '1.00000000'
37 - 'AbsTablePosition' VM 1, VR IS, SyngoDT 6, NoOfItems 6, Data '-1952   '
38 - 'AutoAlignMatrix' VM 16, VR FL, SyngoDT 5, NoOfItems 0, Data
39 - 'MeasurementIndex' VM 1, VR FL, SyngoDT 5, NoOfItems 0, Data
40 - 'CoilString' VM 1, VR LO, SyngoDT 19, NoOfItems 6, Data 'T:BO1,2'
41 - 'PATModeText' VM 1, VR LO, SyngoDT 19, NoOfItems 6, Data 'p2'
42 - 'PatReinPattern' VM 1, VR ST, SyngoDT 23, NoOfItems 6, Data '1;HFS;72.00;15.00;2;0;2;-794520928'
43 - 'ProtocolChangeHistory' VM 1, VR US, SyngoDT 10, NoOfItems 6, Data '0       '
44 - 'Isocentered' VM 1, VR US, SyngoDT 10, NoOfItems 6, Data '1       '
45 - 'MrPhoenixProtocol' VM 1, VR UN, SyngoDT 0, NoOfItems 6, Data '<XProtocol>
<...>
46 - 'GradientMode' VM 1, VR SH, SyngoDT 22, NoOfItems 6, Data 'Fast'
47 - 'FlowCompensation' VM 1, VR SH, SyngoDT 22, NoOfItems 6, Data 'No'
48 - 'PostProcProtocol' VM 1, VR UT, SyngoDT 27, NoOfItems 0, Data
49 - 'RFSWDOperationMode' VM 1, VR SS, SyngoDT 8, NoOfItems 6, Data '+0      '
50 - 'RFSWDMostCriticalAspect' VM 1, VR SH, SyngoDT 22, NoOfItems 6, Data 'Whole Body'
51 - 'SARMostCriticalAspect' VM 3, VR DS, SyngoDT 3, NoOfItems 6, Data '2.00000000'\'1.02534234'\'0.97963309'
52 - 'TablePositionOrigin' VM 3, VR SL, SyngoDT 7, NoOfItems 6, Data '0       '\'0       '\'-1991   '
53 - 'MrProtocol' VM 1, VR UN, SyngoDT 0, NoOfItems 0, Data
54 - 'MrEvaProtocol' VM 1, VR UN, SyngoDT 0, NoOfItems 0, Data
*/
struct equ
{ 
  uint32_t syngodt;
  const char vr[2+1];
};

// Looks like there is mapping in between syngodt and vr...
//  O <=> UN
//  3 <=> DS
//  4 <=> FD
//  5 <=> FL
//  6 <=> IS
//  9 <=> UL
// 10 <=> US
// 16 <=> CS
// 19 <=> LO
// 20 <=> LT
// 22 <=> SH
// 25 <=> UI
static equ mapping[] = {
  {  0 , "UN" },
  {  3 , "DS" },
  {  4 , "FD" },
  {  5 , "FL" },
  {  6 , "IS" },
  {  7 , "SL" },
  {  8 , "SS" },
  {  9 , "UL" },
  { 10 , "US" },
  { 16 , "CS" },
  { 19 , "LO" },
  { 20 , "LT" },
  { 22 , "SH" },
  { 23 , "ST" },
  { 25 , "UI" },
  { 27 , "UT" }
};

bool check_mapping(uint32_t syngodt, const char *vr)
{
  static const unsigned int max = sizeof(mapping) / sizeof(equ);
  const equ *p = mapping;
  assert( syngodt <= mapping[max-1].syngodt ); (void)max;
  while(p->syngodt < syngodt )
    {
    //std::cout << "mapping:" << p->vr << std::endl;
    ++p;
    }
  assert( p->syngodt == syngodt ); // or else need to update mapping
  const char* lvr = p->vr;
  int check = strcmp(vr, lvr) == 0;
  assert( check );
  return true;
}

bool checkallzero(std::istream &is)
{
  bool res = true;
  char c;
  while( is >> c )
    {
    if( c != 0 )
      {
      res = false;
      break;
      }
    }
  return res;
}

CSAHeader::CSAHeaderType CSAHeader::GetFormat() const
{
  return InternalType;
}

// dcmInfo.exe print like this:
// 67 - 'SlicePosition_PCS' VM 3, VR FD, SyngoDT 4, NoOfItems 6, Data '-185.77913332'\'-163.80459213'\'72.73944092'
void CSAHeader::Print(DataElement const &de)
{
  InternalType = UNKNOWN; // reset
  gdcm::Tag t1(0x0029,0x0010);
  gdcm::Tag t2(0x0029,0x0020);
  if( uint16_t(de.GetTag().GetElement() << 8 ) >> 8 == t1.GetElement() )
    {
    std::cout << "Image shadow data (0029,xx10)\n\n";
    }
  else if( uint16_t(de.GetTag().GetElement() << 8 ) >> 8 == t2.GetElement() )
    {
    std::cout << "Series shadow data (0029,xx20)\n\n";
    }
  else
    {
    std::cerr << "Unhandled tag: " << de.GetTag() << std::endl;
    }
 
  const ByteValue *bv = de.GetByteValue();
  assert( bv );
  const char *p = bv->GetPointer();
  assert( p );
  std::string s( bv->GetPointer(), bv->GetLength() );
  std::stringstream ss;
  ss.str( s );
  char dummy[4+1];
  dummy[4] = 0;
  ss.read(dummy, 4);
  //std::cout << dummy << std::endl;
  // 1. NEW FORMAT
  // 2. OLD FORMAT
  // 3. Zero out
  // 4. DATASET FORMAT (Explicit Little Endian), with group=0x0 elements:
  if( strcmp( dummy, "SV10" ) != 0 )
    {
    if( checkallzero(ss) )
      {
      std::cout << "Zeroed out" << std::endl;
      InternalType = ZEROED_OUT;
      return;
      }
    else if( strcmp(dummy, "\0\0\0\0" ) == 0 )
      {
      // Most often start with an element (0000,xxxx)
      // And ends with element:
      // (ffff,ffff)	CS	10	END!      
      ss.seekg( 0, std::ios::beg );
      // SIEMENS-JPEG-CorruptFragClean.dcm
      InternalType = DATASET_FORMAT;
      DataSet &ds = InternalDataSet;
      DataElement xde;
      while( xde.Read<ExplicitDataElement,SwapperNoOp>( ss ) )
        {
        ds.Insert( xde );
        }
      //std::cout << ds << std::endl;
      assert( ss.eof() );
      return;
      }
    else
      {
      //abort();
      ss.seekg( 0, std::ios::beg );
      // No magic number for this one:
      // SIEMENS_Sonata-16-MONO2-Value_Multiplicity.dcm
      InternalType = NOMAGIC;
      }
    }
  if( strcmp( dummy, "SV10" ) == 0 )
    {
    // NEW FORMAT !
    ss.read(dummy, 4);
    assert( strcmp( dummy, "\4\3\2\1" ) == 0 );
    InternalType = SV10;
    }
  assert( InternalType != UNKNOWN );

  uint32_t n;
  ss.read((char*)&n, sizeof(n));
  uint32_t unused;
  ss.read((char*)&unused, sizeof(unused));
  assert( unused == 77 ); // 'M' character...

  for(uint32_t i = 0; i < n; ++i)
    {
    std::cout << i;
    std::cout << " - ";
    char name[64+1];
    name[64] = 0; // security
    ss.read(name, 64);
    std::cout << "'" << name << "' ";
    uint32_t vm;
    ss.read((char*)&vm, sizeof(vm));
    std::cout << "VM " << vm <<  ", ";
    char vr[4];
    ss.read(vr, 4);
    // In dataset without magic signature (OLD FORMAT) vr[3] is garbage...
    assert( /*vr[3] == 0 &&*/ vr[2] == 0 );
    std::cout << "VR " << vr << ", ";
    uint32_t syngodt;
    ss.read((char*)&syngodt, sizeof(syngodt));
    check_mapping(syngodt, vr);
    std::cout << "SyngoDT " << syngodt << ", ";
    uint32_t nitems;
    ss.read((char*)&nitems, sizeof(nitems));
    std::cout << "NoOfItems " << nitems << ", ";
    uint32_t xx;
    ss.read((char*)&xx, sizeof(xx));
    //std::cout << "xx=" << xx<< std::endl;
    assert( xx == 77 || xx == 205 );

    std::cout << "Data ";
    for( uint32_t j = 0; j < nitems; ++j)
      {
      uint32_t item_xx[4];
      ss.read((char*)&item_xx, 4*sizeof(uint32_t));
      assert( item_xx[2] == 77 || item_xx[2] == 205 );
      uint32_t len = item_xx[1]; // 2nd element
      assert( item_xx[0] == item_xx[1] && item_xx[1] == item_xx[3] );
      if( len )
        {
        char *val = new char[len+1];
        val[len] = 0; // security
        ss.read(val,len);
        // WARNING vr does not means anything AFAIK, 
        // simply print the value as if it was IS/DS or LO (ASCII)
        if( j ) std::cout << '\\';
        std::cout << "'" << val << "'";

        char dummy[4];
        uint32_t dummy_len = (4 - len % 4) % 4;
        ss.read(dummy, dummy_len );

        for(uint32_t d= 0; d < dummy_len; ++d)
          {
          // dummy[d]  is zero in the NEW format
          //assert( dummy[d] == 0 );
          //for the old format there appears to be some garbage:
          if( dummy[d] )
            {
            //std::cout << "dummy=" << (int)dummy[d] << std::endl;
            }
          }
        delete[] val;     
        }
      }
    std::cout << std::endl;
    }
 
}

static const char csaheader[] = "SIEMENS CSA HEADER";
static const gdcm::PrivateTag t1(0x0029,0x0010,csaheader);
static const gdcm::PrivateTag t2(0x0029,0x0020,csaheader);

const PrivateTag & CSAHeader::GetCSAImageHeaderInfoTag()
{
  return t1;
}

const PrivateTag & CSAHeader::GetCSASeriesHeaderInfoTag()
{
  return t2;
}

} // end namespace gdcm

