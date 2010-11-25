# Client maintainer: inglis.dl gmail . com

set(CTEST_SITE "hyoid")
set(CTEST_BUILD_NAME "Win32-windowsVista-vs2005Express-Release")
set(CTEST_BUILD_CONFIGURATION Release)
set(CTEST_CMAKE_GENERATOR "NMake Makefiles")
set(CTEST_DASHBOARD_ROOT "D:/Developer/Dashboards/Tests")
set(dashboard_binary_name "gdcm-build-release-experimental")
set(dashboard_model Experimental)
set(dashboard_root_name "D:/Developer/Dashboards/Tests")
set(dashboard_cache "
BUILD_TESTING:BOOL=ON
GDCM_BUILD_TESTING:BOOL=ON
CMAKE_BUILD_TYPE:STRING=Release
GDCM_BUILD_SHARED_LIBS:BOOL=OFF
GDCM_BUILD_APPLICATIONS:BOOL=ON
GDCM_BUILD_EXAMPLES:BOOL=ON
CMAKE_CXX_FLAGS:STRING= /DWIN32 /D_WINDOWS /W3 /wd4101 /Zm1000 /EHsc /GR
CMAKE_C_FLAGS:STRING= /DWIN32 /D_WINDOWS /W3 /wd4101 /Zm1000
GDCM_USE_VTK:BOOL=ON
TCL_LIBRARY:FILEPATH=D:/Developer/Releases/VS/STATIC/Tcl/lib/tcl85tsx.lib
TK_LIBRARY:FILEPATH=D:/Developer/Releases/VS/STATIC/Tcl/lib/tk85tsx.lib
VTK_DIR:PATH=D:/Developer/Releases/VS/STATIC/Install/lib/vtk-5.7
")

SET(CTEST_GIT_COMMAND "C:/cygwin/bin/git.exe")

SET (CTEST_ENVIRONMENT
  "INCLUDE=C:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE\;C:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE\;C:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include\;C:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include\;"
  "LIB=C:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/LIB\;C:/Program Files/Microsoft Visual Studio 8/VC/LIB\;C:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/lib\;C:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/lib\;"
  "DevEnvDir=C:/Program Files/Microsoft Visual Studio 8/Common7/IDE"
  "FrameworkDir=C:/Windows/Microsoft.NET/Framework"
  "FrameworkSDKDir=C:/Program Files/Microsoft Visual Studio 8/SDK/v2.0"
  "FrameworkVersion=v2.0.50727"
  "MSVCDir=C:/Program Files/Microsoft Visual Studio .NET/VC7"
  "PATH=C:/Program Files/Microsoft Visual Studio 8/Common7/IDE\;C:/Program Files/Microsoft Visual Studio 8/VC/BIN\;C:/Program Files/Microsoft Visual Studio 8/Common7/Tools\;C:/Program Files/Microsoft Visual Studio 8/Common7/Tools/bin\;C:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/bin\;C:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/bin\;C:/Windows/Microsoft.NET/Framework/v2.0.50727\;C:/Program Files/Microsoft Visual Studio 8/VC/VCPackages\;C:/Perl/site/bin\;C:/Perl/bin\;C:/Windows/system32\;C:/Windows\;C:/Windows/System32/Wbem\;C:/Program Files/CMake 2.6/bin"
  "VCINSTALLDIR=C:/Program Files/Microsoft Visual Studio 8/VC"
  "VS80COMNTOOLS=C:/Program Files/Microsoft Visual Studio 8/Common7/Tools"
  "VSINSTALLDIR=C:/Program Files/Microsoft Visual Studio 8"
  )


include(${CTEST_SCRIPT_DIRECTORY}/gdcm_common.cmake)
