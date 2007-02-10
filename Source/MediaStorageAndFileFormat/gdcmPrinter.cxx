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
void PrintValue(VR::VRType const &vr, const Value &v);
//-----------------------------------------------------------------------------
void PrintExplicitDataElement(std::ostream& _os, const ExplicitDataElement &_val, bool printVR, VR::VRType dictVR, Printer::PrintStyles pstyle)
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
      PrintValue(vr, value );
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
#define PrinterTemplateCase(type, rep) \
  case VR::type: \
    {Element<VR::type, VM::VM1> e; \
    memcpy( (void*)(&e), array, sizeof(TypeToType<VR::type>::Type) ); \
    e.Print( os ); }\
    break;
#define PrinterTemplate(rep) \
PrinterTemplateCase(AE,rep) \
PrinterTemplateCase(AS,rep) \
PrinterTemplateCase(AT,rep) \
PrinterTemplateCase(CS,rep) \
PrinterTemplateCase(DA,rep) \
PrinterTemplateCase(DS,rep) \
PrinterTemplateCase(DT,rep) \
PrinterTemplateCase(FL,rep) \
PrinterTemplateCase(FD,rep) \
PrinterTemplateCase(IS,rep) \
PrinterTemplateCase(LO,rep) \
PrinterTemplateCase(LT,rep) \
PrinterTemplateCase(OB,rep) \
PrinterTemplateCase(OF,rep) \
PrinterTemplateCase(OW,rep) \
PrinterTemplateCase(PN,rep) \
PrinterTemplateCase(SH,rep) \
PrinterTemplateCase(SL,rep) \
PrinterTemplateCase(SQ,rep) \
PrinterTemplateCase(SS,rep) \
PrinterTemplateCase(ST,rep) \
PrinterTemplateCase(TM,rep) \
PrinterTemplateCase(UI,rep) \
PrinterTemplateCase(UL,rep) \
PrinterTemplateCase(UN,rep) \
PrinterTemplateCase(US,rep) \
PrinterTemplateCase(UT,rep)

void PrintValue(VR::VRType const &vr, const Value &v)
{
  const ByteValue &bv = static_cast<const ByteValue&>(v);
  const char *array = bv.GetPointer();
  //unsigned short val = *(unsigned short*)(array);
  std::ostream &os = std::cout;
  switch(vr)
    {
    PrinterTemplate(rep)
    default:
      abort();
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
  static const Dicts dicts;
  const Dict &d = dicts.GetPublicDict();
  //static const Dict d;
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
      const DictEntry &entry = d.GetDictEntry(de.GetTag());
      // Use VR from dictionary
      const VR::VRType vr = entry.GetVR();
      const VR::VRType vr_read = de.GetVR();
      if( VR::IsASCII(vr_read) || VR::IsBinary(vr_read) )
        {
        //PrintExplicitDataElement(_os, de, printVR, vr, pstyle);
        PrintExplicitDataElement(_os, de, printVR, vr_read, pstyle);
        }
      else
        {
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

