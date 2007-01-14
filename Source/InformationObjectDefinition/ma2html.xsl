<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html" indent="yes"/>
<!-- XSL to convert XML GDCM2 data dictionay into HTML form -->
<!--
  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006 Mathieu Malaterre
  Copyright (c) 1993-2005 CREATIS
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
-->
  <xsl:template match="/">
    <html>
      <body>
        <table border="1">
          <tr bgcolor="#d6d6d6"> <!--rgb(214,214,214) -->
            <th>Group</th>
            <th>Element</th>
            <th>Name</th>
            <th>Type</th>
            <th>Description</th>
          </tr>
<!-- The main template that loop over all dict/entry -->
          <xsl:for-each select="tables/table/entry">
            <tr>
              <td>
                <xsl:value-of select="@group"/>
              </td>
              <td>
                <xsl:value-of select="@element"/>
              </td>
              <td>
                <xsl:value-of select="@name"/>
              </td>
              <td>
                <xsl:value-of select="@type"/>
              </td>
              <td>
                <xsl:value-of select="@description"/>
              </td>
            </tr>
          </xsl:for-each>
        </table>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet>
