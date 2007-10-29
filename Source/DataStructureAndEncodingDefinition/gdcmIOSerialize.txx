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
#include "gdcmStringStream.h"
#include "gdcmElement.h"


namespace gdcm
{


//-----------------------------------------------------------------------------
template <typename TSwap>
IStream &IOSerialize<TSwap>::Read(IStream &is,DataSet &ds)
{
  //std::cerr << "DataSet::Read Length=" << Length << std::endl;
  if( ds.Length == 0)
    {
    // Ok we are reading a root DataSet
    if(ds.NegociatedTS == TS::Implicit)
      {
      StructuredSet<ImplicitDataElement> ssi;
      //std::cerr << "passed 0" << std::endl;
      ssi.template Read<TSwap>(is);
      //std::cerr << "passed" << std::endl;
      ds.Internal.Copy(ssi);
      }
    else if ( ds.NegociatedTS == TS::Explicit )
      {
      ds.Internal.template Read<TSwap>(is);
      //Internal.ReadSwap(is);
      }
    }
  else if( ds.Length.IsUndefined() )
    {
    if(ds.NegociatedTS == TS::Implicit)
    {
      StructuredSet<ImplicitDataElement> ssi;
      //std::cerr << "passed nested 0" << std::endl;
      ssi.template ReadNested<TSwap>(is);
      //std::cerr << "passed nested" << std::endl;
      ds.Internal.Copy(ssi);
     }
    else if ( ds.NegociatedTS == TS::Explicit )
    {
    // Nested DataSet with undefined length 
    ds.Internal.template ReadNested<TSwap>(is);
    }
    }
  else
    {
    if(ds.NegociatedTS == TS::Implicit)
    {
      StructuredSet<ImplicitDataElement> ssi;
      //std::cerr << "passed 0" << std::endl;
      ssi.template ReadWithLength<TSwap>(is,ds.Length);
      //std::cerr << "passed" << std::endl;
      ds.Internal.Copy(ssi);
     }
    else if ( ds.NegociatedTS == TS::Explicit )
    {
     // Nested DataSet with defined length
    ds.Internal.template ReadWithLength<TSwap>(is, ds.Length);
    }
    }
  //std::cerr << "Finished DataSet::Read" << std::endl;
  return is;
}

//-----------------------------------------------------------------------------
template <typename TSwap>
OStream const &IOSerialize<TSwap>::Write(OStream &os,DataSet const &ds)
{
    if(ds.NegociatedTS == TS::Implicit)
      {
      StructuredSet<ImplicitDataElement> ssi;
      ssi.Copy(ds.Internal);
      ssi.template Write<TSwap>(os);
      }
    else if ( ds.NegociatedTS == TS::Explicit )
    {
   ds.Internal.template Write<TSwap>(os);
    }
  return os;
}





} // end namespace gdcm

#endif // __gdcmIOSerialize_txx

