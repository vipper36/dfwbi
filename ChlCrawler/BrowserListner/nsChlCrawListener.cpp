#include "nsChlCrawListener.h"
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
#include "nsIUrlAtt.h"
#include "property.h"
#include <iconv.h>
#include <iostream>
#include <stdlib.h>
/* Implementation file */

NS_GENERIC_FACTORY_CONSTRUCTOR(nsChlCrawListener)

static nsModuleComponentInfo components[] =
{
     {
	  NS_CHLCRAWLISTENER_CLASSNAME, 
	  NS_CHLCRAWLISTENER_CID,
	  NS_CHLCRAWLISTENER_CONTRACTID,
	  nsChlCrawListenerConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsChlCrawListenerModule", components)

nsChlCrawListener::nsChlCrawListener()
:nsBrowserListener(),
     ChlSrc(nsnull),
     ChlFetch(nsnull),
     chlWrap(nsnull),
     colTarget(nsnull),
     bodyCheckCount(0)
{
     nsresult rv;
     analyzer=do_CreateInstance("@nyapc.com/XPCOM/LayoutAnalysis;1", &rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"Get Layout analysis  Error:"<<rv<<"\n";
     }
}
NS_IMETHODIMP nsChlCrawListener::Update(PRUint16 stat)
{
     return NS_OK;
}
NS_IMETHODIMP nsChlCrawListener::GetUrl(nsACString &url)
{
     nsresult rv=ChlSrc->GetChl(getter_AddRefs(mChl));
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     if(mChl!=nsnull)
     {
	  nsCString tmpUrl;
	  mChl->GetUrl(tmpUrl);
	  url=tmpUrl;
     }
     return NS_OK;
}

NS_IMETHODIMP nsChlCrawListener::SetWorkSpace(const nsACString & workspace)
{
     nsresult rv=nsBrowserListener::SetWorkSpace(workspace);
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     nsString comName;


     //create nsIChlIO com
     property->GetStringProperty(CHL_IO_COM,comName);

     std::cout<<"comName:"<<NS_ConvertUTF16toUTF8(comName).get()<<std::endl;

     rv = servMan->GetServiceByContractID(NS_ConvertUTF16toUTF8(comName).get(), NS_GET_IID(nsIChlIO), getter_AddRefs(ChlSrc));

     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  nsIChlIO  Error:"<<rv<<"\n";
	  return rv;
     }
     nsString value;
     property->GetStringProperty(CHL_SOURCE,value);
     LOG<<"chl source:"<<NS_ConvertUTF16toUTF8(value).get()<<"\n";
     PRUint16 type;
     ChlSrc->GetType(&type);
     if(type==nsIChlIO::LOCAL_FILE)
     {
	  nsCString urlfile(mWorkspace);
	  urlfile.Append(NS_ConvertUTF16toUTF8(value));

	  rv=ChlSrc->SetLocation(urlfile);
     }else
     {
	  rv=ChlSrc->SetLocation(NS_ConvertUTF16toUTF8(value));
     }
     
     if (NS_FAILED(rv)) 
     {
	  return rv;
     }

     //create nsIChlFetcher com
     property->GetStringProperty(CHL_FETCH_COM,comName);

     LOG<<"comName:"<<NS_ConvertUTF16toUTF8(comName).get()<<"\n";

     rv = servMan->GetServiceByContractID(NS_ConvertUTF16toUTF8(comName).get(), NS_GET_IID(nsIChlFetcher), getter_AddRefs(ChlFetch));

     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  nsIChlFetcher  Error:"<<rv<<"\n";
	  return rv;
     }
     ChlFetch->SetProperty(property);

     //create nsIChlWrapper com
     property->GetStringProperty(CHL_WRAP_COM,comName);

     LOG<<"comName:"<<NS_ConvertUTF16toUTF8(comName).get()<<"\n";

     rv = servMan->GetServiceByContractID(NS_ConvertUTF16toUTF8(comName).get(), NS_GET_IID(nsIChlWrapper), getter_AddRefs(chlWrap));

     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  nsIChlWrapper  Error:"<<rv<<"\n";
	  return rv;
     }
     
     nsString strType;
     PRUint16 chlType;
     property->GetStringProperty(CHL_TYPE,strType);
     chlType=atoi(NS_ConvertUTF16toUTF8(strType).get());
     LOG<<"xpath type:"<<chlType<<"\n";
     chlWrap->SetXType(chlType);
     
//create nsIColIO com
     property->GetStringProperty(COL_IO_COM,comName);

     LOG<<"comName:"<<NS_ConvertUTF16toUTF8(comName).get()<<std::endl;

     rv = servMan->GetServiceByContractID(NS_ConvertUTF16toUTF8(comName).get(), NS_GET_IID(nsIColIO), getter_AddRefs(colTarget));

     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  nsIColIO  Error:"<<rv<<"\n";
	  return rv;
     }

     property->GetStringProperty(COL_SOURCE,value);
     std::cout<<"col target:"<<NS_ConvertUTF16toUTF8(value).get()<<std::endl;
     
     colTarget->GetType(&type);
     if(type==nsIColIO::LOCAL_FILE)
     {
	  nsCString urlfile(mWorkspace);
	  urlfile.Append(NS_ConvertUTF16toUTF8(value));

	  rv=colTarget->SetLocation(urlfile);
     }else
     {
	  rv=colTarget->SetLocation(NS_ConvertUTF16toUTF8(value));
     }     
     if (NS_FAILED(rv)) 
     {
	  return rv;
     }
     timeOut->InitWithCallback(this, 300, 0);
     return NS_OK;
}

NS_IMETHODIMP nsChlCrawListener::Excute(nsIWebNavigation *nav)
{
     nsresult rv=NS_OK;
     nsCOMPtr<nsIDOMDocument> domdoc;
     rv=nav->GetDocument(getter_AddRefs(domdoc));
     if (NS_FAILED(rv))
     {
	  std::cout<<"Get domnode Error:"<<std::hex<<rv<<std::endl;
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

		  
	  nsCString tmpWrap;

	  mChl->GetXPath(tmpWrap);
	  LOG<<"wrap:"<<tmpWrap.get()<<"\n";
	  if(tmpWrap.Length()>0)
	  {
	       PRInt32 len=0;
	       ChlFetch->SetChl(mChl);
	       LOG<<"------------\n";
	       ChlFetch->SetDocument(domdoc);
	       LOG<<"------------1\n";
	       ChlFetch->GetColLength(&len);
	       LOG<<"col count:"<<len<<"\n";
	       for(PRInt32 i=0;i<len;i++)
	       {
		    nsCOMPtr<nsIColAtt> col;
		    ChlFetch->GetColItem(i,getter_AddRefs(col));
		    colTarget->PutCol(col);
	       }
	  }else
	  {
	       nsCString tmpWrap;
	       analyzer->SetDocument(domhtml);
	       analyzer->SetKMeanAlg(nsCString("Hybrid"));
	       nsCOMPtr<nsITreeNode> tn;
	       rv=analyzer->GetResult(getter_AddRefs(tn));
	       if (NS_FAILED(rv))
	       {
		    LOG<<"Get ClustBlock Error:"<<rv<<"\n";
	       }else
	       {
		    chlWrap->SetDocument(domdoc);
		    chlWrap->SetTree(tn);
		    chlWrap->GetWrapper(tmpWrap);
		    LOG<<"Wrapper:"<<tmpWrap.get()<<"\n";
		    PRInt32 chlId;
		    mChl->GetId(&chlId);
		    if(tmpWrap.Length()>0)
		    {
			 ChlSrc->UpdateByID(chlId, nsCString("xpath"), tmpWrap);
		    }
	       }
	  }
	  Update(LINK_STAT_GET);
     }else
     {
	  Update(LINK_STAT_ERROR);
     }
     bodyCheckCount=0;
     return rv;
}
