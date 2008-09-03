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
#ifndef __gdcmImageChangePlanarConfiguration_h
#define __gdcmImageChangePlanarConfiguration_h

#include "gdcmImageToImageFilter.h"

namespace gdcm
{

class DataElement;
/**
 * \brief ImageChangePlanarConfiguration class
 * Class to change the Planar configuration of an input DICOM
 * By default it will change into the more usual reprensentation: PlanarConfiguration = 0
 */
class GDCM_EXPORT ImageChangePlanarConfiguration : public ImageToImageFilter
{
public:
  ImageChangePlanarConfiguration():PlanarConfiguration(0) {}
  ~ImageChangePlanarConfiguration() {}

  /// Set/Get requested PlanarConfigation
  void SetPlanarConfiguration(unsigned int pc) { PlanarConfiguration = pc; }
  unsigned int GetPlanarConfiguration() const { return PlanarConfiguration; }

  /// s is the size of one plane (r,g or b). Thus the output buffer needs to be at least 3*s bytes long
  static size_t RGBPlanesToRGBPixel(char *out, const char *r, const char *g, const char *b, size_t s);

  /// Change
  bool Change();

protected:

private:
  unsigned int PlanarConfiguration;
};

} // end namespace gdcm

#endif //__gdcmImageChangePlanarConfiguration_h

