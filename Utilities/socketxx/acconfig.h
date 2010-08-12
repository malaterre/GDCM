/* Define if extern "C" is needed arround include files */
#undef EXTERN_C_BEGIN
#undef EXTERN_C_END

/* Define either as _sys_siglist or sys_siglist */
#undef SYS_SIGLIST

/* Define the argument type for signal handler function */
#undef SIGHND_ARGTYPE

/* Define either as _sys_errlist or sys_errlist */
#undef SYS_ERRLIST

/* Define SYS_ERRLIST_DECLARED if extern char* SYS_ERRLIST []; is found */
#undef SYS_ERRLIST_DECLARED

/* Define SA_RESTART if it is not defined in sys/signal.h */
#undef SA_RESTART

/* Define if you have libg++ */
#undef _S_LIBGXX

/* Version */
#undef SOCKET_MAJOR_VERSION
#undef SOCKET_MINOR_VERSION
#undef SOCKET_MICRO_VERSION

/* Configuration Options */
#undef ENABLE_DEBUG


@BOTTOM@
#include <local.h>
