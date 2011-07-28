#ifndef GDCMSURFACEREADER_H
#define GDCMSURFACEREADER_H

#include <gdcmSegmentReader.h>
#include <gdcmSurface.h>

namespace gdcm
{

/**
  * \brief  This class defines a SURFACE IE reader.
  * It reads surface mesh module attributes.
  *
  * \see  PS 3.3 A.1.2.18 , A.57 and C.27
  */
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
