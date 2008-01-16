
// GENERATED FILE DO NOT EDIT
// $ xsltproc TagToType.xsl DICOMV3.xml > gdcmTagToType.h

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

#ifndef __gdcmTagToType_h
#define __gdcmTagToType_h

#include "gdcmVR.h"
#include "gdcmVM.h"

namespace gdcm {
// default template:
template <uint16_t,uint16_t> struct TagToType;
// template for group length:
template <uint16_t group> struct TagToType<group,0x0000> { typedef VRToType<VR::UL>::Type Type; enum { VRType = VR::UL }; enum { VMType = VM::VM1 }; };
template <> struct TagToType<0x0000,0x0000> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0001> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0002> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0003> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0010> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0100> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0110> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0120> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0200> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0300> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0400> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0600> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0700> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0800> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0850> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0860> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0900> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0901> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0000,0x0902> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x0903> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x1000> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x1001> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x1002> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x1005> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0000,0x1008> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x1020> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x1021> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x1022> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x1023> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x1030> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x1031> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x4000> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x4010> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x5010> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x5020> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x5110> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x5120> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x5130> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x5140> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x5150> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x5160> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x5170> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x5180> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x5190> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x51a0> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0000,0x51b0> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0002,0x0000> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0002,0x0001> {
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0002,0x0002> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0002,0x0003> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0002,0x0010> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0002,0x0012> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0002,0x0013> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0002,0x0016> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0002,0x0100> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0002,0x0102> {
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1130> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1141> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_8 };
};
template <> struct TagToType<0x0004,0x1142> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1200> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1202> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1212> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1220> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1400> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1410> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1420> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1430> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1432> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1500> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_8 };
};
template <> struct TagToType<0x0004,0x1504> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1510> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1511> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x1512> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0004,0x151a> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0004,0x1600> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0001> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0005> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x0008> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM2_n };
};
template <> struct TagToType<0x0008,0x0010> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0012> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0013> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0014> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0016> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0018> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x001a> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x001b> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0020> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0021> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0022> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0023> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0024> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0025> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x002a> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0030> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0031> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0032> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0033> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0034> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0035> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0040> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0041> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0042> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0050> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0052> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0054> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x0056> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0058> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x0060> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0061> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x0062> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x0064> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0068> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0070> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0080> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0081> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0082> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0090> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0092> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0094> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x0096> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0100> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0102> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0103> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0104> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0105> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0106> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0107> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x010b> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x010c> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x010d> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x010f> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0110> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0112> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0114> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0115> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0116> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x0201> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1000> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1010> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1030> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1032> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x103e> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1040> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1048> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x1049> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1050> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x1052> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1060> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x1062> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1070> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x1072> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1080> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x1084> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1090> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1100> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1110> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1111> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1115> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1120> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1125> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1130> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x113a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1140> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1145> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x114a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x114b> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1150> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1155> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x115a> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x1160> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x1195> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1197> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1198> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1199> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1200> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x1250> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2110> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2111> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2112> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2120> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2122> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2124> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2127> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2128> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2129> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x212a> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2130> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x2132> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0008,0x2142> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2143> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2144> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2200> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2204> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2208> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2218> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2220> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2228> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2229> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2230> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2240> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2242> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2244> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2246> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2251> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2253> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2255> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2256> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2257> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2258> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x2259> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x225a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x225c> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x3001> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x3010> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x4000> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9007> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM4 };
};
template <> struct TagToType<0x0008,0x9092> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9121> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9123> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9124> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9154> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9205> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9206> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9207> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9208> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9209> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9215> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9237> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9410> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9458> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9459> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0008,0x9460> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x0010> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x0020> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x0021> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x0022> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x0030> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x0032> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x0040> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x0050> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x0101> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x0102> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x1000> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0010,0x1001> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0010,0x1002> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x1005> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x1010> {
typedef VRToType<VR::AS>::Type Type;
enum { VRType = VR::AS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x1020> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x1030> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x1040> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x1050> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0010,0x1060> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x1080> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x1081> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x1090> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2000> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0010,0x2110> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0010,0x2150> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2152> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2154> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0010,0x2160> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2180> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x21a0> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x21b0> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x21c0> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x21d0> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x21f0> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2201> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2202> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2203> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2292> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2293> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2294> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2295> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2296> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2297> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2298> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x2299> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x4000> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0010,0x9431> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0010> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0020> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0021> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0030> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0031> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0040> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0042> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0050> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0051> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0060> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0062> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0063> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0012,0x0064> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0071> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0012,0x0072> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0010> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0012> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0014> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0015> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x0021> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x0022> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x0023> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0024> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0025> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0026> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0027> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0028> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0029> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x002a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0030> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x0031> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0032> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0033> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x0034> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0035> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0036> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0037> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0038> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0039> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x003a> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0040> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0050> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0060> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0070> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0071> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0072> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0073> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0074> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0075> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0080> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0081> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0082> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0083> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0084> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0085> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0086> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x0087> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0088> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0089> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0090> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0091> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0093> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0094> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x0095> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1000> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1002> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1003> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1004> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1005> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1006> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1007> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1008> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1010> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1011> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1012> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1014> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1016> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1017> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1018> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1019> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x101a> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x101b> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1020> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1022> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1023> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1030> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1040> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1041> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1042> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1043> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1044> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1045> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1046> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1047> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1048> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1049> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1050> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1060> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1061> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1062> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1063> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1064> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1065> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1066> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1067> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1068> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1069> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x106a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x106c> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x106e> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1070> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1071> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1072> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1073> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1074> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1075> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1076> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1077> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1078> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1079> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1080> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1081> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1082> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1083> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1084> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1085> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1086> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1088> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1090> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1094> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1100> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1110> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1111> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1114> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1120> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1121> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1130> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1131> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1134> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1135> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1136> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1137> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1138> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x113a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1140> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1141> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1142> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1143> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1144> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1145> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1146> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1147> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1149> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x1150> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1151> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1152> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1153> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1154> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1155> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1156> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x115a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x115e> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1160> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1161> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1162> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1164> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x1166> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1170> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1180> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1181> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1182> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x1183> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x1184> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x1190> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1191> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x11a0> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x11a2> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1200> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1201> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1210> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1240> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1242> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1243> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1244> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1250> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1251> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1260> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1261> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1300> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1301> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1302> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1310> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM4 };
};
template <> struct TagToType<0x0018,0x1312> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1314> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1315> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1316> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1318> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1400> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1401> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1402> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1403> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1404> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1405> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1450> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1460> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1470> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1480> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1490> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1491> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1495> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1500> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1508> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1510> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1511> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1520> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1521> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x1530> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1531> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1600> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_3 };
};
template <> struct TagToType<0x0018,0x1602> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1604> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1606> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1608> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1610> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x1612> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1620> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2_2n };
};
template <> struct TagToType<0x0018,0x1622> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1623> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1624> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0018,0x1700> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_3 };
};
template <> struct TagToType<0x0018,0x1702> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1704> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1706> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1708> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1710> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x1712> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1720> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2_2n };
};
template <> struct TagToType<0x0018,0x1800> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1801> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1802> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x1803> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x2001> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x2002> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x2003> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x2004> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x2005> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x2006> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x2010> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x2020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x2030> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x3100> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x3101> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x3102> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x3103> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x3104> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x3105> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x4000> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5000> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x5010> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0018,0x5012> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5020> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5021> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5022> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5024> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5026> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5027> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5028> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5029> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5030> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5040> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5050> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5100> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5101> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5104> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x5210> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM6 };
};
template <> struct TagToType<0x0018,0x5212> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0018,0x6000> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6011> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6012> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6014> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6016> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6018> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x601a> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x601c> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x601e> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6020> {
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6022> {
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6024> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6026> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6028> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x602a> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x602c> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x602e> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6030> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6031> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6032> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6034> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6036> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6038> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6039> {
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x603a> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x603b> {
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x603c> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x603d> {
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x603e> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x603f> {
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6040> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6041> {
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6042> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6043> {
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6044> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6046> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6048> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x604a> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x604c> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x604e> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6050> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6052> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x6054> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x6056> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x6058> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x605a> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x6060> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x7000> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7001> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7004> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7005> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7006> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7008> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x700a> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x700c> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x700e> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7010> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7011> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7012> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7014> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7016> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x701a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x7020> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x7022> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x7024> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7026> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x7028> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x702a> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x702b> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7030> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x7032> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7034> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7040> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7041> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7042> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7044> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7046> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x7048> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x704c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7050> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x7052> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x7054> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x7060> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7062> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7064> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x7065> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x8150> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x8151> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9004> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9005> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9006> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9008> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9009> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9010> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9011> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9012> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9014> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9015> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9016> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9017> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9018> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9019> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9021> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9022> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9024> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9025> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9026> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9027> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9028> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9029> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9030> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9032> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9033> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9034> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9035> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9036> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9037> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9041> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9042> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9043> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9044> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9045> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9046> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9047> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9048> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9049> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9050> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9051> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9052> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x9053> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x9054> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9058> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9059> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9060> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x9061> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x9062> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9063> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x9064> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9065> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x9066> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x9067> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9069> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9070> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9073> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9074> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9075> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9076> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9077> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9078> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9079> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0018,0x9080> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9081> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9082> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9083> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9084> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9085> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9087> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9089> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0018,0x9090> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0018,0x9091> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9093> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9094> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9095> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9096> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9098> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x9100> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x9101> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9103> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9104> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9105> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0018,0x9106> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0018,0x9107> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9112> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9114> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9115> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9117> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9118> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9119> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9125> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9126> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9127> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9147> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9151> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9152> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9155> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9159> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9166> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9168> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9169> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9170> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9171> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9172> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9173> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9174> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9175> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9176> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9177> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9178> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9179> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9180> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9181> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9182> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9183> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9184> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9185> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9186> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9195> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9196> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9197> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9198> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9199> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9200> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9214> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9217> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9218> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9219> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9220> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9226> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9227> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9231> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9232> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9234> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9236> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9239> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9240> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9241> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9295> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9296> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9301> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9302> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9303> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9304> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9305> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9306> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9307> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9308> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9309> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9310> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9311> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9312> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9313> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0018,0x9314> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9315> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9316> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9317> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x9318> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0018,0x9319> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9320> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9321> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9322> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x9323> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9324> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9325> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9326> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9327> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9328> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9329> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9330> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9332> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9333> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9334> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9335> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9337> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9338> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9340> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9341> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9342> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9343> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9344> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9345> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9346> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9351> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9352> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0018,0x9360> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9401> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9402> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9403> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9404> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x9405> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9406> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9407> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9412> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9417> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9420> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9423> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9424> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9425> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9426> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9427> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9428> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x9429> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x9430> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x9432> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9433> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9434> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9435> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9436> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9437> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9438> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9439> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9440> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0018,0x9441> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9442> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM2_n };
};
template <> struct TagToType<0x0018,0x9447> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9449> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9451> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9452> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9455> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9456> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9457> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9461> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0018,0x9462> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9463> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9464> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9465> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9466> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9467> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9468> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9469> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9470> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9471> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9472> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9473> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9474> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9476> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9477> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9504> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9506> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9507> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9508> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9509> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9510> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9511> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9514> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9515> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9516> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9517> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9524> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9525> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9526> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9527> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9528> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9530> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9531> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9538> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9601> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9602> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9603> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9604> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9605> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9606> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0x9607> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0xa001> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0xa002> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0018,0xa003> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x000d> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x000e> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0010> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0011> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0012> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0013> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0014> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0015> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0016> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0017> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0018> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0019> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0020,0x0022> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0024> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0026> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0030> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0020,0x0032> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0020,0x0035> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM6 };
};
template <> struct TagToType<0x0020,0x0037> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM6 };
};
template <> struct TagToType<0x0020,0x0050> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0052> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0060> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0062> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0070> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0080> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0020,0x0100> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0105> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0110> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x0200> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1000> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1001> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1002> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1003> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1004> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1005> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0020,0x1040> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1041> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1070> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0020,0x1200> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1202> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1204> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1206> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1208> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x1209> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x3100> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0020,0x3401> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x3402> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x3403> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x3404> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x3405> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x3406> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x4000> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x5000> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0020,0x5002> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0020,0x9056> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9057> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9071> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9072> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9111> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9113> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9116> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9128> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9153> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9156> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9157> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0020,0x9158> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9161> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9162> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9163> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9164> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9165> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9167> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9213> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9221> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9222> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9228> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9238> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9241> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9245> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9246> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9247> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9248> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9249> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9250> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9251> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9252> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9253> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9254> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9255> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9256> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9257> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9421> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9450> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9453> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9518> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0020,0x9529> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0020,0x9536> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0001> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0002> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0022,0x0003> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0004> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0022,0x0005> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0006> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0007> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0008> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0009> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x000a> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x000b> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x000c> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x000d> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x000e> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0010> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0011> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0012> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0013> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0014> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0015> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0016> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0017> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0018> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0019> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x001a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x001b> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x001c> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x001d> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0020> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0021> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0022> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0030> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0031> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0032> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2_2n };
};
template <> struct TagToType<0x0022,0x0035> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0036> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0037> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0038> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0039> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0041> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0042> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0048> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0049> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x004e> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0055> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0056> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0057> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0022,0x0058> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0002> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0003> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0004> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0005> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0006> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0008> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0009> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x000a> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0010> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0011> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0012> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0014> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0030> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0028,0x0031> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0028,0x0032> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0028,0x0034> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0028,0x0040> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0050> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0051> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x005f> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0060> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0061> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0062> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0063> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0065> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0066> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0068> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0069> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0070> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0080> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0081> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0082> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0090> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0091> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0092> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0093> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0094> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0100> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0101> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0102> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0103> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0200> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0300> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0301> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0400> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0401> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0402> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0403> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0404> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0400> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0401> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0402> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0403> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0700> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0701> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0702> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0710> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0720> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0721> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0722> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0730> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0740> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0800> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0802> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0803> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0804> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0808> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x0a02> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x0a04> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1040> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1041> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1050> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x1051> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x1052> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1053> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1054> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1055> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x1056> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1080> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1090> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1199> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1201> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1202> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1203> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1211> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1212> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1213> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1214> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1221> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1222> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1223> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1300> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1350> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1351> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x1352> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x135a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x2000> {
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x2110> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x2112> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x2114> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x3000> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x3003> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x3004> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x3010> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x3110> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x4000> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x5000> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x6010> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x6020> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x6022> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x6023> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x6030> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x6040> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x6100> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x6101> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x6102> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2_2n };
};
template <> struct TagToType<0x0028,0x6110> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x6112> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x6114> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0028,0x6120> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x6190> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x7fe0> {
typedef VRToType<VR::UT>::Type Type;
enum { VRType = VR::UT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9001> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9002> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9003> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9099> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9108> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9110> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9132> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9145> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9235> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9411> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9415> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9416> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9422> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9443> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9444> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9445> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9446> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0028,0x9454> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9474> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0028,0x9520> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM16 };
};
template <> struct TagToType<0x0028,0x9537> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x000a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x000c> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x0012> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x0032> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x0033> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x0034> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x0035> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1000> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1001> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1010> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1011> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1020> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1021> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0032,0x1030> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1031> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1032> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1033> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1040> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1041> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1050> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1051> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1055> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1060> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1064> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x1070> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0032,0x4000> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0004> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0008> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0010> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0011> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0016> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x001a> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x001b> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x001c> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x001d> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x001e> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0020> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0021> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0030> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0032> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0040> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0044> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0050> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0060> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0061> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0062> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0100> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0300> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0400> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0500> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x0502> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0038,0x4000> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0004> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0005> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0010> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x001a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0020> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0200> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0202> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0203> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0205> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x003a,0x0208> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0209> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x020a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x020c> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0210> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0211> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0212> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0213> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0214> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0215> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0218> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x021a> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0220> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0221> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0222> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0223> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0230> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0231> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x003a,0x0240> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0241> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0242> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0244> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x003a,0x0245> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0246> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0247> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0248> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0300> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0301> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x003a,0x0302> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0001> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0040,0x0002> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0003> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0004> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0005> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0006> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0007> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0008> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0009> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x000a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x000b> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0010> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0040,0x0011> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0012> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0100> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0220> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0241> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0242> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0243> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0244> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0245> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0250> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0251> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0252> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0253> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0254> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0255> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0260> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0270> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0275> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0280> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0281> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0293> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0294> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0295> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0296> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0300> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0301> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0302> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0303> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_2 };
};
template <> struct TagToType<0x0040,0x0306> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0307> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x030e> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0310> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0312> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0314> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0316> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0318> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0320> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0321> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0324> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0330> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0340> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0400> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0440> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0441> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x050a> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0550> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0551> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0552> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0553> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0555> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x0556> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x059a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x06fa> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x071a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x072a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x073a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x074a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x08d8> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x08da> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x08ea> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x09f8> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1001> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1002> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1003> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1004> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1005> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1006> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1007> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1008> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1009> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x100a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1010> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0040,0x1011> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1101> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1102> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x1103> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0040,0x1400> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x2001> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x2004> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x2005> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x2006> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x2007> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x2008> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x2009> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x2010> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x2016> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x2017> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x2400> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x3001> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4001> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4002> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4003> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4004> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4005> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4006> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4007> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4009> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4010> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4011> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4015> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4016> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4018> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4019> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4021> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4022> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4023> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4025> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4026> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4027> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4028> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4029> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4030> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4031> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4032> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4033> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4034> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4035> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4036> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x4037> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x8302> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x9094> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x9096> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x9098> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x9210> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x9212> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0040,0x9224> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0x9225> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa010> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa027> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa030> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa032> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa040> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa043> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa050> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa073> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa075> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa078> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa07a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa07c> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa080> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa082> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa084> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa088> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa090> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa0b0> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2_2n };
};
template <> struct TagToType<0x0040,0xa120> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa121> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa122> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa123> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa124> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa130> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa132> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0040,0xa136> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0040,0xa138> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0040,0xa13a> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0040,0xa160> {
typedef VRToType<VR::UT>::Type Type;
enum { VRType = VR::UT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa168> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa170> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa180> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa195> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa300> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa301> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa30a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0040,0xa353> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa354> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa360> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa370> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa372> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa375> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa385> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa390> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa491> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa492> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa493> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa494> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa504> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa525> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xa730> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xb020> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xdb00> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xdb06> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xdb07> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xdb0b> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xdb0c> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xdb0d> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xdb73> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0040,0xe001> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xe004> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xe006> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0040,0xe010> {
typedef VRToType<VR::UT>::Type Type;
enum { VRType = VR::UT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0042,0x0010> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0042,0x0011> {
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0042,0x0012> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0042,0x0013> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0042,0x0014> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0044,0x0001> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x0002> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x0003> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x0004> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x0007> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x0008> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0044,0x0009> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x000a> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x000b> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x0010> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x0011> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x0012> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x0013> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0044,0x0019> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0050,0x0004> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0050,0x0010> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0050,0x0014> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0050,0x0016> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0050,0x0017> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0050,0x0018> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0050,0x0019> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0050,0x0020> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0010> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x0011> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0012> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0013> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0014> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0015> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0016> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0017> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0018> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0020> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x0021> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0022> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0030> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x0031> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0032> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0033> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0036> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0038> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0039> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0050> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x0051> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0052> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0053> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0060> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x0061> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0062> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0063> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0070> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x0071> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0072> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0073> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0080> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x0081> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0090> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x0100> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x0101> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0200> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0202> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0210> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x0211> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0220> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0222> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0300> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0302> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0304> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0306> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0308> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0400> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0410> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0412> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0414> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x0500> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1000> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0054,0x1001> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1002> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1004> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1100> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1101> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1102> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1103> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1104> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1105> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1200> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1201> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0054,0x1202> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1203> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0054,0x1210> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1220> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x1300> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1310> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1311> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x1320> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1321> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1322> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1323> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1324> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1330> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0054,0x1400> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0054,0x1401> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0060,0x3000> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0060,0x3002> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0060,0x3008> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0060,0x3010> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0060,0x3020> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0062,0x0001> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x0002> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x0003> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x0004> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x0005> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x0006> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x0008> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x0009> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x000a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x000b> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0062,0x000c> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x000d> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0062,0x000e> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x000f> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0062,0x0010> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0064,0x0002> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0064,0x0003> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0064,0x0005> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0064,0x0007> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0064,0x0008> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0064,0x0009> {
typedef VRToType<VR::OF>::Type Type;
enum { VRType = VR::OF };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0064,0x000f> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0064,0x0010> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0001> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0002> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0003> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0004> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0005> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0006> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0008> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0009> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0010> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0070,0x0011> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0070,0x0012> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0014> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0070,0x0015> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0020> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0021> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0022> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2_n };
};
template <> struct TagToType<0x0070,0x0023> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0024> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0040> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0041> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0042> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0050> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0070,0x0051> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0070,0x0052> {
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0070,0x0053> {
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0070,0x005a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0060> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0062> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0066> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0067> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0070,0x0068> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0080> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0081> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0082> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0083> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0084> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0086> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0100> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0101> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0070,0x0102> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0070,0x0103> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0306> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0308> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0309> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x030a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x030c> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x030d> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x030f> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0310> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0311> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0312> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0314> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0318> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x031a> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x031c> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x031e> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0401> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x0070,0x0402> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0403> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0404> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0070,0x0405> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0002> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0004> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0006> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0008> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x000a> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x000c> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x000e> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0010> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0012> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0014> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0020> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0022> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0024> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0026> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0028> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0030> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0032> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0034> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0038> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0072,0x003a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x003c> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0072,0x003e> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0040> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0050> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0052> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0054> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0056> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0060> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x0062> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x0064> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x0066> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x0068> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x006a> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x006c> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x006e> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0070> {
typedef VRToType<VR::UT>::Type Type;
enum { VRType = VR::UT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0072> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x0074> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x0076> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x0078> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x007a> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x007c> {
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x007e> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x0080> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0100> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0102> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0104> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0106> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0108> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM4 };
};
template <> struct TagToType<0x0072,0x010a> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x010c> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x010e> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0200> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0202> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0203> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0204> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0206> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0208> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0210> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0212> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2_n };
};
template <> struct TagToType<0x0072,0x0214> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0216> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0218> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x0300> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0302> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0304> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0306> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0308> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0310> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0312> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0314> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0316> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0318> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0320> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0330> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0400> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0402> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0404> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0406> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0500> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0510> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0512> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0514> {
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0516> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0520> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0072,0x0600> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0602> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0604> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0700> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x0072,0x0702> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0704> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0706> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0710> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0712> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0714> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0716> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0717> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0072,0x0718> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1000> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1002> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1004> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1006> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1008> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x100a> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x100c> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x100e> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1020> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1022> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1024> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1030> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1032> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1034> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1036> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1038> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x103a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM4 };
};
template <> struct TagToType<0x0074,0x1040> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1042> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1044> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1046> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1048> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0074,0x104a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0074,0x104c> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x104e> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1050> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0074,0x1052> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1054> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1056> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1200> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1202> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1204> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1210> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1212> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1216> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1220> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1222> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1230> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1234> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1236> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1238> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1242> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1244> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0074,0x1246> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0088,0x0130> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0088,0x0140> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0088,0x0200> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0088,0x0904> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0088,0x0906> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0088,0x0910> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0088,0x0912> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_32 };
};
template <> struct TagToType<0x0100,0x0410> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0100,0x0420> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0100,0x0424> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0100,0x0426> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0005> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0010> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0015> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0020> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x0400,0x0100> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0105> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0110> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0115> {
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0120> {
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0305> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0310> {
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0401> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0402> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0403> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0404> {
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0500> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0510> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0520> {
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0550> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0561> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0562> {
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0563> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0564> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x0400,0x0565> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x1000,0x0000> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x1000,0x0001> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x1000,0x0002> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x1000,0x0003> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x1000,0x0004> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x1000,0x0005> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x1010,0x0000> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x2000,0x0010> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x001e> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0030> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0040> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0050> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0060> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0061> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0062> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0063> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0065> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0067> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0069> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x006a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x00a0> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x00a1> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x00a2> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x00a4> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x00a8> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0500> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2000,0x0510> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0010> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0030> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0040> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0050> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0052> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0054> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0060> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0080> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x00a6> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x00a7> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x2010,0x00a8> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x00a9> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x2010,0x0100> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0110> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0120> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0130> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0140> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0150> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0152> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0154> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x015e> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0160> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0376> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x2010,0x0500> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0510> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2010,0x0520> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2020,0x0010> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2020,0x0020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2020,0x0030> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2020,0x0040> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2020,0x0050> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2020,0x00a0> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2020,0x00a2> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2020,0x0110> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2020,0x0111> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2020,0x0130> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2020,0x0140> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2030,0x0010> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2030,0x0020> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2040,0x0010> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2040,0x0011> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_99 };
};
template <> struct TagToType<0x2040,0x0020> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2040,0x0060> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2040,0x0070> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2040,0x0072> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2040,0x0074> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2040,0x0080> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2040,0x0082> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2040,0x0090> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2040,0x0100> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2040,0x0500> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2050,0x0010> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2050,0x0020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2050,0x0500> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2100,0x0010> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2100,0x0020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2100,0x0030> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2100,0x0040> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2100,0x0050> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2100,0x0070> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2100,0x0140> {
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2100,0x0160> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2100,0x0170> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2100,0x0500> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2110,0x0010> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2110,0x0020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2110,0x0030> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2110,0x0099> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2120,0x0010> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2120,0x0050> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2120,0x0070> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2130,0x0010> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2130,0x0015> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2130,0x0030> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2130,0x0040> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2130,0x0050> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2130,0x0060> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2130,0x0080> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2130,0x00a0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2130,0x00c0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x0001> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x0002> {
typedef VRToType<VR::UT>::Type Type;
enum { VRType = VR::UT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x0003> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x0004> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x0005> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x0006> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x0007> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x0008> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x0009> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x000a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x000b> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x000c> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x000d> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x000e> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x2200,0x000f> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x2200,0x0020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0002> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0003> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0004> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x000a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x000c> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x000d> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x3002,0x000e> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0010> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM6 };
};
template <> struct TagToType<0x3002,0x0011> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x3002,0x0012> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x3002,0x0020> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0022> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0024> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0026> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0028> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0029> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0030> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0032> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0034> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM4 };
};
template <> struct TagToType<0x3002,0x0040> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0041> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3002,0x0042> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0001> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0002> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0004> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0006> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0008> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x3004,0x000a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x000c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2_n };
};
template <> struct TagToType<0x3004,0x000e> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0010> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0012> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0014> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_3 };
};
template <> struct TagToType<0x3004,0x0040> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x3004,0x0042> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0050> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0052> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0054> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0056> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0058> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2_2n };
};
template <> struct TagToType<0x3004,0x0060> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0062> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0070> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0072> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3004,0x0074> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0002> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0004> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0006> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0008> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0009> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0010> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0012> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0014> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0016> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0020> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0022> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0024> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0026> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0028> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x002a> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x3006,0x002c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0030> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0033> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0036> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0038> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0039> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0040> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0042> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0044> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0045> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x3006,0x0046> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0048> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0049> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x3006,0x0050> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3_3n };
};
template <> struct TagToType<0x3006,0x0080> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0082> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0084> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0085> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0086> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x0088> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00a0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00a4> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00a6> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00b0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00b2> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00b4> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00b6> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00b7> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00b8> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00c0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00c2> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00c4> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3006,0x00c6> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM16 };
};
template <> struct TagToType<0x3006,0x00c8> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0010> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0012> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0014> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0016> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0020> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0021> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0022> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0024> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0025> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x002a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x002b> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x002c> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0030> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0032> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0033> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0036> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0037> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x003a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x003b> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0040> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0041> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0042> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0044> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0045> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0046> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0047> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x3008,0x0048> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0050> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0052> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0054> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0056> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x005a> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0060> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0061> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0062> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0063> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0064> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0065> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0066> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0068> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x006a> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0070> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0072> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0074> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0076> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0078> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x007a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0080> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0082> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0090> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0092> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x00a0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x00b0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x00c0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x00d0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x00e0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x00f0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x00f2> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x00f4> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x00f6> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0100> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0105> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0110> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0116> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0120> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0122> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0130> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0132> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0134> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0136> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0138> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x013a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x013c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0140> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0142> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0150> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0152> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0160> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0162> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0164> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0166> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0168> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0200> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0202> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0220> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0223> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0224> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0230> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0240> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0250> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x3008,0x0251> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0002> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0003> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0004> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0006> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0007> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0009> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x300a,0x000a> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x000b> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x300a,0x000c> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x000e> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0010> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0012> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0013> {
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0014> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0015> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0016> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0018> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x300a,0x001a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0021> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0022> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0023> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0025> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0026> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0027> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0028> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x002a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x002b> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x002c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x002d> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0040> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0042> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0043> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0044> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0046> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0048> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x004a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x004b> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x004c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x004e> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x004f> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0050> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0051> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0052> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0053> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0055> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0070> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0071> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0072> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0078> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0079> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x007a> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x007b> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0080> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0082> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x300a,0x0084> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0086> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0088> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0089> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x008a> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00a0> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00a2> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x300a,0x00a4> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00b0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00b2> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00b3> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00b4> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00b6> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00b8> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00ba> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00bb> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00bc> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00be> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3_n };
};
template <> struct TagToType<0x300a,0x00c0> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00c2> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00c3> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00c4> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00c6> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00c7> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00c8> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00ca> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00cc> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x300a,0x00ce> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00d0> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00d1> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00d2> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00d3> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00d4> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00d5> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00d6> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00d7> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00d8> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00d9> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00da> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00db> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00dc> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00dd> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00e0> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00e1> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00e2> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00e3> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00e4> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00e5> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00e6> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00e7> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00e8> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00e9> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x300a,0x00ea> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x300a,0x00eb> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x300a,0x00ec> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x300a,0x00ed> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00ee> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00f0> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00f2> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00f3> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00f4> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00f5> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00f6> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00f7> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00f8> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00f9> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00fa> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00fb> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00fc> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x00fe> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0100> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0102> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0104> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0106> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2_2n };
};
template <> struct TagToType<0x300a,0x0107> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0108> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0109> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x010a> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x010c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x010e> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0110> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0111> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0112> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0114> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0115> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0116> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0118> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x011a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x011c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2_2n };
};
template <> struct TagToType<0x300a,0x011e> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x011f> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0120> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0121> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0122> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0123> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0124> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0125> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0126> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0128> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0129> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x012a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x012c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x300a,0x012e> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x300a,0x0130> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0134> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0140> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0142> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0144> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0146> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0148> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x014a> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x014c> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x014e> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0180> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0182> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0183> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0184> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0190> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0192> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0194> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0196> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0198> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0199> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x019a> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01a0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01a2> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01a4> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01a6> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01a8> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01b0> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01b2> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01b4> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01b6> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01b8> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01ba> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01bc> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01d0> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01d2> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01d4> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x01d6> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0200> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0202> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0206> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0210> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0212> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0214> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0216> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0218> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x021a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0222> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0224> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0226> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0228> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0229> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x022a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x022b> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x022c> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x022e> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0230> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0232> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0234> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0236> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0238> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0240> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0242> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0244> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0250> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0260> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0262> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0263> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0264> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0266> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x026a> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x026c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0280> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0282> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0284> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0286> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0288> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x028a> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x028c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0290> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0291> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0292> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0294> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0296> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0298> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x029c> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x029e> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02a0> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02a2> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02a4> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02b0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02b2> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02b3> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02b4> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02b8> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02ba> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02c8> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02d0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02d2> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02d4> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x300a,0x02d6> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02e0> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02e1> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02e2> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x300a,0x02e3> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02e4> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02e5> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02e6> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x300a,0x02e7> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02e8> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02ea> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x02eb> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0302> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0304> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0306> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0308> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x030a> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x300a,0x030c> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x030d> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x030f> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0312> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0314> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0316> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0318> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0320> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0322> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0330> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0332> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0334> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0336> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0338> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x033a> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x033c> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0340> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0342> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0344> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0346> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0348> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x034a> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x034c> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0350> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0352> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0354> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0356> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0358> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x035a> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0360> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0362> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0364> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0366> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0370> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0372> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0374> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0380> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0382> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0384> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0386> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0388> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x038a> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0390> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0392> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0394> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x300a,0x0396> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x300a,0x0398> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x300a,0x039a> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x03a0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x03a2> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x03a4> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x03a6> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x03a8> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x03aa> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x03ac> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0401> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0402> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0410> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0412> {
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM3 };
};
template <> struct TagToType<0x300a,0x0420> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0421> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0422> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0423> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300a,0x0424> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0002> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0004> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0006> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0007> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0008> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0009> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x000a> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x000c> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x000e> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0020> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0022> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0040> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0042> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0050> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0051> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0055> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0060> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x006a> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0080> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x00a0> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x00b0> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x00c0> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x00d0> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x00e0> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x00f0> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x00f2> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x00f4> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x00f6> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0100> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0102> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300c,0x0104> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300e,0x0002> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300e,0x0004> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300e,0x0005> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x300e,0x0008> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4000,0x0010> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4000,0x4000> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0040> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0042> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0050> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0100> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0101> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0102> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0103> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0108> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0109> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x010a> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x010b> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x010c> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0111> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0112> {
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0113> {
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0114> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0115> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0117> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0118> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0119> {
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x011a> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0200> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0202> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0210> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0212> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x0300> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4008,0x4000> {
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x4ffe,0x0001> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x0005> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x0010> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x0020> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x0022> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x0030> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x5000,0x0040> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x5000,0x0103> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x0104> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x5000,0x0105> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x5000,0x0106> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x5000,0x0110> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x5000,0x0112> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x5000,0x0114> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x5000,0x1001> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x2000> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x2002> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x2004> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x2006> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x2008> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x200a> {
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x200e> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x2500> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x2600> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5000,0x2610> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5200,0x9229> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5200,0x9230> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5400,0x0100> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5400,0x1004> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5400,0x1006> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5600,0x0010> {
typedef VRToType<VR::OF>::Type Type;
enum { VRType = VR::OF };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x5600,0x0020> {
typedef VRToType<VR::OF>::Type Type;
enum { VRType = VR::OF };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0010> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0011> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0012> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0015> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0022> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0040> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0045> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0050> {
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM2 };
};
template <> struct TagToType<0x6000,0x0051> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0052> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0060> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0061> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0062> {
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0063> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0066> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x6000,0x0068> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0069> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0100> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0102> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0110> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0200> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0800> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x6000,0x0802> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x0803> {
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x6000,0x0804> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x1001> {
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x1100> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x1101> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x1102> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x1103> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x1200> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x6000,0x1201> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x6000,0x1202> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x6000,0x1203> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
};
template <> struct TagToType<0x6000,0x1301> {
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x1302> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x1303> {
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x1500> {
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x6000,0x4000> {
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x7fe0,0x0020> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x7fe0,0x0030> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x7fe0,0x0040> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x7f00,0x0011> {
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x7f00,0x0020> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x7f00,0x0030> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0x7f00,0x0040> {
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0xfffa,0xfffa> {
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
};
template <> struct TagToType<0xfffc,0xfffc> {
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
};

} // end namespace gdcm
#endif // __gdcmTagToType_h
