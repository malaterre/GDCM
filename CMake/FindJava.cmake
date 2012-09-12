# - Find Java
# This module finds if Java is installed and determines where the
# include files and libraries are. This code sets the following
# variables:
#
#  Java_JAVA_EXECUTABLE    = the full path to the Java runtime
#  Java_JAVAC_EXECUTABLE   = the full path to the Java compiler
#  Java_JAR_EXECUTABLE     = the full path to the Java archiver
#  Java_VERSION_STRING     = Version of the package found (java version), eg. 1.6.0_12
#  Java_VERSION_MAJOR      = The major version of the package found.
#  Java_VERSION_MINOR      = The minor version of the package found.
#  Java_VERSION_PATCH      = The patch version of the package found.
#  Java_VERSION_TWEAK      = The tweak version of the package found (after '_')
#  Java_VERSION            = This is set to: $major.$minor.$patch(.$tweak)
#

#=============================================================================
# Copyright 2002-2009 Kitware, Inc.
# Copyright 2009-2011 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distributed this file outside of CMake, substitute the full
#  License text for the above reference.)

# The HINTS option should only be used for values computed from the system.
set(_JAVA_HINTS
  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Development Kit\\2.0;JavaHome]/bin"
  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Development Kit\\1.9;JavaHome]/bin"
  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Development Kit\\1.8;JavaHome]/bin"
  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Development Kit\\1.7;JavaHome]/bin"
  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Development Kit\\1.6;JavaHome]/bin"
  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Development Kit\\1.5;JavaHome]/bin"
  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Development Kit\\1.4;JavaHome]/bin"
  "[HKEY_LOCAL_MACHINE\\SOFTWARE\\JavaSoft\\Java Development Kit\\1.3;JavaHome]/bin"
  $ENV{JAVA_HOME}/bin
  )
# Hard-coded guesses should still go in PATHS. This ensures that the user
# environment can always override hard guesses.
set(_JAVA_PATHS
  /usr/lib/java/bin
  /usr/share/java/bin
  /usr/local/java/bin
  /usr/local/java/share/bin
  /usr/java/j2sdk1.4.2_04
  /usr/lib/j2sdk1.4-sun/bin
  /usr/java/j2sdk1.4.2_09/bin
  /usr/lib/j2sdk1.5-sun/bin
  /opt/sun-jdk-1.5.0.04/bin
  )
find_program(Java_JAVA_EXECUTABLE
  NAMES java
  HINTS ${_JAVA_HINTS}
  PATHS ${_JAVA_PATHS}
)

if(Java_JAVA_EXECUTABLE)
    set(_java_version_acceptable TRUE)
    execute_process(COMMAND ${Java_JAVA_EXECUTABLE} -version
      RESULT_VARIABLE res
      OUTPUT_VARIABLE var
      ERROR_VARIABLE var # sun-java output to stderr
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_STRIP_TRAILING_WHITESPACE)
    if( res )
      message( FATAL_ERROR "Error executing java -version" )
    else()
      # extract major/minor version and patch level from "java -version" output
      # Tested on linux using
      # 1. Sun / Sun OEM
      # 2. OpenJDK 1.6
      # 3. GCJ 1.5
      # 4. Kaffe 1.4.2
      if(var MATCHES "java version \"[0-9]+\\.[0-9]+\\.[0-9_]+[oem-]*\".*")
        # This is most likely Sun / OpenJDK, or maybe GCJ-java compat layer
        string( REGEX REPLACE ".* version \"([0-9]+\\.[0-9]+\\.[0-9_]+)[oem-]*\".*"
                "\\1" Java_VERSION_STRING "${var}" )
      elseif(var MATCHES "java full version \"kaffe-[0-9]+\\.[0-9]+\\.[0-9_]+\".*")
        # Kaffe style
        string( REGEX REPLACE "java full version \"kaffe-([0-9]+\\.[0-9]+\\.[0-9_]+).*"
                "\\1" Java_VERSION_STRING "${var}" )
      else()
        if(NOT Java_FIND_QUIETLY)
          message(WARNING "regex not supported: ${var}. Please report")
          set(_java_version_acceptable FALSE)
        endif()
      endif()
      string( REGEX REPLACE "([0-9]+).*" "\\1" Java_VERSION_MAJOR "${Java_VERSION_STRING}" )
      string( REGEX REPLACE "[0-9]+\\.([0-9]+).*" "\\1" Java_VERSION_MINOR "${Java_VERSION_STRING}" )
      string( REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" Java_VERSION_PATCH "${Java_VERSION_STRING}" )
      # warning tweak version can be empty:
      string( REGEX REPLACE "[0-9]+\\.[0-9]+\\.[0-9]+\\_?([0-9]*)$" "\\1" Java_VERSION_TWEAK "${Java_VERSION_STRING}" )
      if( Java_VERSION_TWEAK STREQUAL "" ) # check case where tweak is not defined
        set(Java_VERSION ${Java_VERSION_MAJOR}.${Java_VERSION_MINOR}.${Java_VERSION_PATCH})
      else()
        set(Java_VERSION ${Java_VERSION_MAJOR}.${Java_VERSION_MINOR}.${Java_VERSION_PATCH}.${Java_VERSION_TWEAK})
      endif()
      # display info
      #message( STATUS "Java version ${Java_VERSION_STRING} configured successfully!" ) # keep me, used for debug
      if(NOT Java_FIND_QUIETLY)
        message( STATUS "Java version ${Java_VERSION} configured successfully!" )
      endif()
    endif()

    # check version if requested:
    if( Java_FIND_VERSION )
      if("${Java_VERSION}" VERSION_LESS "${Java_FIND_VERSION}")
        set(_java_version_acceptable FALSE)
      endif()
      if( Java_FIND_VERSION_EXACT )
        if("${Java_VERSION}" VERSION_GREATER "${Java_FIND_VERSION}")
          set(_java_version_acceptable FALSE)
        endif()
      endif()
    endif()
endif()

get_filename_component(Java_JAVA_PATH ${Java_JAVA_EXECUTABLE} PATH)

# Prefer same path as java
find_program(Java_JAR_EXECUTABLE NAMES jar PATHS ${Java_JAVA_PATH} NO_DEFAULT_PATH)
find_program(Java_JAR_EXECUTABLE
  NAMES jar
  HINTS ${_JAVA_HINTS}
  PATHS ${_JAVA_PATHS}
)

find_program(Java_JAVAC_EXECUTABLE NAMES javac PATHS ${Java_JAVA_PATH} NO_DEFAULT_PATH)
find_program(Java_JAVAC_EXECUTABLE
  NAMES javac
  HINTS ${_JAVA_HINTS}
  PATHS ${_JAVA_PATHS}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Java DEFAULT_MSG
  Java_JAVA_EXECUTABLE
  Java_JAR_EXECUTABLE
  Java_JAVAC_EXECUTABLE
  _java_version_acceptable
)

mark_as_advanced(
  Java_JAVA_EXECUTABLE
  Java_JAR_EXECUTABLE
  Java_JAVAC_EXECUTABLE
  )
