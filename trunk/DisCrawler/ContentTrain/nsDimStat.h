#include "nsIDimStat.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIAttDim.h"
#include "nsIDOMDocument.h"
#include "nsStringAPI.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMNSDocument.h"
#include "nsIDOMNode.h"
#include "nsIXpathUtil.h"
#include "nsIDomAttUtil.h"
#include "BlockUtils.h"
#include <map>
#include <list>
#ifndef __NSDIMSTAT_H__
#define __NSDIMSTAT_H__
#define NS_DIMSTAT_CONTRACTID "@nyapc.com/XPCOM/nsDimStat;1"
#define NS_DIMSTAT_CLASSNAME "nsDimStat"

#define NS_DIMSTAT_CID NS_IDIMSTAT_IID

class nsDimStat : public nsIDimStat
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_NSIDIMSTAT

	nsDimStat();
private:
	~nsDimStat();

	void WalkTree(nsIDOMNode * node, nsIDOMNSDocument * doc);
	void DoStatistic(nsIDOMNode * node, nsIDOMDocument * doc);
	void CombineStatisticResults();

	std::map< int,std::list< std::pair<int,int> > > raw_dim;
	std::map< int,std::list<int> > xpathstat;
	nsCOMPtr<nsIAttDim> p_attdim;
	nsCOMPtr<nsIDomAttUtil> p_domutil;
	nsCOMPtr<nsIXpathUtil> p_xpathutil;
	int doc_count;
};

#endif
