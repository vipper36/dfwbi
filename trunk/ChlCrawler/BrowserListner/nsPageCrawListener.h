#ifndef __NSPAGECRAWLISTENER_H__
#define __NSPAGECRAWLISTENER_H__
#include "nsIDOMHTMLDocument.h"
#include "nsIWebNavigation.h"
#include "nsIDOMAnalysis.h"
#include "BrowserListener.h"
#include <stack>
#include <set>



#define NS_PAGECRAWLISTENER_CONTRACTID "@nyapc.com/XPCOM/nsPageCrawListener;1"
#define NS_PAGECRAWLISTENER_CLASSNAME "nsPageCrawListener"

#define NS_PAGECRAWLISTENER_CID {0x2539cd4b,0x9a16,0x44d4,{0xa4,0x4b,0x3b,0xdb,0x10,0x23,0x1e,0xc9}}


class nsPageCrawListener :public nsBrowserListener
{
public: 
     nsPageCrawListener();
     virtual ~nsPageCrawListener(){};
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
