<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
		xmlns:ns="http://www.w3.org/1999/xhtml">
  <xsl:output method="xml" indent="yes" />
  <xsl:variable name="title" select="//h1[@id='h1title']"/> 
  <xsl:variable name="content" select="//div[@id='endText']//p"/> 
  <xsl:template match="/">
    <Result type="content">
      <Title>
	<xsl:for-each select="$title">
	  <xsl:value-of select="text()"/>
	</xsl:for-each>
      </Title>
      <Content>
	<xsl:for-each select="$content">
	  <xsl:value-of select="text()"/>
	  <xsl:value-of select="string('&#10;')"/>
	</xsl:for-each>
      </Content>
    </Result>
  </xsl:template>
</xsl:stylesheet>
