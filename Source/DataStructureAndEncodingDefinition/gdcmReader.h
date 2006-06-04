
#ifndef __gdcmReader_h
#define __gdcmReader_h

#include "gdcmIStream.h"
#include "gdcmDataSet.h"

namespace gdcm
{
/**
 * \brief Reader ala DOM (Document Object Model)
 *
 * Detailled description here
 *
 * A DataSet DOES NOT contains group 0x0002
 *
 * This is really a DataSet reader. This will not make sure the dataset
 * conform to any IOD at all. This is a completely different step. The 
 * reasoning was that user could control the IOD there lib would handle
 * and thus we would not be able to read a DataSet if the IOD was not found
 * Instead we separate the reading from the validation.
 *
 * From GDCM1.x. Users will realize that one feature is missing
 * from this DOM implementation. In GDCM 1.x user used to be able to 
 * control the size of the Value to be read. By default it was 0xfff.
 * The main author of GDCM2 thought this was too dangerous and harmful and 
 * therefore this feaure did not make it into GDCM2
 */
class GDCM_EXPORT Reader
{
public:
  Reader():Stream(),DS(0) {}
  ~Reader() {}

  int Read(); // Execute()

  const DataSet &GetDataSet() const {
    return *DS;
  }

protected:
  bool ReadPreamble();
  void ReadMetaInformation();

private:
  IStream Stream;
  DataSet *DS;
  typedef enum {
    Unknown = 0,
    Implicit,
    Explicit
    } NegociatedTSType;

  NegociatedTSType MetaInformationTS;
  TS::TSType       UsedTS;
};

} // end namespace gdcm

#endif //__gdcmReader_h
