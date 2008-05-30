/*=========================================================================

  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2008 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __gdcmImageHelper_h
#define __gdcmImageHelper_h

#include "gdcmTypes.h"
#include "gdcmTag.h"
#include <vector>

namespace gdcm
{

/**
 * \brief ImageHelper (internal class)
 *
 * \note
 * Helper for writing World images in DICOM. DICOM has a 'template' approach to image where 
 * MR Image Storage are distinct object from Enhanced MR Image Storage. For example the
 * Pixel Spacing in one object is not at the same position (ie Tag) as in the other
 * this class is the central (read: fragile) place where all the dispatching is done from
 * a united view of a world image (typically VTK or ITK point of view) down to the low
 * level DICOM point of view.
 *
 * Warning: do not expect the API of this class to be maintain at any point, since as
 * Modalities are added the API might have to be augmented or behavior changed to cope
 * with new modalities.
 */
class MediaStorage;
class DataSet;
class File;
class Image;
class GDCM_EXPORT ImageHelper
{
public:
  static std::vector<double> GetRescaleInterceptSlopeValue(File const & f);
  static void SetRescaleInterceptSlopeValue(File & f, const Image & img);

  static std::vector<double> GetOriginValue(File const & f);
  static void SetOriginValue(DataSet & ds, const Image & img);

  static std::vector<double> GetDirectionCosinesValue(File const & f);
  static void SetDirectionCosinesValue(DataSet & ds, const std::vector<double> & dircos);

  static std::vector<double> GetSpacingValue(File const & f);
  static void SetSpacingValue(DataSet & ds, const std::vector<double> & spacing);

  static bool ComputeSpacingFromImagePositionPatient(const std::vector<double> &imageposition, std::vector<double> & spacing);

protected:
  static Tag GetSpacingTagFromMediaStorage(MediaStorage const &ms);
  static Tag GetZSpacingTagFromMediaStorage(MediaStorage const &ms);
};

} // end namespace gdcm

#endif //__gdcmSpacing_h

