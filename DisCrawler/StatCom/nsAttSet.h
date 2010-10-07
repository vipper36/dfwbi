#include "nsIAttSet.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIAttVec.h"
#include "nsStringAPI.h"
#include "nsCOMArray.h"
#ifndef __NSATTSET_H__
#define __NSATTSET_H__
#define NS_ATTSET_CONTRACTID "@nyapc.com/XPCOM/nsAttSet;1"
#define NS_ATTSET_CLASSNAME "nsAttSet"

#define NS_ATTSET_CID NS_IATTSET_IID
class nsAttSet : public nsIAttSet
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIATTSET

  nsAttSet();

private:
  ~nsAttSet();
  nsCOMArray<nsIAttVec> vects;
protected:
  /* additional members */
};
#endif
