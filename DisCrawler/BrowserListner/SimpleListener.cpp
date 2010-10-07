#include "SimpleListener.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMNode.h"
#include "nsXPCOMGlue.h"
#include "nsIDOMDocument.h"
#include "nsIDOMElement.h"
#include "nsNetUtil.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMDocument.h"
#include "nsIDOMHTMLElement.h"
#include "nsIWebProgress.h"
#include "nsIDOMWindow.h"
#include "nsIXpathUtil.h"
#include "nsISupportsArray.h"
#include "property.h"
#include <iostream>
#include <stdlib.h>

/* Implementation file */
NS_IMPL_ISUPPORTS4(nsSimpleListener,
		   nsIWebProgressListener,
		   nsISupportsWeakReference,
		   nsIListenerSetter,
		   nsITimerCallback)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsSimpleListener)

static nsModuleComponentInfo components[] =
{
     {
	  NS_SIMPLELISTENER_CLASSNAME, 
	  NS_SIMPLELISTENER_CID,
	  NS_SIMPLELISTENER_CONTRACTID,
	  nsSimpleListenerConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsSimpleListenerModule", components)
/** 
 * @brief When timeout the Timer call this function.
 * 
 * @param timer The Navigate timer,watch the document load.
 * 
 * @return 
 */
NS_IMETHODIMP nsSimpleListener::Notify(nsITimer  *timer)
{
     if(bodyCheckCount>0)
	  statMan->ChangeStat(lid, nsIStatManager::FINISH);
     else
	  statMan->ChangeStat(lid, nsIStatManager::TIME_OUT_ERROR);
}
bool nsSimpleListener::HasBody(nsIDOMHTMLDocument *html)
{
     nsCOMPtr<nsIDOMHTMLElement> ele;
     if(html!=nsnull)
     {
	  nsresult rv=html->GetBody(getter_AddRefs(ele));
	  if (!NS_FAILED(rv)&&ele!=nsnull)
	  {
	       nsString tag;
	       ele->GetTagName(tag);
	       std::string stag(NS_ConvertUTF16toUTF8(tag).get());
	       if(stag=="BODY")
	       {
		    nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
		    if (NS_FAILED(rv))
		    {
			 return false;
		    }
		    xpathUtil->SetDocument(html);
		    
		    nsCString xpath("/html/body//*");
		    nsCOMPtr<nsISupportsArray> nodes(nsnull);
		    xpathUtil->GetNodes(xpath,getter_AddRefs(nodes));
		    if(nodes!=nsnull)
		    {
			 PRUint32 arrlen=0;
			 nodes->Count(&arrlen);
			 if(arrlen>10)
			      return true;
			 
		    }
	       }else if(stag=="FRAMESET")
	       {
		    nsCOMPtr<nsISupportsArray> docArr=do_CreateInstance(NS_SUPPORTSARRAY_CONTRACTID,&rv);
		    if (NS_FAILED(rv))
		    {
			 LOG<<"Create Array Error:"<<std::hex<<rv<<std::endl;
			 return false;
		    }
		    
		    domUtil->GetALLDocumentArray(html, docArr);
		    
		    PRUint32 docCount;
		    docArr->Count(&docCount);
		    PRUint32 eleCount=0;
		    for(int i=0;i<docCount;i++)
		    {
			 nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
			 if (NS_FAILED(rv))
			 {
			      return false;
			 }
			 nsCOMPtr<nsISupports> docSup;
			 docArr->GetElementAt(i,getter_AddRefs(docSup));
			 nsCOMPtr<nsIDOMDocument> tmpdoc = do_QueryInterface(docSup);
			 
			 if(tmpdoc!=nsnull)
			 {
			      xpathUtil->SetDocument(tmpdoc);
		    
			      nsCString xpath("/html/body//*");
			      nsCOMPtr<nsISupportsArray> nodes(nsnull);
			      xpathUtil->GetNodes(xpath,getter_AddRefs(nodes));
			      if(nodes!=nsnull)
			      {
				   PRUint32 arrlen=0;
				   nodes->Count(&arrlen);
				   eleCount+=arrlen;
			      }
			 }
		    }
		    if(eleCount>10)
			 return true;

	       }
	  }
	  
     }
     return false;

}

nsSimpleListener::nsSimpleListener()
     :WinStop(true),
      docStop(true),
      bodyCheckCount(0)
{
     nsresult rv;
     timeOut=do_CreateInstance("@mozilla.org/timer;1", &rv);
     if (NS_FAILED(rv)) 
     {
	  LOG<<"Get Timmer Error:"<<rv<<std::endl;
     }
     domUtil=do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1",&rv);
     if (NS_FAILED(rv))
     {
          LOG<<"nsDomAttUtil inti erroe!\n";;
     }
}
nsSimpleListener::~nsSimpleListener()
{
}

NS_IMETHODIMP nsSimpleListener::OnStateChange(nsIWebProgress* aWebProgress, nsIRequest* aRequest, PRUint32 aFlag, PRUint32 aStatus)
{
     LOG<<std::dec<<"id:"<<lid<<"flag"<<aFlag<<"stat"<<std::hex<<aStatus<<std::endl;
     nsresult rv=NS_OK;
     if(aFlag&STATE_IS_REQUEST&&aFlag&STATE_IS_DOCUMENT&&(aFlag&STATE_TRANSFERRING||aFlag&STATE_REDIRECTING||aFlag&STATE_START))
     {
	  docStop=false;
	  WinStop=false;
	  return rv;
     }
     if(aFlag&STATE_STOP)
     {
	  LOG<<"stop stat...\n";
	  nsCOMPtr<nsIDOMWindow> domwin;
	  aWebProgress->GetDOMWindow(getter_AddRefs(domwin));
	  
	  if(aFlag&STATE_IS_DOCUMENT)
	  {
	       docStop=true;
	  }
	  if(aFlag&STATE_IS_WINDOW)
	  {
	       WinStop=true;
	  }
	  if(aStatus==0||aStatus==0x804b0002)
	  {
	       if(docStop&&WinStop)
	       {
		    nsresult rv=NS_OK;
		    nsCOMPtr<nsIDOMDocument> domdoc;
		    rv=domwin->GetDocument(getter_AddRefs(domdoc));
		    if (NS_FAILED(rv))
		    {
			 std::cout<<"Get domnode Error:"<<std::hex<<rv<<std::endl;
			 return rv;
		    }
		    if(domdoc!=nsnull)
		      {
			domdoc->Normalize();
			nsCOMPtr<nsIDOMHTMLDocument> domhtml=do_QueryInterface(domdoc);
			nsString nsUrl;
			domhtml->GetURL(nsUrl);
		     
			bool hasb=HasBody(domhtml);
			if(hasb)
			  {
			    bodyCheckCount++;
			    if(bodyCheckCount>3)
			      statMan->ChangeStat(lid, nsIStatManager::FINISH);
			    else
			      {
				statMan->ChangeStat(lid, nsIStatManager::FIN_DOC);
			      }
			  }
		      }
	       }
	       
	  }else if(aStatus==0x8000ffff||aStatus==0x804b001e||aStatus==0x804b000e)
	  {
	       statMan->ChangeStat(lid, nsIStatManager::NETWORK_ERROR);
	  }
     }
     timeOut->Cancel();
     timeOut->InitWithCallback(this, 60000, 0);	  
     return rv;
}
NS_IMETHODIMP nsSimpleListener::OnProgressChange(nsIWebProgress* webProgress , nsIRequest* request , PRInt32 curSelfProgress , PRInt32 maxSelfProgress , PRInt32 curTotalProgress , PRInt32 maxTotalProgress ) 
{
     return NS_OK;
}
NS_IMETHODIMP nsSimpleListener::OnLocationChange(nsIWebProgress* aWebProgress, nsIRequest* aRequest, nsIURI* location)
{ 
     return NS_OK;
}
NS_IMETHODIMP nsSimpleListener::OnStatusChange(nsIWebProgress* aWebProgress, nsIRequest* aRequest, PRUint32 status, unsigned short const* msgh)
{ 
     return NS_OK;
}
NS_IMETHODIMP nsSimpleListener::OnSecurityChange(nsIWebProgress* aWebProgress, nsIRequest* aRequest, unsigned int state)
{ 

     return NS_OK;
}

/* void SetStatManager (in nsIStatManager id); */
NS_IMETHODIMP nsSimpleListener::SetStatManager(nsIStatManager *man)
{
     statMan=man;
     return NS_OK;
}

/* void SetId (in long id); */
NS_IMETHODIMP nsSimpleListener::SetId(PRInt32 id)
{
     lid=id;
     return NS_OK;
}
