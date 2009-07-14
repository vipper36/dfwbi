#include "nsIChlFetcher.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsCOMArray.h"
#include "nsIPersistentProperties2.h"
#include "nsIDOMDocument.h"
#include "nsIDOMNSDocument.h"
#include "nsIChlAtt.h"
#include "nsStringAPI.h"
#include <string>
#ifndef __NSCHLATT_H__
#define __NSCHLATT_H__
#define NS_CHLXPATHFETCHER_CONTRACTID "@nyapc.com/XPCOM/nsChlXpathFetcher;1"
#define NS_CHLXPATHFETCHER_CLASSNAME "nsChlXpathFetcher"

#define NS_CHLXPATHFETCHER_CID {0x49bd9c25,0x0726,0x4a2c,{0xbe,0x8f,0x4a,0xae,0xdc,0x1f,0x88,0x58}}

class nsChlXpathFetcher : public nsIChlFetcher
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICHLFETCHER

  nsChlXpathFetcher();

private:
  ~nsChlXpathFetcher();
  nsCOMPtr<nsIChlAtt> mChl;
  nsCOMPtr<nsIDOMDocument> mDoc;
  nsCOMPtr<nsIDOMNSDocument> nsdoc;
  nsCOMPtr<nsIPersistentProperties> property;
  nsCOMArray<nsIColAtt> cols; 
  int replaceType;
  int expNabor;
  std::string RepFrom;
  std::string RepTo;

  int GetColums();
  NS_IMETHODIMP GetColUrl(nsIDOMNode * aNode,nsACString &url);
  NS_IMETHODIMP GetKinUrl(nsIDOMNode * aNode,nsACString &url);
  NS_IMETHODIMP GetColTitle(nsIDOMNode * aNode,const nsACString & titlePath,nsACString &title);
  bool IsTitle(const std::string &str);
  void string_filter(std::string & s);
  void ReplaceString(std::string & s,const std::string &from,const std::string &to,int type);
  std::string TranHost(const std::string &from);
protected:
  /* additional members */
};
#endif
