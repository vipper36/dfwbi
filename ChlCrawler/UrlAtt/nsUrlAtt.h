#include "nsIUrlAtt.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"

#include "nsStringAPI.h"

#ifndef __NSURLATT_H__
#define __NSURLATT_H__
#define NS_URLATT_CONTRACTID "@nyapc.com/XPCOM/nsUrlAtt;1"
#define NS_URLATT_CLASSNAME "nsUrlAtt"

#define NS_URLATT_CID NS_IURLATT_IID
class nsUrlAtt : public nsIUrlAtt
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIURLATT

  nsUrlAtt();

private:
  ~nsUrlAtt();
  PRUint32 Id;
  nsCString Hash;
  nsCString Link;
  nsCString Title;
  PRUint16 Layer;
  nsCString urlType;
  nsCString conType;
  nsCString conAtt;
  PRUint32 colId;
  PRInt32 nextId;
  PRInt32 parId;
protected:
  /* additional members */
};
#endif
