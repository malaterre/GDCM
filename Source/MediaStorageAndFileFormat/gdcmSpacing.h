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
#ifndef __gdcmSpacing_h
#define __gdcmSpacing_h

#include "gdcmTypes.h"
#include "gdcmAttribute.h"

namespace gdcm
{
/**
 * \brief Class for Spacing 
 *
 * See PS 3.3-2008, Table C.7-11b IMAGE PIXEL MACRO ATTRIBUTES 

Ratio of the vertical size and horizontal size
of the pixels in the image specified by a
pair of integer values where the first value
is the vertical pixel size, and the second
value is the horizontal pixel size. Required
if the aspect ratio values do not have a
ratio of 1:1 and the physical pixel spacing is
not specified by Pixel Spacing (0028,0030),
or Imager Pixel Spacing (0018,1164) or
Nominal Scanned Pixel Spacing
(0018,2010), either for the entire Image or
per-frame in a Functional Group Macro.
See C.7.6.3.1.7.


Ref:
http://apps.sourceforge.net/mediawiki/gdcm/index.php?title=Imager_Pixel_Spacing
 */
class GDCM_EXPORT Spacing
{
public :
  Spacing();
  ~Spacing();

  static Attribute<0x28,0x34> ComputePixelAspectRatioFromPixelSpacing(const Attribute<0x28,0x30>& pixelspacing);
};
} // end namespace gdcm
//-----------------------------------------------------------------------------
#endif //__gdcmSpacing_h
