<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html" indent="yes"/>
<!-- XSL to convert XML GDCM2 data dictionay into HTML form -->
<!--
  Program: GDCM (Grass Root DICOM). A DICOM library
  Module:  $URL$

  Copyright (c) 2006-2007 Mathieu Malaterre
  All rights reserved.
  See Copyright.txt or http://gdcm.sourceforge.net/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
-->

  <!-- an Entry line -->
  <xsl:template match="entry">
    <tr>
<!-- TODO which one is expected ? -->
<!-- Version 1 -->
<!--xsl:text>(</xsl:text>
                <xsl:value-of select="@group"/>
                <xsl:text>,</xsl:text>
                <xsl:value-of select="@element"/>
                <xsl:text>)</xsl:text-->
<!-- Version 2 -->
      <td>(<xsl:value-of select="@group"/>,<xsl:value-of select="@element"/>)</td>
      <td>
        <xsl:value-of select="@name"/>
      </td>
      <td>
        <xsl:value-of select="@type"/>
      </td>
      <td>
        <xsl:value-of select="description"/>
      </td>
    </tr>
  </xsl:template>


  <!-- an Include line -->
  <xsl:template match="include">
    <tr>
      <td colspan="4">
        <xsl:value-of select="@ref"/>
      </td>
    </tr>
  </xsl:template>


  <xsl:template match="/">
    <html>
      <body>
<!-- The main template that loop over all dict/entry -->
        <xsl:for-each select="tables/table">
          <table border="1">
            <caption>
              <em>
                <xsl:value-of select="@name"/>
                <br/>
                <xsl:value-of select="@ref"/>
              </em>
            </caption>
            <tr bgcolor="#d6d6d6">
<!--rgb(214,214,214) -->
              <th>Tag</th>
              <th>Name</th>
              <th>Type</th>
              <th>Description</th>
            </tr>
            <xsl:apply-templates/>
          </table>
        </xsl:for-each>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet>
