#include "nsIDocSet.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIDOMDocument.h"
#include "nsStringAPI.h"
#include "nsCOMArray.h"
#ifndef __NSDOCSET_H__
#define __NSDOCSET_H__
#define NS_DOCSET_CONTRACTID "@nyapc.com/XPCOM/nsDocSet;1"
#define NS_DOCSET_CLASSNAME "nsDocSet"

#define NS_DOCSET_CID NS_IDOCSET_IID
class nsDocSet : public nsIDocSet
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOCSET

  nsDocSet();

private:
  ~nsDocSet();
    nsCOMArray<nsIDOMDocument> docs;
protected:
  /* additional members */
};
#endif
