#include "gdcmPrinter.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmDict.h"
#include "gdcmGroupDict.h"

namespace gdcm
{

void PrintImplicitDataElements(gdcm::DICOMIStream &is)
{
  gdcm::ImplicitDataElement de;
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
        std::cout << de << "\t # (" << gd.GetName(de.GetTag().GetGroup() ) << ") " 
          << entry.GetName() << std::endl;
        }
      else
        {
        // Use VR from dictionary
        VR::VRType vr = entry.GetVR();
        de.Print(vr, std::cout);
        std::cout << "\t # " << entry.GetName() << std::endl;
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
        std::cout << de << "\t # (" << gd.GetName(de.GetTag().GetGroup() ) << ") " 
          << entry.GetName() << std::endl;
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
