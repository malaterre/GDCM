#include "gdcmPrinter.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmDict.h"
#include "gdcmGroupDict.h"
#include "gdcmAttribute.h"

namespace gdcm
{
//  uint32_t FindLength(VR::VRType vr, VM::VMType vm)
//    {
//    uint32_t size = VR::GetLength(vr);
//    uint32_t nVM = VM::GetLength(vm); // number of separators
//    size *= nVM;
//    size += nVM - 1; // number of separators (\)
//    return size;
//    }
//
//void PrintValue(const Value &val, VR::VRType vr, VM::VMType )
//    {
//    std::ostream &_os = std::cout;
//    const char *p = val.GetPointer();
//    if ( VR::IsString( vr ) )
//      {
//      assert( val.IsPrintable() );
//      _os << p;
//      }
//    else if ( vr == VR::FL )
//      {
//      }
//    else if ( vr == VR::SL )
//      {
//      int32_t length;
//      assert( val.GetLength() == 4);
//      memcpy(&length, p, 4);
//      _os << length;
//      }
//    else if ( vr == VR::SS )
//      {
//      int16_t length;
//      assert( val.GetLength() == 2);
//      memcpy(&length, p, 2);
//      _os << length;
//      }
//    else if ( vr == VR::UL )
//      {
//      uint32_t length;
//      assert( val.GetLength() == 4);
//      memcpy(&length, p, 4);
//      _os << length;
//      }
//    else if ( vr == VR::US )
//      {
//      uint16_t length;
//      assert( val.GetLength() == 2);
//      memcpy(&length, p, 2);
//      _os << length;
//      }
//    else
//      {
//      _os << "FIXME";
//      _os << " (Length: " << val.GetLength() << ")";
//      }
//    }

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
        _os << de.GetTag() << " VR(?)=" << vr;
        _os << ",VL=" << std::dec << de.GetValueLength()
          << " ValueField=[";

        // Use super class of the template stuff
        gdcm::Attribute af;
        af.SetVR(vr);
        af.SetVM(vm);
        //af.SetLength( val.GetLength() );
        //std::cerr << "Diff:" << val.GetLength() << " " << 
        //  strlen(val.GetPointer()) << std::endl;
        af.SetLength( strlen( val.GetPointer() ) );
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
