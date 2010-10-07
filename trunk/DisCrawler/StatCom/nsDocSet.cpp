#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsDocSet.h"
#include <iostream>
#include <sstream>
#include "property.h"
NS_IMPL_ISUPPORTS1(nsDocSet, nsIDocSet)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsDocSet)

static nsModuleComponentInfo components[] =
{
     {
	  NS_DOCSET_CLASSNAME,
	  NS_DOCSET_CID,
	  NS_DOCSET_CONTRACTID,
	  nsDocSetConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsDocSetModule", components)


nsDocSet::nsDocSet()
{
  /* member initializers and constructor code */
}

nsDocSet::~nsDocSet()
{
  /* destructor code */
}

/* long GetDocCount (); */
NS_IMETHODIMP nsDocSet::GetDocCount(PRInt32 *_retval )
{
     *_retval=docs.Count();
     return NS_OK;
}

/* nsIDOMDocument GetDocByIndex (in long index); */
NS_IMETHODIMP nsDocSet::GetDocByIndex(PRInt32 index, nsIDOMDocument **_retval )
{
     if(index<docs.Count())
     {
	  *_retval=docs[index];
	  NS_ADDREF(*_retval);
	  return NS_OK;
     }else
     {
	  return NS_ERROR_FAILURE;
     }
}

/* void AddDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDocSet::AddDocument(nsIDOMDocument *doc)
{
     docs.AppendObject(doc);
     return NS_OK;
}
