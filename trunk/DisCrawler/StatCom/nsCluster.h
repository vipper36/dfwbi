#include "nsICluster.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIAttSet.h"
#include "nsStringAPI.h"
#include "nsIClustModel.h"
#include <map>
#include <string>
#ifndef __NSCLUSTER_H__
#define __NSCLUSTER_H__
#define NS_CLUSTER_CONTRACTID "@nyapc.com/XPCOM/nsCluster;1"
#define NS_CLUSTER_CLASSNAME "nsCluster"

#define NS_CLUSTER_CID NS_ICLUSTER_IID
class nsCluster : public nsICluster
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICLUSTER

  nsCluster();

private:
  ~nsCluster();
  nsCOMPtr<nsIAttSet> m_atts;
  std::map<std::string,double> dParams;
  std::map<std::string,std::string> sParams;
  nsCOMPtr<nsIClustModel> m_model;
protected:
  /* additional members */
};
#endif
