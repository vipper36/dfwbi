#ifndef __NSCOLCRAWLISTENER_H__
#define __NSCOLCRAWLISTENER_H__
#include "nsIDOMHTMLDocument.h"
#include "BrowserListener.h"
#include "nsIWebNavigation.h"
#include "nsIColIO.h"
#include "nsIColFetcher.h"
#include "nsIUrlIO.h"
#include "nsIColAtt.h"
#include "nsIUrlAtt.h"
#include "ILayoutAnalysis.h"
#include "nsIColNextPageFetcher.h"
#include <stack>
#include <set>



#define NS_COLCRAWLISTENER_CONTRACTID "@nyapc.com/XPCOM/nsColCrawListener;1"
#define NS_COLCRAWLISTENER_CLASSNAME "nsColCrawListener"

#define NS_COLCRAWLISTENER_CID {0xbc6a54a7,0x3121,0x4070,{0x9e,0x4c,0xd9,0xbd,0xd8,0x53,0x35,0x1e}}

class  nsColCrawListener:public nsBrowserListener
{
public: 
     nsColCrawListener();
     virtual ~nsColCrawListener(){};
     NS_IMETHODIMP Excute(nsIWebNavigation *nav);
     NS_IMETHODIMP SetWorkSpace(const nsACString & workspace);
     NS_IMETHODIMP Update(PRUint16 stat);
     NS_IMETHODIMP GetUrl(nsACString &url);

protected:
     nsCOMPtr<nsIColIO> ColSrc;
     nsCOMPtr<nsIColFetcher> ColFetch;
     nsCOMPtr<nsIColNextPageFetcher> ColPageFetch;
     nsCOMPtr<nsIUrlIO> urlTarget;
     

     nsCOMPtr<nsIColAtt> mCol;
     nsString AliasPath;
     int bodyCheckCount;
};

#endif
