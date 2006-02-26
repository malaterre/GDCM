
#ifndef __gdcmDictConverter_h
#define __gdcmDictConverter_h

#include "gdcmVR.h"
#include "gdcmVM.h"

namespace gdcm
{

/**
 * \brief Class to convert a .dic file into something else:
 *  - CXX code (embeede dict into shared lib)
 *  - XML dict
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

  void Convert();

  // Leaving them public for now. Not really user oriented but may be 
  // usefull
  static bool ReadVR(const char *raw, VR::VRType &type);
  static bool ReadVM(const char *raw, VM::VMType &type);
  static bool Readuint16(const char *raw, uint16_t &ov);

protected:
  void WriteHeader();
  void WriteFooter();
  bool ConvertToXML(const char *raw, std::string &cxx);
  bool ConvertToCXX(const char *raw, std::string &cxx);
  void AddGroupLength(); //std::ifstream &from, std::ofstream &into);

private:
  DictConverterInternal *Internal;
  //enum WriteModes {
  //  CXX_OUTPUT=0,
  //  XML_OUTPUT
  //};
  //int WriteMode;

  enum OutputTypes {
    DICT_DEFAULT = 0,
    DICT_DEBUG,
    DICT_XML
  };
  int OutputType;
};

} // end namespace gdcm

#endif //__gdcmDictConverter_h
