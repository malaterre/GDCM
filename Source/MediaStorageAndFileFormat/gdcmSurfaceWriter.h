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

    /// Write
    bool Write(); // Execute()

    const unsigned long GetNumberOfSurfaces() const { return NumberOfSurfaces; }
    void SetNumberOfSurfaces(const unsigned long nb) { NumberOfSurfaces = nb; }

protected:

    // Write Surface Mesh Module
    bool PrepareWrite();

    //0066 0001 UL 1 Number of Surfaces
    unsigned long NumberOfSurfaces;
};

}

#endif // GDCMSURFACEWRITER_H
