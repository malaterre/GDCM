#!/bin/sh

# grab me at:
# wget "http://sourceforge.net/p/gdcm/gdcm/ci/190055fe66c74cdbc6a7a3ea03735906df49ee6b/tree/setupgdcm.sh?format=raw" -O setupgdcm.sh

# sudo apt-get install git
# sudo apt-get install cmake

# Setup the GDCM scripts:
mkdir -p ~/Dashboards/GDCMScripts
cd ~/Dashboards/GDCMScripts
git init
git remote add -t dashboard origin git://git.code.sf.net/p/gdcm/gdcm
git pull origin

ctest -S generic_linux.cmake -V
