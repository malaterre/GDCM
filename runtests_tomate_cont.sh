#!/bin/sh

cd $HOME/Dashboards/GDCMScripts && git pull

#PATH=$PATH:/local/mmalater/install/bin

ctest -S tomate-gdcm-gcc-64-makefiles-cont.cmake -V -O tomate-gdcm-gcc-64-makefiles-cont.log

