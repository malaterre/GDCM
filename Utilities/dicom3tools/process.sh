#!/bin/sh

############################################################################
#
#  Program: GDCM (Grassroots DICOM). A DICOM library
#
#  Copyright (c) 2006-2011 Mathieu Malaterre
#  All rights reserved.
#  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.
#
#     This software is distributed WITHOUT ANY WARRANTY; without even
#     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#     PURPOSE.  See the above copyright notice for more information.
#
############################################################################

# This script convert dicom3tools internal txt format into XML for GDCM

# Usage:
# $ process.sh agfa.tpl

# remove empty lines
sed '/^$/d' $1 > /tmp/clean.tpl
# convert to xml
sed 's/^.*$/<d3t tag="&\/>/' /tmp/clean.tpl > /tmp/dummy.xml
# make sure to close quotes
sed -i -e 's@) V@)" V@' /tmp/dummy.xml
#
sed -i -e 's/&/\&amp;/g' /tmp/dummy.xml
# add start of xml
sed -i -e '1i <d3ts>' /tmp/dummy.xml
# add end:
echo '</d3ts>' >> /tmp/dummy.xml
# format and check if valid xml
xmllint --format /tmp/dummy.xml -o `basename $1 tpl`xml
