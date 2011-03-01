/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmPresentationContextGenerator.h"

#include "gdcmScanner.h"

namespace gdcm
{

namespace network
{
PresentationContextGenerator::PresentationContextGenerator() {}

bool PresentationContextGenerator::GenerateFromUID(UIDs::TSName tsname)
{
  PresContext.clear();

  AbstractSyntax as;
  as.SetNameFromUID( tsname );

  TransferSyntaxSub ts;
  ts.SetNameFromUID( UIDs::ImplicitVRLittleEndianDefaultTransferSyntaxforDICOM );

  AddPresentationContext( as, ts );

  return true;
}

bool PresentationContextGenerator::GenerateFromFilenames(const Directory::FilenamesType &filenames)
{
  PresContext.clear();

  // By design GDCM C-STORE implementation only setup the association for any dataset we are
  // about to send. This is therefore very important to gather all possible SOP Class
  // we are about to send otherwise the other end will simply disconnect us
  // this imply that C-STORE will refuse any DataSet without SOP Clas or SOP Instances
  gdcm::Scanner sc;
  gdcm::Tag tsuid(0x2,0x10);
  gdcm::Tag sopclass(0x2,0x2);
  //gdcm::Tag sopclass(0x8,0x16);
  gdcm::Tag sopinstance(0x8,0x18);
  sc.AddTag( tsuid );
  sc.AddTag( sopclass );
  //sc.AddTag( sopinstance );
  if( !sc.Scan( filenames ) )
    {
    gdcmErrorMacro( "Could not scan filenames" );
    return 1;
    }

  Directory::FilenamesType::const_iterator file = filenames.begin();
  for(; file != filenames.end(); ++file)
    {
    const char *fn = file->c_str();
    const char *tsuidvalue = sc.GetValue(fn, tsuid);
    const char *sopclassvalue = sc.GetValue(fn, sopclass );

    AbstractSyntax as;
    as.SetName( sopclassvalue );
    TransferSyntaxSub ts;
    ts.SetName( tsuidvalue );
    AddPresentationContext( as, ts );
    }

  return true;
}

bool PresentationContextGenerator::AddPresentationContext( AbstractSyntax const & as, TransferSyntaxSub const & ts )
{
  SizeType n = PresContext.size();
  PresentationContext pc;
  pc.SetAbstractSyntax( as );
  pc.SetPresentationContextID( 2*n + 1 );
  pc.AddTransferSyntax( ts );

  PresContext.push_back( pc );

  return true;
}


} // end namespace network

} // end namespace gdcm
