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
#include <stack>
#include <vector>
#include "nsIDOM3Node.h"
#include "nsIDOMHTMLAnchorElement.h"
#include "nsIDOMHTMLLinkElement.h"
#include "mozIJSSubScriptLoader.h"
#include "nsIDOMDocumentEvent.h"
#include "nsIDOMEvent.h"
#include "nsIColAtt.h"
#include "sha1.h"
#include "property.h"
#include <regex.h>
#include <stdlib.h>
static NS_DEFINE_CID(kIOServiceCID, NS_IOSERVICE_CID);
NS_IMPL_ISUPPORTS1(nsColNextPageFetcher, nsIColNextPageFetcher)

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
:hasLoadJs(false),
     mNextPage(nsnull)
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
     mNextPage=nsnull;
     mEvtEle=nsnull;
     FillPages();
     return NS_OK;
}

/* void SetProperty (in nsIPersistentProperties prop); */
NS_IMETHODIMP nsColNextPageFetcher::SetProperty(nsIPersistentProperties *prop)
{
     property=prop;


     return NS_OK;
}
/* attribute nsIColAtt nextPage; */
NS_IMETHODIMP nsColNextPageFetcher::GetNextPage(nsIColAtt * *aNextPage)
{
     if(mNextPage!=nsnull)
     {
	  *aNextPage=mNextPage;
	  NS_ADDREF(*aNextPage);
     }
     return NS_OK;
}
/* void GetEventEle (out nsIDOMElement ele); */
NS_IMETHODIMP nsColNextPageFetcher::GetEventEle(nsIDOMElement **ele)
{
     if(mEvtEle!=nsnull)
     {
	  *ele=mEvtEle;
	  NS_ADDREF(*ele);
     }
     return NS_OK;
}
/** 
 * @brief Get the urls on the other page or Get the next page url and create a new Colum. 
 * 
 * 
 * @return 
 */
NS_IMETHODIMP nsColNextPageFetcher::FillPages()
{
     nsCOMPtr<nsIDOMElement> domele;
     mDoc->GetDocumentElement(getter_AddRefs(domele));
     nsIDOMNode *domnode;
     CallQueryInterface(domele,&domnode);
     std::list<nsIDOMNode*> leafList;
     std::stack<nsIDOMNode*> eleStack;
     eleStack.push(domnode);
     while(!eleStack.empty())
     {
	  nsIDOMNode *domele=eleStack.top();
	  eleStack.pop();
	  nsCOMPtr<nsIDOMElement> tmpEle=do_QueryInterface(domele);
	  bool isLeaf=true;
	  domnode=nsnull;
	  for(domele->GetFirstChild(&domnode);domnode!=nsnull;domnode->GetNextSibling(&domnode))
	  {
	       PRUint16 type;
	       domnode->GetNodeType(&type);
	       if(type==nsIDOMNode::ELEMENT_NODE)
	       {
		    isLeaf=false;
		    break;
	       }
	  }
	  if(isLeaf)
	       leafList.push_back(domele);
	  else
	  {
	       domnode=nsnull;
	       for(domele->GetFirstChild(&domnode);domnode!=nsnull;domnode->GetNextSibling(&domnode))
	       {
		    PRUint16 type;
		    domnode->GetNodeType(&type);
		    if(type==nsIDOMNode::ELEMENT_NODE)
		    {
			 eleStack.push(domnode);
		    }
	       }
	  }
     }
     for(std::list<nsIDOMNode*>::iterator it=leafList.begin();it!=leafList.end();++it)
     {
	  nsCOMPtr<nsIDOMElement> tmpEle=do_QueryInterface(*it);
	  
	  nsString Text;
	  nsCOMPtr<nsIDOM3Node> nsEle=do_QueryInterface(tmpEle);
	  nsEle->GetTextContent(Text);
	  std::string eleTextStr(NS_ConvertUTF16toUTF8(Text).get());
	  LOG<<"title:"<<eleTextStr<<"\n";
	  if(is_nextpage_text(eleTextStr))
	  {
	       nsString linkUrl;
	       nsCOMPtr<nsIDOMHTMLAnchorElement> linkEle=do_QueryInterface(tmpEle);
	       if(linkEle!=nsnull)
	       {
		    linkEle->GetHref(linkUrl);
	       }else
	       {
		    nsCOMPtr<nsIDOMHTMLLinkElement>  linkEle2=do_QueryInterface(tmpEle);
		    if(linkEle2!=nsnull)
		    {
			 linkEle2->GetHref(linkUrl);
		    }
	       }
	       nsresult rv;
	       if(linkUrl.Length()>0&&linkUrl.Find(NS_ConvertUTF8toUTF16("javascript:"))<0&&linkUrl.Find(NS_ConvertUTF8toUTF16("#"))<0)
	       {
		    mNextPage=do_CreateInstance("@nyapc.com/XPCOM/nsColAtt;1", &rv);
		    if (NS_FAILED(rv))
		    {
			 LOG<<"Get nsWebChannel Error:"<<rv<<"\n";
		    }else
		    {
			  PRInt32 chlId;
			  nsCString strName,strAlias;
			  mCol->GetChlId(&chlId);
			  mCol->GetName(strName);
			  mCol->GetAlias(strAlias);
			  nsCString strUrl(NS_ConvertUTF16toUTF8(linkUrl).get());
			  LOG<<"name:"<<strName.get()<<" url:"<<strUrl.get()<<" chl id:"<<chlId<<"\n";
			  mNextPage->SetCOL(strName,strUrl ,chlId);
			  mNextPage->SetAlias(strAlias);
		    }
		    break;
	       }
	       else
	       {
		    nsString onclick;
		    tmpEle->GetAttribute(NS_ConvertUTF8toUTF16("onclick"),onclick);
		    if(onclick.Length()>0)
		    {
			 mEvtEle=tmpEle;
		    }
		    break;
	       }
	       
	  }
     }
     return NS_OK;
}


bool nsColNextPageFetcher::is_nextpage_text(std::string text)
{
     bool b = false;

     int flag = 0;
     regex_t reg;
     int r = regcomp(&reg, "^\\(下.\\{,6\\}页.\\?>*\\|>\\+\\)$", flag);
     if(r != 0)
     {
	  char ebuf[128];
	  regerror(r, &reg, ebuf, sizeof(ebuf));
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
