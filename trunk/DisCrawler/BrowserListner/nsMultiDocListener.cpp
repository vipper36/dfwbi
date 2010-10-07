#include "nsMultiDocListener.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMNode.h"
#include "nsXPCOMGlue.h"
#include "nsIDOMDocument.h"
#include "nsIWebNavigation.h"
#include "nsIDOMElement.h"
#include "nsNetUtil.h"
#include "nsIDOMDocument.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMHTMLElement.h"
#include "nsIDOMHTMLCollection.h"
#include "nsIDOM3Document.h"
#include "nsIDOMSerializer.h"
#include "nsParserCIID.h"
#include "nsIDOMParser.h"
#include "property.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
/* Implementation file */

NS_GENERIC_FACTORY_CONSTRUCTOR(nsMultiDocListener)

static nsModuleComponentInfo components[] =
{
     {
	  NS_MULTIDOCLISTENER_CLASSNAME, 
	  NS_MULTIDOCLISTENER_CID,
	  NS_MULTIDOCLISTENER_CONTRACTID,
	  nsMultiDocListenerConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsMultiDocListenerModule", components)

nsMultiDocListener::nsMultiDocListener()
:nsBrowserListener(),
     bodyCheckCount(0),
     task(nsnull),
     curIndex(0),
     Uid(0)
{
     nsresult rv;
     
     inter=do_CreateInstance("@nyapc.com/XPCOM/nsSoapInter;1",&rv);
     if (NS_FAILED(rv)) 
     {
	  LOG<<"Init Soap Inter error\n";
     }
     parser=do_CreateInstance(NS_DOMPARSER_CONTRACTID,&rv );
     if (NS_FAILED(rv))
     {
	  LOG<<"Init Parser error\n";
     }
     taskstream<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
     
}

NS_IMETHODIMP nsMultiDocListener::GetUrl(nsACString &url)
{
     if(task==nsnull)
     {
	  LOG<<"Crawler ID:"<<cid<<"num:"<<MaxAccCount<<"\n";
	  inter->GetTask(cid,MaxAccCount,getter_AddRefs(task));
	  if(task!=nsnull)
	  {
	       PRInt32 taskid=-1;
	       task->GetTaskId(&taskid);
	       
	       if(taskid>=0)
	       {
		    nsCString jobtype;
		    task->GetType(jobtype);
		    
		    taskstream<<"<Task id=\""<<taskid;
		    taskstream<<"\" type=\""<<jobtype.get()<<"\">";
		    
	       }
	       
	       PRInt32 wrapid;
	       task->GetWrapid(&wrapid);
	  
	       LOG<<"wrapid:"<<wrapid<<"\n";
	       inter->GetWrapper(wrapid,Wrapper);
	       LOG<<"wrapper:"<<Wrapper.get()<<"\n";
	  }
	  
     }
     if(task!=nsnull)
     {
	  PRInt32 len;
	  task->GetUrlCount(&len);
	  LOG<<"urlcount:"<<len<<"curIndex:"<<curIndex<<"\n";
	  if(curIndex<len)
	  {
	       nsCString aurl;
	       
	       task->GetUrlByIndex(curIndex,&Uid,aurl);
	       LOG<<"cur UID:"<<Uid<<"url:"<<aurl.get()<<"\n";
	       url=aurl;
	       curIndex++;
	       
	  }
	  else
	  {
	       if(len>0)
	       {
		    
		    taskstream<<"</Task>";
		    nsCString retStr(taskstream.str().c_str());
		    LOG<<"result:"<<retStr.get()<<"\n";
		    PRBool ret;
		    inter->PutResult(retStr,cid,&ret);
		    return NS_OK;
	       }
	  }
     }
     
     return NS_OK;
}


NS_IMETHODIMP nsMultiDocListener::Excute(nsIWebNavigation *nav)
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
     nsString nsUrl;
     domhtml->GetURL(nsUrl);
     
     bool hasb=HasBody(domhtml);
     if(!hasb&&bodyCheckCount<3)
     {
	  bodyCheckCount++;
	  return NS_ERROR_FAILURE;
     }
     else if(hasb)
     {
	  if(Wrapper.Length()>0)
	  {
	       
	       LOG<<"Start Fetch.....\n";
	       nsCOMPtr<nsIXSLTFetcher> fetcher=do_CreateInstance("@nyapc.com/XPCOM/nsXSLTFetcher;1",&rv);
	       if (NS_FAILED(rv)) 
	       {
		    LOG<<"Init Fetcher error!\n";
		    return rv;
	       }
	  
	       rv=fetcher->SetXsltDocStr(Wrapper);
	       if (NS_FAILED(rv)) 
	       {
		    LOG<<"Set Wrapper error!\n";
		    return rv;
	       }
	       rv=fetcher->SetDocument(domdoc);
	       if (NS_FAILED(rv)) 
	       {
		    LOG<<"Set Document error!\n";
		    return rv;
	       }
	       std::stringstream ss;
	       nsCString nsUidName("urlid");
	       nsCString nsUrlName("docurl");
	       ss<<Uid;
	       nsCString nsUidValue(ss.str().c_str());
	       LOG<<"uid:"<<Uid<<"url:"<<NS_ConvertUTF16toUTF8(nsUrl).get()<<"\n";
	       rv=fetcher->SetXsltParam(nsUidName,nsUidValue);
	       if (NS_FAILED(rv)) 
	       {
		    LOG<<"Set Param error!\n";
		    return rv;
	       }
	       rv=fetcher->SetXsltParam(nsUrlName,NS_ConvertUTF16toUTF8(nsUrl));
	       if (NS_FAILED(rv)) 
	       {
		    LOG<<"Set Param error!\n";
		    return rv;
	       }
	  
	       nsCString result;
	       rv=fetcher->GetResultXML(result);
	       if (NS_FAILED(rv)) 
	       {
		    return rv;
	       }
	       std::string resultStr(result.get());
	       std::string head("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	       std::size_t pos=resultStr.find(head);
	       if(pos!=std::string::npos)
	       {
		    taskstream<<resultStr.substr(head.length());
	       }
	       else
		    taskstream<<resultStr;
	  }	  
     }else
     {
	  bodyCheckCount=0;
	  return NS_ERROR_FAILURE;
	  
     }
}
