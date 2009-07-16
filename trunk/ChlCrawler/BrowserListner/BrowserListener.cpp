#include "BrowserListener.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMNode.h"
#include "nsXPCOMGlue.h"
#include "nsIDOMDocument.h"
#include "nsIWebNavigation.h"
#include "nsIDOMElement.h"
#include "nsNetUtil.h"
#include "ILayoutAnalysis.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMDocument.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMHTMLElement.h"
#include "nsIUrlAtt.h"
#include "nsIWebProgress.h"
#include "nsIBaseWindow.h"
#include "nsIScrollable.h"
#include "nsIDOMMouseEvent.h"
#include "nsIDOMDocumentView.h"
#include "nsIDOMAbstractView.h"
#include "nsIDOMEventTarget.h"
#include "nsIDOMDocumentEvent.h"
#include "property.h"
#include <iostream>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "sha1.h"
static NS_DEFINE_CID(kIOServiceCID, NS_IOSERVICE_CID);
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
     int breTime=(int)(interTime*(float)1000);
     if(running==NOT_RUN)
     {
	  if(brwStop)
	  {
	       timer->Cancel();
	       exit(1);
	  }else
	  {
	       if(docStop&&WinStop)
	       {
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
			      Excute(nav);
			 else
			      Update(LINK_STAT_ERROR);
			 //if the evenWait has set, do not change the web site.
			 if(evenWait)
			 {
			      breTime=1000;
			 }else
			 {
			      nsCString tmpUrl;
			      GetUrl(tmpUrl);
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
	  timeCount=0;
	  SetRunning(NOT_RUN);
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
/* void SetWorkSpace (in AUTF8String workspace); */
NS_IMETHODIMP nsBrowserListener::SetWorkSpace(const nsACString & workspace)
{
     nsCString fileName(workspace);
     fileName.Append("/Crawler.ini");
     nsCOMPtr<nsILocalFile> file;
     nsresult rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16(fileName), PR_FALSE,
				   getter_AddRefs(file));
     if (NS_FAILED(rv))
	  return rv;
     nsCOMPtr<nsIInputStream> fistream;
     rv=NS_NewLocalFileInputStream(getter_AddRefs(fistream), file);
     if (NS_FAILED(rv)) 
     {
	  return rv; 
     }
     property->Load(fistream);
    
     mWorkspace=nsCString(workspace);

     nsString strLay;
     property->GetStringProperty(STARTLAYER,strLay);
     startLayer=(PRUint16)atoi(NS_ConvertUTF16toUTF8(strLay).get());
     LOG<<"start layer:"<<startLayer<<"\n";
     
     property->GetStringProperty(ENDLAYER,strLay);
     endLayer=(PRUint16)atoi(NS_ConvertUTF16toUTF8(strLay).get());
     LOG<<"end layer:"<<endLayer<<"\n"; 
     nsString strTime;
     property->GetStringProperty(INTERTIME,strTime);
     if(strTime.Length()>0)
	  interTime=atof(NS_ConvertUTF16toUTF8(strTime).get());
     LOG<<"interTime:"<<interTime<<"\n";
     nsString strScrool;
     property->GetStringProperty(SCROOLWAIT,strScrool);
     if(strScrool.Length()>0)
	  scroolWait=atof(NS_ConvertUTF16toUTF8(strScrool).get());
     LOG<<"scrool:"<<scroolWait<<"\n";
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
      NetStop(false),
      startLayer(0),
      endLayer(0),
      browError(true),
      interTime(0.3),
      timeCount(0),
      isScrolled(false),
      scroolWait(-1),
      evenWait(false)
{
     nsresult rv = NS_GetServiceManager(getter_AddRefs(servMan));
     if (NS_FAILED(rv))
     {
          std::cout<<"Get manager Error:"<<rv<<std::endl;
     }
     property=do_CreateInstance("@mozilla.org/persistent-properties;1", &rv);
     if (NS_FAILED(rv)) 
     {
	  std::cout<<"Get nsIWebBrowser Error:"<<rv<<std::endl;
     }
     iio=do_GetService(kIOServiceCID, &rv);
     if (NS_FAILED(rv))
     {
	  std::cout<<"Get ioservice  Error:"<<std::hex<<rv<<std::endl;
     }
     timeOut=do_CreateInstance("@mozilla.org/timer;1", &rv);
     if (NS_FAILED(rv)) 
     {
	  std::cout<<"Get Timmer Error:"<<rv<<std::endl;
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
	  SetRunning(RUNNING);
//     std::cout<<std::dec<<"flag"<<aFlag<<"stat"<<std::hex<<aStatus<<"running:"<<running<<std::endl;
     if(aFlag==(STATE_IS_REQUEST|STATE_IS_DOCUMENT|STATE_IS_WINDOW|STATE_IS_NETWORK|STATE_START))
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
