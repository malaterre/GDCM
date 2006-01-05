#ifndef __gdcmImageReader_h
#define __gdcmImageReader_h


namespace gdcm
{
/**
 * \brief Class for that only deal with DICOM Image (precondition)
 * Make use of a Parser
 *   Check for Row Column...
 *   Need a decompressor to decompress the Frames/Fragments for Encapsulated Data
 *
 * \note
 */
class GDCM_EXPORT ImageReader
{
public:
private:
};

} // end namespace gdcm

#endif //__gdcmImageReader_h
