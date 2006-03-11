I changed:
0008 0040 SS 1 Data Set Type (RET)
into:
0008 0040 US 1 Data Set Type (RET)
Indeed valid values are:
IMAGE=               0
GRAPHICS=            2
TEXT=                3
OTHER=             100
NULL=              101
IDENTIFIER=        102
PRIVATE IMAGE=    8000
PRIVATE GRAPHICS= 8002
PRIVATE TEXT=     8003 

therefore would not be able to do:
signed short a = 0x8003;
if ( a == 0x8003 )
