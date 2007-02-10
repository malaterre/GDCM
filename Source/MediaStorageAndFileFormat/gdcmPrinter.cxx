/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmPrinter.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmDict.h"
#include "gdcmDicts.h"
#include "gdcmGroupDict.h"
//#include "gdcmAttribute.h"
#include "gdcmVR.h"
#include "gdcmStructuredSet.h"

#include <typeinfo> // for typeid

namespace gdcm
{
//-----------------------------------------------------------------------------
Printer::Printer():PrintStyle(Printer::VERBOSE_STYLE)
{
}
//-----------------------------------------------------------------------------
Printer::~Printer()
{
}

#if 1
void PrintValue(VR::VRType const &vr, VM::VMType const &vm, const Value &v);
//-----------------------------------------------------------------------------
void PrintExplicitDataElement(std::ostream& _os, const ExplicitDataElement &_val, bool printVR, VR::VRType dictVR, VM::VMType vm, Printer::PrintStyles pstyle)
{
  const Tag &t = _val.GetTag();
  const VR::VRType vr = _val.GetVR();
  const uint32_t vl = _val.GetVL();
  const Value& value = _val.GetValue();
  (void)printVR;
  if( pstyle == Printer::CONDENSED_STYLE )
    {
    _os << t << " " << vr;
    }
  else
    {
    _os << t << " VR=" << VR::GetVRString(vr);
    }
  if( dictVR != VR::INVALID && !(vr & dictVR) ) //printVR )
    {
    gdcmErrorMacro( "Wrong VR should be " << dictVR );
    // LEADTOOLS_FLOWERS-8-PAL-RLE.dcm has (0040,0253) : CS instead of SH
    //abort();
    }
  if( pstyle == Printer::CONDENSED_STYLE )
    {
    (void)vl;
    _os /*<< "\t " << std::dec << vl  */
      << " [" << value << "]";
    }
  else
    {
    _os << "\tVL=" << std::dec << vl;
    if( VR::IsASCII(vr)  )
      {
      _os << "\t ValueField=[" << value << "]";
      }
    else if ( VR::IsBinary(vr) )
      {
      _os << "\t ValueField=[";
      PrintValue(vr, vm, value );
      _os << "]";
      }
    else 
      abort();
    }
}
//-----------------------------------------------------------------------------
void PrintImplicitDataElement(std::ostream& _os, const ImplicitDataElement &_val, bool printVR, VR::VRType dictVR)
{
  const Tag &t = _val.GetTag();
  const uint32_t vl = _val.GetVL();
  const Value& value = _val.GetValue();
  _os << t;
  if ( printVR )
    {
    _os << " ?VR=" << dictVR;
    }
  _os << "\tVL=" << std::dec << vl
    << "\tValueField=[" << value << "]";
}

//     = reinterpret_cast< const Element<VR::type, VM::VM1>& > ( array );
// os.flush();
#define PrinterTemplateSubCaseOB(type,rep) \
  case VM::rep: \
    {Element<VR::OB, VM::rep> e; \
    assert( VR::type == VR::OB ); \
    e.SetArray( (unsigned char*)array, length, true ); \
    e.Print( os ); }\
    break;
#define PrinterTemplateSubCase(type,rep) \
  case VM::rep: \
    {Element<VR::type, VM::rep> e; \
    /*assert( bv.GetLength() == TypeToLength<VM::rep>::Length * sizeof( TypeToType<VR::type>::Type) ); */ \
    assert( bv.GetLength() == e.GetLength() * sizeof( TypeToType<VR::type>::Type) ); \
    memcpy( (void*)(&e), array, e.GetLength() * sizeof( TypeToType<VR::type>::Type) ); \
    e.Print( os ); }\
    break;
#define PrinterTemplateSub(type) \
switch(vm) { \
PrinterTemplateSubCase(type, VM::VM1) \
PrinterTemplateSubCase(type, VM::VM2) \
PrinterTemplateSubCase(type, VM::VM3) \
PrinterTemplateSubCase(type, VM::VM4) \
PrinterTemplateSubCaseOB(type, VM::VM1_n) \
default: abort(); }

#define PrinterTemplateCase(type) \
  case VR::type: \
    PrinterTemplateSub(type) \
    break;
#define PrinterTemplate() \
switch(vr) { \
PrinterTemplateCase(AE) \
PrinterTemplateCase(AS) \
PrinterTemplateCase(AT) \
PrinterTemplateCase(CS) \
PrinterTemplateCase(DA) \
PrinterTemplateCase(DS) \
PrinterTemplateCase(DT) \
PrinterTemplateCase(FL) \
PrinterTemplateCase(FD) \
PrinterTemplateCase(IS) \
PrinterTemplateCase(LO) \
PrinterTemplateCase(LT) \
PrinterTemplateCase(OB) \
PrinterTemplateCase(OF) \
PrinterTemplateCase(OW) \
PrinterTemplateCase(PN) \
PrinterTemplateCase(SH) \
PrinterTemplateCase(SL) \
PrinterTemplateCase(SQ) \
PrinterTemplateCase(SS) \
PrinterTemplateCase(ST) \
PrinterTemplateCase(TM) \
PrinterTemplateCase(UI) \
PrinterTemplateCase(UL) \
PrinterTemplateCase(UN) \
PrinterTemplateCase(US) \
PrinterTemplateCase(UT) \
default: abort(); }

void PrintValue(VR::VRType const &vr, VM::VMType const &vm, const Value &v)
{
  try
    {
    const ByteValue &bv = dynamic_cast<const ByteValue&>(v);
    const char *array = bv.GetPointer();
    const VL &length = bv.GetLength();
    //unsigned short val = *(unsigned short*)(array);
    std::ostream &os = std::cout;

    // Big phat MACRO:
    PrinterTemplate()
    }
  catch(...)
    {
    }
}

//-----------------------------------------------------------------------------
void PrintImplicitDataElements(Printer &is, StructuredSet<ImplicitDataElement>&ds)
{
  //ImplicitDataElement de;
  Printer::PrintStyles pstyle = is.GetPrintStyle();
  (void)pstyle;
  bool printVR = false; //is.GetPrintVR();

  std::ostream &_os = std::cout;
  //static const Dicts dicts;
  //const Dict &d = dicts.GetPublicDict();
  static const Dict d;
  static const GroupDict gd;
  try
    {
    //while( is.Read(de) )
    StructuredSet<ImplicitDataElement>::DataElementSetIterator it = ds.Begin();
    for( ; it != ds.End(); ++it )
      {
      const ImplicitDataElement &de = *it;
      const DictEntry &entry = d.GetDictEntry(de.GetTag());
      // Use VR from dictionary
      VR::VRType vr = entry.GetVR();
      VM::VMType vm = entry.GetVM();
      if( de.GetTag().GetGroup()%2 && de.GetTag().GetElement() == 0 )
        {
        assert( vr == VR::INVALID );
        vr = VR::UL;
        vm = VM::VM1;
        }
      if( vr == VR::INVALID || VR::IsBinary(vr) || VR::IsASCII( vr ) )
        {
        PrintImplicitDataElement(_os, de, printVR, entry.GetVR());
        }
      else
        {
        const Value& val = de.GetValue();
        _os << de.GetTag();
        if ( printVR )
          {
          _os << " ?VR=" << vr;
          }
        _os << "\tVL=" << std::dec << de.GetVL() << "\tValueField=[";

        // Use super class of the template stuff
        //Attribute af;
        //// Last minute check, is it a Group Length:
        //af.SetVR(vr);
        //af.SetVM(vm);
        //af.SetLength( val.GetLength() );
        //std::istringstream iss;
        //iss.str( std::string( val.GetPointer(), val.GetLength() ) );
        //af.Read( iss );
        //af.Print( _os );
        _os << "]";
        }
      if( de.GetTag().GetElement() == 0x0 )
        {
        _os << "\t\t# (" << gd.GetName(de.GetTag().GetGroup() )
          << ") " << entry.GetName() << std::endl;
        }
      else
        {
        _os << "\t\t# " << entry.GetName() << std::endl;
        }
      }
    }
  catch(std::exception &e)
    {
    std::cerr << "Exception:" << typeid(e).name() << std::endl;
    }
}

//-----------------------------------------------------------------------------
void PrintExplicitDataElements(Printer &is, StructuredSet<ExplicitDataElement> &ds)
{
  //ExplicitDataElement de;

  std::ostream &_os = std::cout;
  static const Dict d;
  static const GroupDict gd;
  Printer::PrintStyles pstyle = is.GetPrintStyle();
  bool printVR = false; //is.GetPrintVR();
  try
    {
    StructuredSet<ExplicitDataElement>::DataElementSetIterator it = ds.Begin();
    for( ; it != ds.End(); ++it )
    //while( !is.eof() && is.Read(de) )
      {
      const ExplicitDataElement &de = *it;
      //is.Read(de);
  if( de.GetTag() == Tag(0x0043,0x1028) )
    {
    std::cerr << "bla" << std::endl;
    }
      const DictEntry &entry = d.GetDictEntry(de.GetTag());
      // Use VR from dictionary
      VR::VRType vr = entry.GetVR();
      VM::VMType vm = entry.GetVM();
      // TODO: FIXME FIXME FIXME
      if ( de.GetTag().GetElement() == 0x0 )
        {
        if( vm == VM::VM0 ) // not found
          {
          vm = VM::VM1; // this is a group length (VR=UL,VM=1)
          }
        if( vr == VR::INVALID ) // not found
          {
          vr = VR::UL;  // this is a group length (VR=UL,VM=1)
          }
        }
      const VR::VRType vr_read = de.GetVR();
      if( de.GetTag().IsPrivate() )
        {
        assert( !de.GetTag().GetElement() || vr == VR::INVALID );
        assert( !de.GetTag().GetElement() || vm == VM::VM0 );
        vr = vr_read; // we have no choice for now but trust it
        if( vr & VR::OB_OW )
          {
          vm = VM::VM1_n;
          }
        else
          {
          vm = VM::VM1;
          }
        }
      assert( vr != VR::INVALID );
      assert( vm != VM::VM0 );
      if( VR::IsASCII(vr_read) || VR::IsBinary(vr_read) )
        {
        //PrintExplicitDataElement(_os, de, printVR, vr, pstyle);
        PrintExplicitDataElement(_os, de, printVR, vr_read, vm, pstyle);
        }
      else
        {
        abort();
        const VM::VMType vm = entry.GetVM();
        const Value& val = de.GetValue();
        _os << de.GetTag();
        if( pstyle == Printer::CONDENSED_STYLE )
          {
          _os << " " << vr_read;
          }
        else
          {
          _os << " VR=" << VR::GetVRString(vr_read);
          }
        if( vr != VR::INVALID && !(vr_read & vr) )
          {
          gdcmErrorMacro( "Wrong VR should be " << vr );
          // PHILIPS_Gyroscan-12-Jpeg_Extended_Process_2_4.dcm
          // 0008,0040 VR=SS VR(?)=US
          // After posting to dicom newsgroup there were reasons for doing SS
          // but in this case user should really do US...
          }
        if( pstyle == Printer::CONDENSED_STYLE )
          {
          _os << /*"\t " << std::dec << de.GetVL() << */
            " ";
          }
        else
          {
          _os << "\tVL=" << std::dec << de.GetVL() 
            << "\tValueField=[";
          }

        // Use super class of the template stuff
        //Attribute af;
        //af.SetVR(vr_read);
        //af.SetVM(vm);
        //af.SetLength( val.GetLength() );
        //std::istringstream iss;
        //iss.str( std::string( val.GetPointer(), val.GetLength() ) );
        //af.Read( iss );
        //af.Print( _os );
        if( pstyle == Printer::CONDENSED_STYLE )
          {
          _os << "]";
          }
        }
      if( de.GetTag().GetElement() == 0x0 )
        {
        _os << "\t\t# (" << gd.GetName(de.GetTag().GetGroup() )
          << ") " << entry.GetName() << std::endl;
        }
      else
        {
        _os << "\t\t# " << entry.GetName() << std::endl;
        }
      }
    }
  catch(std::exception &e)
    {
    std::cerr << "Exception:" << typeid(e).name() << std::endl;
    }
}
#endif

//-----------------------------------------------------------------------------
void Printer::Print(std::ostream& os)
{
  const gdcm::DataSet &ds = *DS;
  const StructuredSetBase *base = ds.GetInternal();
  if ( ds.GetNegociatedType() == TS::Explicit )
    {
    const StructuredSet<ExplicitDataElement> *exds = 
      dynamic_cast< const StructuredSet<ExplicitDataElement>* > ( base );
    PrintExplicitDataElements(*this, const_cast<StructuredSet<ExplicitDataElement>& >(*exds));
    }
  else if ( ds.GetNegociatedType() == TS::Implicit )
    {
    const StructuredSet<ImplicitDataElement> *exds = 
      dynamic_cast< const StructuredSet<ImplicitDataElement>* > ( base );
    PrintImplicitDataElements(*this, const_cast<StructuredSet<ImplicitDataElement>& >(*exds));
    }
  //os << ds << std::endl;
  //DataSet::Iterator it = ds.Begin();
}

}

