#!/bin/sh

cd $HOME/Dashboards/GDCMScripts && git pull

PATH=$HOME/Software/cmake-2.8.2-Linux-i386/bin:$PATH:/local/mmalater/install/bin

ctest -S tomate-gdcm-gcc-64-makefiles-cont.cmake -V -O tomate-gdcm-gcc-64-makefiles-cont.log

