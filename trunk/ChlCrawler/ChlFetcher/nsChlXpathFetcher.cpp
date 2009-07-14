#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsChlXpathFetcher.h"
#include "nsIDOMElement.h"
#include "nsIDOMNode.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMHTMLCollection.h"
#include "nsIDOMHTMLAnchorElement.h"
#include "nsIDOMHTMLLinkElement.h"
#include "nsIDOMXPathEvaluator.h"
#include "nsIDOMXPathNSResolver.h"
#include "nsIDOMXPathExpression.h"
#include "nsIDOMXPathResult.h"
#include "nsIDOM3Node.h"
#include "nsIColAtt.h"
#include "nsIBoxObject.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <list>
#include <set>
#include "sha1.h"
#include "property.h"
#include "ChlXpath.h"
#include <regex.h>
#include <stdlib.h>
NS_IMPL_ISUPPORTS1(nsChlXpathFetcher, nsIChlFetcher)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsChlXpathFetcher)

static nsModuleComponentInfo components[] =
{
     {
	  NS_CHLXPATHFETCHER_CLASSNAME,
	  NS_CHLXPATHFETCHER_CID,
	  NS_CHLXPATHFETCHER_CONTRACTID,
	  nsChlXpathFetcherConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsChlXpathFetcherModule", components)




/* Implementation file */


nsChlXpathFetcher::nsChlXpathFetcher()
:mChl(nsnull),
     mDoc(nsnull),
     property(nsnull),
     replaceType(0),
     expNabor(0)
{
     /* member initializers and constructor code */
}

nsChlXpathFetcher::~nsChlXpathFetcher()
{
     /* destructor code */
}

/* void SetChl (in nsIColAtt chl); */
NS_IMETHODIMP nsChlXpathFetcher::SetChl(nsIChlAtt *chl)
{
     mChl=chl;
     return NS_OK;
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsChlXpathFetcher::SetDocument(nsIDOMDocument *doc)
{
     mDoc=doc;
     nsdoc=do_QueryInterface(doc);
     cols.Clear();
     GetColums();
     return NS_OK;
}

/* void SetProperty (in nsIPersistentProperties prop); */
NS_IMETHODIMP nsChlXpathFetcher::SetProperty(nsIPersistentProperties *prop)
{
     property=prop;
     nsString expNab;
     nsString rplType;
     nsString strFrom;
     nsString strTo;
     property->GetStringProperty(COL_REPLACE_TYPE,rplType);
     replaceType=atol(NS_ConvertUTF16toUTF8(rplType).get());
     LOG<<"rt:"<<replaceType<<"\n";
     property->GetStringProperty(COL_EXP_NABOR,expNab);
     expNabor=atol(NS_ConvertUTF16toUTF8(expNab).get());

     property->GetStringProperty(COL_REPLACE_FROM,strFrom);
     RepFrom=std::string(NS_ConvertUTF16toUTF8(strFrom).get());

     property->GetStringProperty(COL_REPLACE_TO,strTo);
     RepTo=std::string(NS_ConvertUTF16toUTF8(strTo).get());
     return NS_OK;
}

/* long GetColLength (); */
NS_IMETHODIMP nsChlXpathFetcher::GetColLength(PRInt32 *_retval)
{
     *_retval=cols.Count();
     return NS_OK;
}

/* void GetColItem (in long index, out nsIColAtt col); */
NS_IMETHODIMP nsChlXpathFetcher::GetColItem(PRInt32 index, nsIColAtt **col)
{
     if(index<cols.Count())
     {
	  *col = cols[index];
	  NS_ADDREF(*col);
     }
     else
     {
	  *col=nsnull;
     }
     return NS_OK;
}
int nsChlXpathFetcher::GetColums()
{
     nsresult rv;
     nsCOMPtr<nsIDOMXPathEvaluator> xpathEV=do_QueryInterface(mDoc,&rv);
     if (NS_FAILED(rv))
     {
          std::cout<<"Get evaluator Error:"<<rv<<std::endl;
	  return rv;
     }
     
     ChlXpath cp;
     nsCString wrap;
     mChl->GetXPath(wrap);
     PRInt32 chlId;
     mChl->GetId(&chlId);
     std::string strWrap(wrap.get());
     LOG<<"wrap:"<<wrap.get()<<"chl id"<<chlId<<"\n";
     cp.SetWapper(strWrap);
     PathList &plist=cp.GetPathList();
     LOG<<"list size:"<<plist.size()<<"\n";
     for(PathList::iterator pit=plist.begin();pit!=plist.end();++pit)
     {
	  LOG<<"xpath:"<<pit->first<<"\n";
	  nsCOMPtr<nsIDOMXPathNSResolver> resov;
	  
	  nsCOMPtr<nsIDOMElement> docele;
     
	  mDoc->GetDocumentElement(getter_AddRefs(docele));

	  nsCOMPtr<nsIDOMNode> elenode=do_QueryInterface(docele);

  
	  xpathEV->CreateNSResolver(elenode,getter_AddRefs(resov));
	  
	  nsCOMPtr<nsIDOMXPathExpression> expr;

	  xpathEV->CreateExpression(NS_ConvertUTF8toUTF16(pit->first.c_str()),resov,getter_AddRefs(expr));
	  
	  nsCOMPtr<nsISupports> ret;
	  
	  expr->Evaluate(elenode,0,nsnull,getter_AddRefs(ret));
     
	  nsCOMPtr<nsIDOMXPathResult> exprresults=do_QueryInterface(ret);
	  std::list<nsIDOMNode *> nodeList;
	  std::set<nsIDOMNode *> nodeset;
	  nsIDOMNode* anode=nsnull;
	  do
	  {
	       exprresults->IterateNext(&anode);
	       if(anode!=nsnull)
	       {
		    nsCOMPtr<nsIBoxObject> box;
		    nsIDOMElement* tele;
		    CallQueryInterface(anode,&tele);
		    rv=nsdoc->GetBoxObjectFor(tele,getter_AddRefs(box));
		    if (NS_FAILED(rv))
		    {
			 continue;
		    }
		    PRInt32 h,w;
		    box->GetHeight(&h);
		    box->GetWidth(&w);
		    if(w>h)
		    {
			 nodeList.push_back(anode);
			 nodeset.insert(anode);
		    }
	       }
	  }while(anode!=nsnull);
	  
	  for(std::list<nsIDOMNode *>::iterator lit=nodeList.begin();lit!=nodeList.end();++lit)
	  {
	       nsCString tpath(pit->second.c_str());
	       nsIDOMNode *tmp=*lit;
	       nsIDOMNode *next=nsnull,*pre=nsnull;
	       for(tmp->GetNextSibling(&next);next!=nsnull;next->GetNextSibling(&next))
	       {
		    PRUint16 type;
		    next->GetNodeType(&type);
		    if(type==nsIDOMNode::ELEMENT_NODE)
		    {
			 break;
		    }
	       }
	       for(tmp->GetPreviousSibling(&pre);pre!=nsnull;pre->GetPreviousSibling(&pre))
	       {
		    PRUint16 type;
		    pre->GetNodeType(&type);
		    if(type==nsIDOMNode::ELEMENT_NODE)
		    {
			 break;
		    }
	       }
	       
	       nsCString strName;
	       rv=GetColTitle(tmp,tpath,strName);
	       if (!NS_FAILED(rv))
	       {
		    nsCString strUrl;
		    GetColUrl(tmp,strUrl);
		    if (!NS_FAILED(rv)&&strUrl.Length()>0)
		    {
			 bool isNextCol=false;
			 
			 bool isPreCol=false;
			 if(expNabor==0)
			 {
			      isNextCol=pre!=nsnull&&nodeset.find(pre)!=nodeset.end();
			      isPreCol=next!=nsnull&&nodeset.find(next)!=nodeset.end();
			 }
			 LOG<<"next"<<isNextCol<<next<<"pre"<<isPreCol<<pre<<"curr"<<(nodeset.find(tmp)!=nodeset.end())<<tmp<<"\n";
			 if(!isNextCol&&!isPreCol)
			 {
			      
			 
			      nsCOMPtr<nsIColAtt> col=do_CreateInstance("@nyapc.com/XPCOM/nsColAtt;1", &rv);
			      if (NS_FAILED(rv))
			      {
				   LOG<<"Get nsWebChannel Error:"<<rv<<"\n";
			      }else
			      {
				   LOG<<"name:"<<strName.get()<<" url:"<<strUrl.get()<<" chl id:"<<chlId<<"\n";
				   col->SetCOL(strName, strUrl,chlId);
				   nsCString tpName;
				   col->GetName(tpName);
				   cols.AppendObject(col);
			      }
			 }
		    }
	       }

	  }
     }
}
NS_IMETHODIMP nsChlXpathFetcher::GetColUrl(nsIDOMNode * aNode,nsACString &url)
{
     std::list<std::string> linkList;
     std::stack<nsIDOMNode*> nodestack;
     nodestack.push(aNode);
     while(!nodestack.empty())
     {
	  nsIDOMNode* domele=nodestack.top();
	  nodestack.pop();
	  PRUint16 type;
	  domele->GetNodeType(&type);
	  if(type==nsIDOMNode::ELEMENT_NODE)
	  {
			 
	       nsString linkUrl;
	       nsCOMPtr<nsIDOMHTMLAnchorElement> linkEle=do_QueryInterface(domele);
	       if(linkEle!=nsnull)
	       {
		    linkEle->GetHref(linkUrl);
	       }else
	       {
		    nsCOMPtr<nsIDOMHTMLLinkElement>  linkEle2=do_QueryInterface(domele);
		    if(linkEle!=nsnull)
		    {
			 linkEle->GetHref(linkUrl);
		    }
	       }
	       if(linkUrl.Length()>0)
	       {
		    nsCString jshead("javascript:");
		    if(linkUrl.Find(NS_ConvertUTF8toUTF16(jshead))<0)
		    {
			 std::string tmpLink(NS_ConvertUTF16toUTF8(linkUrl).get());
			 linkList.push_back(tmpLink);
		    }
	       }else
	       {
		    nsIDOMNode *domnode=nsnull;
		    for(domele->GetFirstChild(&domnode);domnode!=nsnull;domnode->GetNextSibling(&domnode))
		    {
			 nodestack.push(domnode); 
		    }
	       }
	  }
	  
     }
     nsCString ret;
     if(!linkList.empty())
     {
	  std::string tmpUrl=linkList.front();
	  ReplaceString(tmpUrl,RepFrom,RepTo,replaceType);
	  ret=nsCString(tmpUrl.c_str());
     }
     if(ret.Length()==0)
     {
	   nsIDOMNode * par;
	   aNode->GetParentNode(&par);
	   if(par!=nsnull)
		GetKinUrl(par,ret);
     }
     if(ret.Length()==0)
     {
	  nsIDOMNode *next;
	  aNode->GetNextSibling(&next);
	  if(next!=nsnull)
		GetKinUrl(next,ret);
     }
     url=ret;
     return NS_OK;
}
NS_IMETHODIMP nsChlXpathFetcher::GetKinUrl(nsIDOMNode * aNode,nsACString &url)
{
     std::list< std::pair<std::string,std::string> > linkList;
     std::stack<nsIDOMNode*> nodestack;
     nodestack.push(aNode);
     
     while(!nodestack.empty())
     {
	  nsIDOMNode* domele=nodestack.top();
	  nodestack.pop();
	  PRUint16 type;
	  domele->GetNodeType(&type);
	  if(type==nsIDOMNode::ELEMENT_NODE)
	  {
	       nsString linkUrl;
	       
	       nsCOMPtr<nsIDOMHTMLAnchorElement> linkEle=do_QueryInterface(domele);
	       if(linkEle!=nsnull)
	       {
		    linkEle->GetHref(linkUrl);
	       }else
	       {
		    nsCOMPtr<nsIDOMHTMLLinkElement>  linkEle2=do_QueryInterface(domele);
		    if(linkEle!=nsnull)
		    {
			 linkEle->GetHref(linkUrl);
		    }
	       }
	       if(linkUrl.Length()>0)
	       {
		    nsCString jshead("javascript:");
		    if(linkUrl.Find(NS_ConvertUTF8toUTF16(jshead))<0)
		    {
			 nsString Value;
			 nsCOMPtr<nsIDOM3Node> nsEle=do_QueryInterface(domele);
			 nsEle->GetTextContent(Value);
			 std::string tmpLink(NS_ConvertUTF16toUTF8(linkUrl).get());
			 std::string tmpTitle(NS_ConvertUTF16toUTF8(Value).get());
			 linkList.push_back(make_pair(tmpTitle,tmpLink));
		    }
	       }else
	       {
		    nsIDOMNode *domnode=nsnull;
		    for(domele->GetFirstChild(&domnode);domnode!=nsnull;domnode->GetNextSibling(&domnode))
		    {
			 nodestack.push(domnode); 
		    }
	       }
	  }
	  
     }
     if(!linkList.empty())
     {
	  std::string tmpTitle=linkList.front().first;
	  if(tmpTitle.find("更多")!=std::string::npos)
	  {
	       std::string tmpUrl=linkList.front().second;
	       ReplaceString(tmpUrl,RepFrom,RepTo,replaceType);
	       nsCString ret(tmpUrl.c_str());
	       url=ret;
	  }
     }
}
NS_IMETHODIMP nsChlXpathFetcher::GetColTitle(nsIDOMNode * aNode,const nsACString & titlePath,nsACString &title)
{
     nsresult rv;
     nsCOMPtr<nsIDOMDocument> doc;
     aNode->GetOwnerDocument(getter_AddRefs(doc));

     nsCOMPtr<nsIDOMXPathEvaluator> xpathEV=do_QueryInterface(doc,&rv);
     if (NS_FAILED(rv))
     {
          std::cout<<"Get evaluator Error:"<<rv<<std::endl;
	  return rv;
     }
     LOG<<"titlePath:"<<nsCString(titlePath).get()<<"\n";
     nsCOMPtr<nsIDOMXPathNSResolver> resov;
     
     nsCOMPtr<nsIDOMElement> docele;
     
     doc->GetDocumentElement(getter_AddRefs(docele));
     
     nsCOMPtr<nsIDOMNode> elenode=do_QueryInterface(docele);
     
     xpathEV->CreateNSResolver(aNode,getter_AddRefs(resov));
	  
     nsCOMPtr<nsIDOMXPathExpression> expr;
     
     
     xpathEV->CreateExpression(NS_ConvertUTF8toUTF16(titlePath),resov,getter_AddRefs(expr));
	  
     nsCOMPtr<nsISupports> ret;
     
     expr->Evaluate(aNode,0,nsnull,getter_AddRefs(ret));
     
     nsCOMPtr<nsIDOMXPathResult> exprresults=do_QueryInterface(ret);
     nsIDOMNode* node=nsnull;
     
     do
     {
	  exprresults->IterateNext(&node);
	  if(node!=nsnull)
	  {
	       nsString nodetext;
	       nsIDOMNode *domnode=nsnull;
	       for(node->GetFirstChild(&domnode);domnode!=nsnull;domnode->GetNextSibling(&domnode))
	       {
		    PRUint16 type;
		    domnode->GetNodeType(&type);
		    if(type==nsIDOMNode::TEXT_NODE)
		    {
			 nsString tmp;
			 domnode->GetNodeValue(tmp);
			 nodetext.Append(tmp);
		    }
	       }
	       std::string tmpStrTil(NS_ConvertUTF16toUTF8(nodetext).get());
	       string_filter(tmpStrTil);
			 
	       if(IsTitle(tmpStrTil))
	       {		    
		    title=nsCString(tmpStrTil.c_str());
		    break;
	       }else
	       {
		    nsCOMPtr<nsIDOMElement> ele=do_QueryInterface(node);
		    nsString tag;
		    ele->GetTagName(tag);
		    if(std::string(NS_ConvertUTF16toUTF8(tag).get())=="IMG")
		    {
			 ele->GetAttribute(NS_ConvertUTF8toUTF16("alt"),nodetext);
			 std::string tmpStrTil(NS_ConvertUTF16toUTF8(nodetext).get());
			 
			 if(IsTitle(tmpStrTil))
			 {
			      title=nsCString(tmpStrTil.c_str());
			      break;
			 }
		    }
	       }
	  }
     }while(node!=nsnull);
     if(node==nsnull)
	  return NS_ERROR_FAILURE;
     else
	  return NS_OK;
}
bool nsChlXpathFetcher::IsTitle(const std::string &str)
{
     int len=str.length();
     if(str.find("\n")!=std::string::npos)
     {
	  return false;
     }
     if(str.find("更多")!=std::string::npos)
     {
	  return false;
     }
     if(len>21||len<4)
     {
	  return false;
     }
     return true;
}
/** 
 * @brief Mapping the url to the right one 
 * 
 * @param s the url
 * @param from replace this string
 * @param to   the target substring
 * @param type  mapping type.
 */
void nsChlXpathFetcher::ReplaceString(std::string & s,const std::string &from,const std::string &to,int type)
{
     LOG<<"s:"<<s<<"type:"<<type<<"\n";
     std::size_t index;
     if(type==1)
     {
	  index=s.find(from);
     }else if(type==2)
     {
	  index=s.rfind(from);
     }else if(type==3)
     {
	  index=s.find(from);
     }
     else if(type==4)
     {
	  index=s.rfind(from);
     }else
     {
	  return;
     }
     if(index!=std::string::npos)
     {
	  s.replace(index,from.length(),to);
	  LOG<<"s:"<<s<<"type:"<<type<<"\n";
	  if(type>2)
	  {
	       std::string ret=TranHost(s);
	       s=ret;
	  }
     }
     LOG<<"s:"<<s<<"type:"<<type<<"\n";
}
std::string nsChlXpathFetcher::TranHost(const std::string &from)
{
     std::string ret;
     std::size_t index,index1=7;
     index=from.rfind("/");
     std::string blogname=from.substr(index);
     blogname.append(".blog.");
     ret.append("http:/");
     ret.append(blogname);
     std::string host=from.substr(index1,index-index1);
     ret.append(host);
     return ret;
     
}
void nsChlXpathFetcher::string_filter(std::string & s)
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
