/*=========================================================================

  Program: GDCM (Grassroots DICOM). A DICOM library

  Copyright (c) 2006-2011 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef GDCMSURFACEWRITER_H
#define GDCMSURFACEWRITER_H

#include <gdcmSegmentWriter.h>
#include <gdcmSurface.h>

namespace gdcm
{

class GDCM_EXPORT SurfaceWriter : public SegmentWriter
{
public:
    SurfaceWriter();

    virtual ~SurfaceWriter();

//    const Surface & GetSurface() const { return *SurfaceData; }
//    Surface & GetSurface() { return *SurfaceData; }
//    void SetSurface(Surface const & segment);

    /// Write
    bool Write(); // Execute()

    const unsigned long GetNumberOfSurfaces();
    void SetNumberOfSurfaces(const unsigned long nb);

protected:

    bool PrepareWrite();

    const unsigned long ComputeNumberOfSurfaces();

    //0066 0001 UL 1 Number of Surfaces
    unsigned long NumberOfSurfaces;
};

}

#endif // GDCMSURFACEWRITER_H
