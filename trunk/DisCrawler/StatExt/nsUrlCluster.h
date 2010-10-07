#include "nsICluster.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIAttSet.h"
#include "nsStringAPI.h"
#include "nsIClustModel.h"
#include "nsIDomAttUtil.h"
#include <map>
#include <vector>
#include <string>
#ifndef __NSURLCLUSTER_H__
#define __NSURLCLUSTER_H__
#define NS_URLCLUSTER_CONTRACTID "@nyapc.com/XPCOM/nsUrlCluster;1"
#define NS_URLCLUSTER_CLASSNAME "nsUrlCluster"

#define NS_URLCLUSTER_CID {0x4d4aff52,0x9b69,0x4b76,{0xa2,0xb8,0xd2,0x44,0xdf,0xae,0xb3,0xdb}}
class nsUrlCluster : public nsICluster
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICLUSTER

  nsUrlCluster();

private:
  ~nsUrlCluster();
  nsCOMPtr<nsIAttSet> m_atts;
  std::map<std::string,double> dParams;
  std::map<std::string,std::string> sParams;
  nsCOMPtr<nsIClustModel> m_model;
  nsCOMPtr<nsIDomAttUtil> domUtil;
protected:
  bool split(const std::string& s, std::string c,std::vector<std::string>& v);
  /* additional members */
};
#endif
