#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsIUrlAtt.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMHTMLCollection.h"
#include "nsColBridge.h"
#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <vector>
#include "nsIDOM3Node.h"
#include "nsIDOMHTMLAnchorElement.h"
#include "nsIDOMHTMLLinkElement.h"
#include "nsIColAtt.h"
#include "sha1.h"
#include "property.h"
#include <regex.h>
#include <stdlib.h>

NS_IMPL_ISUPPORTS1(nsColBridge, nsIColBridge)
NS_GENERIC_FACTORY_CONSTRUCTOR(nsColBridge)

static nsModuleComponentInfo components[] =
{
  {
    NS_COLBRIDGE_CLASSNAME,
    NS_COLBRIDGE_CID,
    NS_COLBRIDGE_CONTRACTID,
    nsColBridgeConstructor,
  }
};
NS_IMPL_NSGETMODULE("nsColBridgeModule", components)


/* Implementation file */


nsColBridge::nsColBridge()
{
  /* member initializers and constructor code */
}

nsColBridge::~nsColBridge()
{
  /* destructor code */
}

/* long SetColSource (in AUTF8String src, in AUTF8String comName); */
NS_IMETHODIMP nsColBridge::SetColSource(const nsACString & src, const nsACString & comName)
{
     nsresult rv;
     nsCString tmpName(comName);
     ColSrc = do_CreateInstance(tmpName.get(), &rv);

     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  nsIChlIO  Error:"<<rv<<"\n";
	  return rv;
     }
     nsCString ioSrc(src);
     rv=ColSrc->SetLocation(ioSrc);
     return rv;
}
/* long SetUrlSource (in AUTF8String src, in AUTF8String comName); */
NS_IMETHODIMP nsColBridge::SetUrlSource(const nsACString & src, const nsACString & comName)
{
     nsresult rv;
     nsCString tmpName(comName);
     urlSrc=do_CreateInstance(tmpName.get(),&rv);

     if (NS_FAILED(rv))
     {
 	  LOG<<"Get  nsIChlIO  Error:"<<rv<<"\n";
	  return rv;
     }
     nsCString ioSrc(src);
     rv=urlSrc->SetLocation(ioSrc);
     return rv;
}
/* void GetColName (in AUTF8String url, out AUTF8String name); */
NS_IMETHODIMP nsColBridge::GetColName(const nsACString & url, nsACString & name)
{
     PRUint32 urlId=0;
     urlSrc->GetURLID(url, &urlId);
     if(urlId>0)
     {
	  nsCOMPtr<nsIUrlAtt> urlatt;
	  urlSrc->GetURLbyID(getter_AddRefs(urlatt), urlId);
	  if(urlatt!=nsnull)
	  {
	       PRInt32 colId=0;
	       urlatt->GetColId(&colId);
	       if(colId>0)
	       {
		    nsCOMPtr<nsIColAtt> colatt;
		    ColSrc->GetColByID(getter_AddRefs(colatt), colId);
		    if(colatt!=nsnull)
		    {
			 nsCString tmpName;
			 colatt->GetName(tmpName);
			 name=tmpName;
		    }
	       }
	  }
     }
     return NS_OK;
}


