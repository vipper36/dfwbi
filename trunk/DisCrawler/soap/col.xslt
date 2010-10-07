<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" indent="yes"/> 
  <xsl:param name="docurl"/>
  <xsl:param name="urlid"/>
  <xsl:variable name="box" select="/html/body/table/tbody/tr/td/table[@align=&quot;center&quot;]/tbody/tr/td[@valign=&quot;top&quot;]/table/tbody/tr/td/table[@class=&quot;ft12h&quot; and @align=&quot;left&quot;]/tbody"/> 
  <xsl:template match="/">
    <Result>
      <xsl:attribute name="url">
	<xsl:value-of select="$docurl"/>
      </xsl:attribute>
	<xsl:attribute name="uid">
	  <xsl:value-of select="$urlid"/>
	</xsl:attribute>
      <Column>
	<xsl:for-each select="$box">
	  <xsl:variable name="sub" select="tr/td[@align=&quot;left&quot;]/table/tbody/tr/td/a"/> 
	    <xsl:for-each select="$sub">
	      <SubItem>
		<xsl:attribute name="url">
		  <xsl:value-of select="./@href"/>
		</xsl:attribute>
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
	      </SubItem>
	    </xsl:for-each>
	</xsl:for-each>
      </Column>
    </Result>
  </xsl:template>
</xsl:stylesheet>
