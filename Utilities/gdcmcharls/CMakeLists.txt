project(charls)
cmake_minimum_required(VERSION 2.6)


# When user specify build type do not override settings:
IF(NOT CMAKE_BUILD_TYPE)
# The following compiler option are only meant for GCC:
IF(CMAKE_COMPILER_IS_GNUCC)
# the following is optimization micrmanagement that made better code for x86
# SET(CMAKE_CXX_FLAGS "-D NDEBUG -O3 -Wall -Wextra -pedantic -fvisibility=hidden -fomit-frame-pointer -momit-leaf-frame-pointer -fweb  -ftracer" )
SET(CMAKE_CXX_FLAGS "-D NDEBUG -O3" )
ENDIF(CMAKE_COMPILER_IS_GNUCC)
ENDIF(NOT CMAKE_BUILD_TYPE)

OPTION(charls_BUILD_SHARED_LIBS "Build CharLS with shared libraries." OFF)
SET(BUILD_SHARED_LIBS ${charls_BUILD_SHARED_LIBS})

add_library(CharLS header.cpp  interface.cpp  jpegls.cpp  )


add_executable(charlstest test/main.cpp test/time.cpp test/util.cpp test/bitstreamdamage.cpp test/compliance.cpp test/performance.cpp test/dicomsamples.cpp)
target_link_libraries (charlstest CharLS)

