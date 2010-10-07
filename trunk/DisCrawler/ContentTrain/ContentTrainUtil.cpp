#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "ContentTrainUtil.h"
#include "nsIXpathUtil.h"
#include "nsISupportsArray.h"
#include "nsIDOMElement.h"
#include "nsISupports.h"
#include "nsIDOMDocument.h"
#include "nsIDOMNode.h"
#include "nsIAttVec.h"
#include "nsIAttSet.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <limits.h>
#include "math.h"
#include <list>
#include "property.h"
#include "BlockUtils.h"
#include "analysis.h"

NS_IMPL_ISUPPORTS1(ContentTrainUtil, nsIContentTrainUtil)

NS_GENERIC_FACTORY_CONSTRUCTOR(ContentTrainUtil)

static nsModuleComponentInfo components[] =
{
     {
	  CONTENTTRAINUTIL_CLASSNAME,
	  CONTENTTRAINUTIL_CID,
	  CONTENTTRAINUTIL_CONTRACTID,
	  ContentTrainUtilConstructor,
     }
};
NS_IMPL_NSGETMODULE("ContentVarGenModule", components)

ContentTrainUtil::ContentTrainUtil()
{
    /* member initializers and constructor code */
    nsresult rv;
    p_domutil=do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1",&rv);
    if (NS_FAILED(rv))
    {
	LOG<<"[ContentTrainUtil] Constructor:Init nsDomAttUtil error!\n";
    }
}

ContentTrainUtil::~ContentTrainUtil()
{
  /* destructor code */
}

/* void FindCommonDim ([array, size_is (id_size)] out long dims, out PRUint32 id_size); */
NS_IMETHODIMP ContentTrainUtil::FindCommonDim(PRInt32 **dims , PRUint32 *id_size )
{
    PRInt32 * common_dims = NULL;
    PRUint32 common_dim_count = 0;
    PRInt32 doc_count = 0;
    p_attset->GetLength(&doc_count);

    for(PRInt32 i = 0; i < doc_count; i++)
    {
	nsCOMPtr<nsIAttVec> vector;
	p_attset->GetVectorByIndex(i, getter_AddRefs(vector));
	if(NULL == common_dims)
	{
	    vector->GetDims(&common_dims, &common_dim_count);
	}
	else
	{
	    PRInt32 * dims = NULL;
	    PRUint32 dim_count = 0;
	    vector->GetDims(&dims, &dim_count);
	    ElimitDiffDim(common_dims, dims, common_dim_count, dim_count);
	    delete dims;
	}
    }

    //Collect common xpath_id.
    std::list<PRInt32> l_common_dim;
    for(int i = 0; i < common_dim_count; i++)
    {
	if(common_dims[i] >= 0)
	{
	    l_common_dim.push_back(common_dims[i]);
	}
    }

    //Write common xpath_id into return buffer.
    *id_size = l_common_dim.size();
    *dims = new PRInt32[l_common_dim.size()];
    int pos = 0;
    for(std::list<PRInt32>::iterator it = l_common_dim.begin(); it != l_common_dim.end(); it++)
    {
	(*dims)[pos++] = *it;
    }

    delete common_dims;
    return NS_OK;
}

/* void SetVectorSet (in nsIAttSet attset); */
NS_IMETHODIMP ContentTrainUtil::SetVectorSet(nsIAttSet *attset)
{
    p_attset = attset;
    return NS_OK;
}

/* void SetAttDim (in nsIAttDim attdim); */
NS_IMETHODIMP ContentTrainUtil::SetAttDim(nsIAttDim *attdim)
{
    p_attdim = attdim;
    return NS_OK;
}

/* double GetSimilarityByDim (in long dimid); */
NS_IMETHODIMP ContentTrainUtil::GetSimilarityByDim(PRInt32 dimid, double *_retval )
{
    PRInt32 doc_count = 0;
    nsresult rv;
    p_attset->GetLength(&doc_count);
    //LOG<<"[ContentTrainUtil] GetSimilarityByDim:There are "<<doc_count<<" docs\n";

    if(doc_count <= 1)
    {
	//There is only one doc in the set,
	//so each xpath is invalid.
	*_retval = 1.0;
	return NS_OK;
    }

    nsCString xpath;
    p_attdim->GetDesc(dimid, xpath);
    //LOG << "[ContentTrainUtil] GetSimilarityByDim:analysis xpath "<<xpath.get()<<"\n";
    double score = 0.0;
    int n = 0;
    for(int i = 0; i < doc_count - 1; i++)
    {
	nsCOMPtr<nsIAttVec> vec1;
	p_attset->GetVectorByIndex(i, getter_AddRefs(vec1));
	nsCOMPtr<nsIDOMDocument> doc1;
	vec1->GetDoc(getter_AddRefs(doc1));
	nsCOMPtr<nsIXpathUtil> p_xpathutil1 = do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1", &rv);
	p_xpathutil1->SetDocument(doc1);
	nsCString text1 = GetNodesTextByXpath(p_xpathutil1, xpath);

	for(int j = i+1; j < doc_count; j++)
	{
	    nsCOMPtr<nsIAttVec> vec2;
	    p_attset->GetVectorByIndex(j, getter_AddRefs(vec2));
	    nsCOMPtr<nsIXpathUtil> p_xpathutil2 = do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1", &rv);
	    nsCOMPtr<nsIDOMDocument> doc2;
	    vec2->GetDoc(getter_AddRefs(doc2));
	    p_xpathutil2->SetDocument(doc2);
	    nsCString text2 = GetNodesTextByXpath(p_xpathutil2, xpath);

	    n++;
	    double sim = 0.0;
	    //---Test Begin---
	    //std::string s_xpath(xpath.get());
	    //if(s_xpath.find("preart") > 0)
	    //    LOG << text1.get()<<"---------"<<text2.get()<<"\n";
	    //---Test end---
	    GetSimilarityBetweenStrings(text1, text2, &sim);
	    //---Test Begin---
	    //if(s_xpath.find("preart") > 0)
	    //    LOG << "-----sim "<<sim<<"\n";
	    //---Test end---
	    score += sim;
	}
    }

    *_retval = score / (double)n;
    return NS_OK;
}

/* double GetSimilarityBetweenStrings (in AUTF8String s1, in AUTF8String s2); */
NS_IMETHODIMP ContentTrainUtil::GetSimilarityBetweenStrings(const nsACString & s1, const nsACString & s2, double *_retval )
{
    if(s1.Compare(s2) == 0)
    {
	*_retval = 1.0;
    }
    else
    {
    	PRUint32 same_count = SameScore((const nsCString &)s1, (const nsCString &)s2);
	double sim = 2 * same_count / (double) (s1.Length() + s2.Length());
	sim = sim > 1.0 ? 1.0 : sim;
	*_retval = sim;
    }
    return NS_OK;
}

/* double GetSimilarityBetweenDims (in PRInt32 dim1, in PRInt32 dim2); */
NS_IMETHODIMP ContentTrainUtil::GetSimilarityBetweenDims(PRInt32 dim1, PRInt32 dim2, double *_retval )
{
    PRInt32 doc_count = 0;
    nsresult rv;
    p_attset->GetLength(&doc_count);

    if(doc_count < 1)
    {
	//There is no doc in the set.
	LOG<<"[ContentTrainUtil] GetSimilarityBetweenDims:There is no doc in the set.\n";
	return NS_OK;
    }

    nsCString xpath1,xpath2;
    p_attdim->GetDesc(dim1,xpath1);
    p_attdim->GetDesc(dim2,xpath2);
    if(xpath1.Length() == 0 || xpath2.Length() == 0)
    {
	LOG<<"[ContentTrainUtil] GetSimilarityBetweenDims:invalid dim id.\n";
	return NS_OK;
    }
    double score = 0.0;
    int n = 0;
    for(int i = 0; i < doc_count; i++)
    {
	nsCOMPtr<nsIAttVec> vec;
	p_attset->GetVectorByIndex(i, getter_AddRefs(vec));
	nsCOMPtr<nsIXpathUtil> p_xpathutil = do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1", &rv);
	nsCOMPtr<nsIDOMDocument> doc;
	vec->GetDoc(getter_AddRefs(doc));
	p_xpathutil->SetDocument(doc);
	nsCString text1 = GetNodesTextByXpath(p_xpathutil, xpath1);
	nsCString text2 = GetNodesTextByXpath(p_xpathutil, xpath2);
	
	double sim = 0.0;
	GetSimilarityBetweenStrings(text1, text2, &sim);
	n++;
	score += sim;
    }

    *_retval = score / (double)n;
    return NS_OK;
}

/* AUTF8String GetNodesTextByXpath (in nsIXpathUtil xpathutil, in AUTF8String xpath); */
NS_IMETHODIMP ContentTrainUtil::GetNodesTextByXpath(nsIXpathUtil *xpathutil, const nsACString & xpath, nsACString & _retval )
{
    nsCString ret = GetNodesTextByXpath(xpathutil, xpath);
    _retval = ret;
    return NS_OK;
}

/* double IsDateDim (in long dimid, in nsIDimStat dimstat); */
NS_IMETHODIMP ContentTrainUtil::IsDateDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval )
{
    PRInt32 doc_count = 0;
    p_attset->GetLength(&doc_count);
    
    nsresult rv;
    nsCOMPtr<nsIXpathUtil> p_xpathutil = do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1", &rv);
    if(NS_FAILED(rv))
    {
	*_retval = 0.0;
	return NS_OK;
    }

    double show_count = 1;
    dimstat->GetAvrgShowCountByDim(dimid, &show_count);
    if(show_count > 1)
    {
	LOG<<"[ContentTrainUtil] IsDateDim:show count greater than 1.\n";
	*_retval = 0.0;
	return NS_OK;
    }

    for(int i = 0; i < doc_count; i++)
    {
	//Check the node text of specify dim.
	//Get the doc first.
	nsCOMPtr<nsIAttVec> vec;
	p_attset->GetVectorByIndex(i, getter_AddRefs(vec));
	nsCOMPtr<nsIDOMDocument> doc;
	vec->GetDoc(getter_AddRefs(doc));

	//Get the node text secondly.
	nsCString xpath;
        p_attdim->GetDesc(dimid,xpath);
	p_xpathutil->SetDocument(doc);
	nsCOMPtr<nsISupportsArray> array;

	p_xpathutil->GetNodes(xpath, getter_AddRefs(array));

	if(nsnull != array)
	{
	    nsCOMPtr<nsIDOMNode> node;
	    nsCOMPtr<nsISupports> object;
	    array->GetElementAt(0, getter_AddRefs(object));
	    node = do_QueryInterface(object);

	    nsCString node_text;
	    p_domutil->GetNodeText(node, node_text);
	    //Is it a date node?
	    std::string text(node_text.get());
	    if(text.size() < 200){
	        float s = is_date_format(text);
	        bool b = has_word_copyright(text);
		if(!b)
	        {
                    if(s < 0.5)
		    {
			float prob_date = all_words_relate_date(text);
			if(prob_date > 0.8)
			{
			    *_retval = prob_date;
			    return NS_OK;
			}
		    }
		    else
		    {
			*_retval = s;
			return NS_OK;
		    }
		}
	    }
	}

    }
    *_retval = 0.0;
    return NS_OK;
}

/* double IsSourceDim (in long dimid, in nsIDimStat dimstat); */
NS_IMETHODIMP ContentTrainUtil::IsSourceDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval )
{
    PRInt32 doc_count = 0;
    p_attset->GetLength(&doc_count);
    
    nsresult rv;
    nsCOMPtr<nsIXpathUtil> p_xpathutil = do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1", &rv);
    if(NS_FAILED(rv))
    {
	return NS_OK;
    }

    double arvg_weight = 1.0;
    dimstat->GetAvrgWeightByDim(dimid, &arvg_weight);
    if(arvg_weight > 100)
    {
	LOG<<"[ContentTrainUtil] IsSourceDim:dim weight greater than 100.\n";
	*_retval = 0.0;
	return NS_OK;
    }

    for(int i = 0; i < doc_count; i++)
    {
	//Check the node text of specify dim.
	//Get the doc first.
	nsCOMPtr<nsIAttVec> vec;
	p_attset->GetVectorByIndex(i, getter_AddRefs(vec));
	nsCOMPtr<nsIDOMDocument> doc;
	vec->GetDoc(getter_AddRefs(doc));

	//Get the node text secondly.
	nsCString xpath;
        p_attdim->GetDesc(dimid,xpath);
	p_xpathutil->SetDocument(doc);
	nsCOMPtr<nsISupportsArray> array;

	nsCString node_text = GetNodesTextByXpath(p_xpathutil, xpath);
	std::string text(node_text.get());
	bool b = false;
	b = has_word_source(text);
	if(b)
	{
	    *_retval = 0.9;
	    return NS_OK;
	}
    }
    *_retval = 0.0;
    return NS_OK;
}

/* double isAuthorDim (in long dimid, in nsIDimStat dimstat); */
NS_IMETHODIMP ContentTrainUtil::IsAuthorDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval )
{
    PRInt32 doc_count = 0;
    p_attset->GetLength(&doc_count);
    
    nsresult rv;
    nsCOMPtr<nsIXpathUtil> p_xpathutil = do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1", &rv);
    if(NS_FAILED(rv))
    {
	return NS_OK;
    }

    double arvg_weight = 1.0;
    dimstat->GetAvrgWeightByDim(dimid, &arvg_weight);
    if(arvg_weight > 100)
    {
	LOG<<"[ContentTrainUtil] IsAuthorDim:dim weight greater than 100.\n";
	*_retval = 0.0;
	return NS_OK;
    }

    for(int i = 0; i < doc_count; i++)
    {
	//Check the node text of specify dim.
	//Get the doc first.
	nsCOMPtr<nsIAttVec> vec;
	p_attset->GetVectorByIndex(i, getter_AddRefs(vec));
	nsCOMPtr<nsIDOMDocument> doc;
	vec->GetDoc(getter_AddRefs(doc));

	//Get the node text secondly.
	nsCString xpath;
        p_attdim->GetDesc(dimid,xpath);
	p_xpathutil->SetDocument(doc);
	nsCOMPtr<nsISupportsArray> array;

	nsCString node_text = GetNodesTextByXpath(p_xpathutil, xpath);
	std::string text(node_text.get());
	bool b = false;
	b = has_word_author(text);
	if(b)
	{
	    *_retval = 0.9;
	    return NS_OK;
	}
    }
    return NS_OK;
}

void ContentTrainUtil::ElimitDiffDim(PRInt32 * dims1, PRInt32 * dims2, PRUint32 size1, PRUint32 size2)
{
    for(int i = 0; i < size1; i++)
    {
	PRInt32 dim = dims1[i];
	bool has_same_dimension = false;
	for(int j = 0; j < size2; j++)
	{
	    PRInt32 dim2 = dims2[j];
	    if(dim == dim2)
	    {
		//find common dimension
		has_same_dimension = true;
		break;
	    }
	}
	if(!has_same_dimension)
	{
	    dims1[i] = -1;
	}
    }
}

PRUint32 ContentTrainUtil::SameScore(const nsCString & s1, const nsCString & s2)
{
    int len = s1.Length() > s2.Length() ? s1.Length() : s2.Length();
    int d = 0;
    if (s1.Length() == 0 || s2.Length() == 0) {
        d = len;
    } else {
	Distance distance;
	std::string str1, str2;
        int max_len = 900;
        if (s1.Length() <= max_len)
            str1.append(s1.get());
        else
            str1.append(s1.get(), max_len);

        if (s2.Length() <= max_len)
            str2.append(s2.get());
        else
            str2.append(s2.get(), max_len);
        //LOG<<"s1:"<<s1.length()<<"\n";
        //LOG<<"s2:"<<s2.length()<<"\n";
        //const char * c1 = str1.c_str();
        //const char * c2 = str2.c_str();
        len = str1.length() > str2.length() ? str1.length() : str2.length();
        d = distance.LD(str1, str2);
    }
    PRUint32 same_count = 0;
    same_count = len - d;
    return same_count;
}

nsCString ContentTrainUtil::GetNodesTextByXpath(nsIXpathUtil * xpathutil, const nsACString & xpath)
{
    nsCString ret;

    nsCOMPtr<nsISupportsArray> array;
    xpathutil->GetNodes(xpath, getter_AddRefs(array));

    if(nsnull != array)
    {
	//
	PRUint32 count = 0;
        array->Count(&count);
	for(PRUint32 i = 0; i < count; i++)
	{
	    nsCOMPtr<nsIDOMNode> node;
	    nsCOMPtr<nsISupports> object;
	    array->GetElementAt(i, getter_AddRefs(object));
	    node = do_QueryInterface(object);

	    nsCString node_text;
	    p_domutil->GetNodeOwnText(node, node_text);
	    ret.Append(node_text);
	}
    }

    return ret;
}
