@rem update git
git pull

ctest -S silverstreak-vtk-vs9-release-64.cmake          -V -O silverstreak-vtk-vs9-release-64.log
ctest -S silverstreak_gdcm_Nightly_VS9_Release_64.cmake -V -O silverstreak-gdcm-vs9-release-64.log
ctest -S silverstreak_gdcm_Nightly_VS9_Release.cmake    -V -O silverstreak-gdcm-vs9-release.log
ctest -S silverstreak_gdcm_Nightly_VS9_Debug_64.cmake   -V -O silverstreak-gdcm-vs9-debug-64.log
ctest -S silverstreak_gdcm_Nightly_VS9_Debug.cmake      -V -O silverstreak-gdcm-vs9-debug.log
