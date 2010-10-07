#include "nsIXSLTFetcher.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMDocument.h"
#include "nsIDOMXMLDocument.h"
#include "nsStringAPI.h"
#include "nsIXpathUtil.h"
#include <string>
#include <map>
#ifndef __NS_XSLTFETCHER_H__
#define __NS_XSLTFETCHER_H__


#define NS_XSLTFETCHER_CONTRACTID "@nyapc.com/XPCOM/nsXSLTFetcher;1"
#define NS_XSLTFETCHER_CLASSNAME "nsXSLTFetcher"

#define NS_XSLTFETCHER_CID NS_IXSLTFETCHER_IID

class nsXSLTFetcher : public nsIXSLTFetcher
{
public:
     NS_DECL_ISUPPORTS
     NS_DECL_NSIXSLTFETCHER
     
     nsXSLTFetcher();
     
private:
     ~nsXSLTFetcher();
     nsCOMPtr<nsIDOMXMLDocument> mXSLT;
     nsCOMPtr<nsIDOMDocument> mDoc;
     std::map<std::string,nsIDOMNode*> mVarMap;
     std::map<std::string,std::string> mParMap;
     NS_IMETHODIMP GetXsltVars(std::map<std::string,nsIDOMNode*> &varMap);
protected:
  /* additional members */
};
#endif
