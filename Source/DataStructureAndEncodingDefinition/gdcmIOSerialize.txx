/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmIOSerialize_txx
#define __gdcmIOSerialize_txx

#include "gdcmIOSerialize.h"

#include "gdcmStructuredSet.h"
#include "gdcmTag.h"
#include "gdcmVL.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmDataSet.h"
#include "gdcmByteValue.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmElement.h"


namespace gdcm
{


//-----------------------------------------------------------------------------
template <typename TSwap>
std::istream &IOSerialize<TSwap>::Read(std::istream &is,DataSet &ds)
{
  //std::cerr << "DataSet::Read Length=" << Length << std::endl;
  if( ds.Length == 0)
    {
    // Ok we are reading a root DataSet
    if(ds.NegociatedTS == TransferSyntax::Implicit)
      {
      ds.Internal.template Read<ImplicitDataElement,TSwap>(is);
      }
    else if ( ds.NegociatedTS == TransferSyntax::Explicit )
      {
      ds.Internal.template Read<ExplicitDataElement,TSwap>(is);
      //Internal.ReadSwap(is);
      }
    }
  else if( ds.Length.IsUndefined() )
    {
    if(ds.NegociatedTS == TransferSyntax::Implicit)
      {
      ds.Internal.template ReadNested<ImplicitDataElement,TSwap>(is);
      }
    else if ( ds.NegociatedTS == TransferSyntax::Explicit )
    {
    // Nested DataSet with undefined length 
    ds.Internal.template ReadNested<ExplicitDataElement,TSwap>(is);
    }
    }
  else
    {
    if(ds.NegociatedTS == TransferSyntax::Implicit)
     {
      ds.Internal.template ReadWithLength<ImplicitDataElement,TSwap>(is,ds.Length);
     }
    else if ( ds.NegociatedTS == TransferSyntax::Explicit )
    {
     // Nested DataSet with defined length
    ds.Internal.template ReadWithLength<ExplicitDataElement,TSwap>(is, ds.Length);
    }
    }
  //std::cerr << "Finished DataSet::Read" << std::endl;
  return is;
}

//-----------------------------------------------------------------------------
template <typename TSwap>
std::ostream const &IOSerialize<TSwap>::Write(std::ostream &os,DataSet const &ds)
{
    if(ds.NegociatedTS == TransferSyntax::Implicit)
      {
      ds.Internal.template Write<ImplicitDataElement,TSwap>(os);
      }
    else if ( ds.NegociatedTS == TransferSyntax::Explicit )
    {
   ds.Internal.template Write<ExplicitDataElement,TSwap>(os);
    }
  return os;
}





} // end namespace gdcm

#endif // __gdcmIOSerialize_txx

