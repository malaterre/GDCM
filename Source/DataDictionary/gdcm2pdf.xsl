<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:java="http://xml.apache.org/xslt/java" version="1.1" exclude-result-prefixes="java">
  <xsl:output method="pdf"/>
<!-- fop -xml GDCM2.xml -xsl gdcm2pdf.xsl GDCM2.pdf -->
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
    <fo:root xmlns:fo="http://www.w3.org/1999/XSL/Format" xmlns:fox="http://xml.apache.org/fop/extensions">
      <fo:layout-master-set>
        <fo:simple-page-master master-name="A4-L" page-height="297mm" page-width="210mm" margin-top="10mm" margin-bottom="10mm" margin-left="10mm" margin-right="10mm">
          <fo:region-body margin="10mm"/>
          <fo:region-before extent="20mm"/>
          <fo:region-after extent="10mm"/>
          <fo:region-start extent="10mm"/>
          <fo:region-end extent="10mm"/>
        </fo:simple-page-master>
      </fo:layout-master-set>
      <fo:page-sequence master-reference="A4-L">
        <fo:flow flow-name="xsl-region-body">
          <fo:block>
            <fo:table table-layout="fixed" border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
              <fo:table-column column-width="20mm"/>
              <fo:table-column column-width="20mm"/>
              <fo:table-column column-width="10mm"/>
              <fo:table-column column-width="10mm"/>
              <fo:table-column column-width="90mm"/>
              <fo:table-column column-width="15mm"/>
              <fo:table-header background-color="rgb(214,214,214)" font-size="8pt" font-weight="bold" text-align="center">
                <fo:table-row text-align="center" font-size="8pt">
                  <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                    <fo:block>Group</fo:block>
                  </fo:table-cell>
                  <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                    <fo:block>Element</fo:block>
                  </fo:table-cell>
                  <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                    <fo:block>VR</fo:block>
                  </fo:table-cell>
                  <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                    <fo:block>VM</fo:block>
                  </fo:table-cell>
                  <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                    <fo:block>Description</fo:block>
                  </fo:table-cell>
                  <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                    <fo:block>Retired</fo:block>
                  </fo:table-cell>
                </fo:table-row>
              </fo:table-header>
              <fo:table-body>
                <xsl:for-each select="dict/entry">
                  <fo:table-row text-align="center" font-size="8pt">
                    <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                      <fo:block vertical-align="middle">
                        <xsl:value-of select="@group"/>
                      </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                      <fo:block vertical-align="middle">
                        <xsl:value-of select="@element"/>
                      </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                      <fo:block vertical-align="middle">
                        <xsl:for-each select="representations/representation">
                          <xsl:value-of select="@vr"/>
                          <xsl:if test="position() != last()">
                            <!--xsl:text>&#xa;</xsl:text-->
                            <fo:block><xsl:text>&#xA;</xsl:text></fo:block>
                          </xsl:if>
                        </xsl:for-each>
                      </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                      <fo:block vertical-align="middle">
                        <xsl:for-each select="representations/representation">
                          <xsl:value-of select="@vm"/>
                          <xsl:if test="position() != last()">
                            <!--xsl:text>&#xa;</xsl:text-->
                            <fo:block><xsl:text>&#xA;</xsl:text></fo:block>
                          </xsl:if>
                        </xsl:for-each>
                      </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                      <fo:block vertical-align="middle">
                        <xsl:value-of select="description"/>
                      </fo:block>
                    </fo:table-cell>
                    <fo:table-cell border-color="rgb(0,0,0)" border-style="solid" border-width="1pt">
                      <fo:block vertical-align="middle">
                        <xsl:if test="@retired != &quot;false&quot;">
                          <xsl:text> (RET)</xsl:text>
                        </xsl:if>
                      </fo:block>
                    </fo:table-cell>
                  </fo:table-row>
                </xsl:for-each>
              </fo:table-body>
            </fo:table>
          </fo:block>
        </fo:flow>
      </fo:page-sequence>
    </fo:root>
  </xsl:template>
</xsl:stylesheet>
