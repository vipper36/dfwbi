#include "nsIColNextPageFetcher.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsCOMArray.h"
#include "nsIPersistentProperties2.h"
#include "nsStringAPI.h"
#include "nsIColAtt.h"
#include <string>
#include <map>
#ifndef __NSCOLATT_H__
#define __NSCOLATT_H__
#define NS_COLNEXTPAGEFETCHER_CONTRACTID "@nyapc.com/XPCOM/nsColNextPageFetcher;1"
#define NS_COLNEXTPAGEFETCHER_CLASSNAME "nsColNextPageFetcher"

#define NS_COLNEXTPAGEFETCHER_CID {0x0485423d,0xd5e5,0x4940,{0x82,0xb0,0x5b,0x1c,0x1a,0x8a,0x76,0xee}}


class nsColNextPageFetcher : public nsIColNextPageFetcher
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICOLNEXTPAGEFETCHER

  nsColNextPageFetcher();

private:
  ~nsColNextPageFetcher();
  nsCOMPtr<nsIColAtt> mCol;
  nsCOMPtr<nsIDOMDocument> mDoc;
  nsCOMPtr<nsIPersistentProperties> property;

  NS_IMETHODIMP FillPages();
  NS_IMETHODIMP FillUrls();
  bool is_nextpage_text(std::string text);
  void string_filter(std::string & s);

  bool hasLoadJs;
  nsCOMPtr<nsIColAtt> mNextPage;
  nsCOMPtr<nsIDOMElement> mEvtEle;
protected:
  /* additional members */
};
#endif
