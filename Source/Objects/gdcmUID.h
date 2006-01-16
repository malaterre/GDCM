#ifndef __gdcmUID_h
#define __gdcmUID_h


namespace gdcm
{
/**
 * \brief Class for representing a UID
 * \note
 * We should copy paste the old code from gdcm
 * including all the crazy stuff for creating new UID (Study, Serie and 
 * maybe SOP Instance UIDs)
 * Two constructor: one take no input (and use GDCM default Root)
 * other will use a specified Root (will be nicer for ITK which specify 
 * it's own root)
 */
class GDCM_EXPORT UID
{
public:
private:
};

} // end namespace gdcm

#endif //__gdcmUID_h
