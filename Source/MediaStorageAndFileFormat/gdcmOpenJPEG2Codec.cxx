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
#include "gdcmOpenJPEG2Codec.h"

#include "gdcm_openjpeg2.h"

namespace gdcm
{

class OpenJPEG2Internals
{
public:
  OpenJPEG2Internals()
    {
    opj_set_default_encoder_parameters(&parameters);
    }
	opj_cparameters_t parameters;

};

OpenJPEG2Codec::OpenJPEG2Codec()
{
  Internals = new OpenJPEG2Internals;
}

OpenJPEG2Codec::~OpenJPEG2Codec()
{
  delete Internals;
}

} // end namespace gdcm
