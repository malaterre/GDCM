#!/bin/sh

cd $HOME/Dashboards/GDCMScripts && git pull

ctest -S tomate-gcc-64-makefiles.cmake -V -O tomate-gcc-64-makefiles.log

