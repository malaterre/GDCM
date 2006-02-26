
#ifndef __gdcmDictConverter_h
#define __gdcmDictConverter_h

#include "gdcmVR.h"
#include "gdcmVM.h"

namespace gdcm
{

/**
 * \brief Class to convert a .dic file into something else:
 *  - CXX code : embeded dict into shared lib (DICT_DEFAULT)
 *  - Debug mode (DICT_DEBUG)
 *  - XML dict (DICT_XML)
 * \note
 */
class DictConverterInternal;
class GDCM_EXPORT DictConverter
{
public:
  DictConverter();
  ~DictConverter();
  void SetInputFileName(const char* filename);
  const std::string &GetInputFilename() const;
  void SetOutputFileName(const char* filename);
  const std::string &GetOutputFilename() const;

  int GetOutputType() const {
    return OutputType;
  }
  void SetOutputType(int type) {
    OutputType = type;
  }

  void Convert();

  // Leaving them public for now. Not really user oriented but may be 
  // usefull
  static bool ReadVR(const char *raw, VR::VRType &type);
  static bool ReadVM(const char *raw, VM::VMType &type);
  static bool Readuint16(const char *raw, uint16_t &ov);

  enum OutputTypes {
    DICT_DEFAULT = 0,
    DICT_DEBUG,
    DICT_XML
  };

protected:
  void WriteHeader();
  void WriteFooter();
  bool ConvertToXML(const char *raw, std::string &cxx);
  bool ConvertToCXX(const char *raw, std::string &cxx);
  void AddGroupLength();

private:
  DictConverterInternal *Internal;

  int OutputType;
};

} // end namespace gdcm

#endif //__gdcmDictConverter_h
