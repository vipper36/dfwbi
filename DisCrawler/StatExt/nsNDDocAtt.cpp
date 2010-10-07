#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMDocument.h"
#include "nsNetUtil.h"
#include "nsNDDocAtt.h"
#include "nsIAttVec.h"
#include "nsIDOMNodeList.h"
#include "nsIDOMElement.h"
#include "nsIXpathUtil.h"
#include "nsISupportsArray.h"
#include "nsISupports.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMHTMLCollection.h"
#include <iostream>
#include <sstream>
#include <stack>
#include "math.h"
#include "property.h"
#include "StyleCompare.h"
#define VISUALAREA 1024*768

NS_IMPL_ISUPPORTS1(nsNDDocAtt, nsIDocAtt)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsNDDocAtt)

static nsModuleComponentInfo components[] =
{
     {
	  NS_NDDOCATT_CLASSNAME,
	  NS_NDDOCATT_CID,
	  NS_NDDOCATT_CONTRACTID,
	  nsNDDocAttConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsNDDocAttModule", components)



nsNDDocAtt::nsNDDocAtt()
:m_docs(nsnull)
{
     nsresult rv;
     vset=do_CreateInstance("@nyapc.com/XPCOM/nsAttSet;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"nsAttSet inti erroe!\n";;
     }
     domUtil=do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"nsDomAttUtil inti erroe!\n";;
     }
}

nsNDDocAtt::~nsNDDocAtt()
{
  /* destructor code */
}
/* attribute nsIAttDim dim; */
NS_IMETHODIMP nsNDDocAtt::GetDim(nsIAttDim * *aDim)
{
     *aDim=vdim;
     NS_ADDREF(*aDim);
     return NS_OK;
}
NS_IMETHODIMP nsNDDocAtt::SetDim(nsIAttDim * aDim)
{
     vdim=aDim;
     return NS_OK;
}


/* long GetVectorCount (); */
NS_IMETHODIMP nsNDDocAtt::GetVectorCount(PRInt32 *_retval )
{
     PRInt32 len=0;
     vset->GetLength(&len);
     *_retval=len;
     return NS_OK;
}

/* nsIAttVec GetVectorByIndex (in long index); */
NS_IMETHODIMP nsNDDocAtt::GetVectorByIndex(PRInt32 index, nsIAttVec **_retval )
{
     nsCOMPtr<nsIAttVec> res;
     vset->GetVectorByIndex(index,getter_AddRefs(res));
     *_retval=res;
     NS_ADDREF(*_retval);
     return NS_OK;
}

/* nsIAttSet GetResult (); */
NS_IMETHODIMP nsNDDocAtt::GetResult(nsIAttSet **_retval)
{
     *_retval=vset;
     NS_ADDREF(*_retval);
     return NS_OK;
}
bool nsNDDocAtt::GetLinkAtt(nsIDOMDocument *domdoc)
{
     
     nsCOMPtr<nsIDOMHTMLDocument> domhtml=do_QueryInterface(domdoc);
     nsCOMPtr<nsIDOMHTMLCollection> links(nsnull);
     domhtml->GetLinks(getter_AddRefs(links));

     if(links!=nsnull)
     {
	  PRUint32 len;
	  links->GetLength(&len);
	  for(PRUint32 i=0;i<len;i++)
	  {
	       nsCOMPtr<nsIDOMNode> aLink(nsnull);
	       links->Item(i,getter_AddRefs(aLink));
	       if(aLink!=nsnull)
	       {
		    PRBool isLink=PR_FALSE;
		    domUtil->IsLinkNotInCal(aLink,&isLink);
		    if(isLink)
		    { 
			 nsCOMPtr<nsIAttVec> tmpV=do_CreateInstance("@nyapc.com/XPCOM/nsAttVec;1");
			 if(tmpV!=nsnull)
			 {
			      tmpV->SetDoc(domdoc);
			      tmpV->SetNode(aLink);
			      vset->AppendVector(tmpV);
			 }
		    }
		    
		    
	       }
	  }
     }
     return true;
}
/* void AddDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsNDDocAtt::AddDocument(nsIDOMDocument *doc)
{
     if(doc!=nsnull)
     {
	  if(m_docs==nsnull)
	  {
	       nsresult rv;
	       m_docs=do_CreateInstance("@nyapc.com/XPCOM/nsDocSet;1",&rv);
	       if (NS_FAILED(rv))
	       {
		    return rv;
	       }
	  }
	  m_docs->AddDocument(doc);
	  GetLinkAtt(doc);
     }
     
     return NS_OK;
}




