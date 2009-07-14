#ifndef __NSCHLCRAWLISTENER_H__
#define __NSCHLCRAWLISTENER_H__
#include "nsIDOMHTMLDocument.h"
#include "BrowserListener.h"
#include "nsIWebNavigation.h"
#include "nsIChlIO.h"
#include "nsIChlFetcher.h"
#include "nsIChlWrapper.h"
#include "nsIColIO.h"
#include "nsIColAtt.h"
#include "nsIChlAtt.h"
#include "ILayoutAnalysis.h"
#include "nsStringAPI.h"
#include <stack>
#include <set>



#define NS_CHLCRAWLISTENER_CONTRACTID "@nyapc.com/XPCOM/nsChlCrawListener;1"
#define NS_CHLCRAWLISTENER_CLASSNAME "nsChlCrawListener"

#define NS_CHLCRAWLISTENER_CID {0x1b515074,0x23fd,0x424c,{0xba45,0xab,0x1c,0xc0,0xe3,0x0d,0xed}}

class  nsChlCrawListener:public nsBrowserListener
{
public: 
     nsChlCrawListener();
     virtual ~nsChlCrawListener(){};
     NS_IMETHODIMP Excute(nsIWebNavigation *nav);
     NS_IMETHODIMP SetWorkSpace(const nsACString & workspace);
     NS_IMETHODIMP Update(PRUint16 stat);
     NS_IMETHODIMP GetUrl(nsACString &url);

protected:
     nsCOMPtr<ILayoutAnalysis> analyzer;
     nsCOMPtr<nsIChlIO> ChlSrc;
     nsCOMPtr<nsIChlFetcher> ChlFetch;
     nsCOMPtr<nsIChlWrapper> chlWrap;
     nsCOMPtr<nsIColIO> colTarget;

     nsCOMPtr<nsIChlAtt> mChl;
     int bodyCheckCount;
};

#endif
