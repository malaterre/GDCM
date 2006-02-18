#ifndef __gdcmFilePrinter_h
#define __gdcmFilePrinter_h
// TODO Class to implement printing
// Since DICOM does printing ?
// Also I would like to encapsulate the IsCharacterPrintable thing 
// (to avoid printing \0 and other weird characters)

#include "gdcmDICOMIStream.h"

namespace gdcm
{
class GDCM_EXPORT Printer : public DICOMIStream
{
public:
  void Initialize();
private:
};

}

#endif
