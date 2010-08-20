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
#ifndef GDCMASSOCIATIONRELEASE_H
#define GDCMASSOCIATIONRELEASE_H

#include "gdcmTypes.h"

namespace gdcm
{

namespace network
{

/**
 */
class AssociationRelease
{
public:
  AssociationRelease();
  std::iostream &Run(std::iostream &is);

  /// \internal Compute Size
  //size_t Size() const;
  //void Print(std::ostream &os) const;

private:
};

} // end namespace network

} // end namespace gdcm

#endif //GDCMASSOCIATIONRELEASE_H
