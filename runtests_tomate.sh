#!/bin/sh

cd $HOME/Dashboards/GDCMScripts && git pull

PATH=$HOME/Software/cmake-2.8.2-Linux-i386/bin:$PATH

ctest -S tomate-itk-gcc-64-makefiles.cmake -V -O tomate-itk-gcc-64-makefiles.log
ctest -S tomate-vtk-gcc-64-makefiles.cmake -V -O tomate-vtk-gcc-64-makefiles.log
ctest -S tomate-gcc-64-makefiles.cmake -V -O tomate-gcc-64-makefiles.log

