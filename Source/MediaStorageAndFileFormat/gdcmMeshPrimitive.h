#ifndef GDCMMESHPRIMITIVE_H
#define GDCMMESHPRIMITIVE_H

#include "gdcmObject.h"
#include "gdcmDataElement.h"

#include <vector>

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

    const DataElement & GetPrimitiveData() const;
    DataElement & GetPrimitiveData();
    void SetPrimitiveData(DataElement const & de);

    const ::std::vector< DataElement > & GetPrimitivesData() const;
    ::std::vector< DataElement > & GetPrimitivesData();
    void SetPrimitivesData(::std::vector< DataElement > const & DEs);

protected:

    MPType                        PrimitiveType;

    ::std::vector< DataElement >  PrimitiveData;
};

}

#endif // GDCMMESHPRIMITIVE_H
