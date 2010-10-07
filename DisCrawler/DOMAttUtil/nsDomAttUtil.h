#include "nsIDomAttUtil.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIAttSet.h"
#include "nsIDOMDocument.h"
#include "nsStringAPI.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMNSDocument.h"
#include "inIDOMUtils.h"
#include "nsIDOMViewCSS.h"
#include <map>
#include <string>
#ifndef __NSDOMATTUTIL_H__
#define __NSDOMATTUTIL_H__
#define NS_DOMATTUTIL_CONTRACTID "@nyapc.com/XPCOM/nsDomAttUtil;1"
#define NS_DOMATTUTIL_CLASSNAME "nsDomAttUtil"

#define NS_DOMATTUTIL_CID NS_IDOMATTUTIL_IID
class nsDomAttUtil : public nsIDomAttUtil
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMATTUTIL

  nsDomAttUtil();

private:
  ~nsDomAttUtil();
  void GetComLayoutInfo(nsIDOMElement* node,std::map<std::string,std::string> &lmap);
protected:
  /* additional members */
};
#endif
