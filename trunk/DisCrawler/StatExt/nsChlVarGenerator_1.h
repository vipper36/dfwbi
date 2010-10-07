#include "nsIVarGenerator.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIAttSet.h"
#include "nsIClustModel.h"
#include "nsStringAPI.h"
#include "nsIDomAttUtil.h"
#include "nsIDOMNode.h"
#include <map>
#include <set>
#include <vector>
#include <string>
#ifndef __NSCHLVARGENERATOR_1_H__
#define __NSCHLVARGENERATOR_1_H__
#define NS_CHLVARGENERATOR_1_CONTRACTID "@nyapc.com/XPCOM/nsChlVarGenerator_1;1"
#define NS_CHLVARGENERATOR_1_CLASSNAME "nsChlVarGenerator_1"

#define NS_CHLVARGENERATOR_1_CID {0xd86f2913,0x1a11,0x4b52,{0xb7,0x97,0xa5,0xfd,0xc6,0x1e,0x38,0x14}}

class nsChlVarGenerator_1 : public nsIVarGenerator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIVARGENERATOR

  nsChlVarGenerator_1();

private:
  ~nsChlVarGenerator_1();
  nsCOMPtr<nsIClustModel> m_model;
  std::map<std::string ,std::string> m_vars;
  std::map<std::string ,std::string> m_parm;
  nsCOMPtr<nsIDomAttUtil> dUtil;
  nsIDOMNode *GetParent(std::set<nsIDOMNode*> nodeSet);
protected:
  bool split(const std::string& s, std::string c,std::vector<std::string>& v);
  /* additional members */
};
#endif
