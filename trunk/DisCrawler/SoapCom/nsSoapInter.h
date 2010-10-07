#include "nsISoapInter.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsCOMArray.h"
#include "nsStringAPI.h"
#include "nsISoapJob.h"
#include "nsISoapTask.h"

#include "soapCrawlerCtrlSoapBindingProxy.h"
#include "CrawlerCtrlSoapBinding.nsmap"
#ifndef __NSSOAPINTER_H__
#define __NSSOAPINTER_H__
#define NS_SOAPINTER_CONTRACTID "@nyapc.com/XPCOM/nsSoapInter;1"
#define NS_SOAPINTER_CLASSNAME "nsSoapInter"

#define NS_SOAPINTER_CID NS_ISOAPINTER_IID
class nsSoapInter : public nsISoapInter
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISOAPINTER

  nsSoapInter();

private:
  ~nsSoapInter();
protected:
  nsCString mAddress;
  CrawlerCtrlSoapBindingProxy service;
  bool split(const std::string& s, std::string c,std::vector<std::string>& v);
  /* additional members */
};
#endif
