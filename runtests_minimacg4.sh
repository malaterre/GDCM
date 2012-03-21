#!/bin/sh

cd $HOME/Dashboards/GDCMScripts && git pull

ctest -S minimacg4-gdcm-gcc-64-makefiles-release.cmake -V -O minimacg4-gdcm-gcc-64-makefiles-release.log
ctest -S minimacg4-gcc-64-makefiles.cmake -V -O minimacg4-gcc-64-makefiles.log
ctest -S minimacg4-gdcm-gcc-64-cov.cmake -V -O minimacg4-gdcm-gcc-64-cov.log
