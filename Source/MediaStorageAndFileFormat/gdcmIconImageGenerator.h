/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMICONIMAGEGENERATOR_H
#define GDCMICONIMAGEGENERATOR_H

#include "gdcmPixmap.h"
#include "gdcmIconImage.h"

namespace gdcm
{
class IconImageGeneratorInternals;
/**
 * \brief IconImageGenerator
 * \see ImageReader
 */
class GDCM_EXPORT IconImageGenerator
{
public:
  IconImageGenerator();
  ~IconImageGenerator();

  /// Set/Get File
  void SetPixmap(const Pixmap& p) { P = p; }
  Pixmap &GetPixmap() { return *P; }
  const Pixmap &GetPixmap() const { return *P; }

  /// Set Target dimension of output Icon
  void SetOutputDimensions(const unsigned int dims[2]);

  /// Override default min/max to compute best rescale for 16bits -> 8bits
  /// downscale. Typically those value can be read from the SmallestImagePixelValue
  /// LargestImagePixelValue DICOM attribute.
  void SetPixelMinMax(double min, double max);

  /// Generate Icon
  bool Generate();

  /// Retrieve generated Icon
  const IconImage& GetIconImage() const { return *I; }

protected:

private:
  SmartPointer<Pixmap> P;
  SmartPointer<IconImage> I;
  IconImageGeneratorInternals *Internals;
};

} // end namespace gdcm

#endif //GDCMICONIMAGEGENERATOR_H
