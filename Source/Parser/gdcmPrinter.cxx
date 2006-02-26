#include "gdcmPrinter.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmDict.h"
#include "gdcmDicts.h"
#include "gdcmGroupDict.h"
#include "gdcmAttribute.h"
#include "gdcmVR.h"

namespace gdcm
{
//-----------------------------------------------------------------------------
Printer::Printer()
{
  PrintVR = true;
}
//-----------------------------------------------------------------------------
Printer::~Printer()
{
}
//-----------------------------------------------------------------------------
void PrintExplicitDataElement(std::ostream& _os, const ExplicitDataElement &_val, bool printVR, VR::VRType dictVR)
{
  const Tag &t = _val.GetTag();
  const VR::VRType vr = _val.GetVR();
  const uint32_t vl = _val.GetValueLength();
  const Value& value = _val.GetValue();
  _os << t << " VR=" << vr;
  if ( printVR )
    {
    _os << " ?VR=" << dictVR;
    }
  _os << "\tVL=" << std::dec << vl  
      << "\tValueField=[" << value << "]";
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
void PrintImplicitDataElements(gdcm::DICOMIStream &is, bool printVR)
{
  gdcm::ImplicitDataElement de;
  gdcm::DataElement &de_tag = de;

  std::ostream &_os = std::cout;
  static const gdcm::Dicts dicts;
  const gdcm::Dict &d = dicts.GetPublicDict();
  static const gdcm::GroupDict gd;
  try
    {
    while( !is.eof() && is.Read(de_tag) )
      {
      is.Read(de);
      const gdcm::DictEntry &entry = d.GetDictEntry(de.GetTag());
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
        gdcm::Attribute af;
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
void PrintExplicitDataElements(gdcm::DICOMIStream &is, bool printVR)
{
  gdcm::ExplicitDataElement de;
  gdcm::DataElement &de_tag = de;

  std::ostream &_os = std::cout;
  static const gdcm::Dict d;
  static const gdcm::GroupDict gd;
  (void)printVR;
  try
    {
    while( !is.eof() && is.Read(de_tag) )
      {
      is.Read(de);
      const gdcm::DictEntry &entry = d.GetDictEntry(de.GetTag());
      // Use VR from dictionary
      const VR::VRType vr = entry.GetVR();
      const VR::VRType vr_read = de.GetVR();
      if( VR::IsString(vr_read) || VR::IsBinary(vr_read) )
        {
        PrintExplicitDataElement(_os, de, printVR, vr);
        }
      else
        {
        const VM::VMType vm = entry.GetVM();
        const Value& val = de.GetValue();
        _os << de.GetTag();
        _os << " VR=" << vr_read;
        if( vr != VR::INVALID && !(vr_read & vr) ) //printVR )
          {
          gdcmWarningMacro( "Wrong VR" );
          _os << " VR(?)=" << vr;
          abort();
          }
        _os << "\tVL=" << std::dec << de.GetValueLength() << "\tValueField=[";

        // Use super class of the template stuff
        gdcm::Attribute af;
        af.SetVR(vr_read);
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
        }      }
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

  std::cout << "Meta Header: " << std::endl;
  std::cout << "Negociated Transfer Syntax: " << 
    (NegociatedTS == Explicit ? "Explicit" : "Implicit") << std::endl;
  // Skip one line:
  std::cout << std::endl;
  if( NegociatedTS == Explicit )
    {
    PrintExplicitDataElements(*this, PrintVR);
    }
  else
    {
    PrintImplicitDataElements(*this, PrintVR);
    }
  // FIXME a file that reach eof is not valid...
  Close();
  Open();
}

}
