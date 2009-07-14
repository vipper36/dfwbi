#include "nsIColBridge.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsCOMArray.h"
#include "nsIPersistentProperties2.h"
#include "nsStringAPI.h"
#include "nsIColIO.h"
#include "nsIUrlIO.h"
#include <string>
#include <map>
#ifndef __NSCOLBRIDGE_H__
#define __NSCOLBRIDGE_H__
#define NS_COLBRIDGE_CONTRACTID "@nyapc.com/XPCOM/nsColBridge;1"
#define NS_COLBRIDGE_CLASSNAME "nsColBridge"

#define NS_COLBRIDGE_CID NS_ICOLBRIDGE_IID
class nsColBridge : public nsIColBridge
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICOLBRIDGE

  nsColBridge();

private:
  ~nsColBridge();
  nsCOMPtr<nsIColIO> ColSrc;
  nsCOMPtr<nsIUrlIO> urlSrc;
protected:
  /* additional members */
};

#endif
