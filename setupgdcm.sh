#!/bin/sh

# sudo apt-get install git
# sudo apt-get install cmake

# Setup the GDCM scripts:
mkdir -p ~/Dashboards/GDCMScripts
cd ~/Dashboards/GDCMScripts
git init
git remote add -t dashboard origin git://gdcm.git.sourceforge.net/gitroot/gdcm/gdcm
git pull origin

ctest -S generic_linux.cmake -V
