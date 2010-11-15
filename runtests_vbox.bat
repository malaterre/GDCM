@rem Update ourselves
cd %HOME%/Dashboards/GDCMScripts && git pull

ctest -S vbox-vtk-vs10-debug.cmake -V -O vbox-vtk-vs10-debug.log
ctest -S vbox-gdcm-vs10-debug.cmake -V -O vbox-gdcm-vs10-debug.log
