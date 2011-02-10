# Client maintainer: setupgdcm.sh
#
# TODO: use cmake --system-information
cmake_minimum_required(VERSION 2.4)

set(parallel 0)
if(EXISTS "/proc/cpuinfo")
  file(STRINGS "/proc/cpuinfo" CPUINFO)
  foreach(line ${CPUINFO})
    if("${line}" MATCHES processor)
      math(EXPR parallel "${parallel} + 1")
    endif()
  endforeach(line)
else()
  set(parallel 1)
endif()
message("parallel: ${parallel}")

#exec_program(${CMAKE_COMMAND} ARGS --system-information
#OUTPUT_VARIABLE cmake_system_information)
##execute_process(${CMAKE_COMMAND} --system-information)
##OUTPUT_VARIABLE cmake_system_information
##  ERROR_VARIABLE error_cmake_system_information)
#string(REGEX REPLACE "^CMAKE_SYSTEM_NAME ([A-Za-z])$" "\\1" hostname2 "${cmake_system_information}")
#message("HOSTNAME2: ${hostname2}")

find_program(HOSTNAME NAMES hostname)
find_program(UNAME NAMES uname)

# Get the build name and hostname
exec_program(${HOSTNAME} ARGS OUTPUT_VARIABLE hostname)
string(REGEX REPLACE "[/\\\\+<> #]" "-" hostname "${hostname}")
message("HOSTNAME: ${hostname}")

macro(getuname name flag)
  exec_program("${UNAME}" ARGS "${flag}" OUTPUT_VARIABLE "${name}")
  string(REGEX REPLACE "[/\\\\+<> #()]" "-" "${name}" "${${name}}")
  string(REGEX REPLACE "^(......|.....|....|...|..|.).*" "\\1" "${name}" "${${name}}")
endmacro(getuname)

getuname(osname -s)
getuname(osver  -v)
getuname(osrel  -r)
getuname(cpu    -m)
if("${osname}" MATCHES Darwin)
  find_program(SW_VER sw_vers)
  execute_process(COMMAND "${SW_VER}" -productVersion OUTPUT_VARIABLE osver)
  string(REPLACE "\n" "" osver "${osver}")
  set(osname "MacOSX")
  set(osrel "")
  if("${cpu}" MATCHES "Power")
    set(cpu "ppc")
  endif("${cpu}" MATCHES "Power")
endif("${osname}" MATCHES Darwin)

set(BUILDNAME "${osname}${osver}${osrel}${cpu}-${compiler}")
message("BUILDNAME: ${BUILDNAME}")
message("COMPILER: ${CMAKE_CXX_COMPILER}")

set(CTEST_SITE "${hostname}")
set(CTEST_BUILD_NAME "${BUILDNAME}")
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")
# MM: prefer no space in path:
set(dashboard_root_name "MyTests")
SET(CTEST_BUILD_FLAGS "-j${parallel}")
message("CTEST_BUILD_FLAGS: ${CTEST_BUILD_FLAGS}")
set(CTEST_BUILD_CONFIGURATION Debug)

macro(dashboard_hook_init)
  set( dashboard_cache "
    GDCM_BUILD_SHARED_LIBS:BOOL=ON
    GDCM_BUILD_TESTING:BOOL=ON
    GDCM_BUILD_APPLICATIONS:BOOL=ON
    GDCM_BUILD_EXAMPLES:BOOL=ON
    GDCM_USE_VTK:BOOL=OFF
    GDCM_WRAP_PYTHON:BOOL=OFF
    GDCM_WRAP_CSHARP:BOOL=OFF
    GDCM_WRAP_JAVA:BOOL=OFF
    GDCM_USE_SYSTEM_OPENSSL:BOOL=OFF
    "
    )
endmacro(dashboard_hook_init)

include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
