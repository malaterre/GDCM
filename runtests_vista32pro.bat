@rem Update ourselves
cd C:/Dashboards/GDCMScripts && git pull

@rem Use Visual Studio 2010:
call "%VS100COMNTOOLS%vsvars32.bat"

@rem ctest -S vbox-vtk-vs10-debug.cmake -V -O vbox-vtk-vs10-debug.log
ctest -S vbox-gdcm-vs10-debug.cmake -V -O vbox-gdcm-vs10-debug.log
