#include "nsIDocAtt.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDocSet.h"
#include "nsIAttSet.h"
#include "nsIAttDim.h"
#include "nsStringAPI.h"
#include "nsIDomAttUtil.h"
#include <map>
#include <string>
#ifndef __NSDOCATT_H__
#define __NSDOCATT_H__
#define NS_DOCATT_CONTRACTID "@nyapc.com/XPCOM/nsDocAtt;1"
#define NS_DOCATT_CLASSNAME "nsDocAtt"

#define NS_DOCATT_CID NS_IDOCATT_IID

class nsDocAtt : public nsIDocAtt
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOCATT

  nsDocAtt();

private:
  ~nsDocAtt();

  nsCOMPtr<nsIDocSet> m_docs;
  nsCOMPtr<nsIDomAttUtil> domUtil;
  nsCOMPtr<nsIAttSet> vset;
  nsCOMPtr<nsIAttDim> vdim;
  bool GetBoxAtt(nsIDOMDocument *domdoc);
protected:
  /* additional members */
};
#endif
