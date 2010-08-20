/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2010 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmAssociationRelease.h"
#include "gdcmAReleaseRQPDU.h"

namespace gdcm
{
namespace network
{

/*
*/

AssociationRelease::AssociationRelease()
{
}

std::iostream &AssociationRelease::Run(std::iostream &ios)
{
  // send release:
  gdcm::network::AReleaseRQPDU rel;
  rel.Write( ios );

  return ios;
}

} // end namespace network
} // end namespace gdcm
