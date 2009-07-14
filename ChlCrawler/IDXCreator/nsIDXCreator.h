#ifndef __NSIURLCOLLECTOR_H__
#define __NSIURLCOLLECTOR_H__
#include "xpcom-config.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsStringAPI.h"
#include "nsIIDXCreator.h"
#include "nsIXMLHttpRequest.h"
#include <list>

#define NS_IDXCREATOR_CONTRACTID "@nyapc.com/XPCOM/nsIIDXCreator;1"
#define NS_IDXCREATOR_CLASSNAME "nsIIDXCreator"

#define NS_IDXCREATOR_CID NS_IIDXCREATOR_IID

class nsIDXCreator : public nsIIDXCreator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIIDXCREATOR

  nsIDXCreator();

private:
  ~nsIDXCreator();

protected:
  nsCOMPtr<nsIXMLHttpRequest> req;
  nsCString mReference;
  nsCString mTitle;
  nsCString mDate;
  std::list< std::pair<nsCString,nsCString> > mField;
  nsCString mDbName;
  nsCString mContent;
  /* additional members */
  void ConvertBufToPlainText(nsString &aConBuf);
};
#endif
