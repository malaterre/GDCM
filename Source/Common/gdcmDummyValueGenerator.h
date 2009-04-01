/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2009 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmDummyValueGenerator_h
#define __gdcmDummyValueGenerator_h

#include "gdcmTypes.h"

namespace gdcm
{

/**
 * \brief Class for generating dummy value
 * \note bla
 */
class GDCM_EXPORT DummyValueGenerator
{
public:
//  DummyValueGenerator();

  /// NOT THREAD SAFE:
  static const char* Generate(const char *input);

private:
};


} // end namespace gdcm

#endif //__gdcmDummyValueGenerator_h
