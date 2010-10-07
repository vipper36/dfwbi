#include "nsIVarGenerator.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIAttSet.h"
#include "nsIClustModel.h"
#include "nsStringAPI.h"
#include "nsIDomAttUtil.h"
#include "nsIAttDim.h"
#include "NodeTree.h"
#include <map>
#include <vector>
#include <list>
#include <string>
#ifndef __NSCOLVARGENERATOR_H__
#define __NSCOLVARGENERATOR_H__
#define NS_COLVARGENERATOR_CONTRACTID "@nyapc.com/XPCOM/nsColVarGenerator;1"
#define NS_COLVARGENERATOR_CLASSNAME "nsColVarGenerator"

#define NS_COLVARGENERATOR_CID {0x2e514f3f,0xf306,0x4aa2,{0x99,0x20,0x5a,0xdc,0xd7,0x09,0xc6,0xee}}

class nsColVarGenerator : public nsIVarGenerator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIVARGENERATOR

  nsColVarGenerator();

private:
  ~nsColVarGenerator();
  nsCOMPtr<nsIClustModel> m_model;
  std::map<std::string ,std::string> m_vars;
  std::map<std::string ,std::string> m_parm;
  nsCOMPtr<nsIDomAttUtil> dUtil;
  nsCOMPtr<nsIAttDim> m_attDim;
  nsIDOMNode* CaculAtt(std::map<nsIDOMDocument*,NodeTree > &map);
  int StrNumCount(std::string str);
  bool split(const std::string& s, std::string c,std::vector<std::string>& v);
protected:
  /* additional members */
};
#endif
