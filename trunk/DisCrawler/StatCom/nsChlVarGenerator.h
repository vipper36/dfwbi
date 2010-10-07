#include "nsIVarGenerator.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIAttSet.h"
#include "nsIClustModel.h"
#include "nsStringAPI.h"
#include "nsIDomAttUtil.h"
#include <map>
#include <string>
#ifndef __NSCHLVARGENERATOR_H__
#define __NSCHLVARGENERATOR_H__
#define NS_CHLVARGENERATOR_CONTRACTID "@nyapc.com/XPCOM/nsChlVarGenerator;1"
#define NS_CHLVARGENERATOR_CLASSNAME "nsChlVarGenerator"

#define NS_CHLVARGENERATOR_CID {0xa3df9d0e,0xf49b,0x4837,{0x9,0x47,0x52,0x00,0x7e,0x2a,0x54,0x3d}}
class nsChlVarGenerator : public nsIVarGenerator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIVARGENERATOR

  nsChlVarGenerator();

private:
  ~nsChlVarGenerator();
  nsCOMPtr<nsIClustModel> m_model;
  std::map<std::string ,std::string> m_vars;
  std::map<std::string ,std::string> m_parm;
  nsCOMPtr<nsIDomAttUtil> dUtil;
  bool CaculAtt(nsIAttVec *vec,double *ret);
  
protected:
  /* additional members */
};
#endif
