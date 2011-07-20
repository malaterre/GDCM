#ifndef GDCMMESHPRIMITIVE_H
#define GDCMMESHPRIMITIVE_H

#include <gdcmObject.h>
#include <gdcmDataElement.h>

namespace gdcm
{

class GDCM_EXPORT MeshPrimitive : public Object
{
public:

  typedef std::vector< DataElement > PrimitivesData;

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

    const PrimitivesData & GetPrimitivesData() const;
    PrimitivesData & GetPrimitivesData();
    void SetPrimitivesData(PrimitivesData const & DEs);

    const DataElement & GetPrimitiveData(const unsigned int idx) const;
    DataElement & GetPrimitiveData(const unsigned int idx);
    void SetPrimitiveData(const unsigned int idx, DataElement const & de);

    const unsigned int GetNumberOfPrimitivesData() const;

protected:

    MPType                        PrimitiveType;

    PrimitivesData  PrimitiveData;
};

}

#endif // GDCMMESHPRIMITIVE_H
