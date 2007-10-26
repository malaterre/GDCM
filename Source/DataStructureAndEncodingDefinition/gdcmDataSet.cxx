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
#include "gdcmDataSet.h"
//#include "gdcmExplicitDataElement.h"
//#include "gdcmImplicitDataElement.h"
//#include "gdcmElement.h"

namespace gdcm
{

//-----------------------------------------------------------------------------
void DataSet::Print(std::ostream &os) const
{
  os << "TS: " << NegociatedTS << "\n";
  Internal.Print( os );
}


//-----------------------------------------------------------------------------
DataSet::DataSet(TS::NegociatedType type):NegociatedTS(type),Length(0)
{
  assert( NegociatedTS == TS::Implicit ||
          NegociatedTS == TS::Explicit );
}

//-----------------------------------------------------------------------------
DataSet::~DataSet()
{
}

//-----------------------------------------------------------------------------
DataSet& DataSet::operator=(DataSet const &val)
{
  NegociatedTS = val.NegociatedTS;
  Internal = val.Internal;
  Length = val.Length;

  return *this;
}

//-----------------------------------------------------------------------------
DataSet::DataSet(DataSet const &ds):Value(ds)
{
  NegociatedTS = ds.NegociatedTS;
  Internal = ds.Internal;
  Length = ds.Length;
}

//-----------------------------------------------------------------------------
void DataSet::Clear()
{
  Internal.Clear();
}

//-----------------------------------------------------------------------------
void DataSet::InsertDataElement(ExplicitDataElement const &de)
{
  Internal.Insert(de);
}

//-----------------------------------------------------------------------------
const ExplicitDataElement& DataSet::GetDataElement(const Tag &t) const
{
    return Internal.GetDataElement(t);
}

bool DataSet::FindDataElement(const Tag &t) const
{
  return Internal.FindDataElement(t);
}

//-----------------------------------------------------------------------------
VL DataSet::GetLength() const
{
  //static VL length = 0;
  //if( Length.IsUndefined() || Length == 0 )
  //  {
  //  length = Internal.GetLength();
  //  assert( length != 0 );
  //  return length;
  //  }
  //assert( Length != 0 );
  //return Length;
  assert( NegociatedTS != TS::Implicit ); // TODO: when copying an internal DataSet GetLength
  // will take into account the VR... sigh
  return Internal.GetLength();
}

} // end namespace gdcm

