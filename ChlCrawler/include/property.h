#ifndef __PROPERTY_H__
#define __PROPERTY_H__
#include <string>
#include <iostream>

#define LINUX_SUSE          1
#define OS                  LINUX_SUSE

#define IDX_COM             nsCString("IdxCom")

#define MUST_HAVE_CSV       nsCString("MustHaveCSV")
#define DONT_MUST_HAVE_CSV  nsCString("DontMustHaveCSV")
#define STOP_TAG            nsCString("StopTag")
#define START_TAG           nsCString("StartTag")
#define ADVERTISE_NODE      nsCString("AdvertiseNode")
#define DATE_NODE           nsCString("DateNode")
#define AUTHOR_NODE         nsCString("AuthorNode")
#define SOURCE_NODE         nsCString("SourceNode")
#define TITLE_NODE          nsCString("TitleNode")

#define DOM_ANALYZER        nsCString("domanalyzer")
#define DATE_FORMAT         nsCString("dateformat")
#define STARTLAYER          nsCString("StartLayer")
#define ENDLAYER            nsCString("EndLayer")
#define INTERTIME           nsCString("InterTime")

#define URL_IO_COM          nsCString("UrlIOCom")
#define URL_SOURCE          nsCString("UrlSource")

#define CHL_FETCH_COM       nsCString("ChlFetchCom")
#define CHL_WRAP_COM        nsCString("ChlWrapCom")
#define CHL_IO_COM          nsCString("ChlIOCom")
#define CHL_SOURCE          nsCString("ChlSource")
#define CHL_TYPE            nsCString("ChlType")
#define CHL_NAMETYPE        nsCString("ChlNameType")
#define COL_REPLACE_TYPE    nsCString("ColReplaceType")
#define COL_REPLACE_FROM    nsCString("ColReplaceFrom")
#define COL_REPLACE_TO      nsCString("ColReplaceTo")
#define COL_EXP_NABOR       nsCString("expNabor")


#define COL_FETCH_COM       nsCString("ColFetchCom")
#define COL_IO_COM          nsCString("ColIOCom")
#define COL_SOURCE          nsCString("ColSource")
#define EXCEPT_REG          nsCString("ExceptREG")
#define INCLUDE_REG         nsCString("IncludeREG")
#define URL_EDIT_DIS        nsCString("UrlEditDis")
#define URL_CLASS_COUNT     nsCString("UrlClassCount")
#define COL_ALIAS_PATH      nsCString("ColAliasPath")
#define COL_PAGE_COM        nsCString("ColPageCom")
#define COL_PAGE_COUNT      nsCString("ColPageCount")

#define COL_BRIDGE_SOURCE   nsCString("ColBridgeSource")

#define URL_REPLACE_TYPE    nsCString("UrlReplaceType")
#define URL_REPLACE_FROM    nsCString("UrlReplaceFrom")
#define URL_REPLACE_TO      nsCString("UrlReplaceTo")

#define WRAP_MODE_CONTENT       nsCString("WrapModeContent")
#define WRAP_MODE_CONTENT_AD    2
#define WRAP_MODE_CONTENT_MN    1

#define INDEX_URL               nsCString("IndexURL")
#define MARK_SOURCEINFO         nsCString("SOURCEINFO")
#define MARK_COLUMNMAP          nsCString("COLUMNMAP")
#define MARK_SITEDOMAIN         nsCString("SITEDOMAIN")

#define LINK_STAT_NEW 0
#define LINK_STAT_GET 1
#define LINK_STAT_ANALYZED 2
#define LINK_STAT_ANALYZED_DOM 3
#define LINK_STAT_ERROR 9

#define CHL_TYPE_USR 0
#define CHL_TYPE_ABS 1
#define CHL_TYPE_REL 2
#define CHL_TYPE_DUL 3

/*-----------------------------------------------------------
		Page Analysis Macro Define
  -----------------------------------------------------------*/
#define WRAPPER_NAME nsCString("WrapperName")
#define LEVEL 3
#define LOG				if(LEVEL<=3) std::cout
#define DEBUG				if(LEVEL<=3) std::cout
#define INFO				if(LEVEL<=2) std::cout
#define ERROR				if(LEVEL<=1) std::cout

/*
   每个blocknode最大的权重
   */
#define BLOCK_MAX_WEIGHT		100

/*
   每个cluster最多有多少个blocklist对象
   */
#define BLOCK_NUMBER_IN_A_CLUSTER	10

/*
   如果blocks之间的相似度大于此值，则两个blocks是同一个类
   */
#define SIMILAR_THRESHOLD		0.97
#define WRAP_SIMILAR_THRESHOLD		0.9

/*
   如果同一个cluster中，各个blocklists之间相似度如果大于此值，则此cluster无效
   */
#define SIMILAR_CONTENT_THRESHOLD	0.6

/*
   如果一个cluster中的链接文字比大于此值，则此cluster为链接块
   */
#define LINK_BLOCK_THRESHOLD		0.7

/*
   如果一个cluster中的文字权重大于此值，则此cluster为内容块
   */
#define MIN_CONTENT_LENGTH		50

/*
   如果一个cluster中的，相同blocknodes之间相似度如果大于此值，则此blocknode为广告节点
   */
#define SIMILAR_NODE_THRESHOLD		SIMILAR_CONTENT_THRESHOLD

/*
   如果一个页面的content比例大于此值，则此页面为内容页
   */
#define CONTENT_PAGE_THRESHOLD		0.3

/*
   title length (unit:byte; encode:utf8)
   */
#define AVERAGE_TITLE_LENGTH		54

#define RULE_SEPARATOR			"->"
#define RULE_LINE_SEPARATOR		"\\n"
#define RULE_TITLE                      "title"
#define RULE_AUTHOR_SOURCE              "a&s"
#define RULE_AUTHOR                     "author"
#define RULE_SOURCE                     "source"
#define RULE_DATE                       "date"
#define RULE_MAIN_NODE                  "mn"
#define RULE_AD_NODE                    "ad"

#define XPATH_WITH_ATTRIBUTE		true

#define CONTENT_BLOCK			1
#define LINK_BLOCK			2
#define CHANNEL_BLOCK			4
#define INVALID_BLOCK			0

#define ALLOWED_CLUSTER_TYPE		nsCString("allowed_cluster_type")

const std::string non_tag[]=
{
     "FORM",
     "SELECT",
     "LI",
     "A",
     "UL",
     "LABEL",
     "OPTION",
     "MENU"
};
const std::string AttNames[]=
{
     "class",
     "id",
     "valign",
     "halign",
     "align",
     "bgcolor",
     "color",
     "font"
};
#endif
