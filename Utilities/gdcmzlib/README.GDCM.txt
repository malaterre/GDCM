This directory contains a subset of the zlib library (1.3.1) and
some custom changes.

We only include enough of the distribution to provide the functionalities
required.

We would like to thank the zlib team for distributing this library.
https://www.zlib.net

Added Files
-----------

zlib.rc
  -For MS Windows only: provide a version resource in a dll build so that
   when you look at the dll file in Windows explorer, it will show you the
   version in the "Version" tab of the file's properties view.

zlib.def.in
  -For MS Windows only: used to explicitly list the exports from dll builds.

zconf.h.in
  -a copy of zconf.h, but renamed
  -#cmakedefine ZLIB_DLL was added at lines 11-12

Changed Files
-------------

CMakeLists.txt
  -This file was originally created when zlib didn't have CMake support,
   which is why it's so different.

COPYING
  -An exact copy of LICENSE

You can search the code for "GDCM_ZLIB_CHANGE" to find modifications
vs the original zlib code
