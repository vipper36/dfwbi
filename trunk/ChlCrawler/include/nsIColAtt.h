/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIColAtt.idl
 */

#ifndef __gen_nsIColAtt_h__
#define __gen_nsIColAtt_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIColAtt */
#define NS_ICOLATT_IID_STR "3062b651-6ba3-4e6d-8bdc-d83b0095b864"

#define NS_ICOLATT_IID \
  {0x3062b651, 0x6ba3, 0x4e6d, \
    { 0x8b, 0xdc, 0xd8, 0x3b, 0x00, 0x95, 0xb8, 0x64 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIColAtt : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICOLATT_IID)

  /* attribute long Id; */
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) = 0;

  /* attribute long ChlId; */
  NS_SCRIPTABLE NS_IMETHOD GetChlId(PRInt32 *aChlId) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetChlId(PRInt32 aChlId) = 0;

  /* attribute AUTF8String Hash; */
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash) = 0;

  /* attribute AUTF8String Url; */
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsACString & aUrl) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetUrl(const nsACString & aUrl) = 0;

  /* attribute AUTF8String Name; */
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName) = 0;

  /* attribute AUTF8String Alias; */
  NS_SCRIPTABLE NS_IMETHOD GetAlias(nsACString & aAlias) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetAlias(const nsACString & aAlias) = 0;

  /* void SetCOL (in AUTF8String name, in AUTF8String url, in long chlId); */
  NS_SCRIPTABLE NS_IMETHOD SetCOL(const nsACString & name, const nsACString & url, PRInt32 chlId) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIColAtt, NS_ICOLATT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICOLATT \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId); \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId); \
  NS_SCRIPTABLE NS_IMETHOD GetChlId(PRInt32 *aChlId); \
  NS_SCRIPTABLE NS_IMETHOD SetChlId(PRInt32 aChlId); \
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash); \
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash); \
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsACString & aUrl); \
  NS_SCRIPTABLE NS_IMETHOD SetUrl(const nsACString & aUrl); \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName); \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName); \
  NS_SCRIPTABLE NS_IMETHOD GetAlias(nsACString & aAlias); \
  NS_SCRIPTABLE NS_IMETHOD SetAlias(const nsACString & aAlias); \
  NS_SCRIPTABLE NS_IMETHOD SetCOL(const nsACString & name, const nsACString & url, PRInt32 chlId); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICOLATT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) { return _to GetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) { return _to SetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD GetChlId(PRInt32 *aChlId) { return _to GetChlId(aChlId); } \
  NS_SCRIPTABLE NS_IMETHOD SetChlId(PRInt32 aChlId) { return _to SetChlId(aChlId); } \
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash) { return _to GetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash) { return _to SetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsACString & aUrl) { return _to GetUrl(aUrl); } \
  NS_SCRIPTABLE NS_IMETHOD SetUrl(const nsACString & aUrl) { return _to SetUrl(aUrl); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName) { return _to GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName) { return _to SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD GetAlias(nsACString & aAlias) { return _to GetAlias(aAlias); } \
  NS_SCRIPTABLE NS_IMETHOD SetAlias(const nsACString & aAlias) { return _to SetAlias(aAlias); } \
  NS_SCRIPTABLE NS_IMETHOD SetCOL(const nsACString & name, const nsACString & url, PRInt32 chlId) { return _to SetCOL(name, url, chlId); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICOLATT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD GetChlId(PRInt32 *aChlId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetChlId(aChlId); } \
  NS_SCRIPTABLE NS_IMETHOD SetChlId(PRInt32 aChlId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetChlId(aChlId); } \
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsACString & aUrl) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUrl(aUrl); } \
  NS_SCRIPTABLE NS_IMETHOD SetUrl(const nsACString & aUrl) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetUrl(aUrl); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD GetAlias(nsACString & aAlias) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAlias(aAlias); } \
  NS_SCRIPTABLE NS_IMETHOD SetAlias(const nsACString & aAlias) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAlias(aAlias); } \
  NS_SCRIPTABLE NS_IMETHOD SetCOL(const nsACString & name, const nsACString & url, PRInt32 chlId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCOL(name, url, chlId); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsColAtt : public nsIColAtt
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICOLATT

  nsColAtt();

private:
  ~nsColAtt();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsColAtt, nsIColAtt)

nsColAtt::nsColAtt()
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
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsColAtt::SetId(PRInt32 aId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long ChlId; */
NS_IMETHODIMP nsColAtt::GetChlId(PRInt32 *aChlId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsColAtt::SetChlId(PRInt32 aChlId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Hash; */
NS_IMETHODIMP nsColAtt::GetHash(nsACString & aHash)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsColAtt::SetHash(const nsACString & aHash)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Url; */
NS_IMETHODIMP nsColAtt::GetUrl(nsACString & aUrl)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsColAtt::SetUrl(const nsACString & aUrl)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Name; */
NS_IMETHODIMP nsColAtt::GetName(nsACString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsColAtt::SetName(const nsACString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Alias; */
NS_IMETHODIMP nsColAtt::GetAlias(nsACString & aAlias)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsColAtt::SetAlias(const nsACString & aAlias)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCOL (in AUTF8String name, in AUTF8String url, in long chlId); */
NS_IMETHODIMP nsColAtt::SetCOL(const nsACString & name, const nsACString & url, PRInt32 chlId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIColAtt_h__ */
