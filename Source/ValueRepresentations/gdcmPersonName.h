
#ifndef __gdcmPersonName_h
#define __gdcmPersonName_h

#include "gdcmType.h"
#include "gdcmString.h"
#include <iostream>
#include <iomanip>
#include <assert.h>

namespace gdcm
{

/**
 * \brief Class 
 * Components: <family name (ST)> ^ <given name (ST)> ^ <middle initial or name (ST)> ^ <suffix (e.g., JR or III) (ST)> ^ <prefix (e.g., DR) (ST)> ^ <degree (e.g., MD) (ST)>

Example:

|SMITH^JOHN^J^III^DR^PHD|

This data type includes multiple free text components. Each component is specified to be an HL7 ST data type. The maximum length of a PN field is 48 characters including component separators. The sending system may send upper- and lowercase or all uppercase. The receiving system may convert to all uppercase if required.
2.8.28.1 Family name (ST)
2.8.28.2 Given name (ST)
2.8.28.3 Middle initial or name (ST)
2.8.28.4 Suffix (ST)

Used to specify a name suffix (e.g., Jr. or III).
2.8.28.5 Prefix (ST)

Used specify a name prefix (e.g., Dr.).
2.8.28.6 Degree (ST)

Used to specify an educational degree (e.g., MD).
 */
const unsigned int PersonNameMaxSize = 48;
class GDCM_EXPORT PersonName : public String
{
public:
  typedef String Superclass;
  PersonName() : Superclass() {}
  PersonName(const value_type* s) : Superclass(s) {}

  unsigned int GetMaxSize() { return PersonNameMaxSize; }

private:
};

//inline std::istream& operator>>(std::istream &_is, const PersonName &_val)
//{
//  _is.getline(_val, GetMaxSize(), '\\');
//}

} // end namespace gdcm

#endif //__gdcmPersonName_h
