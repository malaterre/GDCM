#ifndef __gdcmCharacterSet_h
#define __gdcmCharacterSet_h

namespace gdcm
{
/**
 * \brief Class for representing a CharacterSet
 * \note bla
 * Encapsulate the functionality defined by the DICOM Specific Character 
 * Set attribute. should be able to
 * - parse the string values of the attribute,
 * - apply appropriate character conversions from c-string into 
 *   Unicode (?? to be defined later)
 * CHARACTER REPERTOIRE: 
 * A finite set of different characters that is considered to be complete 
 * for a given purpose and is specified independently of their encoding 
 * (also referred to as a character set).
 *
 * 3.11 CHARACTER HANDLING DEFINITIONS
 * This part of the standard makes use of the following terms defined in ISO/IEC 2022:1994
 * a) Coded Character Set; Code
 * b) Code Extension
 * c) Control Character
 * d) To Designate
 * e) Escape Sequence
 * f) Graphic Character
 * g) To Invoke
 */
class GDCM_EXPORT CharacterSet
{
public:
private:
};

} // end namespace gdcm

#endif //__gdcmCharacterSet_h
