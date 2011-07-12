#ifndef GDCMMESHPRIMITIVE_H
#define GDCMMESHPRIMITIVE_H

#include <gdcmObject.h>
#include <gdcmDataElement.h>

namespace gdcm
{

class GDCM_EXPORT MeshPrimitive : public Object
{
public:

    typedef enum {
        VERTEX = 0,
        EDGE,
        TRIANGLE,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
        LINE,
        FACET,
        MPType_END
        } MPType;

    static const char * GetMPTypeString(const MPType type);

    static MPType GetMPType(const char * type);

    MeshPrimitive();

    virtual ~MeshPrimitive();

    const MPType GetPrimitiveType() const { return PrimitiveType; }
    MPType GetPrimitiveType() { return PrimitiveType; }
    void SetPrimitiveType(const MPType type)
    {
        assert( type <= MPType_END );
        PrimitiveType = type;
    }

    const DataElement & GetPrimitiveData() const { return PrimitiveData; }
    DataElement & GetPrimitiveData() { return PrimitiveData; }
    void SetPrimitiveData(DataElement const & de) { PrimitiveData = de; }

protected:

    MPType      PrimitiveType;

    DataElement PrimitiveData;
};

}

#endif // GDCMMESHPRIMITIVE_H
