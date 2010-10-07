#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "ThresholdCluster.h"
#include <iostream>
#include <sstream>
#include "math.h"
#include "property.h"
#include <KMlocal.h>

NS_IMPL_ISUPPORTS1(ThresholdCluster, nsICluster)

NS_GENERIC_FACTORY_CONSTRUCTOR(ThresholdCluster)

static nsModuleComponentInfo components[] =
{
     {
	  THRESHOLDCLUSTER_CLASSNAME,
	  THRESHOLDCLUSTER_CID,
          THRESHOLDCLUSTER_CONTRACTID,
	  ThresholdClusterConstructor,
     }
};
NS_IMPL_NSGETMODULE("ThresholdClusterModule", components)


ThresholdCluster::ThresholdCluster()
{
     nsresult rv;
     m_model=do_CreateInstance("@nyapc.com/XPCOM/nsClustModel;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"[ThresholdCluster] Constructor:Init model error!\n";
     }
}

ThresholdCluster::~ThresholdCluster()
{
     /* destructor code */
}

/* void SetAtt (in nsIAttSet set); */
NS_IMETHODIMP ThresholdCluster::SetAtt(nsIAttSet *set)
{
     m_atts=set;
     return NS_OK;
}
/* void SetDoubleParam (in AUTF8String name, in double value); */
NS_IMETHODIMP ThresholdCluster::SetDoubleParam(const nsACString & name, double value)
{
     nsCString nsName(name);
     std::string nameStr(nsName.get());
     dParams.insert(make_pair(nameStr,value));
     return NS_OK;
}


/* void SetStringParam (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP ThresholdCluster::SetStringParam(const nsACString & name, const nsACString & value)
{
     nsCString nsName(name);
     nsCString nsValue(value);
     std::string nameStr(nsName.get());
     std::string valueStr(nsValue.get());
     sParams.insert(make_pair(nameStr,valueStr));
     return NS_OK;
}

/* void CaculModel (); */
NS_IMETHODIMP ThresholdCluster::CaculModel()
{
    PRInt32 doc_count = 0;
    m_atts->GetLength(&doc_count);
    LOG << "[ThresholdCluster] CaculModel:There are "<<doc_count<<" documents.\n";
    for(int i = 0; i < doc_count; i++)
    {
	nsCOMPtr<nsIAttVec> vec;
	m_atts->GetVectorByIndex(i,getter_AddRefs(vec));
	int classid = FindSimilarClass(vec);
	if(classid < 0)
	{
	    //Create a new Class and add into ClusterModel.
	    LOG << "[ThresholdCluster] CaculModel:Create a new class.\n";
	    nsresult rv;
	    nsCOMPtr<nsIAttSet> p_attset = do_CreateInstance("@nyapc.com/XPCOM/nsAttSet;1",&rv);
	    if(!NS_FAILED(rv))
	    {
		p_attset->AppendVector(vec);
		//Add a class into model.
		m_model->AppendClass(p_attset, vec);
	    }
	}
	else
	{
	    //Get a Class from ClusterModel,
	    //and add this Vector into this Class.
	    LOG << "[ThresholdCluster] CaculModel:Add doc into a class " << classid <<"\n";
	    nsCOMPtr<nsIAttSet> p_attset;
	    m_model->GetClassSet(classid, getter_AddRefs(p_attset));

	    p_attset->AppendVector(vec);
	}
    }
    return NS_OK;
}

/* nsIClustModel GetResultModel (); */
NS_IMETHODIMP ThresholdCluster::GetResultModel(nsIClustModel **_retval )
{
     *_retval=m_model;
     NS_ADDREF(*_retval);
     return NS_OK;
}

int ThresholdCluster::FindSimilarClass(nsIAttVec * vec)
{
    PRInt32 ret = -1;
    PRInt32 class_count = 0;
    double th = 0.9;
    std::map<std::string,double>::iterator it = dParams.find("threshold");
    if(it != dParams.end())
    {
	th = it->second;
    }
    m_model->GetClassCount(&class_count);
    for(int classid = 0; classid < class_count; classid++)
    {
	nsCOMPtr<nsIAttVec> cp;
	m_model->GetClassAtt(classid, getter_AddRefs(cp));
	if(nsnull != cp)
	{
	    //Caculate the similarity of two vectors.
	    double sim = CaculSimilarity(vec, cp);
	    LOG << "[ThresholdCluster] FindSimilarClass:similarity with class " << classid << " is " << sim << "\n";
	    if(sim > th)
	    {
		ret = classid;
		break;
	    }
	}
    }

    return ret;
}

double ThresholdCluster::CaculSimilarity(nsIAttVec * v1, nsIAttVec * v2)
{
    double sim = 0.0;

    double d1 = CaculDot(v1,v1);
    double d2 = CaculDot(v2,v2);
    double dot = CaculDot(v1,v2);

    sim = dot / sqrt(d1 * d2);

    return sim;
}

double ThresholdCluster::CaculDot(nsIAttVec * v1, nsIAttVec * v2)
{
    double dot = 0.0;
    PRUint32 len1,len2;
    PRInt32 * dims1;
    len1 = len2 = 0;
    dims1 = NULL;

    v1->GetDims(&dims1,&len1);
    for(int i = 0; i < len1; i++)
    {
	PRInt32 dimid = dims1[i];
	PRBool contain = false;
	v2->Contains(dimid, &contain);
	if(contain)
	{
	    double value1 = 0.0;
	    double value2 = 0.0;
	    v1->GetValueByDim(dimid, &value1);
	    v2->GetValueByDim(dimid, &value2);
	    dot += value1 * value2;
	}
    }
    delete dims1;

    return dot;
}

