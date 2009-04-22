#include "BrowserListener.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMNode.h"
#include "nsXPCOMGlue.h"
#include "nsIDOMDocument.h"
#include "nsIWebNavigation.h"
#include "nsIDOMElement.h"
#include "nsStringAPI.h"
#include "ILayoutAnalysis.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMDocument.h"
#include <iconv.h>
#include <iostream>

/* Implementation file */
NS_IMPL_ISUPPORTS3(nsBrowserListener,
		   nsIBrowserConnector,
		   nsIWebProgressListener,
		   nsISupportsWeakReference)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsBrowserListener)

static nsModuleComponentInfo components[] =
{
     {
	  NS_BROWSERLISTENER_CLASSNAME, 
	  NS_BROWSERLISTENER_CID,
	  NS_BROWSERLISTENER_CONTRACTID,
	  nsBrowserListenerConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsBrowserListenerModule", components)

NS_IMETHODIMP nsBrowserListener::SetBrowser(nsIWebBrowser * aBrowser)
{
     mBro=aBrowser;
     return NS_OK;
}
nsBrowserListener::nsBrowserListener():mBro(nsnull)
{
     nsresult rv = NS_GetServiceManager(getter_AddRefs(servMan));
     if (NS_FAILED(rv))
     {
          std::cout<<"Get manager Error:"<<rv<<std::endl;
     }
     rv = servMan->GetServiceByContractID("@nyapc.com/XPCOM/nsUrlCollector;1", NS_GET_IID(nsIUrlCollector), getter_AddRefs(urls)); 
     if (NS_FAILED(rv))
     {
 	  std::cout<<"Get listener  Error:"<<std::hex<<rv<<std::endl;
     }
}

NS_IMETHODIMP nsBrowserListener::OnStateChange(nsIWebProgress* aWebProgress, nsIRequest* aRequest, PRUint32 aFlag, PRUint32 aStatus)
{ 
     nsresult rv;
     if(aFlag&STATE_STOP&&aFlag&STATE_IS_DOCUMENT)
     {
	  std::cout<<"aflag:"<<aFlag<<"status:"<<aStatus<<std::endl;
	  // if(aStatus==0)
// 	  {
// 	       std::cout<<"add the component to deal with document"<<std::endl;
// 	       nsCOMPtr<ILayoutAnalysis> ana;
// 	       rv = servMan->GetServiceByContractID("@nyapc.com/XPCOM/LayoutAnalysis;1", NS_GET_IID(ILayoutAnalysis), getter_AddRefs(ana)); 
// 	       if (NS_FAILED(rv))
// 	       {
// 		    std::cout<<"Get Layout analysis  Error:"<<std::hex<<rv<<std::endl;
// 	       }
 	       nsCOMPtr<nsIWebNavigation> nav = do_QueryInterface(mBro);
// 	       nsCOMPtr<nsIDOMDocument> domdoc;
// 	       rv=nav->GetDocument(getter_AddRefs(domdoc));
// 	       if (NS_FAILED(rv))
// 	       {
// 		    std::cout<<"Get domnode Error:"<<std::hex<<rv<<std::endl;
// 	       }
// 	       nsCOMPtr<nsIDOMHTMLDocument> domhtml=do_QueryInterface(domdoc);
// 	       ana->SetDocument(domhtml);
// 	       ana->ShowLayout();
// 	  }
// 	  else
// 	  {
// 	       std::cout<<"add error deal component"<<std::endl;
// 	  }
	  nsCString aurl;
	  urls->GetURL(aurl);
	  std::cout<<ToNewCString(aurl)<<std::endl;
	  if(aurl.Length()>0)
	  {
	       rv = nav->LoadURI(NS_ConvertUTF8toUTF16(aurl).get(),nsIWebNavigation::LOAD_FLAGS_NONE, nsnull, nsnull, nsnull);
	       if (NS_FAILED(rv)) {
		    printf("LoadURI\n");
	       }
	  }
	  
     }
     return NS_OK;
}
NS_IMETHODIMP nsBrowserListener::OnProgressChange(nsIWebProgress* webProgress , nsIRequest* request , PRInt32 curSelfProgress , PRInt32 maxSelfProgress , PRInt32 curTotalProgress , PRInt32 maxTotalProgress ) 
{
     //printf("progress");
     return NS_OK;
}
NS_IMETHODIMP nsBrowserListener::OnLocationChange(nsIWebProgress* aWebProgress, nsIRequest* aRequest, nsIURI* location)
{ 
     //  printf("location");
     return NS_OK;
}
NS_IMETHODIMP nsBrowserListener::OnStatusChange(nsIWebProgress* aWebProgress, nsIRequest* aRequest, PRUint32 status, unsigned short const* msg)
{ 
     // printf("status");
     return NS_OK;
}
NS_IMETHODIMP nsBrowserListener::OnSecurityChange(nsIWebProgress* aWebProgress, nsIRequest* aRequest, unsigned int state)
{ 

//     printf("security");
     return NS_OK;
}
