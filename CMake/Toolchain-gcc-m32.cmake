# http://www.cmake.org/Wiki/CmakeMingw
# Usage:
#
#  $ cmake ../trunk -DCMAKE_TOOLCHAIN_FILE=../trunk/CMake/Toolchain-mingw32.cmake 
#

# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Linux)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_C_FLAGS -m32)
SET(CMAKE_CXX_COMPILER g++)
SET(CMAKE_CXX_FLAGS -m32)

# here is the target environment located
SET(CMAKE_FIND_ROOT_PATH  /emul/ia32-linux )

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

