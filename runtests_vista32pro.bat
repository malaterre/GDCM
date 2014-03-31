@rem Update ourselves
cd c:/Dashboards/GDCMScripts && git pull

@rem ctest -S vbox-vtk-vs10-debug.cmake -V -O vbox-vtk-vs10-debug.log
ctest -S vbox-gdcm-vs10-debug.cmake -V -O vbox-gdcm-vs10-debug.log
