#include "nsIVarGenerator.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIAttSet.h"
#include "nsIClustModel.h"
#include "nsStringAPI.h"
#include "nsIDomAttUtil.h"
#include "nsIContentTrainUtil.h"
#include "nsIAttDim.h"
#include "nsIDimStat.h"
#include <map>
#include <string>
#include <list>
#ifndef __CONTENTVARGEN_H__
#define __CONTENTVARGEN_H__
#define CONTENTVARGEN_CONTRACTID "@nyapc.com/XPCOM/ContentVarGen;1"
#define CONTENTVARGEN_CLASSNAME "ContentVarGen"

#define CONTENTVARGEN_CID {0x457010ba,0x92ee,0x4157,{0x81,0x7d,0xba,0xe1,0x2f,0xa3,0x21,0x2c}}
class ContentVarGen : public nsIVarGenerator
{
public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSIVARGENERATOR

    ContentVarGen();

private:
    ~ContentVarGen();
    std::string ConcatTwoParams(std::string & param1, std::string & param2);
    PRInt32 FindMainNode(std::list<PRInt32> & main_node, PRInt32 * common_dims, PRUint32 common_dim_count, nsIDimStat * p_dimstat);
    PRInt32 FindTitleNode(std::list<PRInt32> & main_node, nsIDimStat * p_dimstat);
    void FindOtherNode(PRInt32 * common_dims, PRUint32 dims_count, nsIDimStat * p_dimstat);
    void ConfirmAdvertiseNode(PRInt32 * common_dims, PRUint32 dims_count, std::list<PRInt32> & main_node);
    bool CouldBeMainNode(nsCString & xpath);
    void StatisticAttSet(nsIDimStat ** dimstat, nsIAttSet * attset);
    double ParseStringToDouble(std::string & s);

    void SetVar(std::string key, std::string value);
    void AppendParamToVariable(std::string key, std::string value);
    void PrintTrainingResults();

    nsCOMPtr<nsIClustModel> p_model;
    std::map<std::string ,std::string> m_vars;
    std::map<std::string ,std::string> m_parm;
    nsCOMPtr<nsIDomAttUtil> p_domutil;
    nsCOMPtr<nsIContentTrainUtil> p_contentutil;
    nsCOMPtr<nsIAttDim> p_attdim;
    PRInt32 important_dim;
};
#endif
