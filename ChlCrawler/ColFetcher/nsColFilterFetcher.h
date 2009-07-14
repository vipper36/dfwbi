#include "nsIColFetcher.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsCOMArray.h"
#include "nsIPersistentProperties2.h"
#include "nsStringAPI.h"
#include <string>
#include <map>
#ifndef __NSCOLATT_H__
#define __NSCOLATT_H__
#define NS_COLFILTERFETCHER_CONTRACTID "@nyapc.com/XPCOM/nsColFilterFetcher;1"
#define NS_COLFILTERFETCHER_CLASSNAME "nsColFilterFetcher"

#define NS_COLFILTERFETCHER_CID {0x157ca3ef,0x3b50,0x4296,{0xb3,0x0f,0x6d,0xa2,0x69,0x99,0xfb,0x06}}
struct URLDesc
{
     std::string url;
     std::string title;
};


class nsColFilterFetcher : public nsIColFetcher
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICOLFETCHER

  nsColFilterFetcher();

private:
  ~nsColFilterFetcher();
  nsCOMPtr<nsIColAtt> mCol;
  nsCOMPtr<nsIDOMDocument> mDoc;
  nsCOMPtr<nsIPersistentProperties> property;
  nsCOMArray<nsIUrlAtt> urls;
  int classCount;
  int editDis;
  nsCString expStr;
  nsCString incStr;
  int replaceType;
  std::string RepFrom;
  std::string RepTo;
  bool StrMatch(const std::string &src,const std::string &match);
  NS_IMETHODIMP FillUrls();
  bool is_nextpage_text(std::string text);
  int distance(const std::string source, const std::string target);
  void string_filter(std::string & s);
  void ReplaceString(std::string & s,const std::string &from,const std::string &to,int type);
  std::string TranHost(const std::string &from);
protected:
  /* additional members */
};
#endif
