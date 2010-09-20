// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GDCMNETWORKTESTBED_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GDCMNETWORKTESTBED_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef GDCMNETWORKTESTBED_EXPORTS
#define GDCMNETWORKTESTBED_API __declspec(dllexport)
#else
#define GDCMNETWORKTESTBED_API __declspec(dllimport)
#endif

// This class is exported from the gdcmNetworkTestbed.dll
class GDCMNETWORKTESTBED_API CgdcmNetworkTestbed {
public:
	CgdcmNetworkTestbed(void);
	// TODO: add your methods here.
};

extern GDCMNETWORKTESTBED_API int ngdcmNetworkTestbed;

GDCMNETWORKTESTBED_API int fngdcmNetworkTestbed(void);
