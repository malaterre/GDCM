CMAKE_MINIMUM_REQUIRED(VERSION 2.2)
###################################################################
# The values in this section must always be provided
###################################################################

FIND_PROGRAM(HOSTNAME NAMES hostname)
FIND_PROGRAM(UNAME NAMES uname)

# Get the build name and hostname
EXEC_PROGRAM(${HOSTNAME} ARGS OUTPUT_VARIABLE hostname)
STRING(REGEX REPLACE "[/\\\\+<> #]" "-" hostname "${hostname}")

MESSAGE("HOSTNAME: ${hostname}")
SET(MAKE make)
SET(MAKEOPTS )
SET (CTEST_UPDATE_COMMAND      "/mnt/kitware/bin-${hostname}/cvs")
IF(EXISTS /opt/OpenSource/xcdroast-0.98/opt/make/bin/gmake)
  SET(MAKE "/opt/OpenSource/xcdroast-0.98/opt/make/bin/gmake")
  SET(MAKEOPTS "-j 2")
ENDIF(EXISTS /opt/OpenSource/xcdroast-0.98/opt/make/bin/gmake)
IF(EXISTS /etc/debian_version)
  SET(MAKE "/usr/bin/make")
  SET(MAKEOPTS "-j 2")
ENDIF(EXISTS /etc/debian_version)

SET(c_compiler "cc")
IF($ENV{CXX})
  MESSAGE("ENV: $ENV{CXX}")
  SET(mycxx "$ENV{CXX}")
ELSE($ENV{CXX})
  IF("${hostname}" MATCHES "boston")
    SET(mycxx "g++")
  ENDIF("${hostname}" MATCHES "boston")
  IF("${hostname}" MATCHES "styx")
    SET(mycxx "g++")
  ENDIF("${hostname}" MATCHES "styx")
ENDIF($ENV{CXX})

IF(mycxx)
  SET(compiler "${mycxx}")
  SET(full_compiler "${mycxx}")
ELSE(mycxx)
  SET(compiler aCC)
  SET(full_compiler "/opt/aCC/bin/aCC")
ENDIF(mycxx)
MACRO(getuname name flag)
  EXEC_PROGRAM("${UNAME}" ARGS "${flag}" OUTPUT_VARIABLE "${name}")
  STRING(REGEX REPLACE "[/\\\\+<> #]" "-" "${name}" "${${name}}")
  STRING(REGEX REPLACE "^(......|.....|....|...|..|.).*" "\\1" "${name}" "${${name}}")
ENDMACRO(getuname)

getuname(osname -s)
getuname(osver  -v)
getuname(osrel  -r)
getuname(cpu    -m)

SET(BUILDNAME "${osname}${osver}${osrel}${cpu}-${compiler}")
SET(SHORT_BUILDNAME "${osname}${cpu}-${compiler}")
MESSAGE("BUILDNAME: ${BUILDNAME}")

# this is the cvs module name that should be checked out
SET (CTEST_MODULE_NAME VTK)

# Settings:
SET(CTEST_DASHBOARD_ROOT    "/tmp")
SET(CTEST_SITE              "${hostname}")
SET(CTEST_BUILD_NAME        "${SHORT_BUILDNAME}")
SET(CTEST_TIMEOUT           "1500")

# CVS command and the checkout command
IF(NOT EXISTS "${CTEST_DASHBOARD_ROOT}/${CTEST_MODULE_NAME}")
  SET(CTEST_CHECKOUT_COMMAND     "\"${CTEST_UPDATE_COMMAND}\" -q -z3 -d:pserver:anoncvs@www.vtk.org:/cvsroot/VTK co -d ${CTEST_MODULE_NAME} -r VTK-5-2 ${CTEST_MODULE_NAME}")
ENDIF(NOT EXISTS "${CTEST_DASHBOARD_ROOT}/${CTEST_MODULE_NAME}")

# Set the generator and build configuration
SET(CTEST_CMAKE_GENERATOR      "Unix Makefiles")
SET(CTEST_BUILD_CONFIGURATION  "Release")

# Extra special variables
SET(ENV{DISPLAY}             "")
SET(ENV{CC}                  "${c_compiler}")
SET(ENV{CXX}                 "${full_compiler}")

#----------------------------------------------------------------------------------
# Should not need to edit under this line
#----------------------------------------------------------------------------------

# if you do not want to use the default location for a 
# dashboard then set this variable to the directory
# the dashboard should be in
#MAKE_DIRECTORY("${CTEST_DASHBOARD_ROOT}")
# these are the the name of the source and binary directory on disk. 
# They will be appended to DASHBOARD_ROOT
SET(CTEST_SOURCE_DIRECTORY  "${CTEST_DASHBOARD_ROOT}/${CTEST_MODULE_NAME}")
SET(CTEST_BINARY_DIRECTORY  "${CTEST_SOURCE_DIRECTORY}-${CTEST_BUILD_NAME}")
SET(CTEST_BUILD_COMMAND     "${MAKE}")
SET(CTEST_NOTES_FILES       "${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}")

##########################################################################
# wipe the binary dir
MESSAGE("Remove binary directory...")
CTEST_EMPTY_BINARY_DIRECTORY(${CTEST_BINARY_DIRECTORY})

MESSAGE("CTest Directory: ${CTEST_DASHBOARD_ROOT}")
MESSAGE("Initial checkout: ${CTEST_CVS_CHECKOUT}")
MESSAGE("Initial cmake: ${CTEST_CMAKE_COMMAND}")
MESSAGE("CTest command: ${CTEST_COMMAND}")

# this is the initial cache to use for the binary tree, be careful to escape
# any quotes inside of this string if you use it
FILE(WRITE "${CTEST_BINARY_DIRECTORY}/CMakeCache.txt" "
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

MESSAGE("Start dashboard...")
CTEST_START(Nightly)
MESSAGE("  Update")
CTEST_UPDATE(SOURCE "${CTEST_SOURCE_DIRECTORY}" RETURN_VALUE res)
MESSAGE("  Configure")
CTEST_CONFIGURE(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
CTEST_READ_CUSTOM_FILES( "${CTEST_BINARY_DIRECTORY}" )
MESSAGE("  Build")
CTEST_BUILD(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
#MESSAGE("  Test")
#CTEST_TEST(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
MESSAGE("  Submit")
CTEST_SUBMIT(RETURN_VALUE res)
MESSAGE("  All done")
