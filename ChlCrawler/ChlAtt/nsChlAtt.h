#include "nsIChlAtt.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"

#include "nsStringAPI.h"

#ifndef __NSCHLATT_H__
#define __NSCHLATT_H__
#define NS_CHLATT_CONTRACTID "@nyapc.com/XPCOM/nsChlAtt;1"
#define NS_CHLATT_CLASSNAME "nsChlAtt"

#define NS_CHLATT_CID NS_ICHLATT_IID
class nsChlAtt : public nsIChlAtt
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICHLATT

  nsChlAtt();

private:
  ~nsChlAtt();
  PRUint32 Id;
  nsCString Hash;
  nsCString Url;
  nsCString Name;
  nsCString XPath;
protected:
  /* additional members */
};
#endif
