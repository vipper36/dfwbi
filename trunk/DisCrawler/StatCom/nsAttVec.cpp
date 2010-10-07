#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsAttVec.h"
#include <iostream>
#include <sstream>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsAttVec, nsIAttVec)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsAttVec)

static nsModuleComponentInfo components[] =
{
     {
	  NS_ATTVEC_CLASSNAME,
	  NS_ATTVEC_CID,
	  NS_ATTVEC_CONTRACTID,
	  nsAttVecConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsAttVecModule", components)



nsAttVec::nsAttVec()
{
  /* member initializers and constructor code */
}

nsAttVec::~nsAttVec()
{
  /* destructor code */
}
/* attribute nsIDOMDocument doc; */
NS_IMETHODIMP nsAttVec::SetDoc(nsIDOMDocument * aDoc)
{
     m_doc=aDoc;
     return NS_OK;
}
NS_IMETHODIMP nsAttVec::GetDoc(nsIDOMDocument * *aDoc)
{
     *aDoc=m_doc;
     NS_ADDREF(*aDoc);
     return NS_OK;
}
/* attribute nsIDOMNode node; */
NS_IMETHODIMP nsAttVec::SetNode(nsIDOMNode * aNode)
{
     m_node=aNode;
     return NS_OK;
}


NS_IMETHODIMP nsAttVec::GetNode(nsIDOMNode * *aNode)
{
     *aNode=m_node;
     NS_ADDREF(*aNode);
     return NS_OK;
}

/* long GetLength (); */
NS_IMETHODIMP nsAttVec::GetLength(PRInt32 *_retval )
{
     *_retval=vect.size();
     return NS_OK;
}

/* void SetValue (in long dim, in double value); */
NS_IMETHODIMP nsAttVec::SetValue(PRInt32 dim, double value)
{
     if(vect.find(dim)!=vect.end())
     {
	  vect[dim]=value;
     }else
     {
	  vect.insert(std::make_pair(dim,value));
     }
     return NS_OK;
     
}
/* void AddValue (in long dim, in double value); */
NS_IMETHODIMP nsAttVec::AddValue(PRInt32 dim, double value)
{
     vect.insert(std::make_pair(dim,value));
     return NS_OK;
}
/* void AppendVector (in nsIAttVec vec); */
NS_IMETHODIMP nsAttVec::AppendVector(nsIAttVec *vec)
{
     PRInt32 *dims;
     PRUint32 len;
     vec->GetDims(&dims , &len);
     for(int i=0;i<len;i++)
     {
	  double value=.0;
	  vec->GetValueByDim(dims[i], &value);
	  AddValue(dims[i],value);
     }
     delete [] dims;
     return NS_OK;
}
/* void SetVector (in nsIAttVec vec); */
NS_IMETHODIMP nsAttVec::SetVector(nsIAttVec *vec)
{
     vec->GetDoc(getter_AddRefs(m_doc));
     vec->GetNode(getter_AddRefs(m_node));
     AppendVector(vec);
     return NS_OK;
}
/* boolean Contains (in long dim); */
NS_IMETHODIMP nsAttVec::Contains(PRInt32 dim, PRBool *_retval)
{
     if(vect.find(dim)!=vect.end())
     {
	  *_retval=PR_TRUE;
     }else
     {
	  *_retval=PR_FALSE;
     }
     
     return NS_OK;
}

/* double GetValueByDim (in long dim); */
NS_IMETHODIMP nsAttVec::GetValueByDim(PRInt32 dim, double *_retval)
{
    // for(std::map<int,double>::iterator it=vect.begin();it!=vect.end();++it)
    // {
//	  LOG<<it->first<<":"<<it->second<<"\n";
  //   }
     if(vect.find(dim)!=vect.end())
     {
	  *_retval=vect[dim];
	  return NS_OK;
     }else
     {
	  return NS_ERROR_FAILURE;
     }
}
/* void GetDims ([array, size_is (cv_size)] out long dims, out unsigned long cv_size); */
NS_IMETHODIMP nsAttVec::GetDims(PRInt32 **dims , PRUint32 *cv_size)
{
     *cv_size=vect.size();
     *dims=new int[*cv_size];
     int i=0;
     for(std::map<int,double>::iterator it=vect.begin();it!=vect.end();++it)
     {
	  (*dims)[i]=it->first;
	  i++;
     }
     return NS_OK;
}




