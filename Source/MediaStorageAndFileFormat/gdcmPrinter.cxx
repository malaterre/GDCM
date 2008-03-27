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
#include "gdcmPrinter.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmDict.h"
#include "gdcmDicts.h"
#include "gdcmGroupDict.h"
#include "gdcmVR.h"
#include "gdcmVM.h"
#include "gdcmElement.h"
#include "gdcmGlobal.h"
#include "gdcmAttribute.h"

#include "gdcmDataSet.h"

#include <typeinfo> // for typeid

#ifdef _WIN32
#define GDCM_TERMINAL_DISABLE_COLOR
#endif

#ifdef GDCM_TERMINAL_DISABLE_COLOR
#define GDCM_TERMINAL_VT100_NORMAL              ""
#define GDCM_TERMINAL_VT100_BOLD                ""
#define GDCM_TERMINAL_VT100_UNDERLINE           ""
#define GDCM_TERMINAL_VT100_BLINK               ""
#define GDCM_TERMINAL_VT100_INVERSE             ""
#define GDCM_TERMINAL_VT100_FOREGROUND_BLACK    ""
#define GDCM_TERMINAL_VT100_FOREGROUND_RED      ""
#define GDCM_TERMINAL_VT100_FOREGROUND_GREEN    ""
#define GDCM_TERMINAL_VT100_FOREGROUND_YELLOW   ""
#define GDCM_TERMINAL_VT100_FOREGROUND_BLUE     ""
#define GDCM_TERMINAL_VT100_FOREGROUND_MAGENTA  ""
#define GDCM_TERMINAL_VT100_FOREGROUND_CYAN     ""
#define GDCM_TERMINAL_VT100_FOREGROUND_WHITE    ""
#define GDCM_TERMINAL_VT100_BACKGROUND_BLACK    ""
#define GDCM_TERMINAL_VT100_BACKGROUND_RED      ""
#define GDCM_TERMINAL_VT100_BACKGROUND_GREEN    ""
#define GDCM_TERMINAL_VT100_BACKGROUND_YELLOW   ""
#define GDCM_TERMINAL_VT100_BACKGROUND_BLUE     ""
#define GDCM_TERMINAL_VT100_BACKGROUND_MAGENTA  ""
#define GDCM_TERMINAL_VT100_BACKGROUND_CYAN     ""
#define GDCM_TERMINAL_VT100_BACKGROUND_WHITE    ""
#else
#define GDCM_TERMINAL_VT100_NORMAL              "\33[0m"
#define GDCM_TERMINAL_VT100_BOLD                "\33[1m"
#define GDCM_TERMINAL_VT100_UNDERLINE           "\33[4m"
#define GDCM_TERMINAL_VT100_BLINK               "\33[5m"
#define GDCM_TERMINAL_VT100_INVERSE             "\33[7m"
#define GDCM_TERMINAL_VT100_FOREGROUND_BLACK    "\33[30m"
#define GDCM_TERMINAL_VT100_FOREGROUND_RED      "\33[31m"
#define GDCM_TERMINAL_VT100_FOREGROUND_GREEN    "\33[32m"
#define GDCM_TERMINAL_VT100_FOREGROUND_YELLOW   "\33[33m"
#define GDCM_TERMINAL_VT100_FOREGROUND_BLUE     "\33[34m"
#define GDCM_TERMINAL_VT100_FOREGROUND_MAGENTA  "\33[35m"
#define GDCM_TERMINAL_VT100_FOREGROUND_CYAN     "\33[36m"
#define GDCM_TERMINAL_VT100_FOREGROUND_WHITE    "\33[37m"
#define GDCM_TERMINAL_VT100_BACKGROUND_BLACK    "\33[40m"
#define GDCM_TERMINAL_VT100_BACKGROUND_RED      "\33[41m"
#define GDCM_TERMINAL_VT100_BACKGROUND_GREEN    "\33[42m"
#define GDCM_TERMINAL_VT100_BACKGROUND_YELLOW   "\33[43m"
#define GDCM_TERMINAL_VT100_BACKGROUND_BLUE     "\33[44m"
#define GDCM_TERMINAL_VT100_BACKGROUND_MAGENTA  "\33[45m"
#define GDCM_TERMINAL_VT100_BACKGROUND_CYAN     "\33[46m"
#define GDCM_TERMINAL_VT100_BACKGROUND_WHITE    "\33[47m"
#endif

namespace gdcm
{
//-----------------------------------------------------------------------------
Printer::Printer():PrintStyle(Printer::VERBOSE_STYLE),F(0)
{
  MaxPrintLength = 0x100; // Need to be %2 
}
//-----------------------------------------------------------------------------
Printer::~Printer()
{
}

void PrintValue(VR::VRType const &vr, VM const &vm, const Value &v);

//-----------------------------------------------------------------------------
void Printer::PrintElement(std::ostream& os, const DataElement &xde, const DictEntry& entry) 
{
  const Tag &t = xde.GetTag();
  const VR &vr = xde.GetVR();
  const VL &vl = xde.GetVL();
  const Value& value = xde.GetValue();
  VR lvr = vr;

  // FIXME:
  if( xde.IsEmpty() // 0xfffe item thingy
    || entry.GetVR() == VR::INVALID ) // private element with no known VR
    {
    os << xde; 
    return;
    }
  // first of' do the VR:
  if( lvr == VR::UN )
    {
    if( t.GetElement() == 0x0 || t.GetElement() == 0x1 ) // is 0x1 actually UN ?
      {
      lvr = VR::UL;
      }
    else
      {
      //assert( t.IsPublic() );
      lvr = entry.GetVR();
      }
    // Data Element (7FE0,0010) Pixel Data has the Value Representation 
    // OW and shall be encoded in Little Endian.
    if( t == Tag(0x7fe0,0x0010) )
      {
      assert( lvr == VR::OB_OW );
      lvr = VR::OW;
      }
    //if( lvr == VR::UN ) lvr = VR::LO; // why not ?
    }

  VM vm = entry.GetVM();
  if( vm == VM::VM0 )
    {
    assert( lvr != VR::UN );
    //assert( lvr != VR::INVALID );
    assert( t.IsPrivate() || t.GetElement() == 0x0 );
    if ( lvr & VR::OB_OW )
      {
      vm = VM::VM1;
      }
    else
      {
      vm = VM::GetVMTypeFromLength( value.GetLength(), lvr.GetSize() );
      //gdcmWarningMacro( "VM for " << vm );
      if( t.GetElement() == 0x0 )
        {
        //gdcmWarningMacro( "Lgt= " << value.GetLength() << " size= " << vr.GetSize() );
        //assert( vm == VM::VM1 && lvr == VR::UL );
        if( vm != VM::VM1 )  gdcmWarningMacro( "Problem with " << t << " VM would be " << vm );
        }
      }
    }
  // Print Tag and VR:
  os << t << " " << lvr;
  if( lvr == VR::INVALID )
    {
    os << "(" << entry.GetVR() << ")";
    }
  //os << " " << VM::GetVMString( vm ) ;
  //  if( dictVR != VR::INVALID && !(vr & dictVR) )
  //    {
  //    gdcmErrorMacro( "Wrong VR should be " << dictVR );
  //    // LEADTOOLS_FLOWERS-8-PAL-RLE.dcm has (0040,0253) : CS instead of SH
  //    //abort();
  //    }
  //  if( pstyle == Printer::CONDENSED_STYLE )
  //    {
  //    (void)vl;
  //    _os /*<< "\t " << std::dec << vl  */
  //      << " [" << value << "]";
  //    }

  if( !entry.GetVR().Compatible( lvr ) )
    {
    gdcmErrorMacro( "Wrong VR should be " << entry.GetVR() );
    }
  if( VR::IsASCII(lvr) )
    {
    // TODO FIXME (value is a null object)
    if( vl ) os << " [" << value << "] ";
    }
  else if ( lvr == VR::SQ || vl.IsUndefined() )
    {
    //	    os << "DEBUG";
    //	    value.Print( _os );
    }
  else if ( VR::IsBinary(lvr) )
    {
    //os << "\t ValueField=[";
    os << " ";
    if( vl ) PrintValue(lvr, vm, value );
    //os << "]";
    os << " ";
    }
  else 
    {
    std::cerr << "Should not happen: " << lvr << std::endl;
    }
  //
  os << "\t\t# " << std::dec << vl;
  os << ", 1";

  if( vl.IsUndefined() ) { assert ( t == Tag(0x7fe0, 0x0010) || lvr == VR::SQ ) ; }
  if ( lvr == VR::SQ )
    {
    os << std::endl;
    const SequenceOfItems &sqi = static_cast<const SequenceOfItems&>(value);
    SequenceOfItems::ItemVector::const_iterator it = sqi.Items.begin();
    for(; it != sqi.Items.end(); ++it)
      {
      const Item &item = *it;
      const DataSet &ds = item.GetNestedDataSet();
      //const DataSet &exds = ds.GetInternal();
      PrintDataSetOld(os << "  ", ds);
      }
    }
  else if ( vl.IsUndefined() )
    {
    os << std::endl;
    const SequenceOfFragments &sqf = static_cast<const SequenceOfFragments&>(value);
    os << sqf.GetTable() << std::endl;
    SequenceOfFragments::FragmentVector::const_iterator it = sqf.Fragments.begin();
    for(; it != sqf.Fragments.end(); ++it)
      {
      const Fragment &frag = *it;
      const Value &val = frag.GetValue(); (void)val;
      //PrintValue(lvr, vm, val );
      os << "  " << frag << std::endl;
      }
    }
}

template <typename T>
inline char *bswap(char *out, const char *in, size_t length)
{
  assert( !(length % sizeof(T)) );
  assert( out != in );
  for(size_t i = 0; i < length; i+=2)
    {
    //const char copy = in[i];
    out[i] = in[i+1];
    out[i+1] = in[i];
    }
  return out;
}

//-----------------------------------------------------------------------------
	/*
void Printer::PrintElement(std::ostream& os, const ImplicitDataElement &ide, DictEntry const &entry)
{
  const Tag &t = _val.GetTag();
  const uint32_t vl = _val.GetVL();
  _os << t;

  if ( printVR )
    {
    //_os << " (VR=" << VR::GetVRString(dictVR) << ")";
    _os << " " << VR::GetVRString(dictVR) << " ";
    }
  //_os << "\tVL=" << std::dec << vl << "\tValueField=[";
  if( _val.GetVL() )
    {
    // FIXME FIXME: 
    // value could dereference a NULL pointer in case of 0 length...
    const Value& value = _val.GetValue();
    if( dictVR != VR::INVALID && VR::IsBinary(dictVR) )
      {
      PrintValue(dictVR, vm, value);
      }
    else
      {
      _os << "[" << value << "]";
      }
    }
  //_os  << "]";
  _os  << "\t\t";
  _os << "#" << std::setw(4) << std::setfill(' ') << std::dec << vl << ", 1 ";
}
  */

//     = reinterpret_cast< const Element<VR::type, VM::VM1>& > ( array );
// os.flush();
    // memcpy( (void*)(&e), array, e.GetLength() * sizeof( VRToType<VR::type>::Type) ); 
    // bswap<VRToType<VR::type>::Type>( (char*)(&e), array, e.GetLength() * sizeof( VRToType<VR::type>::Type) ); 
#define PrinterTemplateSubCase1n(type,rep) \
  case VM::rep: \
    {Element<VR::type, VM::rep> e; \
    /*assert( VM::rep == VM::VM1_n );*/ \
    e.SetArray( (VRToType<VR::type>::Type *)array, length, true ); \
    e.Print( os ); }\
    break;
#define PrinterTemplateSubCase(type,rep) \
  case VM::rep: \
    {Element<VR::type, VM::rep> e; \
    /*assert( bv.GetLength() == VMToLength<VM::rep>::Length * sizeof( VRToType<VR::type>::Type) ); */ \
    assert( bv.GetLength() == e.GetLength() * sizeof( VRToType<VR::type>::Type) ); \
    memcpy( (void*)(&e), array, e.GetLength() * sizeof( VRToType<VR::type>::Type) ); \
    e.Print( os ); }\
    break;
#define PrinterTemplateSub(type) \
switch(vm) { \
PrinterTemplateSubCase(type, VM1) \
PrinterTemplateSubCase(type, VM2) \
PrinterTemplateSubCase(type, VM3) \
PrinterTemplateSubCase(type, VM4) \
PrinterTemplateSubCase(type, VM5) \
PrinterTemplateSubCase(type, VM6) \
PrinterTemplateSubCase(type, VM24) \
PrinterTemplateSubCase1n(type, VM1_n) \
default: abort(); }

#define PrinterTemplateSub2(type) \
switch(vm) { \
	PrinterTemplateSubCase1n(type, VM1) \
default: abort(); }

#define PrinterTemplateCase(type) \
  case VR::type: \
    PrinterTemplateSub(type) \
    break;
#define PrinterTemplateCase2(type) \
  case VR::type: \
    PrinterTemplateSub2(type) \
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
PrinterTemplateCase2(OB) \
PrinterTemplateCase(OF) \
PrinterTemplateCase2(OW) \
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

void PrintValue(VR::VRType const &vr, VM const &vm, const Value &v)
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
	    // Indeed a SequenceOfFragments is not handle ...
	    std::cerr << "Problem in PrintValue" << std::endl;
    }
}

//-----------------------------------------------------------------------------
#if 0
void Printer::PrintDataSet(std::ostream& os, const DataSet<ImplicitDataElement> &ds)
{
  //ImplicitDataElement de;
  Printer::PrintStyles pstyle = is.GetPrintStyle();
  (void)pstyle;
  bool printVR = true; //is.GetPrintVR();

  std::ostream &_os = std::cout;
  //static const Dicts dicts;
  //const Dict &d = dicts.GetPublicDict();
  static const Dict d;
  static const GroupDict gd;
  try
    {
    //while( is.Read(de) )
    DataSet<ImplicitDataElement>::ConstIterator it = ds.Begin();
    for( ; it != ds.End(); ++it )
      {
      const ImplicitDataElement &de = *it;
      const Tag &t = de.GetTag();
      const DictEntry &entry = d.GetDictEntry(de.GetTag());
      // Use VR from dictionary
      VR::VRType vr = entry.GetVR();
      VM::VMType vm = entry.GetVM();
      if( /*de.GetTag().GetGroup()%2 &&*/ de.GetTag().GetElement() == 0 )
        {
        assert( vr == VR::INVALID || vr == VR::UL );
        assert( vm == VM::VM0 || vm == VM::VM1 );
        vr = VR::UL;
        vm = VM::VM1;
        }
      if( vr == VR::INVALID || VR::IsBinary(vr) || VR::IsASCII( vr ) )
        {
      // TODO: FIXME FIXME FIXME
      if ( de.GetTag().GetElement() == 0x0 )
        {
        if( vr == VR::INVALID ) // not found
          {
          vr = VR::UL;  // this is a group length (VR=UL,VM=1)
          }
        }
      if( vr == VR::INVALID && entry.GetVR() != VR::INVALID )
        {
        vr = entry.GetVR();
        }
  // TODO FIXME FIXME FIXME
  // Data Element (7FE0,0010) Pixel Data has the Value Representation 
  // OW and shall be encoded in Little Endian.
  //VM::VMType vm = VM::VM1;
  if( t == Tag(0x7fe0,0x0010) )
    {
    assert( vr == VR::OB_OW );
    vr = VR::OW;
    //vm = VM::VM1_n;
    }
  // RETIRED:
  // See PS 3.5 - 2004
  // Data Element (50xx,3000) Curve Data has the Value Representation OB 
  // with its component points (n-tuples) having the Value Representation
  // specified in Data Value Representation (50xx,0103). 
  // The component points shall be encoded in Little Endian.
  else if( t == Tag(0x5004,0x3000) ) // FIXME
    {
    assert( vr == VR::OB_OW );
    vr = VR::OB;
    }
  // Value of pixels not present in the native image added to an image 
  // to pad to rectangular format. See C.7.5.1.1.2 for further explanation. 
  // Note:     The Value Representation of this Attribute is determined 
  // by the value of Pixel Representation (0028,0103).
  if( vr == VR::US_SS )
    {
    if( t == Tag(0x0028,0x0120)  // Pixel Padding Value
      || t == Tag(0x0028,0x0106) // Smallest Image Pixel Value
      || t == Tag(0x0028,0x0107) // Largest Image Pixel Value
      || t == Tag(0x0028,0x0108) // Smallest Pixel Value in Series
      || t == Tag(0x0028,0x0109) // Largest Pixel Value in Series
      || t == Tag(0x0028,0x1101) // Red Palette Color Lookup Table Descriptor
      || t == Tag(0x0028,0x1102)  // Green Palette Color Lookup Table Descriptor
      || t == Tag(0x0028,0x1103) // Blue Palette Color Lookup Table Descriptor
    )
      {
      // TODO It would be nice to have a TagToVR<0x0028,0x0103>::VRType
      // and TagToVM<0x0028,0x0103>::VMType ...
      // to be able to have an independant Standard from implementation :)
      const ImplicitDataElement &pixel_rep = 
        ds.GetDataElement( Tag(0x0028, 0x0103) );
      const Value &value = pixel_rep.GetValue();
      const ByteValue &bv = static_cast<const ByteValue&>(value);
      // FIXME:
      unsigned short pixel_rep_value = *(unsigned short*)(bv.GetPointer());
      assert( pixel_rep_value == 0x0 || pixel_rep_value == 0x1 );
      vr = pixel_rep_value ? VR::SS : VR::US;
      }
    else
    {
	    abort();
    }
    }

        PrintImplicitDataElement(_os, de, printVR, vr /*entry.GetVR()*/, vm);
        }
      else
        {
        abort();
        const Value& val = de.GetValue();
        _os << de.GetTag();
        if ( printVR )
          {
          //_os << " ?VR=" << vr;
          _os << " " << vr;
          }
        //_os << "\tVL=" << std::dec << de.GetVL() << "\tValueField=[";
        _os << "\t" << std::dec << de.GetVL() << "\tValueField=[";

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
        _os << "\t\t" << gd.GetName(de.GetTag().GetGroup() )
          << " " << entry.GetName() << std::endl;
        }
      else
        {
//		_os.flush();
//        std::streampos pos = _os.tellp();
//        streambuf *s = _os.rdbuf();
        //int pos = _os.str().size();
        _os << " " << entry.GetName() << std::endl;
        }
      }
    }
  catch(std::exception &e)
    {
    std::cerr << "Exception:" << typeid(e).name() << std::endl;
    }
}
#endif

// TODO / FIXME
// SIEMENS_GBS_III-16-ACR_NEMA_1.acr is a tough kid: 0009,1131 is supposed to be VR::UL, but
// there are only two bytes...
#define StringFilterCase(type) \
  case VR::type: \
    { \
      Element<VR::type,VM::VM1_n> el; \
      if( !de.IsEmpty() ) { \
      el.Set( de.GetValue() ); \
      if( el.GetLength() ) { \
      os << "" << el.GetValue(); \
      for(unsigned long i = 1; i < el.GetLength(); ++i) os << "\\" << el.GetValue(i); \
      os << ""; } \
      else { if( de.IsEmpty() ) os << GDCM_TERMINAL_VT100_INVERSE << "(no value)" << GDCM_TERMINAL_VT100_NORMAL; \
                 else os << GDCM_TERMINAL_VT100_INVERSE << GDCM_TERMINAL_VT100_FOREGROUND_RED << "(VR=" << refvr << " is incompatible with length)" << GDCM_TERMINAL_VT100_NORMAL; } } \
      else { assert( de.IsEmpty()); os << GDCM_TERMINAL_VT100_INVERSE << "(no value)" << GDCM_TERMINAL_VT100_NORMAL; } \
    } break


VR Printer::PrintDataElement(std::ostringstream &os, const Dicts &dicts, const DataSet & ds, const DataElement &de, std::ostream &out, std::string const & indent )
{
    const ByteValue *bv = de.GetByteValue();
    const SequenceOfItems *sqi = de.GetSequenceOfItems();
    const SequenceOfFragments *sqf = de.GetSequenceOfFragments();

    std::string strowner;
    const char *owner = 0;
    const Tag& t = de.GetTag();
    if( t.IsPrivate() )
      { 
      strowner = ds.GetPrivateCreator(t);
      owner = strowner.c_str();
      }
    const DictEntry &entry = dicts.GetDictEntry(t,owner);
    const VR &vr = entry.GetVR();
    const VM &vm = entry.GetVM();
    const char *name = entry.GetName();
    bool retired = entry.GetRetired();
    //if( t.IsPrivate() ) assert( retired == false );

    const VR &vr_read = de.GetVR();
    const VL &vl_read = de.GetVL();
    os << indent; // first thing do the shift !
    os << t << " ";
    os << vr_read << " ";

    //VR refvr = GetRefVR(dicts, de);
    VR refvr;
    // always prefer the vr from the file:
    if( vr_read == VR::INVALID )
      {
      refvr = vr;
      }
    else if ( vr_read == VR::UN && vr != VR::INVALID ) // File is explicit, but still prefer vr from dict when UN
      {
      refvr = vr;
      }
    else // cool the file is Explicit !
      {
      refvr = vr_read;
      }
    // Special handling of US or SS vr:
    if( refvr == VR::US_SS )
      {
      // I believe all US_SS VR derived from the value from 0028,0103 ... except 0028,0071
      if( t != Tag(0x0028,0x0071) )
        {
        // In case of SAX parser, we would have had to process Pixel Representation already:
        Tag pixelrep(0x0028,0x0103);
        assert( pixelrep < t );
        const DataSet &rootds = F->GetDataSet();
        // FIXME
        // PhilipsWith15Overlays.dcm has a Private SQ with public elements such as
        // 0028,3002, so we cannot look up element in current dataset, but have to get the root dataset
        // to loop up...
        assert( rootds.FindDataElement( pixelrep ) );
        Attribute<0x0028,0x0103> at;
        at.SetFromDataElement( rootds.GetDataElement( pixelrep ) );
        assert( at.GetValue() == 0 || at.GetValue() == 1 );
        if( at.GetValue() )
          {
          refvr = VR::SS;
          }
        else
          {
          refvr = VR::US;
          }
        }
      }
    assert( refvr != VR::US_SS );
    // Special handling of OB or OW vr:
    if( refvr == VR::OB_OW )
      {
      /*
      For the Value Representations OB and OW, the encoding shall meet the following
      specification depending on the Data Element Tag:
      - Data Element (7FE0,0010) Pixel Data has the Value Representation OW and shall
      be encoded in Little Endian.
      - Data Element (60xx,3000) Overlay Data has the Value Representation OW and shall
      be encoded in Little Endian.

      See PS 3.5 - 2004
      - Data Element (50xx,3000) Curve Data has the Value Representation OB with its
      component points (n-tuples) having the Value Representation specified in Data
      Value Representation (50xx,0103). The component points shall be encoded in Little
      Endian.
      */
      Tag pixeldata(0x7fe0,0x0010);
      Tag overlaydata(0x6000,0x3000);
      Tag curvedata(0x5000,0x3000);
      Tag bitsallocated(0x0028,0x0100);
      assert( ds.FindDataElement( pixeldata ) );
      assert( ds.FindDataElement( bitsallocated ) );
      Attribute<0x0028,0x0100> at;
      at.SetFromDataElement( ds.GetDataElement( bitsallocated ) );
      
      if( pixeldata == t || t.IsGroupXX(overlaydata) )
        {
        refvr = VR::OW;
        }
      else if ( t.IsGroupXX(curvedata) )
        {
        refvr = VR::OB;
        }
      else
        {
        assert( 0 && "Should not happen" );
        }
      }
    assert( refvr != VR::OB_OW );

    if( !vr.Compatible( vr_read ) )
      {
      // FIXME : if terminal supports it: print in red/green !
      os << GDCM_TERMINAL_VT100_FOREGROUND_GREEN;
      if( vr == VR::US_SS || vr == VR::OB_OW )
        {
        os << "(" << vr << " => " << refvr << ") ";
        }
      else
        {
        os << "(" << vr << ") ";
        }
      os << GDCM_TERMINAL_VT100_NORMAL;
      }
    else if( de.GetSequenceOfItems() && refvr == VR::INVALID )
      {
      // when vr == VR::INVALID and vr_read is also VR::INVALID, we have a seldom case where we can guess
      // the vr
      // eg. CD1/647662/647663/6471066 has a SQ at (2001,9000)
      os << GDCM_TERMINAL_VT100_FOREGROUND_GREEN;
      os << "(SQ) ";
      os << GDCM_TERMINAL_VT100_NORMAL;
      assert( refvr == VR::INVALID );
      refvr = VR::SQ;
      }
    // Print Value now:
    if( refvr & VR::VRASCII )
      {
      if( bv )
        {
        VL l = std::min( bv->GetLength(), MaxPrintLength );
        os << "[";
        if( bv->IsPrintable(l) )
          {
          bv->PrintASCII(os,l);
          }
        else
          {
          os << GDCM_TERMINAL_VT100_INVERSE;
          os << GDCM_TERMINAL_VT100_FOREGROUND_RED;
          bv->PrintASCII(os,l);
          os << GDCM_TERMINAL_VT100_NORMAL;
          }
        os << "]";
        }
      else
        {
        assert( de.IsEmpty() );
        os << GDCM_TERMINAL_VT100_INVERSE;
        os << "(no value)";
        os << GDCM_TERMINAL_VT100_NORMAL;
        }
      }
    else
      {
      assert( refvr & VR::VRBINARY || (vr == VR::INVALID && refvr == VR::INVALID) );
      //std::ostringstream os;
      std::string s;
      switch(refvr)
        {
        StringFilterCase(AT);
        StringFilterCase(FL);
        StringFilterCase(FD);
        //StringFilterCase(OB);
        StringFilterCase(OF);
        //StringFilterCase(OW);
        StringFilterCase(SL);
        //StringFilterCase(SQ);
        StringFilterCase(SS);
        StringFilterCase(UL);
        //StringFilterCase(UN);
        StringFilterCase(US);
        //StringFilterCase(UT);
      case VR::OB:
      case VR::OW:
      case VR::OB_OW:
          {
          if ( bv )
            {
            //VL l = std::min( bv->GetLength(), MaxPrintLength );
            //VL l = std::min( (int)bv->GetLength(), 0xF );
            //int width = (vr == VR::OW ? 4 : 2);
            //os << std::hex << std::setw( width ) << std::setfill('0');
            bv->PrintHex(os, MaxPrintLength / 4);
            //os << std::dec;
            }
          else if ( sqf )
            {
            assert( t == Tag(0x7fe0,0x0010) );
            //os << *sqf;
            }
          else
            {
            assert( !sqi && !sqf );
            assert( de.IsEmpty() );
            os << GDCM_TERMINAL_VT100_INVERSE << "(no value)" << GDCM_TERMINAL_VT100_NORMAL;
            }
          }
        break;
      case VR::UN:
      case VR::US_SS:
      case VR::US_SS_OW:
        os << "TODO";
        break;
      case VR::SQ:
        if( vl_read.IsUndefined() )
          {
          os << "(Sequence with undefined length)";
          }
        else
          {
          os << "(Sequence with defined length)";
          }
        break;
      // Let's be a little more helpful and try to print anyway when possible:
      case VR::INVALID:
          {
          if( bv )
            {
            VL l = std::min( bv->GetLength(), MaxPrintLength );
            if( bv->IsPrintable(l) ) 
              {
              os << "[";
              bv->PrintASCII(os,l);
              os << "]";
              }
            else if( t == Tag(0xfffe,0xe000) ) bv->PrintHex(os, MaxPrintLength / 8);
            else 
              {
              os << GDCM_TERMINAL_VT100_INVERSE;
              // << "(non-printable character found)"
              bv->PrintHex(os, MaxPrintLength / 8);
              os << GDCM_TERMINAL_VT100_NORMAL;
              }
            }
          else
            {
            assert( !sqi && !sqf );
            assert( de.IsEmpty() );
            os << GDCM_TERMINAL_VT100_INVERSE << "(no value)" << GDCM_TERMINAL_VT100_NORMAL;
            }
          }
        break;
      default:
        abort();
        break;
        }
      os << s;
      }
    out.width(57);
    out << std::left << os.str();
    // There is something wrong going on when doing terminal color stuff
    // Let's add a couple of space to be nicer...
    if( os.str().find( GDCM_TERMINAL_VT100_NORMAL ) != std::string::npos )
      {
      out << "        ";
      }
    os.str( "" );
    // Extra info (not in the file)
    os << " # ";
    // Append the VL
    if( vl_read.IsUndefined() )
      {
      os << "u/l";
      }
    else
      {
      os << std::dec << vl_read;
      }
    if( vl_read.IsOdd() )
      {
      os << GDCM_TERMINAL_VT100_FOREGROUND_GREEN;
      os << " (" << (vl_read + 1) << ")";
      os << GDCM_TERMINAL_VT100_NORMAL;
      }
    os << ",";
    // Append the VM
    if( vm != VM::VM0 )
      {
      os << vm;
      }
    else
      {
      os << GDCM_TERMINAL_VT100_FOREGROUND_RED;
      os << "?";
      os << GDCM_TERMINAL_VT100_NORMAL;
      }
    VM guessvm = VM::VM0;
    if( refvr & VR::VRASCII )
      {
      assert( refvr != VR::INVALID );
      assert( refvr & VR::VRASCII );
      if( bv )
        {
        unsigned int count = VM::GetNumberOfElementsFromArray(bv->GetPointer(), bv->GetLength());
        guessvm = VM::GetVMTypeFromLength(count, 1); // hackish...
        }
      }
    else if( refvr & VR::VRBINARY )
      {
      assert( refvr != VR::INVALID );
      assert( refvr & VR::VRBINARY );
      if( refvr & VR::OB_OW || refvr == VR::SQ )
        {
        guessvm = VM::VM1;
        }
      else if ( refvr == VR::UN && sqi )
        {
        // This is a SQ / UN
        guessvm = VM::VM1;
        }
      else if( bv )
        {
        guessvm = VM::GetVMTypeFromLength(bv->GetLength(), refvr.GetSize() );
        }
      else
        {
        if( de.IsEmpty() ) guessvm = VM::VM0;
        else assert( 0 && "Impossible" );
        }
      }
    else if( refvr == VR::INVALID )
      {
      refvr = VR::UN;
      guessvm = VM::VM1;
      }
    else
      {
      // Burst into flames !
      assert( 0 && "Impossible happen" );
      }
    if( !vm.Compatible( guessvm ) )
      {
      os << GDCM_TERMINAL_VT100_FOREGROUND_GREEN;
      os << " (" << guessvm << ") ";
      os << GDCM_TERMINAL_VT100_NORMAL;
      }
    // Append the name now:
    if( name && *name )
      {
      // No owner case !
      if( t.IsPrivate() && (owner == 0 || *owner == 0 ) && t.IsPrivateCreator() )
        {
        os << GDCM_TERMINAL_VT100_FOREGROUND_RED;
        os << " " << name;
        os << GDCM_TERMINAL_VT100_NORMAL;
        }
      // retired element
      else if( retired )
        {
        assert( t.IsPublic() || t.GetElement() == 0x0 ); // Is there such thing as private and retired element ?
        os << " " << GDCM_TERMINAL_VT100_FOREGROUND_RED << GDCM_TERMINAL_VT100_UNDERLINE;
        os << name;
        os << GDCM_TERMINAL_VT100_NORMAL;
        os << GDCM_TERMINAL_VT100_NORMAL;
        }
      else
        {
        os << GDCM_TERMINAL_VT100_BOLD;
        os << " " << name;
        os << GDCM_TERMINAL_VT100_NORMAL;
        }
      }
    else
      {
      os << GDCM_TERMINAL_VT100_FOREGROUND_RED;
      if( t.IsPublic() )
        {
        // What ? A public element that we do not know about !!!
        os << GDCM_TERMINAL_VT100_BLINK;
        }
      os << " UNKNOWN";
      os << GDCM_TERMINAL_VT100_NORMAL;
      }
    os << "\n";
return refvr;
}

void Printer::PrintDataSet(const DataSet &ds, std::ostream &out, std::string const & indent )
{
  const Global& g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  const Dict &d = dicts.GetPublicDict(); (void)d;
 
  DataSet::ConstIterator it = ds.Begin();
  for( ; it != ds.End(); ++it )
    {
    const DataElement &de = *it;

    //const ByteValue *bv = de.GetByteValue();
    const SequenceOfItems *sqi = de.GetSequenceOfItems();
    const SequenceOfFragments *sqf = de.GetSequenceOfFragments();

    std::ostringstream os;

    VR refvr = PrintDataElement(os, dicts, ds, de, out, indent);

    if( refvr == VR::SQ || sqi )
      {
      if( sqi ) // empty SQ ?
        {
        assert( sqi );
        SequenceOfItems::ItemVector::const_iterator it = sqi->Items.begin();
        for(; it != sqi->Items.end(); ++it)
          {
          const Item &item = *it;
          const DataSet &ds = item.GetNestedDataSet();
          const DataElement &deitem = item;
          std::string nextindent = indent + "  ";
          os << nextindent << deitem.GetTag();
          os << " ";
          os << deitem.GetVR();
          os << " ";
          if( deitem.GetVL().IsUndefined() )
            {
            os << "(Item with undefined length)";
            }
          else
            {
            os << "(Item with defined length)";
            }
          os << "\n";
          PrintDataSet(ds, os, nextindent + "  ");
          if( deitem.GetVL().IsUndefined() )
            {
            const Tag itemDelItem(0xfffe,0xe00d);
            os << nextindent << itemDelItem << "\n";
            }
          }
        if( sqi->GetLength().IsUndefined() )
          {
          const Tag seqDelItem(0xfffe,0xe0dd);
          os << indent << seqDelItem << "\n";
          }
        }
      }
    else if ( sqf )
      {
      std::string nextindent = indent + "  ";
      const BasicOffsetTable & table = sqf->GetTable();
      //os << nextindent  << table.GetTag() << "\n";
      PrintDataElement(os,dicts,ds,table,out,nextindent);
      unsigned int numfrag = sqf->GetNumberOfFragments();
      for(unsigned int i = 0; i < numfrag; ++i)
        {
        const Fragment& frag = sqf->GetFragment(i);
        //os << nextindent<< frag << "\n";
        PrintDataElement(os,dicts,ds,frag,out,nextindent);
        }
      const Tag seqDelItem(0xfffe,0xe0dd);
      VL zero = 0;
      os << /*nextindent <<*/ seqDelItem;
      os << " " << zero << "\n";
      }
    else
      {
      // This is a byte value, so it should have been already treated 
      }
    out << os.str();
    }
}

//-----------------------------------------------------------------------------
void Printer::PrintDataSetOld(std::ostream &os, const DataSet &ds)
{
  const Global& g = GlobalInstance;
  const Dicts &dicts = g.GetDicts();
  const Dict &d = dicts.GetPublicDict(); (void)d;
 
  static const GroupDict gd; // FIXME
//  try
    {
    DataSet::ConstIterator it = ds.Begin();
    for( ; it != ds.End(); ++it )
      {
      const DataElement &de = *it;
      //const DictEntry &entry = d.GetDictEntry(de.GetTag());
      std::string owner;
      const char *strowner = 0;
      if( de.GetTag().IsPrivate() /*&& de.GetTag().GetElement()*/ )
        {
        Tag t = de.GetTag().GetPrivateCreator();
        const ByteValue * bv = de.GetByteValue();
        if( t.GetElement() )
          {
          const DataElement & de = ds.GetDataElement( t );
          bv = de.GetByteValue();
          }
        else
          {
          //assert( vr == VR::LO );
          //assert( vm == VM::VM1 );
          }
        assert( bv );
        owner = std::string(bv->GetPointer(),bv->GetLength());
        assert(  owner.size() );
        if( owner[owner.size()-1] == ' ' )
          {
          owner.erase(owner.size()-1,1);
          }
        assert( owner[owner.size()-1] != ' ' );
        strowner = owner.c_str();
        }
      const DictEntry &entry = dicts.GetDictEntry(de.GetTag(),strowner);
      // Use VR from dictionary
      VR vr = entry.GetVR();
      VM vm = entry.GetVM();
      // TODO: FIXME FIXME FIXME
      const Tag& t = de.GetTag();
      //std::cerr << t << std::endl;
      const VR::VRType vr_read = de.GetVR();
      if( t == Tag(0x7fe0,0x0010) )
        {
        assert( vr & VR::OB_OW );
        //vr = VR::OW;
        //vm = VM::VM1_n;
        }
      if ( de.GetTag().GetElement() == 0x0 )
        {
        assert( vm == VM::VM0 || vm == VM::VM1 ); // not found
        vm = VM::VM1; // this is a group length (VR=UL,VM=1)
        assert( vr == VR::INVALID || vr == VR::UL ); // not found
        vr = VR::UL;  // this is a group length (VR=UL,VM=1)
        }
      else if( de.GetTag().IsPrivate() )
        {
        //assert( !de.GetTag().GetElement() || vr == VR::INVALID );
        //assert( !de.GetTag().GetElement() || vm == VM::VM0 );
        if ( vr == VR::INVALID )
          {
          vr = vr_read; // we have no choice for now but trust it
          assert( vm == VM::VM0 );
          if( vr & VR::OB_OW )
            {
            vm = VM::VM1;
            }
          else
            {
            vm = VM::VM1_n; // FIXME: Is this always correct ?
            }
          }
        }
      assert( vm != VM::VM0 );
      //assert( vr != VR::INVALID );
      /*if( vr == VR::INVALID )
        {
        const VM vm = entry.GetVM();
        const Value& val = de.GetValue();
        os << de.GetTag();
        }
      else */
      if( VR::IsASCII(vr_read) || VR::IsBinary(vr_read) )
        {
	//	_os << de << std::endl;
        PrintElement(os, de, entry);
        }
      else // INVALID case
        {
        const VM& vm = entry.GetVM(); (void)vm;
        const Value& val = de.GetValue(); (void)val;
        os << de.GetTag();
        //if( pstyle == Printer::CONDENSED_STYLE )
        //  {
        //  os << " " << vr_read;
        //  }
          {
          //os << " VR=" << VR::GetVRString(vr_read);
          os << " " << VR::GetVRString(vr_read);
          os << "(" << vr << ")";
          }
        if( !vr.Compatible( vr_read ) )
          {
          gdcmErrorMacro( "Wrong VR should be " << vr );
          // PHILIPS_Gyroscan-12-Jpeg_Extended_Process_2_4.dcm
          // 0008,0040 VR=SS VR(?)=US
          // After posting to dicom newsgroup there were reasons for doing SS
          // but in this case user should really do US...
          }
        //if( pstyle == Printer::CONDENSED_STYLE )
        //  {
        //  os << /*"\t " << std::dec << de.GetVL() << */
        //    " ";
        //  }
          {
          //_os << "\tVL=" << std::dec << de.GetVL() << "\tValueField=[";
          os << " " << std::dec << de.GetVL() << " ";
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
        //if( pstyle == Printer::CONDENSED_STYLE )
        //  {
        //  os << "]";
        //  }
        }
      if( de.GetTag().GetElement() == 0x0 )
        {
        os << " (" << gd.GetName(de.GetTag().GetGroup() )
          << ") " << entry.GetName() << std::endl;
        }
      else
        {
        const char *name = entry.GetName();
        if( name && *name )
          {
          os << " " << name << std::endl;
          }
        else
          {
          //assert( strowner );
          os << " FIXME: " << owner << std::endl;
          }
        }
      }
    }
  //catch(std::exception &e)
  //  {
  //  std::cerr << "Exception:" << typeid(e).name() << std::endl;
  //  }
}

//-----------------------------------------------------------------------------
void DumpDataSet(const DataSet &ds, std::ostream &os )
{
  DataSet::ConstIterator it = ds.Begin();
  for( ; it != ds.End(); ++it )
    {
    const DataElement &de = *it;
    const Tag& t = de.GetTag(); (void)t;
    const VR& vr = de.GetVR(); (void)vr;
    os << de << std::endl;
    //if( VR::IsASCII( vr ) )
    //  {
    //  }
    }
}

//-----------------------------------------------------------------------------
void Printer::Print(std::ostream& os)
{
  os << "# Dicom-File-Format\n";
  os << "\n";
  os << "# Dicom-Meta-Information-Header\n";
  os << "# Used TransferSyntax: \n";

  const FileMetaInformation &meta = F->GetHeader();
  if( PrintStyle == VERBOSE_STYLE )
    PrintDataSet(meta, os);
  else if (PrintStyle == CONDENSED_STYLE )
    DumpDataSet(meta, os);

  os << "\n# Dicom-Data-Set\n";
  os << "# Used TransferSyntax: ";
  const TransferSyntax &metats = meta.GetDataSetTransferSyntax();
  os << metats;
  os << std::endl;
  const DataSet &ds = F->GetDataSet();
  if( PrintStyle == VERBOSE_STYLE )
    PrintDataSet(ds, os);
  else if (PrintStyle == CONDENSED_STYLE )
    DumpDataSet(ds, os);
}

}

