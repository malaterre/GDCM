@rem go the GDCMScripts dir:
@rem cd h:\src\dashboard\gdcmscripts

@rem update git
@rem git pull

echo %date% %time% Starting GDCM >> runtests_silverstreak.log

"c:\program files (x86)\cmake 2.8\bin\ctest" -S silverstreak-vtk-vs9-release-64.cmake          -V -O silverstreak-vtk-vs9-release-64.log
"c:\program files (x86)\cmake 2.8\bin\ctest" -S silverstreak_gdcm_Nightly_VS9_Release_64.cmake -V -O silverstreak-gdcm-vs9-release-64.log
"c:\program files (x86)\cmake 2.8\bin\ctest" -S silverstreak_gdcm_Nightly_VS9_Release.cmake    -V -O silverstreak-gdcm-vs9-release.log
"c:\program files (x86)\cmake 2.8\bin\ctest" -S silverstreak_gdcm_Nightly_VS9_Debug_64.cmake   -V -O silverstreak-gdcm-vs9-debug-64.log
"c:\program files (x86)\cmake 2.8\bin\ctest" -S silverstreak_gdcm_Nightly_VS9_Debug.cmake      -V -O silverstreak-gdcm-vs9-debug.log

echo %date% %time% Finish GDCM >> runtests_silverstreak.log
