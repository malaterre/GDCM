#ifndef __gdcmPrinter_h
#define __gdcmPrinter_h
// TODO Class to implement printing
// Since DICOM does printing ?
// Also I would like to encapsulate the IsCharacterPrintable thing 
// (to avoid printing \0 and other weird characters)
// \todo I still need to implement skiping of group (shadow)
// need to implement longer field to read

#include "gdcmDICOMIStream.h"

namespace gdcm
{
class GDCM_EXPORT Printer : public DICOMIStream
{
public:
  Printer();
  ~Printer();
  void Initialize();

  void SetPrintVR(bool b) { PrintVR = b; }
  bool GetPrintVR() { return PrintVR; }

private:
  // If User wants to see the VR for ImplicitFile, option dont do anythin
  // in Explicit Transfer Syntax
  bool PrintVR;
};

}

#endif
