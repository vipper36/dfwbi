<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="xml" indent="yes"/>
  <xsl:param name="docurl"/>
  <xsl:param name="urlid"/>
  <xsl:variable name="box" select="/html/body"/> 
  <xsl:template match="/">
    <Result>
      <xsl:attribute name="url">
	<xsl:value-of select="$docurl"/>
      </xsl:attribute>
	<xsl:attribute name="uid">
	  <xsl:value-of select="$urlid"/>
	</xsl:attribute>
      <Content>
	<xsl:for-each select="$box">
          <xsl:variable name="author" select="string('')"/> 
          <xsl:variable name="source" select="string('')"/>
          <xsl:variable name="attr" select="string('')"/>       
	  <xsl:variable name="title" select="/html/body/div[@class=&quot;content&quot;]/div[@class=&quot;right_c&quot;]/div[@class=&quot;list_t&quot;]/div[@class=&quot;text_c&quot;]/h1"/> 
	  <xsl:variable name="publishdate" select="/html/body/div[@class=&quot;content&quot;]/div[@class=&quot;right_c&quot;]/div[@class=&quot;list_t&quot;]/div[@class=&quot;text_c&quot;]/div[@class=&quot;lai&quot;]"/> 
	  <xsl:variable name="content" select="/html/body/div[@class=&quot;content&quot;]/div[@class=&quot;right_c&quot;]/div[@class=&quot;list_t&quot;]/div[@class=&quot;text_c&quot;]/h1 | /html/body/div[@class=&quot;content&quot;]/div[@class=&quot;right_c&quot;]/div[@class=&quot;list_t&quot;]/div[@class=&quot;text_c&quot;]/div[@class=&quot;c_c&quot;]/div[@id=&quot;ozoom&quot;]/founder-content/p | /html/body/div[@class=&quot;content&quot;]/div[@class=&quot;right_c&quot;]/div[@id=&quot;articlecontent&quot;]/founder-content/p"/> 
	    <ContAtts>
	      <Att name="#DRETITLE ">
                <xsl:if test="string-length($title)&gt;0">
		<xsl:value-of select="$title"/>
                </xsl:if>
	      </Att>
	      <Att name="#DREFIELD PUBLISHDATE=">
		<xsl:value-of select="$publishdate"/>
	      </Att>
              <Att name="#DREFIELD AUTHOR=">
                <xsl:if test="string-length($author)&gt;0">
		<xsl:value-of select="$author"/>
                </xsl:if>
	      </Att>
              <Att name="#DREFIELD SOURCE=">
                <xsl:if test="string-length($source)&gt;0">
		<xsl:value-of select="$source"/>
                </xsl:if>
	      </Att>
              <Att name="#DREFIELD ATTR=">
                <xsl:if test="string-length($attr)&gt;0">
		<xsl:value-of select="$attr"/>
                </xsl:if>
	      </Att>
              <Att name="#DREDBNAME ">
		<xsl:value-of select="string('NEWS')"/>
	      </Att>
	    </ContAtts>  
	    <Content>
	       <xsl:for-each select="$content">
		 <xsl:choose>       
                   <xsl:when test="name() = 'SCRIPT' "> 
		     <xsl:text/>
		   </xsl:when> 
		   <xsl:otherwise> 
		     <xsl:value-of select="text()"/>
		   </xsl:otherwise> 
		 </xsl:choose> 
	       </xsl:for-each>
	    </Content>
	</xsl:for-each>
      </Content>
    </Result>
  </xsl:template>
</xsl:stylesheet>
