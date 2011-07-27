/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMSURFACEREADER_H
#define GDCMSURFACEREADER_H

#include <gdcmSegmentReader.h>
#include <gdcmSurface.h>

namespace gdcm
{

class GDCM_EXPORT SurfaceReader : public SegmentReader
{
public:
    SurfaceReader();

    virtual ~SurfaceReader();

    /// Read
    virtual bool Read();

    unsigned long GetNumberOfSurfaces() const;

  protected:

    bool ReadSurfaces();

    bool ReadSurface(const Item & surfaceItem, const unsigned long idx);
};

}

#endif // GDCMSURFACEREADER_H
