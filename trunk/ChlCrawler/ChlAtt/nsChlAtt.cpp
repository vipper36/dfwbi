#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsChlAtt.h"
#include <iostream>
#include <sstream>
#include "sha1.h"
#include "property.h"
NS_IMPL_ISUPPORTS1(nsChlAtt, nsIChlAtt)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsChlAtt)

static nsModuleComponentInfo components[] =
{
     {
	  NS_CHLATT_CLASSNAME,
	  NS_CHLATT_CID,
	  NS_CHLATT_CONTRACTID,
	  nsChlAttConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsChlAttModule", components)




nsChlAtt::nsChlAtt()
:Id(0)
{
     /* member initializers and constructor code */
}

nsChlAtt::~nsChlAtt()
{
     /* destructor code */
}

/* attribute long Id; */
NS_IMETHODIMP nsChlAtt::GetId(PRInt32 *aId)
{
     *aId=Id;
     return NS_OK;
}
NS_IMETHODIMP nsChlAtt::SetId(PRInt32 aId)
{
     Id=aId;
     return NS_OK;
}

/* attribute AUTF8String Hash; */
NS_IMETHODIMP nsChlAtt::GetHash(nsACString & aHash)
{
     if(Url.Length()>0&&Hash.Length()==0)
     {
	  SHA1 sha;
	  sha.Reset();
	  
	  sha << Url.get();
	  unsigned message_digest[5];
	  sha.Result(message_digest);
	  std::stringstream ss;
	  for(int i=0;i<5;i++)
	  {
	       ss<<std::hex<<message_digest[i];
	  }
	  Hash=nsCString((ss.str().c_str()));
     }
     aHash=Hash;
     return NS_OK;
}
NS_IMETHODIMP nsChlAtt::SetHash(const nsACString & aHash)
{
     Hash=aHash;
     return NS_OK;
}

/* attribute AUTF8String Url; */
NS_IMETHODIMP nsChlAtt::GetUrl(nsACString & aUrl)
{
     aUrl=Url;
     return NS_OK;
}
NS_IMETHODIMP nsChlAtt::SetUrl(const nsACString & aUrl)
{
     Url=aUrl;
     return NS_OK;
}

/* attribute AUTF8String Name; */
NS_IMETHODIMP nsChlAtt::GetName(nsACString & aName)
{
     aName=Name;
     return NS_OK;
}
NS_IMETHODIMP nsChlAtt::SetName(const nsACString & aName)
{
     Name=aName;
     return NS_OK;
}

/* attribute AUTF8String XPath; */
NS_IMETHODIMP nsChlAtt::GetXPath(nsACString & aXPath)
{
     aXPath=XPath;
     return NS_OK;
}
NS_IMETHODIMP nsChlAtt::SetXPath(const nsACString & aXPath)
{
     XPath=aXPath;
     return NS_OK;
}

/* void SetCHL (in AUTF8String name, in AUTF8String url); */
NS_IMETHODIMP nsChlAtt::SetCHL(const nsACString & name, const nsACString & url)
{
     Name=name;
     Url=url;
     return NS_OK;
}
