#include "BrowserListener.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMNode.h"
#include "nsXPCOMGlue.h"
#include "nsIDOMDocument.h"
#include "nsIWebNavigation.h"
#include "nsIDOMElement.h"
#include "nsNetUtil.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMDocument.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMHTMLElement.h"
#include "nsIWebProgress.h"
#include "nsIBaseWindow.h"
#include "nsIScrollable.h"
#include "nsIDOMMouseEvent.h"
#include "nsIDOMDocumentView.h"
#include "nsIDOMAbstractView.h"
#include "nsIDOMEventTarget.h"
#include "nsIDOMDocumentEvent.h"
#include "nsIDOMNodeList.h"
#include "nsIDOMHTMLIFrameElement.h"
#include "nsIDOMHTMLFrameElement.h"
#include "property.h"
#include <iostream>
#include <stdlib.h>

/* Implementation file */
NS_IMPL_ISUPPORTS4(nsBrowserListener,
		   nsIBrowserConnector,
		   nsIWebProgressListener,
		   nsISupportsWeakReference,
		   nsITimerCallback)

/** 
 * @brief When timeout the Timer call this function.
 * 
 * @param timer The Navigate timer,watch the document load.
 * 
 * @return 
 */
NS_IMETHODIMP nsBrowserListener::Notify(nsITimer  *timer)
{
     LOG<<"timmer start:"<<running<<"count"<<timeCount<<"isScroll"<<isScrolled<<"\n";
     LOG<<"doc flag:"<<docStop<<" win flag"<<WinStop<<"\n";
     int breTime=(int)(interTime*(float)1000);
     if(running==NOT_RUN)
     {
	  if(brwStop)
	  {
	       LOG<<"stop browser set!\n";
	       timer->Cancel();
	       exit(1);
	  }else
	  {
	       if(docStop&&WinStop)
	       {
		    LOG<<"doc  fetched!\n";
		    if(scroolWait>0&&!isScrolled)
		    {
			 ScrollWin();
			 SetRunning(RUNNING);
			 isScrolled=true;
			 breTime=scroolWait*1000;
		    }else
		    {
			 //Init event stat.
			 SetEventWait(false);
			      
			 nsCOMPtr<nsIWebNavigation> nav = do_QueryInterface(mBro);
			 if(!browError)
			 {
			      //redirect the browser to the target
			      ReDirect(nav);
			      if(!isred)
			      {
				   Excute(nav);			      
			      }
			 }
			 //if the evenWait has set, do not change the web site.
			 if(evenWait||isred)
			 {
			      SetRunning(RUNNING);
			      breTime=1000;
			 }else
			 {
			      nsCString tmpUrl;
			      GetUrl(tmpUrl);
			      LOG<<tmpUrl.get()<<"\n";
			      
			      if(tmpUrl.Length()>0)
			      {
				   //init running stat and scrool stat.
				   SetRunning(RUNNING);
				   isScrolled=false;
				   //navigate the web site.
				   WebNav(nav,tmpUrl);
			      }else
			      {
				   StopBrows();
			      }
			 }
		    }    
	       }else
	       {
		    LOG<<"waite count set!\n";
		    if(timeCount>3)
		    {
			 docStop=true;
			 WinStop=true;
			 timeCount=0;
		    }else
		    {
			 timeCount++;
		    }
	       }
	  }
     }else
     {
	  LOG<<"set not run!\n";
	  timeCount=0;
	  SetRunning(NOT_RUN);
	  breTime=6000;
     }
     timeOut->Cancel();

     LOG<<"timmer stop:"<<running<<"inter time:"<<breTime<<"\n";
     timeOut->InitWithCallback(this, breTime, 0);


     return NS_OK;
}
void nsBrowserListener::SetEventWait(bool ew)
{
     evenWait=ew;
}
/** 
 * @brief Send a mouse click event to the element.
 * 
 * @param ele the element which has a "onclick" event.
 * @param doc The owner document.
 * 
 * @return 
 */
NS_IMETHODIMP nsBrowserListener::SendEvent(nsIDOMElement* ele,nsIDOMDocument *doc)
{
     nsresult rv;
     nsCOMPtr<nsIDOMDocumentView> docView =do_QueryInterface(doc); 
     nsCOMPtr<nsIDOMDocumentEvent> docEvent = do_QueryInterface(doc);
     nsCOMPtr<nsIDOMAbstractView> view;        
     docView->GetDefaultView(getter_AddRefs(view)); 
     nsCOMPtr<nsIDOMEvent> event;
     docEvent->CreateEvent(NS_LITERAL_STRING("MouseEvents"),getter_AddRefs(event));
     nsCOMPtr<nsIDOMMouseEvent> mouseEvt=do_QueryInterface(event,&rv); 
     mouseEvt->InitMouseEvent(NS_LITERAL_STRING("click"),PR_TRUE,PR_TRUE,view,0,0,0,0,0,PR_FALSE,PR_FALSE,PR_FALSE,PR_FALSE,1,nsnull); 
     nsCOMPtr<nsIDOMEventTarget> evtTarget=do_QueryInterface(ele);
     PRBool clickStatus;
     evtTarget->DispatchEvent(mouseEvt,&clickStatus);
     return NS_OK;
}
/** 
 * @brief Set the Vertical scroll to the max position.
 * 
 */
NS_IMETHODIMP nsBrowserListener::ScrollWin()
{
     nsCOMPtr<nsIScrollable> scoll= do_QueryInterface(mBro);
     PRInt32 minPos,maxPos;
     nsresult rv=scoll->GetScrollRange(nsIScrollable::ScrollOrientation_Y,&minPos,&maxPos);
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     rv= scoll->SetCurScrollPos(nsIScrollable::ScrollOrientation_Y,maxPos);
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     LOG<<"Scroll the browser!\n";
     return NS_OK;
}
NS_IMETHODIMP nsBrowserListener::SetBrowser(nsIWebBrowser * aBrowser)
{
     mBro=aBrowser;
     Notify(timeOut);
     return NS_OK;
}
void nsBrowserListener::GetHost(const nsCString &url,nsCString &host)
{
     nsCOMPtr<nsIURI> uri(nsnull);
     iio->NewURI(url,nsnull,nsnull,getter_AddRefs(uri)); 
     if (uri==nsnull)
     {
	  return;
     }
     uri->GetHost(host);     
}
void nsBrowserListener::SetCookie(const nsCString &cookie)
{
     nsCOMPtr<nsIURI> cookieUri(nsnull);
     iio->NewURI(aurl,nsnull,nsnull,getter_AddRefs(cookieUri));
     if (cookieUri==nsnull)
     {
	  return;
     }
     std::string strCookie(cookie.get());
     size_t index=0;
     do
     {
	  size_t curr=index;
	  index=strCookie.find(";",curr);
	  if(index!=std::string::npos)
	  {
	       index++;
	       std::string tmpCook=strCookie.substr(curr,index-curr);
	       LOG<<"tmpcook:"<<tmpCook<<"\n";
	       cookServ->SetCookieString(cookieUri, nsnull, tmpCook.c_str(), nsnull);
	  }
     }while(index!=std::string::npos);
}
bool nsBrowserListener::HasBody(nsIDOMHTMLDocument *html)
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
	       LOG<<"body:"<<stag<<"\n";
	       if((stag!="BODY")&&(stag!="FRAMESET"))
	       {
		    return false;
	       }
	       PRBool hsc=false ;
	       ele->HasChildNodes(&hsc);
	       return hsc;
	  }
     }
     return false;

}
/* void SetInterrupt (in double inter); */
NS_IMETHODIMP nsBrowserListener::SetInterrupt(double inter)
{
     interTime=inter;
     return NS_OK;
}

/* void SetDefDoc (in long num); */
NS_IMETHODIMP nsBrowserListener::SetDefDoc(PRInt32 num)
{
     MaxAccCount=num;
     return NS_OK;
}

/* void SetID (in long id); */
NS_IMETHODIMP nsBrowserListener::SetID(PRInt32 id)
{
     cid=id;
     
     return NS_OK;
}
NS_IMETHODIMP nsBrowserListener::WebNav(nsIWebNavigation *nav,const nsACString &url)
{
     nsresult rv;
     aurl=url;
     LOG<<"acess:"<<aurl.get()<<"\n";
     if(aurl.Length()>0)
     {

	  GetHost(aurl,mTarDomain);
	  LOG<<"domain:"<<mTarDomain.get()<<"\n";
	  if(cookie.Length()>0)
	       SetCookie(cookie);

	  rv = nav->LoadURI(NS_ConvertUTF8toUTF16(aurl).get(),nsIWebNavigation::LOAD_FLAGS_STOP_CONTENT, nsnull, nsnull, nsnull);
	  if (NS_FAILED(rv)) {
	       return rv;
	  }
     }
     return NS_OK;
}
nsBrowserListener::nsBrowserListener()
     :mBro(nsnull),
      running(NOT_RUN),
      brwStop(false),
      WinStop(true),
      docStop(true),
      NetStop(true),
      browError(true),
      interTime(0.3),
      timeCount(0),
      isScrolled(false),
      scroolWait(-1),
      evenWait(false),
      LastDoc(nsnull),
      isred(false),
      cid(0),
      MaxAccCount(20)
{
     
     nsresult rv = NS_GetServiceManager(getter_AddRefs(servMan));
     if (NS_FAILED(rv))
     {
          std::cout<<"Get manager Error:"<<rv<<std::endl;
     }
     rv=servMan->GetServiceByContractID("@mozilla.org/network/io-service;1", NS_GET_IID(nsIIOService), getter_AddRefs(iio));
     
     if (NS_FAILED(rv))
     {
	  std::cout<<"Get ioservice  Error:"<<std::hex<<rv<<std::endl;
     }
     
     timeOut=do_CreateInstance("@mozilla.org/timer;1", &rv);
     if (NS_FAILED(rv)) 
     {
	  std::cout<<"Get Timmer Error:"<<rv<<std::endl;
     }
     rv=servMan->GetServiceByContractID("@mozilla.org/cookieService;1",  NS_GET_IID(nsICookieService),getter_AddRefs(cookServ));
     if (NS_FAILED(rv)) 
     {
	  std::cout<<"Get nsicookieservice Error:"<<rv<<std::endl;
     }
}
nsBrowserListener::~nsBrowserListener()
{
}
void nsBrowserListener::StopBrows()
{
     //exit 退出
     LOG<<"Exit browser!\n";     
     brwStop=true;
}

void nsBrowserListener::SetRunning(PRUint16 stat)
{
     LOG<<"setting----------\n";
     running=stat;
}

void nsBrowserListener::SetCurrentUrl(const nsACString &url)
{
     aurl=url;
}
NS_IMETHODIMP nsBrowserListener::OnStateChange(nsIWebProgress* aWebProgress, nsIRequest* aRequest, PRUint32 aFlag, PRUint32 aStatus)
{
     nsresult rv=NS_OK;
     PRBool isLoading;
     std::cout<<std::dec<<"flag"<<aFlag<<"stat"<<std::hex<<aStatus<<std::endl;
     if(running==NOT_RUN)
     {
	  if(!docStop||!WinStop)
	       SetRunning(RUNNING);
     }
//     std::cout<<std::dec<<"flag"<<aFlag<<"stat"<<std::hex<<aStatus<<"running:"<<running<<std::endl;
     if(aFlag&STATE_IS_REQUEST&&aFlag&STATE_IS_DOCUMENT&&(aFlag&STATE_TRANSFERRING||aFlag&STATE_REDIRECTING||aFlag&STATE_START))
     {
	  LOG<<"set flag\n";
	  docStop=false;
	  WinStop=false;
//	  NetStop=false;
     	return rv;
     }
     if(aFlag&STATE_STOP)
     {
	  nsCOMPtr<nsIWebNavigation> nav= do_QueryInterface(mBro);

	  if(aFlag&STATE_IS_DOCUMENT)
	  {
	       	  LOG<<"set doc flag\n";
	       docStop=true;
	  }
	  if(aFlag&STATE_IS_WINDOW)
	  {
	       	  LOG<<"set win flag\n";
	       WinStop=true;
	  }
	  if(aStatus==0||aStatus==0x804b0002)
	  {
	       browError=false;
	  }
	  else if(aStatus==0x8000ffff||aStatus==0x804b001e)
	  {
	       browError=true;
	  }
     	timeOut->Cancel();
     	timeOut->InitWithCallback(this, 100, 0);	  
     }
     return rv;
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
void nsBrowserListener::GetProperty(nsIPersistentProperties **prop,nsACString &fileName)
{
  nsresult rv;
  nsCOMPtr<nsIPersistentProperties> tmpprop=do_CreateInstance("@mozilla.org/persistent-properties;1", &rv);
  if (NS_FAILED(rv)) 
    {
      LOG<<"Get properties Error:"<<rv<<"\n";
    }
  nsCOMPtr<nsILocalFile> file;
  rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16(fileName), PR_FALSE,
				   getter_AddRefs(file));
  if (NS_FAILED(rv))
    return ;
  nsCOMPtr<nsIInputStream> fistream;
  rv=NS_NewLocalFileInputStream(getter_AddRefs(fistream), file);
  if (NS_FAILED(rv)) 
    {
      return ; 
    }
  tmpprop->Load(fistream);
  *prop=tmpprop;
  NS_ADDREF(*prop);
}
NS_IMETHODIMP  nsBrowserListener::ReleaseDoc(nsIWebNavigation *nav)
{
     nsCOMPtr<nsIDOMDocument> domdoc;
     nsresult rv=nav->GetDocument(getter_AddRefs(domdoc));
     if (NS_FAILED(rv))
     {
	  LOG<<"Get domnode Error:"<<std::hex<<rv<<"\n";
	  return rv;
     }
     if(LastDoc!=nsnull&&LastDoc!=domdoc)
     {
	  LOG<<"release doc start\n";
	  nsCOMPtr<nsIDOMHTMLDocument> htmldoc=do_QueryInterface(LastDoc);
	  htmldoc->Close();
//	  LastDoc->Release();
     }
     LastDoc=domdoc;
     LOG<<"release doc end\n";
     return NS_OK;
}

NS_IMETHODIMP  nsBrowserListener::ReDirect(nsIWebNavigation *nav)
{
     if(isred)
	  isred=false;
     else
     {
	  LOG<<"redirect:"<<red.get()<<"\n";
	  if(red.Length()>0)
	  {
	       nsCOMPtr<nsIDOMDocument> domdoc;
	       nsresult rv=nav->GetDocument(getter_AddRefs(domdoc));
	       if (NS_FAILED(rv))
	       {
		    LOG<<"Get domnode Error:"<<std::hex<<rv<<"\n";
		    return rv;
	       }
	       nsCOMPtr<nsIDOMElement> domele;
	       domdoc->GetDocumentElement(getter_AddRefs(domele));
	       nsCOMPtr<nsIDOMNode> nodee=do_QueryInterface(domele);
	       nsCString reurlStr;
	       std::string redstr(red.get());
	       if(redstr=="iframe")
	       {
		    nsString tag=NS_ConvertUTF8toUTF16("iframe");
		    nsCOMPtr<nsIDOMNodeList> dli;
		    domdoc->GetElementsByTagName(tag,getter_AddRefs(dli));
		    PRUint32 len=1;
		    dli->GetLength(&len);
		    if(len>0)
		    {
			 nsCOMPtr<nsIDOMNode> node;
			 dli->Item(0,getter_AddRefs(node));
			 nsCOMPtr<nsIDOMHTMLIFrameElement> frame=do_QueryInterface(node);
			 nsString reurl;
			 frame->GetSrc(reurl);
			 reurlStr=NS_ConvertUTF16toUTF8(reurl);
		    }
	       }else if(redstr=="frame")
	       {
		    nsString tag=NS_ConvertUTF8toUTF16("frame");
		    nsCOMPtr<nsIDOMNodeList> dli;
		    domdoc->GetElementsByTagName(tag,getter_AddRefs(dli));
		    PRUint32 len=1;
		    dli->GetLength(&len);
		    if(len>0)
		    {
			 nsCOMPtr<nsIDOMNode> node;
			 dli->Item(0,getter_AddRefs(node));
			 nsCOMPtr<nsIDOMHTMLFrameElement> frame=do_QueryInterface(node);
			 nsString reurl;
			 frame->GetSrc(reurl);
			 reurlStr=NS_ConvertUTF16toUTF8(reurl);
		    }
	       }else
	       {
		    nsCOMPtr<nsIURI> uri;
		    nav->GetCurrentURI(getter_AddRefs(uri));
		    nsCString reurl;
		    uri->GetSpec(reurl);
		    PRUint32 len=reurl.RFind("/");
		    reurlStr.Append(reurl.get(),len+1);
		    reurlStr.Append(red);
	       }
	       if(reurlStr.Length()>0)
	       {
		    isred=true;
		    WebNav(nav,reurlStr);
	       }
	  }
     }
     return NS_OK;
}
