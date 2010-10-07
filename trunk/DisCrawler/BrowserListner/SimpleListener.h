#ifndef __SIMPLELISTENER_H__
#define __SIMPLELISTENER_H__

#include "xpcom-config.h"
#include "nsIWebProgressListener.h"
#include "nsIListenerSetter.h"
#include "nsWeakReference.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsStringAPI.h"
#include "nsIPersistentProperties2.h"
#include "nsIIOService.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIWebNavigation.h"
#include "nsIStatManager.h"
#include "nsIDomAttUtil.h"
#include "nsITimer.h"
#include <string>
#include <map>
#include <list>

#define NS_SIMPLELISTENER_CONTRACTID "@nyapc.com/XPCOM/nsSimpleListener;1"
#define NS_SIMPLELISTENER_CLASSNAME "nsSimpleListener"

#define NS_SIMPLELISTENER_CID {0xfacaaeba,0xb564,0x4d90,{0x84,0x14,0xcf,0x74,0xcc,0x33,0xfa,0x02}}


class nsSimpleListener :public nsSupportsWeakReference,
			public nsIWebProgressListener,
			public nsIListenerSetter,
			public nsITimerCallback
{
public: 
     NS_DECL_ISUPPORTS 
     NS_DECL_NSIWEBPROGRESSLISTENER
     NS_DECL_NSILISTENERSETTER
     NS_DECL_NSITIMERCALLBACK
     nsSimpleListener();
     virtual ~nsSimpleListener();
protected:
     nsCOMPtr<nsITimer> timeOut;
     nsCOMPtr<nsIDomAttUtil> domUtil;
     nsCOMPtr<nsIStatManager> statMan;
     bool HasBody(nsIDOMHTMLDocument *html);
     bool WinStop;
     bool docStop;
     int bodyCheckCount;
     int lid;
	
};

#endif
