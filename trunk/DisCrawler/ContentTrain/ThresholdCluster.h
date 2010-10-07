#include "nsICluster.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIAttSet.h"
#include "nsIAttVec.h"
#include "nsStringAPI.h"
#include "nsIClustModel.h"
#include <map>
#include <string>
#ifndef __THRESHOLDCLUSTER_H__
#define __THRESHOLDCLUSTER_H__
#define THRESHOLDCLUSTER_CONTRACTID "@nyapc.com/XPCOM/ThresholdCluster;1"
#define THRESHOLDCLUSTER_CLASSNAME "ThresholdCluster"

#define THRESHOLDCLUSTER_CID {0x621762af,0xaf98,0x4f24,{0x9a,0x57,0x7c,0xb2,0x6b,0x53,0x42,0x96}}
class ThresholdCluster : public nsICluster
{
public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSICLUSTER
    ThresholdCluster();

private:
    ~ThresholdCluster();
    int FindSimilarClass(nsIAttVec * vec);
    double CaculSimilarity(nsIAttVec * v1, nsIAttVec * v2);
    double CaculDot(nsIAttVec * v1, nsIAttVec * v2);

    nsCOMPtr<nsIAttSet> m_atts;
    std::map<std::string,double> dParams;
    std::map<std::string,std::string> sParams;
    nsCOMPtr<nsIClustModel> m_model;
protected:
  /* additional members */
};
#endif
