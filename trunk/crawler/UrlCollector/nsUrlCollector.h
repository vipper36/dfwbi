#ifndef __NS_URLCOLLECTOR__
#define __NS_URLCOLLECTOR__
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIUrlCollector.h"
#include "nsIInputStream.h"
#define NS_URLCOLLECTOR_CONTRACTID "@nyapc.com/XPCOM/nsUrlCollector;1"
#define NS_URLCOLLECTOR_CLASSNAME "nsUrlCollector"

#define NS_URLCOLLECTOR_CID NS_IURLCOLLECTOR_IID

class nsUrlCollector : public nsIUrlCollector
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIURLCOLLECTOR

  nsUrlCollector();

private:
  ~nsUrlCollector();

protected:
  nsCOMPtr<nsIInputStream> mInput;
  /* additional members */
};
#endif
