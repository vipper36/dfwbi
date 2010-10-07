#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsDimStat.h"
#include "nsIDOMNodeList.h"
#include "nsIDOMElement.h"
#include "nsIXpathUtil.h"
#include "nsNetUtil.h"
#include "xpcom-config.h"
#include <iostream>
#include <sstream>
#include <stack>
#include "property.h"

NS_IMPL_ISUPPORTS1(nsDimStat, nsIDimStat)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsDimStat)

static nsModuleComponentInfo components[] =
{
     {
	  NS_DIMSTAT_CLASSNAME,
	  NS_DIMSTAT_CID,
	  NS_DIMSTAT_CONTRACTID,
	  nsDimStatConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsDimStatModule", components)

nsDimStat::nsDimStat()
{
  /* member initializers and constructor code */
    nsresult rv;
    p_xpathutil = do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1", &rv);
    if (NS_FAILED(rv)) {
        LOG << "[nsDimStat] Constructor:Get nsIXpathUtil Error" << rv << "\n";
    }
    p_domutil = do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1", &rv);
    if (NS_FAILED(rv)) {
        LOG << "[nsDimStat] Constructor:Get nsIDomAttUtil Error" << rv << "\n";
    }
}

nsDimStat::~nsDimStat()
{
  /* destructor code */
}

/* double GetTotalWeightByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetTotalWeightByDim(PRInt32 id, double *_retval)
{
    std::map< int, std::list< std::pair<int,int> > >::iterator it = raw_dim.find(id);
    if(it != raw_dim.end())
    {
	std::list<std::pair<int,int> > & records = it->second;
	std::list< std::pair<int,int> >::iterator ite = records.begin();
	double total_weight = 0.0;
	for(; ite != records.end(); ite++)
	{
	    total_weight += ite->first;
	}

	if(total_weight > 0.001)
	{
	    *_retval = (double)total_weight;
	    return NS_OK;
	}
    }
    *_retval = 0.0;
    return NS_OK;
}

/* double GetAvrgWeightByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetAvrgWeightByDim(PRInt32 id, double *_retval)
{
    std::map< int, std::list< std::pair<int,int> > >::iterator it = raw_dim.find(id);
    if(it != raw_dim.end())
    {
	std::list<std::pair<int,int> > & records = it->second;
	int inverse_doc_count = records.size();
	std::list< std::pair<int,int> >::iterator ite = records.begin();
	int total_weight = 0;
	for(; ite != records.end(); ite++)
	{
	    total_weight += ite->first;
	}

	if(total_weight > 0)
	{
	    *_retval = (double)total_weight / (double)inverse_doc_count;
	}
	else
	{
	    *_retval = 0.0;
	}
    }
    return NS_OK;
}

/* double GetWeightVarianceByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetWeightVarianceByDim(PRInt32 id, double *_retval)
{
    double avrg_weight = 0.0;
    GetAvrgWeightByDim(id, &avrg_weight);
    std::map< int, std::list< std::pair<int,int> > >::iterator it = raw_dim.find(id);
    if(it != raw_dim.end())
    {
	std::list<std::pair<int,int> > & records = it->second;
	int inverse_doc_count = records.size();
	std::list< std::pair<int,int> >::iterator ite = records.begin();
	double total_deviation = 0.0;
	for(; ite != records.end(); ite++)
	{
	    total_deviation = total_deviation + (ite->first - avrg_weight);
	}

	if(total_deviation > 0.001 || total_deviation < 0.001)
	{
	    *_retval = (double)total_deviation / (double)inverse_doc_count;
	}
	else
	{
	    *_retval = 0.0;
	}
    }
    return NS_OK;
}

/* double GetInverseDocCountByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetInverseDocCountByDim(PRInt32 id, double *_retval)
{
    std::map< int, std::list< std::pair<int,int> > >::iterator it = raw_dim.find(id);
    if(it != raw_dim.end())
    {
	std::list<std::pair<int,int> > & records = it->second;
	int inverse_doc_count = records.size();
	*_retval = (double) inverse_doc_count;
    }
    else
    {
	*_retval = 0.0001;
    }
    return NS_OK;
}

/* double GetArvgShowCountByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetAvrgShowCountByDim(PRInt32 id, double *_retval)
{
    std::map< int, std::list< std::pair<int,int> > >::iterator it = raw_dim.find(id);
    if(it != raw_dim.end())
    {
	std::list<std::pair<int,int> > & records = it->second;
	int inverse_doc_count = records.size();
	std::list< std::pair<int,int> >::iterator ite = records.begin();
	int total_show_count = 0;
	for(; ite != records.end(); ite++)
	{
	    total_show_count += ite->second;
	}

	if(total_show_count > 0)
	{
	    *_retval = (double)total_show_count / (double)inverse_doc_count;
	}
	else
	{
	    *_retval = 0.0;
	}
    }
    return NS_OK;
}

/* double GetShowCountVarianceByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetShowCountVarianceByDim(PRInt32 id, double *_retval)
{
    double avrg_show_count = 0.0;
    GetAvrgShowCountByDim(id, &avrg_show_count);
    std::map< int, std::list< std::pair<int,int> > >::iterator it = raw_dim.find(id);
    if(it != raw_dim.end())
    {
	std::list<std::pair<int,int> > & records = it->second;
	int inverse_doc_count = records.size();
	std::list< std::pair<int,int> >::iterator ite = records.begin();
	double total_deviation = 0.0;
	for(; ite != records.end(); ite++)
	{
	    total_deviation = total_deviation + (ite->second - avrg_show_count);
	}

	if(total_deviation > 0.001 || total_deviation < 0.001)
	{
	    *_retval = (double)total_deviation / (double)inverse_doc_count;
	}
	else
	{
	    *_retval = 0.0;
	}
    }
    return NS_OK;
}

/* long GetDocCount (); */
NS_IMETHODIMP nsDimStat::GetDocCount(PRInt32 *_retval)
{
    *_retval = doc_count;
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDimStat::SetDocument(nsIDOMDocument *doc)
{
    if (doc != nsnull) {
        nsCOMPtr<nsIDOMNode> node = do_QueryInterface(doc);
        nsCOMPtr<nsIDOMNSDocument> nsdoc = do_QueryInterface(doc);
        LOG << "[nsDimStat] SetDocument:start parsing doc\n";
	xpathstat.clear();
        WalkTree(node, nsdoc);
	CombineStatisticResults();
    }
    return NS_OK;
}

/* void SetAttDim (in nsIAttDim attdim); */
NS_IMETHODIMP nsDimStat::SetAttDim(nsIAttDim *attdim)
{
    this->p_attdim = attdim;
    return NS_OK;
}

void nsDimStat::WalkTree(nsIDOMNode * node, nsIDOMNSDocument * doc)
{
	if(nsnull == node){
		LOG << "[nsDimStat] WalkTree:node is null";
		return;
	}

	nsresult rv;
	PRBool has_child = false;
	node->HasChildNodes(&has_child);
	if(has_child){
		nsCOMPtr<nsIDOMNodeList> children;
		rv = node->GetChildNodes(getter_AddRefs(children));
		if(!NS_FAILED(rv)){
			PRUint32 len;
			children->GetLength(&len);
			for(int i = 0; i < len; i++)
			{
				nsIDOMNode * n;
				children->Item(i, &n);

				nsString name;
				n->GetNodeName(name);
				unsigned short type;
				n->GetNodeType(&type);

				//LOG << "[nsDimStat] WalkTree:node name is "<< NS_ConvertUTF16toUTF8(name).get() << " node type is " << type <<"\n";
				if(type == nsIDOMNode::ELEMENT_NODE)
				{
					//Do statistic here
					nsCOMPtr<nsIDOMDocument> document = do_QueryInterface(doc);
					DoStatistic(n, document);				
					//Recursive walk
					WalkTree(n, doc);
				}
			}
		}
	}
}

void nsDimStat::DoStatistic(nsIDOMNode * node, nsIDOMDocument * doc)
{
    
    p_xpathutil->SetDocument(doc);
    nsCString xp;
    p_xpathutil->GetXpath(node, 1, xp);

    if(xp.Length()==0){
	LOG << "[nsDimStat] DoStatistic:Can not get valid xpath.\n";
	return;
    }

    PRInt32 i_dimid = -1;
    p_attdim->GetDimId(xp, &i_dimid);
    if(-1 == i_dimid)
    {
	p_attdim->GetCount(&i_dimid);
	p_attdim->AddDim(i_dimid, xp);
    }

    nsCString nodetext;
    p_domutil->GetNodeOwnText(node, nodetext);
    PRInt32 weight = nodetext.Length();

    std::map< int,std::list<int> >::iterator it;
    it = xpathstat.find(i_dimid);
    if(it != xpathstat.end())
    {
        std::list<int> & weights = it->second;
	weights.push_back(weight);
    }
    else
    {
	std::list<int> weights;
	weights.push_back(weight);
	xpathstat.insert(std::pair<int,std::list<int> >(i_dimid, weights));
    }
}

void nsDimStat::CombineStatisticResults()
{
    std::map< int,std::list<int> >::iterator it = xpathstat.begin();
    for(;it != xpathstat.end(); it++)
    {
	int xpathid = it->first;
	std::list<int> & weights_of_doc = it->second;
	int showcount = weights_of_doc.size();
	int total_weight = 0;
	std::list<int>::iterator ite = weights_of_doc.begin();
	for(;ite != weights_of_doc.end(); ite++){
	    total_weight += *ite;
	}

	std::map< int, std::list< std::pair<int,int> > >::iterator iter;
	iter = raw_dim.find(xpathid);
	if(iter != raw_dim.end())
	{
	    std::list< std::pair<int,int> > & records = iter->second;
	    records.push_back(std::pair<int,int>(total_weight, showcount));
	}
	else
	{
	    std::list< std::pair<int,int> > records;
	    records.push_back(std::pair<int,int>(total_weight, showcount));
	    raw_dim.insert(std::pair<int, std::list<std::pair<int,int> > >(xpathid, records));
	}
    }
}
