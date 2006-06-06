#include "gdcmPrinter.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
//#include "gdcmDict.h"
//#include "gdcmDicts.h"
//#include "gdcmGroupDict.h"
//#include "gdcmAttribute.h"
#include "gdcmVR.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
Printer::Printer():PrintStyle(PrintStyles::VERBOSE_STYLE)
{
}
//-----------------------------------------------------------------------------
Printer::~Printer()
{
}

//-----------------------------------------------------------------------------
//std::ostream& Printer::PrintTag(std::ostream &_os, const Tag &_val)
//{
//  if (PrintStyle == DCMTK_STYLE )
//    {
//    _os.setf( std::ios::right);
//    _os << "(" << std::hex << std::setw( 4 ) << std::setfill( '0' )
//      << _val[0] << ',' << std::setw( 4 ) 
//      << std::setfill( '0' )
//      << _val[1] << std::setfill( ' ' ) << ")" << std::dec;
//    }
//  else
//    {
//    _os.setf( std::ios::right);
//    _os << std::hex << std::setw( 4 ) << std::setfill( '0' )
//      << _val[0] << ',' << std::setw( 4 ) << std::setfill( '0' )
//      << _val[1] << std::setfill( ' ' ) << std::dec;
//    }
//  return _os;
//}

//-----------------------------------------------------------------------------
void PrintExplicitDataElement(std::ostream& _os, const ExplicitDataElement &_val, bool printVR, VR::VRType dictVR, Printer::PrintStyles pstyle)
{
  const Tag &t = _val.GetTag();
  const VR::VRType vr = _val.GetVR();
  const uint32_t vl = _val.GetValueLength();
  const Value& value = _val.GetValue();
  (void)printVR;
  if( pstyle == Printer::DCMTK_STYLE )
    {
  _os << t << " " << vr;
    }
  else
    {
  _os << t << " VR=" << vr;
    }
  if( dictVR != VR::INVALID && !(vr & dictVR) ) //printVR )
    {
    gdcmErrorMacro( "Wrong VR should be " << dictVR );
    // LEADTOOLS_FLOWERS-8-PAL-RLE.dcm has (0040,0253) : CS instead of SH
    //abort();
    }
  if( pstyle == Printer::DCMTK_STYLE )
    {
  (void)vl;
  _os /*<< "\t " << std::dec << vl  */
      << " [" << value << "]";
    }
  else
    {
  _os << "\tVL=" << std::dec << vl <<
      "\t ValueField=[" << value << "]";
    }
}
//-----------------------------------------------------------------------------
void PrintImplicitDataElement(std::ostream& _os, const ImplicitDataElement &_val, bool printVR, VR::VRType dictVR)
{
  const Tag &t = _val.GetTag();
  const uint32_t vl = _val.GetValueLength();
  const Value& value = _val.GetValue();
  _os << t;
  if ( printVR )
    {
    _os << " ?VR=" << dictVR;
    }
  _os << "\tVL=" << std::dec << vl
    << "\tValueField=[" << value << "]";
}

//-----------------------------------------------------------------------------
void PrintImplicitDataElements(Printer &is)
{
  ImplicitDataElement de;
  Printer::PrintStyles pstyle = is.GetPrintStyle();
  (void)pstyle;
  bool printVR = is.GetPrintVR();

  std::ostream &_os = std::cout;
  //static const Dicts dicts;
  //const Dict &d = dicts.GetPublicDict();
  static const Dict d;
  static const GroupDict gd;
  try
    {
    while( is.Read(de) )
      {
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
      if( VR::IsString( vr ) || VR::IsBinary(vr) || vr == VR::INVALID )
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
        _os << "\tVL=" << std::dec << de.GetValueLength() << "\tValueField=[";

        // Use super class of the template stuff
        Attribute af;
        // Last minute check, is it a Group Length:
        af.SetVR(vr);
        af.SetVM(vm);
        af.SetLength( val.GetLength() );
        std::istringstream iss;
        iss.str( std::string( val.GetPointer(), val.GetLength() ) );
        af.Read( iss );
        af.Print( _os );
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
void PrintExplicitDataElements(Printer &is)
{
  ExplicitDataElement de;

  std::ostream &_os = std::cout;
  static const Dict d;
  static const GroupDict gd;
  Printer::PrintStyles pstyle = is.GetPrintStyle();
  bool printVR = is.GetPrintVR();
  try
    {
    while( !is.eof() && is.Read(de) )
      {
      is.Read(de);
      const DictEntry &entry = d.GetDictEntry(de.GetTag());
      // Use VR from dictionary
      const VR::VRType vr = entry.GetVR();
      const VR::VRType vr_read = de.GetVR();
      if( VR::IsString(vr_read) || VR::IsBinary(vr_read) )
        {
        PrintExplicitDataElement(_os, de, printVR, vr, pstyle);
        }
      else
        {
        const VM::VMType vm = entry.GetVM();
        const Value& val = de.GetValue();
        _os << de.GetTag();
        if( pstyle == Printer::DCMTK_STYLE )
          {
          _os << " " << vr_read;
          }
        else
          {
          _os << " VR=" << vr_read;
          }
        if( vr != VR::INVALID && !(vr_read & vr) )
          {
          gdcmErrorMacro( "Wrong VR should be " << vr );
          // PHILIPS_Gyroscan-12-Jpeg_Extended_Process_2_4.dcm
          // 0008,0040 VR=SS VR(?)=US
          // After posting to dicom newsgroup there were reasons for doing SS
          // but in this case user should really do US...
          }
        if( pstyle == Printer::DCMTK_STYLE )
          {
        _os << /*"\t " << std::dec << de.GetValueLength() << */
          " ";
        }
        else
          {
        _os << "\tVL=" << std::dec << de.GetValueLength() 
          << "\tValueField=[";
          }

        // Use super class of the template stuff
        Attribute af;
        af.SetVR(vr_read);
        af.SetVM(vm);
        af.SetLength( val.GetLength() );
        std::istringstream iss;
        iss.str( std::string( val.GetPointer(), val.GetLength() ) );
        af.Read( iss );
        af.Print( _os );
        if( pstyle == Printer::DCMTK_STYLE )
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


//-----------------------------------------------------------------------------
void Printer::Initialize()
{
  DICOMIStream::Initialize();

  if ( PrintStyle == DCMTK_STYLE )
    {
    std::cout << "# Dicom-File-Format" << std::endl;
    std::cout << std::endl;
    std::cout << "# Dicom-Meta-Information-Header" << std::endl;
    // TODO Not always Little
    std::cout << "# Used TransferSyntax: LittleEndian" <<
      (NegociatedTS == Explicit ? "Explicit" : "Implicit") << std::endl;

    std::cout << "# Dicom-Data-Set" << std::endl;
    std::cout << "# Used TransferSyntax: " <<
      TS::GetTSString(GetUsedTS()) << std::endl;
    }
  else
    {
    std::cout << "Meta Header: " << std::endl;
    std::cout << "Negociated Transfer Syntax: " << 
      (NegociatedTS == Explicit ? "Explicit" : "Implicit") << std::endl;
    }

  // Skip one line:
  std::cout << std::endl;
  if( NegociatedTS == Explicit )
    {
    PrintExplicitDataElements(*this);
    }
  else
    {
    PrintImplicitDataElements(*this);
    }
  // FIXME a file that reach eof is not valid...
  Close();
  Open();
}

}
