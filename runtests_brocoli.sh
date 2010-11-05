#!/bin/sh

cd $HOME/Dashboards/GDCMScripts && git pull

PATH=$HOME/Software/cmake-2.8.2-Linux-i386/bin:$PATH

ctest -S brocoli-gcc-64-makefiles.cmake -V -O brocoli-gcc-64-makefiles.log

