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

#ifdef GDCM_SUPPORT_BROKEN_IMPLEMENTATION
#include "gdcmUNExplicitDataElement.h"
#include "gdcmCP246ExplicitDataElement.h"
#include "gdcmExplicitImplicitDataElement.h"
#endif

namespace gdcm
{

std::istream &File::Read(std::istream &is) 
{
  bool haspreamble = true;
  try
    {
    P.Read( is );
    }
  catch( std::exception &ex )
    {
    // return to beginning of file, hopefully this file is simply missing preamble
    is.seekg(0, std::ios::beg);
    haspreamble = false;
    }
  catch( ... )
    {
    abort();
    }

  bool hasmetaheader = true;
  try
    {
    if( haspreamble )
      {
      try
        {
        Header.Read( is );
        }
      catch( std::exception &ex )
        {
        // Weird implicit meta header:
        is.seekg(128+4, std::ios::beg );
        try
          {
          Header.ReadCompat(is);
          }
        catch( std::exception &ex )
          {
          // Ok I get it now... there is absolutely no meta header, giving up
          hasmetaheader = false;
          }
        }
      }
    else
      Header.ReadCompat(is);
    }
  catch( std::exception &ex )
    {
    // Same player play again:
    is.seekg(0, std::ios::beg );
    hasmetaheader = false;
    }
  catch( ... )
    {
    // Ooops..
    abort();
    }

  const TransferSyntax &ts = Header.GetDataSetTransferSyntax();
  //std::cerr << ts.GetNegociatedType() << std::endl;
  //std::cerr << TransferSyntax::GetTSString(ts) << std::endl;
  // Special case where the dataset was compressed using the deflate
  // algorithm
  if( ts == TransferSyntax::DeflatedExplicitVRLittleEndian )
    {
    gzistream gzis(is.rdbuf());
    // FIXME: we also know in this case that we are dealing with Explicit:
    assert( ts.GetNegociatedType() == TransferSyntax::Explicit );
    DS.Read<ExplicitDataElement,SwapperNoOp>(gzis);
    is.seekg(0, std::ios::end);
    is.peek();

    return is;
    }

  try
    {
    if( ts.GetSwapCode() == SwapCode::BigEndian )
      {
      //US-RGB-8-epicard.dcm is big endian
      if( ts.GetNegociatedType() == TransferSyntax::Implicit )
        {
        // There is no such thing as Implicit Big Endian... oh well
        // LIBIDO-16-ACR_NEMA-Volume.dcm 
        DS.Read<ImplicitDataElement,SwapperDoOp>(is);
        }
      else
        {
        DS.Read<ExplicitDataElement,SwapperDoOp>(is);
        }
      }
    else // LittleEndian
      {
      if( ts.GetNegociatedType() == TransferSyntax::Implicit )
        {
        DS.Read<ImplicitDataElement,SwapperNoOp>(is);
        }
      else
        {
        DS.Read<ExplicitDataElement,SwapperNoOp>(is);
        }
      }
    }
  // Only catch parse exception at this point
  catch( ParseException &ex )
    {
    if( ex.GetLastElement().GetVR() == VR::UN && ex.GetLastElement().IsUndefinedLength() )
      {
      // non CP 246
      // P.Read( is );
      is.clear();
      if( haspreamble )
        {
        is.seekg(128+4, std::ios::beg);
        }
      else
        {
        is.seekg(0, std::ios::beg);
        }
      if( hasmetaheader )
        {
        // FIXME: we are reading twice the same meta-header, we succedeed the first time...
        // We should be able to seek to proper place instead of re-reading
        FileMetaInformation header;
        header.Read(is);
        }

      // GDCM 1.X
      gdcmWarningMacro( "Attempt to read non CP 246" );
      DS.Clear(); // remove garbage from 1st attempt...
      DS.Read<CP246ExplicitDataElement,SwapperNoOp>(is);
      }
    else if( ex.GetLastElement().GetVR() == VR::UN )
      {
      // P.Read( is );
      is.clear();
      if( haspreamble )
        {
        is.seekg(128+4, std::ios::beg);
        }
      else
        {
        is.seekg(0, std::ios::beg);
        }
      if( hasmetaheader )
        {
        // FIXME: we are reading twice the same meta-header, we succedeed the first time...
        // We should be able to seek to proper place instead of re-reading
        FileMetaInformation header;
        header.Read(is);
        }

      // GDCM 1.X
      gdcmWarningMacro( "Attempt to read GDCM 1.X wrongly encoded");
      DS.Clear(); // remove garbage from 1st attempt...
      DS.Read<UNExplicitDataElement,SwapperNoOp>(is);
      // This file can only be rewritten as implicit...
      }
    else
      {
      // Let's try again with an ExplicitImplicitDataElement:
      if( ts.GetSwapCode() == SwapCode::LittleEndian &&
        ts.GetNegociatedType() == TransferSyntax::Explicit )
        {
        // P.Read( is );
        if( haspreamble )
          {
          is.seekg(128+4, std::ios::beg);
          }
        else
          {
          is.seekg(0, std::ios::beg);
          }
        if( hasmetaheader )
          {
          // FIXME: we are reading twice the same meta-header, we succedeed the first time...
          // We should be able to seek to proper place instead of re-reading
          FileMetaInformation header;
          header.ReadCompat(is);
          }

        // Philips
        gdcmWarningMacro( "Attempt to read the file as mixture of explicit/implicit");
        DS.Clear(); // remove garbage from 1st attempt...
        DS.Read<ExplicitImplicitDataElement,SwapperNoOp>(is);
        // This file can only be rewritten as implicit...
        }
      }
    }

  return is;
}

std::ostream const &File::Write(std::ostream &os) const
{
  P.Write(os);

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
    if( P.IsEmpty() )
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

