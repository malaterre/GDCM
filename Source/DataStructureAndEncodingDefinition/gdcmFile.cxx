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
#include "gdcmFile.h"

#include "gdcmSwapper.txx"
#include "gdcmDataSet.txx"
#include "gdcmExplicitDataElement.txx"
#include "gdcmImplicitDataElement.txx"
#include "gdcmValue.h"

#include "gdcmIOSerialize.txx"

namespace gdcm
{

IStream &File::Read(IStream &is) 
{
  P.Read( is );

  Header.Read( is );

  const TS &ts = Header.GetDataSetTransferSyntax();
  //std::cerr << ts.GetNegociatedType() << std::endl;
  if( ts.GetNegociatedType() == TS::Implicit )
  {
	  DS.SetType( TS::Implicit );
  }
  if( ts.GetSwapCode() == SwapCode::BigEndian )
  {
  //US-RGB-8-epicard.dcm is big endian
  IOSerialize<SwapperDoOp>::Read(is,DS);
  }
  else
  {
  IOSerialize<SwapperNoOp>::Read(is,DS);
  }

  return is;
}

OStream const &File::Write(OStream &os) const
{

	std::cerr << "Write" << std::endl;
  P.Write(os);
	std::cerr << "Write header" << std::endl;

  Header.Write(os);

	//std::cerr << "Write dataset: " << DS.GetNegociatedType() << std::endl;
  IOSerialize<SwapperNoOp>::Write(os,DS);

  return os;
}

} // end namespace gdcm

