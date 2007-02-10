/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmElement.h"
#include "gdcmStructuredSet.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
void DataSet::Print(std::ostream &os) const
{
  os << "TS: " << NegociatedTS << "\n";
  StructuredSetBase *p = Internal;
  p->Print( os );
}


//-----------------------------------------------------------------------------
DataSet::DataSet(TS::NegociatedType const &type):Length(0)
{
  if(type == TS::Explicit)
    {
    Internal = new StructuredSet<ExplicitDataElement>;
    }
  else if ( type == TS::Implicit )
    {
    Internal = new StructuredSet<ImplicitDataElement>;
    }
  else
    {
    Internal = 0;
    }
  NegociatedTS = type;
}

//-----------------------------------------------------------------------------
DataSet::~DataSet()
{
  delete Internal;
}

//-----------------------------------------------------------------------------
DataSet& DataSet::operator=(DataSet const &)
{
  abort();
  return *this;
}

//-----------------------------------------------------------------------------
DataSet::DataSet(DataSet const &ds):Value(ds)
{
  NegociatedTS = ds.NegociatedTS;
  if ( NegociatedTS == TS::Explicit )
    {
    Internal = new StructuredSet<ExplicitDataElement>;
    }
  else if ( NegociatedTS == TS::Implicit )
    {
    Internal = new StructuredSet<ImplicitDataElement>;
    }
  else
    {
    Internal = 0;
    }
  *Internal = *(ds.Internal);
}

//-----------------------------------------------------------------------------
void DataSet::Clear() {
  Internal->Clear();
}

//-----------------------------------------------------------------------------
void DataSet::InsertDataElement(DataElement const &de)
{
  if(NegociatedTS == TS::Explicit)
    {
    const ExplicitDataElement & xde =
      static_cast<const ExplicitDataElement&>(de);
    static_cast<StructuredSet<ExplicitDataElement>* >(Internal)->
      Insert(xde);
    }
  else
    {
    const ImplicitDataElement & ide =
      static_cast<const ImplicitDataElement&>(de);
    static_cast<StructuredSet<ImplicitDataElement>* >(Internal)->
      Insert(ide);
    }
}

//-----------------------------------------------------------------------------
const DataElement& DataSet::GetDataElement(const Tag &t) const
{
  if(NegociatedTS == TS::Explicit)
  {
    return static_cast<StructuredSet<ExplicitDataElement>* >(Internal)->
      GetDataElement(t);
  }
  else
  {
    return static_cast<StructuredSet<ImplicitDataElement>* >(Internal)->
      GetDataElement(t);
  }
}

bool DataSet::FindDataElement(const Tag &t) const
{
  if(NegociatedTS == TS::Explicit)
  {
    return static_cast<StructuredSet<ExplicitDataElement>* >(Internal)->
      FindDataElement(t);
  }
  else
  {
    return static_cast<StructuredSet<ImplicitDataElement>* >(Internal)->
      FindDataElement(t);
  }
}

//-----------------------------------------------------------------------------
IStream &DataSet::Read(IStream &is)
{
  if( Length == 0)
    {
    // Ok we are reading a root DataSet
    Internal->Read(is);
    }
  else if( Length.IsUndefined() )
    {
    // Nested DataSet with undefined length 
    Internal->ReadNested(is);
    }
  else
    {
    // Nested DataSet with defined length
    Internal->ReadWithLength(is, Length);
    }
  return is;
}

const VL & DataSet::GetLength() const
{
  static VL length = 0;
  if( Length.IsUndefined() || Length == 0 )
    {
    length = Internal->GetLength();
    assert( length != 0 );
    return length;
    }
  assert( Length != 0 );
  return Length;
}

//-----------------------------------------------------------------------------
OStream const &DataSet::Write(OStream &os) const
{
  Internal->Write(os);
  return os;
}

} // end namespace gdcm
