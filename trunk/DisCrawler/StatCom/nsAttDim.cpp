#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsAttDim.h"
#include <iostream>
#include <sstream>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsAttDim, nsIAttDim)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsAttDim)

static nsModuleComponentInfo components[] =
{
     {
	  NS_ATTDIM_CLASSNAME,
	  NS_ATTDIM_CID,
	  NS_ATTDIM_CONTRACTID,
	  nsAttDimConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsAttDimModule", components)

nsAttDim::nsAttDim()
{
  /* member initializers and constructor code */
}

nsAttDim::~nsAttDim()
{
  /* destructor code */
}

/* long GetCount (); */
NS_IMETHODIMP nsAttDim::GetCount(PRInt32 *_retval )
{
     *_retval=dims.size();
     return NS_OK;
}

/* long GetDimId (in AUTF8String desc); */
NS_IMETHODIMP nsAttDim::GetDimId(const nsACString & desc, PRInt32 *_retval )
{
     nsCString nsDesc(desc);
     std::string descStr(nsDesc.get());
     std::map<std::string,int>::iterator it=dims.find(descStr);
     if(it!=dims.end())
     {
	  *_retval=it->second;
	  return NS_OK;
     }else
     {
	  *_retval=-1;
	  return NS_ERROR_FAILURE;
     }
}

/* void AddDim (in long id, in AUTF8String desc); */
NS_IMETHODIMP nsAttDim::AddDim(PRInt32 id, const nsACString & desc)
{
     nsCString nsDesc(desc);
     std::string descStr(nsDesc.get());
     std::map<std::string,int>::iterator it=dims.find(descStr);
     if(it!=dims.end())
     {
	  it->second=id;
     }else
     {
	  dims.insert(std::make_pair(descStr,id));
     }
     return NS_OK;
}

/* AUTF8String GetDesc (in long id); */
NS_IMETHODIMP nsAttDim::GetDesc(PRInt32 id, nsACString & _retval )
{
     for(std::map<std::string,int>::iterator it=dims.begin();it!=dims.end();++it)
     {
	  if(id==it->second)
	  {
	       nsCString nsDesc(it->first.c_str());
	       _retval=nsDesc;
	       break;
	  }
     }
     return NS_OK;
}
