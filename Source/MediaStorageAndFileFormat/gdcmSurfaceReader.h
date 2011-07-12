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

  protected:

    bool ReadSurfaces();

    bool ReadSurface(const Item & surfaceItem, const unsigned long idx);
};

}

#endif // GDCMSURFACEREADER_H
