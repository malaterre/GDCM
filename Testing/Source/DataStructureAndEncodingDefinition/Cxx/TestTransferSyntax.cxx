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
#include "gdcmTransferSyntax.h"

int TestTransferSyntax(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  gdcm::TransferSyntax ts;

  ts = gdcm::TransferSyntax::JPEG2000;
  if( !ts.IsLossless() )
    {
    return 1;
    }
  if( !ts.IsLossy() )
    {
    return 1;
    }
  ts = gdcm::TransferSyntax::JPEGLosslessProcess14_1;
  if( !ts.IsLossless() )
    {
    return 1;
    }
  if( ts.IsLossy() )
    {
    return 1;
    }
  ts = gdcm::TransferSyntax::DeflatedExplicitVRLittleEndian;
  if( !ts.IsLossless() )
    {
    return 1;
    }
  if( ts.IsLossy() )
    {
    return 1;
    }

  return 0;
}
