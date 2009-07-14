#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsColAtt.h"
#include <iostream>
#include <sstream>
#include "sha1.h"
#include "property.h"
NS_IMPL_ISUPPORTS1(nsColAtt, nsIColAtt)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsColAtt)

static nsModuleComponentInfo components[] =
{
     {
	  NS_COLATT_CLASSNAME,
	  NS_COLATT_CID,
	  NS_COLATT_CONTRACTID,
	  nsColAttConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsColAttModule", components)




nsColAtt::nsColAtt()
:Id(0),
     chlId(0)
{
     /* member initializers and constructor code */
}

nsColAtt::~nsColAtt()
{
     /* destructor code */
}

/* attribute long Id; */
NS_IMETHODIMP nsColAtt::GetId(PRInt32 *aId)
{
     *aId=Id;
     return NS_OK;
}
NS_IMETHODIMP nsColAtt::SetId(PRInt32 aId)
{
     Id=aId;
     return NS_OK;
}
/* attribute long ChlId; */
NS_IMETHODIMP nsColAtt::GetChlId(PRInt32 *aChlId)
{
     *aChlId=chlId;
     return NS_OK;
}
NS_IMETHODIMP nsColAtt::SetChlId(PRInt32 aChlId)
{
     chlId=aChlId;
     return NS_OK;
}

/* attribute AUTF8String Hash; */
NS_IMETHODIMP nsColAtt::GetHash(nsACString & aHash)
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
NS_IMETHODIMP nsColAtt::SetHash(const nsACString & aHash)
{
     Hash=aHash;
     return NS_OK;
}

/* attribute AUTF8String Url; */
NS_IMETHODIMP nsColAtt::GetUrl(nsACString & aUrl)
{
     aUrl=Url;
     return NS_OK;
}
NS_IMETHODIMP nsColAtt::SetUrl(const nsACString & aUrl)
{
     Url=aUrl;
     return NS_OK;
}

/* attribute AUTF8String Name; */
NS_IMETHODIMP nsColAtt::GetName(nsACString & aName)
{
     aName=Name;
     return NS_OK;
}
NS_IMETHODIMP nsColAtt::SetName(const nsACString & aName)
{
     Name=aName;
     return NS_OK;
}
/* attribute AUTF8String Alias; */
NS_IMETHODIMP nsColAtt::GetAlias(nsACString & aAlias)
{
     aAlias=Alias;
    return NS_OK;
}
NS_IMETHODIMP nsColAtt::SetAlias(const nsACString & aAlias)
{
     Alias=aAlias;
    return NS_OK;
}

/* void SetCOL (in AUTF8String name, in AUTF8String url, in long chlId); */
NS_IMETHODIMP nsColAtt::SetCOL(const nsACString & name, const nsACString & url, PRInt32 chlId)
{
     this->Name=name;
     this->Url=url;
     this->chlId=chlId;
     return NS_OK;
}


