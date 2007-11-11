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
#include "gdcmFile.h"

#include "gdcmSwapper.txx"
#include "gdcmDataSet.h"
#include "gdcmExplicitDataElement.h"
#include "gdcmImplicitDataElement.h"
#include "gdcmValue.h"

#include "gdcmIOSerialize.h"
#include "gdcmValue.h"
#include "gdcmItem.h"
#include "gdcmSequenceOfItems.h"

namespace gdcm
{

IStream &File::Read(IStream &is) 
{
  P.Read( is );

  try
    {
    Header.Read( is );
    }
  catch( std::exception &ex )
    {
    //std::cerr << ex.what() << std::endl;
    is.seekg(0, std::ios::beg );
    P.Read( is ); // FIXME: leak
    Header.ReadCompat(is);
    //throw ex; // re throw for now but we are loosing it's real type...
    //return is;
    }
  catch( ... )
    {
    // Ooops..
    // Same player play again:
    Header.ReadCompat( is );
    }

  // Now is a good time to find out the dataset transfer syntax
  //Header.ComputeDataSetTransferSyntax(); // FIXME !

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

  P.Write(os);

  Header.Write(os);

	//std::cerr << "Write dataset: " << DS.GetNegociatedType() << std::endl;
  IOSerialize<SwapperNoOp>::Write(os,DS);

  return os;
}

} // end namespace gdcm

