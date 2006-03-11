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

      while( !eof() && Read(de) )
        {
        ds.AddDataElement(de);
        }
      gdcmDebugMacro( ds );
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

      while( !eof() && Read(de) )
        {
        ds.AddDataElement(de);
        }
      gdcmDebugMacro( ds );
      }
    catch(std::exception &e)
      {
      std::cerr << "Exception:" << typeid(e).name() << std::endl;
      }
    }
}

} // end namespace gdcm
