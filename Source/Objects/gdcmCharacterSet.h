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
  

  /*
   * Comments by JPR:
    We have to check :
    0008|0005 [Specific Character Set]

    ASCII         "ISO_IR 6"    (UTF-8)
    UTF-8         "ISO_IR 192"  (UTF-8)
    ISO Latin 1   "ISO_IR 100"  (ISO-8859-1)
    ISO Latin 2   "ISO_IR 101"  (ISO-8859-2)
    ISO Latin 3   "ISO_IR 109"  (ISO-8859-3)
    ISO Latin 4   "ISO_IR 110"  (ISO-8859-4)
    ISO Latin 5   "ISO_IR 148"  (ISO-8859-9)
    Cyrillic      "ISO_IR 144"  (ISO-8859-5)
    Arabic        "ISO_IR 127"  (ISO-8859-6)
    Greek         "ISO_IR 126"  (ISO-8859-7)
    Hebrew        "ISO_IR 138"  (ISO-8859-8)
    Japanese
    ISO_IR 13
    ISO-IR 13
    94
    G1
    JIS X 0201: Katakana
    ISO-IR 14
    94
    G0
    JIS X 0201: Romaji 
    */
class GDCM_EXPORT CharacterSet
{
public:
private:
};

} // end namespace gdcm

#endif //__gdcmCharacterSet_h
