#!/bin/sh

# grab me at:
# wget "http://gdcm.git.sourceforge.net/git/gitweb.cgi?p=gdcm/gdcm;a=blob_plain;f=setupgdcm.sh;hb=8b66f6fa797a5979d43fcfdd0d3da634a861cd3a" -O setupgdcm.sh

# sudo apt-get install git
# sudo apt-get install cmake

# Setup the GDCM scripts:
mkdir -p ~/Dashboards/GDCMScripts
cd ~/Dashboards/GDCMScripts
git init
git remote add -t dashboard origin git://gdcm.git.sourceforge.net/gitroot/gdcm/gdcm
git pull origin

ctest -S generic_linux.cmake -V
