#include "nsILoginCookieFetch.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMDocument.h"
#include "nsIDOMXMLDocument.h"
#include "nsIDOMNode.h"
#include "nsStringAPI.h"
#include "nsIXpathUtil.h"
#include "nsISupportsArray.h"
#include "nsISupports.h"
#include <string>
#include <map>
#ifndef __NS_LOGINCOOKIEFETCH_H__
#define __NS_LOGINCOOKIEFETCH_H__


#define NS_LOGINCOOKIEFETCH_CONTRACTID "@nyapc.com/XPCOM/nsLoginCookieFetch;1"
#define NS_LOGINCOOKIEFETCH_CLASSNAME "nsLoginCookieFetch"

#define NS_LOGINCOOKIEFETCH_CID NS_ILOGINCOOKIEFETCH_IID
using namespace std;
class nsLoginCookieFetch : public nsILoginCookieFetch
{
public:
     NS_DECL_ISUPPORTS
     NS_DECL_NSILOGINCOOKIEFETCH

     nsLoginCookieFetch();

private:
     ~nsLoginCookieFetch();
     nsCOMPtr<nsIDOMDocument> mDoc;
     nsString userName;
     nsString password;
     nsString url;
	 NS_IMETHODIMP SetNodeAttributValue(nsCOMPtr<nsIDOMNode> &,const nsString);
	 NS_IMETHODIMP SetUserAttribut(nsCOMPtr<nsIDOMNode>&);
	 NS_IMETHODIMP GetALLDocumentArray(nsIDOMDocument *, nsISupportsArray **);
	 NS_IMETHODIMP GetPassWordDomNode(nsIDOMNode **);
	 //NS_IMETHODIMP GetFormNode(nsCOMPtr<nsIDOMNode>&);
	 NS_IMETHODIMP SendClickEvent(nsCOMPtr<nsIDOMNode> &, nsCOMPtr<nsIDOMDocument> &);
	 NS_IMETHODIMP DoLogin();
     //std::map<std::string,nsIDOMNode*> mVarMap;
     //std::map<std::string,std::string> mParMap;
     //NS_IMETHODIMP GetXsltVars(map<string,nsIDOMNode*> &varMap);
protected:
  /* additional members */
};
#endif

