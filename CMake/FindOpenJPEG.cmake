# - Try to find the OpenJPEG (JPEG 2000) library
#
# Read-Only variables:
#  OPENJPEG_FOUND - system has the OpenJPEG library
#  OPENJPEG_INCLUDE_DIR - the OpenJPEG include directory
#  OPENJPEG_LIBRARIES - The libraries needed to use OpenJPEG

#=============================================================================
# Copyright 2006-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

# Try with pkg-config first
find_package(PkgConfig)
pkg_check_modules(OPENJPEG libopenjpeg1)
if(OPENJPEG_FOUND)
    set(OPENJPEG_INCLUDE_DIR ${OPENJPEG_INCLUDE_DIRS})
    set(OPENJPEG_LIBRARIES ${OPENJPEG_LDFLAGS})
else()
# Try to locate a cmake config file
find_package(OpenJPEG QUIET NO_MODULE)
mark_as_advanced(OpenJPEG_DIR)

if( NOT OpenJPEG_DIR )
set(OPENJPEG_VERSION_MAJOR 2) # FIXME ?
set(OPENJPEG_VERSION_MINOR 0) # FIXME ?
set(OPENJPEG_VERSION_PATCH 0) # FIXME ?
set(OPENJPEG_VERSION "${OPENJPEG_VERSION_MAJOR}.${OPENJPEG_VERSION_MINOR}.${OPENJPEG_VERSION_PATCH}")
find_path(OPENJPEG_INCLUDE_DIR
  NAMES openjpeg.h #openjpeg-1.0/openjpeg.h
  PATHS /usr/local/include
  /usr/local/include/openjpeg-1.0
  /usr/include
  /usr/include/openjpeg-1.0
  )

find_library(OPENJPEG_LIBRARY
  NAMES openjpeg
  )
endif()
endif()
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OpenJPEG REQUIRED_VARS
  OPENJPEG_LIBRARY
  OPENJPEG_INCLUDE_DIR
  VERSION_VAR OPENJPEG_VERSION
)

if(OPENJPEG_FOUND)
  set(OPENJPEG_LIBRARIES ${OPENJPEG_LIBRARY})
  set(OPENJPEG_INCLUDE_DIRS ${OPENJPEG_INCLUDE_DIR})
endif()

mark_as_advanced(
  OPENJPEG_LIBRARY
  OPENJPEG_INCLUDE_DIR
  )
