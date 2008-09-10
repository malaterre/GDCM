/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "gdcmImageChangePhotometricInterpretation.h"
#include "gdcmSequenceOfFragments.h"
#include "gdcmSequenceOfItems.h"
#include "gdcmFragment.h"

namespace gdcm
{

bool ImageChangePhotometricInterpretation::Change()
{
  // PS 3.3 - 2008 C.7.6.3.1.2 Photometric Interpretation
  Output = Input;
  if( PI == PhotometricInterpretation::YBR_FULL )
    {
    assert( Input->GetPhotometricInterpretation() == PhotometricInterpretation::RGB );
    /*
    In the case where Bits Allocated (0028,0100) has a value of 8 then the following equations convert
    between RGB and YCBCR Photometric Interpretation.
    Y = + .2990R + .5870G + .1140B
    CB = - .1687R - .3313G + .5000B + 128
    CR = + .5000R - .4187G - .0813B + 128
    Note: The above is based on CCIR Recommendation 601-2 dated 1990.
    */
    }
  else if( PI == PhotometricInterpretation::RGB )
    {
    /* octave:
     * B = [.2990,.5870,.1140;- .16874, - .33126,  .5000; .5000, - .41869, - .08131]
     * inv(B)
     * 1.0000e+00   -3.6820e-05    1.4020e+00
     * 1.0000e+00   -3.4411e-01   -7.1410e-01
     * 1.0000e+00    1.7720e+00   -1.3458e-04
     */

    }
  else
    {
    return false;
    }

  return true;
}


} // end namespace gdcm

