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

/*
 * http://groups.google.com/group/comp.protocols.dicom/browse_thread/thread/10f91b14e3013a11
 * http://groups.google.com/group/comp.protocols.dicom/browse_thread/thread/1190189387c1702c
 * http://groups.google.com/group/comp.protocols.dicom/browse_thread/thread/a9e118fbbf6dcc9f
 * http://forum.dcmtk.org/viewtopic.php?p=5441&sid=61ad1304edb31203c4136890ab651405
YBR_FULL as Photometric Interpretation is really the right thing to do. The problem is that the JPEG bitstream as such does not contain any indication of the color model - it just specifies that there are three samples per pixel. In theory it is well possible to apply baseline JPEG compression to RGB pixel data, although this is an unusual approach since YCbCr provides for better compression ratio at given image quality. A JFIF header would contain that information, but the JFIF header is neither required nor recommended in the DICOM JPEG bitstream. In the absence of that information, and with a JPEG compressed DICOM file where Photometric Interpretation is "RGB", the parser needs to decide whether the encoder did something unsual but legal and decompress the JPEG bitstream as RGB, or whether the encoder just failed to correctly encode the color model of the JPEG bitstream (which in my experience is in most cases the correct assumption) and ignore Photometric Interpretation (and thus incorrectly decode unusual but legal images).
*/
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

