#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsUrlAtt.h"
#include <iostream>
#include <sstream>
#include "sha1.h"
#include "property.h"
NS_IMPL_ISUPPORTS1(nsUrlAtt, nsIUrlAtt)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsUrlAtt)

static nsModuleComponentInfo components[] =
{
  {
    NS_URLATT_CLASSNAME,
    NS_URLATT_CID,
    NS_URLATT_CONTRACTID,
    nsUrlAttConstructor,
  }
};
NS_IMPL_NSGETMODULE("nsUrlAttModule", components)


nsUrlAtt::nsUrlAtt()
:colId(0),
     nextId(0),
     parId(0),
     Layer(0)
{
  /* member initializers and constructor code */
}

nsUrlAtt::~nsUrlAtt()
{
  /* destructor code */
}

NS_IMETHODIMP nsUrlAtt::GetId(PRInt32 *aId)
{
     *aId=Id;
    return NS_OK;
}
NS_IMETHODIMP nsUrlAtt::SetId(PRInt32 aId)
{
     Id=aId;
    return NS_OK;
}
/* attribute AUTF8String Hash; */
NS_IMETHODIMP nsUrlAtt::GetHash(nsACString & aHash)
{
     if(Link.Length()>0&&Hash.Length()==0)
     {
	  SHA1 sha;
	  sha.Reset();
	  
	  sha << Link.get();
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
NS_IMETHODIMP nsUrlAtt::SetHash(const nsACString & aHash)
{
     Hash=aHash;
     return NS_OK;
}

/* attribute AUTF8String Link; */
NS_IMETHODIMP nsUrlAtt::GetLink(nsACString & aLink)
{
     aLink=Link;
     return NS_OK;
}
NS_IMETHODIMP nsUrlAtt::SetLink(const nsACString & aLink)
{
     Link=aLink;
     Link.StripChars("'");
     return NS_OK;
}

/* attribute AUTF8String Title; */
NS_IMETHODIMP nsUrlAtt::GetTitle(nsACString & aTitle)
{
     aTitle=Title;
     return NS_OK;
}
NS_IMETHODIMP nsUrlAtt::SetTitle(const nsACString & aTitle)
{
     Title=aTitle;
     Title.StripChars("'");
     return NS_OK;
}

/* attribute unsigned short Layer; */
NS_IMETHODIMP nsUrlAtt::GetLayer(PRUint16 *aLayer)
{
     *aLayer=Layer;
     return NS_OK;
}
NS_IMETHODIMP nsUrlAtt::SetLayer(PRUint16 aLayer)
{
     Layer=aLayer;
     return NS_OK;
}


/* attribute unsigned short urlType; */
NS_IMETHODIMP nsUrlAtt::GetUrlType(nsACString & aUrlType)
{
     aUrlType=urlType;
     return NS_OK;
}
NS_IMETHODIMP nsUrlAtt::SetUrlType(const nsACString & aUrlType)
{
     urlType=aUrlType;
     return NS_OK;
}

/* attribute unsigned short conType; */
NS_IMETHODIMP nsUrlAtt::GetConType(nsACString & aConType)
{
     aConType=conType;
     return NS_OK;
}
NS_IMETHODIMP nsUrlAtt::SetConType(const nsACString & aConType)
{
     conType=aConType;
    return NS_OK;
}
/* attribute long colId; */
NS_IMETHODIMP nsUrlAtt::GetColId(PRInt32 *aColId)
{
     *aColId=colId;
    return NS_OK;
}
NS_IMETHODIMP nsUrlAtt::SetColId(PRInt32 aColId)
{
     colId=aColId;
    return NS_OK;
}

/* attribute long nextId; */
NS_IMETHODIMP nsUrlAtt::GetNextId(PRInt32 *aNextId)
{
     *aNextId=nextId;
     return NS_OK;
}
NS_IMETHODIMP nsUrlAtt::SetNextId(PRInt32 aNextId)
{
     nextId=aNextId;
     return NS_OK;
}

/* attribute long parId; */
NS_IMETHODIMP nsUrlAtt::GetParId(PRInt32 *aParId)
{
     *aParId=parId;
    return NS_OK;
}
NS_IMETHODIMP nsUrlAtt::SetParId(PRInt32 aParId)
{
     parId=aParId;
     return NS_OK;
}


/* void SetURL (in AUTF8String Title, in AUTF8String Link, in AUTF8String chlName); */
NS_IMETHODIMP nsUrlAtt::SetURL(const nsACString & aTitle, const nsACString & aLink, PRUint32 aColId)
{
     Link=aLink;
     Link.StripChars("'");
     Title=aTitle;
     Title.StripChars("'");
     colId=aColId;
     return NS_OK;
}

/* attribute AUTF8String conAtt; */
NS_IMETHODIMP nsUrlAtt::GetConAtt(nsACString & aConAtt)
{
     aConAtt=conAtt;
    return NS_OK;
}
NS_IMETHODIMP nsUrlAtt::SetConAtt(const nsACString & aConAtt)
{
     conAtt=aConAtt;
    return NS_OK;
}
