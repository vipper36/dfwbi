/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIChlAtt.idl
 */

#ifndef __gen_nsIChlAtt_h__
#define __gen_nsIChlAtt_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIChlAtt */
#define NS_ICHLATT_IID_STR "e737af45-9b30-4dcd-ae4d-2d355a6f13b3"

#define NS_ICHLATT_IID \
  {0xe737af45, 0x9b30, 0x4dcd, \
    { 0xae, 0x4d, 0x2d, 0x35, 0x5a, 0x6f, 0x13, 0xb3 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIChlAtt : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICHLATT_IID)

  /* attribute long Id; */
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) = 0;

  /* attribute AUTF8String Hash; */
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash) = 0;

  /* attribute AUTF8String Url; */
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsACString & aUrl) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetUrl(const nsACString & aUrl) = 0;

  /* attribute AUTF8String Name; */
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName) = 0;

  /* attribute AUTF8String XPath; */
  NS_SCRIPTABLE NS_IMETHOD GetXPath(nsACString & aXPath) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetXPath(const nsACString & aXPath) = 0;

  /* void SetCHL (in AUTF8String name, in AUTF8String url); */
  NS_SCRIPTABLE NS_IMETHOD SetCHL(const nsACString & name, const nsACString & url) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIChlAtt, NS_ICHLATT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICHLATT \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId); \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId); \
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash); \
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash); \
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsACString & aUrl); \
  NS_SCRIPTABLE NS_IMETHOD SetUrl(const nsACString & aUrl); \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName); \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName); \
  NS_SCRIPTABLE NS_IMETHOD GetXPath(nsACString & aXPath); \
  NS_SCRIPTABLE NS_IMETHOD SetXPath(const nsACString & aXPath); \
  NS_SCRIPTABLE NS_IMETHOD SetCHL(const nsACString & name, const nsACString & url); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICHLATT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) { return _to GetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) { return _to SetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash) { return _to GetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash) { return _to SetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsACString & aUrl) { return _to GetUrl(aUrl); } \
  NS_SCRIPTABLE NS_IMETHOD SetUrl(const nsACString & aUrl) { return _to SetUrl(aUrl); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName) { return _to GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName) { return _to SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD GetXPath(nsACString & aXPath) { return _to GetXPath(aXPath); } \
  NS_SCRIPTABLE NS_IMETHOD SetXPath(const nsACString & aXPath) { return _to SetXPath(aXPath); } \
  NS_SCRIPTABLE NS_IMETHOD SetCHL(const nsACString & name, const nsACString & url) { return _to SetCHL(name, url); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICHLATT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrl(nsACString & aUrl) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUrl(aUrl); } \
  NS_SCRIPTABLE NS_IMETHOD SetUrl(const nsACString & aUrl) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetUrl(aUrl); } \
  NS_SCRIPTABLE NS_IMETHOD GetName(nsACString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD SetName(const nsACString & aName) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetName(aName); } \
  NS_SCRIPTABLE NS_IMETHOD GetXPath(nsACString & aXPath) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetXPath(aXPath); } \
  NS_SCRIPTABLE NS_IMETHOD SetXPath(const nsACString & aXPath) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetXPath(aXPath); } \
  NS_SCRIPTABLE NS_IMETHOD SetCHL(const nsACString & name, const nsACString & url) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCHL(name, url); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsChlAtt : public nsIChlAtt
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICHLATT

  nsChlAtt();

private:
  ~nsChlAtt();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsChlAtt, nsIChlAtt)

nsChlAtt::nsChlAtt()
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
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsChlAtt::SetId(PRInt32 aId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Hash; */
NS_IMETHODIMP nsChlAtt::GetHash(nsACString & aHash)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsChlAtt::SetHash(const nsACString & aHash)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Url; */
NS_IMETHODIMP nsChlAtt::GetUrl(nsACString & aUrl)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsChlAtt::SetUrl(const nsACString & aUrl)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Name; */
NS_IMETHODIMP nsChlAtt::GetName(nsACString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsChlAtt::SetName(const nsACString & aName)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String XPath; */
NS_IMETHODIMP nsChlAtt::GetXPath(nsACString & aXPath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsChlAtt::SetXPath(const nsACString & aXPath)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCHL (in AUTF8String name, in AUTF8String url); */
NS_IMETHODIMP nsChlAtt::SetCHL(const nsACString & name, const nsACString & url)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIChlAtt_h__ */
