#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "ContentVarGen.h"
#include "nsIXpathUtil.h"
#include "nsISupportsArray.h"
#include "nsIDOMElement.h"
#include "nsISupports.h"
#include "nsIDOMDocument.h"
#include "nsIAttVec.h"
#include "nsIAttSet.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <limits.h>
#include <stdlib.h>
#include "math.h"
#include "property.h"
#include "StyleCompare.h"

NS_IMPL_ISUPPORTS1(ContentVarGen, nsIVarGenerator)

NS_GENERIC_FACTORY_CONSTRUCTOR(ContentVarGen)

static nsModuleComponentInfo components[] =
{
     {
	  CONTENTVARGEN_CLASSNAME,
	  CONTENTVARGEN_CID,
	  CONTENTVARGEN_CONTRACTID,
	  ContentVarGenConstructor,
     }
};
NS_IMPL_NSGETMODULE("ContentVarGenModule", components)



ContentVarGen::ContentVarGen()
{
    nsresult rv;
    p_domutil=do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1",&rv);
    if (NS_FAILED(rv))
    {
	LOG<<"[ContentVarGen] Constructor:Init nsDomAttUtil error!\n";
    }
    p_contentutil=do_CreateInstance("@nyapc.com/XPCOM/ContentTrainUtil;1",&rv);
    if (NS_FAILED(rv))
    {
	LOG<<"[ContentVarGen] Constructor:Init ContentTrainUtil error!\n";
    }

    m_vars[std::string("box")] = std::string("/html/body");
    important_dim = -1;
}

ContentVarGen::~ContentVarGen()
{
    /* destructor code */
}

/* void SetModel (in nsIClustModel model); */
NS_IMETHODIMP ContentVarGen::SetModel(nsIClustModel *model)
{
    p_model=model;
    return NS_OK;
}

/* void GenVar (); */
NS_IMETHODIMP ContentVarGen::GenVar()
{
    //Generate the wrapper variables
    PRInt32 class_count = 0;
    p_model->GetClassCount(&class_count);
    LOG << "[ContentVarGen] GenVar:There are " << class_count <<" classes in model.\n";
    for(int classid = 0; classid < class_count; classid++)
    {
	nsCOMPtr<nsIAttSet> set_class;
	p_model->GetClassSet(classid, getter_AddRefs(set_class));

	//Do a statistic again for a set of docs,
	//which in a same class.
	LOG << "[ContentVarGen] GenVar:Statistic the class with classid " << classid << "\n";
	nsCOMPtr<nsIDimStat> p_dimstat;
	StatisticAttSet(getter_AddRefs(p_dimstat), set_class);
	LOG << "[ContentVarGen] GenVar:Statistic has completed with classid " << classid << "\n";
	
	//Find common dimension(xpath)
	LOG << "[ContentVarGen] GenVar:Find the common dimensions in class " << classid << "\n";
	PRInt32 * common_dims = NULL;
	PRUint32 common_dim_count = 0;
	p_contentutil->SetVectorSet(set_class);
	p_contentutil->SetAttDim(p_attdim);
	p_contentutil->FindCommonDim(&common_dims, &common_dim_count);
	LOG << "[ContentVarGen] GenVar:Found " << common_dim_count << " common dims.\n";

	//Caculate the content similarity of common xpath.
	//Find the main path.
	LOG << "[ContentVarGen] GenVar:Find the most important dimension in class " << classid << "\n";
	std::list<PRInt32> main_node;
	important_dim = 
		FindMainNode(main_node, common_dims, common_dim_count, p_dimstat);
	nsCString important_dim_xpath;
	p_attdim->GetDesc(important_dim, important_dim_xpath);
	LOG<<"[ContentVarGen] GenVar:important xpath " << important_dim_xpath.get() <<"\n";

	//Find title.
	LOG << "[ContentVarGen] GenVar:Find the title dimension in class " << classid << "\n";
	PRInt32 title_dim = 
		FindTitleNode(main_node, p_dimstat);
	nsCString title_xpath;
	p_attdim->GetDesc(title_dim, title_xpath);
	
	LOG<<"[ContentVarGen] GenVar:title xpath " << title_xpath.get() <<"\n";
	
	//Find others(date, source, author).
	LOG << "[ContentVarGen] GenVar:Find others(date, source, author)\n";
	FindOtherNode(common_dims, common_dim_count, p_dimstat);
	
	//Confirm advertise nodes
	ConfirmAdvertiseNode(common_dims, common_dim_count, main_node);
    }

    //PrintTrainingResults();
    return NS_OK;
}
/* void SetParam (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP ContentVarGen::SetParam(const nsACString & name, const nsACString & value)
{
    nsCString nsName(name);
    nsCString nsValue(value);
    m_parm.insert(make_pair(std::string(nsName.get()),std::string(nsValue.get())));
    return NS_OK;
}

/* void SetAttDim (in nsIAttDim attdim); */
NS_IMETHODIMP ContentVarGen::SetAttDim(nsIAttDim *attdim)
{
    p_attdim = attdim;
    return NS_OK;
}

/* AUTF8String GetVar (in AUTF8String name); */
NS_IMETHODIMP ContentVarGen::GetVar(const nsACString & name, nsACString & _retval)
{
    nsCString nsName(name);
    std::string nameStr(nsName.get());
    std::string valueStr=m_vars[nameStr];
    if(valueStr.compare("") == 0)
    {
	valueStr = std::string("string(\"\")");
    }
    nsCString nsValue(valueStr.c_str());
    _retval=nsValue;
    return NS_OK;
}

std::string ContentVarGen::ConcatTwoParams(std::string & param1, std::string & param2)
{
    std::string ret;
    ret.append(param1.c_str());
    ret.append(" | ");
    ret.append(param2.c_str());

    return ret;
}

PRInt32 ContentVarGen::FindMainNode(std::list<PRInt32> & main_node, PRInt32 * common_dims, PRUint32 common_dim_count, nsIDimStat * p_dimstat)
{
    PRInt32 most_important_dim = -1;
    double important_dim_weight = 0.0;

    if(nsnull == common_dims || common_dim_count < 1)
    {
	LOG << "[ContentVarGen] FindMainNode:There are no common dims here.\n";
	return most_important_dim;
    }

    double th = 0.5;
    std::string threshold = m_parm["similar_node_th"];
    double tmp = ParseStringToDouble(threshold);
    if(tmp > 0.0001)
    {
	th = tmp;
    }

    //Start analysis the common nodes
    for(int i = 0; i < common_dim_count; i++)
    {
	nsCString xpath;
	p_attdim->GetDesc(common_dims[i], xpath);
	if(!CouldBeMainNode(xpath))
	{
	    continue;
	}
	else
	{
	    //Only xpath which similarity lower than a threshold, 
	    //and weight must greater than a value, could be main node.
	    //LOG << "[ContentVarGen] FindMainNode:analysis xpath "<<xpath.get()<<"\n";
	    double avrg_weight = 0.0;
	    p_dimstat->GetAvrgWeightByDim(common_dims[i], &avrg_weight);
	    //LOG << "[ContentVarGen] FindMainNode:average weight "<<avrg_weight<<"\n";
	    if(avrg_weight < 7)
	    {
		continue;
	    }
	    double sim = 1.0;
	    p_contentutil->GetSimilarityByDim(common_dims[i], &sim);
	    //LOG << "[ContentVarGen] FindMainNode:similarity "<<sim<<"\n";

	    if(sim < th)
	    {
		//Confirm main node, and push into stack.
		main_node.push_back(common_dims[i]);
		AppendParamToVariable(std::string("content"), std::string(xpath.get()));
		if(avrg_weight > important_dim_weight)
		{
		    most_important_dim = common_dims[i];
		    important_dim_weight = avrg_weight;
		}
	    }
	}
    }
    return most_important_dim;
}

bool ContentVarGen::CouldBeMainNode(nsCString & xpath)
{
    bool ret = true;

    PRInt32 index = xpath.Find("/html/head");
    if(index >= 0)
    {
	LOG << "[ContentVarGen] CouldBeMainNode: wrong path: "<<xpath.get()<<"\n";
	return false;
    }

    return ret;
}

void ContentVarGen::StatisticAttSet(nsIDimStat ** dimstat, nsIAttSet * attset)
{
    nsresult rv;
    PRInt32 doc_count = 0;
    attset->GetLength(&doc_count);
    nsCOMPtr<nsIDimStat> p_dimstat = do_CreateInstance("@nyapc.com/XPCOM/nsDimStat;1",&rv);
    if(NS_FAILED(rv))
    {
	LOG << "[ContentVarGen] StatisticAttSet:can not init nsIDimStat.\n";
	return;
    }
    p_dimstat->SetAttDim(p_attdim);
    for(int i = 0; i < doc_count; i++)
    {
	nsCOMPtr<nsIAttVec> vec;
	attset->GetVectorByIndex(i, getter_AddRefs(vec));
	nsCOMPtr<nsIDOMDocument> doc;
	vec->GetDoc(getter_AddRefs(doc));
	if(nsnull != doc)
	{
	    p_dimstat->SetDocument(doc);
	}

    }

    *dimstat = p_dimstat;
    NS_ADDREF(p_dimstat);
    return;
}

double ContentVarGen::ParseStringToDouble(std::string & s)
{
    double ret = -1.0;
    if(s.length() > 0)
    {
	ret = atof(s.c_str());
    }
    return ret;
}

PRInt32 ContentVarGen::FindTitleNode(std::list<PRInt32> & main_node, nsIDimStat * p_dimstat)
{
    PRInt32 title_dim = -1;
    double title_dim_sim = 0.0;
    if(main_node.size() <= 0)
    {
	LOG << "[ContentVarGen] FindTitleNode:there is no element in main node set.\n";
	return title_dim;
    }
    else
    {
	LOG << "[ContentVarGen] FindTitleNode:There are "<<main_node.size()<<" main nodes\n";
    }

    //
    std::list<PRInt32>::iterator it = main_node.begin();
    for(;it != main_node.end(); it++)
    {
	PRInt32 dim = *it;
	if(dim >=0 && dim != important_dim)
	{
	    double weight = 0.0;
	    p_dimstat->GetAvrgWeightByDim(dim, &weight);
	    if(weight < 12)
	    {
		continue;
	    }
	    double sim = 0.0;
	    p_contentutil->GetSimilarityBetweenDims(important_dim, dim, &sim);

	    //Caculate weight of a dim
	    PRInt32 avrg_title_length = 54;
	    double a = -1 / (double) avrg_title_length;
	    weight = weight - avrg_title_length;
	    weight = a * weight * weight + avrg_title_length;

	    double w = weight * sim;
	    LOG <<"[ContentVarGen] FindTitleNode:w "<<w<<" sim "<<sim<<"\n";
	    if(w > title_dim_sim)
	    {
		title_dim_sim = w;
		title_dim = dim;
	    }
	}
    }

    if(title_dim >= 0)
    {
	nsCString title_xpath;
	p_attdim->GetDesc(title_dim, title_xpath);
	AppendParamToVariable(std::string("title"), std::string(title_xpath.get()));
    }

    return title_dim;
}
    
void ContentVarGen::FindOtherNode(PRInt32 * common_dims, PRUint32 dims_count, nsIDimStat * p_dimstat)
{
    double prob_date = 0.49;
    double prob_author = 0.59;
    double prob_source = 0.59;
    for(int i = 0; i < dims_count; i++)
    {
	//Analysis each common dim, maybe it is date, source or author.
	PRInt32 dim = common_dims[i];
	if(dim >= important_dim)
	{
	    break;
	}

	nsCString cstr_xpath;
	p_attdim->GetDesc(dim, cstr_xpath);
	std::string xpath(cstr_xpath.get());

	//Is it a date node
	double p_date = 0.0;
	p_contentutil->IsDateDim(dim, p_dimstat, &p_date);
	if(p_date >= prob_date)
	{
	    LOG << "[ContentVarGen] FindOtherNode:Find date node "<<xpath <<"\n";
	    std::string key("publishdate");
	    AppendParamToVariable(key, xpath);
	    prob_date = p_date;
	}
	
	//Is it a author node
	double p_author = 0.0;
	p_contentutil->IsAuthorDim(dim, p_dimstat, &p_author);
	if(p_author > prob_author)
	{
	    LOG << "[ContentVarGen] FindOtherNode:Find author node "<<dim <<"\n";
	    std::string key("author");
	    AppendParamToVariable(key, xpath);
	    prob_author = p_author;
	}

	//Is it a source node
	double p_source = 0.0;
	p_contentutil->IsSourceDim(dim, p_dimstat, &p_source);
	if(p_source > prob_source)
	{
	    LOG << "[ContentVarGen] FindOtherNode:Find source node "<<dim <<"\n";
	    std::string key("source");
	    AppendParamToVariable(key, xpath);
	    prob_source = p_source;
	}

	//Is author node and source node a same node.
	double prob = p_date + p_source + p_author;
	if(prob >= 1.0)
	{
	    LOG << "[ContentVarGen] FindOtherNode:This node is an attribute node "<<dim <<"\n";
	    std::string key("attr");
	    AppendParamToVariable(key, xpath);
	}

    }
}

void ContentVarGen::SetVar(std::string key, std::string value)
{
    //LOG << "[ContentVarGen] SetVar:key "<<key<<" value "<<value<<"\n";
    m_vars[key] = value;
}

void ContentVarGen::AppendParamToVariable(std::string key, std::string value)
{
    std::string old_var = m_vars[key];
    if(old_var.size() > 0)
    {
	std::string new_value = ConcatTwoParams(old_var, value);
	SetVar(key, new_value);
    }
    else
    {
	SetVar(key, value);
    }
}

void ContentVarGen::ConfirmAdvertiseNode(PRInt32 * common_dims, PRUint32 dims_count, std::list<PRInt32> & main_node)
{
    std::set<PRInt32> set_main_node(main_node.begin(), main_node.end());
    for(PRUint32 i = 0; i < dims_count; i++)
    {
	PRInt32 dim = common_dims[i];
	std::set<PRInt32>::iterator it = set_main_node.find(dim);
	if(it == set_main_node.end())
	{
	    //It is an advertise node.
	    nsCString xpath;
	    p_attdim->GetDesc(dim, xpath);
	    AppendParamToVariable(std::string("ad"), std::string(xpath.get()));
	}
    }
}

void ContentVarGen::PrintTrainingResults()
{
    std::map<std::string, std::string>::iterator it = m_vars.begin();
    for(;it != m_vars.end(); it++)
    {
	std::string key = it->first;
	std::string value = it->second;
	LOG << "[ContentVarGen] PrintTrainingResults:key "<<key<<" value "<<value<<"\n";
    }
}
