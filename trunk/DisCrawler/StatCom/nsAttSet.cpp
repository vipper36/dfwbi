#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsAttSet.h"
#include <iostream>
#include <sstream>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsAttSet, nsIAttSet)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsAttSet)

static nsModuleComponentInfo components[] =
{
     {
	  NS_ATTSET_CLASSNAME,
	  NS_ATTSET_CID,
	  NS_ATTSET_CONTRACTID,
	  nsAttSetConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsAttSetModule", components)




nsAttSet::nsAttSet()
{
  /* member initializers and constructor code */
}

nsAttSet::~nsAttSet()
{
  /* destructor code */
}

/* long GetLength (); */
NS_IMETHODIMP nsAttSet::GetLength(PRInt32 *_retval )
{
     *_retval=vects.Count();
     return NS_OK;
}


/* void SetVetor (in long index, in nsIAttVec value); */
NS_IMETHODIMP nsAttSet::SetVetor(PRInt32 index, nsIAttVec *value)
{
     if(index<vects.Count())
     {
	  vects.ReplaceObjectAt(value,index);
	  return NS_OK;
     }else
     {
	  return NS_ERROR_FAILURE;
     }
}

/* void AppendVector (in nsIAttSet value); */
NS_IMETHODIMP nsAttSet::AppendVector(nsIAttVec *value)
{
     vects.AppendObject(value);
     return NS_OK;
}
/* void AppendSet (in nsIAttSet set); */
NS_IMETHODIMP nsAttSet::AppendSet(nsIAttSet *set)
{

     PRInt32 len=0;
     set->GetLength(&len);
     for(int i=0;i<len;i++)
     {
	  nsCOMPtr<nsIAttVec> avec(nsnull);
	  set->GetVectorByIndex(i, getter_AddRefs(avec));
	  if(avec!=nsnull)
	       AppendVector(avec);
     }
     return NS_OK;
}
/* nsIAttVec GetVectorByIndex (in long index); */
NS_IMETHODIMP nsAttSet::GetVectorByIndex(PRInt32 index, nsIAttVec **_retval)
{
     if(index<vects.Count())
     {
	  *_retval=vects[index];
	  NS_ADDREF(*_retval);
	  return NS_OK;
     }else
     {
	  return NS_ERROR_FAILURE;
     }
}

