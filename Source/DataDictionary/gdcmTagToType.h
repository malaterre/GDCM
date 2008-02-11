
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
#include "gdcmStaticAssert.h"

namespace gdcm {
// default template: the compiler should only pick it up when the element is private:
template <uint16_t group,uint16_t element> struct TagToType {
GDCM_STATIC_ASSERT( group % 2 );
enum { VRType = VR::VRALL };
enum { VMType = VM::VM1_n };
};
// template for group length:
template <uint16_t group> struct TagToType<group,0x0000> { typedef VRToType<VR::UL>::Type Type; enum { VRType = VR::UL }; enum { VMType = VM::VM1 }; };
template <> struct TagToType<0x0000,0x0000> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0000>::VRString[] = "UL";
const char TagToType<0x0000,0x0000>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0001> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0001>::VRString[] = "UL";
const char TagToType<0x0000,0x0001>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0002> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0002>::VRString[] = "UI";
const char TagToType<0x0000,0x0002>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0003> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0003>::VRString[] = "UI";
const char TagToType<0x0000,0x0003>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0010> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0010>::VRString[] = "CS";
const char TagToType<0x0000,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0100> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0100>::VRString[] = "US";
const char TagToType<0x0000,0x0100>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0110> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0110>::VRString[] = "US";
const char TagToType<0x0000,0x0110>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0120> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0120>::VRString[] = "US";
const char TagToType<0x0000,0x0120>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0200> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0200>::VRString[] = "AE";
const char TagToType<0x0000,0x0200>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0300> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0300>::VRString[] = "AE";
const char TagToType<0x0000,0x0300>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0400> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0400>::VRString[] = "AE";
const char TagToType<0x0000,0x0400>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0600> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0600>::VRString[] = "AE";
const char TagToType<0x0000,0x0600>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0700> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0700>::VRString[] = "US";
const char TagToType<0x0000,0x0700>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0800> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0800>::VRString[] = "US";
const char TagToType<0x0000,0x0800>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0850> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0850>::VRString[] = "US";
const char TagToType<0x0000,0x0850>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0860> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0860>::VRString[] = "US";
const char TagToType<0x0000,0x0860>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0900> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0900>::VRString[] = "US";
const char TagToType<0x0000,0x0900>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0901> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0000,0x0901>::VRString[] = "AT";
const char TagToType<0x0000,0x0901>::VMString[] = "1-n";
template <> struct TagToType<0x0000,0x0902> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0902>::VRString[] = "LO";
const char TagToType<0x0000,0x0902>::VMString[] = "1";
template <> struct TagToType<0x0000,0x0903> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x0903>::VRString[] = "US";
const char TagToType<0x0000,0x0903>::VMString[] = "1";
template <> struct TagToType<0x0000,0x1000> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x1000>::VRString[] = "UI";
const char TagToType<0x0000,0x1000>::VMString[] = "1";
template <> struct TagToType<0x0000,0x1001> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x1001>::VRString[] = "UI";
const char TagToType<0x0000,0x1001>::VMString[] = "1";
template <> struct TagToType<0x0000,0x1002> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x1002>::VRString[] = "US";
const char TagToType<0x0000,0x1002>::VMString[] = "1";
template <> struct TagToType<0x0000,0x1005> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0000,0x1005>::VRString[] = "AT";
const char TagToType<0x0000,0x1005>::VMString[] = "1-n";
template <> struct TagToType<0x0000,0x1008> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x1008>::VRString[] = "US";
const char TagToType<0x0000,0x1008>::VMString[] = "1";
template <> struct TagToType<0x0000,0x1020> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x1020>::VRString[] = "US";
const char TagToType<0x0000,0x1020>::VMString[] = "1";
template <> struct TagToType<0x0000,0x1021> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x1021>::VRString[] = "US";
const char TagToType<0x0000,0x1021>::VMString[] = "1";
template <> struct TagToType<0x0000,0x1022> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x1022>::VRString[] = "US";
const char TagToType<0x0000,0x1022>::VMString[] = "1";
template <> struct TagToType<0x0000,0x1023> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x1023>::VRString[] = "US";
const char TagToType<0x0000,0x1023>::VMString[] = "1";
template <> struct TagToType<0x0000,0x1030> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x1030>::VRString[] = "AE";
const char TagToType<0x0000,0x1030>::VMString[] = "1";
template <> struct TagToType<0x0000,0x1031> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x1031>::VRString[] = "US";
const char TagToType<0x0000,0x1031>::VMString[] = "1";
template <> struct TagToType<0x0000,0x4000> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x4000>::VRString[] = "AT";
const char TagToType<0x0000,0x4000>::VMString[] = "1";
template <> struct TagToType<0x0000,0x4010> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x4010>::VRString[] = "AT";
const char TagToType<0x0000,0x4010>::VMString[] = "1";
template <> struct TagToType<0x0000,0x5010> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x5010>::VRString[] = "SH";
const char TagToType<0x0000,0x5010>::VMString[] = "1";
template <> struct TagToType<0x0000,0x5020> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x5020>::VRString[] = "SH";
const char TagToType<0x0000,0x5020>::VMString[] = "1";
template <> struct TagToType<0x0000,0x5110> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x5110>::VRString[] = "AT";
const char TagToType<0x0000,0x5110>::VMString[] = "1";
template <> struct TagToType<0x0000,0x5120> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x5120>::VRString[] = "AT";
const char TagToType<0x0000,0x5120>::VMString[] = "1";
template <> struct TagToType<0x0000,0x5130> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x5130>::VRString[] = "CS";
const char TagToType<0x0000,0x5130>::VMString[] = "1";
template <> struct TagToType<0x0000,0x5140> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x5140>::VRString[] = "CS";
const char TagToType<0x0000,0x5140>::VMString[] = "1";
template <> struct TagToType<0x0000,0x5150> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x5150>::VRString[] = "CS";
const char TagToType<0x0000,0x5150>::VMString[] = "1";
template <> struct TagToType<0x0000,0x5160> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x5160>::VRString[] = "CS";
const char TagToType<0x0000,0x5160>::VMString[] = "1";
template <> struct TagToType<0x0000,0x5170> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x5170>::VRString[] = "IS";
const char TagToType<0x0000,0x5170>::VMString[] = "1";
template <> struct TagToType<0x0000,0x5180> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x5180>::VRString[] = "CS";
const char TagToType<0x0000,0x5180>::VMString[] = "1";
template <> struct TagToType<0x0000,0x5190> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x5190>::VRString[] = "CS";
const char TagToType<0x0000,0x5190>::VMString[] = "1";
template <> struct TagToType<0x0000,0x51a0> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0000,0x51a0>::VRString[] = "CS";
const char TagToType<0x0000,0x51a0>::VMString[] = "1";
template <> struct TagToType<0x0000,0x51b0> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0000,0x51b0>::VRString[] = "US";
const char TagToType<0x0000,0x51b0>::VMString[] = "1-n";
template <> struct TagToType<0x0002,0x0000> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0002,0x0000>::VRString[] = "UL";
const char TagToType<0x0002,0x0000>::VMString[] = "1";
template <> struct TagToType<0x0002,0x0001> {
static const char VRString[];
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0002,0x0001>::VRString[] = "OB";
const char TagToType<0x0002,0x0001>::VMString[] = "1";
template <> struct TagToType<0x0002,0x0002> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0002,0x0002>::VRString[] = "UI";
const char TagToType<0x0002,0x0002>::VMString[] = "1";
template <> struct TagToType<0x0002,0x0003> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0002,0x0003>::VRString[] = "UI";
const char TagToType<0x0002,0x0003>::VMString[] = "1";
template <> struct TagToType<0x0002,0x0010> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0002,0x0010>::VRString[] = "UI";
const char TagToType<0x0002,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0002,0x0012> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0002,0x0012>::VRString[] = "UI";
const char TagToType<0x0002,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0002,0x0013> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0002,0x0013>::VRString[] = "SH";
const char TagToType<0x0002,0x0013>::VMString[] = "1";
template <> struct TagToType<0x0002,0x0016> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0002,0x0016>::VRString[] = "AE";
const char TagToType<0x0002,0x0016>::VMString[] = "1";
template <> struct TagToType<0x0002,0x0100> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0002,0x0100>::VRString[] = "UI";
const char TagToType<0x0002,0x0100>::VMString[] = "1";
template <> struct TagToType<0x0002,0x0102> {
static const char VRString[];
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0002,0x0102>::VRString[] = "OB";
const char TagToType<0x0002,0x0102>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1130> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1130>::VRString[] = "CS";
const char TagToType<0x0004,0x1130>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1141> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_8 };
static const char VMString[];
};
const char TagToType<0x0004,0x1141>::VRString[] = "CS";
const char TagToType<0x0004,0x1141>::VMString[] = "1-8";
template <> struct TagToType<0x0004,0x1142> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1142>::VRString[] = "CS";
const char TagToType<0x0004,0x1142>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1200> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1200>::VRString[] = "UL";
const char TagToType<0x0004,0x1200>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1202> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1202>::VRString[] = "UL";
const char TagToType<0x0004,0x1202>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1212> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1212>::VRString[] = "US";
const char TagToType<0x0004,0x1212>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1220> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1220>::VRString[] = "SQ";
const char TagToType<0x0004,0x1220>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1400> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1400>::VRString[] = "UL";
const char TagToType<0x0004,0x1400>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1410> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1410>::VRString[] = "US";
const char TagToType<0x0004,0x1410>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1420> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1420>::VRString[] = "UL";
const char TagToType<0x0004,0x1420>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1430> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1430>::VRString[] = "CS";
const char TagToType<0x0004,0x1430>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1432> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1432>::VRString[] = "UI";
const char TagToType<0x0004,0x1432>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1500> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_8 };
static const char VMString[];
};
const char TagToType<0x0004,0x1500>::VRString[] = "CS";
const char TagToType<0x0004,0x1500>::VMString[] = "1-8";
template <> struct TagToType<0x0004,0x1504> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1504>::VRString[] = "UL";
const char TagToType<0x0004,0x1504>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1510> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1510>::VRString[] = "UI";
const char TagToType<0x0004,0x1510>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1511> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1511>::VRString[] = "UI";
const char TagToType<0x0004,0x1511>::VMString[] = "1";
template <> struct TagToType<0x0004,0x1512> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1512>::VRString[] = "UI";
const char TagToType<0x0004,0x1512>::VMString[] = "1";
template <> struct TagToType<0x0004,0x151a> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0004,0x151a>::VRString[] = "UI";
const char TagToType<0x0004,0x151a>::VMString[] = "1-n";
template <> struct TagToType<0x0004,0x1600> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0004,0x1600>::VRString[] = "UL";
const char TagToType<0x0004,0x1600>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0001> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0001>::VRString[] = "UL";
const char TagToType<0x0008,0x0001>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0005> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x0005>::VRString[] = "CS";
const char TagToType<0x0008,0x0005>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x0008> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM2_n };
static const char VMString[];
};
const char TagToType<0x0008,0x0008>::VRString[] = "CS";
const char TagToType<0x0008,0x0008>::VMString[] = "2-n";
template <> struct TagToType<0x0008,0x0010> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0010>::VRString[] = "CS";
const char TagToType<0x0008,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0012> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0012>::VRString[] = "DA";
const char TagToType<0x0008,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0013> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0013>::VRString[] = "TM";
const char TagToType<0x0008,0x0013>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0014> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0014>::VRString[] = "UI";
const char TagToType<0x0008,0x0014>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0016> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0016>::VRString[] = "UI";
const char TagToType<0x0008,0x0016>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0018> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0018>::VRString[] = "UI";
const char TagToType<0x0008,0x0018>::VMString[] = "1";
template <> struct TagToType<0x0008,0x001a> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x001a>::VRString[] = "UI";
const char TagToType<0x0008,0x001a>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x001b> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x001b>::VRString[] = "UI";
const char TagToType<0x0008,0x001b>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0020> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0020>::VRString[] = "DA";
const char TagToType<0x0008,0x0020>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0021> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0021>::VRString[] = "DA";
const char TagToType<0x0008,0x0021>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0022> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0022>::VRString[] = "DA";
const char TagToType<0x0008,0x0022>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0023> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0023>::VRString[] = "DA";
const char TagToType<0x0008,0x0023>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0024> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0024>::VRString[] = "DA";
const char TagToType<0x0008,0x0024>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0025> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0025>::VRString[] = "DA";
const char TagToType<0x0008,0x0025>::VMString[] = "1";
template <> struct TagToType<0x0008,0x002a> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x002a>::VRString[] = "DT";
const char TagToType<0x0008,0x002a>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0030> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0030>::VRString[] = "TM";
const char TagToType<0x0008,0x0030>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0031> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0031>::VRString[] = "TM";
const char TagToType<0x0008,0x0031>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0032> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0032>::VRString[] = "TM";
const char TagToType<0x0008,0x0032>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0033> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0033>::VRString[] = "TM";
const char TagToType<0x0008,0x0033>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0034> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0034>::VRString[] = "TM";
const char TagToType<0x0008,0x0034>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0035> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0035>::VRString[] = "TM";
const char TagToType<0x0008,0x0035>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0040> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0040>::VRString[] = "US";
const char TagToType<0x0008,0x0040>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0041> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0041>::VRString[] = "LO";
const char TagToType<0x0008,0x0041>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0042> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0042>::VRString[] = "CS";
const char TagToType<0x0008,0x0042>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0050> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0050>::VRString[] = "SH";
const char TagToType<0x0008,0x0050>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0052> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0052>::VRString[] = "CS";
const char TagToType<0x0008,0x0052>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0054> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x0054>::VRString[] = "AE";
const char TagToType<0x0008,0x0054>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x0056> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0056>::VRString[] = "CS";
const char TagToType<0x0008,0x0056>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0058> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x0058>::VRString[] = "UI";
const char TagToType<0x0008,0x0058>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x0060> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0060>::VRString[] = "CS";
const char TagToType<0x0008,0x0060>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0061> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x0061>::VRString[] = "CS";
const char TagToType<0x0008,0x0061>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x0062> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x0062>::VRString[] = "UI";
const char TagToType<0x0008,0x0062>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x0064> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0064>::VRString[] = "CS";
const char TagToType<0x0008,0x0064>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0068> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0068>::VRString[] = "CS";
const char TagToType<0x0008,0x0068>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0070> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0070>::VRString[] = "LO";
const char TagToType<0x0008,0x0070>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0080> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0080>::VRString[] = "LO";
const char TagToType<0x0008,0x0080>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0081> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0081>::VRString[] = "ST";
const char TagToType<0x0008,0x0081>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0082> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0082>::VRString[] = "SQ";
const char TagToType<0x0008,0x0082>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0090> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0090>::VRString[] = "PN";
const char TagToType<0x0008,0x0090>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0092> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0092>::VRString[] = "ST";
const char TagToType<0x0008,0x0092>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0094> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x0094>::VRString[] = "SH";
const char TagToType<0x0008,0x0094>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x0096> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0096>::VRString[] = "SQ";
const char TagToType<0x0008,0x0096>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0100> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0100>::VRString[] = "SH";
const char TagToType<0x0008,0x0100>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0102> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0102>::VRString[] = "SH";
const char TagToType<0x0008,0x0102>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0103> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0103>::VRString[] = "SH";
const char TagToType<0x0008,0x0103>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0104> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0104>::VRString[] = "LO";
const char TagToType<0x0008,0x0104>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0105> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0105>::VRString[] = "CS";
const char TagToType<0x0008,0x0105>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0106> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0106>::VRString[] = "DT";
const char TagToType<0x0008,0x0106>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0107> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0107>::VRString[] = "DT";
const char TagToType<0x0008,0x0107>::VMString[] = "1";
template <> struct TagToType<0x0008,0x010b> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x010b>::VRString[] = "CS";
const char TagToType<0x0008,0x010b>::VMString[] = "1";
template <> struct TagToType<0x0008,0x010c> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x010c>::VRString[] = "UI";
const char TagToType<0x0008,0x010c>::VMString[] = "1";
template <> struct TagToType<0x0008,0x010d> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x010d>::VRString[] = "UI";
const char TagToType<0x0008,0x010d>::VMString[] = "1";
template <> struct TagToType<0x0008,0x010f> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x010f>::VRString[] = "CS";
const char TagToType<0x0008,0x010f>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0110> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0110>::VRString[] = "SQ";
const char TagToType<0x0008,0x0110>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0112> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0112>::VRString[] = "LO";
const char TagToType<0x0008,0x0112>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0114> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0114>::VRString[] = "ST";
const char TagToType<0x0008,0x0114>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0115> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0115>::VRString[] = "ST";
const char TagToType<0x0008,0x0115>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0116> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0116>::VRString[] = "ST";
const char TagToType<0x0008,0x0116>::VMString[] = "1";
template <> struct TagToType<0x0008,0x0201> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x0201>::VRString[] = "SH";
const char TagToType<0x0008,0x0201>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1000> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1000>::VRString[] = "AE";
const char TagToType<0x0008,0x1000>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1010> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1010>::VRString[] = "SH";
const char TagToType<0x0008,0x1010>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1030> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1030>::VRString[] = "LO";
const char TagToType<0x0008,0x1030>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1032> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1032>::VRString[] = "SQ";
const char TagToType<0x0008,0x1032>::VMString[] = "1";
template <> struct TagToType<0x0008,0x103e> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x103e>::VRString[] = "LO";
const char TagToType<0x0008,0x103e>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1040> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1040>::VRString[] = "LO";
const char TagToType<0x0008,0x1040>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1048> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x1048>::VRString[] = "PN";
const char TagToType<0x0008,0x1048>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x1049> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1049>::VRString[] = "SQ";
const char TagToType<0x0008,0x1049>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1050> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x1050>::VRString[] = "PN";
const char TagToType<0x0008,0x1050>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x1052> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1052>::VRString[] = "SQ";
const char TagToType<0x0008,0x1052>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1060> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x1060>::VRString[] = "PN";
const char TagToType<0x0008,0x1060>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x1062> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1062>::VRString[] = "SQ";
const char TagToType<0x0008,0x1062>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1070> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x1070>::VRString[] = "PN";
const char TagToType<0x0008,0x1070>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x1072> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1072>::VRString[] = "SQ";
const char TagToType<0x0008,0x1072>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1080> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x1080>::VRString[] = "LO";
const char TagToType<0x0008,0x1080>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x1084> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1084>::VRString[] = "SQ";
const char TagToType<0x0008,0x1084>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1090> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1090>::VRString[] = "LO";
const char TagToType<0x0008,0x1090>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1100> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1100>::VRString[] = "SQ";
const char TagToType<0x0008,0x1100>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1110> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1110>::VRString[] = "SQ";
const char TagToType<0x0008,0x1110>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1111> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1111>::VRString[] = "SQ";
const char TagToType<0x0008,0x1111>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1115> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1115>::VRString[] = "SQ";
const char TagToType<0x0008,0x1115>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1120> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1120>::VRString[] = "SQ";
const char TagToType<0x0008,0x1120>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1125> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1125>::VRString[] = "SQ";
const char TagToType<0x0008,0x1125>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1130> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1130>::VRString[] = "SQ";
const char TagToType<0x0008,0x1130>::VMString[] = "1";
template <> struct TagToType<0x0008,0x113a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x113a>::VRString[] = "SQ";
const char TagToType<0x0008,0x113a>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1140> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1140>::VRString[] = "SQ";
const char TagToType<0x0008,0x1140>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1145> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1145>::VRString[] = "SQ";
const char TagToType<0x0008,0x1145>::VMString[] = "1";
template <> struct TagToType<0x0008,0x114a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x114a>::VRString[] = "SQ";
const char TagToType<0x0008,0x114a>::VMString[] = "1";
template <> struct TagToType<0x0008,0x114b> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x114b>::VRString[] = "SQ";
const char TagToType<0x0008,0x114b>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1150> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1150>::VRString[] = "UI";
const char TagToType<0x0008,0x1150>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1155> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1155>::VRString[] = "UI";
const char TagToType<0x0008,0x1155>::VMString[] = "1";
template <> struct TagToType<0x0008,0x115a> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x115a>::VRString[] = "UI";
const char TagToType<0x0008,0x115a>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x1160> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x1160>::VRString[] = "IS";
const char TagToType<0x0008,0x1160>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x1195> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1195>::VRString[] = "UI";
const char TagToType<0x0008,0x1195>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1197> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1197>::VRString[] = "US";
const char TagToType<0x0008,0x1197>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1198> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1198>::VRString[] = "SQ";
const char TagToType<0x0008,0x1198>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1199> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1199>::VRString[] = "SQ";
const char TagToType<0x0008,0x1199>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1200> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1200>::VRString[] = "SQ";
const char TagToType<0x0008,0x1200>::VMString[] = "1";
template <> struct TagToType<0x0008,0x1250> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x1250>::VRString[] = "SQ";
const char TagToType<0x0008,0x1250>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2110> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2110>::VRString[] = "CS";
const char TagToType<0x0008,0x2110>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2111> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2111>::VRString[] = "ST";
const char TagToType<0x0008,0x2111>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2112> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2112>::VRString[] = "SQ";
const char TagToType<0x0008,0x2112>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2120> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2120>::VRString[] = "SH";
const char TagToType<0x0008,0x2120>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2122> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2122>::VRString[] = "IS";
const char TagToType<0x0008,0x2122>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2124> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2124>::VRString[] = "IS";
const char TagToType<0x0008,0x2124>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2127> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2127>::VRString[] = "SH";
const char TagToType<0x0008,0x2127>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2128> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2128>::VRString[] = "IS";
const char TagToType<0x0008,0x2128>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2129> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2129>::VRString[] = "IS";
const char TagToType<0x0008,0x2129>::VMString[] = "1";
template <> struct TagToType<0x0008,0x212a> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x212a>::VRString[] = "IS";
const char TagToType<0x0008,0x212a>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2130> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x2130>::VRString[] = "DS";
const char TagToType<0x0008,0x2130>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x2132> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0008,0x2132>::VRString[] = "LO";
const char TagToType<0x0008,0x2132>::VMString[] = "1-n";
template <> struct TagToType<0x0008,0x2142> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2142>::VRString[] = "IS";
const char TagToType<0x0008,0x2142>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2143> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2143>::VRString[] = "IS";
const char TagToType<0x0008,0x2143>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2144> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2144>::VRString[] = "IS";
const char TagToType<0x0008,0x2144>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2200> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2200>::VRString[] = "CS";
const char TagToType<0x0008,0x2200>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2204> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2204>::VRString[] = "CS";
const char TagToType<0x0008,0x2204>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2208> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2208>::VRString[] = "CS";
const char TagToType<0x0008,0x2208>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2218> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2218>::VRString[] = "SQ";
const char TagToType<0x0008,0x2218>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2220> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2220>::VRString[] = "SQ";
const char TagToType<0x0008,0x2220>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2228> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2228>::VRString[] = "SQ";
const char TagToType<0x0008,0x2228>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2229> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2229>::VRString[] = "SQ";
const char TagToType<0x0008,0x2229>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2230> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2230>::VRString[] = "SQ";
const char TagToType<0x0008,0x2230>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2240> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2240>::VRString[] = "SQ";
const char TagToType<0x0008,0x2240>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2242> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2242>::VRString[] = "SQ";
const char TagToType<0x0008,0x2242>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2244> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2244>::VRString[] = "SQ";
const char TagToType<0x0008,0x2244>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2246> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2246>::VRString[] = "SQ";
const char TagToType<0x0008,0x2246>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2251> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2251>::VRString[] = "SQ";
const char TagToType<0x0008,0x2251>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2253> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2253>::VRString[] = "SQ";
const char TagToType<0x0008,0x2253>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2255> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2255>::VRString[] = "SQ";
const char TagToType<0x0008,0x2255>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2256> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2256>::VRString[] = "ST";
const char TagToType<0x0008,0x2256>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2257> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2257>::VRString[] = "SQ";
const char TagToType<0x0008,0x2257>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2258> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2258>::VRString[] = "ST";
const char TagToType<0x0008,0x2258>::VMString[] = "1";
template <> struct TagToType<0x0008,0x2259> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x2259>::VRString[] = "SQ";
const char TagToType<0x0008,0x2259>::VMString[] = "1";
template <> struct TagToType<0x0008,0x225a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x225a>::VRString[] = "SQ";
const char TagToType<0x0008,0x225a>::VMString[] = "1";
template <> struct TagToType<0x0008,0x225c> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x225c>::VRString[] = "SQ";
const char TagToType<0x0008,0x225c>::VMString[] = "1";
template <> struct TagToType<0x0008,0x3001> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x3001>::VRString[] = "SQ";
const char TagToType<0x0008,0x3001>::VMString[] = "1";
template <> struct TagToType<0x0008,0x3010> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x3010>::VRString[] = "UI";
const char TagToType<0x0008,0x3010>::VMString[] = "1";
template <> struct TagToType<0x0008,0x4000> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x4000>::VRString[] = "LT";
const char TagToType<0x0008,0x4000>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9007> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM4 };
static const char VMString[];
};
const char TagToType<0x0008,0x9007>::VRString[] = "CS";
const char TagToType<0x0008,0x9007>::VMString[] = "4";
template <> struct TagToType<0x0008,0x9092> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9092>::VRString[] = "SQ";
const char TagToType<0x0008,0x9092>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9121> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9121>::VRString[] = "SQ";
const char TagToType<0x0008,0x9121>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9123> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9123>::VRString[] = "UI";
const char TagToType<0x0008,0x9123>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9124> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9124>::VRString[] = "SQ";
const char TagToType<0x0008,0x9124>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9154> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9154>::VRString[] = "SQ";
const char TagToType<0x0008,0x9154>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9205> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9205>::VRString[] = "CS";
const char TagToType<0x0008,0x9205>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9206> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9206>::VRString[] = "CS";
const char TagToType<0x0008,0x9206>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9207> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9207>::VRString[] = "CS";
const char TagToType<0x0008,0x9207>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9208> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9208>::VRString[] = "CS";
const char TagToType<0x0008,0x9208>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9209> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9209>::VRString[] = "CS";
const char TagToType<0x0008,0x9209>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9215> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9215>::VRString[] = "SQ";
const char TagToType<0x0008,0x9215>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9237> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9237>::VRString[] = "SQ";
const char TagToType<0x0008,0x9237>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9410> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9410>::VRString[] = "SQ";
const char TagToType<0x0008,0x9410>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9458> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9458>::VRString[] = "SQ";
const char TagToType<0x0008,0x9458>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9459> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9459>::VRString[] = "FL";
const char TagToType<0x0008,0x9459>::VMString[] = "1";
template <> struct TagToType<0x0008,0x9460> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0008,0x9460>::VRString[] = "CS";
const char TagToType<0x0008,0x9460>::VMString[] = "1";
template <> struct TagToType<0x0010,0x0010> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x0010>::VRString[] = "PN";
const char TagToType<0x0010,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0010,0x0020> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x0020>::VRString[] = "LO";
const char TagToType<0x0010,0x0020>::VMString[] = "1";
template <> struct TagToType<0x0010,0x0021> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x0021>::VRString[] = "LO";
const char TagToType<0x0010,0x0021>::VMString[] = "1";
template <> struct TagToType<0x0010,0x0022> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x0022>::VRString[] = "CS";
const char TagToType<0x0010,0x0022>::VMString[] = "1";
template <> struct TagToType<0x0010,0x0030> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x0030>::VRString[] = "DA";
const char TagToType<0x0010,0x0030>::VMString[] = "1";
template <> struct TagToType<0x0010,0x0032> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x0032>::VRString[] = "TM";
const char TagToType<0x0010,0x0032>::VMString[] = "1";
template <> struct TagToType<0x0010,0x0040> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x0040>::VRString[] = "CS";
const char TagToType<0x0010,0x0040>::VMString[] = "1";
template <> struct TagToType<0x0010,0x0050> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x0050>::VRString[] = "SQ";
const char TagToType<0x0010,0x0050>::VMString[] = "1";
template <> struct TagToType<0x0010,0x0101> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x0101>::VRString[] = "SQ";
const char TagToType<0x0010,0x0101>::VMString[] = "1";
template <> struct TagToType<0x0010,0x0102> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x0102>::VRString[] = "SQ";
const char TagToType<0x0010,0x0102>::VMString[] = "1";
template <> struct TagToType<0x0010,0x1000> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0010,0x1000>::VRString[] = "LO";
const char TagToType<0x0010,0x1000>::VMString[] = "1-n";
template <> struct TagToType<0x0010,0x1001> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0010,0x1001>::VRString[] = "PN";
const char TagToType<0x0010,0x1001>::VMString[] = "1-n";
template <> struct TagToType<0x0010,0x1002> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x1002>::VRString[] = "SQ";
const char TagToType<0x0010,0x1002>::VMString[] = "1";
template <> struct TagToType<0x0010,0x1005> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x1005>::VRString[] = "PN";
const char TagToType<0x0010,0x1005>::VMString[] = "1";
template <> struct TagToType<0x0010,0x1010> {
static const char VRString[];
typedef VRToType<VR::AS>::Type Type;
enum { VRType = VR::AS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x1010>::VRString[] = "AS";
const char TagToType<0x0010,0x1010>::VMString[] = "1";
template <> struct TagToType<0x0010,0x1020> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x1020>::VRString[] = "DS";
const char TagToType<0x0010,0x1020>::VMString[] = "1";
template <> struct TagToType<0x0010,0x1030> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x1030>::VRString[] = "DS";
const char TagToType<0x0010,0x1030>::VMString[] = "1";
template <> struct TagToType<0x0010,0x1040> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x1040>::VRString[] = "LO";
const char TagToType<0x0010,0x1040>::VMString[] = "1";
template <> struct TagToType<0x0010,0x1050> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0010,0x1050>::VRString[] = "LO";
const char TagToType<0x0010,0x1050>::VMString[] = "1-n";
template <> struct TagToType<0x0010,0x1060> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x1060>::VRString[] = "PN";
const char TagToType<0x0010,0x1060>::VMString[] = "1";
template <> struct TagToType<0x0010,0x1080> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x1080>::VRString[] = "LO";
const char TagToType<0x0010,0x1080>::VMString[] = "1";
template <> struct TagToType<0x0010,0x1081> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x1081>::VRString[] = "LO";
const char TagToType<0x0010,0x1081>::VMString[] = "1";
template <> struct TagToType<0x0010,0x1090> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x1090>::VRString[] = "LO";
const char TagToType<0x0010,0x1090>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2000> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0010,0x2000>::VRString[] = "LO";
const char TagToType<0x0010,0x2000>::VMString[] = "1-n";
template <> struct TagToType<0x0010,0x2110> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0010,0x2110>::VRString[] = "LO";
const char TagToType<0x0010,0x2110>::VMString[] = "1-n";
template <> struct TagToType<0x0010,0x2150> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2150>::VRString[] = "LO";
const char TagToType<0x0010,0x2150>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2152> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2152>::VRString[] = "LO";
const char TagToType<0x0010,0x2152>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2154> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0010,0x2154>::VRString[] = "SH";
const char TagToType<0x0010,0x2154>::VMString[] = "1-n";
template <> struct TagToType<0x0010,0x2160> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2160>::VRString[] = "SH";
const char TagToType<0x0010,0x2160>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2180> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2180>::VRString[] = "SH";
const char TagToType<0x0010,0x2180>::VMString[] = "1";
template <> struct TagToType<0x0010,0x21a0> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x21a0>::VRString[] = "CS";
const char TagToType<0x0010,0x21a0>::VMString[] = "1";
template <> struct TagToType<0x0010,0x21b0> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x21b0>::VRString[] = "LT";
const char TagToType<0x0010,0x21b0>::VMString[] = "1";
template <> struct TagToType<0x0010,0x21c0> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x21c0>::VRString[] = "US";
const char TagToType<0x0010,0x21c0>::VMString[] = "1";
template <> struct TagToType<0x0010,0x21d0> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x21d0>::VRString[] = "DA";
const char TagToType<0x0010,0x21d0>::VMString[] = "1";
template <> struct TagToType<0x0010,0x21f0> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x21f0>::VRString[] = "LO";
const char TagToType<0x0010,0x21f0>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2201> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2201>::VRString[] = "LO";
const char TagToType<0x0010,0x2201>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2202> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2202>::VRString[] = "SQ";
const char TagToType<0x0010,0x2202>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2203> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2203>::VRString[] = "CS";
const char TagToType<0x0010,0x2203>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2292> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2292>::VRString[] = "LO";
const char TagToType<0x0010,0x2292>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2293> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2293>::VRString[] = "SQ";
const char TagToType<0x0010,0x2293>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2294> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2294>::VRString[] = "SQ";
const char TagToType<0x0010,0x2294>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2295> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2295>::VRString[] = "LO";
const char TagToType<0x0010,0x2295>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2296> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2296>::VRString[] = "SQ";
const char TagToType<0x0010,0x2296>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2297> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2297>::VRString[] = "PN";
const char TagToType<0x0010,0x2297>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2298> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2298>::VRString[] = "CS";
const char TagToType<0x0010,0x2298>::VMString[] = "1";
template <> struct TagToType<0x0010,0x2299> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x2299>::VRString[] = "LO";
const char TagToType<0x0010,0x2299>::VMString[] = "1";
template <> struct TagToType<0x0010,0x4000> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x4000>::VRString[] = "LT";
const char TagToType<0x0010,0x4000>::VMString[] = "1";
template <> struct TagToType<0x0010,0x9431> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0010,0x9431>::VRString[] = "FL";
const char TagToType<0x0010,0x9431>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0010> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0010>::VRString[] = "LO";
const char TagToType<0x0012,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0020> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0020>::VRString[] = "LO";
const char TagToType<0x0012,0x0020>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0021> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0021>::VRString[] = "LO";
const char TagToType<0x0012,0x0021>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0030> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0030>::VRString[] = "LO";
const char TagToType<0x0012,0x0030>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0031> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0031>::VRString[] = "LO";
const char TagToType<0x0012,0x0031>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0040> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0040>::VRString[] = "LO";
const char TagToType<0x0012,0x0040>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0042> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0042>::VRString[] = "LO";
const char TagToType<0x0012,0x0042>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0050> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0050>::VRString[] = "LO";
const char TagToType<0x0012,0x0050>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0051> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0051>::VRString[] = "ST";
const char TagToType<0x0012,0x0051>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0060> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0060>::VRString[] = "LO";
const char TagToType<0x0012,0x0060>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0062> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0062>::VRString[] = "CS";
const char TagToType<0x0012,0x0062>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0063> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0012,0x0063>::VRString[] = "LO";
const char TagToType<0x0012,0x0063>::VMString[] = "1-n";
template <> struct TagToType<0x0012,0x0064> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0064>::VRString[] = "SQ";
const char TagToType<0x0012,0x0064>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0071> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0071>::VRString[] = "LO";
const char TagToType<0x0012,0x0071>::VMString[] = "1";
template <> struct TagToType<0x0012,0x0072> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0012,0x0072>::VRString[] = "LO";
const char TagToType<0x0012,0x0072>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0010> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0010>::VRString[] = "LO";
const char TagToType<0x0018,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0012> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0012>::VRString[] = "SQ";
const char TagToType<0x0018,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0014> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0014>::VRString[] = "SQ";
const char TagToType<0x0018,0x0014>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0015> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0015>::VRString[] = "CS";
const char TagToType<0x0018,0x0015>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x0020>::VRString[] = "CS";
const char TagToType<0x0018,0x0020>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x0021> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x0021>::VRString[] = "CS";
const char TagToType<0x0018,0x0021>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x0022> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x0022>::VRString[] = "CS";
const char TagToType<0x0018,0x0022>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x0023> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0023>::VRString[] = "CS";
const char TagToType<0x0018,0x0023>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0024> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0024>::VRString[] = "SH";
const char TagToType<0x0018,0x0024>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0025> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0025>::VRString[] = "CS";
const char TagToType<0x0018,0x0025>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0026> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0026>::VRString[] = "SQ";
const char TagToType<0x0018,0x0026>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0027> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0027>::VRString[] = "TM";
const char TagToType<0x0018,0x0027>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0028> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0028>::VRString[] = "DS";
const char TagToType<0x0018,0x0028>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0029> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0029>::VRString[] = "SQ";
const char TagToType<0x0018,0x0029>::VMString[] = "1";
template <> struct TagToType<0x0018,0x002a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x002a>::VRString[] = "SQ";
const char TagToType<0x0018,0x002a>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0030> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x0030>::VRString[] = "LO";
const char TagToType<0x0018,0x0030>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x0031> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0031>::VRString[] = "LO";
const char TagToType<0x0018,0x0031>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0032> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0032>::VRString[] = "DS";
const char TagToType<0x0018,0x0032>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0033> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x0033>::VRString[] = "DS";
const char TagToType<0x0018,0x0033>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x0034> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0034>::VRString[] = "LO";
const char TagToType<0x0018,0x0034>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0035> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0035>::VRString[] = "TM";
const char TagToType<0x0018,0x0035>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0036> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0036>::VRString[] = "SQ";
const char TagToType<0x0018,0x0036>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0037> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0037>::VRString[] = "CS";
const char TagToType<0x0018,0x0037>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0038> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0038>::VRString[] = "CS";
const char TagToType<0x0018,0x0038>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0039> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0039>::VRString[] = "CS";
const char TagToType<0x0018,0x0039>::VMString[] = "1";
template <> struct TagToType<0x0018,0x003a> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x003a>::VRString[] = "ST";
const char TagToType<0x0018,0x003a>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0040> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0040>::VRString[] = "IS";
const char TagToType<0x0018,0x0040>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0050> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0050>::VRString[] = "DS";
const char TagToType<0x0018,0x0050>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0060> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0060>::VRString[] = "DS";
const char TagToType<0x0018,0x0060>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0070> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0070>::VRString[] = "IS";
const char TagToType<0x0018,0x0070>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0071> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0071>::VRString[] = "CS";
const char TagToType<0x0018,0x0071>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0072> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0072>::VRString[] = "DS";
const char TagToType<0x0018,0x0072>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0073> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0073>::VRString[] = "CS";
const char TagToType<0x0018,0x0073>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0074> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0074>::VRString[] = "IS";
const char TagToType<0x0018,0x0074>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0075> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0075>::VRString[] = "IS";
const char TagToType<0x0018,0x0075>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0080> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0080>::VRString[] = "DS";
const char TagToType<0x0018,0x0080>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0081> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0081>::VRString[] = "DS";
const char TagToType<0x0018,0x0081>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0082> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0082>::VRString[] = "DS";
const char TagToType<0x0018,0x0082>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0083> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0083>::VRString[] = "DS";
const char TagToType<0x0018,0x0083>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0084> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0084>::VRString[] = "DS";
const char TagToType<0x0018,0x0084>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0085> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0085>::VRString[] = "SH";
const char TagToType<0x0018,0x0085>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0086> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x0086>::VRString[] = "IS";
const char TagToType<0x0018,0x0086>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x0087> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0087>::VRString[] = "DS";
const char TagToType<0x0018,0x0087>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0088> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0088>::VRString[] = "DS";
const char TagToType<0x0018,0x0088>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0089> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0089>::VRString[] = "IS";
const char TagToType<0x0018,0x0089>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0090> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0090>::VRString[] = "DS";
const char TagToType<0x0018,0x0090>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0091> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0091>::VRString[] = "IS";
const char TagToType<0x0018,0x0091>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0093> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0093>::VRString[] = "DS";
const char TagToType<0x0018,0x0093>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0094> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0094>::VRString[] = "DS";
const char TagToType<0x0018,0x0094>::VMString[] = "1";
template <> struct TagToType<0x0018,0x0095> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x0095>::VRString[] = "DS";
const char TagToType<0x0018,0x0095>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1000> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1000>::VRString[] = "LO";
const char TagToType<0x0018,0x1000>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1002> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1002>::VRString[] = "UI";
const char TagToType<0x0018,0x1002>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1003> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1003>::VRString[] = "LO";
const char TagToType<0x0018,0x1003>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1004> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1004>::VRString[] = "LO";
const char TagToType<0x0018,0x1004>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1005> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1005>::VRString[] = "LO";
const char TagToType<0x0018,0x1005>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1006> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1006>::VRString[] = "LO";
const char TagToType<0x0018,0x1006>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1007> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1007>::VRString[] = "LO";
const char TagToType<0x0018,0x1007>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1008> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1008>::VRString[] = "LO";
const char TagToType<0x0018,0x1008>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1010> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1010>::VRString[] = "LO";
const char TagToType<0x0018,0x1010>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1011> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1011>::VRString[] = "LO";
const char TagToType<0x0018,0x1011>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1012> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1012>::VRString[] = "DA";
const char TagToType<0x0018,0x1012>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1014> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1014>::VRString[] = "TM";
const char TagToType<0x0018,0x1014>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1016> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1016>::VRString[] = "LO";
const char TagToType<0x0018,0x1016>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1017> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1017>::VRString[] = "LO";
const char TagToType<0x0018,0x1017>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1018> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1018>::VRString[] = "LO";
const char TagToType<0x0018,0x1018>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1019> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1019>::VRString[] = "LO";
const char TagToType<0x0018,0x1019>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x101a> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x101a>::VRString[] = "LO";
const char TagToType<0x0018,0x101a>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x101b> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x101b>::VRString[] = "LO";
const char TagToType<0x0018,0x101b>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1020> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1020>::VRString[] = "LO";
const char TagToType<0x0018,0x1020>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1022> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1022>::VRString[] = "SH";
const char TagToType<0x0018,0x1022>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1023> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1023>::VRString[] = "LO";
const char TagToType<0x0018,0x1023>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1030> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1030>::VRString[] = "LO";
const char TagToType<0x0018,0x1030>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1040> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1040>::VRString[] = "LO";
const char TagToType<0x0018,0x1040>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1041> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1041>::VRString[] = "DS";
const char TagToType<0x0018,0x1041>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1042> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1042>::VRString[] = "TM";
const char TagToType<0x0018,0x1042>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1043> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1043>::VRString[] = "TM";
const char TagToType<0x0018,0x1043>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1044> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1044>::VRString[] = "DS";
const char TagToType<0x0018,0x1044>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1045> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1045>::VRString[] = "IS";
const char TagToType<0x0018,0x1045>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1046> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1046>::VRString[] = "DS";
const char TagToType<0x0018,0x1046>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1047> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1047>::VRString[] = "DS";
const char TagToType<0x0018,0x1047>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1048> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1048>::VRString[] = "CS";
const char TagToType<0x0018,0x1048>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1049> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1049>::VRString[] = "DS";
const char TagToType<0x0018,0x1049>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1050> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1050>::VRString[] = "DS";
const char TagToType<0x0018,0x1050>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1060> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1060>::VRString[] = "DS";
const char TagToType<0x0018,0x1060>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1061> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1061>::VRString[] = "LO";
const char TagToType<0x0018,0x1061>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1062> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1062>::VRString[] = "IS";
const char TagToType<0x0018,0x1062>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1063> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1063>::VRString[] = "DS";
const char TagToType<0x0018,0x1063>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1064> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1064>::VRString[] = "LO";
const char TagToType<0x0018,0x1064>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1065> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1065>::VRString[] = "DS";
const char TagToType<0x0018,0x1065>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1066> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1066>::VRString[] = "DS";
const char TagToType<0x0018,0x1066>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1067> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1067>::VRString[] = "DS";
const char TagToType<0x0018,0x1067>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1068> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1068>::VRString[] = "DS";
const char TagToType<0x0018,0x1068>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1069> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1069>::VRString[] = "DS";
const char TagToType<0x0018,0x1069>::VMString[] = "1";
template <> struct TagToType<0x0018,0x106a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x106a>::VRString[] = "CS";
const char TagToType<0x0018,0x106a>::VMString[] = "1";
template <> struct TagToType<0x0018,0x106c> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x106c>::VRString[] = "US";
const char TagToType<0x0018,0x106c>::VMString[] = "2";
template <> struct TagToType<0x0018,0x106e> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x106e>::VRString[] = "UL";
const char TagToType<0x0018,0x106e>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1070> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1070>::VRString[] = "LO";
const char TagToType<0x0018,0x1070>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1071> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1071>::VRString[] = "DS";
const char TagToType<0x0018,0x1071>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1072> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1072>::VRString[] = "TM";
const char TagToType<0x0018,0x1072>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1073> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1073>::VRString[] = "TM";
const char TagToType<0x0018,0x1073>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1074> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1074>::VRString[] = "DS";
const char TagToType<0x0018,0x1074>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1075> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1075>::VRString[] = "DS";
const char TagToType<0x0018,0x1075>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1076> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1076>::VRString[] = "DS";
const char TagToType<0x0018,0x1076>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1077> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1077>::VRString[] = "DS";
const char TagToType<0x0018,0x1077>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1078> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1078>::VRString[] = "DT";
const char TagToType<0x0018,0x1078>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1079> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1079>::VRString[] = "DT";
const char TagToType<0x0018,0x1079>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1080> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1080>::VRString[] = "CS";
const char TagToType<0x0018,0x1080>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1081> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1081>::VRString[] = "IS";
const char TagToType<0x0018,0x1081>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1082> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1082>::VRString[] = "IS";
const char TagToType<0x0018,0x1082>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1083> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1083>::VRString[] = "IS";
const char TagToType<0x0018,0x1083>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1084> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1084>::VRString[] = "IS";
const char TagToType<0x0018,0x1084>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1085> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1085>::VRString[] = "LO";
const char TagToType<0x0018,0x1085>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1086> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1086>::VRString[] = "IS";
const char TagToType<0x0018,0x1086>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1088> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1088>::VRString[] = "IS";
const char TagToType<0x0018,0x1088>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1090> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1090>::VRString[] = "IS";
const char TagToType<0x0018,0x1090>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1094> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1094>::VRString[] = "IS";
const char TagToType<0x0018,0x1094>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1100> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1100>::VRString[] = "DS";
const char TagToType<0x0018,0x1100>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1110> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1110>::VRString[] = "DS";
const char TagToType<0x0018,0x1110>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1111> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1111>::VRString[] = "DS";
const char TagToType<0x0018,0x1111>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1114> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1114>::VRString[] = "DS";
const char TagToType<0x0018,0x1114>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1120> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1120>::VRString[] = "DS";
const char TagToType<0x0018,0x1120>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1121> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1121>::VRString[] = "DS";
const char TagToType<0x0018,0x1121>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1130> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1130>::VRString[] = "DS";
const char TagToType<0x0018,0x1130>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1131> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1131>::VRString[] = "DS";
const char TagToType<0x0018,0x1131>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1134> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1134>::VRString[] = "CS";
const char TagToType<0x0018,0x1134>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1135> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1135>::VRString[] = "DS";
const char TagToType<0x0018,0x1135>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1136> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1136>::VRString[] = "DS";
const char TagToType<0x0018,0x1136>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1137> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1137>::VRString[] = "DS";
const char TagToType<0x0018,0x1137>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1138> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1138>::VRString[] = "DS";
const char TagToType<0x0018,0x1138>::VMString[] = "1";
template <> struct TagToType<0x0018,0x113a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x113a>::VRString[] = "CS";
const char TagToType<0x0018,0x113a>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1140> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1140>::VRString[] = "CS";
const char TagToType<0x0018,0x1140>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1141> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1141>::VRString[] = "DS";
const char TagToType<0x0018,0x1141>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1142> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1142>::VRString[] = "DS";
const char TagToType<0x0018,0x1142>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1143> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1143>::VRString[] = "DS";
const char TagToType<0x0018,0x1143>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1144> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1144>::VRString[] = "DS";
const char TagToType<0x0018,0x1144>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1145> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1145>::VRString[] = "DS";
const char TagToType<0x0018,0x1145>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1146> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1146>::VRString[] = "DS";
const char TagToType<0x0018,0x1146>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1147> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1147>::VRString[] = "CS";
const char TagToType<0x0018,0x1147>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1149> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x1149>::VRString[] = "IS";
const char TagToType<0x0018,0x1149>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x1150> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1150>::VRString[] = "IS";
const char TagToType<0x0018,0x1150>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1151> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1151>::VRString[] = "IS";
const char TagToType<0x0018,0x1151>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1152> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1152>::VRString[] = "IS";
const char TagToType<0x0018,0x1152>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1153> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1153>::VRString[] = "IS";
const char TagToType<0x0018,0x1153>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1154> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1154>::VRString[] = "DS";
const char TagToType<0x0018,0x1154>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1155> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1155>::VRString[] = "CS";
const char TagToType<0x0018,0x1155>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1156> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1156>::VRString[] = "CS";
const char TagToType<0x0018,0x1156>::VMString[] = "1";
template <> struct TagToType<0x0018,0x115a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x115a>::VRString[] = "CS";
const char TagToType<0x0018,0x115a>::VMString[] = "1";
template <> struct TagToType<0x0018,0x115e> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x115e>::VRString[] = "DS";
const char TagToType<0x0018,0x115e>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1160> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1160>::VRString[] = "SH";
const char TagToType<0x0018,0x1160>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1161> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1161>::VRString[] = "LO";
const char TagToType<0x0018,0x1161>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1162> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1162>::VRString[] = "DS";
const char TagToType<0x0018,0x1162>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1164> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x1164>::VRString[] = "DS";
const char TagToType<0x0018,0x1164>::VMString[] = "2";
template <> struct TagToType<0x0018,0x1166> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1166>::VRString[] = "CS";
const char TagToType<0x0018,0x1166>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1170> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1170>::VRString[] = "IS";
const char TagToType<0x0018,0x1170>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1180> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1180>::VRString[] = "SH";
const char TagToType<0x0018,0x1180>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1181> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1181>::VRString[] = "CS";
const char TagToType<0x0018,0x1181>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1182> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x1182>::VRString[] = "IS";
const char TagToType<0x0018,0x1182>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x1183> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x1183>::VRString[] = "DS";
const char TagToType<0x0018,0x1183>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x1184> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x1184>::VRString[] = "DS";
const char TagToType<0x0018,0x1184>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x1190> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1190>::VRString[] = "DS";
const char TagToType<0x0018,0x1190>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1191> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1191>::VRString[] = "CS";
const char TagToType<0x0018,0x1191>::VMString[] = "1";
template <> struct TagToType<0x0018,0x11a0> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x11a0>::VRString[] = "DS";
const char TagToType<0x0018,0x11a0>::VMString[] = "1";
template <> struct TagToType<0x0018,0x11a2> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x11a2>::VRString[] = "DS";
const char TagToType<0x0018,0x11a2>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1200> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1200>::VRString[] = "DA";
const char TagToType<0x0018,0x1200>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1201> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1201>::VRString[] = "TM";
const char TagToType<0x0018,0x1201>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1210> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1210>::VRString[] = "SH";
const char TagToType<0x0018,0x1210>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1240> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1240>::VRString[] = "IS";
const char TagToType<0x0018,0x1240>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1242> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1242>::VRString[] = "IS";
const char TagToType<0x0018,0x1242>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1243> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1243>::VRString[] = "IS";
const char TagToType<0x0018,0x1243>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1244> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1244>::VRString[] = "US";
const char TagToType<0x0018,0x1244>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1250> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1250>::VRString[] = "SH";
const char TagToType<0x0018,0x1250>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1251> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1251>::VRString[] = "SH";
const char TagToType<0x0018,0x1251>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1260> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1260>::VRString[] = "SH";
const char TagToType<0x0018,0x1260>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1261> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1261>::VRString[] = "LO";
const char TagToType<0x0018,0x1261>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1300> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1300>::VRString[] = "DS";
const char TagToType<0x0018,0x1300>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1301> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1301>::VRString[] = "CS";
const char TagToType<0x0018,0x1301>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1302> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1302>::VRString[] = "IS";
const char TagToType<0x0018,0x1302>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1310> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM4 };
static const char VMString[];
};
const char TagToType<0x0018,0x1310>::VRString[] = "US";
const char TagToType<0x0018,0x1310>::VMString[] = "4";
template <> struct TagToType<0x0018,0x1312> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1312>::VRString[] = "CS";
const char TagToType<0x0018,0x1312>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1314> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1314>::VRString[] = "DS";
const char TagToType<0x0018,0x1314>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1315> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1315>::VRString[] = "CS";
const char TagToType<0x0018,0x1315>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1316> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1316>::VRString[] = "DS";
const char TagToType<0x0018,0x1316>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1318> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1318>::VRString[] = "DS";
const char TagToType<0x0018,0x1318>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1400> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1400>::VRString[] = "LO";
const char TagToType<0x0018,0x1400>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1401> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1401>::VRString[] = "LO";
const char TagToType<0x0018,0x1401>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1402> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1402>::VRString[] = "CS";
const char TagToType<0x0018,0x1402>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1403> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1403>::VRString[] = "CS";
const char TagToType<0x0018,0x1403>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1404> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1404>::VRString[] = "US";
const char TagToType<0x0018,0x1404>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1405> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1405>::VRString[] = "IS";
const char TagToType<0x0018,0x1405>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1450> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1450>::VRString[] = "DS";
const char TagToType<0x0018,0x1450>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1460> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1460>::VRString[] = "DS";
const char TagToType<0x0018,0x1460>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1470> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1470>::VRString[] = "DS";
const char TagToType<0x0018,0x1470>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1480> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1480>::VRString[] = "DS";
const char TagToType<0x0018,0x1480>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1490> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1490>::VRString[] = "CS";
const char TagToType<0x0018,0x1490>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1491> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1491>::VRString[] = "CS";
const char TagToType<0x0018,0x1491>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1495> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1495>::VRString[] = "IS";
const char TagToType<0x0018,0x1495>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1500> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1500>::VRString[] = "CS";
const char TagToType<0x0018,0x1500>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1508> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1508>::VRString[] = "CS";
const char TagToType<0x0018,0x1508>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1510> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1510>::VRString[] = "DS";
const char TagToType<0x0018,0x1510>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1511> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1511>::VRString[] = "DS";
const char TagToType<0x0018,0x1511>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1520> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1520>::VRString[] = "DS";
const char TagToType<0x0018,0x1520>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1521> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x1521>::VRString[] = "DS";
const char TagToType<0x0018,0x1521>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x1530> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1530>::VRString[] = "DS";
const char TagToType<0x0018,0x1530>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1531> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1531>::VRString[] = "DS";
const char TagToType<0x0018,0x1531>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1600> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_3 };
static const char VMString[];
};
const char TagToType<0x0018,0x1600>::VRString[] = "CS";
const char TagToType<0x0018,0x1600>::VMString[] = "1-3";
template <> struct TagToType<0x0018,0x1602> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1602>::VRString[] = "IS";
const char TagToType<0x0018,0x1602>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1604> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1604>::VRString[] = "IS";
const char TagToType<0x0018,0x1604>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1606> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1606>::VRString[] = "IS";
const char TagToType<0x0018,0x1606>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1608> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1608>::VRString[] = "IS";
const char TagToType<0x0018,0x1608>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1610> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x1610>::VRString[] = "IS";
const char TagToType<0x0018,0x1610>::VMString[] = "2";
template <> struct TagToType<0x0018,0x1612> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1612>::VRString[] = "IS";
const char TagToType<0x0018,0x1612>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1620> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2_2n };
static const char VMString[];
};
const char TagToType<0x0018,0x1620>::VRString[] = "IS";
const char TagToType<0x0018,0x1620>::VMString[] = "2-2n";
template <> struct TagToType<0x0018,0x1622> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1622>::VRString[] = "US";
const char TagToType<0x0018,0x1622>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1623> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1623>::VRString[] = "US";
const char TagToType<0x0018,0x1623>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1624> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0018,0x1624>::VRString[] = "US";
const char TagToType<0x0018,0x1624>::VMString[] = "3";
template <> struct TagToType<0x0018,0x1700> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_3 };
static const char VMString[];
};
const char TagToType<0x0018,0x1700>::VRString[] = "CS";
const char TagToType<0x0018,0x1700>::VMString[] = "1-3";
template <> struct TagToType<0x0018,0x1702> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1702>::VRString[] = "IS";
const char TagToType<0x0018,0x1702>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1704> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1704>::VRString[] = "IS";
const char TagToType<0x0018,0x1704>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1706> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1706>::VRString[] = "IS";
const char TagToType<0x0018,0x1706>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1708> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1708>::VRString[] = "IS";
const char TagToType<0x0018,0x1708>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1710> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x1710>::VRString[] = "IS";
const char TagToType<0x0018,0x1710>::VMString[] = "2";
template <> struct TagToType<0x0018,0x1712> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1712>::VRString[] = "IS";
const char TagToType<0x0018,0x1712>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1720> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2_2n };
static const char VMString[];
};
const char TagToType<0x0018,0x1720>::VRString[] = "IS";
const char TagToType<0x0018,0x1720>::VMString[] = "2-2n";
template <> struct TagToType<0x0018,0x1800> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1800>::VRString[] = "CS";
const char TagToType<0x0018,0x1800>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1801> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1801>::VRString[] = "SH";
const char TagToType<0x0018,0x1801>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1802> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1802>::VRString[] = "CS";
const char TagToType<0x0018,0x1802>::VMString[] = "1";
template <> struct TagToType<0x0018,0x1803> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x1803>::VRString[] = "LO";
const char TagToType<0x0018,0x1803>::VMString[] = "1";
template <> struct TagToType<0x0018,0x2001> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x2001>::VRString[] = "IS";
const char TagToType<0x0018,0x2001>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x2002> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x2002>::VRString[] = "SH";
const char TagToType<0x0018,0x2002>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x2003> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x2003>::VRString[] = "DS";
const char TagToType<0x0018,0x2003>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x2004> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x2004>::VRString[] = "DS";
const char TagToType<0x0018,0x2004>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x2005> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x2005>::VRString[] = "DS";
const char TagToType<0x0018,0x2005>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x2006> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x2006>::VRString[] = "SH";
const char TagToType<0x0018,0x2006>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x2010> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x2010>::VRString[] = "DS";
const char TagToType<0x0018,0x2010>::VMString[] = "2";
template <> struct TagToType<0x0018,0x2020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x2020>::VRString[] = "CS";
const char TagToType<0x0018,0x2020>::VMString[] = "1";
template <> struct TagToType<0x0018,0x2030> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x2030>::VRString[] = "DS";
const char TagToType<0x0018,0x2030>::VMString[] = "1";
template <> struct TagToType<0x0018,0x3100> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x3100>::VRString[] = "CS";
const char TagToType<0x0018,0x3100>::VMString[] = "1";
template <> struct TagToType<0x0018,0x3101> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x3101>::VRString[] = "DS";
const char TagToType<0x0018,0x3101>::VMString[] = "1";
template <> struct TagToType<0x0018,0x3102> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x3102>::VRString[] = "DS";
const char TagToType<0x0018,0x3102>::VMString[] = "1";
template <> struct TagToType<0x0018,0x3103> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x3103>::VRString[] = "IS";
const char TagToType<0x0018,0x3103>::VMString[] = "1";
template <> struct TagToType<0x0018,0x3104> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x3104>::VRString[] = "IS";
const char TagToType<0x0018,0x3104>::VMString[] = "1";
template <> struct TagToType<0x0018,0x3105> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x3105>::VRString[] = "IS";
const char TagToType<0x0018,0x3105>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x4000> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x4000>::VRString[] = "LT";
const char TagToType<0x0018,0x4000>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5000> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x5000>::VRString[] = "SH";
const char TagToType<0x0018,0x5000>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x5010> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0018,0x5010>::VRString[] = "LO";
const char TagToType<0x0018,0x5010>::VMString[] = "3";
template <> struct TagToType<0x0018,0x5012> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5012>::VRString[] = "DS";
const char TagToType<0x0018,0x5012>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5020> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5020>::VRString[] = "LO";
const char TagToType<0x0018,0x5020>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5021> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5021>::VRString[] = "LO";
const char TagToType<0x0018,0x5021>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5022> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5022>::VRString[] = "DS";
const char TagToType<0x0018,0x5022>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5024> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5024>::VRString[] = "DS";
const char TagToType<0x0018,0x5024>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5026> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5026>::VRString[] = "DS";
const char TagToType<0x0018,0x5026>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5027> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5027>::VRString[] = "DS";
const char TagToType<0x0018,0x5027>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5028> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5028>::VRString[] = "DS";
const char TagToType<0x0018,0x5028>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5029> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5029>::VRString[] = "DS";
const char TagToType<0x0018,0x5029>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5030> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5030>::VRString[] = "DS";
const char TagToType<0x0018,0x5030>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5040> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5040>::VRString[] = "DS";
const char TagToType<0x0018,0x5040>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5050> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5050>::VRString[] = "IS";
const char TagToType<0x0018,0x5050>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5100> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5100>::VRString[] = "CS";
const char TagToType<0x0018,0x5100>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5101> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5101>::VRString[] = "CS";
const char TagToType<0x0018,0x5101>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5104> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x5104>::VRString[] = "SQ";
const char TagToType<0x0018,0x5104>::VMString[] = "1";
template <> struct TagToType<0x0018,0x5210> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM6 };
static const char VMString[];
};
const char TagToType<0x0018,0x5210>::VRString[] = "DS";
const char TagToType<0x0018,0x5210>::VMString[] = "6";
template <> struct TagToType<0x0018,0x5212> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0018,0x5212>::VRString[] = "DS";
const char TagToType<0x0018,0x5212>::VMString[] = "3";
template <> struct TagToType<0x0018,0x6000> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6000>::VRString[] = "DS";
const char TagToType<0x0018,0x6000>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6011> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6011>::VRString[] = "SQ";
const char TagToType<0x0018,0x6011>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6012> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6012>::VRString[] = "US";
const char TagToType<0x0018,0x6012>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6014> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6014>::VRString[] = "US";
const char TagToType<0x0018,0x6014>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6016> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6016>::VRString[] = "UL";
const char TagToType<0x0018,0x6016>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6018> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6018>::VRString[] = "UL";
const char TagToType<0x0018,0x6018>::VMString[] = "1";
template <> struct TagToType<0x0018,0x601a> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x601a>::VRString[] = "UL";
const char TagToType<0x0018,0x601a>::VMString[] = "1";
template <> struct TagToType<0x0018,0x601c> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x601c>::VRString[] = "UL";
const char TagToType<0x0018,0x601c>::VMString[] = "1";
template <> struct TagToType<0x0018,0x601e> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x601e>::VRString[] = "UL";
const char TagToType<0x0018,0x601e>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6020> {
static const char VRString[];
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6020>::VRString[] = "SL";
const char TagToType<0x0018,0x6020>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6022> {
static const char VRString[];
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6022>::VRString[] = "SL";
const char TagToType<0x0018,0x6022>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6024> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6024>::VRString[] = "US";
const char TagToType<0x0018,0x6024>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6026> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6026>::VRString[] = "US";
const char TagToType<0x0018,0x6026>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6028> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6028>::VRString[] = "FD";
const char TagToType<0x0018,0x6028>::VMString[] = "1";
template <> struct TagToType<0x0018,0x602a> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x602a>::VRString[] = "FD";
const char TagToType<0x0018,0x602a>::VMString[] = "1";
template <> struct TagToType<0x0018,0x602c> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x602c>::VRString[] = "FD";
const char TagToType<0x0018,0x602c>::VMString[] = "1";
template <> struct TagToType<0x0018,0x602e> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x602e>::VRString[] = "FD";
const char TagToType<0x0018,0x602e>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6030> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6030>::VRString[] = "UL";
const char TagToType<0x0018,0x6030>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6031> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6031>::VRString[] = "CS";
const char TagToType<0x0018,0x6031>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6032> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6032>::VRString[] = "UL";
const char TagToType<0x0018,0x6032>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6034> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6034>::VRString[] = "FD";
const char TagToType<0x0018,0x6034>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6036> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6036>::VRString[] = "FD";
const char TagToType<0x0018,0x6036>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6038> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6038>::VRString[] = "UL";
const char TagToType<0x0018,0x6038>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6039> {
static const char VRString[];
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6039>::VRString[] = "SL";
const char TagToType<0x0018,0x6039>::VMString[] = "1";
template <> struct TagToType<0x0018,0x603a> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x603a>::VRString[] = "UL";
const char TagToType<0x0018,0x603a>::VMString[] = "1";
template <> struct TagToType<0x0018,0x603b> {
static const char VRString[];
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x603b>::VRString[] = "SL";
const char TagToType<0x0018,0x603b>::VMString[] = "1";
template <> struct TagToType<0x0018,0x603c> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x603c>::VRString[] = "UL";
const char TagToType<0x0018,0x603c>::VMString[] = "1";
template <> struct TagToType<0x0018,0x603d> {
static const char VRString[];
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x603d>::VRString[] = "SL";
const char TagToType<0x0018,0x603d>::VMString[] = "1";
template <> struct TagToType<0x0018,0x603e> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x603e>::VRString[] = "UL";
const char TagToType<0x0018,0x603e>::VMString[] = "1";
template <> struct TagToType<0x0018,0x603f> {
static const char VRString[];
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x603f>::VRString[] = "SL";
const char TagToType<0x0018,0x603f>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6040> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6040>::VRString[] = "UL";
const char TagToType<0x0018,0x6040>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6041> {
static const char VRString[];
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6041>::VRString[] = "SL";
const char TagToType<0x0018,0x6041>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6042> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6042>::VRString[] = "UL";
const char TagToType<0x0018,0x6042>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6043> {
static const char VRString[];
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6043>::VRString[] = "SL";
const char TagToType<0x0018,0x6043>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6044> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6044>::VRString[] = "US";
const char TagToType<0x0018,0x6044>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6046> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6046>::VRString[] = "UL";
const char TagToType<0x0018,0x6046>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6048> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6048>::VRString[] = "UL";
const char TagToType<0x0018,0x6048>::VMString[] = "1";
template <> struct TagToType<0x0018,0x604a> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x604a>::VRString[] = "UL";
const char TagToType<0x0018,0x604a>::VMString[] = "1";
template <> struct TagToType<0x0018,0x604c> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x604c>::VRString[] = "US";
const char TagToType<0x0018,0x604c>::VMString[] = "1";
template <> struct TagToType<0x0018,0x604e> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x604e>::VRString[] = "US";
const char TagToType<0x0018,0x604e>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6050> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6050>::VRString[] = "UL";
const char TagToType<0x0018,0x6050>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6052> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x6052>::VRString[] = "UL";
const char TagToType<0x0018,0x6052>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x6054> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x6054>::VRString[] = "FD";
const char TagToType<0x0018,0x6054>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x6056> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x6056>::VRString[] = "UL";
const char TagToType<0x0018,0x6056>::VMString[] = "1";
template <> struct TagToType<0x0018,0x6058> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x6058>::VRString[] = "UL";
const char TagToType<0x0018,0x6058>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x605a> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x605a>::VRString[] = "FL";
const char TagToType<0x0018,0x605a>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x6060> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x6060>::VRString[] = "FL";
const char TagToType<0x0018,0x6060>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x7000> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7000>::VRString[] = "CS";
const char TagToType<0x0018,0x7000>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7001> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7001>::VRString[] = "DS";
const char TagToType<0x0018,0x7001>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7004> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7004>::VRString[] = "CS";
const char TagToType<0x0018,0x7004>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7005> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7005>::VRString[] = "CS";
const char TagToType<0x0018,0x7005>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7006> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7006>::VRString[] = "LT";
const char TagToType<0x0018,0x7006>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7008> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7008>::VRString[] = "LT";
const char TagToType<0x0018,0x7008>::VMString[] = "1";
template <> struct TagToType<0x0018,0x700a> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x700a>::VRString[] = "SH";
const char TagToType<0x0018,0x700a>::VMString[] = "1";
template <> struct TagToType<0x0018,0x700c> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x700c>::VRString[] = "DA";
const char TagToType<0x0018,0x700c>::VMString[] = "1";
template <> struct TagToType<0x0018,0x700e> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x700e>::VRString[] = "TM";
const char TagToType<0x0018,0x700e>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7010> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7010>::VRString[] = "IS";
const char TagToType<0x0018,0x7010>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7011> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7011>::VRString[] = "IS";
const char TagToType<0x0018,0x7011>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7012> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7012>::VRString[] = "DS";
const char TagToType<0x0018,0x7012>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7014> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7014>::VRString[] = "DS";
const char TagToType<0x0018,0x7014>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7016> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7016>::VRString[] = "DS";
const char TagToType<0x0018,0x7016>::VMString[] = "1";
template <> struct TagToType<0x0018,0x701a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x701a>::VRString[] = "DS";
const char TagToType<0x0018,0x701a>::VMString[] = "2";
template <> struct TagToType<0x0018,0x7020> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x7020>::VRString[] = "DS";
const char TagToType<0x0018,0x7020>::VMString[] = "2";
template <> struct TagToType<0x0018,0x7022> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x7022>::VRString[] = "DS";
const char TagToType<0x0018,0x7022>::VMString[] = "2";
template <> struct TagToType<0x0018,0x7024> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7024>::VRString[] = "CS";
const char TagToType<0x0018,0x7024>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7026> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x7026>::VRString[] = "DS";
const char TagToType<0x0018,0x7026>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x7028> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x7028>::VRString[] = "DS";
const char TagToType<0x0018,0x7028>::VMString[] = "2";
template <> struct TagToType<0x0018,0x702a> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x702a>::VRString[] = "LO";
const char TagToType<0x0018,0x702a>::VMString[] = "1";
template <> struct TagToType<0x0018,0x702b> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x702b>::VRString[] = "LO";
const char TagToType<0x0018,0x702b>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7030> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x7030>::VRString[] = "DS";
const char TagToType<0x0018,0x7030>::VMString[] = "2";
template <> struct TagToType<0x0018,0x7032> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7032>::VRString[] = "DS";
const char TagToType<0x0018,0x7032>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7034> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7034>::VRString[] = "CS";
const char TagToType<0x0018,0x7034>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7040> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7040>::VRString[] = "LT";
const char TagToType<0x0018,0x7040>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7041> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7041>::VRString[] = "LT";
const char TagToType<0x0018,0x7041>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7042> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7042>::VRString[] = "DS";
const char TagToType<0x0018,0x7042>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7044> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7044>::VRString[] = "DS";
const char TagToType<0x0018,0x7044>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7046> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x7046>::VRString[] = "IS";
const char TagToType<0x0018,0x7046>::VMString[] = "2";
template <> struct TagToType<0x0018,0x7048> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7048>::VRString[] = "DS";
const char TagToType<0x0018,0x7048>::VMString[] = "1";
template <> struct TagToType<0x0018,0x704c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x704c>::VRString[] = "DS";
const char TagToType<0x0018,0x704c>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7050> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x7050>::VRString[] = "CS";
const char TagToType<0x0018,0x7050>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x7052> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x7052>::VRString[] = "DS";
const char TagToType<0x0018,0x7052>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x7054> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x7054>::VRString[] = "DS";
const char TagToType<0x0018,0x7054>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x7060> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7060>::VRString[] = "CS";
const char TagToType<0x0018,0x7060>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7062> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7062>::VRString[] = "LT";
const char TagToType<0x0018,0x7062>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7064> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7064>::VRString[] = "CS";
const char TagToType<0x0018,0x7064>::VMString[] = "1";
template <> struct TagToType<0x0018,0x7065> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x7065>::VRString[] = "DS";
const char TagToType<0x0018,0x7065>::VMString[] = "1";
template <> struct TagToType<0x0018,0x8150> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x8150>::VRString[] = "DS";
const char TagToType<0x0018,0x8150>::VMString[] = "1";
template <> struct TagToType<0x0018,0x8151> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x8151>::VRString[] = "DS";
const char TagToType<0x0018,0x8151>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9004> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9004>::VRString[] = "CS";
const char TagToType<0x0018,0x9004>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9005> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9005>::VRString[] = "SH";
const char TagToType<0x0018,0x9005>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9006> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9006>::VRString[] = "SQ";
const char TagToType<0x0018,0x9006>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9008> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9008>::VRString[] = "CS";
const char TagToType<0x0018,0x9008>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9009> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9009>::VRString[] = "CS";
const char TagToType<0x0018,0x9009>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9010> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9010>::VRString[] = "CS";
const char TagToType<0x0018,0x9010>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9011> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9011>::VRString[] = "CS";
const char TagToType<0x0018,0x9011>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9012> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9012>::VRString[] = "CS";
const char TagToType<0x0018,0x9012>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9014> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9014>::VRString[] = "CS";
const char TagToType<0x0018,0x9014>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9015> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9015>::VRString[] = "CS";
const char TagToType<0x0018,0x9015>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9016> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9016>::VRString[] = "CS";
const char TagToType<0x0018,0x9016>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9017> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9017>::VRString[] = "CS";
const char TagToType<0x0018,0x9017>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9018> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9018>::VRString[] = "CS";
const char TagToType<0x0018,0x9018>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9019> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9019>::VRString[] = "FD";
const char TagToType<0x0018,0x9019>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9020>::VRString[] = "CS";
const char TagToType<0x0018,0x9020>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9021> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9021>::VRString[] = "CS";
const char TagToType<0x0018,0x9021>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9022> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9022>::VRString[] = "CS";
const char TagToType<0x0018,0x9022>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9024> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9024>::VRString[] = "CS";
const char TagToType<0x0018,0x9024>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9025> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9025>::VRString[] = "CS";
const char TagToType<0x0018,0x9025>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9026> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9026>::VRString[] = "CS";
const char TagToType<0x0018,0x9026>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9027> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9027>::VRString[] = "CS";
const char TagToType<0x0018,0x9027>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9028> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9028>::VRString[] = "CS";
const char TagToType<0x0018,0x9028>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9029> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9029>::VRString[] = "CS";
const char TagToType<0x0018,0x9029>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9030> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9030>::VRString[] = "FD";
const char TagToType<0x0018,0x9030>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9032> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9032>::VRString[] = "CS";
const char TagToType<0x0018,0x9032>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9033> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9033>::VRString[] = "CS";
const char TagToType<0x0018,0x9033>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9034> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9034>::VRString[] = "CS";
const char TagToType<0x0018,0x9034>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9035> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9035>::VRString[] = "FD";
const char TagToType<0x0018,0x9035>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9036> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9036>::VRString[] = "CS";
const char TagToType<0x0018,0x9036>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9037> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9037>::VRString[] = "CS";
const char TagToType<0x0018,0x9037>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9041> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9041>::VRString[] = "LO";
const char TagToType<0x0018,0x9041>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9042> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9042>::VRString[] = "SQ";
const char TagToType<0x0018,0x9042>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9043> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9043>::VRString[] = "CS";
const char TagToType<0x0018,0x9043>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9044> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9044>::VRString[] = "CS";
const char TagToType<0x0018,0x9044>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9045> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9045>::VRString[] = "SQ";
const char TagToType<0x0018,0x9045>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9046> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9046>::VRString[] = "LO";
const char TagToType<0x0018,0x9046>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9047> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9047>::VRString[] = "SH";
const char TagToType<0x0018,0x9047>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9048> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9048>::VRString[] = "CS";
const char TagToType<0x0018,0x9048>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9049> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9049>::VRString[] = "SQ";
const char TagToType<0x0018,0x9049>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9050> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9050>::VRString[] = "LO";
const char TagToType<0x0018,0x9050>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9051> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9051>::VRString[] = "CS";
const char TagToType<0x0018,0x9051>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9052> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9052>::VRString[] = "FD";
const char TagToType<0x0018,0x9052>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x9053> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9053>::VRString[] = "FD";
const char TagToType<0x0018,0x9053>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x9054> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9054>::VRString[] = "CS";
const char TagToType<0x0018,0x9054>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9058> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9058>::VRString[] = "US";
const char TagToType<0x0018,0x9058>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9059> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9059>::VRString[] = "CS";
const char TagToType<0x0018,0x9059>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9060> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9060>::VRString[] = "CS";
const char TagToType<0x0018,0x9060>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x9061> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9061>::VRString[] = "FD";
const char TagToType<0x0018,0x9061>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x9062> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9062>::VRString[] = "CS";
const char TagToType<0x0018,0x9062>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9063> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9063>::VRString[] = "FD";
const char TagToType<0x0018,0x9063>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x9064> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9064>::VRString[] = "CS";
const char TagToType<0x0018,0x9064>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9065> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9065>::VRString[] = "CS";
const char TagToType<0x0018,0x9065>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x9066> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9066>::VRString[] = "US";
const char TagToType<0x0018,0x9066>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x9067> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9067>::VRString[] = "CS";
const char TagToType<0x0018,0x9067>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9069> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9069>::VRString[] = "FD";
const char TagToType<0x0018,0x9069>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9070> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9070>::VRString[] = "FD";
const char TagToType<0x0018,0x9070>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9073> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9073>::VRString[] = "FD";
const char TagToType<0x0018,0x9073>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9074> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9074>::VRString[] = "DT";
const char TagToType<0x0018,0x9074>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9075> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9075>::VRString[] = "CS";
const char TagToType<0x0018,0x9075>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9076> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9076>::VRString[] = "SQ";
const char TagToType<0x0018,0x9076>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9077> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9077>::VRString[] = "CS";
const char TagToType<0x0018,0x9077>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9078> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9078>::VRString[] = "CS";
const char TagToType<0x0018,0x9078>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9079> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0018,0x9079>::VRString[] = "FD";
const char TagToType<0x0018,0x9079>::VMString[] = "1-n";
template <> struct TagToType<0x0018,0x9080> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9080>::VRString[] = "ST";
const char TagToType<0x0018,0x9080>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9081> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9081>::VRString[] = "CS";
const char TagToType<0x0018,0x9081>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9082> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9082>::VRString[] = "FD";
const char TagToType<0x0018,0x9082>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9083> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9083>::VRString[] = "SQ";
const char TagToType<0x0018,0x9083>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9084> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9084>::VRString[] = "SQ";
const char TagToType<0x0018,0x9084>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9085> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9085>::VRString[] = "CS";
const char TagToType<0x0018,0x9085>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9087> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9087>::VRString[] = "FD";
const char TagToType<0x0018,0x9087>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9089> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0018,0x9089>::VRString[] = "FD";
const char TagToType<0x0018,0x9089>::VMString[] = "3";
template <> struct TagToType<0x0018,0x9090> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0018,0x9090>::VRString[] = "FD";
const char TagToType<0x0018,0x9090>::VMString[] = "3";
template <> struct TagToType<0x0018,0x9091> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9091>::VRString[] = "FD";
const char TagToType<0x0018,0x9091>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9093> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9093>::VRString[] = "US";
const char TagToType<0x0018,0x9093>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9094> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9094>::VRString[] = "CS";
const char TagToType<0x0018,0x9094>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9095> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9095>::VRString[] = "UL";
const char TagToType<0x0018,0x9095>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9096> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9096>::VRString[] = "FD";
const char TagToType<0x0018,0x9096>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9098> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9098>::VRString[] = "FD";
const char TagToType<0x0018,0x9098>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x9100> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9100>::VRString[] = "CS";
const char TagToType<0x0018,0x9100>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x9101> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9101>::VRString[] = "CS";
const char TagToType<0x0018,0x9101>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9103> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9103>::VRString[] = "SQ";
const char TagToType<0x0018,0x9103>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9104> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9104>::VRString[] = "FD";
const char TagToType<0x0018,0x9104>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9105> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0018,0x9105>::VRString[] = "FD";
const char TagToType<0x0018,0x9105>::VMString[] = "3";
template <> struct TagToType<0x0018,0x9106> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0018,0x9106>::VRString[] = "FD";
const char TagToType<0x0018,0x9106>::VMString[] = "3";
template <> struct TagToType<0x0018,0x9107> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9107>::VRString[] = "SQ";
const char TagToType<0x0018,0x9107>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9112> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9112>::VRString[] = "SQ";
const char TagToType<0x0018,0x9112>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9114> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9114>::VRString[] = "SQ";
const char TagToType<0x0018,0x9114>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9115> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9115>::VRString[] = "SQ";
const char TagToType<0x0018,0x9115>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9117> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9117>::VRString[] = "SQ";
const char TagToType<0x0018,0x9117>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9118> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9118>::VRString[] = "SQ";
const char TagToType<0x0018,0x9118>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9119> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9119>::VRString[] = "SQ";
const char TagToType<0x0018,0x9119>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9125> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9125>::VRString[] = "SQ";
const char TagToType<0x0018,0x9125>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9126> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9126>::VRString[] = "SQ";
const char TagToType<0x0018,0x9126>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9127> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9127>::VRString[] = "UL";
const char TagToType<0x0018,0x9127>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9147> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9147>::VRString[] = "CS";
const char TagToType<0x0018,0x9147>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9151> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9151>::VRString[] = "DT";
const char TagToType<0x0018,0x9151>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9152> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9152>::VRString[] = "SQ";
const char TagToType<0x0018,0x9152>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9155> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9155>::VRString[] = "FD";
const char TagToType<0x0018,0x9155>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9159> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9159>::VRString[] = "UL";
const char TagToType<0x0018,0x9159>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9166> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9166>::VRString[] = "CS";
const char TagToType<0x0018,0x9166>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9168> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9168>::VRString[] = "FD";
const char TagToType<0x0018,0x9168>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9169> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9169>::VRString[] = "CS";
const char TagToType<0x0018,0x9169>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9170> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9170>::VRString[] = "CS";
const char TagToType<0x0018,0x9170>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9171> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9171>::VRString[] = "CS";
const char TagToType<0x0018,0x9171>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9172> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9172>::VRString[] = "CS";
const char TagToType<0x0018,0x9172>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9173> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9173>::VRString[] = "CS";
const char TagToType<0x0018,0x9173>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9174> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9174>::VRString[] = "CS";
const char TagToType<0x0018,0x9174>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9175> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9175>::VRString[] = "LO";
const char TagToType<0x0018,0x9175>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9176> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9176>::VRString[] = "SQ";
const char TagToType<0x0018,0x9176>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9177> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9177>::VRString[] = "CS";
const char TagToType<0x0018,0x9177>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9178> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9178>::VRString[] = "CS";
const char TagToType<0x0018,0x9178>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9179> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9179>::VRString[] = "CS";
const char TagToType<0x0018,0x9179>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9180> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9180>::VRString[] = "CS";
const char TagToType<0x0018,0x9180>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9181> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9181>::VRString[] = "FD";
const char TagToType<0x0018,0x9181>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9182> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9182>::VRString[] = "FD";
const char TagToType<0x0018,0x9182>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9183> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9183>::VRString[] = "CS";
const char TagToType<0x0018,0x9183>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9184> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9184>::VRString[] = "FD";
const char TagToType<0x0018,0x9184>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9185> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9185>::VRString[] = "ST";
const char TagToType<0x0018,0x9185>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9186> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9186>::VRString[] = "SH";
const char TagToType<0x0018,0x9186>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9195> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9195>::VRString[] = "FD";
const char TagToType<0x0018,0x9195>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9196> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9196>::VRString[] = "FD";
const char TagToType<0x0018,0x9196>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9197> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9197>::VRString[] = "SQ";
const char TagToType<0x0018,0x9197>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9198> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9198>::VRString[] = "CS";
const char TagToType<0x0018,0x9198>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9199> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9199>::VRString[] = "CS";
const char TagToType<0x0018,0x9199>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9200> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9200>::VRString[] = "CS";
const char TagToType<0x0018,0x9200>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9214> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9214>::VRString[] = "CS";
const char TagToType<0x0018,0x9214>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9217> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9217>::VRString[] = "FD";
const char TagToType<0x0018,0x9217>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9218> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9218>::VRString[] = "FD";
const char TagToType<0x0018,0x9218>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9219> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9219>::VRString[] = "SS";
const char TagToType<0x0018,0x9219>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9220> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9220>::VRString[] = "FD";
const char TagToType<0x0018,0x9220>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9226> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9226>::VRString[] = "SQ";
const char TagToType<0x0018,0x9226>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9227> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9227>::VRString[] = "SQ";
const char TagToType<0x0018,0x9227>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9231> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9231>::VRString[] = "US";
const char TagToType<0x0018,0x9231>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9232> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9232>::VRString[] = "US";
const char TagToType<0x0018,0x9232>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9234> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9234>::VRString[] = "UL";
const char TagToType<0x0018,0x9234>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9236> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9236>::VRString[] = "CS";
const char TagToType<0x0018,0x9236>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9239> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9239>::VRString[] = "SQ";
const char TagToType<0x0018,0x9239>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9240> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9240>::VRString[] = "US";
const char TagToType<0x0018,0x9240>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9241> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9241>::VRString[] = "US";
const char TagToType<0x0018,0x9241>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9295> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9295>::VRString[] = "FD";
const char TagToType<0x0018,0x9295>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9296> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9296>::VRString[] = "FD";
const char TagToType<0x0018,0x9296>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9301> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9301>::VRString[] = "SQ";
const char TagToType<0x0018,0x9301>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9302> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9302>::VRString[] = "CS";
const char TagToType<0x0018,0x9302>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9303> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9303>::VRString[] = "FD";
const char TagToType<0x0018,0x9303>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9304> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9304>::VRString[] = "SQ";
const char TagToType<0x0018,0x9304>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9305> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9305>::VRString[] = "FD";
const char TagToType<0x0018,0x9305>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9306> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9306>::VRString[] = "FD";
const char TagToType<0x0018,0x9306>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9307> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9307>::VRString[] = "FD";
const char TagToType<0x0018,0x9307>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9308> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9308>::VRString[] = "SQ";
const char TagToType<0x0018,0x9308>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9309> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9309>::VRString[] = "FD";
const char TagToType<0x0018,0x9309>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9310> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9310>::VRString[] = "FD";
const char TagToType<0x0018,0x9310>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9311> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9311>::VRString[] = "FD";
const char TagToType<0x0018,0x9311>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9312> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9312>::VRString[] = "SQ";
const char TagToType<0x0018,0x9312>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9313> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0018,0x9313>::VRString[] = "FD";
const char TagToType<0x0018,0x9313>::VMString[] = "3";
template <> struct TagToType<0x0018,0x9314> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9314>::VRString[] = "SQ";
const char TagToType<0x0018,0x9314>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9315> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9315>::VRString[] = "CS";
const char TagToType<0x0018,0x9315>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9316> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9316>::VRString[] = "CS";
const char TagToType<0x0018,0x9316>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9317> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9317>::VRString[] = "FD";
const char TagToType<0x0018,0x9317>::VMString[] = "2";
template <> struct TagToType<0x0018,0x9318> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0018,0x9318>::VRString[] = "FD";
const char TagToType<0x0018,0x9318>::VMString[] = "3";
template <> struct TagToType<0x0018,0x9319> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9319>::VRString[] = "FD";
const char TagToType<0x0018,0x9319>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9320> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9320>::VRString[] = "SH";
const char TagToType<0x0018,0x9320>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9321> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9321>::VRString[] = "SQ";
const char TagToType<0x0018,0x9321>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9322> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9322>::VRString[] = "FD";
const char TagToType<0x0018,0x9322>::VMString[] = "2";
template <> struct TagToType<0x0018,0x9323> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9323>::VRString[] = "CS";
const char TagToType<0x0018,0x9323>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9324> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9324>::VRString[] = "FD";
const char TagToType<0x0018,0x9324>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9325> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9325>::VRString[] = "SQ";
const char TagToType<0x0018,0x9325>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9326> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9326>::VRString[] = "SQ";
const char TagToType<0x0018,0x9326>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9327> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9327>::VRString[] = "FD";
const char TagToType<0x0018,0x9327>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9328> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9328>::VRString[] = "FD";
const char TagToType<0x0018,0x9328>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9329> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9329>::VRString[] = "SQ";
const char TagToType<0x0018,0x9329>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9330> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9330>::VRString[] = "FD";
const char TagToType<0x0018,0x9330>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9332> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9332>::VRString[] = "FD";
const char TagToType<0x0018,0x9332>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9333> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9333>::VRString[] = "CS";
const char TagToType<0x0018,0x9333>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9334> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9334>::VRString[] = "CS";
const char TagToType<0x0018,0x9334>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9335> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9335>::VRString[] = "FD";
const char TagToType<0x0018,0x9335>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9337> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9337>::VRString[] = "US";
const char TagToType<0x0018,0x9337>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9338> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9338>::VRString[] = "SQ";
const char TagToType<0x0018,0x9338>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9340> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9340>::VRString[] = "SQ";
const char TagToType<0x0018,0x9340>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9341> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9341>::VRString[] = "SQ";
const char TagToType<0x0018,0x9341>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9342> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9342>::VRString[] = "CS";
const char TagToType<0x0018,0x9342>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9343> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9343>::VRString[] = "CS";
const char TagToType<0x0018,0x9343>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9344> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9344>::VRString[] = "CS";
const char TagToType<0x0018,0x9344>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9345> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9345>::VRString[] = "FD";
const char TagToType<0x0018,0x9345>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9346> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9346>::VRString[] = "SQ";
const char TagToType<0x0018,0x9346>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9351> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9351>::VRString[] = "FL";
const char TagToType<0x0018,0x9351>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9352> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0018,0x9352>::VRString[] = "FL";
const char TagToType<0x0018,0x9352>::VMString[] = "3";
template <> struct TagToType<0x0018,0x9360> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9360>::VRString[] = "SQ";
const char TagToType<0x0018,0x9360>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9401> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9401>::VRString[] = "SQ";
const char TagToType<0x0018,0x9401>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9402> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9402>::VRString[] = "FL";
const char TagToType<0x0018,0x9402>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9403> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9403>::VRString[] = "FL";
const char TagToType<0x0018,0x9403>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9404> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9404>::VRString[] = "FL";
const char TagToType<0x0018,0x9404>::VMString[] = "2";
template <> struct TagToType<0x0018,0x9405> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9405>::VRString[] = "SQ";
const char TagToType<0x0018,0x9405>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9406> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9406>::VRString[] = "SQ";
const char TagToType<0x0018,0x9406>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9407> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9407>::VRString[] = "SQ";
const char TagToType<0x0018,0x9407>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9412> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9412>::VRString[] = "SQ";
const char TagToType<0x0018,0x9412>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9417> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9417>::VRString[] = "SQ";
const char TagToType<0x0018,0x9417>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9420> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9420>::VRString[] = "CS";
const char TagToType<0x0018,0x9420>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9423> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9423>::VRString[] = "LO";
const char TagToType<0x0018,0x9423>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9424> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9424>::VRString[] = "LT";
const char TagToType<0x0018,0x9424>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9425> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9425>::VRString[] = "CS";
const char TagToType<0x0018,0x9425>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9426> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9426>::VRString[] = "FL";
const char TagToType<0x0018,0x9426>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9427> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9427>::VRString[] = "CS";
const char TagToType<0x0018,0x9427>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9428> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9428>::VRString[] = "FL";
const char TagToType<0x0018,0x9428>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x9429> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9429>::VRString[] = "FL";
const char TagToType<0x0018,0x9429>::VMString[] = "2";
template <> struct TagToType<0x0018,0x9430> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9430>::VRString[] = "US";
const char TagToType<0x0018,0x9430>::VMString[] = "2";
template <> struct TagToType<0x0018,0x9432> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9432>::VRString[] = "SQ";
const char TagToType<0x0018,0x9432>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9433> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9433>::VRString[] = "LO";
const char TagToType<0x0018,0x9433>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9434> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9434>::VRString[] = "SQ";
const char TagToType<0x0018,0x9434>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9435> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9435>::VRString[] = "CS";
const char TagToType<0x0018,0x9435>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9436> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9436>::VRString[] = "SS";
const char TagToType<0x0018,0x9436>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9437> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9437>::VRString[] = "SS";
const char TagToType<0x0018,0x9437>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9438> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9438>::VRString[] = "SS";
const char TagToType<0x0018,0x9438>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9439> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9439>::VRString[] = "SS";
const char TagToType<0x0018,0x9439>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9440> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9440>::VRString[] = "SS";
const char TagToType<0x0018,0x9440>::VMString[] = "2";
template <> struct TagToType<0x0018,0x9441> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9441>::VRString[] = "US";
const char TagToType<0x0018,0x9441>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9442> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM2_n };
static const char VMString[];
};
const char TagToType<0x0018,0x9442>::VRString[] = "SS";
const char TagToType<0x0018,0x9442>::VMString[] = "2-n";
template <> struct TagToType<0x0018,0x9447> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9447>::VRString[] = "FL";
const char TagToType<0x0018,0x9447>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9449> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9449>::VRString[] = "FL";
const char TagToType<0x0018,0x9449>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9451> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9451>::VRString[] = "SQ";
const char TagToType<0x0018,0x9451>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9452> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9452>::VRString[] = "FL";
const char TagToType<0x0018,0x9452>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9455> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9455>::VRString[] = "SQ";
const char TagToType<0x0018,0x9455>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9456> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9456>::VRString[] = "SQ";
const char TagToType<0x0018,0x9456>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9457> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9457>::VRString[] = "CS";
const char TagToType<0x0018,0x9457>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9461> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0018,0x9461>::VRString[] = "FL";
const char TagToType<0x0018,0x9461>::VMString[] = "1-2";
template <> struct TagToType<0x0018,0x9462> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9462>::VRString[] = "SQ";
const char TagToType<0x0018,0x9462>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9463> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9463>::VRString[] = "FL";
const char TagToType<0x0018,0x9463>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9464> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9464>::VRString[] = "FL";
const char TagToType<0x0018,0x9464>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9465> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9465>::VRString[] = "FL";
const char TagToType<0x0018,0x9465>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9466> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9466>::VRString[] = "FL";
const char TagToType<0x0018,0x9466>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9467> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9467>::VRString[] = "FL";
const char TagToType<0x0018,0x9467>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9468> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9468>::VRString[] = "FL";
const char TagToType<0x0018,0x9468>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9469> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9469>::VRString[] = "FL";
const char TagToType<0x0018,0x9469>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9470> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9470>::VRString[] = "FL";
const char TagToType<0x0018,0x9470>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9471> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9471>::VRString[] = "FL";
const char TagToType<0x0018,0x9471>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9472> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9472>::VRString[] = "SQ";
const char TagToType<0x0018,0x9472>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9473> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9473>::VRString[] = "FL";
const char TagToType<0x0018,0x9473>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9474> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9474>::VRString[] = "CS";
const char TagToType<0x0018,0x9474>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9476> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9476>::VRString[] = "SQ";
const char TagToType<0x0018,0x9476>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9477> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9477>::VRString[] = "SQ";
const char TagToType<0x0018,0x9477>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9504> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9504>::VRString[] = "SQ";
const char TagToType<0x0018,0x9504>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9506> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9506>::VRString[] = "SQ";
const char TagToType<0x0018,0x9506>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9507> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9507>::VRString[] = "SQ";
const char TagToType<0x0018,0x9507>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9508> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9508>::VRString[] = "FL";
const char TagToType<0x0018,0x9508>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9509> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9509>::VRString[] = "FL";
const char TagToType<0x0018,0x9509>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9510> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9510>::VRString[] = "FL";
const char TagToType<0x0018,0x9510>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9511> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9511>::VRString[] = "FL";
const char TagToType<0x0018,0x9511>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9514> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9514>::VRString[] = "FL";
const char TagToType<0x0018,0x9514>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9515> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9515>::VRString[] = "FL";
const char TagToType<0x0018,0x9515>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9516> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9516>::VRString[] = "DT";
const char TagToType<0x0018,0x9516>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9517> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9517>::VRString[] = "DT";
const char TagToType<0x0018,0x9517>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9524> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9524>::VRString[] = "LO";
const char TagToType<0x0018,0x9524>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9525> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9525>::VRString[] = "LO";
const char TagToType<0x0018,0x9525>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9526> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9526>::VRString[] = "LO";
const char TagToType<0x0018,0x9526>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9527> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9527>::VRString[] = "CS";
const char TagToType<0x0018,0x9527>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9528> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9528>::VRString[] = "LO";
const char TagToType<0x0018,0x9528>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9530> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9530>::VRString[] = "SQ";
const char TagToType<0x0018,0x9530>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9531> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9531>::VRString[] = "LO";
const char TagToType<0x0018,0x9531>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9538> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9538>::VRString[] = "SQ";
const char TagToType<0x0018,0x9538>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9601> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9601>::VRString[] = "SQ";
const char TagToType<0x0018,0x9601>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9602> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9602>::VRString[] = "FD";
const char TagToType<0x0018,0x9602>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9603> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9603>::VRString[] = "FD";
const char TagToType<0x0018,0x9603>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9604> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9604>::VRString[] = "FD";
const char TagToType<0x0018,0x9604>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9605> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9605>::VRString[] = "FD";
const char TagToType<0x0018,0x9605>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9606> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9606>::VRString[] = "FD";
const char TagToType<0x0018,0x9606>::VMString[] = "1";
template <> struct TagToType<0x0018,0x9607> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0x9607>::VRString[] = "FD";
const char TagToType<0x0018,0x9607>::VMString[] = "1";
template <> struct TagToType<0x0018,0xa001> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0xa001>::VRString[] = "SQ";
const char TagToType<0x0018,0xa001>::VMString[] = "1";
template <> struct TagToType<0x0018,0xa002> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0xa002>::VRString[] = "DT";
const char TagToType<0x0018,0xa002>::VMString[] = "1";
template <> struct TagToType<0x0018,0xa003> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0018,0xa003>::VRString[] = "ST";
const char TagToType<0x0018,0xa003>::VMString[] = "1";
template <> struct TagToType<0x0020,0x000d> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x000d>::VRString[] = "UI";
const char TagToType<0x0020,0x000d>::VMString[] = "1";
template <> struct TagToType<0x0020,0x000e> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x000e>::VRString[] = "UI";
const char TagToType<0x0020,0x000e>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0010> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0010>::VRString[] = "SH";
const char TagToType<0x0020,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0011> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0011>::VRString[] = "IS";
const char TagToType<0x0020,0x0011>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0012> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0012>::VRString[] = "IS";
const char TagToType<0x0020,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0013> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0013>::VRString[] = "IS";
const char TagToType<0x0020,0x0013>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0014> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0014>::VRString[] = "IS";
const char TagToType<0x0020,0x0014>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0015> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0015>::VRString[] = "IS";
const char TagToType<0x0020,0x0015>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0016> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0016>::VRString[] = "IS";
const char TagToType<0x0020,0x0016>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0017> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0017>::VRString[] = "IS";
const char TagToType<0x0020,0x0017>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0018> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0018>::VRString[] = "IS";
const char TagToType<0x0020,0x0018>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0019> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0019>::VRString[] = "IS";
const char TagToType<0x0020,0x0019>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0020,0x0020>::VRString[] = "CS";
const char TagToType<0x0020,0x0020>::VMString[] = "2";
template <> struct TagToType<0x0020,0x0022> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0022>::VRString[] = "IS";
const char TagToType<0x0020,0x0022>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0024> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0024>::VRString[] = "IS";
const char TagToType<0x0020,0x0024>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0026> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0026>::VRString[] = "IS";
const char TagToType<0x0020,0x0026>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0030> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0020,0x0030>::VRString[] = "DS";
const char TagToType<0x0020,0x0030>::VMString[] = "3";
template <> struct TagToType<0x0020,0x0032> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0020,0x0032>::VRString[] = "DS";
const char TagToType<0x0020,0x0032>::VMString[] = "3";
template <> struct TagToType<0x0020,0x0035> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM6 };
static const char VMString[];
};
const char TagToType<0x0020,0x0035>::VRString[] = "DS";
const char TagToType<0x0020,0x0035>::VMString[] = "6";
template <> struct TagToType<0x0020,0x0037> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM6 };
static const char VMString[];
};
const char TagToType<0x0020,0x0037>::VRString[] = "DS";
const char TagToType<0x0020,0x0037>::VMString[] = "6";
template <> struct TagToType<0x0020,0x0050> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0050>::VRString[] = "DS";
const char TagToType<0x0020,0x0050>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0052> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0052>::VRString[] = "UI";
const char TagToType<0x0020,0x0052>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0060> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0060>::VRString[] = "CS";
const char TagToType<0x0020,0x0060>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0062> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0062>::VRString[] = "CS";
const char TagToType<0x0020,0x0062>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0070> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0070>::VRString[] = "LO";
const char TagToType<0x0020,0x0070>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0080> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0020,0x0080>::VRString[] = "CS";
const char TagToType<0x0020,0x0080>::VMString[] = "1-n";
template <> struct TagToType<0x0020,0x0100> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0100>::VRString[] = "IS";
const char TagToType<0x0020,0x0100>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0105> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0105>::VRString[] = "IS";
const char TagToType<0x0020,0x0105>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0110> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0110>::VRString[] = "DS";
const char TagToType<0x0020,0x0110>::VMString[] = "1";
template <> struct TagToType<0x0020,0x0200> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x0200>::VRString[] = "UI";
const char TagToType<0x0020,0x0200>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1000> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1000>::VRString[] = "IS";
const char TagToType<0x0020,0x1000>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1001> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1001>::VRString[] = "IS";
const char TagToType<0x0020,0x1001>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1002> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1002>::VRString[] = "IS";
const char TagToType<0x0020,0x1002>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1003> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1003>::VRString[] = "IS";
const char TagToType<0x0020,0x1003>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1004> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1004>::VRString[] = "IS";
const char TagToType<0x0020,0x1004>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1005> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1005>::VRString[] = "IS";
const char TagToType<0x0020,0x1005>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0020,0x1020>::VRString[] = "CS";
const char TagToType<0x0020,0x1020>::VMString[] = "1-n";
template <> struct TagToType<0x0020,0x1040> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1040>::VRString[] = "LO";
const char TagToType<0x0020,0x1040>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1041> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1041>::VRString[] = "DS";
const char TagToType<0x0020,0x1041>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1070> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0020,0x1070>::VRString[] = "IS";
const char TagToType<0x0020,0x1070>::VMString[] = "1-n";
template <> struct TagToType<0x0020,0x1200> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1200>::VRString[] = "IS";
const char TagToType<0x0020,0x1200>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1202> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1202>::VRString[] = "IS";
const char TagToType<0x0020,0x1202>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1204> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1204>::VRString[] = "IS";
const char TagToType<0x0020,0x1204>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1206> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1206>::VRString[] = "IS";
const char TagToType<0x0020,0x1206>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1208> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1208>::VRString[] = "IS";
const char TagToType<0x0020,0x1208>::VMString[] = "1";
template <> struct TagToType<0x0020,0x1209> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x1209>::VRString[] = "IS";
const char TagToType<0x0020,0x1209>::VMString[] = "1";
template <> struct TagToType<0x0020,0x3401> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x3401>::VRString[] = "CS";
const char TagToType<0x0020,0x3401>::VMString[] = "1";
template <> struct TagToType<0x0020,0x3402> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x3402>::VRString[] = "CS";
const char TagToType<0x0020,0x3402>::VMString[] = "1";
template <> struct TagToType<0x0020,0x3403> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x3403>::VRString[] = "DA";
const char TagToType<0x0020,0x3403>::VMString[] = "1";
template <> struct TagToType<0x0020,0x3404> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x3404>::VRString[] = "LO";
const char TagToType<0x0020,0x3404>::VMString[] = "1";
template <> struct TagToType<0x0020,0x3405> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x3405>::VRString[] = "TM";
const char TagToType<0x0020,0x3405>::VMString[] = "1";
template <> struct TagToType<0x0020,0x3406> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x3406>::VRString[] = "LO";
const char TagToType<0x0020,0x3406>::VMString[] = "1";
template <> struct TagToType<0x0020,0x4000> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x4000>::VRString[] = "LT";
const char TagToType<0x0020,0x4000>::VMString[] = "1";
template <> struct TagToType<0x0020,0x5000> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0020,0x5000>::VRString[] = "AT";
const char TagToType<0x0020,0x5000>::VMString[] = "1-n";
template <> struct TagToType<0x0020,0x5002> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0020,0x5002>::VRString[] = "CS";
const char TagToType<0x0020,0x5002>::VMString[] = "1-n";
template <> struct TagToType<0x0020,0x9056> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9056>::VRString[] = "SH";
const char TagToType<0x0020,0x9056>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9057> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9057>::VRString[] = "UL";
const char TagToType<0x0020,0x9057>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9071> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9071>::VRString[] = "SQ";
const char TagToType<0x0020,0x9071>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9072> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9072>::VRString[] = "CS";
const char TagToType<0x0020,0x9072>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9111> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9111>::VRString[] = "SQ";
const char TagToType<0x0020,0x9111>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9113> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9113>::VRString[] = "SQ";
const char TagToType<0x0020,0x9113>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9116> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9116>::VRString[] = "SQ";
const char TagToType<0x0020,0x9116>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9128> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9128>::VRString[] = "UL";
const char TagToType<0x0020,0x9128>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9153> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9153>::VRString[] = "FD";
const char TagToType<0x0020,0x9153>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9156> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9156>::VRString[] = "US";
const char TagToType<0x0020,0x9156>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9157> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0020,0x9157>::VRString[] = "UL";
const char TagToType<0x0020,0x9157>::VMString[] = "1-n";
template <> struct TagToType<0x0020,0x9158> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9158>::VRString[] = "LT";
const char TagToType<0x0020,0x9158>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9161> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9161>::VRString[] = "UI";
const char TagToType<0x0020,0x9161>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9162> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9162>::VRString[] = "US";
const char TagToType<0x0020,0x9162>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9163> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9163>::VRString[] = "US";
const char TagToType<0x0020,0x9163>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9164> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9164>::VRString[] = "UI";
const char TagToType<0x0020,0x9164>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9165> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9165>::VRString[] = "AT";
const char TagToType<0x0020,0x9165>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9167> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9167>::VRString[] = "AT";
const char TagToType<0x0020,0x9167>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9213> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9213>::VRString[] = "LO";
const char TagToType<0x0020,0x9213>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9221> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9221>::VRString[] = "SQ";
const char TagToType<0x0020,0x9221>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9222> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9222>::VRString[] = "SQ";
const char TagToType<0x0020,0x9222>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9228> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9228>::VRString[] = "UL";
const char TagToType<0x0020,0x9228>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9238> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9238>::VRString[] = "LO";
const char TagToType<0x0020,0x9238>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9241> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9241>::VRString[] = "FL";
const char TagToType<0x0020,0x9241>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9245> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9245>::VRString[] = "FL";
const char TagToType<0x0020,0x9245>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9246> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9246>::VRString[] = "FL";
const char TagToType<0x0020,0x9246>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9247> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9247>::VRString[] = "CS";
const char TagToType<0x0020,0x9247>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9248> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9248>::VRString[] = "FL";
const char TagToType<0x0020,0x9248>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9249> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9249>::VRString[] = "CS";
const char TagToType<0x0020,0x9249>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9250> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9250>::VRString[] = "CS";
const char TagToType<0x0020,0x9250>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9251> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9251>::VRString[] = "FD";
const char TagToType<0x0020,0x9251>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9252> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9252>::VRString[] = "FD";
const char TagToType<0x0020,0x9252>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9253> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9253>::VRString[] = "SQ";
const char TagToType<0x0020,0x9253>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9254> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9254>::VRString[] = "FD";
const char TagToType<0x0020,0x9254>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9255> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9255>::VRString[] = "FD";
const char TagToType<0x0020,0x9255>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9256> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9256>::VRString[] = "FD";
const char TagToType<0x0020,0x9256>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9257> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9257>::VRString[] = "FD";
const char TagToType<0x0020,0x9257>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9421> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9421>::VRString[] = "LO";
const char TagToType<0x0020,0x9421>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9450> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9450>::VRString[] = "SQ";
const char TagToType<0x0020,0x9450>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9453> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9453>::VRString[] = "LO";
const char TagToType<0x0020,0x9453>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9518> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0020,0x9518>::VRString[] = "US";
const char TagToType<0x0020,0x9518>::VMString[] = "1-n";
template <> struct TagToType<0x0020,0x9529> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9529>::VRString[] = "SQ";
const char TagToType<0x0020,0x9529>::VMString[] = "1";
template <> struct TagToType<0x0020,0x9536> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0020,0x9536>::VRString[] = "US";
const char TagToType<0x0020,0x9536>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0001> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0001>::VRString[] = "US";
const char TagToType<0x0022,0x0001>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0002> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0022,0x0002>::VRString[] = "US";
const char TagToType<0x0022,0x0002>::VMString[] = "2";
template <> struct TagToType<0x0022,0x0003> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0003>::VRString[] = "US";
const char TagToType<0x0022,0x0003>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0004> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0022,0x0004>::VRString[] = "US";
const char TagToType<0x0022,0x0004>::VMString[] = "2";
template <> struct TagToType<0x0022,0x0005> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0005>::VRString[] = "CS";
const char TagToType<0x0022,0x0005>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0006> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0006>::VRString[] = "SQ";
const char TagToType<0x0022,0x0006>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0007> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0007>::VRString[] = "FL";
const char TagToType<0x0022,0x0007>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0008> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0008>::VRString[] = "FL";
const char TagToType<0x0022,0x0008>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0009> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0009>::VRString[] = "FL";
const char TagToType<0x0022,0x0009>::VMString[] = "1";
template <> struct TagToType<0x0022,0x000a> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x000a>::VRString[] = "FL";
const char TagToType<0x0022,0x000a>::VMString[] = "1";
template <> struct TagToType<0x0022,0x000b> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x000b>::VRString[] = "FL";
const char TagToType<0x0022,0x000b>::VMString[] = "1";
template <> struct TagToType<0x0022,0x000c> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x000c>::VRString[] = "FL";
const char TagToType<0x0022,0x000c>::VMString[] = "1";
template <> struct TagToType<0x0022,0x000d> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x000d>::VRString[] = "CS";
const char TagToType<0x0022,0x000d>::VMString[] = "1";
template <> struct TagToType<0x0022,0x000e> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x000e>::VRString[] = "FL";
const char TagToType<0x0022,0x000e>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0010> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0010>::VRString[] = "FL";
const char TagToType<0x0022,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0011> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0011>::VRString[] = "FL";
const char TagToType<0x0022,0x0011>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0012> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0012>::VRString[] = "FL";
const char TagToType<0x0022,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0013> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0013>::VRString[] = "FL";
const char TagToType<0x0022,0x0013>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0014> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0014>::VRString[] = "FL";
const char TagToType<0x0022,0x0014>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0015> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0015>::VRString[] = "SQ";
const char TagToType<0x0022,0x0015>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0016> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0016>::VRString[] = "SQ";
const char TagToType<0x0022,0x0016>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0017> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0017>::VRString[] = "SQ";
const char TagToType<0x0022,0x0017>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0018> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0018>::VRString[] = "SQ";
const char TagToType<0x0022,0x0018>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0019> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0019>::VRString[] = "SQ";
const char TagToType<0x0022,0x0019>::VMString[] = "1";
template <> struct TagToType<0x0022,0x001a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x001a>::VRString[] = "SQ";
const char TagToType<0x0022,0x001a>::VMString[] = "1";
template <> struct TagToType<0x0022,0x001b> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x001b>::VRString[] = "SQ";
const char TagToType<0x0022,0x001b>::VMString[] = "1";
template <> struct TagToType<0x0022,0x001c> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x001c>::VRString[] = "SQ";
const char TagToType<0x0022,0x001c>::VMString[] = "1";
template <> struct TagToType<0x0022,0x001d> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x001d>::VRString[] = "SQ";
const char TagToType<0x0022,0x001d>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0020> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0020>::VRString[] = "SQ";
const char TagToType<0x0022,0x0020>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0021> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0021>::VRString[] = "SQ";
const char TagToType<0x0022,0x0021>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0022> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0022>::VRString[] = "SQ";
const char TagToType<0x0022,0x0022>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0030> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0030>::VRString[] = "FL";
const char TagToType<0x0022,0x0030>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0031> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0031>::VRString[] = "SQ";
const char TagToType<0x0022,0x0031>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0032> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2_2n };
static const char VMString[];
};
const char TagToType<0x0022,0x0032>::VRString[] = "FL";
const char TagToType<0x0022,0x0032>::VMString[] = "2-2n";
template <> struct TagToType<0x0022,0x0035> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0035>::VRString[] = "FL";
const char TagToType<0x0022,0x0035>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0036> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0036>::VRString[] = "FL";
const char TagToType<0x0022,0x0036>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0037> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0037>::VRString[] = "FL";
const char TagToType<0x0022,0x0037>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0038> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0038>::VRString[] = "FL";
const char TagToType<0x0022,0x0038>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0039> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0039>::VRString[] = "CS";
const char TagToType<0x0022,0x0039>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0041> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0041>::VRString[] = "FL";
const char TagToType<0x0022,0x0041>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0042> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0042>::VRString[] = "SQ";
const char TagToType<0x0022,0x0042>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0048> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0048>::VRString[] = "FL";
const char TagToType<0x0022,0x0048>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0049> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0049>::VRString[] = "FL";
const char TagToType<0x0022,0x0049>::VMString[] = "1";
template <> struct TagToType<0x0022,0x004e> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x004e>::VRString[] = "DS";
const char TagToType<0x0022,0x004e>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0055> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0055>::VRString[] = "FL";
const char TagToType<0x0022,0x0055>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0056> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0056>::VRString[] = "FL";
const char TagToType<0x0022,0x0056>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0057> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0057>::VRString[] = "FL";
const char TagToType<0x0022,0x0057>::VMString[] = "1";
template <> struct TagToType<0x0022,0x0058> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0022,0x0058>::VRString[] = "SQ";
const char TagToType<0x0022,0x0058>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0002> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0002>::VRString[] = "US";
const char TagToType<0x0028,0x0002>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0003> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0003>::VRString[] = "US";
const char TagToType<0x0028,0x0003>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0004> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0004>::VRString[] = "CS";
const char TagToType<0x0028,0x0004>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0005> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0005>::VRString[] = "US";
const char TagToType<0x0028,0x0005>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0006> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0006>::VRString[] = "US";
const char TagToType<0x0028,0x0006>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0008> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0008>::VRString[] = "IS";
const char TagToType<0x0028,0x0008>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0009> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0009>::VRString[] = "AT";
const char TagToType<0x0028,0x0009>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x000a> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x000a>::VRString[] = "AT";
const char TagToType<0x0028,0x000a>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x0010> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0010>::VRString[] = "US";
const char TagToType<0x0028,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0011> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0011>::VRString[] = "US";
const char TagToType<0x0028,0x0011>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0012> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0012>::VRString[] = "US";
const char TagToType<0x0028,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0014> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0014>::VRString[] = "US";
const char TagToType<0x0028,0x0014>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0030> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0028,0x0030>::VRString[] = "DS";
const char TagToType<0x0028,0x0030>::VMString[] = "2";
template <> struct TagToType<0x0028,0x0031> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0028,0x0031>::VRString[] = "DS";
const char TagToType<0x0028,0x0031>::VMString[] = "2";
template <> struct TagToType<0x0028,0x0032> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0028,0x0032>::VRString[] = "DS";
const char TagToType<0x0028,0x0032>::VMString[] = "2";
template <> struct TagToType<0x0028,0x0034> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0028,0x0034>::VRString[] = "IS";
const char TagToType<0x0028,0x0034>::VMString[] = "2";
template <> struct TagToType<0x0028,0x0040> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0040>::VRString[] = "CS";
const char TagToType<0x0028,0x0040>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0050> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0050>::VRString[] = "LO";
const char TagToType<0x0028,0x0050>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x0051> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0051>::VRString[] = "CS";
const char TagToType<0x0028,0x0051>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x005f> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x005f>::VRString[] = "LO";
const char TagToType<0x0028,0x005f>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0060> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0060>::VRString[] = "CS";
const char TagToType<0x0028,0x0060>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0061> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0061>::VRString[] = "SH";
const char TagToType<0x0028,0x0061>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0062> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0062>::VRString[] = "LO";
const char TagToType<0x0028,0x0062>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0063> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0063>::VRString[] = "SH";
const char TagToType<0x0028,0x0063>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0065> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0065>::VRString[] = "CS";
const char TagToType<0x0028,0x0065>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x0066> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0066>::VRString[] = "AT";
const char TagToType<0x0028,0x0066>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x0068> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0068>::VRString[] = "US";
const char TagToType<0x0028,0x0068>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0069> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0069>::VRString[] = "US";
const char TagToType<0x0028,0x0069>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0070> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0070>::VRString[] = "US";
const char TagToType<0x0028,0x0070>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x0080> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0080>::VRString[] = "US";
const char TagToType<0x0028,0x0080>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0081> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0081>::VRString[] = "US";
const char TagToType<0x0028,0x0081>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0082> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0082>::VRString[] = "US";
const char TagToType<0x0028,0x0082>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x0090> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0090>::VRString[] = "CS";
const char TagToType<0x0028,0x0090>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0091> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0091>::VRString[] = "US";
const char TagToType<0x0028,0x0091>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0092> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0092>::VRString[] = "US";
const char TagToType<0x0028,0x0092>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0093> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0093>::VRString[] = "US";
const char TagToType<0x0028,0x0093>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0094> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0094>::VRString[] = "US";
const char TagToType<0x0028,0x0094>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0100> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0100>::VRString[] = "US";
const char TagToType<0x0028,0x0100>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0101> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0101>::VRString[] = "US";
const char TagToType<0x0028,0x0101>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0102> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0102>::VRString[] = "US";
const char TagToType<0x0028,0x0102>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0103> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0103>::VRString[] = "US";
const char TagToType<0x0028,0x0103>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0200> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0200>::VRString[] = "US";
const char TagToType<0x0028,0x0200>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0300> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0300>::VRString[] = "CS";
const char TagToType<0x0028,0x0300>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0301> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0301>::VRString[] = "CS";
const char TagToType<0x0028,0x0301>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0400> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0400>::VRString[] = "LO";
const char TagToType<0x0028,0x0400>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0401> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0401>::VRString[] = "LO";
const char TagToType<0x0028,0x0401>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0402> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0402>::VRString[] = "US";
const char TagToType<0x0028,0x0402>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0403> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0403>::VRString[] = "LO";
const char TagToType<0x0028,0x0403>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x0404> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0404>::VRString[] = "AT";
const char TagToType<0x0028,0x0404>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x0700> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0700>::VRString[] = "LO";
const char TagToType<0x0028,0x0700>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0701> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0701>::VRString[] = "CS";
const char TagToType<0x0028,0x0701>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x0702> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0702>::VRString[] = "AT";
const char TagToType<0x0028,0x0702>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x0710> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0710>::VRString[] = "US";
const char TagToType<0x0028,0x0710>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0720> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0720>::VRString[] = "US";
const char TagToType<0x0028,0x0720>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0721> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x0721>::VRString[] = "AT";
const char TagToType<0x0028,0x0721>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x0722> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0722>::VRString[] = "US";
const char TagToType<0x0028,0x0722>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0730> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0730>::VRString[] = "US";
const char TagToType<0x0028,0x0730>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0740> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0740>::VRString[] = "US";
const char TagToType<0x0028,0x0740>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0a02> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0a02>::VRString[] = "CS";
const char TagToType<0x0028,0x0a02>::VMString[] = "1";
template <> struct TagToType<0x0028,0x0a04> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x0a04>::VRString[] = "LO";
const char TagToType<0x0028,0x0a04>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1040> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1040>::VRString[] = "CS";
const char TagToType<0x0028,0x1040>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1041> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1041>::VRString[] = "SS";
const char TagToType<0x0028,0x1041>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1050> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x1050>::VRString[] = "DS";
const char TagToType<0x0028,0x1050>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x1051> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x1051>::VRString[] = "DS";
const char TagToType<0x0028,0x1051>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x1052> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1052>::VRString[] = "DS";
const char TagToType<0x0028,0x1052>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1053> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1053>::VRString[] = "DS";
const char TagToType<0x0028,0x1053>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1054> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1054>::VRString[] = "LO";
const char TagToType<0x0028,0x1054>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1055> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x1055>::VRString[] = "LO";
const char TagToType<0x0028,0x1055>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x1056> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1056>::VRString[] = "CS";
const char TagToType<0x0028,0x1056>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1080> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1080>::VRString[] = "CS";
const char TagToType<0x0028,0x1080>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1090> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1090>::VRString[] = "CS";
const char TagToType<0x0028,0x1090>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1199> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1199>::VRString[] = "UI";
const char TagToType<0x0028,0x1199>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1201> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1201>::VRString[] = "OW";
const char TagToType<0x0028,0x1201>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1202> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1202>::VRString[] = "OW";
const char TagToType<0x0028,0x1202>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1203> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1203>::VRString[] = "OW";
const char TagToType<0x0028,0x1203>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1211> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1211>::VRString[] = "OW";
const char TagToType<0x0028,0x1211>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1212> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1212>::VRString[] = "OW";
const char TagToType<0x0028,0x1212>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1213> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1213>::VRString[] = "OW";
const char TagToType<0x0028,0x1213>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1214> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1214>::VRString[] = "UI";
const char TagToType<0x0028,0x1214>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1221> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1221>::VRString[] = "OW";
const char TagToType<0x0028,0x1221>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1222> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1222>::VRString[] = "OW";
const char TagToType<0x0028,0x1222>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1223> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1223>::VRString[] = "OW";
const char TagToType<0x0028,0x1223>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1300> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1300>::VRString[] = "CS";
const char TagToType<0x0028,0x1300>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1350> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1350>::VRString[] = "CS";
const char TagToType<0x0028,0x1350>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1351> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1351>::VRString[] = "ST";
const char TagToType<0x0028,0x1351>::VMString[] = "1";
template <> struct TagToType<0x0028,0x1352> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x1352>::VRString[] = "SQ";
const char TagToType<0x0028,0x1352>::VMString[] = "1";
template <> struct TagToType<0x0028,0x135a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x135a>::VRString[] = "CS";
const char TagToType<0x0028,0x135a>::VMString[] = "1";
template <> struct TagToType<0x0028,0x2000> {
static const char VRString[];
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x2000>::VRString[] = "OB";
const char TagToType<0x0028,0x2000>::VMString[] = "1";
template <> struct TagToType<0x0028,0x2110> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x2110>::VRString[] = "CS";
const char TagToType<0x0028,0x2110>::VMString[] = "1";
template <> struct TagToType<0x0028,0x2112> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x2112>::VRString[] = "DS";
const char TagToType<0x0028,0x2112>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x2114> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x2114>::VRString[] = "CS";
const char TagToType<0x0028,0x2114>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x3000> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x3000>::VRString[] = "SQ";
const char TagToType<0x0028,0x3000>::VMString[] = "1";
template <> struct TagToType<0x0028,0x3003> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x3003>::VRString[] = "LO";
const char TagToType<0x0028,0x3003>::VMString[] = "1";
template <> struct TagToType<0x0028,0x3004> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x3004>::VRString[] = "LO";
const char TagToType<0x0028,0x3004>::VMString[] = "1";
template <> struct TagToType<0x0028,0x3010> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x3010>::VRString[] = "SQ";
const char TagToType<0x0028,0x3010>::VMString[] = "1";
template <> struct TagToType<0x0028,0x3110> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x3110>::VRString[] = "SQ";
const char TagToType<0x0028,0x3110>::VMString[] = "1";
template <> struct TagToType<0x0028,0x4000> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x4000>::VRString[] = "LT";
const char TagToType<0x0028,0x4000>::VMString[] = "1";
template <> struct TagToType<0x0028,0x5000> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x5000>::VRString[] = "SQ";
const char TagToType<0x0028,0x5000>::VMString[] = "1";
template <> struct TagToType<0x0028,0x6010> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x6010>::VRString[] = "US";
const char TagToType<0x0028,0x6010>::VMString[] = "1";
template <> struct TagToType<0x0028,0x6020> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x6020>::VRString[] = "US";
const char TagToType<0x0028,0x6020>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x6022> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x6022>::VRString[] = "LO";
const char TagToType<0x0028,0x6022>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x6023> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x6023>::VRString[] = "CS";
const char TagToType<0x0028,0x6023>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x6030> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x6030>::VRString[] = "US";
const char TagToType<0x0028,0x6030>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x6040> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x6040>::VRString[] = "US";
const char TagToType<0x0028,0x6040>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x6100> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x6100>::VRString[] = "SQ";
const char TagToType<0x0028,0x6100>::VMString[] = "1";
template <> struct TagToType<0x0028,0x6101> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x6101>::VRString[] = "CS";
const char TagToType<0x0028,0x6101>::VMString[] = "1";
template <> struct TagToType<0x0028,0x6102> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2_2n };
static const char VMString[];
};
const char TagToType<0x0028,0x6102>::VRString[] = "US";
const char TagToType<0x0028,0x6102>::VMString[] = "2-2n";
template <> struct TagToType<0x0028,0x6110> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x6110>::VRString[] = "US";
const char TagToType<0x0028,0x6110>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x6112> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x6112>::VRString[] = "US";
const char TagToType<0x0028,0x6112>::VMString[] = "1";
template <> struct TagToType<0x0028,0x6114> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0028,0x6114>::VRString[] = "FL";
const char TagToType<0x0028,0x6114>::VMString[] = "2";
template <> struct TagToType<0x0028,0x6120> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x6120>::VRString[] = "SS";
const char TagToType<0x0028,0x6120>::VMString[] = "1";
template <> struct TagToType<0x0028,0x6190> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x6190>::VRString[] = "ST";
const char TagToType<0x0028,0x6190>::VMString[] = "1";
template <> struct TagToType<0x0028,0x7fe0> {
static const char VRString[];
typedef VRToType<VR::UT>::Type Type;
enum { VRType = VR::UT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x7fe0>::VRString[] = "UT";
const char TagToType<0x0028,0x7fe0>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9001> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9001>::VRString[] = "UL";
const char TagToType<0x0028,0x9001>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9002> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9002>::VRString[] = "UL";
const char TagToType<0x0028,0x9002>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9003> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9003>::VRString[] = "CS";
const char TagToType<0x0028,0x9003>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9099> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9099>::VRString[] = "US";
const char TagToType<0x0028,0x9099>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9108> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9108>::VRString[] = "CS";
const char TagToType<0x0028,0x9108>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9110> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9110>::VRString[] = "SQ";
const char TagToType<0x0028,0x9110>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9132> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9132>::VRString[] = "SQ";
const char TagToType<0x0028,0x9132>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9145> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9145>::VRString[] = "SQ";
const char TagToType<0x0028,0x9145>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9235> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9235>::VRString[] = "CS";
const char TagToType<0x0028,0x9235>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9411> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9411>::VRString[] = "FL";
const char TagToType<0x0028,0x9411>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9415> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9415>::VRString[] = "SQ";
const char TagToType<0x0028,0x9415>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9416> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9416>::VRString[] = "US";
const char TagToType<0x0028,0x9416>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9422> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9422>::VRString[] = "SQ";
const char TagToType<0x0028,0x9422>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9443> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9443>::VRString[] = "SQ";
const char TagToType<0x0028,0x9443>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9444> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9444>::VRString[] = "CS";
const char TagToType<0x0028,0x9444>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9445> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9445>::VRString[] = "FL";
const char TagToType<0x0028,0x9445>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9446> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0028,0x9446>::VRString[] = "CS";
const char TagToType<0x0028,0x9446>::VMString[] = "1-n";
template <> struct TagToType<0x0028,0x9454> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9454>::VRString[] = "CS";
const char TagToType<0x0028,0x9454>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9474> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9474>::VRString[] = "CS";
const char TagToType<0x0028,0x9474>::VMString[] = "1";
template <> struct TagToType<0x0028,0x9520> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM16 };
static const char VMString[];
};
const char TagToType<0x0028,0x9520>::VRString[] = "DS";
const char TagToType<0x0028,0x9520>::VMString[] = "16";
template <> struct TagToType<0x0028,0x9537> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0028,0x9537>::VRString[] = "CS";
const char TagToType<0x0028,0x9537>::VMString[] = "1";
template <> struct TagToType<0x0032,0x000a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x000a>::VRString[] = "CS";
const char TagToType<0x0032,0x000a>::VMString[] = "1";
template <> struct TagToType<0x0032,0x000c> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x000c>::VRString[] = "CS";
const char TagToType<0x0032,0x000c>::VMString[] = "1";
template <> struct TagToType<0x0032,0x0012> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x0012>::VRString[] = "LO";
const char TagToType<0x0032,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0032,0x0032> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x0032>::VRString[] = "DA";
const char TagToType<0x0032,0x0032>::VMString[] = "1";
template <> struct TagToType<0x0032,0x0033> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x0033>::VRString[] = "TM";
const char TagToType<0x0032,0x0033>::VMString[] = "1";
template <> struct TagToType<0x0032,0x0034> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x0034>::VRString[] = "DA";
const char TagToType<0x0032,0x0034>::VMString[] = "1";
template <> struct TagToType<0x0032,0x0035> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x0035>::VRString[] = "TM";
const char TagToType<0x0032,0x0035>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1000> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1000>::VRString[] = "DA";
const char TagToType<0x0032,0x1000>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1001> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1001>::VRString[] = "TM";
const char TagToType<0x0032,0x1001>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1010> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1010>::VRString[] = "DA";
const char TagToType<0x0032,0x1010>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1011> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1011>::VRString[] = "TM";
const char TagToType<0x0032,0x1011>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1020> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1020>::VRString[] = "LO";
const char TagToType<0x0032,0x1020>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1021> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0032,0x1021>::VRString[] = "AE";
const char TagToType<0x0032,0x1021>::VMString[] = "1-n";
template <> struct TagToType<0x0032,0x1030> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1030>::VRString[] = "LO";
const char TagToType<0x0032,0x1030>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1031> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1031>::VRString[] = "SQ";
const char TagToType<0x0032,0x1031>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1032> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1032>::VRString[] = "PN";
const char TagToType<0x0032,0x1032>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1033> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1033>::VRString[] = "LO";
const char TagToType<0x0032,0x1033>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1040> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1040>::VRString[] = "DA";
const char TagToType<0x0032,0x1040>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1041> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1041>::VRString[] = "TM";
const char TagToType<0x0032,0x1041>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1050> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1050>::VRString[] = "DA";
const char TagToType<0x0032,0x1050>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1051> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1051>::VRString[] = "TM";
const char TagToType<0x0032,0x1051>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1055> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1055>::VRString[] = "CS";
const char TagToType<0x0032,0x1055>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1060> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1060>::VRString[] = "LO";
const char TagToType<0x0032,0x1060>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1064> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1064>::VRString[] = "SQ";
const char TagToType<0x0032,0x1064>::VMString[] = "1";
template <> struct TagToType<0x0032,0x1070> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x1070>::VRString[] = "LO";
const char TagToType<0x0032,0x1070>::VMString[] = "1";
template <> struct TagToType<0x0032,0x4000> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0032,0x4000>::VRString[] = "LT";
const char TagToType<0x0032,0x4000>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0004> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0004>::VRString[] = "SQ";
const char TagToType<0x0038,0x0004>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0008> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0008>::VRString[] = "CS";
const char TagToType<0x0038,0x0008>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0010> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0010>::VRString[] = "LO";
const char TagToType<0x0038,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0011> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0011>::VRString[] = "LO";
const char TagToType<0x0038,0x0011>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0016> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0016>::VRString[] = "LO";
const char TagToType<0x0038,0x0016>::VMString[] = "1";
template <> struct TagToType<0x0038,0x001a> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x001a>::VRString[] = "DA";
const char TagToType<0x0038,0x001a>::VMString[] = "1";
template <> struct TagToType<0x0038,0x001b> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x001b>::VRString[] = "TM";
const char TagToType<0x0038,0x001b>::VMString[] = "1";
template <> struct TagToType<0x0038,0x001c> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x001c>::VRString[] = "DA";
const char TagToType<0x0038,0x001c>::VMString[] = "1";
template <> struct TagToType<0x0038,0x001d> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x001d>::VRString[] = "TM";
const char TagToType<0x0038,0x001d>::VMString[] = "1";
template <> struct TagToType<0x0038,0x001e> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x001e>::VRString[] = "LO";
const char TagToType<0x0038,0x001e>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0020> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0020>::VRString[] = "DA";
const char TagToType<0x0038,0x0020>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0021> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0021>::VRString[] = "TM";
const char TagToType<0x0038,0x0021>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0030> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0030>::VRString[] = "DA";
const char TagToType<0x0038,0x0030>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0032> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0032>::VRString[] = "TM";
const char TagToType<0x0038,0x0032>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0040> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0040>::VRString[] = "LO";
const char TagToType<0x0038,0x0040>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0044> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0044>::VRString[] = "SQ";
const char TagToType<0x0038,0x0044>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0050> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0050>::VRString[] = "LO";
const char TagToType<0x0038,0x0050>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0060> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0060>::VRString[] = "LO";
const char TagToType<0x0038,0x0060>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0061> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0061>::VRString[] = "LO";
const char TagToType<0x0038,0x0061>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0062> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0062>::VRString[] = "LO";
const char TagToType<0x0038,0x0062>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0100> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0100>::VRString[] = "SQ";
const char TagToType<0x0038,0x0100>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0300> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0300>::VRString[] = "LO";
const char TagToType<0x0038,0x0300>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0400> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0400>::VRString[] = "LO";
const char TagToType<0x0038,0x0400>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0500> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0500>::VRString[] = "LO";
const char TagToType<0x0038,0x0500>::VMString[] = "1";
template <> struct TagToType<0x0038,0x0502> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x0502>::VRString[] = "SQ";
const char TagToType<0x0038,0x0502>::VMString[] = "1";
template <> struct TagToType<0x0038,0x4000> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0038,0x4000>::VRString[] = "LT";
const char TagToType<0x0038,0x4000>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0004> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0004>::VRString[] = "CS";
const char TagToType<0x003a,0x0004>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0005> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0005>::VRString[] = "US";
const char TagToType<0x003a,0x0005>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0010> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0010>::VRString[] = "UL";
const char TagToType<0x003a,0x0010>::VMString[] = "1";
template <> struct TagToType<0x003a,0x001a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x001a>::VRString[] = "DS";
const char TagToType<0x003a,0x001a>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0020> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0020>::VRString[] = "SH";
const char TagToType<0x003a,0x0020>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0200> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0200>::VRString[] = "SQ";
const char TagToType<0x003a,0x0200>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0202> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0202>::VRString[] = "IS";
const char TagToType<0x003a,0x0202>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0203> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0203>::VRString[] = "SH";
const char TagToType<0x003a,0x0203>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0205> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x003a,0x0205>::VRString[] = "CS";
const char TagToType<0x003a,0x0205>::VMString[] = "1-n";
template <> struct TagToType<0x003a,0x0208> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0208>::VRString[] = "SQ";
const char TagToType<0x003a,0x0208>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0209> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0209>::VRString[] = "SQ";
const char TagToType<0x003a,0x0209>::VMString[] = "1";
template <> struct TagToType<0x003a,0x020a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x020a>::VRString[] = "SQ";
const char TagToType<0x003a,0x020a>::VMString[] = "1";
template <> struct TagToType<0x003a,0x020c> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x020c>::VRString[] = "LO";
const char TagToType<0x003a,0x020c>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0210> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0210>::VRString[] = "DS";
const char TagToType<0x003a,0x0210>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0211> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0211>::VRString[] = "SQ";
const char TagToType<0x003a,0x0211>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0212> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0212>::VRString[] = "DS";
const char TagToType<0x003a,0x0212>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0213> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0213>::VRString[] = "DS";
const char TagToType<0x003a,0x0213>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0214> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0214>::VRString[] = "DS";
const char TagToType<0x003a,0x0214>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0215> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0215>::VRString[] = "DS";
const char TagToType<0x003a,0x0215>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0218> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0218>::VRString[] = "DS";
const char TagToType<0x003a,0x0218>::VMString[] = "1";
template <> struct TagToType<0x003a,0x021a> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x021a>::VRString[] = "US";
const char TagToType<0x003a,0x021a>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0220> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0220>::VRString[] = "DS";
const char TagToType<0x003a,0x0220>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0221> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0221>::VRString[] = "DS";
const char TagToType<0x003a,0x0221>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0222> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0222>::VRString[] = "DS";
const char TagToType<0x003a,0x0222>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0223> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0223>::VRString[] = "DS";
const char TagToType<0x003a,0x0223>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0230> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0230>::VRString[] = "FL";
const char TagToType<0x003a,0x0230>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0231> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x003a,0x0231>::VRString[] = "US";
const char TagToType<0x003a,0x0231>::VMString[] = "3";
template <> struct TagToType<0x003a,0x0240> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0240>::VRString[] = "SQ";
const char TagToType<0x003a,0x0240>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0241> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0241>::VRString[] = "US";
const char TagToType<0x003a,0x0241>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0242> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0242>::VRString[] = "SQ";
const char TagToType<0x003a,0x0242>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0244> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x003a,0x0244>::VRString[] = "US";
const char TagToType<0x003a,0x0244>::VMString[] = "3";
template <> struct TagToType<0x003a,0x0245> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0245>::VRString[] = "FL";
const char TagToType<0x003a,0x0245>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0246> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0246>::VRString[] = "CS";
const char TagToType<0x003a,0x0246>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0247> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0247>::VRString[] = "FL";
const char TagToType<0x003a,0x0247>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0248> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0248>::VRString[] = "FL";
const char TagToType<0x003a,0x0248>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0300> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0300>::VRString[] = "SQ";
const char TagToType<0x003a,0x0300>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0301> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0301>::VRString[] = "IS";
const char TagToType<0x003a,0x0301>::VMString[] = "1";
template <> struct TagToType<0x003a,0x0302> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x003a,0x0302>::VRString[] = "CS";
const char TagToType<0x003a,0x0302>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0001> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0040,0x0001>::VRString[] = "AE";
const char TagToType<0x0040,0x0001>::VMString[] = "1-n";
template <> struct TagToType<0x0040,0x0002> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0002>::VRString[] = "DA";
const char TagToType<0x0040,0x0002>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0003> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0003>::VRString[] = "TM";
const char TagToType<0x0040,0x0003>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0004> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0004>::VRString[] = "DA";
const char TagToType<0x0040,0x0004>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0005> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0005>::VRString[] = "TM";
const char TagToType<0x0040,0x0005>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0006> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0006>::VRString[] = "PN";
const char TagToType<0x0040,0x0006>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0007> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0007>::VRString[] = "LO";
const char TagToType<0x0040,0x0007>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0008> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0008>::VRString[] = "SQ";
const char TagToType<0x0040,0x0008>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0009> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0009>::VRString[] = "SH";
const char TagToType<0x0040,0x0009>::VMString[] = "1";
template <> struct TagToType<0x0040,0x000a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x000a>::VRString[] = "SQ";
const char TagToType<0x0040,0x000a>::VMString[] = "1";
template <> struct TagToType<0x0040,0x000b> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x000b>::VRString[] = "SQ";
const char TagToType<0x0040,0x000b>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0010> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0040,0x0010>::VRString[] = "SH";
const char TagToType<0x0040,0x0010>::VMString[] = "1-n";
template <> struct TagToType<0x0040,0x0011> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0011>::VRString[] = "SH";
const char TagToType<0x0040,0x0011>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0012> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0012>::VRString[] = "LO";
const char TagToType<0x0040,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0020>::VRString[] = "CS";
const char TagToType<0x0040,0x0020>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0100> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0100>::VRString[] = "SQ";
const char TagToType<0x0040,0x0100>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0220> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0220>::VRString[] = "SQ";
const char TagToType<0x0040,0x0220>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0241> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0241>::VRString[] = "AE";
const char TagToType<0x0040,0x0241>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0242> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0242>::VRString[] = "SH";
const char TagToType<0x0040,0x0242>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0243> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0243>::VRString[] = "SH";
const char TagToType<0x0040,0x0243>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0244> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0244>::VRString[] = "DA";
const char TagToType<0x0040,0x0244>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0245> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0245>::VRString[] = "TM";
const char TagToType<0x0040,0x0245>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0250> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0250>::VRString[] = "DA";
const char TagToType<0x0040,0x0250>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0251> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0251>::VRString[] = "TM";
const char TagToType<0x0040,0x0251>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0252> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0252>::VRString[] = "CS";
const char TagToType<0x0040,0x0252>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0253> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0253>::VRString[] = "SH";
const char TagToType<0x0040,0x0253>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0254> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0254>::VRString[] = "LO";
const char TagToType<0x0040,0x0254>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0255> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0255>::VRString[] = "LO";
const char TagToType<0x0040,0x0255>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0260> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0260>::VRString[] = "SQ";
const char TagToType<0x0040,0x0260>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0270> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0270>::VRString[] = "SQ";
const char TagToType<0x0040,0x0270>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0275> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0275>::VRString[] = "SQ";
const char TagToType<0x0040,0x0275>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0280> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0280>::VRString[] = "ST";
const char TagToType<0x0040,0x0280>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0281> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0281>::VRString[] = "SQ";
const char TagToType<0x0040,0x0281>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0293> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0293>::VRString[] = "SQ";
const char TagToType<0x0040,0x0293>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0294> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0294>::VRString[] = "DS";
const char TagToType<0x0040,0x0294>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0295> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0295>::VRString[] = "SQ";
const char TagToType<0x0040,0x0295>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0296> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0296>::VRString[] = "SQ";
const char TagToType<0x0040,0x0296>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0300> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0300>::VRString[] = "US";
const char TagToType<0x0040,0x0300>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0301> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0301>::VRString[] = "US";
const char TagToType<0x0040,0x0301>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0302> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0302>::VRString[] = "US";
const char TagToType<0x0040,0x0302>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0303> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_2 };
static const char VMString[];
};
const char TagToType<0x0040,0x0303>::VRString[] = "US";
const char TagToType<0x0040,0x0303>::VMString[] = "1-2";
template <> struct TagToType<0x0040,0x0306> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0306>::VRString[] = "DS";
const char TagToType<0x0040,0x0306>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0307> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0307>::VRString[] = "DS";
const char TagToType<0x0040,0x0307>::VMString[] = "1";
template <> struct TagToType<0x0040,0x030e> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x030e>::VRString[] = "SQ";
const char TagToType<0x0040,0x030e>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0310> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0310>::VRString[] = "ST";
const char TagToType<0x0040,0x0310>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0312> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0312>::VRString[] = "DS";
const char TagToType<0x0040,0x0312>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0314> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0314>::VRString[] = "DS";
const char TagToType<0x0040,0x0314>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0316> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0316>::VRString[] = "DS";
const char TagToType<0x0040,0x0316>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0318> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0318>::VRString[] = "CS";
const char TagToType<0x0040,0x0318>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0320> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0320>::VRString[] = "SQ";
const char TagToType<0x0040,0x0320>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0321> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0321>::VRString[] = "SQ";
const char TagToType<0x0040,0x0321>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0324> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0324>::VRString[] = "SQ";
const char TagToType<0x0040,0x0324>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0330> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0330>::VRString[] = "SQ";
const char TagToType<0x0040,0x0330>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0340> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0340>::VRString[] = "SQ";
const char TagToType<0x0040,0x0340>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0400> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0400>::VRString[] = "LT";
const char TagToType<0x0040,0x0400>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0440> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0440>::VRString[] = "SQ";
const char TagToType<0x0040,0x0440>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0441> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0441>::VRString[] = "SQ";
const char TagToType<0x0040,0x0441>::VMString[] = "1";
template <> struct TagToType<0x0040,0x050a> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x050a>::VRString[] = "LO";
const char TagToType<0x0040,0x050a>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0550> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0550>::VRString[] = "SQ";
const char TagToType<0x0040,0x0550>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0551> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0551>::VRString[] = "LO";
const char TagToType<0x0040,0x0551>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0552> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0552>::VRString[] = "SQ";
const char TagToType<0x0040,0x0552>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0553> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0553>::VRString[] = "ST";
const char TagToType<0x0040,0x0553>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0555> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0555>::VRString[] = "SQ";
const char TagToType<0x0040,0x0555>::VMString[] = "1";
template <> struct TagToType<0x0040,0x0556> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x0556>::VRString[] = "ST";
const char TagToType<0x0040,0x0556>::VMString[] = "1";
template <> struct TagToType<0x0040,0x059a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x059a>::VRString[] = "SQ";
const char TagToType<0x0040,0x059a>::VMString[] = "1";
template <> struct TagToType<0x0040,0x06fa> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x06fa>::VRString[] = "LO";
const char TagToType<0x0040,0x06fa>::VMString[] = "1";
template <> struct TagToType<0x0040,0x071a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x071a>::VRString[] = "SQ";
const char TagToType<0x0040,0x071a>::VMString[] = "1";
template <> struct TagToType<0x0040,0x072a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x072a>::VRString[] = "DS";
const char TagToType<0x0040,0x072a>::VMString[] = "1";
template <> struct TagToType<0x0040,0x073a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x073a>::VRString[] = "DS";
const char TagToType<0x0040,0x073a>::VMString[] = "1";
template <> struct TagToType<0x0040,0x074a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x074a>::VRString[] = "DS";
const char TagToType<0x0040,0x074a>::VMString[] = "1";
template <> struct TagToType<0x0040,0x08d8> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x08d8>::VRString[] = "SQ";
const char TagToType<0x0040,0x08d8>::VMString[] = "1";
template <> struct TagToType<0x0040,0x08da> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x08da>::VRString[] = "SQ";
const char TagToType<0x0040,0x08da>::VMString[] = "1";
template <> struct TagToType<0x0040,0x08ea> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x08ea>::VRString[] = "SQ";
const char TagToType<0x0040,0x08ea>::VMString[] = "1";
template <> struct TagToType<0x0040,0x09f8> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x09f8>::VRString[] = "SQ";
const char TagToType<0x0040,0x09f8>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1001> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1001>::VRString[] = "SH";
const char TagToType<0x0040,0x1001>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1002> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1002>::VRString[] = "LO";
const char TagToType<0x0040,0x1002>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1003> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1003>::VRString[] = "SH";
const char TagToType<0x0040,0x1003>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1004> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1004>::VRString[] = "LO";
const char TagToType<0x0040,0x1004>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1005> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1005>::VRString[] = "LO";
const char TagToType<0x0040,0x1005>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1006> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1006>::VRString[] = "SH";
const char TagToType<0x0040,0x1006>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1007> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1007>::VRString[] = "SH";
const char TagToType<0x0040,0x1007>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1008> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1008>::VRString[] = "LO";
const char TagToType<0x0040,0x1008>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1009> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1009>::VRString[] = "SH";
const char TagToType<0x0040,0x1009>::VMString[] = "1";
template <> struct TagToType<0x0040,0x100a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x100a>::VRString[] = "SQ";
const char TagToType<0x0040,0x100a>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1010> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0040,0x1010>::VRString[] = "PN";
const char TagToType<0x0040,0x1010>::VMString[] = "1-n";
template <> struct TagToType<0x0040,0x1011> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1011>::VRString[] = "SQ";
const char TagToType<0x0040,0x1011>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1101> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1101>::VRString[] = "SQ";
const char TagToType<0x0040,0x1101>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1102> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1102>::VRString[] = "ST";
const char TagToType<0x0040,0x1102>::VMString[] = "1";
template <> struct TagToType<0x0040,0x1103> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0040,0x1103>::VRString[] = "LO";
const char TagToType<0x0040,0x1103>::VMString[] = "1-n";
template <> struct TagToType<0x0040,0x1400> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x1400>::VRString[] = "LT";
const char TagToType<0x0040,0x1400>::VMString[] = "1";
template <> struct TagToType<0x0040,0x2001> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x2001>::VRString[] = "LO";
const char TagToType<0x0040,0x2001>::VMString[] = "1";
template <> struct TagToType<0x0040,0x2004> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x2004>::VRString[] = "DA";
const char TagToType<0x0040,0x2004>::VMString[] = "1";
template <> struct TagToType<0x0040,0x2005> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x2005>::VRString[] = "TM";
const char TagToType<0x0040,0x2005>::VMString[] = "1";
template <> struct TagToType<0x0040,0x2006> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x2006>::VRString[] = "SH";
const char TagToType<0x0040,0x2006>::VMString[] = "1";
template <> struct TagToType<0x0040,0x2007> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x2007>::VRString[] = "SH";
const char TagToType<0x0040,0x2007>::VMString[] = "1";
template <> struct TagToType<0x0040,0x2008> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x2008>::VRString[] = "PN";
const char TagToType<0x0040,0x2008>::VMString[] = "1";
template <> struct TagToType<0x0040,0x2009> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x2009>::VRString[] = "SH";
const char TagToType<0x0040,0x2009>::VMString[] = "1";
template <> struct TagToType<0x0040,0x2010> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x2010>::VRString[] = "SH";
const char TagToType<0x0040,0x2010>::VMString[] = "1";
template <> struct TagToType<0x0040,0x2016> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x2016>::VRString[] = "LO";
const char TagToType<0x0040,0x2016>::VMString[] = "1";
template <> struct TagToType<0x0040,0x2017> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x2017>::VRString[] = "LO";
const char TagToType<0x0040,0x2017>::VMString[] = "1";
template <> struct TagToType<0x0040,0x2400> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x2400>::VRString[] = "LT";
const char TagToType<0x0040,0x2400>::VMString[] = "1";
template <> struct TagToType<0x0040,0x3001> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x3001>::VRString[] = "LO";
const char TagToType<0x0040,0x3001>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4001> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4001>::VRString[] = "CS";
const char TagToType<0x0040,0x4001>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4002> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4002>::VRString[] = "CS";
const char TagToType<0x0040,0x4002>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4003> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4003>::VRString[] = "CS";
const char TagToType<0x0040,0x4003>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4004> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4004>::VRString[] = "SQ";
const char TagToType<0x0040,0x4004>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4005> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4005>::VRString[] = "DT";
const char TagToType<0x0040,0x4005>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4006> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4006>::VRString[] = "CS";
const char TagToType<0x0040,0x4006>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4007> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4007>::VRString[] = "SQ";
const char TagToType<0x0040,0x4007>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4009> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4009>::VRString[] = "SQ";
const char TagToType<0x0040,0x4009>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4010> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4010>::VRString[] = "DT";
const char TagToType<0x0040,0x4010>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4011> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4011>::VRString[] = "DT";
const char TagToType<0x0040,0x4011>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4015> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4015>::VRString[] = "SQ";
const char TagToType<0x0040,0x4015>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4016> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4016>::VRString[] = "SQ";
const char TagToType<0x0040,0x4016>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4018> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4018>::VRString[] = "SQ";
const char TagToType<0x0040,0x4018>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4019> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4019>::VRString[] = "SQ";
const char TagToType<0x0040,0x4019>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4020>::VRString[] = "CS";
const char TagToType<0x0040,0x4020>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4021> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4021>::VRString[] = "SQ";
const char TagToType<0x0040,0x4021>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4022> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4022>::VRString[] = "SQ";
const char TagToType<0x0040,0x4022>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4023> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4023>::VRString[] = "UI";
const char TagToType<0x0040,0x4023>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4025> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4025>::VRString[] = "SQ";
const char TagToType<0x0040,0x4025>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4026> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4026>::VRString[] = "SQ";
const char TagToType<0x0040,0x4026>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4027> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4027>::VRString[] = "SQ";
const char TagToType<0x0040,0x4027>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4028> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4028>::VRString[] = "SQ";
const char TagToType<0x0040,0x4028>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4029> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4029>::VRString[] = "SQ";
const char TagToType<0x0040,0x4029>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4030> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4030>::VRString[] = "SQ";
const char TagToType<0x0040,0x4030>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4031> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4031>::VRString[] = "SQ";
const char TagToType<0x0040,0x4031>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4032> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4032>::VRString[] = "SQ";
const char TagToType<0x0040,0x4032>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4033> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4033>::VRString[] = "SQ";
const char TagToType<0x0040,0x4033>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4034> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4034>::VRString[] = "SQ";
const char TagToType<0x0040,0x4034>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4035> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4035>::VRString[] = "SQ";
const char TagToType<0x0040,0x4035>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4036> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4036>::VRString[] = "LO";
const char TagToType<0x0040,0x4036>::VMString[] = "1";
template <> struct TagToType<0x0040,0x4037> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x4037>::VRString[] = "PN";
const char TagToType<0x0040,0x4037>::VMString[] = "1";
template <> struct TagToType<0x0040,0x8302> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x8302>::VRString[] = "DS";
const char TagToType<0x0040,0x8302>::VMString[] = "1";
template <> struct TagToType<0x0040,0x9094> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x9094>::VRString[] = "SQ";
const char TagToType<0x0040,0x9094>::VMString[] = "1";
template <> struct TagToType<0x0040,0x9096> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x9096>::VRString[] = "SQ";
const char TagToType<0x0040,0x9096>::VMString[] = "1";
template <> struct TagToType<0x0040,0x9098> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x9098>::VRString[] = "SQ";
const char TagToType<0x0040,0x9098>::VMString[] = "1";
template <> struct TagToType<0x0040,0x9210> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x9210>::VRString[] = "SH";
const char TagToType<0x0040,0x9210>::VMString[] = "1";
template <> struct TagToType<0x0040,0x9212> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0040,0x9212>::VRString[] = "FD";
const char TagToType<0x0040,0x9212>::VMString[] = "1-n";
template <> struct TagToType<0x0040,0x9224> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x9224>::VRString[] = "FD";
const char TagToType<0x0040,0x9224>::VMString[] = "1";
template <> struct TagToType<0x0040,0x9225> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0x9225>::VRString[] = "FD";
const char TagToType<0x0040,0x9225>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa010> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa010>::VRString[] = "CS";
const char TagToType<0x0040,0xa010>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa027> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa027>::VRString[] = "LO";
const char TagToType<0x0040,0xa027>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa030> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa030>::VRString[] = "DT";
const char TagToType<0x0040,0xa030>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa032> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa032>::VRString[] = "DT";
const char TagToType<0x0040,0xa032>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa040> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa040>::VRString[] = "CS";
const char TagToType<0x0040,0xa040>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa043> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa043>::VRString[] = "SQ";
const char TagToType<0x0040,0xa043>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa050> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa050>::VRString[] = "CS";
const char TagToType<0x0040,0xa050>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa073> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa073>::VRString[] = "SQ";
const char TagToType<0x0040,0xa073>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa075> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa075>::VRString[] = "PN";
const char TagToType<0x0040,0xa075>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa078> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa078>::VRString[] = "SQ";
const char TagToType<0x0040,0xa078>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa07a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa07a>::VRString[] = "SQ";
const char TagToType<0x0040,0xa07a>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa07c> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa07c>::VRString[] = "SQ";
const char TagToType<0x0040,0xa07c>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa080> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa080>::VRString[] = "CS";
const char TagToType<0x0040,0xa080>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa082> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa082>::VRString[] = "DT";
const char TagToType<0x0040,0xa082>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa084> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa084>::VRString[] = "CS";
const char TagToType<0x0040,0xa084>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa088> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa088>::VRString[] = "SQ";
const char TagToType<0x0040,0xa088>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa090> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa090>::VRString[] = "SQ";
const char TagToType<0x0040,0xa090>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa0b0> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2_2n };
static const char VMString[];
};
const char TagToType<0x0040,0xa0b0>::VRString[] = "US";
const char TagToType<0x0040,0xa0b0>::VMString[] = "2-2n";
template <> struct TagToType<0x0040,0xa120> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa120>::VRString[] = "DT";
const char TagToType<0x0040,0xa120>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa121> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa121>::VRString[] = "DA";
const char TagToType<0x0040,0xa121>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa122> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa122>::VRString[] = "TM";
const char TagToType<0x0040,0xa122>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa123> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa123>::VRString[] = "PN";
const char TagToType<0x0040,0xa123>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa124> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa124>::VRString[] = "UI";
const char TagToType<0x0040,0xa124>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa130> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa130>::VRString[] = "CS";
const char TagToType<0x0040,0xa130>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa132> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0040,0xa132>::VRString[] = "UL";
const char TagToType<0x0040,0xa132>::VMString[] = "1-n";
template <> struct TagToType<0x0040,0xa136> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0040,0xa136>::VRString[] = "US";
const char TagToType<0x0040,0xa136>::VMString[] = "1-n";
template <> struct TagToType<0x0040,0xa138> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0040,0xa138>::VRString[] = "DS";
const char TagToType<0x0040,0xa138>::VMString[] = "1-n";
template <> struct TagToType<0x0040,0xa13a> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0040,0xa13a>::VRString[] = "DT";
const char TagToType<0x0040,0xa13a>::VMString[] = "1-n";
template <> struct TagToType<0x0040,0xa160> {
static const char VRString[];
typedef VRToType<VR::UT>::Type Type;
enum { VRType = VR::UT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa160>::VRString[] = "UT";
const char TagToType<0x0040,0xa160>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa168> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa168>::VRString[] = "SQ";
const char TagToType<0x0040,0xa168>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa170> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa170>::VRString[] = "SQ";
const char TagToType<0x0040,0xa170>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa180> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa180>::VRString[] = "US";
const char TagToType<0x0040,0xa180>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa195> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa195>::VRString[] = "SQ";
const char TagToType<0x0040,0xa195>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa300> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa300>::VRString[] = "SQ";
const char TagToType<0x0040,0xa300>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa301> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa301>::VRString[] = "SQ";
const char TagToType<0x0040,0xa301>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa30a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0040,0xa30a>::VRString[] = "DS";
const char TagToType<0x0040,0xa30a>::VMString[] = "1-n";
template <> struct TagToType<0x0040,0xa353> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa353>::VRString[] = "ST";
const char TagToType<0x0040,0xa353>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa354> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa354>::VRString[] = "LO";
const char TagToType<0x0040,0xa354>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa360> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa360>::VRString[] = "SQ";
const char TagToType<0x0040,0xa360>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa370> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa370>::VRString[] = "SQ";
const char TagToType<0x0040,0xa370>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa372> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa372>::VRString[] = "SQ";
const char TagToType<0x0040,0xa372>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa375> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa375>::VRString[] = "SQ";
const char TagToType<0x0040,0xa375>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa385> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa385>::VRString[] = "SQ";
const char TagToType<0x0040,0xa385>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa390> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa390>::VRString[] = "SQ";
const char TagToType<0x0040,0xa390>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa491> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa491>::VRString[] = "CS";
const char TagToType<0x0040,0xa491>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa492> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa492>::VRString[] = "LO";
const char TagToType<0x0040,0xa492>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa493> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa493>::VRString[] = "CS";
const char TagToType<0x0040,0xa493>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa494> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa494>::VRString[] = "CS";
const char TagToType<0x0040,0xa494>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa504> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa504>::VRString[] = "SQ";
const char TagToType<0x0040,0xa504>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa525> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa525>::VRString[] = "SQ";
const char TagToType<0x0040,0xa525>::VMString[] = "1";
template <> struct TagToType<0x0040,0xa730> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xa730>::VRString[] = "SQ";
const char TagToType<0x0040,0xa730>::VMString[] = "1";
template <> struct TagToType<0x0040,0xb020> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xb020>::VRString[] = "SQ";
const char TagToType<0x0040,0xb020>::VMString[] = "1";
template <> struct TagToType<0x0040,0xdb00> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xdb00>::VRString[] = "CS";
const char TagToType<0x0040,0xdb00>::VMString[] = "1";
template <> struct TagToType<0x0040,0xdb06> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xdb06>::VRString[] = "DT";
const char TagToType<0x0040,0xdb06>::VMString[] = "1";
template <> struct TagToType<0x0040,0xdb07> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xdb07>::VRString[] = "DT";
const char TagToType<0x0040,0xdb07>::VMString[] = "1";
template <> struct TagToType<0x0040,0xdb0b> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xdb0b>::VRString[] = "CS";
const char TagToType<0x0040,0xdb0b>::VMString[] = "1";
template <> struct TagToType<0x0040,0xdb0c> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xdb0c>::VRString[] = "UI";
const char TagToType<0x0040,0xdb0c>::VMString[] = "1";
template <> struct TagToType<0x0040,0xdb0d> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xdb0d>::VRString[] = "UI";
const char TagToType<0x0040,0xdb0d>::VMString[] = "1";
template <> struct TagToType<0x0040,0xdb73> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0040,0xdb73>::VRString[] = "UL";
const char TagToType<0x0040,0xdb73>::VMString[] = "1-n";
template <> struct TagToType<0x0040,0xe001> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xe001>::VRString[] = "ST";
const char TagToType<0x0040,0xe001>::VMString[] = "1";
template <> struct TagToType<0x0040,0xe004> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xe004>::VRString[] = "DT";
const char TagToType<0x0040,0xe004>::VMString[] = "1";
template <> struct TagToType<0x0040,0xe006> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xe006>::VRString[] = "SQ";
const char TagToType<0x0040,0xe006>::VMString[] = "1";
template <> struct TagToType<0x0040,0xe010> {
static const char VRString[];
typedef VRToType<VR::UT>::Type Type;
enum { VRType = VR::UT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0040,0xe010>::VRString[] = "UT";
const char TagToType<0x0040,0xe010>::VMString[] = "1";
template <> struct TagToType<0x0042,0x0010> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0042,0x0010>::VRString[] = "ST";
const char TagToType<0x0042,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0042,0x0011> {
static const char VRString[];
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0042,0x0011>::VRString[] = "OB";
const char TagToType<0x0042,0x0011>::VMString[] = "1";
template <> struct TagToType<0x0042,0x0012> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0042,0x0012>::VRString[] = "LO";
const char TagToType<0x0042,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0042,0x0013> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0042,0x0013>::VRString[] = "SQ";
const char TagToType<0x0042,0x0013>::VMString[] = "1";
template <> struct TagToType<0x0042,0x0014> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0042,0x0014>::VRString[] = "LO";
const char TagToType<0x0042,0x0014>::VMString[] = "1-n";
template <> struct TagToType<0x0044,0x0001> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x0001>::VRString[] = "ST";
const char TagToType<0x0044,0x0001>::VMString[] = "1";
template <> struct TagToType<0x0044,0x0002> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x0002>::VRString[] = "CS";
const char TagToType<0x0044,0x0002>::VMString[] = "1";
template <> struct TagToType<0x0044,0x0003> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x0003>::VRString[] = "LT";
const char TagToType<0x0044,0x0003>::VMString[] = "1";
template <> struct TagToType<0x0044,0x0004> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x0004>::VRString[] = "DT";
const char TagToType<0x0044,0x0004>::VMString[] = "1";
template <> struct TagToType<0x0044,0x0007> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x0007>::VRString[] = "SQ";
const char TagToType<0x0044,0x0007>::VMString[] = "1";
template <> struct TagToType<0x0044,0x0008> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0044,0x0008>::VRString[] = "LO";
const char TagToType<0x0044,0x0008>::VMString[] = "1-n";
template <> struct TagToType<0x0044,0x0009> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x0009>::VRString[] = "LT";
const char TagToType<0x0044,0x0009>::VMString[] = "1";
template <> struct TagToType<0x0044,0x000a> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x000a>::VRString[] = "LO";
const char TagToType<0x0044,0x000a>::VMString[] = "1";
template <> struct TagToType<0x0044,0x000b> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x000b>::VRString[] = "DT";
const char TagToType<0x0044,0x000b>::VMString[] = "1";
template <> struct TagToType<0x0044,0x0010> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x0010>::VRString[] = "DT";
const char TagToType<0x0044,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0044,0x0011> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x0011>::VRString[] = "LO";
const char TagToType<0x0044,0x0011>::VMString[] = "1";
template <> struct TagToType<0x0044,0x0012> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x0012>::VRString[] = "LO";
const char TagToType<0x0044,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0044,0x0013> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x0013>::VRString[] = "SQ";
const char TagToType<0x0044,0x0013>::VMString[] = "1";
template <> struct TagToType<0x0044,0x0019> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0044,0x0019>::VRString[] = "SQ";
const char TagToType<0x0044,0x0019>::VMString[] = "1";
template <> struct TagToType<0x0050,0x0004> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0050,0x0004>::VRString[] = "CS";
const char TagToType<0x0050,0x0004>::VMString[] = "1";
template <> struct TagToType<0x0050,0x0010> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0050,0x0010>::VRString[] = "SQ";
const char TagToType<0x0050,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0050,0x0014> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0050,0x0014>::VRString[] = "DS";
const char TagToType<0x0050,0x0014>::VMString[] = "1";
template <> struct TagToType<0x0050,0x0016> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0050,0x0016>::VRString[] = "DS";
const char TagToType<0x0050,0x0016>::VMString[] = "1";
template <> struct TagToType<0x0050,0x0017> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0050,0x0017>::VRString[] = "CS";
const char TagToType<0x0050,0x0017>::VMString[] = "1";
template <> struct TagToType<0x0050,0x0018> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0050,0x0018>::VRString[] = "DS";
const char TagToType<0x0050,0x0018>::VMString[] = "1";
template <> struct TagToType<0x0050,0x0019> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0050,0x0019>::VRString[] = "DS";
const char TagToType<0x0050,0x0019>::VMString[] = "1";
template <> struct TagToType<0x0050,0x0020> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0050,0x0020>::VRString[] = "LO";
const char TagToType<0x0050,0x0020>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0010> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x0010>::VRString[] = "US";
const char TagToType<0x0054,0x0010>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x0011> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0011>::VRString[] = "US";
const char TagToType<0x0054,0x0011>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0012> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0012>::VRString[] = "SQ";
const char TagToType<0x0054,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0013> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0013>::VRString[] = "SQ";
const char TagToType<0x0054,0x0013>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0014> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0014>::VRString[] = "DS";
const char TagToType<0x0054,0x0014>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0015> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0015>::VRString[] = "DS";
const char TagToType<0x0054,0x0015>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0016> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0016>::VRString[] = "SQ";
const char TagToType<0x0054,0x0016>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0017> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0017>::VRString[] = "IS";
const char TagToType<0x0054,0x0017>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0018> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0018>::VRString[] = "SH";
const char TagToType<0x0054,0x0018>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0020> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x0020>::VRString[] = "US";
const char TagToType<0x0054,0x0020>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x0021> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0021>::VRString[] = "US";
const char TagToType<0x0054,0x0021>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0022> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0022>::VRString[] = "SQ";
const char TagToType<0x0054,0x0022>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0030> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x0030>::VRString[] = "US";
const char TagToType<0x0054,0x0030>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x0031> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0031>::VRString[] = "US";
const char TagToType<0x0054,0x0031>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0032> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0032>::VRString[] = "SQ";
const char TagToType<0x0054,0x0032>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0033> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0033>::VRString[] = "US";
const char TagToType<0x0054,0x0033>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0036> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0036>::VRString[] = "IS";
const char TagToType<0x0054,0x0036>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0038> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0038>::VRString[] = "IS";
const char TagToType<0x0054,0x0038>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0039> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0039>::VRString[] = "CS";
const char TagToType<0x0054,0x0039>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0050> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x0050>::VRString[] = "US";
const char TagToType<0x0054,0x0050>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x0051> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0051>::VRString[] = "US";
const char TagToType<0x0054,0x0051>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0052> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0052>::VRString[] = "SQ";
const char TagToType<0x0054,0x0052>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0053> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0053>::VRString[] = "US";
const char TagToType<0x0054,0x0053>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0060> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x0060>::VRString[] = "US";
const char TagToType<0x0054,0x0060>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x0061> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0061>::VRString[] = "US";
const char TagToType<0x0054,0x0061>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0062> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0062>::VRString[] = "SQ";
const char TagToType<0x0054,0x0062>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0063> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0063>::VRString[] = "SQ";
const char TagToType<0x0054,0x0063>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0070> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x0070>::VRString[] = "US";
const char TagToType<0x0054,0x0070>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x0071> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0071>::VRString[] = "US";
const char TagToType<0x0054,0x0071>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0072> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0072>::VRString[] = "SQ";
const char TagToType<0x0054,0x0072>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0073> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0073>::VRString[] = "DS";
const char TagToType<0x0054,0x0073>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0080> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x0080>::VRString[] = "US";
const char TagToType<0x0054,0x0080>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x0081> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0081>::VRString[] = "US";
const char TagToType<0x0054,0x0081>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0090> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x0090>::VRString[] = "US";
const char TagToType<0x0054,0x0090>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x0100> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x0100>::VRString[] = "US";
const char TagToType<0x0054,0x0100>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x0101> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0101>::VRString[] = "US";
const char TagToType<0x0054,0x0101>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0200> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0200>::VRString[] = "DS";
const char TagToType<0x0054,0x0200>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0202> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0202>::VRString[] = "CS";
const char TagToType<0x0054,0x0202>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0210> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x0210>::VRString[] = "IS";
const char TagToType<0x0054,0x0210>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x0211> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0211>::VRString[] = "US";
const char TagToType<0x0054,0x0211>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0220> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0220>::VRString[] = "SQ";
const char TagToType<0x0054,0x0220>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0222> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0222>::VRString[] = "SQ";
const char TagToType<0x0054,0x0222>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0300> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0300>::VRString[] = "SQ";
const char TagToType<0x0054,0x0300>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0302> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0302>::VRString[] = "SQ";
const char TagToType<0x0054,0x0302>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0304> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0304>::VRString[] = "SQ";
const char TagToType<0x0054,0x0304>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0306> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0306>::VRString[] = "SQ";
const char TagToType<0x0054,0x0306>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0308> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0308>::VRString[] = "US";
const char TagToType<0x0054,0x0308>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0400> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0400>::VRString[] = "SH";
const char TagToType<0x0054,0x0400>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0410> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0410>::VRString[] = "SQ";
const char TagToType<0x0054,0x0410>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0412> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0412>::VRString[] = "SQ";
const char TagToType<0x0054,0x0412>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0414> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0414>::VRString[] = "SQ";
const char TagToType<0x0054,0x0414>::VMString[] = "1";
template <> struct TagToType<0x0054,0x0500> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x0500>::VRString[] = "CS";
const char TagToType<0x0054,0x0500>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1000> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0054,0x1000>::VRString[] = "CS";
const char TagToType<0x0054,0x1000>::VMString[] = "2";
template <> struct TagToType<0x0054,0x1001> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1001>::VRString[] = "CS";
const char TagToType<0x0054,0x1001>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1002> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1002>::VRString[] = "CS";
const char TagToType<0x0054,0x1002>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1004> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1004>::VRString[] = "CS";
const char TagToType<0x0054,0x1004>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1100> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1100>::VRString[] = "CS";
const char TagToType<0x0054,0x1100>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1101> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1101>::VRString[] = "LO";
const char TagToType<0x0054,0x1101>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1102> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1102>::VRString[] = "CS";
const char TagToType<0x0054,0x1102>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1103> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1103>::VRString[] = "LO";
const char TagToType<0x0054,0x1103>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1104> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1104>::VRString[] = "LO";
const char TagToType<0x0054,0x1104>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1105> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1105>::VRString[] = "LO";
const char TagToType<0x0054,0x1105>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1200> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1200>::VRString[] = "DS";
const char TagToType<0x0054,0x1200>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1201> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0054,0x1201>::VRString[] = "IS";
const char TagToType<0x0054,0x1201>::VMString[] = "2";
template <> struct TagToType<0x0054,0x1202> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1202>::VRString[] = "IS";
const char TagToType<0x0054,0x1202>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1203> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0054,0x1203>::VRString[] = "DS";
const char TagToType<0x0054,0x1203>::VMString[] = "2";
template <> struct TagToType<0x0054,0x1210> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1210>::VRString[] = "DS";
const char TagToType<0x0054,0x1210>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1220> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x1220>::VRString[] = "CS";
const char TagToType<0x0054,0x1220>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x1300> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1300>::VRString[] = "DS";
const char TagToType<0x0054,0x1300>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1310> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1310>::VRString[] = "IS";
const char TagToType<0x0054,0x1310>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1311> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x1311>::VRString[] = "IS";
const char TagToType<0x0054,0x1311>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x1320> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1320>::VRString[] = "DS";
const char TagToType<0x0054,0x1320>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1321> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1321>::VRString[] = "DS";
const char TagToType<0x0054,0x1321>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1322> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1322>::VRString[] = "DS";
const char TagToType<0x0054,0x1322>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1323> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1323>::VRString[] = "DS";
const char TagToType<0x0054,0x1323>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1324> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1324>::VRString[] = "DS";
const char TagToType<0x0054,0x1324>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1330> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1330>::VRString[] = "US";
const char TagToType<0x0054,0x1330>::VMString[] = "1";
template <> struct TagToType<0x0054,0x1400> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0054,0x1400>::VRString[] = "CS";
const char TagToType<0x0054,0x1400>::VMString[] = "1-n";
template <> struct TagToType<0x0054,0x1401> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0054,0x1401>::VRString[] = "CS";
const char TagToType<0x0054,0x1401>::VMString[] = "1";
template <> struct TagToType<0x0060,0x3000> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0060,0x3000>::VRString[] = "SQ";
const char TagToType<0x0060,0x3000>::VMString[] = "1";
template <> struct TagToType<0x0060,0x3002> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0060,0x3002>::VRString[] = "US";
const char TagToType<0x0060,0x3002>::VMString[] = "1";
template <> struct TagToType<0x0060,0x3008> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0060,0x3008>::VRString[] = "US";
const char TagToType<0x0060,0x3008>::VMString[] = "1";
template <> struct TagToType<0x0060,0x3010> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0060,0x3010>::VRString[] = "LO";
const char TagToType<0x0060,0x3010>::VMString[] = "1";
template <> struct TagToType<0x0060,0x3020> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0060,0x3020>::VRString[] = "UL";
const char TagToType<0x0060,0x3020>::VMString[] = "1-n";
template <> struct TagToType<0x0062,0x0001> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x0001>::VRString[] = "CS";
const char TagToType<0x0062,0x0001>::VMString[] = "1";
template <> struct TagToType<0x0062,0x0002> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x0002>::VRString[] = "SQ";
const char TagToType<0x0062,0x0002>::VMString[] = "1";
template <> struct TagToType<0x0062,0x0003> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x0003>::VRString[] = "SQ";
const char TagToType<0x0062,0x0003>::VMString[] = "1";
template <> struct TagToType<0x0062,0x0004> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x0004>::VRString[] = "US";
const char TagToType<0x0062,0x0004>::VMString[] = "1";
template <> struct TagToType<0x0062,0x0005> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x0005>::VRString[] = "LO";
const char TagToType<0x0062,0x0005>::VMString[] = "1";
template <> struct TagToType<0x0062,0x0006> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x0006>::VRString[] = "ST";
const char TagToType<0x0062,0x0006>::VMString[] = "1";
template <> struct TagToType<0x0062,0x0008> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x0008>::VRString[] = "CS";
const char TagToType<0x0062,0x0008>::VMString[] = "1";
template <> struct TagToType<0x0062,0x0009> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x0009>::VRString[] = "LO";
const char TagToType<0x0062,0x0009>::VMString[] = "1";
template <> struct TagToType<0x0062,0x000a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x000a>::VRString[] = "SQ";
const char TagToType<0x0062,0x000a>::VMString[] = "1";
template <> struct TagToType<0x0062,0x000b> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0062,0x000b>::VRString[] = "US";
const char TagToType<0x0062,0x000b>::VMString[] = "1-n";
template <> struct TagToType<0x0062,0x000c> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x000c>::VRString[] = "US";
const char TagToType<0x0062,0x000c>::VMString[] = "1";
template <> struct TagToType<0x0062,0x000d> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0062,0x000d>::VRString[] = "US";
const char TagToType<0x0062,0x000d>::VMString[] = "3";
template <> struct TagToType<0x0062,0x000e> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x000e>::VRString[] = "US";
const char TagToType<0x0062,0x000e>::VMString[] = "1";
template <> struct TagToType<0x0062,0x000f> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x000f>::VRString[] = "SQ";
const char TagToType<0x0062,0x000f>::VMString[] = "1";
template <> struct TagToType<0x0062,0x0010> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0062,0x0010>::VRString[] = "CS";
const char TagToType<0x0062,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0064,0x0002> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0064,0x0002>::VRString[] = "SQ";
const char TagToType<0x0064,0x0002>::VMString[] = "1";
template <> struct TagToType<0x0064,0x0003> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0064,0x0003>::VRString[] = "UI";
const char TagToType<0x0064,0x0003>::VMString[] = "1";
template <> struct TagToType<0x0064,0x0005> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0064,0x0005>::VRString[] = "SQ";
const char TagToType<0x0064,0x0005>::VMString[] = "1";
template <> struct TagToType<0x0064,0x0007> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0064,0x0007>::VRString[] = "UL";
const char TagToType<0x0064,0x0007>::VMString[] = "3";
template <> struct TagToType<0x0064,0x0008> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0064,0x0008>::VRString[] = "FD";
const char TagToType<0x0064,0x0008>::VMString[] = "3";
template <> struct TagToType<0x0064,0x0009> {
static const char VRString[];
typedef VRToType<VR::OF>::Type Type;
enum { VRType = VR::OF };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0064,0x0009>::VRString[] = "OF";
const char TagToType<0x0064,0x0009>::VMString[] = "1";
template <> struct TagToType<0x0064,0x000f> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0064,0x000f>::VRString[] = "SQ";
const char TagToType<0x0064,0x000f>::VMString[] = "1";
template <> struct TagToType<0x0064,0x0010> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0064,0x0010>::VRString[] = "SQ";
const char TagToType<0x0064,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0001> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0001>::VRString[] = "SQ";
const char TagToType<0x0070,0x0001>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0002> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0002>::VRString[] = "CS";
const char TagToType<0x0070,0x0002>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0003> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0003>::VRString[] = "CS";
const char TagToType<0x0070,0x0003>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0004> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0004>::VRString[] = "CS";
const char TagToType<0x0070,0x0004>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0005> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0005>::VRString[] = "CS";
const char TagToType<0x0070,0x0005>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0006> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0006>::VRString[] = "ST";
const char TagToType<0x0070,0x0006>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0008> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0008>::VRString[] = "SQ";
const char TagToType<0x0070,0x0008>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0009> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0009>::VRString[] = "SQ";
const char TagToType<0x0070,0x0009>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0010> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0070,0x0010>::VRString[] = "FL";
const char TagToType<0x0070,0x0010>::VMString[] = "2";
template <> struct TagToType<0x0070,0x0011> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0070,0x0011>::VRString[] = "FL";
const char TagToType<0x0070,0x0011>::VMString[] = "2";
template <> struct TagToType<0x0070,0x0012> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0012>::VRString[] = "CS";
const char TagToType<0x0070,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0014> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0070,0x0014>::VRString[] = "FL";
const char TagToType<0x0070,0x0014>::VMString[] = "2";
template <> struct TagToType<0x0070,0x0015> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0015>::VRString[] = "CS";
const char TagToType<0x0070,0x0015>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0020> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0020>::VRString[] = "US";
const char TagToType<0x0070,0x0020>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0021> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0021>::VRString[] = "US";
const char TagToType<0x0070,0x0021>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0022> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2_n };
static const char VMString[];
};
const char TagToType<0x0070,0x0022>::VRString[] = "FL";
const char TagToType<0x0070,0x0022>::VMString[] = "2-n";
template <> struct TagToType<0x0070,0x0023> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0023>::VRString[] = "CS";
const char TagToType<0x0070,0x0023>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0024> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0024>::VRString[] = "CS";
const char TagToType<0x0070,0x0024>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0040> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0040>::VRString[] = "IS";
const char TagToType<0x0070,0x0040>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0041> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0041>::VRString[] = "CS";
const char TagToType<0x0070,0x0041>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0042> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0042>::VRString[] = "US";
const char TagToType<0x0070,0x0042>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0050> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0070,0x0050>::VRString[] = "US";
const char TagToType<0x0070,0x0050>::VMString[] = "2";
template <> struct TagToType<0x0070,0x0051> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0070,0x0051>::VRString[] = "US";
const char TagToType<0x0070,0x0051>::VMString[] = "2";
template <> struct TagToType<0x0070,0x0052> {
static const char VRString[];
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0070,0x0052>::VRString[] = "SL";
const char TagToType<0x0070,0x0052>::VMString[] = "2";
template <> struct TagToType<0x0070,0x0053> {
static const char VRString[];
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0070,0x0053>::VRString[] = "SL";
const char TagToType<0x0070,0x0053>::VMString[] = "2";
template <> struct TagToType<0x0070,0x005a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x005a>::VRString[] = "SQ";
const char TagToType<0x0070,0x005a>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0060> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0060>::VRString[] = "SQ";
const char TagToType<0x0070,0x0060>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0062> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0062>::VRString[] = "IS";
const char TagToType<0x0070,0x0062>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0066> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0066>::VRString[] = "US";
const char TagToType<0x0070,0x0066>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0067> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0070,0x0067>::VRString[] = "US";
const char TagToType<0x0070,0x0067>::VMString[] = "3";
template <> struct TagToType<0x0070,0x0068> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0068>::VRString[] = "LO";
const char TagToType<0x0070,0x0068>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0080> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0080>::VRString[] = "CS";
const char TagToType<0x0070,0x0080>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0081> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0081>::VRString[] = "LO";
const char TagToType<0x0070,0x0081>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0082> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0082>::VRString[] = "DA";
const char TagToType<0x0070,0x0082>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0083> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0083>::VRString[] = "TM";
const char TagToType<0x0070,0x0083>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0084> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0084>::VRString[] = "PN";
const char TagToType<0x0070,0x0084>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0086> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0086>::VRString[] = "SQ";
const char TagToType<0x0070,0x0086>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0100> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0100>::VRString[] = "CS";
const char TagToType<0x0070,0x0100>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0101> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0070,0x0101>::VRString[] = "DS";
const char TagToType<0x0070,0x0101>::VMString[] = "2";
template <> struct TagToType<0x0070,0x0102> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0070,0x0102>::VRString[] = "IS";
const char TagToType<0x0070,0x0102>::VMString[] = "2";
template <> struct TagToType<0x0070,0x0103> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0103>::VRString[] = "FL";
const char TagToType<0x0070,0x0103>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0306> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0306>::VRString[] = "CS";
const char TagToType<0x0070,0x0306>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0308> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0308>::VRString[] = "SQ";
const char TagToType<0x0070,0x0308>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0309> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0309>::VRString[] = "SQ";
const char TagToType<0x0070,0x0309>::VMString[] = "1";
template <> struct TagToType<0x0070,0x030a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x030a>::VRString[] = "SQ";
const char TagToType<0x0070,0x030a>::VMString[] = "1";
template <> struct TagToType<0x0070,0x030c> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x030c>::VRString[] = "CS";
const char TagToType<0x0070,0x030c>::VMString[] = "1";
template <> struct TagToType<0x0070,0x030d> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x030d>::VRString[] = "SQ";
const char TagToType<0x0070,0x030d>::VMString[] = "1";
template <> struct TagToType<0x0070,0x030f> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x030f>::VRString[] = "ST";
const char TagToType<0x0070,0x030f>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0310> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0310>::VRString[] = "SH";
const char TagToType<0x0070,0x0310>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0311> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0311>::VRString[] = "SQ";
const char TagToType<0x0070,0x0311>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0312> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0312>::VRString[] = "FD";
const char TagToType<0x0070,0x0312>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0314> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0314>::VRString[] = "SQ";
const char TagToType<0x0070,0x0314>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0318> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0318>::VRString[] = "SQ";
const char TagToType<0x0070,0x0318>::VMString[] = "1";
template <> struct TagToType<0x0070,0x031a> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x031a>::VRString[] = "UI";
const char TagToType<0x0070,0x031a>::VMString[] = "1";
template <> struct TagToType<0x0070,0x031c> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x031c>::VRString[] = "SQ";
const char TagToType<0x0070,0x031c>::VMString[] = "1";
template <> struct TagToType<0x0070,0x031e> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x031e>::VRString[] = "SQ";
const char TagToType<0x0070,0x031e>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0401> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x0070,0x0401>::VRString[] = "US";
const char TagToType<0x0070,0x0401>::VMString[] = "3";
template <> struct TagToType<0x0070,0x0402> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0402>::VRString[] = "SQ";
const char TagToType<0x0070,0x0402>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0403> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0403>::VRString[] = "FL";
const char TagToType<0x0070,0x0403>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0404> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0404>::VRString[] = "SQ";
const char TagToType<0x0070,0x0404>::VMString[] = "1";
template <> struct TagToType<0x0070,0x0405> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0070,0x0405>::VRString[] = "CS";
const char TagToType<0x0070,0x0405>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0002> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0002>::VRString[] = "SH";
const char TagToType<0x0072,0x0002>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0004> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0004>::VRString[] = "LO";
const char TagToType<0x0072,0x0004>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0006> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0006>::VRString[] = "CS";
const char TagToType<0x0072,0x0006>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0008> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0008>::VRString[] = "LO";
const char TagToType<0x0072,0x0008>::VMString[] = "1";
template <> struct TagToType<0x0072,0x000a> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x000a>::VRString[] = "DT";
const char TagToType<0x0072,0x000a>::VMString[] = "1";
template <> struct TagToType<0x0072,0x000c> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x000c>::VRString[] = "SQ";
const char TagToType<0x0072,0x000c>::VMString[] = "1";
template <> struct TagToType<0x0072,0x000e> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x000e>::VRString[] = "SQ";
const char TagToType<0x0072,0x000e>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0010> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0010>::VRString[] = "LO";
const char TagToType<0x0072,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0012> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0012>::VRString[] = "SQ";
const char TagToType<0x0072,0x0012>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0014> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0014>::VRString[] = "US";
const char TagToType<0x0072,0x0014>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0020> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0020>::VRString[] = "SQ";
const char TagToType<0x0072,0x0020>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0022> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0022>::VRString[] = "SQ";
const char TagToType<0x0072,0x0022>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0024> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0024>::VRString[] = "CS";
const char TagToType<0x0072,0x0024>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0026> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0026>::VRString[] = "AT";
const char TagToType<0x0072,0x0026>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0028> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0028>::VRString[] = "US";
const char TagToType<0x0072,0x0028>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0030> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0030>::VRString[] = "SQ";
const char TagToType<0x0072,0x0030>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0032> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0032>::VRString[] = "US";
const char TagToType<0x0072,0x0032>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0034> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0034>::VRString[] = "CS";
const char TagToType<0x0072,0x0034>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0038> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0072,0x0038>::VRString[] = "US";
const char TagToType<0x0072,0x0038>::VMString[] = "2";
template <> struct TagToType<0x0072,0x003a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x003a>::VRString[] = "CS";
const char TagToType<0x0072,0x003a>::VMString[] = "1";
template <> struct TagToType<0x0072,0x003c> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0072,0x003c>::VRString[] = "SS";
const char TagToType<0x0072,0x003c>::VMString[] = "2";
template <> struct TagToType<0x0072,0x003e> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x003e>::VRString[] = "SQ";
const char TagToType<0x0072,0x003e>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0040> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0040>::VRString[] = "LO";
const char TagToType<0x0072,0x0040>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0050> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0050>::VRString[] = "CS";
const char TagToType<0x0072,0x0050>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0052> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0052>::VRString[] = "AT";
const char TagToType<0x0072,0x0052>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0054> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0054>::VRString[] = "LO";
const char TagToType<0x0072,0x0054>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0056> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0056>::VRString[] = "LO";
const char TagToType<0x0072,0x0056>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0060> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x0060>::VRString[] = "AT";
const char TagToType<0x0072,0x0060>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x0062> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x0062>::VRString[] = "CS";
const char TagToType<0x0072,0x0062>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x0064> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x0064>::VRString[] = "IS";
const char TagToType<0x0072,0x0064>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x0066> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x0066>::VRString[] = "LO";
const char TagToType<0x0072,0x0066>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x0068> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0068>::VRString[] = "LT";
const char TagToType<0x0072,0x0068>::VMString[] = "1";
template <> struct TagToType<0x0072,0x006a> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x006a>::VRString[] = "PN";
const char TagToType<0x0072,0x006a>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x006c> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x006c>::VRString[] = "SH";
const char TagToType<0x0072,0x006c>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x006e> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x006e>::VRString[] = "ST";
const char TagToType<0x0072,0x006e>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0070> {
static const char VRString[];
typedef VRToType<VR::UT>::Type Type;
enum { VRType = VR::UT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0070>::VRString[] = "UT";
const char TagToType<0x0072,0x0070>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0072> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x0072>::VRString[] = "DS";
const char TagToType<0x0072,0x0072>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x0074> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x0074>::VRString[] = "FD";
const char TagToType<0x0072,0x0074>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x0076> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x0076>::VRString[] = "FL";
const char TagToType<0x0072,0x0076>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x0078> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x0078>::VRString[] = "UL";
const char TagToType<0x0072,0x0078>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x007a> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x007a>::VRString[] = "US";
const char TagToType<0x0072,0x007a>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x007c> {
static const char VRString[];
typedef VRToType<VR::SL>::Type Type;
enum { VRType = VR::SL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x007c>::VRString[] = "SL";
const char TagToType<0x0072,0x007c>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x007e> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x007e>::VRString[] = "SS";
const char TagToType<0x0072,0x007e>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x0080> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0080>::VRString[] = "SQ";
const char TagToType<0x0072,0x0080>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0100> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0100>::VRString[] = "US";
const char TagToType<0x0072,0x0100>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0102> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0102>::VRString[] = "SQ";
const char TagToType<0x0072,0x0102>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0104> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0104>::VRString[] = "US";
const char TagToType<0x0072,0x0104>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0106> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0106>::VRString[] = "US";
const char TagToType<0x0072,0x0106>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0108> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM4 };
static const char VMString[];
};
const char TagToType<0x0072,0x0108>::VRString[] = "FD";
const char TagToType<0x0072,0x0108>::VMString[] = "4";
template <> struct TagToType<0x0072,0x010a> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x010a>::VRString[] = "US";
const char TagToType<0x0072,0x010a>::VMString[] = "1";
template <> struct TagToType<0x0072,0x010c> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x010c>::VRString[] = "US";
const char TagToType<0x0072,0x010c>::VMString[] = "1";
template <> struct TagToType<0x0072,0x010e> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x010e>::VRString[] = "US";
const char TagToType<0x0072,0x010e>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0200> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0200>::VRString[] = "SQ";
const char TagToType<0x0072,0x0200>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0202> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0202>::VRString[] = "US";
const char TagToType<0x0072,0x0202>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0203> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0203>::VRString[] = "LO";
const char TagToType<0x0072,0x0203>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0204> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0204>::VRString[] = "US";
const char TagToType<0x0072,0x0204>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0206> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0206>::VRString[] = "LO";
const char TagToType<0x0072,0x0206>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0208> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0208>::VRString[] = "CS";
const char TagToType<0x0072,0x0208>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0210> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0210>::VRString[] = "SQ";
const char TagToType<0x0072,0x0210>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0212> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM2_n };
static const char VMString[];
};
const char TagToType<0x0072,0x0212>::VRString[] = "US";
const char TagToType<0x0072,0x0212>::VMString[] = "2-n";
template <> struct TagToType<0x0072,0x0214> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0214>::VRString[] = "SQ";
const char TagToType<0x0072,0x0214>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0216> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0216>::VRString[] = "US";
const char TagToType<0x0072,0x0216>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0218> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x0218>::VRString[] = "US";
const char TagToType<0x0072,0x0218>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x0300> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0300>::VRString[] = "SQ";
const char TagToType<0x0072,0x0300>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0302> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0302>::VRString[] = "US";
const char TagToType<0x0072,0x0302>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0304> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0304>::VRString[] = "CS";
const char TagToType<0x0072,0x0304>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0306> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0306>::VRString[] = "US";
const char TagToType<0x0072,0x0306>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0308> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0308>::VRString[] = "US";
const char TagToType<0x0072,0x0308>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0310> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0310>::VRString[] = "CS";
const char TagToType<0x0072,0x0310>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0312> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0312>::VRString[] = "CS";
const char TagToType<0x0072,0x0312>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0314> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0314>::VRString[] = "US";
const char TagToType<0x0072,0x0314>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0316> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0316>::VRString[] = "CS";
const char TagToType<0x0072,0x0316>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0318> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0318>::VRString[] = "US";
const char TagToType<0x0072,0x0318>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0320> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0320>::VRString[] = "US";
const char TagToType<0x0072,0x0320>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0330> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0330>::VRString[] = "FD";
const char TagToType<0x0072,0x0330>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0400> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0400>::VRString[] = "SQ";
const char TagToType<0x0072,0x0400>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0402> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0402>::VRString[] = "CS";
const char TagToType<0x0072,0x0402>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0404> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0404>::VRString[] = "CS";
const char TagToType<0x0072,0x0404>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0406> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0406>::VRString[] = "CS";
const char TagToType<0x0072,0x0406>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0500> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0500>::VRString[] = "CS";
const char TagToType<0x0072,0x0500>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0510> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0510>::VRString[] = "CS";
const char TagToType<0x0072,0x0510>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0512> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0512>::VRString[] = "FD";
const char TagToType<0x0072,0x0512>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0514> {
static const char VRString[];
typedef VRToType<VR::FD>::Type Type;
enum { VRType = VR::FD };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0514>::VRString[] = "FD";
const char TagToType<0x0072,0x0514>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0516> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0516>::VRString[] = "CS";
const char TagToType<0x0072,0x0516>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0520> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0072,0x0520>::VRString[] = "CS";
const char TagToType<0x0072,0x0520>::VMString[] = "1-n";
template <> struct TagToType<0x0072,0x0600> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0600>::VRString[] = "SQ";
const char TagToType<0x0072,0x0600>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0602> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0602>::VRString[] = "CS";
const char TagToType<0x0072,0x0602>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0604> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0604>::VRString[] = "CS";
const char TagToType<0x0072,0x0604>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0700> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x0072,0x0700>::VRString[] = "CS";
const char TagToType<0x0072,0x0700>::VMString[] = "2";
template <> struct TagToType<0x0072,0x0702> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0702>::VRString[] = "CS";
const char TagToType<0x0072,0x0702>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0704> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0704>::VRString[] = "CS";
const char TagToType<0x0072,0x0704>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0706> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0706>::VRString[] = "CS";
const char TagToType<0x0072,0x0706>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0710> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0710>::VRString[] = "CS";
const char TagToType<0x0072,0x0710>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0712> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0712>::VRString[] = "CS";
const char TagToType<0x0072,0x0712>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0714> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0714>::VRString[] = "CS";
const char TagToType<0x0072,0x0714>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0716> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0716>::VRString[] = "CS";
const char TagToType<0x0072,0x0716>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0717> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0717>::VRString[] = "CS";
const char TagToType<0x0072,0x0717>::VMString[] = "1";
template <> struct TagToType<0x0072,0x0718> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0072,0x0718>::VRString[] = "CS";
const char TagToType<0x0072,0x0718>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1000> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1000>::VRString[] = "CS";
const char TagToType<0x0074,0x1000>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1002> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1002>::VRString[] = "SQ";
const char TagToType<0x0074,0x1002>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1004> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1004>::VRString[] = "DS";
const char TagToType<0x0074,0x1004>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1006> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1006>::VRString[] = "ST";
const char TagToType<0x0074,0x1006>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1008> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1008>::VRString[] = "SQ";
const char TagToType<0x0074,0x1008>::VMString[] = "1";
template <> struct TagToType<0x0074,0x100a> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x100a>::VRString[] = "ST";
const char TagToType<0x0074,0x100a>::VMString[] = "1";
template <> struct TagToType<0x0074,0x100c> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x100c>::VRString[] = "LO";
const char TagToType<0x0074,0x100c>::VMString[] = "1";
template <> struct TagToType<0x0074,0x100e> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x100e>::VRString[] = "SQ";
const char TagToType<0x0074,0x100e>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1020> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1020>::VRString[] = "SQ";
const char TagToType<0x0074,0x1020>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1022> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1022>::VRString[] = "CS";
const char TagToType<0x0074,0x1022>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1024> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1024>::VRString[] = "IS";
const char TagToType<0x0074,0x1024>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1030> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1030>::VRString[] = "SQ";
const char TagToType<0x0074,0x1030>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1032> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1032>::VRString[] = "CS";
const char TagToType<0x0074,0x1032>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1034> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1034>::VRString[] = "CS";
const char TagToType<0x0074,0x1034>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1036> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1036>::VRString[] = "CS";
const char TagToType<0x0074,0x1036>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1038> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1038>::VRString[] = "DS";
const char TagToType<0x0074,0x1038>::VMString[] = "1";
template <> struct TagToType<0x0074,0x103a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM4 };
static const char VMString[];
};
const char TagToType<0x0074,0x103a>::VRString[] = "DS";
const char TagToType<0x0074,0x103a>::VMString[] = "4";
template <> struct TagToType<0x0074,0x1040> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1040>::VRString[] = "SQ";
const char TagToType<0x0074,0x1040>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1042> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1042>::VRString[] = "SQ";
const char TagToType<0x0074,0x1042>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1044> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1044>::VRString[] = "SQ";
const char TagToType<0x0074,0x1044>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1046> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1046>::VRString[] = "SQ";
const char TagToType<0x0074,0x1046>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1048> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1048>::VRString[] = "SQ";
const char TagToType<0x0074,0x1048>::VMString[] = "1";
template <> struct TagToType<0x0074,0x104a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x104a>::VRString[] = "SQ";
const char TagToType<0x0074,0x104a>::VMString[] = "1";
template <> struct TagToType<0x0074,0x104c> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x104c>::VRString[] = "SQ";
const char TagToType<0x0074,0x104c>::VMString[] = "1";
template <> struct TagToType<0x0074,0x104e> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x104e>::VRString[] = "SQ";
const char TagToType<0x0074,0x104e>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1050> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1050>::VRString[] = "SQ";
const char TagToType<0x0074,0x1050>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1052> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1052>::VRString[] = "AT";
const char TagToType<0x0074,0x1052>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1054> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1054>::VRString[] = "UL";
const char TagToType<0x0074,0x1054>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1056> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1056>::VRString[] = "LO";
const char TagToType<0x0074,0x1056>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1200> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1200>::VRString[] = "CS";
const char TagToType<0x0074,0x1200>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1202> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1202>::VRString[] = "LO";
const char TagToType<0x0074,0x1202>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1204> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1204>::VRString[] = "LO";
const char TagToType<0x0074,0x1204>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1210> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1210>::VRString[] = "SQ";
const char TagToType<0x0074,0x1210>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1212> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1212>::VRString[] = "SQ";
const char TagToType<0x0074,0x1212>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1216> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1216>::VRString[] = "SQ";
const char TagToType<0x0074,0x1216>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1220> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1220>::VRString[] = "SQ";
const char TagToType<0x0074,0x1220>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1222> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1222>::VRString[] = "LO";
const char TagToType<0x0074,0x1222>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1230> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1230>::VRString[] = "LO";
const char TagToType<0x0074,0x1230>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1234> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1234>::VRString[] = "AE";
const char TagToType<0x0074,0x1234>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1236> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1236>::VRString[] = "AE";
const char TagToType<0x0074,0x1236>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1238> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1238>::VRString[] = "LT";
const char TagToType<0x0074,0x1238>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1242> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1242>::VRString[] = "CS";
const char TagToType<0x0074,0x1242>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1244> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1244>::VRString[] = "CS";
const char TagToType<0x0074,0x1244>::VMString[] = "1";
template <> struct TagToType<0x0074,0x1246> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0074,0x1246>::VRString[] = "CS";
const char TagToType<0x0074,0x1246>::VMString[] = "1";
template <> struct TagToType<0x0088,0x0130> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0088,0x0130>::VRString[] = "SH";
const char TagToType<0x0088,0x0130>::VMString[] = "1";
template <> struct TagToType<0x0088,0x0140> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0088,0x0140>::VRString[] = "UI";
const char TagToType<0x0088,0x0140>::VMString[] = "1";
template <> struct TagToType<0x0088,0x0200> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0088,0x0200>::VRString[] = "SQ";
const char TagToType<0x0088,0x0200>::VMString[] = "1";
template <> struct TagToType<0x0088,0x0904> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0088,0x0904>::VRString[] = "LO";
const char TagToType<0x0088,0x0904>::VMString[] = "1";
template <> struct TagToType<0x0088,0x0906> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0088,0x0906>::VRString[] = "ST";
const char TagToType<0x0088,0x0906>::VMString[] = "1";
template <> struct TagToType<0x0088,0x0910> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0088,0x0910>::VRString[] = "LO";
const char TagToType<0x0088,0x0910>::VMString[] = "1";
template <> struct TagToType<0x0088,0x0912> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_32 };
static const char VMString[];
};
const char TagToType<0x0088,0x0912>::VRString[] = "LO";
const char TagToType<0x0088,0x0912>::VMString[] = "1-32";
template <> struct TagToType<0x0100,0x0410> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0100,0x0410>::VRString[] = "CS";
const char TagToType<0x0100,0x0410>::VMString[] = "1";
template <> struct TagToType<0x0100,0x0420> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0100,0x0420>::VRString[] = "DT";
const char TagToType<0x0100,0x0420>::VMString[] = "1";
template <> struct TagToType<0x0100,0x0424> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0100,0x0424>::VRString[] = "LT";
const char TagToType<0x0100,0x0424>::VMString[] = "1";
template <> struct TagToType<0x0100,0x0426> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0100,0x0426>::VRString[] = "LO";
const char TagToType<0x0100,0x0426>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0005> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0005>::VRString[] = "US";
const char TagToType<0x0400,0x0005>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0010> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0010>::VRString[] = "UI";
const char TagToType<0x0400,0x0010>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0015> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0015>::VRString[] = "CS";
const char TagToType<0x0400,0x0015>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0020> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x0400,0x0020>::VRString[] = "AT";
const char TagToType<0x0400,0x0020>::VMString[] = "1-n";
template <> struct TagToType<0x0400,0x0100> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0100>::VRString[] = "UI";
const char TagToType<0x0400,0x0100>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0105> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0105>::VRString[] = "DT";
const char TagToType<0x0400,0x0105>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0110> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0110>::VRString[] = "CS";
const char TagToType<0x0400,0x0110>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0115> {
static const char VRString[];
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0115>::VRString[] = "OB";
const char TagToType<0x0400,0x0115>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0120> {
static const char VRString[];
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0120>::VRString[] = "OB";
const char TagToType<0x0400,0x0120>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0305> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0305>::VRString[] = "CS";
const char TagToType<0x0400,0x0305>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0310> {
static const char VRString[];
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0310>::VRString[] = "OB";
const char TagToType<0x0400,0x0310>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0401> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0401>::VRString[] = "SQ";
const char TagToType<0x0400,0x0401>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0402> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0402>::VRString[] = "SQ";
const char TagToType<0x0400,0x0402>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0403> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0403>::VRString[] = "SQ";
const char TagToType<0x0400,0x0403>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0404> {
static const char VRString[];
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0404>::VRString[] = "OB";
const char TagToType<0x0400,0x0404>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0500> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0500>::VRString[] = "SQ";
const char TagToType<0x0400,0x0500>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0510> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0510>::VRString[] = "UI";
const char TagToType<0x0400,0x0510>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0520> {
static const char VRString[];
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0520>::VRString[] = "OB";
const char TagToType<0x0400,0x0520>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0550> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0550>::VRString[] = "SQ";
const char TagToType<0x0400,0x0550>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0561> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0561>::VRString[] = "SQ";
const char TagToType<0x0400,0x0561>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0562> {
static const char VRString[];
typedef VRToType<VR::DT>::Type Type;
enum { VRType = VR::DT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0562>::VRString[] = "DT";
const char TagToType<0x0400,0x0562>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0563> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0563>::VRString[] = "LO";
const char TagToType<0x0400,0x0563>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0564> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0564>::VRString[] = "LO";
const char TagToType<0x0400,0x0564>::VMString[] = "1";
template <> struct TagToType<0x0400,0x0565> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x0400,0x0565>::VRString[] = "CS";
const char TagToType<0x0400,0x0565>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0010> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0010>::VRString[] = "IS";
const char TagToType<0x2000,0x0010>::VMString[] = "1";
template <> struct TagToType<0x2000,0x001e> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x001e>::VRString[] = "SQ";
const char TagToType<0x2000,0x001e>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0020>::VRString[] = "CS";
const char TagToType<0x2000,0x0020>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0030> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0030>::VRString[] = "CS";
const char TagToType<0x2000,0x0030>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0040> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0040>::VRString[] = "CS";
const char TagToType<0x2000,0x0040>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0050> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0050>::VRString[] = "LO";
const char TagToType<0x2000,0x0050>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0060> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0060>::VRString[] = "IS";
const char TagToType<0x2000,0x0060>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0061> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0061>::VRString[] = "IS";
const char TagToType<0x2000,0x0061>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0062> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0062>::VRString[] = "CS";
const char TagToType<0x2000,0x0062>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0063> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0063>::VRString[] = "CS";
const char TagToType<0x2000,0x0063>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0065> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0065>::VRString[] = "CS";
const char TagToType<0x2000,0x0065>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0067> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0067>::VRString[] = "CS";
const char TagToType<0x2000,0x0067>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0069> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0069>::VRString[] = "CS";
const char TagToType<0x2000,0x0069>::VMString[] = "1";
template <> struct TagToType<0x2000,0x006a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x006a>::VRString[] = "CS";
const char TagToType<0x2000,0x006a>::VMString[] = "1";
template <> struct TagToType<0x2000,0x00a0> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x00a0>::VRString[] = "US";
const char TagToType<0x2000,0x00a0>::VMString[] = "1";
template <> struct TagToType<0x2000,0x00a1> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x00a1>::VRString[] = "US";
const char TagToType<0x2000,0x00a1>::VMString[] = "1";
template <> struct TagToType<0x2000,0x00a2> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x00a2>::VRString[] = "SQ";
const char TagToType<0x2000,0x00a2>::VMString[] = "1";
template <> struct TagToType<0x2000,0x00a4> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x00a4>::VRString[] = "SQ";
const char TagToType<0x2000,0x00a4>::VMString[] = "1";
template <> struct TagToType<0x2000,0x00a8> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x00a8>::VRString[] = "SQ";
const char TagToType<0x2000,0x00a8>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0500> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0500>::VRString[] = "SQ";
const char TagToType<0x2000,0x0500>::VMString[] = "1";
template <> struct TagToType<0x2000,0x0510> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2000,0x0510>::VRString[] = "SQ";
const char TagToType<0x2000,0x0510>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0010> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0010>::VRString[] = "ST";
const char TagToType<0x2010,0x0010>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0030> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0030>::VRString[] = "CS";
const char TagToType<0x2010,0x0030>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0040> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0040>::VRString[] = "CS";
const char TagToType<0x2010,0x0040>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0050> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0050>::VRString[] = "CS";
const char TagToType<0x2010,0x0050>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0052> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0052>::VRString[] = "CS";
const char TagToType<0x2010,0x0052>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0054> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0054>::VRString[] = "CS";
const char TagToType<0x2010,0x0054>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0060> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0060>::VRString[] = "CS";
const char TagToType<0x2010,0x0060>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0080> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0080>::VRString[] = "CS";
const char TagToType<0x2010,0x0080>::VMString[] = "1";
template <> struct TagToType<0x2010,0x00a6> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x00a6>::VRString[] = "CS";
const char TagToType<0x2010,0x00a6>::VMString[] = "1";
template <> struct TagToType<0x2010,0x00a7> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x2010,0x00a7>::VRString[] = "CS";
const char TagToType<0x2010,0x00a7>::VMString[] = "1-n";
template <> struct TagToType<0x2010,0x00a8> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x00a8>::VRString[] = "CS";
const char TagToType<0x2010,0x00a8>::VMString[] = "1";
template <> struct TagToType<0x2010,0x00a9> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x2010,0x00a9>::VRString[] = "CS";
const char TagToType<0x2010,0x00a9>::VMString[] = "1-n";
template <> struct TagToType<0x2010,0x0100> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0100>::VRString[] = "CS";
const char TagToType<0x2010,0x0100>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0110> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0110>::VRString[] = "CS";
const char TagToType<0x2010,0x0110>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0120> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0120>::VRString[] = "US";
const char TagToType<0x2010,0x0120>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0130> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0130>::VRString[] = "US";
const char TagToType<0x2010,0x0130>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0140> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0140>::VRString[] = "CS";
const char TagToType<0x2010,0x0140>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0150> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0150>::VRString[] = "ST";
const char TagToType<0x2010,0x0150>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0152> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0152>::VRString[] = "LT";
const char TagToType<0x2010,0x0152>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0154> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0154>::VRString[] = "IS";
const char TagToType<0x2010,0x0154>::VMString[] = "1";
template <> struct TagToType<0x2010,0x015e> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x015e>::VRString[] = "US";
const char TagToType<0x2010,0x015e>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0160> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0160>::VRString[] = "US";
const char TagToType<0x2010,0x0160>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0376> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x2010,0x0376>::VRString[] = "DS";
const char TagToType<0x2010,0x0376>::VMString[] = "2";
template <> struct TagToType<0x2010,0x0500> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0500>::VRString[] = "SQ";
const char TagToType<0x2010,0x0500>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0510> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0510>::VRString[] = "SQ";
const char TagToType<0x2010,0x0510>::VMString[] = "1";
template <> struct TagToType<0x2010,0x0520> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2010,0x0520>::VRString[] = "SQ";
const char TagToType<0x2010,0x0520>::VMString[] = "1";
template <> struct TagToType<0x2020,0x0010> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2020,0x0010>::VRString[] = "US";
const char TagToType<0x2020,0x0010>::VMString[] = "1";
template <> struct TagToType<0x2020,0x0020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2020,0x0020>::VRString[] = "CS";
const char TagToType<0x2020,0x0020>::VMString[] = "1";
template <> struct TagToType<0x2020,0x0030> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2020,0x0030>::VRString[] = "DS";
const char TagToType<0x2020,0x0030>::VMString[] = "1";
template <> struct TagToType<0x2020,0x0040> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2020,0x0040>::VRString[] = "CS";
const char TagToType<0x2020,0x0040>::VMString[] = "1";
template <> struct TagToType<0x2020,0x0050> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2020,0x0050>::VRString[] = "CS";
const char TagToType<0x2020,0x0050>::VMString[] = "1";
template <> struct TagToType<0x2020,0x00a0> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2020,0x00a0>::VRString[] = "CS";
const char TagToType<0x2020,0x00a0>::VMString[] = "1";
template <> struct TagToType<0x2020,0x00a2> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2020,0x00a2>::VRString[] = "CS";
const char TagToType<0x2020,0x00a2>::VMString[] = "1";
template <> struct TagToType<0x2020,0x0110> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2020,0x0110>::VRString[] = "SQ";
const char TagToType<0x2020,0x0110>::VMString[] = "1";
template <> struct TagToType<0x2020,0x0111> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2020,0x0111>::VRString[] = "SQ";
const char TagToType<0x2020,0x0111>::VMString[] = "1";
template <> struct TagToType<0x2020,0x0130> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2020,0x0130>::VRString[] = "SQ";
const char TagToType<0x2020,0x0130>::VMString[] = "1";
template <> struct TagToType<0x2020,0x0140> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2020,0x0140>::VRString[] = "SQ";
const char TagToType<0x2020,0x0140>::VMString[] = "1";
template <> struct TagToType<0x2030,0x0010> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2030,0x0010>::VRString[] = "US";
const char TagToType<0x2030,0x0010>::VMString[] = "1";
template <> struct TagToType<0x2030,0x0020> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2030,0x0020>::VRString[] = "LO";
const char TagToType<0x2030,0x0020>::VMString[] = "1";
template <> struct TagToType<0x2040,0x0010> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2040,0x0010>::VRString[] = "SQ";
const char TagToType<0x2040,0x0010>::VMString[] = "1";
template <> struct TagToType<0x2040,0x0011> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_99 };
static const char VMString[];
};
const char TagToType<0x2040,0x0011>::VRString[] = "US";
const char TagToType<0x2040,0x0011>::VMString[] = "1-99";
template <> struct TagToType<0x2040,0x0020> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2040,0x0020>::VRString[] = "SQ";
const char TagToType<0x2040,0x0020>::VMString[] = "1";
template <> struct TagToType<0x2040,0x0060> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2040,0x0060>::VRString[] = "CS";
const char TagToType<0x2040,0x0060>::VMString[] = "1";
template <> struct TagToType<0x2040,0x0070> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2040,0x0070>::VRString[] = "CS";
const char TagToType<0x2040,0x0070>::VMString[] = "1";
template <> struct TagToType<0x2040,0x0072> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2040,0x0072>::VRString[] = "CS";
const char TagToType<0x2040,0x0072>::VMString[] = "1";
template <> struct TagToType<0x2040,0x0074> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2040,0x0074>::VRString[] = "US";
const char TagToType<0x2040,0x0074>::VMString[] = "1";
template <> struct TagToType<0x2040,0x0080> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2040,0x0080>::VRString[] = "CS";
const char TagToType<0x2040,0x0080>::VMString[] = "1";
template <> struct TagToType<0x2040,0x0082> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2040,0x0082>::VRString[] = "CS";
const char TagToType<0x2040,0x0082>::VMString[] = "1";
template <> struct TagToType<0x2040,0x0090> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2040,0x0090>::VRString[] = "CS";
const char TagToType<0x2040,0x0090>::VMString[] = "1";
template <> struct TagToType<0x2040,0x0100> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2040,0x0100>::VRString[] = "CS";
const char TagToType<0x2040,0x0100>::VMString[] = "1";
template <> struct TagToType<0x2040,0x0500> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2040,0x0500>::VRString[] = "SQ";
const char TagToType<0x2040,0x0500>::VMString[] = "1";
template <> struct TagToType<0x2050,0x0010> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2050,0x0010>::VRString[] = "SQ";
const char TagToType<0x2050,0x0010>::VMString[] = "1";
template <> struct TagToType<0x2050,0x0020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2050,0x0020>::VRString[] = "CS";
const char TagToType<0x2050,0x0020>::VMString[] = "1";
template <> struct TagToType<0x2050,0x0500> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2050,0x0500>::VRString[] = "SQ";
const char TagToType<0x2050,0x0500>::VMString[] = "1";
template <> struct TagToType<0x2100,0x0010> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2100,0x0010>::VRString[] = "SH";
const char TagToType<0x2100,0x0010>::VMString[] = "1";
template <> struct TagToType<0x2100,0x0020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2100,0x0020>::VRString[] = "CS";
const char TagToType<0x2100,0x0020>::VMString[] = "1";
template <> struct TagToType<0x2100,0x0030> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2100,0x0030>::VRString[] = "CS";
const char TagToType<0x2100,0x0030>::VMString[] = "1";
template <> struct TagToType<0x2100,0x0040> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2100,0x0040>::VRString[] = "DA";
const char TagToType<0x2100,0x0040>::VMString[] = "1";
template <> struct TagToType<0x2100,0x0050> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2100,0x0050>::VRString[] = "TM";
const char TagToType<0x2100,0x0050>::VMString[] = "1";
template <> struct TagToType<0x2100,0x0070> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2100,0x0070>::VRString[] = "AE";
const char TagToType<0x2100,0x0070>::VMString[] = "1";
template <> struct TagToType<0x2100,0x0140> {
static const char VRString[];
typedef VRToType<VR::AE>::Type Type;
enum { VRType = VR::AE };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2100,0x0140>::VRString[] = "AE";
const char TagToType<0x2100,0x0140>::VMString[] = "1";
template <> struct TagToType<0x2100,0x0160> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2100,0x0160>::VRString[] = "SH";
const char TagToType<0x2100,0x0160>::VMString[] = "1";
template <> struct TagToType<0x2100,0x0170> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2100,0x0170>::VRString[] = "IS";
const char TagToType<0x2100,0x0170>::VMString[] = "1";
template <> struct TagToType<0x2100,0x0500> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2100,0x0500>::VRString[] = "SQ";
const char TagToType<0x2100,0x0500>::VMString[] = "1";
template <> struct TagToType<0x2110,0x0010> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2110,0x0010>::VRString[] = "CS";
const char TagToType<0x2110,0x0010>::VMString[] = "1";
template <> struct TagToType<0x2110,0x0020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2110,0x0020>::VRString[] = "CS";
const char TagToType<0x2110,0x0020>::VMString[] = "1";
template <> struct TagToType<0x2110,0x0030> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2110,0x0030>::VRString[] = "LO";
const char TagToType<0x2110,0x0030>::VMString[] = "1";
template <> struct TagToType<0x2110,0x0099> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2110,0x0099>::VRString[] = "SH";
const char TagToType<0x2110,0x0099>::VMString[] = "1";
template <> struct TagToType<0x2120,0x0010> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2120,0x0010>::VRString[] = "CS";
const char TagToType<0x2120,0x0010>::VMString[] = "1";
template <> struct TagToType<0x2120,0x0050> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2120,0x0050>::VRString[] = "SQ";
const char TagToType<0x2120,0x0050>::VMString[] = "1";
template <> struct TagToType<0x2120,0x0070> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2120,0x0070>::VRString[] = "SQ";
const char TagToType<0x2120,0x0070>::VMString[] = "1";
template <> struct TagToType<0x2130,0x0010> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2130,0x0010>::VRString[] = "SQ";
const char TagToType<0x2130,0x0010>::VMString[] = "1";
template <> struct TagToType<0x2130,0x0015> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2130,0x0015>::VRString[] = "SQ";
const char TagToType<0x2130,0x0015>::VMString[] = "1";
template <> struct TagToType<0x2130,0x0030> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2130,0x0030>::VRString[] = "SQ";
const char TagToType<0x2130,0x0030>::VMString[] = "1";
template <> struct TagToType<0x2130,0x0040> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2130,0x0040>::VRString[] = "SQ";
const char TagToType<0x2130,0x0040>::VMString[] = "1";
template <> struct TagToType<0x2130,0x0050> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2130,0x0050>::VRString[] = "SQ";
const char TagToType<0x2130,0x0050>::VMString[] = "1";
template <> struct TagToType<0x2130,0x0060> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2130,0x0060>::VRString[] = "SQ";
const char TagToType<0x2130,0x0060>::VMString[] = "1";
template <> struct TagToType<0x2130,0x0080> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2130,0x0080>::VRString[] = "SQ";
const char TagToType<0x2130,0x0080>::VMString[] = "1";
template <> struct TagToType<0x2130,0x00a0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2130,0x00a0>::VRString[] = "SQ";
const char TagToType<0x2130,0x00a0>::VMString[] = "1";
template <> struct TagToType<0x2130,0x00c0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2130,0x00c0>::VRString[] = "SQ";
const char TagToType<0x2130,0x00c0>::VMString[] = "1";
template <> struct TagToType<0x2200,0x0001> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x0001>::VRString[] = "CS";
const char TagToType<0x2200,0x0001>::VMString[] = "1";
template <> struct TagToType<0x2200,0x0002> {
static const char VRString[];
typedef VRToType<VR::UT>::Type Type;
enum { VRType = VR::UT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x0002>::VRString[] = "UT";
const char TagToType<0x2200,0x0002>::VMString[] = "1";
template <> struct TagToType<0x2200,0x0003> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x0003>::VRString[] = "CS";
const char TagToType<0x2200,0x0003>::VMString[] = "1";
template <> struct TagToType<0x2200,0x0004> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x0004>::VRString[] = "LT";
const char TagToType<0x2200,0x0004>::VMString[] = "1";
template <> struct TagToType<0x2200,0x0005> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x0005>::VRString[] = "LT";
const char TagToType<0x2200,0x0005>::VMString[] = "1";
template <> struct TagToType<0x2200,0x0006> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x0006>::VRString[] = "CS";
const char TagToType<0x2200,0x0006>::VMString[] = "1";
template <> struct TagToType<0x2200,0x0007> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x0007>::VRString[] = "CS";
const char TagToType<0x2200,0x0007>::VMString[] = "1";
template <> struct TagToType<0x2200,0x0008> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x0008>::VRString[] = "CS";
const char TagToType<0x2200,0x0008>::VMString[] = "1";
template <> struct TagToType<0x2200,0x0009> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x0009>::VRString[] = "CS";
const char TagToType<0x2200,0x0009>::VMString[] = "1";
template <> struct TagToType<0x2200,0x000a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x000a>::VRString[] = "CS";
const char TagToType<0x2200,0x000a>::VMString[] = "1";
template <> struct TagToType<0x2200,0x000b> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x000b>::VRString[] = "US";
const char TagToType<0x2200,0x000b>::VMString[] = "1";
template <> struct TagToType<0x2200,0x000c> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x000c>::VRString[] = "LO";
const char TagToType<0x2200,0x000c>::VMString[] = "1";
template <> struct TagToType<0x2200,0x000d> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x000d>::VRString[] = "SQ";
const char TagToType<0x2200,0x000d>::VMString[] = "1";
template <> struct TagToType<0x2200,0x000e> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x2200,0x000e>::VRString[] = "AT";
const char TagToType<0x2200,0x000e>::VMString[] = "1-n";
template <> struct TagToType<0x2200,0x000f> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x000f>::VRString[] = "CS";
const char TagToType<0x2200,0x000f>::VMString[] = "1";
template <> struct TagToType<0x2200,0x0020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x2200,0x0020>::VRString[] = "CS";
const char TagToType<0x2200,0x0020>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0002> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0002>::VRString[] = "SH";
const char TagToType<0x3002,0x0002>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0003> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0003>::VRString[] = "LO";
const char TagToType<0x3002,0x0003>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0004> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0004>::VRString[] = "ST";
const char TagToType<0x3002,0x0004>::VMString[] = "1";
template <> struct TagToType<0x3002,0x000a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x000a>::VRString[] = "CS";
const char TagToType<0x3002,0x000a>::VMString[] = "1";
template <> struct TagToType<0x3002,0x000c> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x000c>::VRString[] = "CS";
const char TagToType<0x3002,0x000c>::VMString[] = "1";
template <> struct TagToType<0x3002,0x000d> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x3002,0x000d>::VRString[] = "DS";
const char TagToType<0x3002,0x000d>::VMString[] = "3";
template <> struct TagToType<0x3002,0x000e> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x000e>::VRString[] = "DS";
const char TagToType<0x3002,0x000e>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0010> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM6 };
static const char VMString[];
};
const char TagToType<0x3002,0x0010>::VRString[] = "DS";
const char TagToType<0x3002,0x0010>::VMString[] = "6";
template <> struct TagToType<0x3002,0x0011> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x3002,0x0011>::VRString[] = "DS";
const char TagToType<0x3002,0x0011>::VMString[] = "2";
template <> struct TagToType<0x3002,0x0012> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x3002,0x0012>::VRString[] = "DS";
const char TagToType<0x3002,0x0012>::VMString[] = "2";
template <> struct TagToType<0x3002,0x0020> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0020>::VRString[] = "SH";
const char TagToType<0x3002,0x0020>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0022> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0022>::VRString[] = "DS";
const char TagToType<0x3002,0x0022>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0024> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0024>::VRString[] = "DS";
const char TagToType<0x3002,0x0024>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0026> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0026>::VRString[] = "DS";
const char TagToType<0x3002,0x0026>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0028> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0028>::VRString[] = "DS";
const char TagToType<0x3002,0x0028>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0029> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0029>::VRString[] = "IS";
const char TagToType<0x3002,0x0029>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0030> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0030>::VRString[] = "SQ";
const char TagToType<0x3002,0x0030>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0032> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0032>::VRString[] = "DS";
const char TagToType<0x3002,0x0032>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0034> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM4 };
static const char VMString[];
};
const char TagToType<0x3002,0x0034>::VRString[] = "DS";
const char TagToType<0x3002,0x0034>::VMString[] = "4";
template <> struct TagToType<0x3002,0x0040> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0040>::VRString[] = "SQ";
const char TagToType<0x3002,0x0040>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0041> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0041>::VRString[] = "CS";
const char TagToType<0x3002,0x0041>::VMString[] = "1";
template <> struct TagToType<0x3002,0x0042> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3002,0x0042>::VRString[] = "DS";
const char TagToType<0x3002,0x0042>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0001> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0001>::VRString[] = "CS";
const char TagToType<0x3004,0x0001>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0002> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0002>::VRString[] = "CS";
const char TagToType<0x3004,0x0002>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0004> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0004>::VRString[] = "CS";
const char TagToType<0x3004,0x0004>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0006> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0006>::VRString[] = "LO";
const char TagToType<0x3004,0x0006>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0008> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x3004,0x0008>::VRString[] = "DS";
const char TagToType<0x3004,0x0008>::VMString[] = "3";
template <> struct TagToType<0x3004,0x000a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x000a>::VRString[] = "CS";
const char TagToType<0x3004,0x000a>::VMString[] = "1";
template <> struct TagToType<0x3004,0x000c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2_n };
static const char VMString[];
};
const char TagToType<0x3004,0x000c>::VRString[] = "DS";
const char TagToType<0x3004,0x000c>::VMString[] = "2-n";
template <> struct TagToType<0x3004,0x000e> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x000e>::VRString[] = "DS";
const char TagToType<0x3004,0x000e>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0010> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0010>::VRString[] = "SQ";
const char TagToType<0x3004,0x0010>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0012> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0012>::VRString[] = "DS";
const char TagToType<0x3004,0x0012>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0014> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_3 };
static const char VMString[];
};
const char TagToType<0x3004,0x0014>::VRString[] = "CS";
const char TagToType<0x3004,0x0014>::VMString[] = "1-3";
template <> struct TagToType<0x3004,0x0040> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x3004,0x0040>::VRString[] = "DS";
const char TagToType<0x3004,0x0040>::VMString[] = "3";
template <> struct TagToType<0x3004,0x0042> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0042>::VRString[] = "DS";
const char TagToType<0x3004,0x0042>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0050> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0050>::VRString[] = "SQ";
const char TagToType<0x3004,0x0050>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0052> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0052>::VRString[] = "DS";
const char TagToType<0x3004,0x0052>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0054> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0054>::VRString[] = "CS";
const char TagToType<0x3004,0x0054>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0056> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0056>::VRString[] = "IS";
const char TagToType<0x3004,0x0056>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0058> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2_2n };
static const char VMString[];
};
const char TagToType<0x3004,0x0058>::VRString[] = "DS";
const char TagToType<0x3004,0x0058>::VMString[] = "2-2n";
template <> struct TagToType<0x3004,0x0060> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0060>::VRString[] = "SQ";
const char TagToType<0x3004,0x0060>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0062> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0062>::VRString[] = "CS";
const char TagToType<0x3004,0x0062>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0070> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0070>::VRString[] = "DS";
const char TagToType<0x3004,0x0070>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0072> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0072>::VRString[] = "DS";
const char TagToType<0x3004,0x0072>::VMString[] = "1";
template <> struct TagToType<0x3004,0x0074> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3004,0x0074>::VRString[] = "DS";
const char TagToType<0x3004,0x0074>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0002> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0002>::VRString[] = "SH";
const char TagToType<0x3006,0x0002>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0004> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0004>::VRString[] = "LO";
const char TagToType<0x3006,0x0004>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0006> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0006>::VRString[] = "ST";
const char TagToType<0x3006,0x0006>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0008> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0008>::VRString[] = "DA";
const char TagToType<0x3006,0x0008>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0009> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0009>::VRString[] = "TM";
const char TagToType<0x3006,0x0009>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0010> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0010>::VRString[] = "SQ";
const char TagToType<0x3006,0x0010>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0012> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0012>::VRString[] = "SQ";
const char TagToType<0x3006,0x0012>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0014> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0014>::VRString[] = "SQ";
const char TagToType<0x3006,0x0014>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0016> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0016>::VRString[] = "SQ";
const char TagToType<0x3006,0x0016>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0020> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0020>::VRString[] = "SQ";
const char TagToType<0x3006,0x0020>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0022> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0022>::VRString[] = "IS";
const char TagToType<0x3006,0x0022>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0024> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0024>::VRString[] = "UI";
const char TagToType<0x3006,0x0024>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0026> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0026>::VRString[] = "LO";
const char TagToType<0x3006,0x0026>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0028> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0028>::VRString[] = "ST";
const char TagToType<0x3006,0x0028>::VMString[] = "1";
template <> struct TagToType<0x3006,0x002a> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x3006,0x002a>::VRString[] = "IS";
const char TagToType<0x3006,0x002a>::VMString[] = "3";
template <> struct TagToType<0x3006,0x002c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x002c>::VRString[] = "DS";
const char TagToType<0x3006,0x002c>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0030> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0030>::VRString[] = "SQ";
const char TagToType<0x3006,0x0030>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0033> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0033>::VRString[] = "CS";
const char TagToType<0x3006,0x0033>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0036> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0036>::VRString[] = "CS";
const char TagToType<0x3006,0x0036>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0038> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0038>::VRString[] = "LO";
const char TagToType<0x3006,0x0038>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0039> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0039>::VRString[] = "SQ";
const char TagToType<0x3006,0x0039>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0040> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0040>::VRString[] = "SQ";
const char TagToType<0x3006,0x0040>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0042> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0042>::VRString[] = "CS";
const char TagToType<0x3006,0x0042>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0044> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0044>::VRString[] = "DS";
const char TagToType<0x3006,0x0044>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0045> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x3006,0x0045>::VRString[] = "DS";
const char TagToType<0x3006,0x0045>::VMString[] = "3";
template <> struct TagToType<0x3006,0x0046> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0046>::VRString[] = "IS";
const char TagToType<0x3006,0x0046>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0048> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0048>::VRString[] = "IS";
const char TagToType<0x3006,0x0048>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0049> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x3006,0x0049>::VRString[] = "IS";
const char TagToType<0x3006,0x0049>::VMString[] = "1-n";
template <> struct TagToType<0x3006,0x0050> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3_3n };
static const char VMString[];
};
const char TagToType<0x3006,0x0050>::VRString[] = "DS";
const char TagToType<0x3006,0x0050>::VMString[] = "3-3n";
template <> struct TagToType<0x3006,0x0080> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0080>::VRString[] = "SQ";
const char TagToType<0x3006,0x0080>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0082> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0082>::VRString[] = "IS";
const char TagToType<0x3006,0x0082>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0084> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0084>::VRString[] = "IS";
const char TagToType<0x3006,0x0084>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0085> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0085>::VRString[] = "SH";
const char TagToType<0x3006,0x0085>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0086> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0086>::VRString[] = "SQ";
const char TagToType<0x3006,0x0086>::VMString[] = "1";
template <> struct TagToType<0x3006,0x0088> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x0088>::VRString[] = "ST";
const char TagToType<0x3006,0x0088>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00a0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00a0>::VRString[] = "SQ";
const char TagToType<0x3006,0x00a0>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00a4> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00a4>::VRString[] = "CS";
const char TagToType<0x3006,0x00a4>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00a6> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00a6>::VRString[] = "PN";
const char TagToType<0x3006,0x00a6>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00b0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00b0>::VRString[] = "SQ";
const char TagToType<0x3006,0x00b0>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00b2> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00b2>::VRString[] = "CS";
const char TagToType<0x3006,0x00b2>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00b4> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00b4>::VRString[] = "DS";
const char TagToType<0x3006,0x00b4>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00b6> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00b6>::VRString[] = "SQ";
const char TagToType<0x3006,0x00b6>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00b7> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00b7>::VRString[] = "US";
const char TagToType<0x3006,0x00b7>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00b8> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00b8>::VRString[] = "FL";
const char TagToType<0x3006,0x00b8>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00c0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00c0>::VRString[] = "SQ";
const char TagToType<0x3006,0x00c0>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00c2> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00c2>::VRString[] = "UI";
const char TagToType<0x3006,0x00c2>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00c4> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00c4>::VRString[] = "CS";
const char TagToType<0x3006,0x00c4>::VMString[] = "1";
template <> struct TagToType<0x3006,0x00c6> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM16 };
static const char VMString[];
};
const char TagToType<0x3006,0x00c6>::VRString[] = "DS";
const char TagToType<0x3006,0x00c6>::VMString[] = "16";
template <> struct TagToType<0x3006,0x00c8> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3006,0x00c8>::VRString[] = "LO";
const char TagToType<0x3006,0x00c8>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0010> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0010>::VRString[] = "SQ";
const char TagToType<0x3008,0x0010>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0012> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0012>::VRString[] = "ST";
const char TagToType<0x3008,0x0012>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0014> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0014>::VRString[] = "CS";
const char TagToType<0x3008,0x0014>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0016> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0016>::VRString[] = "DS";
const char TagToType<0x3008,0x0016>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0020> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0020>::VRString[] = "SQ";
const char TagToType<0x3008,0x0020>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0021> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0021>::VRString[] = "SQ";
const char TagToType<0x3008,0x0021>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0022> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0022>::VRString[] = "IS";
const char TagToType<0x3008,0x0022>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0024> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0024>::VRString[] = "DA";
const char TagToType<0x3008,0x0024>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0025> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0025>::VRString[] = "TM";
const char TagToType<0x3008,0x0025>::VMString[] = "1";
template <> struct TagToType<0x3008,0x002a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x002a>::VRString[] = "CS";
const char TagToType<0x3008,0x002a>::VMString[] = "1";
template <> struct TagToType<0x3008,0x002b> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x002b>::VRString[] = "SH";
const char TagToType<0x3008,0x002b>::VMString[] = "1";
template <> struct TagToType<0x3008,0x002c> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x002c>::VRString[] = "CS";
const char TagToType<0x3008,0x002c>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0030> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0030>::VRString[] = "SQ";
const char TagToType<0x3008,0x0030>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0032> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0032>::VRString[] = "DS";
const char TagToType<0x3008,0x0032>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0033> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0033>::VRString[] = "DS";
const char TagToType<0x3008,0x0033>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0036> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0036>::VRString[] = "DS";
const char TagToType<0x3008,0x0036>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0037> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0037>::VRString[] = "DS";
const char TagToType<0x3008,0x0037>::VMString[] = "1";
template <> struct TagToType<0x3008,0x003a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x003a>::VRString[] = "DS";
const char TagToType<0x3008,0x003a>::VMString[] = "1";
template <> struct TagToType<0x3008,0x003b> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x003b>::VRString[] = "DS";
const char TagToType<0x3008,0x003b>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0040> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0040>::VRString[] = "SQ";
const char TagToType<0x3008,0x0040>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0041> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0041>::VRString[] = "SQ";
const char TagToType<0x3008,0x0041>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0042> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0042>::VRString[] = "DS";
const char TagToType<0x3008,0x0042>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0044> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0044>::VRString[] = "DS";
const char TagToType<0x3008,0x0044>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0045> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0045>::VRString[] = "FL";
const char TagToType<0x3008,0x0045>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0046> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0046>::VRString[] = "FL";
const char TagToType<0x3008,0x0046>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0047> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x3008,0x0047>::VRString[] = "FL";
const char TagToType<0x3008,0x0047>::VMString[] = "1-n";
template <> struct TagToType<0x3008,0x0048> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0048>::VRString[] = "DS";
const char TagToType<0x3008,0x0048>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0050> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0050>::VRString[] = "SQ";
const char TagToType<0x3008,0x0050>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0052> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0052>::VRString[] = "DS";
const char TagToType<0x3008,0x0052>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0054> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0054>::VRString[] = "DA";
const char TagToType<0x3008,0x0054>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0056> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0056>::VRString[] = "DA";
const char TagToType<0x3008,0x0056>::VMString[] = "1";
template <> struct TagToType<0x3008,0x005a> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x005a>::VRString[] = "IS";
const char TagToType<0x3008,0x005a>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0060> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0060>::VRString[] = "SQ";
const char TagToType<0x3008,0x0060>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0061> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0061>::VRString[] = "AT";
const char TagToType<0x3008,0x0061>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0062> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0062>::VRString[] = "AT";
const char TagToType<0x3008,0x0062>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0063> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0063>::VRString[] = "IS";
const char TagToType<0x3008,0x0063>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0064> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0064>::VRString[] = "IS";
const char TagToType<0x3008,0x0064>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0065> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0065>::VRString[] = "AT";
const char TagToType<0x3008,0x0065>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0066> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0066>::VRString[] = "ST";
const char TagToType<0x3008,0x0066>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0068> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0068>::VRString[] = "SQ";
const char TagToType<0x3008,0x0068>::VMString[] = "1";
template <> struct TagToType<0x3008,0x006a> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x006a>::VRString[] = "FL";
const char TagToType<0x3008,0x006a>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0070> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0070>::VRString[] = "SQ";
const char TagToType<0x3008,0x0070>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0072> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0072>::VRString[] = "IS";
const char TagToType<0x3008,0x0072>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0074> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0074>::VRString[] = "ST";
const char TagToType<0x3008,0x0074>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0076> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0076>::VRString[] = "DS";
const char TagToType<0x3008,0x0076>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0078> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0078>::VRString[] = "DS";
const char TagToType<0x3008,0x0078>::VMString[] = "1";
template <> struct TagToType<0x3008,0x007a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x007a>::VRString[] = "DS";
const char TagToType<0x3008,0x007a>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0080> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0080>::VRString[] = "SQ";
const char TagToType<0x3008,0x0080>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0082> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0082>::VRString[] = "IS";
const char TagToType<0x3008,0x0082>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0090> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0090>::VRString[] = "SQ";
const char TagToType<0x3008,0x0090>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0092> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0092>::VRString[] = "IS";
const char TagToType<0x3008,0x0092>::VMString[] = "1";
template <> struct TagToType<0x3008,0x00a0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x00a0>::VRString[] = "SQ";
const char TagToType<0x3008,0x00a0>::VMString[] = "1";
template <> struct TagToType<0x3008,0x00b0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x00b0>::VRString[] = "SQ";
const char TagToType<0x3008,0x00b0>::VMString[] = "1";
template <> struct TagToType<0x3008,0x00c0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x00c0>::VRString[] = "SQ";
const char TagToType<0x3008,0x00c0>::VMString[] = "1";
template <> struct TagToType<0x3008,0x00d0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x00d0>::VRString[] = "SQ";
const char TagToType<0x3008,0x00d0>::VMString[] = "1";
template <> struct TagToType<0x3008,0x00e0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x00e0>::VRString[] = "SQ";
const char TagToType<0x3008,0x00e0>::VMString[] = "1";
template <> struct TagToType<0x3008,0x00f0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x00f0>::VRString[] = "SQ";
const char TagToType<0x3008,0x00f0>::VMString[] = "1";
template <> struct TagToType<0x3008,0x00f2> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x00f2>::VRString[] = "SQ";
const char TagToType<0x3008,0x00f2>::VMString[] = "1";
template <> struct TagToType<0x3008,0x00f4> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x00f4>::VRString[] = "SQ";
const char TagToType<0x3008,0x00f4>::VMString[] = "1";
template <> struct TagToType<0x3008,0x00f6> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x00f6>::VRString[] = "SQ";
const char TagToType<0x3008,0x00f6>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0100> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0100>::VRString[] = "SQ";
const char TagToType<0x3008,0x0100>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0105> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0105>::VRString[] = "LO";
const char TagToType<0x3008,0x0105>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0110> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0110>::VRString[] = "SQ";
const char TagToType<0x3008,0x0110>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0116> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0116>::VRString[] = "CS";
const char TagToType<0x3008,0x0116>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0120> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0120>::VRString[] = "SQ";
const char TagToType<0x3008,0x0120>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0122> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0122>::VRString[] = "IS";
const char TagToType<0x3008,0x0122>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0130> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0130>::VRString[] = "SQ";
const char TagToType<0x3008,0x0130>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0132> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0132>::VRString[] = "DS";
const char TagToType<0x3008,0x0132>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0134> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0134>::VRString[] = "DS";
const char TagToType<0x3008,0x0134>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0136> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0136>::VRString[] = "IS";
const char TagToType<0x3008,0x0136>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0138> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0138>::VRString[] = "IS";
const char TagToType<0x3008,0x0138>::VMString[] = "1";
template <> struct TagToType<0x3008,0x013a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x013a>::VRString[] = "DS";
const char TagToType<0x3008,0x013a>::VMString[] = "1";
template <> struct TagToType<0x3008,0x013c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x013c>::VRString[] = "DS";
const char TagToType<0x3008,0x013c>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0140> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0140>::VRString[] = "SQ";
const char TagToType<0x3008,0x0140>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0142> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0142>::VRString[] = "IS";
const char TagToType<0x3008,0x0142>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0150> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0150>::VRString[] = "SQ";
const char TagToType<0x3008,0x0150>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0152> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0152>::VRString[] = "IS";
const char TagToType<0x3008,0x0152>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0160> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0160>::VRString[] = "SQ";
const char TagToType<0x3008,0x0160>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0162> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0162>::VRString[] = "DA";
const char TagToType<0x3008,0x0162>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0164> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0164>::VRString[] = "TM";
const char TagToType<0x3008,0x0164>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0166> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0166>::VRString[] = "DA";
const char TagToType<0x3008,0x0166>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0168> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0168>::VRString[] = "TM";
const char TagToType<0x3008,0x0168>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0200> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0200>::VRString[] = "CS";
const char TagToType<0x3008,0x0200>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0202> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0202>::VRString[] = "ST";
const char TagToType<0x3008,0x0202>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0220> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0220>::VRString[] = "SQ";
const char TagToType<0x3008,0x0220>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0223> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0223>::VRString[] = "IS";
const char TagToType<0x3008,0x0223>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0224> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0224>::VRString[] = "CS";
const char TagToType<0x3008,0x0224>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0230> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0230>::VRString[] = "CS";
const char TagToType<0x3008,0x0230>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0240> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0240>::VRString[] = "SQ";
const char TagToType<0x3008,0x0240>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0250> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0250>::VRString[] = "DA";
const char TagToType<0x3008,0x0250>::VMString[] = "1";
template <> struct TagToType<0x3008,0x0251> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x3008,0x0251>::VRString[] = "TM";
const char TagToType<0x3008,0x0251>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0002> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0002>::VRString[] = "SH";
const char TagToType<0x300a,0x0002>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0003> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0003>::VRString[] = "LO";
const char TagToType<0x300a,0x0003>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0004> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0004>::VRString[] = "ST";
const char TagToType<0x300a,0x0004>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0006> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0006>::VRString[] = "DA";
const char TagToType<0x300a,0x0006>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0007> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0007>::VRString[] = "TM";
const char TagToType<0x300a,0x0007>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0009> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x300a,0x0009>::VRString[] = "LO";
const char TagToType<0x300a,0x0009>::VMString[] = "1-n";
template <> struct TagToType<0x300a,0x000a> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x000a>::VRString[] = "CS";
const char TagToType<0x300a,0x000a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x000b> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x300a,0x000b>::VRString[] = "LO";
const char TagToType<0x300a,0x000b>::VMString[] = "1-n";
template <> struct TagToType<0x300a,0x000c> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x000c>::VRString[] = "CS";
const char TagToType<0x300a,0x000c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x000e> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x000e>::VRString[] = "ST";
const char TagToType<0x300a,0x000e>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0010> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0010>::VRString[] = "SQ";
const char TagToType<0x300a,0x0010>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0012> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0012>::VRString[] = "IS";
const char TagToType<0x300a,0x0012>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0013> {
static const char VRString[];
typedef VRToType<VR::UI>::Type Type;
enum { VRType = VR::UI };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0013>::VRString[] = "UI";
const char TagToType<0x300a,0x0013>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0014> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0014>::VRString[] = "CS";
const char TagToType<0x300a,0x0014>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0015> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0015>::VRString[] = "CS";
const char TagToType<0x300a,0x0015>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0016> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0016>::VRString[] = "LO";
const char TagToType<0x300a,0x0016>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0018> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x300a,0x0018>::VRString[] = "DS";
const char TagToType<0x300a,0x0018>::VMString[] = "3";
template <> struct TagToType<0x300a,0x001a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x001a>::VRString[] = "DS";
const char TagToType<0x300a,0x001a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0020>::VRString[] = "CS";
const char TagToType<0x300a,0x0020>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0021> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0021>::VRString[] = "DS";
const char TagToType<0x300a,0x0021>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0022> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0022>::VRString[] = "DS";
const char TagToType<0x300a,0x0022>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0023> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0023>::VRString[] = "DS";
const char TagToType<0x300a,0x0023>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0025> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0025>::VRString[] = "DS";
const char TagToType<0x300a,0x0025>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0026> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0026>::VRString[] = "DS";
const char TagToType<0x300a,0x0026>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0027> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0027>::VRString[] = "DS";
const char TagToType<0x300a,0x0027>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0028> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0028>::VRString[] = "DS";
const char TagToType<0x300a,0x0028>::VMString[] = "1";
template <> struct TagToType<0x300a,0x002a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x002a>::VRString[] = "DS";
const char TagToType<0x300a,0x002a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x002b> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x002b>::VRString[] = "DS";
const char TagToType<0x300a,0x002b>::VMString[] = "1";
template <> struct TagToType<0x300a,0x002c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x002c>::VRString[] = "DS";
const char TagToType<0x300a,0x002c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x002d> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x002d>::VRString[] = "DS";
const char TagToType<0x300a,0x002d>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0040> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0040>::VRString[] = "SQ";
const char TagToType<0x300a,0x0040>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0042> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0042>::VRString[] = "IS";
const char TagToType<0x300a,0x0042>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0043> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0043>::VRString[] = "SH";
const char TagToType<0x300a,0x0043>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0044> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0044>::VRString[] = "DS";
const char TagToType<0x300a,0x0044>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0046> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0046>::VRString[] = "DS";
const char TagToType<0x300a,0x0046>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0048> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0048>::VRString[] = "SQ";
const char TagToType<0x300a,0x0048>::VMString[] = "1";
template <> struct TagToType<0x300a,0x004a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x004a>::VRString[] = "DS";
const char TagToType<0x300a,0x004a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x004b> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x004b>::VRString[] = "FL";
const char TagToType<0x300a,0x004b>::VMString[] = "1";
template <> struct TagToType<0x300a,0x004c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x004c>::VRString[] = "DS";
const char TagToType<0x300a,0x004c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x004e> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x004e>::VRString[] = "DS";
const char TagToType<0x300a,0x004e>::VMString[] = "1";
template <> struct TagToType<0x300a,0x004f> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x004f>::VRString[] = "FL";
const char TagToType<0x300a,0x004f>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0050> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0050>::VRString[] = "FL";
const char TagToType<0x300a,0x0050>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0051> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0051>::VRString[] = "DS";
const char TagToType<0x300a,0x0051>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0052> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0052>::VRString[] = "DS";
const char TagToType<0x300a,0x0052>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0053> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0053>::VRString[] = "DS";
const char TagToType<0x300a,0x0053>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0055> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0055>::VRString[] = "CS";
const char TagToType<0x300a,0x0055>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0070> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0070>::VRString[] = "SQ";
const char TagToType<0x300a,0x0070>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0071> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0071>::VRString[] = "IS";
const char TagToType<0x300a,0x0071>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0072> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0072>::VRString[] = "LO";
const char TagToType<0x300a,0x0072>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0078> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0078>::VRString[] = "IS";
const char TagToType<0x300a,0x0078>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0079> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0079>::VRString[] = "IS";
const char TagToType<0x300a,0x0079>::VMString[] = "1";
template <> struct TagToType<0x300a,0x007a> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x007a>::VRString[] = "IS";
const char TagToType<0x300a,0x007a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x007b> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x007b>::VRString[] = "LT";
const char TagToType<0x300a,0x007b>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0080> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0080>::VRString[] = "IS";
const char TagToType<0x300a,0x0080>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0082> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x300a,0x0082>::VRString[] = "DS";
const char TagToType<0x300a,0x0082>::VMString[] = "3";
template <> struct TagToType<0x300a,0x0084> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0084>::VRString[] = "DS";
const char TagToType<0x300a,0x0084>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0086> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0086>::VRString[] = "DS";
const char TagToType<0x300a,0x0086>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0088> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0088>::VRString[] = "FL";
const char TagToType<0x300a,0x0088>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0089> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0089>::VRString[] = "FL";
const char TagToType<0x300a,0x0089>::VMString[] = "1";
template <> struct TagToType<0x300a,0x008a> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x008a>::VRString[] = "FL";
const char TagToType<0x300a,0x008a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00a0> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00a0>::VRString[] = "IS";
const char TagToType<0x300a,0x00a0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00a2> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x300a,0x00a2>::VRString[] = "DS";
const char TagToType<0x300a,0x00a2>::VMString[] = "3";
template <> struct TagToType<0x300a,0x00a4> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00a4>::VRString[] = "DS";
const char TagToType<0x300a,0x00a4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00b0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00b0>::VRString[] = "SQ";
const char TagToType<0x300a,0x00b0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00b2> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00b2>::VRString[] = "SH";
const char TagToType<0x300a,0x00b2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00b3> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00b3>::VRString[] = "CS";
const char TagToType<0x300a,0x00b3>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00b4> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00b4>::VRString[] = "DS";
const char TagToType<0x300a,0x00b4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00b6> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00b6>::VRString[] = "SQ";
const char TagToType<0x300a,0x00b6>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00b8> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00b8>::VRString[] = "CS";
const char TagToType<0x300a,0x00b8>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00ba> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00ba>::VRString[] = "DS";
const char TagToType<0x300a,0x00ba>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00bb> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00bb>::VRString[] = "FL";
const char TagToType<0x300a,0x00bb>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00bc> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00bc>::VRString[] = "IS";
const char TagToType<0x300a,0x00bc>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00be> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3_n };
static const char VMString[];
};
const char TagToType<0x300a,0x00be>::VRString[] = "DS";
const char TagToType<0x300a,0x00be>::VMString[] = "3-n";
template <> struct TagToType<0x300a,0x00c0> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00c0>::VRString[] = "IS";
const char TagToType<0x300a,0x00c0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00c2> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00c2>::VRString[] = "LO";
const char TagToType<0x300a,0x00c2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00c3> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00c3>::VRString[] = "ST";
const char TagToType<0x300a,0x00c3>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00c4> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00c4>::VRString[] = "CS";
const char TagToType<0x300a,0x00c4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00c6> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00c6>::VRString[] = "CS";
const char TagToType<0x300a,0x00c6>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00c7> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00c7>::VRString[] = "CS";
const char TagToType<0x300a,0x00c7>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00c8> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00c8>::VRString[] = "IS";
const char TagToType<0x300a,0x00c8>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00ca> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00ca>::VRString[] = "SQ";
const char TagToType<0x300a,0x00ca>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00cc> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x300a,0x00cc>::VRString[] = "LO";
const char TagToType<0x300a,0x00cc>::VMString[] = "1-n";
template <> struct TagToType<0x300a,0x00ce> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00ce>::VRString[] = "CS";
const char TagToType<0x300a,0x00ce>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00d0> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00d0>::VRString[] = "IS";
const char TagToType<0x300a,0x00d0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00d1> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00d1>::VRString[] = "SQ";
const char TagToType<0x300a,0x00d1>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00d2> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00d2>::VRString[] = "IS";
const char TagToType<0x300a,0x00d2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00d3> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00d3>::VRString[] = "CS";
const char TagToType<0x300a,0x00d3>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00d4> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00d4>::VRString[] = "SH";
const char TagToType<0x300a,0x00d4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00d5> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00d5>::VRString[] = "IS";
const char TagToType<0x300a,0x00d5>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00d6> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00d6>::VRString[] = "DS";
const char TagToType<0x300a,0x00d6>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00d7> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00d7>::VRString[] = "FL";
const char TagToType<0x300a,0x00d7>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00d8> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00d8>::VRString[] = "DS";
const char TagToType<0x300a,0x00d8>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00d9> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00d9>::VRString[] = "FL";
const char TagToType<0x300a,0x00d9>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00da> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00da>::VRString[] = "DS";
const char TagToType<0x300a,0x00da>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00db> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00db>::VRString[] = "FL";
const char TagToType<0x300a,0x00db>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00dc> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00dc>::VRString[] = "SH";
const char TagToType<0x300a,0x00dc>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00dd> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00dd>::VRString[] = "ST";
const char TagToType<0x300a,0x00dd>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00e0> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00e0>::VRString[] = "IS";
const char TagToType<0x300a,0x00e0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00e1> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00e1>::VRString[] = "SH";
const char TagToType<0x300a,0x00e1>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00e2> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00e2>::VRString[] = "DS";
const char TagToType<0x300a,0x00e2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00e3> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00e3>::VRString[] = "SQ";
const char TagToType<0x300a,0x00e3>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00e4> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00e4>::VRString[] = "IS";
const char TagToType<0x300a,0x00e4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00e5> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00e5>::VRString[] = "SH";
const char TagToType<0x300a,0x00e5>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00e6> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00e6>::VRString[] = "DS";
const char TagToType<0x300a,0x00e6>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00e7> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00e7>::VRString[] = "IS";
const char TagToType<0x300a,0x00e7>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00e8> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00e8>::VRString[] = "IS";
const char TagToType<0x300a,0x00e8>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00e9> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x300a,0x00e9>::VRString[] = "DS";
const char TagToType<0x300a,0x00e9>::VMString[] = "2";
template <> struct TagToType<0x300a,0x00ea> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x300a,0x00ea>::VRString[] = "DS";
const char TagToType<0x300a,0x00ea>::VMString[] = "2";
template <> struct TagToType<0x300a,0x00eb> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x300a,0x00eb>::VRString[] = "DS";
const char TagToType<0x300a,0x00eb>::VMString[] = "1-n";
template <> struct TagToType<0x300a,0x00ec> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x300a,0x00ec>::VRString[] = "DS";
const char TagToType<0x300a,0x00ec>::VMString[] = "1-n";
template <> struct TagToType<0x300a,0x00ed> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00ed>::VRString[] = "IS";
const char TagToType<0x300a,0x00ed>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00ee> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00ee>::VRString[] = "CS";
const char TagToType<0x300a,0x00ee>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00f0> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00f0>::VRString[] = "IS";
const char TagToType<0x300a,0x00f0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00f2> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00f2>::VRString[] = "DS";
const char TagToType<0x300a,0x00f2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00f3> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00f3>::VRString[] = "FL";
const char TagToType<0x300a,0x00f3>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00f4> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00f4>::VRString[] = "SQ";
const char TagToType<0x300a,0x00f4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00f5> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00f5>::VRString[] = "SH";
const char TagToType<0x300a,0x00f5>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00f6> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00f6>::VRString[] = "DS";
const char TagToType<0x300a,0x00f6>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00f7> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00f7>::VRString[] = "FL";
const char TagToType<0x300a,0x00f7>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00f8> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00f8>::VRString[] = "CS";
const char TagToType<0x300a,0x00f8>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00f9> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00f9>::VRString[] = "LO";
const char TagToType<0x300a,0x00f9>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00fa> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00fa>::VRString[] = "CS";
const char TagToType<0x300a,0x00fa>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00fb> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00fb>::VRString[] = "CS";
const char TagToType<0x300a,0x00fb>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00fc> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00fc>::VRString[] = "IS";
const char TagToType<0x300a,0x00fc>::VMString[] = "1";
template <> struct TagToType<0x300a,0x00fe> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x00fe>::VRString[] = "LO";
const char TagToType<0x300a,0x00fe>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0100> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0100>::VRString[] = "DS";
const char TagToType<0x300a,0x0100>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0102> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0102>::VRString[] = "DS";
const char TagToType<0x300a,0x0102>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0104> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0104>::VRString[] = "IS";
const char TagToType<0x300a,0x0104>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0106> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2_2n };
static const char VMString[];
};
const char TagToType<0x300a,0x0106>::VRString[] = "DS";
const char TagToType<0x300a,0x0106>::VMString[] = "2-2n";
template <> struct TagToType<0x300a,0x0107> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0107>::VRString[] = "SQ";
const char TagToType<0x300a,0x0107>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0108> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0108>::VRString[] = "SH";
const char TagToType<0x300a,0x0108>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0109> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0109>::VRString[] = "CS";
const char TagToType<0x300a,0x0109>::VMString[] = "1";
template <> struct TagToType<0x300a,0x010a> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x010a>::VRString[] = "LO";
const char TagToType<0x300a,0x010a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x010c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x010c>::VRString[] = "DS";
const char TagToType<0x300a,0x010c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x010e> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x010e>::VRString[] = "DS";
const char TagToType<0x300a,0x010e>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0110> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0110>::VRString[] = "IS";
const char TagToType<0x300a,0x0110>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0111> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0111>::VRString[] = "SQ";
const char TagToType<0x300a,0x0111>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0112> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0112>::VRString[] = "IS";
const char TagToType<0x300a,0x0112>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0114> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0114>::VRString[] = "DS";
const char TagToType<0x300a,0x0114>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0115> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0115>::VRString[] = "DS";
const char TagToType<0x300a,0x0115>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0116> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0116>::VRString[] = "SQ";
const char TagToType<0x300a,0x0116>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0118> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0118>::VRString[] = "CS";
const char TagToType<0x300a,0x0118>::VMString[] = "1";
template <> struct TagToType<0x300a,0x011a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x011a>::VRString[] = "SQ";
const char TagToType<0x300a,0x011a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x011c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM2_2n };
static const char VMString[];
};
const char TagToType<0x300a,0x011c>::VRString[] = "DS";
const char TagToType<0x300a,0x011c>::VMString[] = "2-2n";
template <> struct TagToType<0x300a,0x011e> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x011e>::VRString[] = "DS";
const char TagToType<0x300a,0x011e>::VMString[] = "1";
template <> struct TagToType<0x300a,0x011f> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x011f>::VRString[] = "CS";
const char TagToType<0x300a,0x011f>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0120> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0120>::VRString[] = "DS";
const char TagToType<0x300a,0x0120>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0121> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0121>::VRString[] = "CS";
const char TagToType<0x300a,0x0121>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0122> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0122>::VRString[] = "DS";
const char TagToType<0x300a,0x0122>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0123> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0123>::VRString[] = "CS";
const char TagToType<0x300a,0x0123>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0124> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0124>::VRString[] = "DS";
const char TagToType<0x300a,0x0124>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0125> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0125>::VRString[] = "DS";
const char TagToType<0x300a,0x0125>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0126> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0126>::VRString[] = "CS";
const char TagToType<0x300a,0x0126>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0128> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0128>::VRString[] = "DS";
const char TagToType<0x300a,0x0128>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0129> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0129>::VRString[] = "DS";
const char TagToType<0x300a,0x0129>::VMString[] = "1";
template <> struct TagToType<0x300a,0x012a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x012a>::VRString[] = "DS";
const char TagToType<0x300a,0x012a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x012c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x300a,0x012c>::VRString[] = "DS";
const char TagToType<0x300a,0x012c>::VMString[] = "3";
template <> struct TagToType<0x300a,0x012e> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x300a,0x012e>::VRString[] = "DS";
const char TagToType<0x300a,0x012e>::VMString[] = "3";
template <> struct TagToType<0x300a,0x0130> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0130>::VRString[] = "DS";
const char TagToType<0x300a,0x0130>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0134> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0134>::VRString[] = "DS";
const char TagToType<0x300a,0x0134>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0140> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0140>::VRString[] = "FL";
const char TagToType<0x300a,0x0140>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0142> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0142>::VRString[] = "CS";
const char TagToType<0x300a,0x0142>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0144> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0144>::VRString[] = "FL";
const char TagToType<0x300a,0x0144>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0146> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0146>::VRString[] = "CS";
const char TagToType<0x300a,0x0146>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0148> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0148>::VRString[] = "FL";
const char TagToType<0x300a,0x0148>::VMString[] = "1";
template <> struct TagToType<0x300a,0x014a> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x014a>::VRString[] = "FL";
const char TagToType<0x300a,0x014a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x014c> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x014c>::VRString[] = "CS";
const char TagToType<0x300a,0x014c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x014e> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x014e>::VRString[] = "FL";
const char TagToType<0x300a,0x014e>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0180> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0180>::VRString[] = "SQ";
const char TagToType<0x300a,0x0180>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0182> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0182>::VRString[] = "IS";
const char TagToType<0x300a,0x0182>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0183> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0183>::VRString[] = "LO";
const char TagToType<0x300a,0x0183>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0184> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0184>::VRString[] = "LO";
const char TagToType<0x300a,0x0184>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0190> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0190>::VRString[] = "SQ";
const char TagToType<0x300a,0x0190>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0192> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0192>::VRString[] = "CS";
const char TagToType<0x300a,0x0192>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0194> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0194>::VRString[] = "SH";
const char TagToType<0x300a,0x0194>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0196> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0196>::VRString[] = "ST";
const char TagToType<0x300a,0x0196>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0198> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0198>::VRString[] = "SH";
const char TagToType<0x300a,0x0198>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0199> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0199>::VRString[] = "FL";
const char TagToType<0x300a,0x0199>::VMString[] = "1";
template <> struct TagToType<0x300a,0x019a> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x019a>::VRString[] = "FL";
const char TagToType<0x300a,0x019a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01a0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01a0>::VRString[] = "SQ";
const char TagToType<0x300a,0x01a0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01a2> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01a2>::VRString[] = "CS";
const char TagToType<0x300a,0x01a2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01a4> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01a4>::VRString[] = "SH";
const char TagToType<0x300a,0x01a4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01a6> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01a6>::VRString[] = "ST";
const char TagToType<0x300a,0x01a6>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01a8> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01a8>::VRString[] = "SH";
const char TagToType<0x300a,0x01a8>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01b0> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01b0>::VRString[] = "CS";
const char TagToType<0x300a,0x01b0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01b2> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01b2>::VRString[] = "ST";
const char TagToType<0x300a,0x01b2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01b4> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01b4>::VRString[] = "SQ";
const char TagToType<0x300a,0x01b4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01b6> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01b6>::VRString[] = "CS";
const char TagToType<0x300a,0x01b6>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01b8> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01b8>::VRString[] = "SH";
const char TagToType<0x300a,0x01b8>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01ba> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01ba>::VRString[] = "ST";
const char TagToType<0x300a,0x01ba>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01bc> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01bc>::VRString[] = "DS";
const char TagToType<0x300a,0x01bc>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01d0> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01d0>::VRString[] = "ST";
const char TagToType<0x300a,0x01d0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01d2> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01d2>::VRString[] = "DS";
const char TagToType<0x300a,0x01d2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01d4> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01d4>::VRString[] = "DS";
const char TagToType<0x300a,0x01d4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x01d6> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x01d6>::VRString[] = "DS";
const char TagToType<0x300a,0x01d6>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0200> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0200>::VRString[] = "CS";
const char TagToType<0x300a,0x0200>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0202> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0202>::VRString[] = "CS";
const char TagToType<0x300a,0x0202>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0206> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0206>::VRString[] = "SQ";
const char TagToType<0x300a,0x0206>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0210> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0210>::VRString[] = "SQ";
const char TagToType<0x300a,0x0210>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0212> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0212>::VRString[] = "IS";
const char TagToType<0x300a,0x0212>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0214> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0214>::VRString[] = "CS";
const char TagToType<0x300a,0x0214>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0216> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0216>::VRString[] = "LO";
const char TagToType<0x300a,0x0216>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0218> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0218>::VRString[] = "DS";
const char TagToType<0x300a,0x0218>::VMString[] = "1";
template <> struct TagToType<0x300a,0x021a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x021a>::VRString[] = "DS";
const char TagToType<0x300a,0x021a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0222> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0222>::VRString[] = "DS";
const char TagToType<0x300a,0x0222>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0224> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0224>::VRString[] = "DS";
const char TagToType<0x300a,0x0224>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0226> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0226>::VRString[] = "LO";
const char TagToType<0x300a,0x0226>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0228> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0228>::VRString[] = "DS";
const char TagToType<0x300a,0x0228>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0229> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0229>::VRString[] = "CS";
const char TagToType<0x300a,0x0229>::VMString[] = "1";
template <> struct TagToType<0x300a,0x022a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x022a>::VRString[] = "DS";
const char TagToType<0x300a,0x022a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x022b> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x022b>::VRString[] = "DS";
const char TagToType<0x300a,0x022b>::VMString[] = "1";
template <> struct TagToType<0x300a,0x022c> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x022c>::VRString[] = "DA";
const char TagToType<0x300a,0x022c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x022e> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x022e>::VRString[] = "TM";
const char TagToType<0x300a,0x022e>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0230> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0230>::VRString[] = "SQ";
const char TagToType<0x300a,0x0230>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0232> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0232>::VRString[] = "CS";
const char TagToType<0x300a,0x0232>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0234> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0234>::VRString[] = "IS";
const char TagToType<0x300a,0x0234>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0236> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0236>::VRString[] = "LO";
const char TagToType<0x300a,0x0236>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0238> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0238>::VRString[] = "LO";
const char TagToType<0x300a,0x0238>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0240> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0240>::VRString[] = "IS";
const char TagToType<0x300a,0x0240>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0242> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0242>::VRString[] = "SH";
const char TagToType<0x300a,0x0242>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0244> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0244>::VRString[] = "LO";
const char TagToType<0x300a,0x0244>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0250> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0250>::VRString[] = "DS";
const char TagToType<0x300a,0x0250>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0260> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0260>::VRString[] = "SQ";
const char TagToType<0x300a,0x0260>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0262> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0262>::VRString[] = "IS";
const char TagToType<0x300a,0x0262>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0263> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0263>::VRString[] = "SH";
const char TagToType<0x300a,0x0263>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0264> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0264>::VRString[] = "CS";
const char TagToType<0x300a,0x0264>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0266> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0266>::VRString[] = "LO";
const char TagToType<0x300a,0x0266>::VMString[] = "1";
template <> struct TagToType<0x300a,0x026a> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x026a>::VRString[] = "DS";
const char TagToType<0x300a,0x026a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x026c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x026c>::VRString[] = "DS";
const char TagToType<0x300a,0x026c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0280> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0280>::VRString[] = "SQ";
const char TagToType<0x300a,0x0280>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0282> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0282>::VRString[] = "IS";
const char TagToType<0x300a,0x0282>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0284> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0284>::VRString[] = "DS";
const char TagToType<0x300a,0x0284>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0286> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0286>::VRString[] = "DS";
const char TagToType<0x300a,0x0286>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0288> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0288>::VRString[] = "CS";
const char TagToType<0x300a,0x0288>::VMString[] = "1";
template <> struct TagToType<0x300a,0x028a> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x028a>::VRString[] = "IS";
const char TagToType<0x300a,0x028a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x028c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x028c>::VRString[] = "DS";
const char TagToType<0x300a,0x028c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0290> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0290>::VRString[] = "IS";
const char TagToType<0x300a,0x0290>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0291> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0291>::VRString[] = "SH";
const char TagToType<0x300a,0x0291>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0292> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0292>::VRString[] = "CS";
const char TagToType<0x300a,0x0292>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0294> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0294>::VRString[] = "LO";
const char TagToType<0x300a,0x0294>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0296> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0296>::VRString[] = "DS";
const char TagToType<0x300a,0x0296>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0298> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0298>::VRString[] = "LO";
const char TagToType<0x300a,0x0298>::VMString[] = "1";
template <> struct TagToType<0x300a,0x029c> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x029c>::VRString[] = "DS";
const char TagToType<0x300a,0x029c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x029e> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x029e>::VRString[] = "DS";
const char TagToType<0x300a,0x029e>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02a0> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02a0>::VRString[] = "DS";
const char TagToType<0x300a,0x02a0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02a2> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02a2>::VRString[] = "IS";
const char TagToType<0x300a,0x02a2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02a4> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02a4>::VRString[] = "DS";
const char TagToType<0x300a,0x02a4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02b0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02b0>::VRString[] = "SQ";
const char TagToType<0x300a,0x02b0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02b2> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02b2>::VRString[] = "IS";
const char TagToType<0x300a,0x02b2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02b3> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02b3>::VRString[] = "SH";
const char TagToType<0x300a,0x02b3>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02b4> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02b4>::VRString[] = "LO";
const char TagToType<0x300a,0x02b4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02b8> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02b8>::VRString[] = "DS";
const char TagToType<0x300a,0x02b8>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02ba> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02ba>::VRString[] = "DS";
const char TagToType<0x300a,0x02ba>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02c8> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02c8>::VRString[] = "DS";
const char TagToType<0x300a,0x02c8>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02d0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02d0>::VRString[] = "SQ";
const char TagToType<0x300a,0x02d0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02d2> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02d2>::VRString[] = "DS";
const char TagToType<0x300a,0x02d2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02d4> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x300a,0x02d4>::VRString[] = "DS";
const char TagToType<0x300a,0x02d4>::VMString[] = "3";
template <> struct TagToType<0x300a,0x02d6> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02d6>::VRString[] = "DS";
const char TagToType<0x300a,0x02d6>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02e0> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02e0>::VRString[] = "CS";
const char TagToType<0x300a,0x02e0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02e1> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02e1>::VRString[] = "CS";
const char TagToType<0x300a,0x02e1>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02e2> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x300a,0x02e2>::VRString[] = "DS";
const char TagToType<0x300a,0x02e2>::VMString[] = "1-n";
template <> struct TagToType<0x300a,0x02e3> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02e3>::VRString[] = "FL";
const char TagToType<0x300a,0x02e3>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02e4> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02e4>::VRString[] = "FL";
const char TagToType<0x300a,0x02e4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02e5> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02e5>::VRString[] = "FL";
const char TagToType<0x300a,0x02e5>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02e6> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x300a,0x02e6>::VRString[] = "FL";
const char TagToType<0x300a,0x02e6>::VMString[] = "1-n";
template <> struct TagToType<0x300a,0x02e7> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02e7>::VRString[] = "FL";
const char TagToType<0x300a,0x02e7>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02e8> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02e8>::VRString[] = "FL";
const char TagToType<0x300a,0x02e8>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02ea> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02ea>::VRString[] = "SQ";
const char TagToType<0x300a,0x02ea>::VMString[] = "1";
template <> struct TagToType<0x300a,0x02eb> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x02eb>::VRString[] = "LT";
const char TagToType<0x300a,0x02eb>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0302> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0302>::VRString[] = "IS";
const char TagToType<0x300a,0x0302>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0304> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0304>::VRString[] = "IS";
const char TagToType<0x300a,0x0304>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0306> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0306>::VRString[] = "SS";
const char TagToType<0x300a,0x0306>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0308> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0308>::VRString[] = "CS";
const char TagToType<0x300a,0x0308>::VMString[] = "1";
template <> struct TagToType<0x300a,0x030a> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x300a,0x030a>::VRString[] = "FL";
const char TagToType<0x300a,0x030a>::VMString[] = "2";
template <> struct TagToType<0x300a,0x030c> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x030c>::VRString[] = "SQ";
const char TagToType<0x300a,0x030c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x030d> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x030d>::VRString[] = "FL";
const char TagToType<0x300a,0x030d>::VMString[] = "1";
template <> struct TagToType<0x300a,0x030f> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x030f>::VRString[] = "SH";
const char TagToType<0x300a,0x030f>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0312> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0312>::VRString[] = "IS";
const char TagToType<0x300a,0x0312>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0314> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0314>::VRString[] = "SQ";
const char TagToType<0x300a,0x0314>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0316> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0316>::VRString[] = "IS";
const char TagToType<0x300a,0x0316>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0318> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0318>::VRString[] = "SH";
const char TagToType<0x300a,0x0318>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0320> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0320>::VRString[] = "CS";
const char TagToType<0x300a,0x0320>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0322> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0322>::VRString[] = "LO";
const char TagToType<0x300a,0x0322>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0330> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0330>::VRString[] = "IS";
const char TagToType<0x300a,0x0330>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0332> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0332>::VRString[] = "SQ";
const char TagToType<0x300a,0x0332>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0334> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0334>::VRString[] = "IS";
const char TagToType<0x300a,0x0334>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0336> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0336>::VRString[] = "SH";
const char TagToType<0x300a,0x0336>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0338> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0338>::VRString[] = "CS";
const char TagToType<0x300a,0x0338>::VMString[] = "1";
template <> struct TagToType<0x300a,0x033a> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x033a>::VRString[] = "LO";
const char TagToType<0x300a,0x033a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x033c> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x033c>::VRString[] = "FL";
const char TagToType<0x300a,0x033c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0340> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0340>::VRString[] = "IS";
const char TagToType<0x300a,0x0340>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0342> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0342>::VRString[] = "SQ";
const char TagToType<0x300a,0x0342>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0344> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0344>::VRString[] = "IS";
const char TagToType<0x300a,0x0344>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0346> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0346>::VRString[] = "SH";
const char TagToType<0x300a,0x0346>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0348> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0348>::VRString[] = "CS";
const char TagToType<0x300a,0x0348>::VMString[] = "1";
template <> struct TagToType<0x300a,0x034a> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x034a>::VRString[] = "LO";
const char TagToType<0x300a,0x034a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x034c> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x034c>::VRString[] = "SH";
const char TagToType<0x300a,0x034c>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0350> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0350>::VRString[] = "CS";
const char TagToType<0x300a,0x0350>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0352> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0352>::VRString[] = "SH";
const char TagToType<0x300a,0x0352>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0354> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0354>::VRString[] = "LO";
const char TagToType<0x300a,0x0354>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0356> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0356>::VRString[] = "FL";
const char TagToType<0x300a,0x0356>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0358> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0358>::VRString[] = "FL";
const char TagToType<0x300a,0x0358>::VMString[] = "1";
template <> struct TagToType<0x300a,0x035a> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x035a>::VRString[] = "FL";
const char TagToType<0x300a,0x035a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0360> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0360>::VRString[] = "SQ";
const char TagToType<0x300a,0x0360>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0362> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0362>::VRString[] = "LO";
const char TagToType<0x300a,0x0362>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0364> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0364>::VRString[] = "FL";
const char TagToType<0x300a,0x0364>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0366> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0366>::VRString[] = "FL";
const char TagToType<0x300a,0x0366>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0370> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0370>::VRString[] = "SQ";
const char TagToType<0x300a,0x0370>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0372> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0372>::VRString[] = "LO";
const char TagToType<0x300a,0x0372>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0374> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0374>::VRString[] = "FL";
const char TagToType<0x300a,0x0374>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0380> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0380>::VRString[] = "SQ";
const char TagToType<0x300a,0x0380>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0382> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0382>::VRString[] = "FL";
const char TagToType<0x300a,0x0382>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0384> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0384>::VRString[] = "FL";
const char TagToType<0x300a,0x0384>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0386> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0386>::VRString[] = "FL";
const char TagToType<0x300a,0x0386>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0388> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0388>::VRString[] = "FL";
const char TagToType<0x300a,0x0388>::VMString[] = "1";
template <> struct TagToType<0x300a,0x038a> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x038a>::VRString[] = "FL";
const char TagToType<0x300a,0x038a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0390> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0390>::VRString[] = "SH";
const char TagToType<0x300a,0x0390>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0392> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0392>::VRString[] = "IS";
const char TagToType<0x300a,0x0392>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0394> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x300a,0x0394>::VRString[] = "FL";
const char TagToType<0x300a,0x0394>::VMString[] = "1-n";
template <> struct TagToType<0x300a,0x0396> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x300a,0x0396>::VRString[] = "FL";
const char TagToType<0x300a,0x0396>::VMString[] = "1-n";
template <> struct TagToType<0x300a,0x0398> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x300a,0x0398>::VRString[] = "FL";
const char TagToType<0x300a,0x0398>::VMString[] = "2";
template <> struct TagToType<0x300a,0x039a> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x039a>::VRString[] = "IS";
const char TagToType<0x300a,0x039a>::VMString[] = "1";
template <> struct TagToType<0x300a,0x03a0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x03a0>::VRString[] = "SQ";
const char TagToType<0x300a,0x03a0>::VMString[] = "1";
template <> struct TagToType<0x300a,0x03a2> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x03a2>::VRString[] = "SQ";
const char TagToType<0x300a,0x03a2>::VMString[] = "1";
template <> struct TagToType<0x300a,0x03a4> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x03a4>::VRString[] = "SQ";
const char TagToType<0x300a,0x03a4>::VMString[] = "1";
template <> struct TagToType<0x300a,0x03a6> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x03a6>::VRString[] = "SQ";
const char TagToType<0x300a,0x03a6>::VMString[] = "1";
template <> struct TagToType<0x300a,0x03a8> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x03a8>::VRString[] = "SQ";
const char TagToType<0x300a,0x03a8>::VMString[] = "1";
template <> struct TagToType<0x300a,0x03aa> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x03aa>::VRString[] = "SQ";
const char TagToType<0x300a,0x03aa>::VMString[] = "1";
template <> struct TagToType<0x300a,0x03ac> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x03ac>::VRString[] = "SQ";
const char TagToType<0x300a,0x03ac>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0401> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0401>::VRString[] = "SQ";
const char TagToType<0x300a,0x0401>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0402> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0402>::VRString[] = "ST";
const char TagToType<0x300a,0x0402>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0410> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0410>::VRString[] = "SQ";
const char TagToType<0x300a,0x0410>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0412> {
static const char VRString[];
typedef VRToType<VR::FL>::Type Type;
enum { VRType = VR::FL };
enum { VMType = VM::VM3 };
static const char VMString[];
};
const char TagToType<0x300a,0x0412>::VRString[] = "FL";
const char TagToType<0x300a,0x0412>::VMString[] = "3";
template <> struct TagToType<0x300a,0x0420> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0420>::VRString[] = "SQ";
const char TagToType<0x300a,0x0420>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0421> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0421>::VRString[] = "CS";
const char TagToType<0x300a,0x0421>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0422> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0422>::VRString[] = "ST";
const char TagToType<0x300a,0x0422>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0423> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0423>::VRString[] = "SH";
const char TagToType<0x300a,0x0423>::VMString[] = "1";
template <> struct TagToType<0x300a,0x0424> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300a,0x0424>::VRString[] = "IS";
const char TagToType<0x300a,0x0424>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0002> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0002>::VRString[] = "SQ";
const char TagToType<0x300c,0x0002>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0004> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0004>::VRString[] = "SQ";
const char TagToType<0x300c,0x0004>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0006> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0006>::VRString[] = "IS";
const char TagToType<0x300c,0x0006>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0007> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0007>::VRString[] = "IS";
const char TagToType<0x300c,0x0007>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0008> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0008>::VRString[] = "DS";
const char TagToType<0x300c,0x0008>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0009> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0009>::VRString[] = "DS";
const char TagToType<0x300c,0x0009>::VMString[] = "1";
template <> struct TagToType<0x300c,0x000a> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x000a>::VRString[] = "SQ";
const char TagToType<0x300c,0x000a>::VMString[] = "1";
template <> struct TagToType<0x300c,0x000c> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x000c>::VRString[] = "IS";
const char TagToType<0x300c,0x000c>::VMString[] = "1";
template <> struct TagToType<0x300c,0x000e> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x000e>::VRString[] = "IS";
const char TagToType<0x300c,0x000e>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0020> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0020>::VRString[] = "SQ";
const char TagToType<0x300c,0x0020>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0022> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0022>::VRString[] = "IS";
const char TagToType<0x300c,0x0022>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0040> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0040>::VRString[] = "SQ";
const char TagToType<0x300c,0x0040>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0042> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0042>::VRString[] = "SQ";
const char TagToType<0x300c,0x0042>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0050> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0050>::VRString[] = "SQ";
const char TagToType<0x300c,0x0050>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0051> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0051>::VRString[] = "IS";
const char TagToType<0x300c,0x0051>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0055> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0055>::VRString[] = "SQ";
const char TagToType<0x300c,0x0055>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0060> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0060>::VRString[] = "SQ";
const char TagToType<0x300c,0x0060>::VMString[] = "1";
template <> struct TagToType<0x300c,0x006a> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x006a>::VRString[] = "IS";
const char TagToType<0x300c,0x006a>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0080> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0080>::VRString[] = "SQ";
const char TagToType<0x300c,0x0080>::VMString[] = "1";
template <> struct TagToType<0x300c,0x00a0> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x00a0>::VRString[] = "IS";
const char TagToType<0x300c,0x00a0>::VMString[] = "1";
template <> struct TagToType<0x300c,0x00b0> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x00b0>::VRString[] = "SQ";
const char TagToType<0x300c,0x00b0>::VMString[] = "1";
template <> struct TagToType<0x300c,0x00c0> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x00c0>::VRString[] = "IS";
const char TagToType<0x300c,0x00c0>::VMString[] = "1";
template <> struct TagToType<0x300c,0x00d0> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x00d0>::VRString[] = "IS";
const char TagToType<0x300c,0x00d0>::VMString[] = "1";
template <> struct TagToType<0x300c,0x00e0> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x00e0>::VRString[] = "IS";
const char TagToType<0x300c,0x00e0>::VMString[] = "1";
template <> struct TagToType<0x300c,0x00f0> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x00f0>::VRString[] = "IS";
const char TagToType<0x300c,0x00f0>::VMString[] = "1";
template <> struct TagToType<0x300c,0x00f2> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x00f2>::VRString[] = "SQ";
const char TagToType<0x300c,0x00f2>::VMString[] = "1";
template <> struct TagToType<0x300c,0x00f4> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x00f4>::VRString[] = "IS";
const char TagToType<0x300c,0x00f4>::VMString[] = "1";
template <> struct TagToType<0x300c,0x00f6> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x00f6>::VRString[] = "IS";
const char TagToType<0x300c,0x00f6>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0100> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0100>::VRString[] = "IS";
const char TagToType<0x300c,0x0100>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0102> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0102>::VRString[] = "IS";
const char TagToType<0x300c,0x0102>::VMString[] = "1";
template <> struct TagToType<0x300c,0x0104> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300c,0x0104>::VRString[] = "IS";
const char TagToType<0x300c,0x0104>::VMString[] = "1";
template <> struct TagToType<0x300e,0x0002> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300e,0x0002>::VRString[] = "CS";
const char TagToType<0x300e,0x0002>::VMString[] = "1";
template <> struct TagToType<0x300e,0x0004> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300e,0x0004>::VRString[] = "DA";
const char TagToType<0x300e,0x0004>::VMString[] = "1";
template <> struct TagToType<0x300e,0x0005> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300e,0x0005>::VRString[] = "TM";
const char TagToType<0x300e,0x0005>::VMString[] = "1";
template <> struct TagToType<0x300e,0x0008> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x300e,0x0008>::VRString[] = "PN";
const char TagToType<0x300e,0x0008>::VMString[] = "1";
template <> struct TagToType<0x4000,0x0010> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4000,0x0010>::VRString[] = "LT";
const char TagToType<0x4000,0x0010>::VMString[] = "1";
template <> struct TagToType<0x4000,0x4000> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4000,0x4000>::VRString[] = "LT";
const char TagToType<0x4000,0x4000>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0040> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0040>::VRString[] = "SH";
const char TagToType<0x4008,0x0040>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0042> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0042>::VRString[] = "LO";
const char TagToType<0x4008,0x0042>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0050> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0050>::VRString[] = "SQ";
const char TagToType<0x4008,0x0050>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0100> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0100>::VRString[] = "DA";
const char TagToType<0x4008,0x0100>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0101> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0101>::VRString[] = "TM";
const char TagToType<0x4008,0x0101>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0102> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0102>::VRString[] = "PN";
const char TagToType<0x4008,0x0102>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0103> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0103>::VRString[] = "LO";
const char TagToType<0x4008,0x0103>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0108> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0108>::VRString[] = "DA";
const char TagToType<0x4008,0x0108>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0109> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0109>::VRString[] = "TM";
const char TagToType<0x4008,0x0109>::VMString[] = "1";
template <> struct TagToType<0x4008,0x010a> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x010a>::VRString[] = "PN";
const char TagToType<0x4008,0x010a>::VMString[] = "1";
template <> struct TagToType<0x4008,0x010b> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x010b>::VRString[] = "ST";
const char TagToType<0x4008,0x010b>::VMString[] = "1";
template <> struct TagToType<0x4008,0x010c> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x010c>::VRString[] = "PN";
const char TagToType<0x4008,0x010c>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0111> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0111>::VRString[] = "SQ";
const char TagToType<0x4008,0x0111>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0112> {
static const char VRString[];
typedef VRToType<VR::DA>::Type Type;
enum { VRType = VR::DA };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0112>::VRString[] = "DA";
const char TagToType<0x4008,0x0112>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0113> {
static const char VRString[];
typedef VRToType<VR::TM>::Type Type;
enum { VRType = VR::TM };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0113>::VRString[] = "TM";
const char TagToType<0x4008,0x0113>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0114> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0114>::VRString[] = "PN";
const char TagToType<0x4008,0x0114>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0115> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0115>::VRString[] = "LT";
const char TagToType<0x4008,0x0115>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0117> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0117>::VRString[] = "SQ";
const char TagToType<0x4008,0x0117>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0118> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0118>::VRString[] = "SQ";
const char TagToType<0x4008,0x0118>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0119> {
static const char VRString[];
typedef VRToType<VR::PN>::Type Type;
enum { VRType = VR::PN };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0119>::VRString[] = "PN";
const char TagToType<0x4008,0x0119>::VMString[] = "1";
template <> struct TagToType<0x4008,0x011a> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x011a>::VRString[] = "LO";
const char TagToType<0x4008,0x011a>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0200> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0200>::VRString[] = "SH";
const char TagToType<0x4008,0x0200>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0202> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0202>::VRString[] = "LO";
const char TagToType<0x4008,0x0202>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0210> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0210>::VRString[] = "CS";
const char TagToType<0x4008,0x0210>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0212> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0212>::VRString[] = "CS";
const char TagToType<0x4008,0x0212>::VMString[] = "1";
template <> struct TagToType<0x4008,0x0300> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x0300>::VRString[] = "ST";
const char TagToType<0x4008,0x0300>::VMString[] = "1";
template <> struct TagToType<0x4008,0x4000> {
static const char VRString[];
typedef VRToType<VR::ST>::Type Type;
enum { VRType = VR::ST };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4008,0x4000>::VRString[] = "ST";
const char TagToType<0x4008,0x4000>::VMString[] = "1";
template <> struct TagToType<0x4ffe,0x0001> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x4ffe,0x0001>::VRString[] = "SQ";
const char TagToType<0x4ffe,0x0001>::VMString[] = "1";
template <> struct TagToType<0x5000,0x0005> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x0005>::VRString[] = "US";
const char TagToType<0x5000,0x0005>::VMString[] = "1";
template <> struct TagToType<0x5000,0x0010> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x0010>::VRString[] = "US";
const char TagToType<0x5000,0x0010>::VMString[] = "1";
template <> struct TagToType<0x5000,0x0020> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x0020>::VRString[] = "CS";
const char TagToType<0x5000,0x0020>::VMString[] = "1";
template <> struct TagToType<0x5000,0x0022> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x0022>::VRString[] = "LO";
const char TagToType<0x5000,0x0022>::VMString[] = "1";
template <> struct TagToType<0x5000,0x0030> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x5000,0x0030>::VRString[] = "SH";
const char TagToType<0x5000,0x0030>::VMString[] = "1-n";
template <> struct TagToType<0x5000,0x0040> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x5000,0x0040>::VRString[] = "SH";
const char TagToType<0x5000,0x0040>::VMString[] = "1-n";
template <> struct TagToType<0x5000,0x0103> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x0103>::VRString[] = "US";
const char TagToType<0x5000,0x0103>::VMString[] = "1";
template <> struct TagToType<0x5000,0x0104> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x5000,0x0104>::VRString[] = "US";
const char TagToType<0x5000,0x0104>::VMString[] = "1-n";
template <> struct TagToType<0x5000,0x0105> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x5000,0x0105>::VRString[] = "US";
const char TagToType<0x5000,0x0105>::VMString[] = "1-n";
template <> struct TagToType<0x5000,0x0106> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x5000,0x0106>::VRString[] = "SH";
const char TagToType<0x5000,0x0106>::VMString[] = "1-n";
template <> struct TagToType<0x5000,0x0110> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x5000,0x0110>::VRString[] = "US";
const char TagToType<0x5000,0x0110>::VMString[] = "1-n";
template <> struct TagToType<0x5000,0x0112> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x5000,0x0112>::VRString[] = "US";
const char TagToType<0x5000,0x0112>::VMString[] = "1-n";
template <> struct TagToType<0x5000,0x0114> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x5000,0x0114>::VRString[] = "US";
const char TagToType<0x5000,0x0114>::VMString[] = "1-n";
template <> struct TagToType<0x5000,0x1001> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x1001>::VRString[] = "CS";
const char TagToType<0x5000,0x1001>::VMString[] = "1";
template <> struct TagToType<0x5000,0x2000> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x2000>::VRString[] = "US";
const char TagToType<0x5000,0x2000>::VMString[] = "1";
template <> struct TagToType<0x5000,0x2002> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x2002>::VRString[] = "US";
const char TagToType<0x5000,0x2002>::VMString[] = "1";
template <> struct TagToType<0x5000,0x2004> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x2004>::VRString[] = "US";
const char TagToType<0x5000,0x2004>::VMString[] = "1";
template <> struct TagToType<0x5000,0x2006> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x2006>::VRString[] = "UL";
const char TagToType<0x5000,0x2006>::VMString[] = "1";
template <> struct TagToType<0x5000,0x2008> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x2008>::VRString[] = "UL";
const char TagToType<0x5000,0x2008>::VMString[] = "1";
template <> struct TagToType<0x5000,0x200a> {
static const char VRString[];
typedef VRToType<VR::UL>::Type Type;
enum { VRType = VR::UL };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x200a>::VRString[] = "UL";
const char TagToType<0x5000,0x200a>::VMString[] = "1";
template <> struct TagToType<0x5000,0x200e> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x200e>::VRString[] = "LT";
const char TagToType<0x5000,0x200e>::VMString[] = "1";
template <> struct TagToType<0x5000,0x2500> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x2500>::VRString[] = "LO";
const char TagToType<0x5000,0x2500>::VMString[] = "1";
template <> struct TagToType<0x5000,0x2600> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x2600>::VRString[] = "SQ";
const char TagToType<0x5000,0x2600>::VMString[] = "1";
template <> struct TagToType<0x5000,0x2610> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5000,0x2610>::VRString[] = "US";
const char TagToType<0x5000,0x2610>::VMString[] = "1";
template <> struct TagToType<0x5200,0x9229> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5200,0x9229>::VRString[] = "SQ";
const char TagToType<0x5200,0x9229>::VMString[] = "1";
template <> struct TagToType<0x5200,0x9230> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5200,0x9230>::VRString[] = "SQ";
const char TagToType<0x5200,0x9230>::VMString[] = "1";
template <> struct TagToType<0x5400,0x0100> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5400,0x0100>::VRString[] = "SQ";
const char TagToType<0x5400,0x0100>::VMString[] = "1";
template <> struct TagToType<0x5400,0x1004> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5400,0x1004>::VRString[] = "US";
const char TagToType<0x5400,0x1004>::VMString[] = "1";
template <> struct TagToType<0x5400,0x1006> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5400,0x1006>::VRString[] = "CS";
const char TagToType<0x5400,0x1006>::VMString[] = "1";
template <> struct TagToType<0x5600,0x0010> {
static const char VRString[];
typedef VRToType<VR::OF>::Type Type;
enum { VRType = VR::OF };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5600,0x0010>::VRString[] = "OF";
const char TagToType<0x5600,0x0010>::VMString[] = "1";
template <> struct TagToType<0x5600,0x0020> {
static const char VRString[];
typedef VRToType<VR::OF>::Type Type;
enum { VRType = VR::OF };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x5600,0x0020>::VRString[] = "OF";
const char TagToType<0x5600,0x0020>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0010> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0010>::VRString[] = "US";
const char TagToType<0x6000,0x0010>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0011> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0011>::VRString[] = "US";
const char TagToType<0x6000,0x0011>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0012> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0012>::VRString[] = "US";
const char TagToType<0x6000,0x0012>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0015> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0015>::VRString[] = "IS";
const char TagToType<0x6000,0x0015>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0022> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0022>::VRString[] = "LO";
const char TagToType<0x6000,0x0022>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0040> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0040>::VRString[] = "CS";
const char TagToType<0x6000,0x0040>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0045> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0045>::VRString[] = "LO";
const char TagToType<0x6000,0x0045>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0050> {
static const char VRString[];
typedef VRToType<VR::SS>::Type Type;
enum { VRType = VR::SS };
enum { VMType = VM::VM2 };
static const char VMString[];
};
const char TagToType<0x6000,0x0050>::VRString[] = "SS";
const char TagToType<0x6000,0x0050>::VMString[] = "2";
template <> struct TagToType<0x6000,0x0051> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0051>::VRString[] = "US";
const char TagToType<0x6000,0x0051>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0052> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0052>::VRString[] = "US";
const char TagToType<0x6000,0x0052>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0060> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0060>::VRString[] = "CS";
const char TagToType<0x6000,0x0060>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0061> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0061>::VRString[] = "SH";
const char TagToType<0x6000,0x0061>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0062> {
static const char VRString[];
typedef VRToType<VR::SH>::Type Type;
enum { VRType = VR::SH };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0062>::VRString[] = "SH";
const char TagToType<0x6000,0x0062>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0063> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0063>::VRString[] = "CS";
const char TagToType<0x6000,0x0063>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0066> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x6000,0x0066>::VRString[] = "AT";
const char TagToType<0x6000,0x0066>::VMString[] = "1-n";
template <> struct TagToType<0x6000,0x0068> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0068>::VRString[] = "US";
const char TagToType<0x6000,0x0068>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0069> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0069>::VRString[] = "US";
const char TagToType<0x6000,0x0069>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0100> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0100>::VRString[] = "US";
const char TagToType<0x6000,0x0100>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0102> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0102>::VRString[] = "US";
const char TagToType<0x6000,0x0102>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0110> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0110>::VRString[] = "CS";
const char TagToType<0x6000,0x0110>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0200> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0200>::VRString[] = "US";
const char TagToType<0x6000,0x0200>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0800> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x6000,0x0800>::VRString[] = "CS";
const char TagToType<0x6000,0x0800>::VMString[] = "1-n";
template <> struct TagToType<0x6000,0x0802> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0802>::VRString[] = "US";
const char TagToType<0x6000,0x0802>::VMString[] = "1";
template <> struct TagToType<0x6000,0x0803> {
static const char VRString[];
typedef VRToType<VR::AT>::Type Type;
enum { VRType = VR::AT };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x6000,0x0803>::VRString[] = "AT";
const char TagToType<0x6000,0x0803>::VMString[] = "1-n";
template <> struct TagToType<0x6000,0x0804> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x0804>::VRString[] = "US";
const char TagToType<0x6000,0x0804>::VMString[] = "1";
template <> struct TagToType<0x6000,0x1001> {
static const char VRString[];
typedef VRToType<VR::CS>::Type Type;
enum { VRType = VR::CS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x1001>::VRString[] = "CS";
const char TagToType<0x6000,0x1001>::VMString[] = "1";
template <> struct TagToType<0x6000,0x1100> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x1100>::VRString[] = "US";
const char TagToType<0x6000,0x1100>::VMString[] = "1";
template <> struct TagToType<0x6000,0x1101> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x1101>::VRString[] = "US";
const char TagToType<0x6000,0x1101>::VMString[] = "1";
template <> struct TagToType<0x6000,0x1102> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x1102>::VRString[] = "US";
const char TagToType<0x6000,0x1102>::VMString[] = "1";
template <> struct TagToType<0x6000,0x1103> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x1103>::VRString[] = "US";
const char TagToType<0x6000,0x1103>::VMString[] = "1";
template <> struct TagToType<0x6000,0x1200> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x6000,0x1200>::VRString[] = "US";
const char TagToType<0x6000,0x1200>::VMString[] = "1-n";
template <> struct TagToType<0x6000,0x1201> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x6000,0x1201>::VRString[] = "US";
const char TagToType<0x6000,0x1201>::VMString[] = "1-n";
template <> struct TagToType<0x6000,0x1202> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x6000,0x1202>::VRString[] = "US";
const char TagToType<0x6000,0x1202>::VMString[] = "1-n";
template <> struct TagToType<0x6000,0x1203> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1_n };
static const char VMString[];
};
const char TagToType<0x6000,0x1203>::VRString[] = "US";
const char TagToType<0x6000,0x1203>::VMString[] = "1-n";
template <> struct TagToType<0x6000,0x1301> {
static const char VRString[];
typedef VRToType<VR::IS>::Type Type;
enum { VRType = VR::IS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x1301>::VRString[] = "IS";
const char TagToType<0x6000,0x1301>::VMString[] = "1";
template <> struct TagToType<0x6000,0x1302> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x1302>::VRString[] = "DS";
const char TagToType<0x6000,0x1302>::VMString[] = "1";
template <> struct TagToType<0x6000,0x1303> {
static const char VRString[];
typedef VRToType<VR::DS>::Type Type;
enum { VRType = VR::DS };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x1303>::VRString[] = "DS";
const char TagToType<0x6000,0x1303>::VMString[] = "1";
template <> struct TagToType<0x6000,0x1500> {
static const char VRString[];
typedef VRToType<VR::LO>::Type Type;
enum { VRType = VR::LO };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x1500>::VRString[] = "LO";
const char TagToType<0x6000,0x1500>::VMString[] = "1";
template <> struct TagToType<0x6000,0x4000> {
static const char VRString[];
typedef VRToType<VR::LT>::Type Type;
enum { VRType = VR::LT };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x6000,0x4000>::VRString[] = "LT";
const char TagToType<0x6000,0x4000>::VMString[] = "1";
template <> struct TagToType<0x7fe0,0x0020> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x7fe0,0x0020>::VRString[] = "OW";
const char TagToType<0x7fe0,0x0020>::VMString[] = "1";
template <> struct TagToType<0x7fe0,0x0030> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x7fe0,0x0030>::VRString[] = "OW";
const char TagToType<0x7fe0,0x0030>::VMString[] = "1";
template <> struct TagToType<0x7fe0,0x0040> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x7fe0,0x0040>::VRString[] = "OW";
const char TagToType<0x7fe0,0x0040>::VMString[] = "1";
template <> struct TagToType<0x7f00,0x0011> {
static const char VRString[];
typedef VRToType<VR::US>::Type Type;
enum { VRType = VR::US };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x7f00,0x0011>::VRString[] = "US";
const char TagToType<0x7f00,0x0011>::VMString[] = "1";
template <> struct TagToType<0x7f00,0x0020> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x7f00,0x0020>::VRString[] = "OW";
const char TagToType<0x7f00,0x0020>::VMString[] = "1";
template <> struct TagToType<0x7f00,0x0030> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x7f00,0x0030>::VRString[] = "OW";
const char TagToType<0x7f00,0x0030>::VMString[] = "1";
template <> struct TagToType<0x7f00,0x0040> {
static const char VRString[];
typedef VRToType<VR::OW>::Type Type;
enum { VRType = VR::OW };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0x7f00,0x0040>::VRString[] = "OW";
const char TagToType<0x7f00,0x0040>::VMString[] = "1";
template <> struct TagToType<0xfffa,0xfffa> {
static const char VRString[];
typedef VRToType<VR::SQ>::Type Type;
enum { VRType = VR::SQ };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0xfffa,0xfffa>::VRString[] = "SQ";
const char TagToType<0xfffa,0xfffa>::VMString[] = "1";
template <> struct TagToType<0xfffc,0xfffc> {
static const char VRString[];
typedef VRToType<VR::OB>::Type Type;
enum { VRType = VR::OB };
enum { VMType = VM::VM1 };
static const char VMString[];
};
const char TagToType<0xfffc,0xfffc>::VRString[] = "OB";
const char TagToType<0xfffc,0xfffc>::VMString[] = "1";

} // end namespace gdcm
#endif // __gdcmTagToType_h

