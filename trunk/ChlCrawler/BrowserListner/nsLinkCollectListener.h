#ifndef __NSLINKCOLLECTLISTENER_H__
#define __NSLINKCOLLECTLISTENER_H__
#include "nsIDOMHTMLDocument.h"
#include "nsIWebNavigation.h"
#include "nsIDOMAnalysis.h"
#include "BrowserListener.h"
#include <stack>
#include <set>



#define NS_LINKCOLLECTLISTENER_CONTRACTID "@nyapc.com/XPCOM/nsLinkCollectListener;1"
#define NS_LINKCOLLECTLISTENER_CLASSNAME "nsLinkCollectListener"

#define NS_LINKCOLLECTLISTENER_CID {0xe52484f1,0x4e9e,0x4085,{0xbc,0xee,0x77,0x4a,0xf3,0xbf,0x39,0xde}}


class nsLinkCollectListener :public nsBrowserListener
{
public: 
     nsLinkCollectListener();
     virtual ~nsLinkCollectListener(){};
     NS_IMETHODIMP Excute(nsIWebNavigation *nav);
     NS_IMETHODIMP SetWorkSpace(const nsACString & workspace);
     NS_IMETHODIMP Update(PRUint16 stat);
     NS_IMETHODIMP GetUrl(nsACString &url);
protected:
     nsCOMPtr<nsIUrlIO> urlSrc;
     nsCOMPtr<nsIDOMAnalysis> analyzer;
     nsCString must_have;
     int bodyCheckCount;
     nsCOMPtr<nsIUrlAtt> mUrl;
};

#endif
