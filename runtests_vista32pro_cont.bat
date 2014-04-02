@rem Update ourselves
cd C:/Dashboards/GDCMScripts && git pull

@rem Use Visual Studio 2010:
call "%VS100COMNTOOLS%vsvars32.bat"

ctest -S vbox-gdcm-vs10-debug-cont.cmake -V -O vbox-gdcm-vs10-debug-cont.log
