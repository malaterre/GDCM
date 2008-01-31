/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmFile.h"

#include "gdcmSwapper.h"
#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmValue.h"

#include "gdcmValue.h"
#include "gdcmItem.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmParseException.h"

#include "gdcmDeflateStream.h"

namespace gdcm
{

std::istream &File::Read(std::istream &is) 
{
  abort();
}

std::ostream const &File::Write(std::ostream &os) const
{
  // Should I check that 0002,0002 / 0008,0016 and 0002,0003 / 0008,0018 match ?

  try
    {
    Header.Write(os);
    }
  catch( std::exception &ex)
    {
    // File such as PICKER-16-MONO2-No_DicomV3_Preamble.dcm
    // are a pain to rewrite since the metaheader was declared as implicit
    // we have to do a look up the in the dictionary to find out VR for those element
    // this is too much work, and should be up to the user to convert the meta to something
    // legal ! Write them as implicit for now
    gdcmWarningMacro( "File written will not be legal" );
    if( Header.GetPreamble().IsEmpty() )
      {
      os.seekp(0, std::ios::beg);
      }
    else
      {
      os.seekp(128+4, std::ios::beg);
      }
    Header.DataSet::Write<ImplicitDataElement,SwapperNoOp>(os);
    }

  const TransferSyntax &ts = Header.GetDataSetTransferSyntax();
  assert( ts.IsValid() );

  if( ts == TransferSyntax::DeflatedExplicitVRLittleEndian )
    {
    gzostream gzos(os.rdbuf());
    assert( ts.GetNegociatedType() == TransferSyntax::Explicit );
    DS.Write<ExplicitDataElement,SwapperNoOp>(gzos);

    return os;
    }

  if( ts.GetSwapCode() == SwapCode::BigEndian )
    {
    //US-RGB-8-epicard.dcm is big endian
    if( ts.GetNegociatedType() == TransferSyntax::Implicit )
      {
      // There is no such thing as Implicit Big Endian... oh well
      // LIBIDO-16-ACR_NEMA-Volume.dcm 
      DS.Write<ImplicitDataElement,SwapperDoOp>(os);
      }
    else
      {
      assert( ts.GetNegociatedType() == TransferSyntax::Explicit );
      DS.Write<ExplicitDataElement,SwapperDoOp>(os);
      }
    }
  else // LittleEndian
    {
    if( ts.GetNegociatedType() == TransferSyntax::Implicit )
      {
      DS.Write<ImplicitDataElement,SwapperNoOp>(os);
      }
    else
      {
      assert( ts.GetNegociatedType() == TransferSyntax::Explicit );
      DS.Write<ExplicitDataElement,SwapperNoOp>(os);
      }
    }


  return os;
}

} // end namespace gdcm

