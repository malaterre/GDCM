# Client maintainer: setupgdcm.sh
cmake_minimum_required(VERSION 2.4)

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

set(CTEST_SITE "${hostname}")
set(CTEST_BUILD_NAME "${BUILDNAME}")
set(CTEST_CMAKE_GENERATOR "Unix Makefiles")

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
