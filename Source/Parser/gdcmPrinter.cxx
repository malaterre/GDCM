#include "gdcmPrinter.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmDict.h"
#include "gdcmGroupDict.h"
#include "gdcmAttribute.h"

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
void PrintImplicitDataElements(gdcm::DICOMIStream &is, bool printVR)
{
  gdcm::ImplicitDataElement de;
  gdcm::DataElement &de_tag = de;

  std::ostream &_os = std::cout;
  static const gdcm::Dict d;
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
        _os << de;
        }
      else
        {
        const Value& val = de.GetValue();
        _os << de.GetTag();
        if ( printVR )
          {
          _os << " D_VR=" << vr;
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
        _os << de;
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
