#include "nsPageCrawListener.h"
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
#include "nsIUrlAtt.h"
#include "property.h"
#include <iconv.h>
#include <iostream>
#include <stdlib.h>
/* Implementation file */

NS_GENERIC_FACTORY_CONSTRUCTOR(nsPageCrawListener)

static nsModuleComponentInfo components[] =
{
     {
	  NS_PAGECRAWLISTENER_CLASSNAME, 
	  NS_PAGECRAWLISTENER_CID,
	  NS_PAGECRAWLISTENER_CONTRACTID,
	  nsPageCrawListenerConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsPageCrawListenerModule", components)

nsPageCrawListener::nsPageCrawListener()
:nsBrowserListener(),
     bodyCheckCount(0)
{
     nsresult rv;
}
NS_IMETHODIMP nsPageCrawListener::Update(PRUint16 stat)
{
    if(mUrl!=nsnull)
        urlSrc->UpdateStat(mUrl,stat);
     return NS_OK;
}
NS_IMETHODIMP nsPageCrawListener::GetUrl(nsACString &url)
{
	nsresult rv=urlSrc->GetURL(getter_AddRefs(mUrl),LINK_STAT_NEW);
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     if(mUrl!=nsnull)
     {
	  nsCString tmpUrl;
	  mUrl->GetLink(tmpUrl);
	  url=tmpUrl;
     }
     return NS_OK;
}
NS_IMETHODIMP nsPageCrawListener::SetWorkSpace(const nsACString & workspace)
{
     nsresult rv=nsBrowserListener::SetWorkSpace(workspace);
     if (NS_FAILED(rv)) 
     {
	  return rv;
     }

	LOG<<"init nsIDOMAnalysis\n";
	nsString n;
	analyzer=do_CreateInstance("@nyapc.com/XPCOM/nsDOMWrapper;1", &rv);
	if (NS_FAILED(rv))
	{
		std::cout<<"Get DOM analysis Error:"<<std::hex<<rv<<std::endl;
	}

	LOG<<"Set property for analyzer\n";
	analyzer->SetProperty(property);
	analyzer->LoadConfig();

     nsString comName;


     //create urloutput com
     property->GetStringProperty(URL_IO_COM,comName);

     std::cout<<"outcom:"<<NS_ConvertUTF16toUTF8(comName).get()<<std::endl;

     rv = servMan->GetServiceByContractID(NS_ConvertUTF16toUTF8(comName).get(), NS_GET_IID(nsIUrlIO), getter_AddRefs(urlSrc)); 

     if (NS_FAILED(rv))
     {
 	  std::cout<<"Get  nsIUrlIO Error:"<<std::hex<<rv<<std::endl;
	  return rv;
     }
     nsString value;
     property->GetStringProperty(URL_SOURCE,value);
     std::cout<<"urltarget:"<<NS_ConvertUTF16toUTF8(value).get()<<std::endl;
     PRUint16 type;
     urlSrc->GetType(&type);
     if(type==nsIUrlIO::LOCAL_FILE)
     {
	  nsCString urlfile(mWorkspace);
	  urlfile.Append(NS_ConvertUTF16toUTF8(value));

	  rv=urlSrc->SetLocation(urlfile);
     }else
     {
	  rv=urlSrc->SetLocation(NS_ConvertUTF16toUTF8(value));
     }
     
     if (NS_FAILED(rv)) 
     {
	  return rv;
     }
     timeOut->InitWithCallback(this, 300, 0);
     return NS_OK;
}

NS_IMETHODIMP nsPageCrawListener::Excute(nsIWebNavigation *nav)
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
		analyzer->SetCurUrl(mUrl);
		PRUint32 type;
		analyzer->Analysis(domhtml,&type);
	 
	  Update(LINK_STAT_GET);
     }else
     {
	  Update(LINK_STAT_ERROR);
     }
     bodyCheckCount=0;
     return rv;
}
