<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" indent="yes"/>
  <xsl:param name="docurl"/>
  <xsl:param name="urlid"/>
  <xsl:variable name="box" select="//a[@id='pageLink']"/> 
  <xsl:template match="/">
    <Result>
      <xsl:attribute name="url">
	<xsl:value-of select="$docurl"/>
      </xsl:attribute>
	<xsl:attribute name="uid">
	  <xsl:value-of select="$urlid"/>
	</xsl:attribute>
      <Columns>
	<xsl:for-each select="$box">
	  <Column>
	    <xsl:attribute name="name">
	      <xsl:for-each select=".|.//*">
                <xsl:choose>       
                  <xsl:when test="name() = 'SCRIPT' "> 
		    <xsl:text/>
		  </xsl:when> 
		  <xsl:otherwise> 
		    <xsl:value-of select="text()"/>
		  </xsl:otherwise> 
		</xsl:choose> 
	      </xsl:for-each>
	    </xsl:attribute>
	    <xsl:attribute name="url">
	      <xsl:value-of select="./@href"/>
	    </xsl:attribute>
	  </Column>
	</xsl:for-each>
      </Columns>
    </Result>
  </xsl:template>
</xsl:stylesheet>
