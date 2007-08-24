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
#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmDict.h"
#include "gdcmDicts.h"
#include "gdcmGroupDict.h"
#include "gdcmVR.h"
#include "gdcmVM.h"

#include "gdcmStructuredSet.h"

#include <typeinfo> // for typeid

namespace gdcm
{
//-----------------------------------------------------------------------------
Printer::Printer():/*PrintStyle(Printer::VERBOSE_STYLE),*/F(0)
{
}
//-----------------------------------------------------------------------------
Printer::~Printer()
{
}

void PrintValue(VR::VRType const &vr, VM::VMType const &vm, const Value &v);

//-----------------------------------------------------------------------------
void Printer::PrintElement(std::ostream& os, const ExplicitDataElement &xde, const DictEntry& entry) 
{
  const Tag &t = xde.GetTag();
  const VR &vr = xde.GetVR();
  const VL &vl = xde.GetVL();
  const Value& value = xde.GetValue();
  VR lvr = vr;

  // first of' do the VR:
  if( lvr == VR::UN )
  {
	  if( t.GetElement() == 0x0 )
	  {
		  lvr = VR::UL;
	  }
	  else
	  {
    lvr = entry.GetVR();
	  }
  // Data Element (7FE0,0010) Pixel Data has the Value Representation 
  // OW and shall be encoded in Little Endian.
  if( t == Tag(0x7fe0,0x0010) )
    {
    assert( lvr == VR::OB_OW );
    lvr = VR::OW;
    }
   }

  /*const*/ VM::VMType vm = entry.GetVM();
  if( vm == VM::VM0 )
  {
    assert( lvr != VR::UN );
    assert( t.IsPrivate() || t.GetElement() == 0x0 );
    if ( lvr & (VR::OB | VR::OW))
    {
      vm = VM::VM1;
    }
    else
    {
      vm = VM::GetVMTypeFromLength( value.GetLength(), lvr.GetSize() );
      //gdcmWarningMacro( "VM for " << vm );
      if( t.GetElement() == 0x0 )
      {
        //gdcmErrorMacro( "Le= " << value.GetLength() << " size= " << vr.GetSize() );
        assert( vm == VM::VM1 && lvr == VR::UL );
      }
    }
  }
  // Print Tag and VR:
  os << t << " " << VR::GetVRString(lvr);
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

    if( VR::IsASCII(lvr)  )
      {
      os << " [" << value << "] ";
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
      const StructuredSet<ExplicitDataElement> &exds = ds.GetInternal();
      PrintDataSet(os << "  ", exds);
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
      const Value &val = frag.GetValue();
      //PrintValue(lvr, vm, val );
      os << "  " << frag << std::endl;
      }
    }
  }

template <typename T>
inline char *bswap(char *out, const char *in, size_t length)
{
  assert( !(length % sizeof(T)) );
  for(size_t i = 0; i < length; i+=2)
  {
    //const char copy = in[i];
    out[i] = in[i+1];
    out[i+1] = in[i];
  }
}

//-----------------------------------------------------------------------------
void Printer::PrintElement(std::ostream& os, const ImplicitDataElement &ide, DictEntry const &entry)
{
	/*
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
  */
}

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
	    // Indeed a SequenceOfFragments is not handle ...
	    std::cerr << "Problem in PrintValue" << std::endl;
    }
}

//-----------------------------------------------------------------------------
void Printer::PrintDataSet(std::ostream& os, const StructuredSet<ImplicitDataElement> &ds)
{
#if 0
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
    StructuredSet<ImplicitDataElement>::ConstIterator it = ds.Begin();
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
#endif
}

//-----------------------------------------------------------------------------
void Printer::PrintDataSet(std::ostream &os, const StructuredSet<ExplicitDataElement> &ds)
{
  static const Dict d;
  static const GroupDict gd;
  try
    {
    StructuredSet<ExplicitDataElement>::ConstIterator it = ds.Begin();
    for( ; it != ds.End(); ++it )
      {
      const ExplicitDataElement &de = *it;
      const DictEntry &entry = d.GetDictEntry(de.GetTag());
      // Use VR from dictionary
      VR::VRType vr = entry.GetVR();
      VM::VMType vm = entry.GetVM();
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
        assert( !de.GetTag().GetElement() || vr == VR::INVALID );
        assert( !de.GetTag().GetElement() || vm == VM::VM0 );
        vr = vr_read; // we have no choice for now but trust it
        /*if( vr & VR::OB_OW 
         || vr & VR::FL )
          {
          //vm = VM::VM1_n;
          }
        else
          {
          vm = VM::VM1;
          }*/
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
      assert( vm != VM::VM0 );
      assert( vr != VR::INVALID );
      if( VR::IsASCII(vr_read) || VR::IsBinary(vr_read) )
        {
	//	_os << de << std::endl;
        PrintElement(os, de, entry);
        }
      else
        {
        abort();
        const VM::VMType vm = entry.GetVM();
        const Value& val = de.GetValue();
        os << de.GetTag();
        //if( pstyle == Printer::CONDENSED_STYLE )
        //  {
        //  os << " " << vr_read;
        //  }
          {
          //os << " VR=" << VR::GetVRString(vr_read);
          os << " " << VR::GetVRString(vr_read);
          }
        if( vr != VR::INVALID && !(vr_read & vr) )
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
        os << " " << entry.GetName() << std::endl;
        }
      }
    }
  catch(std::exception &e)
    {
    std::cerr << "Exception:" << typeid(e).name() << std::endl;
    }
}

//-----------------------------------------------------------------------------
void Printer::Print(std::ostream& os)
{
  std::cout << "# Dicom-File-Format\n";
  std::cout << "\n";
  std::cout << "# Dicom-Meta-Information-Header\n";
  std::cout << "# Used TransferSyntax: \n";

  const FileMetaInformation &meta = F->GetHeader();
  PrintDataSet(os, meta);

  std::cout << "\n# Dicom-Data-Set\n";
  std::cout << "# Used TransferSyntax: \n";
  const DataSet &ds = F->GetDataSet();
  const StructuredSet<ExplicitDataElement> &exds = ds.GetInternal();
  PrintDataSet(os, exds);
}

}

