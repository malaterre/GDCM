#!/bin/sh

cd $HOME/Dashboards/GDCMScripts && git pull

ctest -S minimacg4-gdcm-gcc-64-makefiles-cont.cmake -V -O minimacg4-gdcm-gcc-64-makefiles-cont.log
