#include "nsIClustModel.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIAttVec.h"
#include "nsIAttSet.h"
#include "nsStringAPI.h"
#include "nsCOMArray.h"
#ifndef __NSCLUSTMODEL_H__
#define __NSCLUSTMODEL_H__
#define NS_CLUSTMODEL_CONTRACTID "@nyapc.com/XPCOM/nsClustModel;1"
#define NS_CLUSTMODEL_CLASSNAME "nsClustModel"

#define NS_CLUSTMODEL_CID NS_ICLUSTMODEL_IID

class nsClustModel : public nsIClustModel
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICLUSTMODEL

  nsClustModel();

private:
  ~nsClustModel();
  nsCOMPtr<nsIAttVec> m_att;
  nsCOMArray<nsIAttVec> c_atts;
  nsCOMArray<nsIAttSet> c_sets;  
protected:
  /* additional members */
};
#endif
