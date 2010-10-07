#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsXPCOMGlue.h"
#include "nsIWebBrowser.h"
#include "nsCrawStatMan.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIWebNavigation.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMElement.h"
#include "nsISoapTask.h"
#include "nsISoapInter.h"
#include "nsIXSLTFetcher.h"
#include "nsISupportsArray.h"
#include <iostream>
#include <sstream>
#include "property.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(nsCrawStatMan)

static nsModuleComponentInfo components[] =
{
     {
	  NS_CRAWSTATMAN_CLASSNAME,
	  NS_CRAWSTATMAN_CID,
	  NS_CRAWSTATMAN_CONTRACTID,
	  nsCrawStatManConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsCrawStatManModule", components)

nsCrawStatMan::nsCrawStatMan()
{
     /* member initializers and constructor code */
     nsresult rv;
     domUtil=do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1",&rv);
     if (NS_FAILED(rv))
     {
          LOG<<"nsDomAttUtil inti erroe!\n";;
     }
}

nsCrawStatMan::~nsCrawStatMan()
{
     /* destructor code */
}
void StripCtl(std::string &str)
{
     for(int i=0x01;i<0x09;i++)
     {
	  size_t index=std::string::npos;
	  do
	  {
	       index=str.find(i);
	       if(index!=std::string::npos)
	       {
		    LOG<<"strip:"<<i<<"\n";
		    str.erase(index,1);
	       }
	  }while(index!=std::string::npos);
     }
     
}
NS_IMETHODIMP nsCrawStatMan::Excute()
{
     nsresult rv;
     std::stringstream taskstream;
     PRInt32 taskid=-1;
     m_task->GetTaskId(&taskid);
	       
     nsCString jobtype;
     m_task->GetType(jobtype);
     taskstream<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
     taskstream<<"<Task id=\""<<taskid;
     taskstream<<"\" type=\""<<jobtype.get()<<"\">";
  
     nsCString Wrapper;
     PRInt32 wrapid;
     m_task->GetWrapid(&wrapid);
	  
     m_inter->GetWrapper(wrapid,Wrapper);
     for(std::map<int,nsIWebBrowser *>::iterator it=bMap.begin();it!=bMap.end();++it)
     {
	  if(sMap[it->first]<=FINISH)
	  {
	      
	       nsCOMPtr<nsIWebNavigation> nav = do_QueryInterface(it->second);
	       nsCOMPtr<nsIDOMDocument> domdoc;
	       rv=nav->GetDocument(getter_AddRefs(domdoc));
	       if (NS_FAILED(rv))
	       {
		    LOG<<"Get domnode Error:"<<std::hex<<rv<<std::endl;
		    continue;
	       }
	       nsCOMPtr<nsISupportsArray> docArr=do_CreateInstance(NS_SUPPORTSARRAY_CONTRACTID,&rv);
	       if (NS_FAILED(rv))
	       {
		    LOG<<"Create Array Error:"<<std::hex<<rv<<std::endl;
		    continue;
	       }
	       
	       domUtil->GetALLDocumentArray(domdoc, docArr);

	       PRUint32 docCount;
	       docArr->Count(&docCount);
	       LOG<<"doc count:"<<docCount<<"\n";
	       for(int i=0;i<docCount;i++)
	       {
		    nsCOMPtr<nsISupports> docSup;
		    docArr->GetElementAt(i,getter_AddRefs(docSup));
		    nsCOMPtr<nsIDOMDocument> tmpdoc = do_QueryInterface(docSup);

		    if(tmpdoc!=nsnull)
		    {
			 
			 nsCOMPtr<nsIDOMHTMLDocument> domhtml=do_QueryInterface(tmpdoc);
			 nsCOMPtr<nsIDOMElement> ele;
			 domhtml->GetDocumentElement(getter_AddRefs(ele));
			 nsCOMPtr<nsIDOMNSHTMLElement> docEle=do_QueryInterface(ele);
			 nsString inHtml;
			 docEle->GetInnerHTML(inHtml);
			 LOG<<"heml:"<<NS_ConvertUTF16toUTF8(inHtml).get()<<"\n";
			 nsString nsUrl;
			 domhtml->GetURL(nsUrl);
		    
			 nsCOMPtr<nsIXSLTFetcher> fetcher=do_CreateInstance("@nyapc.com/XPCOM/nsXSLTFetcher;1",&rv);
			 if (NS_FAILED(rv)) 
			 {
			      LOG<<"Init Fetcher error!\n";
			      return rv;
			 }
			 LOG<<"wrapper:"<<Wrapper.get()<<"\n";
			 rv=fetcher->SetXsltDocStr(Wrapper);
			 LOG<<"------------------------------1\n";
			 if (NS_FAILED(rv)) 
			 {
			      LOG<<"Set Wrapper error!\n";
			      return rv;
			 }
			 rv=fetcher->SetDocument(tmpdoc);
			 LOG<<"------------------------------2\n";
			 if (NS_FAILED(rv)) 
			 {
			      LOG<<"Set Document error!\n";
			      return rv;
			 }
			 std::stringstream ss;
			 nsCString nsUidName("urlid");
			 nsCString nsUrlName("docurl");
			 ss<<it->first;
			 nsCString nsUidValue(ss.str().c_str());
			 LOG<<"uid:"<<it->first<<"url:"<<NS_ConvertUTF16toUTF8(nsUrl).get()<<"\n";
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
			 LOG<<"------------------------------3\n";
			 nsCString result;
			 rv=fetcher->GetResultXML(result);
			 if (NS_FAILED(rv)) 
			 {
			      continue;
			 }
			 std::string resultStr(result.get());
			 LOG<<resultStr<<"\n";
			 StripCtl(resultStr);
			 std::string head("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
			 std::size_t pos=resultStr.find(head);
			 if(pos!=std::string::npos)
			 {
			      taskstream<<resultStr.substr(head.length());
			 }
			 else
			      taskstream<<resultStr;
		    }
		    
	       }
	       
	  }else
	  {
	       taskstream<<"<Result uid=\""<<it->first<<"\" error=\""<<sMap[it->first]<<"\" />";
	  }
     }
     taskstream<<"</Task>";
     nsCString retStr(taskstream.str().c_str());
     LOG<<"result:"<<retStr.get()<<"\n";
     PRBool ret;
     m_inter->PutResult(retStr,cid,&ret);
     LOG<<"Finish.....\n";
     return NS_OK;
}

