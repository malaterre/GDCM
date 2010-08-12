/* socket++/config.h.  Generated from config.h.in by configure.  */
/* socket++/config.h.in.  Generated from configure.in by autoheader.  */
/* Define if extern "C" is needed arround include files */
#define EXTERN_C_BEGIN 
#define EXTERN_C_END 

/* Define either as _sys_siglist or sys_siglist */
#define SYS_SIGLIST sys_siglist

/* Define the argument type for signal handler function */
#define SIGHND_ARGTYPE int

/* Define either as _sys_errlist or sys_errlist */
#define SYS_ERRLIST sys_errlist

/* Define SYS_ERRLIST_DECLARED if extern char* SYS_ERRLIST []; is found */
#define SYS_ERRLIST_DECLARED 1

/* Define SA_RESTART if it is not defined in sys/signal.h */
/* #undef SA_RESTART */

/* Define if you have libg++ */
/* #undef _S_LIBGXX */

/* Version */
/* #undef SOCKET_MAJOR_VERSION */
/* #undef SOCKET_MINOR_VERSION */
/* #undef SOCKET_MICRO_VERSION */

/* Configuration Options */
/* #undef ENABLE_DEBUG */



/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the `fork' function. */
#define HAVE_FORK 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `select' function. */
#define HAVE_SELECT 1

/* Define to 1 if you have the <sstream> header file. */
#define HAVE_SSTREAM 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <string> header file. */
#define HAVE_STRING 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have <sys/wait.h> that is POSIX.1 compatible. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `vfork' function. */
#define HAVE_VFORK 1

/* Define to 1 if you have the <vfork.h> header file. */
/* #undef HAVE_VFORK_H */

/* Define to 1 if `fork' works. */
#define HAVE_WORKING_FORK 1

/* Define to 1 if `vfork' works. */
#define HAVE_WORKING_VFORK 1

/* Name of package */
#define PACKAGE "socket++"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "1.12.12"

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define as `fork' if `vfork' does not work. */
/* #undef vfork */
#include <local.h>
