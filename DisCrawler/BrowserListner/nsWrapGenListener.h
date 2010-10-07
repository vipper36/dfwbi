#ifndef __NSWRAPGENLISTENER_H__
#define __NSWRAPGENLISTENER_H__
#include "nsIDOMHTMLDocument.h"
#include "nsIWebNavigation.h"
#include "BrowserListener.h"
#include "nsISoapTask.h"
#include "nsIXSLTFetcher.h"
#include "nsISoapInter.h"
#include "nsIDocAtt.h"
#include "nsICluster.h"
#include "nsIVarGenerator.h"
#include <stack>
#include <vector>
#include <set>



#define NS_WRAPGENLISTENER_CONTRACTID "@nyapc.com/XPCOM/nsWrapGenListener;1"
#define NS_WRAPGENLISTENER_CLASSNAME "nsWrapGenListener"

#define NS_WRAPGENLISTENER_CID {0x9ea27bcb,0x7c83,0x4175,{0x8d,0xfa,0x8f,0x99,0x04,0x27,0x6e,0x61}}

class nsWrapGenListener :public nsBrowserListener
{
public: 
     nsWrapGenListener();
     virtual ~nsWrapGenListener(){};
     NS_IMETHODIMP Excute(nsIWebNavigation *nav);
     NS_IMETHODIMP SetWorkSpace(const nsACString & workspace);
     NS_IMETHODIMP Update(PRUint16 stat);
     NS_IMETHODIMP GetUrl(nsACString &url);
protected:
     int bodyCheckCount;
     nsCOMPtr<nsISoapTask> task;
     int curIndex;
     nsCOMPtr<nsISoapInter> inter;
     nsCOMPtr<nsIDocAtt> docAtt;
     nsCOMPtr<nsICluster> cluster;
     nsCOMPtr<nsIVarGenerator> generator;
     int MaxDoc;
     int curCount;
     nsCString newWrapper;
     int Uid;
     bool split(const std::string& s, std::string c,std::vector<std::string>& v);
     bool GetParam(const std::string& s, std::map<std::string,std::string>& map);
};

#endif
