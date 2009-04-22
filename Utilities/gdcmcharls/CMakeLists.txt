project(charls)
cmake_minimum_required(VERSION 2.6)

APPEND_COPYRIGHT(${CMAKE_CURRENT_SOURCE_DIR}/License.txt)


# When user specify build type do not override settings:
IF(NOT CMAKE_BUILD_TYPE)
# The following compiler option are only meant for GCC:
IF(CMAKE_COMPILER_IS_GNUCC)
SET(CMAKE_CXX_FLAGS "-Wall -O3 -g" )
ENDIF(CMAKE_COMPILER_IS_GNUCC)
ENDIF(NOT CMAKE_BUILD_TYPE)

OPTION(charls_BUILD_SHARED_LIBS "Build CharLS with shared libraries." OFF)
SET(BUILD_SHARED_LIBS ${charls_BUILD_SHARED_LIBS})

add_library(CharLS header.cpp  interface.cpp  jpegls.cpp  
  stdafx.cpp
  )


add_executable(charlstest test/test.cpp test/time.cpp)
target_link_libraries (charlstest CharLS)

include(CTest)
add_test(charlstest charlstest)
