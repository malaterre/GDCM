#ifndef __gdcmCompositeValue_h
#define __gdcmCompositeValue_h

#include "gdcmValue.h"

namespace gdcm
{
/**
 * \brief Class to 
 * \note
 * Just a design pattern, not sure if this is worse keeping this
 * intermediate class
 */
// Implementation this is called the Composite Design Pattern
class GDCM_EXPORT CompositeValue : public Value
{
};

} // end namespace gdcm

#endif // __gdcmCompositeValue_h
