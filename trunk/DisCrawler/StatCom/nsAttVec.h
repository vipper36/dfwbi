#include "nsIAttVec.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIDOMDocument.h"
#include "nsIDOMNode.h"
#include "nsStringAPI.h"
#include <map>
#ifndef __NSATTVEC_H__
#define __NSATTVEC_H__
#define NS_ATTVEC_CONTRACTID "@nyapc.com/XPCOM/nsAttVec;1"
#define NS_ATTVEC_CLASSNAME "nsAttVec"

#define NS_ATTVEC_CID NS_IATTVEC_IID
class nsAttVec : public nsIAttVec
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIATTVEC

  nsAttVec();

private:
  ~nsAttVec();
  nsCOMPtr<nsIDOMDocument> m_doc;
  nsCOMPtr<nsIDOMNode> m_node;
  std::map<int,double> vect;
protected:
  /* additional members */
};
#endif
