cmake_minimum_required(VERSION 2.2)
###################################################################
# The values in this section must always be provided
###################################################################

find_program(HOSTNAME NAMES hostname)
find_program(UNAME NAMES uname)

# Get the build name and hostname
exec_program(${HOSTNAME} ARGS OUTPUT_VARIABLE hostname)
string(REGEX REPLACE "[/\\\\+<> #]" "-" hostname "${hostname}")

message("HOSTNAME: ${hostname}")
set(MAKE make)
set(MAKEOPTS )
set (CTEST_UPDATE_COMMAND      "/mnt/kitware/bin-${hostname}/cvs")
if(EXISTS /opt/OpenSource/xcdroast-0.98/opt/make/bin/gmake)
  set(MAKE "/opt/OpenSource/xcdroast-0.98/opt/make/bin/gmake")
  set(MAKEOPTS "-j 2")
endif()
if(EXISTS /etc/debian_version)
  set(MAKE "/usr/bin/make")
  set(MAKEOPTS "-j 2")
endif()

set(c_compiler "cc")
if($ENV{CXX})
  message("ENV: $ENV{CXX}")
  set(mycxx "$ENV{CXX}")
else()
  if("${hostname}" MATCHES "boston")
    set(mycxx "g++")
  endif()
  if("${hostname}" MATCHES "styx")
    set(mycxx "g++")
  endif()
endif()

if(mycxx)
  set(compiler "${mycxx}")
  set(full_compiler "${mycxx}")
else()
  set(compiler aCC)
  set(full_compiler "/opt/aCC/bin/aCC")
endif()
macro(getuname name flag)
  exec_program("${UNAME}" ARGS "${flag}" OUTPUT_VARIABLE "${name}")
  string(REGEX REPLACE "[/\\\\+<> #]" "-" "${name}" "${${name}}")
  string(REGEX REPLACE "^(......|.....|....|...|..|.).*" "\\1" "${name}" "${${name}}")
endmacro()

getuname(osname -s)
getuname(osver  -v)
getuname(osrel  -r)
getuname(cpu    -m)

set(BUILDNAME "${osname}${osver}${osrel}${cpu}-${compiler}")
set(SHORT_BUILDNAME "${osname}${cpu}-${compiler}")
message("BUILDNAME: ${BUILDNAME}")

# this is the cvs module name that should be checked out
set (CTEST_MODULE_NAME VTK)

# Settings:
set(CTEST_DASHBOARD_ROOT    "/tmp")
set(CTEST_SITE              "${hostname}")
set(CTEST_BUILD_NAME        "${SHORT_BUILDNAME}")
set(CTEST_TIMEOUT           "1500")

# CVS command and the checkout command
if(NOT EXISTS "${CTEST_DASHBOARD_ROOT}/${CTEST_MODULE_NAME}")
  set(CTEST_CHECKOUT_COMMAND     "\"${CTEST_UPDATE_COMMAND}\" -q -z3 -d:pserver:anoncvs@www.vtk.org:/cvsroot/VTK co -d ${CTEST_MODULE_NAME} -r VTK-5-2 ${CTEST_MODULE_NAME}")
endif()

# Set the generator and build configuration
set(CTEST_CMAKE_GENERATOR      "Unix Makefiles")
set(CTEST_BUILD_CONFIGURATION  "Release")

# Extra special variables
set(ENV{DISPLAY}             "")
set(ENV{CC}                  "${c_compiler}")
set(ENV{CXX}                 "${full_compiler}")

#----------------------------------------------------------------------------------
# Should not need to edit under this line
#----------------------------------------------------------------------------------

# if you do not want to use the default location for a 
# dashboard then set this variable to the directory
# the dashboard should be in
#make_directory("${CTEST_DASHBOARD_ROOT}")
# these are the the name of the source and binary directory on disk. 
# They will be appended to DASHBOARD_ROOT
set(CTEST_SOURCE_DIRECTORY  "${CTEST_DASHBOARD_ROOT}/${CTEST_MODULE_NAME}")
set(CTEST_BINARY_DIRECTORY  "${CTEST_SOURCE_DIRECTORY}-${CTEST_BUILD_NAME}")
set(CTEST_BUILD_COMMAND     "${MAKE}")
set(CTEST_NOTES_FILES       "${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}")

##########################################################################
# wipe the binary dir
message("Remove binary directory...")
CTEST_EMPTY_BINARY_DIRECTORY(${CTEST_BINARY_DIRECTORY})

message("CTest Directory: ${CTEST_DASHBOARD_ROOT}")
message("Initial checkout: ${CTEST_CVS_CHECKOUT}")
message("Initial cmake: ${CTEST_CMAKE_COMMAND}")
message("CTest command: ${CTEST_COMMAND}")

# this is the initial cache to use for the binary tree, be careful to escape
# any quotes inside of this string if you use it
file(WRITE "${CTEST_BINARY_DIRECTORY}/CMakeCache.txt" "
SITE:STRING=${hostname}
BUILDNAME:STRING=${SHORT_BUILDNAME}
DART_ROOT:PATH=
CVSCOMMAND:FILEPATH=${CTEST_UPDATE_COMMAND}
//Command used to build entire project from the command line.
MAKECOMMAND:STRING=${MAKE} -i ${MAKEOPTS}
//make program
CMAKE_MAKE_PROGRAM:FILEPATH=${MAKE}
DROP_METHOD:STRING=http
BUILD_SHARED_LIBS:BOOL=OFF
VTK_USE_RENDERING:BOOL=ON
VTK_USE_PARALLEL:BOOL=OFF
")

message("Start dashboard...")
CTEST_START(Nightly)
message("  Update")
CTEST_UPDATE(SOURCE "${CTEST_SOURCE_DIRECTORY}" RETURN_VALUE res)
message("  Configure")
CTEST_CONFIGURE(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
CTEST_READ_CUSTOM_FILES( "${CTEST_BINARY_DIRECTORY}" )
message("  Build")
CTEST_BUILD(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
#message("  Test")
#CTEST_TEST(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
message("  Submit")
CTEST_SUBMIT(RETURN_VALUE res)
message("  All done")
