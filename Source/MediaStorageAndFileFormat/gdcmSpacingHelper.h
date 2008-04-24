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
#ifndef __gdcmSpacingHelper_h
#define __gdcmSpacingHelper_h

#include "gdcmTypes.h"
#include "gdcmTag.h"
#include <vector>

namespace gdcm
{

/**
 * \brief Spacing
 * \note
 * This is one of the most complex class in the toolkit since it needs to knows exactly where
 * the spacing is stored for each DICOM object (MR, CT, PET, US ... )
 */
class MediaStorage;
class DataSet;
class File;
class GDCM_EXPORT SpacingHelper
{
public:
  static std::vector<double> GetSpacingValue(File const & f);
  static void SetSpacingValue(DataSet & ds, const std::vector<double> & spacing);

  static bool ComputeSpacingFromImagePositionPatient(const std::vector<double> &imageposition, std::vector<double> & spacing);

protected:
  static Tag GetSpacingTagFromMediaStorage(MediaStorage const &ms);
  static Tag GetZSpacingTagFromMediaStorage(MediaStorage const &ms);
};

} // end namespace gdcm

#endif //__gdcmSpacing_h

