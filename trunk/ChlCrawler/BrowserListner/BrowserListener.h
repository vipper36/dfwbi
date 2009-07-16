#ifndef __BROWSERLISTENER_H__
#define __BROWSERLISTENER_H__

#include "xpcom-config.h"
#include "nsIBrowserConnector.h"
#include "nsIWebProgressListener.h"
#include "nsWeakReference.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsStringAPI.h"
#include "nsIPersistentProperties2.h"
#include "nsIIOService.h"
#include "nsITimer.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIWebNavigation.h"
#include "nsIUrlIO.h"
#include "nsITimer.h"
//#include <pthread.h>
#include <string>
#include <map>
#include <list>
#define NOT_RUN 0
#define RUNNING 1
#define RETYRING 2


class nsBrowserListener :public nsSupportsWeakReference,
			 public nsIBrowserConnector, 
			 public nsIWebProgressListener,
			 public nsITimerCallback
{
public: 
     NS_DECL_ISUPPORTS 
     NS_DECL_NSIBROWSERCONNECTOR
     NS_DECL_NSITIMERCALLBACK
     NS_DECL_NSIWEBPROGRESSLISTENER
     nsBrowserListener();
     virtual ~nsBrowserListener();
     void SetRunning(PRUint16 stat);
     void GetHost(const nsCString &url,nsCString &host);

protected:
     nsIWebBrowser* mBro;
     nsCOMPtr<nsIServiceManager> servMan;
     nsCOMPtr<nsIPersistentProperties> property;
     nsCString mWorkspace;
     nsCString mTarDomain;
     nsCOMPtr<nsIIOService> iio;
     PRUint16 running;
     bool brwStop;
     virtual void StopBrows();
     virtual NS_IMETHODIMP Excute(nsIWebNavigation *nav)=0;
     bool HasBody(nsIDOMHTMLDocument *html);
     NS_IMETHODIMP WebNav(nsIWebNavigation *nav,const nsACString &url);
     virtual NS_IMETHODIMP Update(PRUint16 stat)=0;
     virtual NS_IMETHODIMP GetUrl(nsACString &url)=0;

     void SetCurrentUrl(const nsACString &url);
     NS_IMETHODIMP ScrollWin();
     NS_IMETHODIMP SendEvent(nsIDOMElement* ele,nsIDOMDocument *doc);
     bool WinStop;
     bool docStop;
     bool NetStop;
     nsCOMPtr<nsIURI> lastUri;
     nsCString aurl;
     nsCOMPtr<nsITimer> timeOut;
     int timeCount;
     PRUint16 startLayer;
     PRUint16 endLayer;
     float interTime;
     bool browError;
     bool isScrolled;
     float scroolWait;
     bool evenWait;
     void SetEventWait(bool ew);
};

#endif
