<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
		xmlns:ns="http://www.w3.org/1999/xhtml">
  <xsl:output method="xml" indent="yes" />
  <xsl:variable name="box" select="//a"/> 
  <xsl:template match="/">
    <Result type="url">
      <Urls>
	<xsl:for-each select="$box">
	  <Url>
	    <xsl:attribute name="name">
	      <xsl:value-of select="text()"/>
	    </xsl:attribute>
	    <xsl:attribute name="url">
	      <xsl:value-of select="./@href"/>
	    </xsl:attribute>
	  </Url>
	</xsl:for-each>
      </Urls>
    </Result>
  </xsl:template>
</xsl:stylesheet>
