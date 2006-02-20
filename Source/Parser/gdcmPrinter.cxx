#include "gdcmPrinter.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmDict.h"
#include "gdcmGroupDict.h"
#include "gdcmAttribute.h"

namespace gdcm
{
Printer::Printer()
{
  PrintVR = false;
}
Printer::~Printer()
{
  PrintVR = false;
}

void PrintImplicitDataElements(gdcm::DICOMIStream &is)
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
//      if( de.GetTag().GetElement() == 0x0 )
//        {
//        std::cout << de << "\t # (" << gd.GetName(de.GetTag().GetGroup() )
//          << ") " << entry.GetName() << std::endl;
//        }
//      else
        {
        // Use VR from dictionary
        const VR::VRType vr = entry.GetVR();
        if( VR::IsString( vr ) || VR::IsBinary(vr) )
          {
        std::cout << de << "\t # (" << gd.GetName(de.GetTag().GetGroup() )
          << ") " << entry.GetName() << std::endl;
          }
          else
          {
        const VM::VMType vm = entry.GetVM();
        const Value& val = de.GetValue();
        //std::cout << de << "\t # " << entry.GetName() << std::endl;
        _os << de.GetTag();
        if ( false ) // PrintVR
          {
          _os << " VR(?)=" << vr;
          }
        _os << ",VL=" << std::dec << de.GetValueLength()
          << " ValueField=[";

        // Use super class of the template stuff
        gdcm::Attribute af;
        af.SetVR(vr);
        af.SetVM(vm);
        af.SetLength( val.GetLength() );
        std::istringstream is;
        is.str( std::string( val.GetPointer(), val.GetLength() ) );
        af.Read( is );
        af.Print( _os );
        _os << "]\n";
          }
        }
      }
    }
  catch(std::exception &e)
    {
    std::cerr << "Exception:" << typeid(e).name() << std::endl;
    }
}

void PrintExplicitDataElements(gdcm::DICOMIStream &is)
{
  gdcm::ExplicitDataElement de;
  gdcm::DataElement &de_tag = de;

  static const gdcm::Dict d;
  static const gdcm::GroupDict gd;
  try
    {
    while( !is.eof() && is.Read(de_tag) )
      {
      is.Read(de);
      const gdcm::DictEntry &entry = d.GetDictEntry(de.GetTag());
      if( de.GetTag().GetElement() == 0x0 )
        {
        std::cout << de << "\t # (" << gd.GetName(de.GetTag().GetGroup() )
          << ") " << entry.GetName() << std::endl;
        }
      else
        {
        //VR::VRType vr = entry.GetVR();
        std::cout << de << "\t # " << entry.GetName() << std::endl;
        }
      }
    }
  catch(std::exception &e)
    {
    std::cerr << "Exception:" << typeid(e).name() << std::endl;
    }
}


//template<class DEType>
//void PrintDataElements(Printer &is)
//{
//  PrintDataElement<DEType>(is);
//}

void Printer::Initialize()
{
  DICOMIStream::Initialize();

  if( NegociatedTS == Explicit )
    {
    //PrintDataElements<gdcm::ExplicitDataElement>(*this);
    PrintExplicitDataElements(*this);
    }
  else
    {
    //PrintDataElements<gdcm::ImplicitDataElement>(*this);
    PrintImplicitDataElements(*this);
    }
  // FIXME a file that reach eof is not valid...
  Close();
  Open();
}

}
