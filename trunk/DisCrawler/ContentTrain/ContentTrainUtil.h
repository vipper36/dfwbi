#include "nsIContentTrainUtil.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIAttDim.h"
#include "nsIDimStat.h"
#include "nsIAttSet.h"
#include "nsIClustModel.h"
#include "nsStringAPI.h"
#include "nsIDomAttUtil.h"
#include "nsIXpathUtil.h"
#include <map>
#include <string>
#include "distance.h"
#ifndef __CONTENTTRAINUTIL_H__
#define __CONTENTTRAINUTIL_H__
#define CONTENTTRAINUTIL_CONTRACTID "@nyapc.com/XPCOM/ContentTrainUtil;1"
#define CONTENTTRAINUTIL_CLASSNAME "ContentTrainUtil"

#define CONTENTTRAINUTIL_CID NS_ICONTENTTRAINUTIL_IID
class ContentTrainUtil: public nsIContentTrainUtil
{
public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSICONTENTTRAINUTIL

    ContentTrainUtil();

private:
    ~ContentTrainUtil();
    void ElimitDiffDim(PRInt32 * dims1, PRInt32 * dims2, PRUint32 size1, PRUint32 size2);
    PRUint32 SameScore(const nsCString & s1, const nsCString & s2);
    nsCString GetNodesTextByXpath(nsIXpathUtil * xpathutil, const nsACString & xpath);

    nsCOMPtr<nsIAttSet> p_attset;
    nsCOMPtr<nsIAttDim> p_attdim;
    nsCOMPtr<nsIDomAttUtil> p_domutil;
};
#endif
