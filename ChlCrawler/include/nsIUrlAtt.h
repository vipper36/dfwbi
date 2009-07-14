/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIUrlAtt.idl
 */

#ifndef __gen_nsIUrlAtt_h__
#define __gen_nsIUrlAtt_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIUrlAtt */
#define NS_IURLATT_IID_STR "2e5632c1-e046-4a50-9b47-496dbb9d3cb4"

#define NS_IURLATT_IID \
  {0x2e5632c1, 0xe046, 0x4a50, \
    { 0x9b, 0x47, 0x49, 0x6d, 0xbb, 0x9d, 0x3c, 0xb4 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIUrlAtt : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IURLATT_IID)

  /* attribute long Id; */
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) = 0;

  /* attribute AUTF8String Hash; */
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash) = 0;

  /* attribute AUTF8String Link; */
  NS_SCRIPTABLE NS_IMETHOD GetLink(nsACString & aLink) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetLink(const nsACString & aLink) = 0;

  /* attribute AUTF8String Title; */
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsACString & aTitle) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & aTitle) = 0;

  /* attribute unsigned short Layer; */
  NS_SCRIPTABLE NS_IMETHOD GetLayer(PRUint16 *aLayer) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetLayer(PRUint16 aLayer) = 0;

  /* attribute AUTF8String urlType; */
  NS_SCRIPTABLE NS_IMETHOD GetUrlType(nsACString & aUrlType) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetUrlType(const nsACString & aUrlType) = 0;

  /* attribute AUTF8String conType; */
  NS_SCRIPTABLE NS_IMETHOD GetConType(nsACString & aConType) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetConType(const nsACString & aConType) = 0;

  /* attribute AUTF8String conAtt; */
  NS_SCRIPTABLE NS_IMETHOD GetConAtt(nsACString & aConAtt) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetConAtt(const nsACString & aConAtt) = 0;

  /* attribute long colId; */
  NS_SCRIPTABLE NS_IMETHOD GetColId(PRInt32 *aColId) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetColId(PRInt32 aColId) = 0;

  /* attribute long nextId; */
  NS_SCRIPTABLE NS_IMETHOD GetNextId(PRInt32 *aNextId) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetNextId(PRInt32 aNextId) = 0;

  /* attribute long parId; */
  NS_SCRIPTABLE NS_IMETHOD GetParId(PRInt32 *aParId) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetParId(PRInt32 aParId) = 0;

  /* void SetURL (in AUTF8String Title, in AUTF8String Link, in unsigned long colId); */
  NS_SCRIPTABLE NS_IMETHOD SetURL(const nsACString & Title, const nsACString & Link, PRUint32 colId) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIUrlAtt, NS_IURLATT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIURLATT \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId); \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId); \
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash); \
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash); \
  NS_SCRIPTABLE NS_IMETHOD GetLink(nsACString & aLink); \
  NS_SCRIPTABLE NS_IMETHOD SetLink(const nsACString & aLink); \
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsACString & aTitle); \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & aTitle); \
  NS_SCRIPTABLE NS_IMETHOD GetLayer(PRUint16 *aLayer); \
  NS_SCRIPTABLE NS_IMETHOD SetLayer(PRUint16 aLayer); \
  NS_SCRIPTABLE NS_IMETHOD GetUrlType(nsACString & aUrlType); \
  NS_SCRIPTABLE NS_IMETHOD SetUrlType(const nsACString & aUrlType); \
  NS_SCRIPTABLE NS_IMETHOD GetConType(nsACString & aConType); \
  NS_SCRIPTABLE NS_IMETHOD SetConType(const nsACString & aConType); \
  NS_SCRIPTABLE NS_IMETHOD GetConAtt(nsACString & aConAtt); \
  NS_SCRIPTABLE NS_IMETHOD SetConAtt(const nsACString & aConAtt); \
  NS_SCRIPTABLE NS_IMETHOD GetColId(PRInt32 *aColId); \
  NS_SCRIPTABLE NS_IMETHOD SetColId(PRInt32 aColId); \
  NS_SCRIPTABLE NS_IMETHOD GetNextId(PRInt32 *aNextId); \
  NS_SCRIPTABLE NS_IMETHOD SetNextId(PRInt32 aNextId); \
  NS_SCRIPTABLE NS_IMETHOD GetParId(PRInt32 *aParId); \
  NS_SCRIPTABLE NS_IMETHOD SetParId(PRInt32 aParId); \
  NS_SCRIPTABLE NS_IMETHOD SetURL(const nsACString & Title, const nsACString & Link, PRUint32 colId); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIURLATT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) { return _to GetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) { return _to SetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash) { return _to GetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash) { return _to SetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD GetLink(nsACString & aLink) { return _to GetLink(aLink); } \
  NS_SCRIPTABLE NS_IMETHOD SetLink(const nsACString & aLink) { return _to SetLink(aLink); } \
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsACString & aTitle) { return _to GetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & aTitle) { return _to SetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD GetLayer(PRUint16 *aLayer) { return _to GetLayer(aLayer); } \
  NS_SCRIPTABLE NS_IMETHOD SetLayer(PRUint16 aLayer) { return _to SetLayer(aLayer); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrlType(nsACString & aUrlType) { return _to GetUrlType(aUrlType); } \
  NS_SCRIPTABLE NS_IMETHOD SetUrlType(const nsACString & aUrlType) { return _to SetUrlType(aUrlType); } \
  NS_SCRIPTABLE NS_IMETHOD GetConType(nsACString & aConType) { return _to GetConType(aConType); } \
  NS_SCRIPTABLE NS_IMETHOD SetConType(const nsACString & aConType) { return _to SetConType(aConType); } \
  NS_SCRIPTABLE NS_IMETHOD GetConAtt(nsACString & aConAtt) { return _to GetConAtt(aConAtt); } \
  NS_SCRIPTABLE NS_IMETHOD SetConAtt(const nsACString & aConAtt) { return _to SetConAtt(aConAtt); } \
  NS_SCRIPTABLE NS_IMETHOD GetColId(PRInt32 *aColId) { return _to GetColId(aColId); } \
  NS_SCRIPTABLE NS_IMETHOD SetColId(PRInt32 aColId) { return _to SetColId(aColId); } \
  NS_SCRIPTABLE NS_IMETHOD GetNextId(PRInt32 *aNextId) { return _to GetNextId(aNextId); } \
  NS_SCRIPTABLE NS_IMETHOD SetNextId(PRInt32 aNextId) { return _to SetNextId(aNextId); } \
  NS_SCRIPTABLE NS_IMETHOD GetParId(PRInt32 *aParId) { return _to GetParId(aParId); } \
  NS_SCRIPTABLE NS_IMETHOD SetParId(PRInt32 aParId) { return _to SetParId(aParId); } \
  NS_SCRIPTABLE NS_IMETHOD SetURL(const nsACString & Title, const nsACString & Link, PRUint32 colId) { return _to SetURL(Title, Link, colId); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIURLATT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetId(PRInt32 *aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD SetId(PRInt32 aId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetId(aId); } \
  NS_SCRIPTABLE NS_IMETHOD GetHash(nsACString & aHash) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD SetHash(const nsACString & aHash) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetHash(aHash); } \
  NS_SCRIPTABLE NS_IMETHOD GetLink(nsACString & aLink) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLink(aLink); } \
  NS_SCRIPTABLE NS_IMETHOD SetLink(const nsACString & aLink) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLink(aLink); } \
  NS_SCRIPTABLE NS_IMETHOD GetTitle(nsACString & aTitle) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD SetTitle(const nsACString & aTitle) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTitle(aTitle); } \
  NS_SCRIPTABLE NS_IMETHOD GetLayer(PRUint16 *aLayer) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLayer(aLayer); } \
  NS_SCRIPTABLE NS_IMETHOD SetLayer(PRUint16 aLayer) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLayer(aLayer); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrlType(nsACString & aUrlType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUrlType(aUrlType); } \
  NS_SCRIPTABLE NS_IMETHOD SetUrlType(const nsACString & aUrlType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetUrlType(aUrlType); } \
  NS_SCRIPTABLE NS_IMETHOD GetConType(nsACString & aConType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetConType(aConType); } \
  NS_SCRIPTABLE NS_IMETHOD SetConType(const nsACString & aConType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetConType(aConType); } \
  NS_SCRIPTABLE NS_IMETHOD GetConAtt(nsACString & aConAtt) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetConAtt(aConAtt); } \
  NS_SCRIPTABLE NS_IMETHOD SetConAtt(const nsACString & aConAtt) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetConAtt(aConAtt); } \
  NS_SCRIPTABLE NS_IMETHOD GetColId(PRInt32 *aColId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetColId(aColId); } \
  NS_SCRIPTABLE NS_IMETHOD SetColId(PRInt32 aColId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetColId(aColId); } \
  NS_SCRIPTABLE NS_IMETHOD GetNextId(PRInt32 *aNextId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNextId(aNextId); } \
  NS_SCRIPTABLE NS_IMETHOD SetNextId(PRInt32 aNextId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetNextId(aNextId); } \
  NS_SCRIPTABLE NS_IMETHOD GetParId(PRInt32 *aParId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetParId(aParId); } \
  NS_SCRIPTABLE NS_IMETHOD SetParId(PRInt32 aParId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetParId(aParId); } \
  NS_SCRIPTABLE NS_IMETHOD SetURL(const nsACString & Title, const nsACString & Link, PRUint32 colId) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetURL(Title, Link, colId); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsUrlAtt : public nsIUrlAtt
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIURLATT

  nsUrlAtt();

private:
  ~nsUrlAtt();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsUrlAtt, nsIUrlAtt)

nsUrlAtt::nsUrlAtt()
{
  /* member initializers and constructor code */
}

nsUrlAtt::~nsUrlAtt()
{
  /* destructor code */
}

/* attribute long Id; */
NS_IMETHODIMP nsUrlAtt::GetId(PRInt32 *aId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUrlAtt::SetId(PRInt32 aId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Hash; */
NS_IMETHODIMP nsUrlAtt::GetHash(nsACString & aHash)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUrlAtt::SetHash(const nsACString & aHash)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Link; */
NS_IMETHODIMP nsUrlAtt::GetLink(nsACString & aLink)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUrlAtt::SetLink(const nsACString & aLink)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String Title; */
NS_IMETHODIMP nsUrlAtt::GetTitle(nsACString & aTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUrlAtt::SetTitle(const nsACString & aTitle)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute unsigned short Layer; */
NS_IMETHODIMP nsUrlAtt::GetLayer(PRUint16 *aLayer)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUrlAtt::SetLayer(PRUint16 aLayer)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String urlType; */
NS_IMETHODIMP nsUrlAtt::GetUrlType(nsACString & aUrlType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUrlAtt::SetUrlType(const nsACString & aUrlType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String conType; */
NS_IMETHODIMP nsUrlAtt::GetConType(nsACString & aConType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUrlAtt::SetConType(const nsACString & aConType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute AUTF8String conAtt; */
NS_IMETHODIMP nsUrlAtt::GetConAtt(nsACString & aConAtt)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUrlAtt::SetConAtt(const nsACString & aConAtt)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long colId; */
NS_IMETHODIMP nsUrlAtt::GetColId(PRInt32 *aColId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUrlAtt::SetColId(PRInt32 aColId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long nextId; */
NS_IMETHODIMP nsUrlAtt::GetNextId(PRInt32 *aNextId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUrlAtt::SetNextId(PRInt32 aNextId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long parId; */
NS_IMETHODIMP nsUrlAtt::GetParId(PRInt32 *aParId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsUrlAtt::SetParId(PRInt32 aParId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetURL (in AUTF8String Title, in AUTF8String Link, in unsigned long colId); */
NS_IMETHODIMP nsUrlAtt::SetURL(const nsACString & Title, const nsACString & Link, PRUint32 colId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIUrlAtt_h__ */
