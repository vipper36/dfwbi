#include "xpcom-config.h"
#include "nsIBrowserConnector.h"
#include "nsIWebProgressListener.h"
#include "nsWeakReference.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIUrlCollector.h"
#include <string>
#include <map>
#include <list>

#ifndef __BROWSERLISTENER_H__
#define __BROWSERLISTENER_H__

#define NS_BROWSERLISTENER_CONTRACTID "@nyapc.com/XPCOM/nsBrowserListener;1"
#define NS_BROWSERLISTENER_CLASSNAME "nsBrowserListener"

#define NS_BROWSERLISTENER_CID NS_IBROWSERCONNECTOR_IID




class nsBrowserListener :public nsSupportsWeakReference,
		       public nsIBrowserConnector, 
		       public nsIWebProgressListener
{
public: 
     NS_DECL_ISUPPORTS 
     NS_DECL_NSIBROWSERCONNECTOR

     NS_DECL_NSIWEBPROGRESSLISTENER
     nsBrowserListener();
     virtual ~nsBrowserListener(){};
protected:
     nsIWebBrowser* mBro;
     nsCOMPtr<nsIServiceManager> servMan;
     nsCOMPtr<nsIUrlCollector> urls;
};

#endif
