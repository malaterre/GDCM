@rem Update ourselves
cd %HOME%/Dashboards/GDCMScripts && git pull

@rem ctest -S vbox-vtk-gcc-64-makefiles.cmake -V -O vbox-vtk-gcc-64-makefiles.log
ctest -S vbox-gcc-64-makefiles.cmake -V -O vbox-gdcm-vs2010-debug.log
