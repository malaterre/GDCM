git pull
@rem update git
git pull

ctest -S silverstreak-vtk-vs9-release-64.cmake
ctest -S silverstreak_gdcm_Nightly_VS9_Release_64.cmake
ctest -S silverstreak_gdcm_Nightly_VS9_Release.cmake
ctest -S silverstreak_gdcm_Nightly_VS9_Debug_64.cmake
ctest -S silverstreak_gdcm_Nightly_VS9_Debug.cmake
