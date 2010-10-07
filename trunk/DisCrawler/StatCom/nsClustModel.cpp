#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsClustModel.h"
#include <iostream>
#include <sstream>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsClustModel, nsIClustModel)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsClustModel)

static nsModuleComponentInfo components[] =
{
     {
	  NS_CLUSTMODEL_CLASSNAME,
	  NS_CLUSTMODEL_CID,
	  NS_CLUSTMODEL_CONTRACTID,
	  nsClustModelConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsClustModelModule", components)

nsClustModel::nsClustModel()
{
  /* member initializers and constructor code */
}

nsClustModel::~nsClustModel()
{
  /* destructor code */
}
/* attribute nsIAttVec modelAtt; */
// NS_IMETHODIMP nsClustModel::GetModelAtt(nsIAttVec * *aModelAtt)
// {
//      *aModelAtt=m_att;
//      NS_ADDREF(*aModelAtt);
//      return NS_OK;
// }
// NS_IMETHODIMP nsClustModel::SetModelAtt(nsIAttVec * aModelAtt)
// {
//      m_att=aModelAtt;
//      return NS_OK;
// }
/* long GetClassCount (); */
NS_IMETHODIMP nsClustModel::GetClassCount(PRInt32 *_retval )
{
     if(c_atts.Count()==c_sets.Count())
     {
	  *_retval=c_atts.Count();
     
	  return NS_OK;
     }else
     {
     
	  return NS_ERROR_FAILURE;
     }
}

/* nsIAttVec GetClassAtt (in long classid); */
NS_IMETHODIMP nsClustModel::GetClassAtt(PRInt32 classid, nsIAttVec **_retval )
{
     if(classid<c_atts.Count())
     {
	  *_retval=c_atts[classid];
	  NS_ADDREF(*_retval);
	  return NS_OK;
     }else
     {
	  return NS_ERROR_FAILURE;
     }
}

/* nsIAttSet GetClassSet (in long classid); */
NS_IMETHODIMP nsClustModel::GetClassSet(PRInt32 classid, nsIAttSet **_retval )
{
     if(classid<c_sets.Count())
     {
	  *_retval=c_sets[classid];
	  NS_ADDREF(*_retval);
	  return NS_OK;
     }else
     {
	  return NS_ERROR_FAILURE;
     }
}
/* void AppendClass (in nsIAttSet set, in nsIAttVec att); */
NS_IMETHODIMP nsClustModel::AppendClass(nsIAttSet *set, nsIAttVec *att)
{
     if(c_atts.Count()==c_sets.Count())
     {
	  c_atts.AppendObject(att);
	  c_sets.AppendObject(set);
	  return NS_OK;
     }else
     {
	  return NS_ERROR_FAILURE;
     }
}
/* void ClearModel (); */
NS_IMETHODIMP nsClustModel::ClearModel()
{
     if(c_atts.Count()>0)
	  c_atts.Clear();
     if(c_atts.Count()>0)
	  c_sets.Clear();
     return NS_OK;
}
