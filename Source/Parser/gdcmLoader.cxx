#include "gdcmLoader.h"

namespace gdcm
{
void Loader::Update()
{
  // Initialize needs to be call first 
  if( GetNegociatedTS() == DICOMIStream::Explicit )
    {
    DataSet<ExplicitDataElement> ds;
    try
      {
      ExplicitDataElement de;
      gdcm::DataElement &de_tag = de;

      while( !eof() && Read(de_tag) )
        {
        Read(de);
        //std::cerr << de << std::endl;
        ds.AddDataElement(de);
        }
      std::cout << "Debug::\n" << ds << std::endl;
      }
    catch(std::exception &e)
      {
      std::cerr << "Exception:" << typeid(e).name() << std::endl;
      }
    }
  else
    {
    DataSet<ImplicitDataElement> ds;
    try
      {
      ImplicitDataElement de;
      gdcm::DataElement &de_tag = de;

      while( !eof() && Read(de_tag) )
        {
        Read(de);
        //std::cerr << de << std::endl;
        ds.AddDataElement(de);
        }
      std::cout << "Debug::\n" << ds << std::endl;
      }
    catch(std::exception &e)
      {
      std::cerr << "Exception:" << typeid(e).name() << std::endl;
      }
    }
}

} // end namespace gdcm
