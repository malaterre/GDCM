# http://www.cmake.org/Wiki/CmakeMingw
# Usage:
#
#  $ cmake ../gdcm -DCMAKE_TOOLCHAIN_FILE=../gdcm/CMake/Toolchain-mingw32.cmake
#
#
#  Copyright (c) 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

# the name of the target operating system
set(CMAKE_SYSTEM_NAME Windows)

# which compilers to use for C and C++
set(CMAKE_C_COMPILER i586-mingw32msvc-gcc)
set(CMAKE_CXX_COMPILER i586-mingw32msvc-g++)
set(CMAKE_RC_COMPILER i586-mingw32msvc-windres)

# here is the target environment located
set(CMAKE_FIND_ROOT_PATH  /usr/i586-mingw32msvc)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

#find_package(WINE REQUIRED)
find_program(WINE_EXECUTABLE
  NAMES wine
  )
set(TARGET_SYSTEM_EMULATOR ${WINE_EXECUTABLE})
