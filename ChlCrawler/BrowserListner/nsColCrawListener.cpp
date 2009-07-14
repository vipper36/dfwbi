#include "nsColCrawListener.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMNode.h"
#include "nsXPCOMGlue.h"
#include "nsIDOMDocument.h"
#include "nsIWebNavigation.h"
#include "nsIDOMElement.h"
#include "nsNetUtil.h"
#include "ILayoutAnalysis.h"
#include "nsIDOMDocument.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMHTMLElement.h"
#include "nsIDOMHTMLCollection.h"
#include "nsIDOMNamedNodeMap.h"
#include "nsIDOMHTMLLinkElement.h"
#include "nsIDOMAttr.h"
#include "nsIDOM3Node.h"
#include "nsIDOMHTMLLinkElement.h"
#include "nsIDOMHTMLAnchorElement.h"
#include "nsITreeNode.h"
#include "nsIDOMXPathNSResolver.h"
#include "nsIDOMXPathEvaluator.h"
#include "nsIDOMXPathExpression.h"
#include "nsIDOMXPathResult.h"
#include "property.h"
#include <iconv.h>
#include <iostream>
#include <stdlib.h>
/* Implementation file */

NS_GENERIC_FACTORY_CONSTRUCTOR(nsColCrawListener)

static nsModuleComponentInfo components[] =
{
     {
	  NS_COLCRAWLISTENER_CLASSNAME, 
	  NS_COLCRAWLISTENER_CID,
	  NS_COLCRAWLISTENER_CONTRACTID,
	  nsColCrawListenerConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsColCrawListenerModule", components)

nsColCrawListener::nsColCrawListener()
:nsBrowserListener(),
     ColSrc(nsnull),
     ColFetch(nsnull),
     urlTarget(nsnull),
     bodyCheckCount(0)
{

}
NS_IMETHODIMP nsColCrawListener::Update(PRUint16 stat)
{
     nsresult rv=NS_OK;
     if(mCol!=nsnull)
	  rv=ColSrc->UpdateStat(mCol,stat);
     return rv;
}
NS_IMETHODIMP nsColCrawListener::GetUrl(nsACString &url)
{
     nsresult rv=ColSrc->GetColByStat(LINK_STAT_NEW,getter_AddRefs(mCol));
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     if(mCol!=nsnull)
     {
	  nsCString tmpUrl;
	  mCol->GetUrl(tmpUrl);
	  url=tmpUrl;
     }
     return NS_OK;
}

NS_IMETHODIMP nsColCrawListener::SetWorkSpace(const nsACString & workspace)
{
     nsresult rv=nsBrowserListener::SetWorkSpace(workspace);
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     
     property->GetStringProperty(COL_ALIAS_PATH,AliasPath);

     
     rv = servMan->GetServiceByContractID("@nyapc.com/XPCOM/nsColBridge;1", NS_GET_IID(nsIColBridge), getter_AddRefs(bridge));

     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  nsIColBridge  Error:"<<rv<<"\n";
	  return rv;
     }
     nsCString tmpSrc("/root/workspace/ChlCrawler/blog/chl/tt.sqlite");
     nsCString tmpComN("@nyapc.com/XPCOM/nsUrlDBIO;1");
     bridge->SetUrlSource(tmpSrc,tmpComN);
     tmpComN=nsCString("@nyapc.com/XPCOM/nsColDBIO;1");
     bridge->SetColSource(tmpSrc,tmpComN);

     nsString comName;
     //create nsIColIO com
     property->GetStringProperty(COL_IO_COM,comName);

     std::cout<<"comName:"<<NS_ConvertUTF16toUTF8(comName).get()<<std::endl;

     rv = servMan->GetServiceByContractID(NS_ConvertUTF16toUTF8(comName).get(), NS_GET_IID(nsIColIO), getter_AddRefs(ColSrc));

     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  nsIChlIO  Error:"<<rv<<"\n";
	  return rv;
     }
     nsString value;
     property->GetStringProperty(COL_SOURCE,value);
     std::cout<<"chl source:"<<NS_ConvertUTF16toUTF8(value).get()<<std::endl;
     PRUint16 type;
     ColSrc->GetType(&type);
     if(type==nsIColIO::LOCAL_FILE)
     {
	  nsCString urlfile(mWorkspace);
	  urlfile.Append(NS_ConvertUTF16toUTF8(value));

	  rv=ColSrc->SetLocation(urlfile);
     }else
     {
	  rv=ColSrc->SetLocation(NS_ConvertUTF16toUTF8(value));
     }
     
     if (NS_FAILED(rv)) 
     {
	  return rv;
     }
     //create nsIColFetcher com
     property->GetStringProperty(COL_FETCH_COM,comName);

     std::cout<<"comName:"<<NS_ConvertUTF16toUTF8(comName).get()<<std::endl;

     rv = servMan->GetServiceByContractID(NS_ConvertUTF16toUTF8(comName).get(), NS_GET_IID(nsIColFetcher), getter_AddRefs(ColFetch));

     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  nsIChlFetcher  Error:"<<rv<<"\n";
	  return rv;
     }
     ColFetch->SetProperty(property);
     
      //create nsColNextPageFetcher com
     property->GetStringProperty(COL_PAGE_COM,comName);

     std::cout<<"comName:"<<NS_ConvertUTF16toUTF8(comName).get()<<std::endl;

     rv = servMan->GetServiceByContractID(NS_ConvertUTF16toUTF8(comName).get(), NS_GET_IID(nsIColFetcher), getter_AddRefs(ColPageFetch));

     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  nsIChlFetcher  Error:"<<rv<<"\n";
	  return rv;
     }
     ColPageFetch->SetProperty(property);

     //create nsIUrlIO com
     property->GetStringProperty(URL_IO_COM,comName);

     std::cout<<"comName:"<<NS_ConvertUTF16toUTF8(comName).get()<<std::endl;

     rv = servMan->GetServiceByContractID(NS_ConvertUTF16toUTF8(comName).get(), NS_GET_IID(nsIUrlIO), getter_AddRefs(urlTarget));

     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  nsIChlIO  Error:"<<rv<<"\n";
	  return rv;
     }

     property->GetStringProperty(URL_SOURCE,value);
     std::cout<<"url target:"<<NS_ConvertUTF16toUTF8(value).get()<<std::endl;
     
     urlTarget->GetType(&type);
     if(type==nsIUrlIO::LOCAL_FILE)
     {
	  nsCString urlfile(mWorkspace);
	  urlfile.Append(NS_ConvertUTF16toUTF8(value));

	  rv=urlTarget->SetLocation(urlfile);
     }else
     {
	  rv=urlTarget->SetLocation(NS_ConvertUTF16toUTF8(value));
     }     
     if (NS_FAILED(rv)) 
     {
	  return rv;
     }
     timeOut->InitWithCallback(this, 300, 0);
     return NS_OK;
}

NS_IMETHODIMP nsColCrawListener::Excute(nsIWebNavigation *nav)
{
     nsresult rv=NS_OK;
     nsCOMPtr<nsIDOMDocument> domdoc;
     rv=nav->GetDocument(getter_AddRefs(domdoc));
     if (NS_FAILED(rv))
     {
	  LOG<<"Get domnode Error:"<<rv<<"\n";
	  return rv;
     }
     domdoc->Normalize();
     nsCOMPtr<nsIDOMHTMLDocument> domhtml=do_QueryInterface(domdoc);
     bool hasb=HasBody(domhtml);
     if(!hasb&&bodyCheckCount<3)
     {
	  bodyCheckCount++;
	  return NS_ERROR_FAILURE;
     }
     else if(hasb)
     {
	  nsCOMPtr<nsIDOMElement> ele;
	  domhtml->GetDocumentElement(getter_AddRefs(ele));
	  nsCOMPtr<nsIDOMNSHTMLElement> docEle=do_QueryInterface(ele);
	  nsString inHtml;
	  docEle->GetInnerHTML(inHtml);
	  LOG<<"heml:"<<NS_ConvertUTF16toUTF8(inHtml).get()<<"\n";
	  if(mCol!=nsnull)
	  {
	       PRInt32 len=0;
	       ColFetch->SetCol(mCol);
	       ColFetch->SetDocument(domdoc);
	       ColFetch->GetUrlLength(&len);
	       
	       for(PRInt32 i=0;i<len;i++)
	       {
		    nsCOMPtr<nsIUrlAtt> url;
		    ColFetch->GetUrlItem(i,getter_AddRefs(url));
		    nsCString urlStr,name;
		    url->GetLink(urlStr);
		    bridge->GetColName(urlStr,name);
		    LOG<<"title:"<<name.get()<<"\n";
		    urlTarget->PutURL(url);
	       }
	       nsCString alias;
	       mCol->GetAlias(alias);
	       LOG<<"alias:"<<alias.get()<<"\n";
	       if(alias.Length()==0&&AliasPath.Length()>0)
	       {
		    nsCOMPtr<nsIDOMXPathEvaluator> xpathEV=do_QueryInterface(domdoc,&rv);
		    if (NS_FAILED(rv))
		    {
			 std::cout<<"Get evaluator Error:"<<rv<<std::endl;
			 return rv;
		    }
		    nsCOMPtr<nsIDOMXPathNSResolver> resov;
	  
		    nsCOMPtr<nsIDOMNode> elenode=do_QueryInterface(ele);

  
		    xpathEV->CreateNSResolver(elenode,getter_AddRefs(resov));
		    
		    nsCOMPtr<nsIDOMXPathExpression> expr;

		    xpathEV->CreateExpression(AliasPath,resov,getter_AddRefs(expr));
	  
		    nsCOMPtr<nsISupports> ret;
		    
		    expr->Evaluate(elenode,0,nsnull,getter_AddRefs(ret));
     
		    nsCOMPtr<nsIDOMXPathResult> exprresults=do_QueryInterface(ret);

		    nsCOMPtr<nsIDOMNode> nameEle=nsnull;
		    exprresults->IterateNext(getter_AddRefs(nameEle));
		    if(nameEle!=nsnull)
		    {
			 nsString tmpAlias;
			 nsCOMPtr<nsIDOM3Node> nsEle=do_QueryInterface(nameEle);
			 nsEle->GetTextContent(tmpAlias);
			 alias=NS_ConvertUTF16toUTF8(tmpAlias);
			 PRInt32 colId;
			 mCol->GetId(&colId);
			 alias.StripChars("'");
			 LOG<<"aliase:"<<alias.get()<<"\n";
			 ColSrc->UpdateByID(colId,nsCString("alias"), alias); 
		    }
		    
	       }
	       // len=0;
// 	       ColPageFetch->SetCol(mCol);
// 	       ColPageFetch->SetDocument(domdoc);
// 	       ColPageFetch->GetUrlLength(&len);
// 	       LOG<<"page len"<<len<<"\n";
// 	       for(PRInt32 i=0;i<len;i++)
// 	       {
// 		    nsCOMPtr<nsIUrlAtt> url;
// 		    ColPageFetch->GetUrlItem(i,getter_AddRefs(url));
// 		    nsCString urlStr;
// 		    url->GetLink(urlStr);
// 		    nsCOMPtr<nsIColAtt> col=do_CreateInstance("@nyapc.com/XPCOM/nsColAtt;1", &rv);
// 		    if (NS_FAILED(rv))
// 		    {
// 			 LOG<<"Get nsWebChannel Error:"<<rv<<"\n";
// 		    }else
// 		    {
// 			 PRInt32 chlId;
// 			 mCol->GetChlId(&chlId);
// 			 nsCString tmpName;
// 			 mCol->GetName(tmpName);
// 			 col->SetCOL(tmpName, urlStr,chlId);
// 			 col->SetAlias(alias);
// 			 ColSrc->PutCol(col);
// 		    }
// 	       }
	       Update(LINK_STAT_GET);
	  }
     }else
     {
	  Update(LINK_STAT_ERROR);
     }
     bodyCheckCount=0;
     return rv;
}
