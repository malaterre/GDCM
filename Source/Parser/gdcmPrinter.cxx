#include "gdcmPrinter.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"

namespace gdcm
{
template<class DEType>
void PrintDataElements(gdcm::DICOMIStream &is)
{
  DEType de;
  gdcm::DataElement &de_tag = de;

  try
    {
    while( !is.eof() && is.Read(de_tag) )
      {
      is.Read(de);
      std::cerr << de << std::endl;
      }
    }
  catch(std::exception &e)
    {
    std::cerr << "Exception:" << typeid(e).name() << std::endl;
    }
}


template<class DEType>
void BrowseDataElements(Printer &is)
{
  PrintDataElements<DEType>(is);
}

void Printer::Initialize()
{
  DICOMIStream::Initialize();

  if( NegociatedTS == Explicit )
    {
    BrowseDataElements<gdcm::ExplicitDataElement>(*this);
    }
  else
    {
    BrowseDataElements<gdcm::ImplicitDataElement>(*this);
    }
  // FIXME a file that reach eof is not valid...
  Close();
  Open();
}

}
