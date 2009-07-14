#include "nsIColAtt.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"

#include "nsStringAPI.h"

#ifndef __NSCOLATT_H__
#define __NSCOLATT_H__
#define NS_COLATT_CONTRACTID "@nyapc.com/XPCOM/nsColAtt;1"
#define NS_COLATT_CLASSNAME "nsColAtt"

#define NS_COLATT_CID NS_ICOLATT_IID
class nsColAtt : public nsIColAtt
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICOLATT

  nsColAtt();

private:
  ~nsColAtt();
  PRUint32 Id;
  PRUint32 chlId;
  nsCString Hash;
  nsCString Url;
  nsCString Name;
  nsCString XPath;
  nsCString Alias;
protected:
  /* additional members */
};
#endif
