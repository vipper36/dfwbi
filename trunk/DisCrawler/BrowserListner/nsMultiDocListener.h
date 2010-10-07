#ifndef __NSMULTIDOCLISTENER_H__
#define __NSMULTIDOCLISTENER_H__
#include "nsIDOMHTMLDocument.h"
#include "nsIWebNavigation.h"
#include "BrowserListener.h"
#include "nsISoapTask.h"
#include "nsIXSLTFetcher.h"
#include "nsISoapInter.h"
#include "nsIDOMParser.h"
#include <stack>
#include <set>
#include <sstream>


#define NS_MULTIDOCLISTENER_CONTRACTID "@nyapc.com/XPCOM/nsMultiDocListener;1"
#define NS_MULTIDOCLISTENER_CLASSNAME "nsMultiDocListener"

#define NS_MULTIDOCLISTENER_CID {0x59402902,0x40f6,0x4430,{0xac,0x58,0xa9,0x2c,0x7c,0x24,0xb2,0x0f}}


class nsMultiDocListener :public nsBrowserListener
{
public: 
     nsMultiDocListener();
     virtual ~nsMultiDocListener(){};
     NS_IMETHODIMP Excute(nsIWebNavigation *nav);
     NS_IMETHODIMP SetWorkSpace(const nsACString & workspace);
     NS_IMETHODIMP Update(PRUint16 stat);
     NS_IMETHODIMP GetUrl(nsACString &url);
protected:
     int bodyCheckCount;
     nsCOMPtr<nsISoapTask> task;
     nsCOMPtr<nsIDOMParser> parser;
     std::stringstream taskstream;
     nsCString Wrapper;
     int curIndex;
     nsCOMPtr<nsISoapInter> inter;
     int Uid;
     
};

#endif
