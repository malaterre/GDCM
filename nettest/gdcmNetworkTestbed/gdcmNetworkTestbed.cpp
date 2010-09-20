// gdcmNetworkTestbed.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "gdcmNetworkTestbed.h"


// This is an example of an exported variable
GDCMNETWORKTESTBED_API int ngdcmNetworkTestbed=0;

// This is an example of an exported function.
GDCMNETWORKTESTBED_API int fngdcmNetworkTestbed(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see gdcmNetworkTestbed.h for the class definition
CgdcmNetworkTestbed::CgdcmNetworkTestbed()
{
	return;
}
