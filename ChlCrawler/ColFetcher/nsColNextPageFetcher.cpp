#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsIUrlAtt.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMHTMLCollection.h"
#include "nsColNextPageFetcher.h"
#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <vector>
#include "nsIDOM3Node.h"
#include "nsIDOMHTMLAnchorElement.h"
#include "nsIDOMHTMLLinkElement.h"
#include "nsIColAtt.h"
#include "sha1.h"
#include "property.h"
#include <regex.h>
#include <stdlib.h>
static NS_DEFINE_CID(kIOServiceCID, NS_IOSERVICE_CID);
NS_IMPL_ISUPPORTS1(nsColNextPageFetcher, nsIColFetcher)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsColNextPageFetcher)

static nsModuleComponentInfo components[] =
{
     {
	  NS_COLNEXTPAGEFETCHER_CLASSNAME,
	  NS_COLNEXTPAGEFETCHER_CID,
	  NS_COLNEXTPAGEFETCHER_CONTRACTID,
	  nsColNextPageFetcherConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsColNextPageFetcherModule", components)


/* Implementation file */


nsColNextPageFetcher::nsColNextPageFetcher()
:pageCount(1)
{
     /* member initializers and constructor code */
}

nsColNextPageFetcher::~nsColNextPageFetcher()
{
     /* destructor code */
}

/* attribute nsIColAtt col; */
NS_IMETHODIMP nsColNextPageFetcher::GetCol(nsIColAtt * *aCol)
{
     *aCol=mCol;
     NS_ADDREF(*aCol);
     return NS_OK;
}
NS_IMETHODIMP nsColNextPageFetcher::SetCol(nsIColAtt * aCol)
{
     mCol=aCol;
     return NS_OK;
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsColNextPageFetcher::SetDocument(nsIDOMDocument *doc)
{
     mDoc=doc;
     urls.Clear();
     FillUrls();
     return NS_OK;
}

/* void SetProperty (in nsIPersistentProperties prop); */
NS_IMETHODIMP nsColNextPageFetcher::SetProperty(nsIPersistentProperties *prop)
{
     property=prop;
     nsString strCount;
     property->GetStringProperty(COL_PAGE_COUNT,strCount);
     pageCount=atol(NS_ConvertUTF16toUTF8(strCount).get());

     return NS_OK;
}

/* long GetColLength (); */
NS_IMETHODIMP nsColNextPageFetcher::GetUrlLength(PRInt32 *_retval)
{
     *_retval=urls.Count();
     return NS_OK;
}

/* void GetColItem (in long index, out nsIColAtt col); */
NS_IMETHODIMP nsColNextPageFetcher::GetUrlItem(PRInt32 index, nsIUrlAtt **url)
{
     if(index<urls.Count())
     {
	  *url = urls[index];
	  NS_ADDREF(*url);
     }
     else
     {
	  *url=nsnull;
     }
     return NS_OK;
}
NS_IMETHODIMP nsColNextPageFetcher::FillUrls()
{
     nsCOMPtr<nsIDOMHTMLDocument> domhtml=do_QueryInterface(mDoc);
     nsCOMPtr<nsIDOMHTMLCollection> links;
     domhtml->GetLinks(getter_AddRefs(links));
     PRInt32 colId;
     mCol->GetId(&colId);

     PRUint32 len;
     links->GetLength(&len);
           
     for(int i=0;i<len;i++)
     {
	  nsCOMPtr<nsIDOMNode> aLink(nsnull);
	  links->Item(i,getter_AddRefs(aLink));
	  if(aLink!=nsnull)
	  {
	       nsString Value;
	       nsString linkUrl;
	       nsCOMPtr<nsIDOM3Node> nsEle=do_QueryInterface(aLink);
	       nsEle->GetTextContent(Value);
					
	       nsCOMPtr<nsIDOMHTMLAnchorElement> linkEle=do_QueryInterface(aLink);
	       if(linkEle!=nsnull)
	       {
		    linkEle->GetHref(linkUrl);
	       }else
	       {
		    nsCOMPtr<nsIDOMHTMLLinkElement>  linkEle2=do_QueryInterface(aLink);
		    if(linkEle2!=nsnull)
		    {
			 linkEle2->GetHref(linkUrl);
		    }
	       }

	  
	       std::string tmpTitle(NS_ConvertUTF16toUTF8(Value).get());
	       std::string tmpUrl(NS_ConvertUTF16toUTF8(linkUrl).get());
	       std::string expStr("#\\|javascript");
	       LOG<<"title"<<tmpTitle<<" url:"<<tmpUrl<<"\n";
	       if(is_nextpage_text(tmpTitle)&&!StrMatch(tmpUrl,expStr))
	       {
				   
		    nsresult rv;
		    nsCOMPtr<nsIUrlAtt> url=do_CreateInstance("@nyapc.com/XPCOM/nsUrlAtt;1", &rv);
		    if (NS_FAILED(rv))
		    {
			 LOG<<"Get nsWebChannel Error:"<<rv<<"\n";
		    }else
		    {
			 nsCString strName(tmpTitle.c_str());
			 nsCString strUrl(tmpUrl.c_str());
			 LOG<<"name:"<<strName.get()<<" url:"<<strUrl.get()<<" chl id:"<<colId<<"\n";
		    
			 url->SetURL(strName, strUrl,colId);
			 urls.AppendObject(url);
		    }
	       }
	  }
     }

     return NS_OK;
}

bool nsColNextPageFetcher::StrMatch(const std::string &src,const std::string &match)
{
     bool b = false;
     int flag = 0;
     regex_t reg;
     int r = regcomp(&reg, match.c_str(), flag);
     if(r != 0)
     {
	  char ebuf[128];
	  regerror(r, &reg, ebuf, sizeof(ebuf));
	  LOG<<"regexp pattern error: "<<ebuf<<"\n";
     }
     else
     {
	  size_t nmatch = 1;
	  regmatch_t pm;
	  int r = regexec(&reg, src.c_str(), nmatch, &pm, 0);
	  if(r==0)
	  {
	       b = true;
	  }
     }
     regfree(&reg);
     return b;
}

bool nsColNextPageFetcher::is_nextpage_text(std::string text)
{
     bool b = false;

     int flag = 0;
     regex_t reg;
     int r = regcomp(&reg, "^\\([0-9]\\+\\|上.\\{,6\\}页\\|下.\\{,6\\}页\\|>\\+\\|<\\+\\)$", flag);
     if(r != 0)
     {
	  char ebuf[128];
	  regerror(r, &reg, ebuf, sizeof(ebuf));
	  LOG<<"regexp pattern error: "<<ebuf<<"\n";
     }
     else
     {
	  size_t nmatch = 1;
	  regmatch_t pm;
	  string_filter(text);
	  int r = regexec(&reg, text.c_str(), nmatch, &pm, 0);
	  if(!r)
	  {
	       b = true;
	       /*
		 int pos = 0;
		 if(pm.rm_so != -1)
		 {
		 int len = pm.rm_eo - pm.rm_so;
		 s.erase(pm.rm_so, len);
		 string_filter2(s);
		 }
	       */
	  }
     }
     regfree(&reg);

     return b;
}
void nsColNextPageFetcher::string_filter(std::string & s)
{
     int flag = 0;
     regex_t reg;
     int r = regcomp(&reg, "\\(#\\|\n\\| \\|　\\|\\s\\|\r\\|，\\|。\\|：\\|·\\|“\\|[,.:\"|]\\)\\+", flag);
     if(r != 0)
     {
	  char ebuf[128];
	  regerror(r, &reg, ebuf, sizeof(ebuf));
	  LOG<<"regexp pattern error: "<<ebuf<<"\n";
     }
     else
     {
	  size_t nmatch = 1;
	  regmatch_t pm;
	  int r = regexec(&reg, s.c_str(), nmatch, &pm, 0);
	  if(!r)
	  {
	       int pos = 0;
	       if(pm.rm_so != -1)
	       {
		    int len = pm.rm_eo - pm.rm_so;
		    s.erase(pm.rm_so, len);
		    string_filter(s);
	       }
	  }
     }
     regfree(&reg);
}
